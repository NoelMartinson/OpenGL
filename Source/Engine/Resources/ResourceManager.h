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

    private:
        
        friend class Singleton<ResourceManager>;

        /// <summary>
        /// Private default constructor to enforce singleton pattern.
        /// Only accessible through the Singleton base class Instance() method.
        /// </summary>
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
        // Normalize the cache key to lowercase for case-insensitive lookup
        std::string key = toLower(id);

        // Check if resource already exists in cache
        auto iter = m_resources.find(key);
        if (iter != m_resources.end()) {
            // Resource found in cache - attempt to cast to requested type
            auto base = iter->second;
            auto resource = std::dynamic_pointer_cast<T>(base);

            // Verify the cast was successful (type safety check)
            if (resource == nullptr) {
                LOG_ERROR("Resource type mismatch: {}", key);
                return res_t<T>();  // Return empty shared_ptr on type mismatch
            }

            // Return the cached resource with correct type
            return resource;
        }

        // Resource not in cache - create and load new instance
        res_t<T> resource = std::make_shared<T>();

        // Attempt to load the resource with provided arguments
        // Perfect forwarding preserves argument value categories
        if (resource->Load(name, std::forward<Args>(args)...) == false) {
            LOG_ERROR("Could not load resource: {}", name);
            return res_t<T>();  // Return empty shared_ptr on load failure
        }

        // Successfully loaded - add to cache for future use
        // Store as base Resource pointer for type erasure
        m_resources[key] = resource;
        resource->name = key;

        return resource;
    }
      
    inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}