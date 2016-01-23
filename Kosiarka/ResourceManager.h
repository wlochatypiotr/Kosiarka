#pragma once
#include <unordered_map>
#include "SFML\Graphics.hpp"
#include <memory>

template <typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	RESOURCE& get(const IDENTIFIER& id);				//get resource
	template<typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);
private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
};

template<typename RESOURCE, typename IDENTIFIER>
inline RESOURCE & ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER & id)
{
	return *_map[id];
}

template<typename RESOURCE, typename IDENTIFIER>
template<typename ...Args>
inline void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER & id, Args && ... args)
{
	std::unique_ptr<RESOURCE> ptr(new RESOURCE);
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("File loading failed");
	_map.emplace(id, std::move(ptr));
}
