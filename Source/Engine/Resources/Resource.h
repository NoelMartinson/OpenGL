#pragma once
#include <memory>

namespace neu {
    
    class Resource {
    public:
       
        Resource() = default;
                
        virtual ~Resource() = default;

        std::string name;
    };

    
    template <typename T = Resource>
        requires std::derived_from<T, Resource>
	using res_t = std::shared_ptr<T>;
}