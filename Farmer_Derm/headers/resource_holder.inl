#pragma once
#include "resource_holder.h"

template <typename Resource, typename Identifier>
void fd::ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename) {
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// Insert and check success
	auto inserted = resource_map_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void fd::ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename, const Parameter& second_parameter) {
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, second_parameter))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// Insert and check success
	auto inserted = resource_map_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& fd::ResourceHolder<Resource, Identifier>::Get(Identifier id)
{
	auto found = resource_map_.find(id);
	assert(found != resource_map_.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& fd::ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	auto found = resource_map_.find(id);
	assert(found != resource_map_.end());

	return *found->second;
}


