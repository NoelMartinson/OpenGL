#pragma once
#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include "Core/Logger.h"
#include "Resource.h"
#include <string>
#include <map>
#include <iostream>

namespace neu {
    class ResourceManager : public Singleton<ResourceManager> {
    public:
        void RemoveAll() { m_resources.clear(); }
        
        template<typename T, typename ... Args>
            requires std::derived_from<T, Resource>
        res_t<T> Get(const std::string& name, Args&& ... args);
        
        template<typename T, typename ... Args>
            requires std::derived_from<T, Resource>
        res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);

        template<typename T = Resource>
            requires std::derived_from<T, Resource>
        std::vector<T*> GetByType();


    private:
        
        friend class Singleton<ResourceManager>;

        ResourceManager() = default;

    private:
        std::map<std::string, res_t<Resource>> m_resources;
    };

    template<typename T, typename ... Args>
        requires std::derived_from<T, Resource>
    inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args) {
        return GetWithID<T>(name, name, std::forward<Args>(args)...);
    }

    template<typename T, typename ...Args>
        requires std::derived_from<T, Resource>
    inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args && ...args) {
        std::string key = toLower(id);

        auto iter = m_resources.find(key);
        if (iter != m_resources.end()) {
            auto base = iter->second;
            auto resource = std::dynamic_pointer_cast<T>(base);

            if (resource == nullptr) {
                LOG_ERROR("Resource type mismatch: {}", key);
                return res_t<T>(); 
            }

            return resource;
        }

        res_t<T> resource = std::make_shared<T>();

        if (resource->Load(name, std::forward<Args>(args)...) == false) {
            LOG_ERROR("Could not load resource: {}", name);
            return res_t<T>(); 
        }

        resource->name = key;
        m_resources[key] = resource;

        return resource;
    }

    template<typename T>
        requires std::derived_from<T, Resource>
    inline std::vector<T*> ResourceManager::GetByType()
    {
        std::vector<T*> results;

        for (auto& resource : m_resources) {
            auto result = dynamic_cast<T*>(resource.second.get());
            if (result) {
                results.push_back(result);
            }
        }

        return results;
    }

    inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}