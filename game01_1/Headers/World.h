#ifndef WORLD_H
#define WORLD_H

import Headers;
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

constexpr auto WORLD_WIDTH = 128;
constexpr auto WORLD_HEIGHT = 8;

class World : public sf::Drawable, public sf::Transformable
{
    int** world_map;
    TextureHolder world_textures;
    sf::Vector2u world_tile_size;

public:
    World();
    ~World() override;

    bool is_finished;
    sf::VertexArray world_vertices;
    sf::Sprite background_sprite;

    void worldInitialize();
    void loadTerrain(const std::filesystem::path&) const;
    void mapIntToTile();
    void setFinish();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // !WORLD_H
