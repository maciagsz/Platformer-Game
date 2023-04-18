#include "ResourceHolder.h"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadResource(Identifier id, const std::filesystem::path& filepath)
{
	std::string path_string{ filepath.string() };

	if (!exists(filepath))
		throw std::runtime_error("ResourceHolder::load_resource failed to load resource: " + path_string);

	std::unique_ptr<Resource> resource(new Resource());
	resource->loadFromFile(path_string);

	auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::loadResource(Identifier id, const std::filesystem::path& filepath,
	const Parameter& second_param)
{
	std::string path_string{ filepath.string() };

	if (!exists(filepath))
		throw std::runtime_error("ResourceHolder::load_resource failed to load resource: " + path_string);

	std::unique_ptr<Resource> resource(new Resource());
	resource->loadFromFile(filepath, path_string);

	auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::getResource(Identifier id)
{
	auto found = resource_map.find(id);
	assert(found != resource_map.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::getResource(Identifier id) const
{
	auto found = resource_map.find(id);
	assert(found != resource_map.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	auto inserted = resource_map.insert(std::make_pair(id, std::move(resource)));
	//assert(inserted.second);
}