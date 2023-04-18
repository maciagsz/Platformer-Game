#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

import Headers;

template <typename Resource, typename Identifier>
class ResourceHolder
{
    std::map<Identifier, std::unique_ptr<Resource>> resource_map;
    void insertResource(Identifier, std::unique_ptr<Resource>);

public:
    void loadResource(Identifier, const std::filesystem::path&);

    template <typename Parameter>
    void loadResource(Identifier, const std::filesystem::path&, const Parameter&);

    Resource& getResource(Identifier);
    const Resource& getResource(Identifier) const;
};

#include "ResourceHolder.inl"

#endif // !RESOURCEHOLDER_H
