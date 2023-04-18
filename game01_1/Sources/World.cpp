#include "../Headers/World.h"
#include "../Headers/Game.h"

World::World()
    : world_tile_size(TILE_SIZE - 1, TILE_SIZE - 1)
{
    world_textures.loadResource(Textures::ID::WorldBackground, "Resources/textures/world_background.png");
    sf::Texture& background_texture = world_textures.getResource(Textures::ID::WorldBackground);
    background_texture.setRepeated(true);
    background_texture.setSmooth(false);
    background_sprite.setTexture(world_textures.getResource(Textures::ID::WorldBackground));
    background_sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE * WORLD_WIDTH, TILE_SIZE * WORLD_HEIGHT));
    world_textures.loadResource(Textures::ID::WorldTiles, "Resources/textures/tileset_level1.png");
    sf::Texture& tile_texture = world_textures.getResource(Textures::ID::WorldTiles);
    tile_texture.setSmooth(false);

    world_map = new int* [WORLD_HEIGHT];
    for (int i = 0; i < WORLD_HEIGHT; i++)
        world_map[i] = new int[WORLD_WIDTH];

    is_finished = false;
}

World::~World()
{
    for (int i = 0; i < WORLD_HEIGHT; i++)
        delete[] world_map[i];
    delete[] world_map;
    world_map = nullptr;
}

void World::worldInitialize()
{
    loadTerrain("Resources/maps/map2.txt");
    mapIntToTile();
}

void World::loadTerrain(const std::filesystem::path& path) const
{
    if (!exists(path))
        throw std::exception("World terrain file does not exist!");

    std::fstream world_terrain;
    world_terrain.open(path);

    if (!world_terrain.is_open())
        throw std::exception("Could not open world terrain file.");

    for (int i = 0; i < WORLD_HEIGHT; i++)
        for (int j = 0; j < WORLD_WIDTH; j++)
        {
            char buffer;
            world_terrain >> buffer;
            world_map[i][j] = (buffer - '0');
        }

    world_terrain.close();
}

void World::mapIntToTile()
{
    world_vertices.setPrimitiveType(sf::Quads);
    world_vertices.resize(WORLD_HEIGHT * WORLD_WIDTH * 4);

    for (int i = 0; i < WORLD_WIDTH; ++i)
    {
        for (int j = 0; j < WORLD_HEIGHT; ++j)
        {
            const int tile_number = world_map[j][i];

            if (tile_number != 0)
            {
                const int tu = tile_number % (world_textures.getResource(Textures::ID::WorldTiles).getSize().x /
                    world_tile_size.x);
                const int tv = tile_number / (world_textures.getResource(Textures::ID::WorldTiles).getSize().x /
                    world_tile_size.x);

                sf::Vertex* quad = &world_vertices[(i + j * WORLD_WIDTH) * 4];

                quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
                quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
                quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
                quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

                quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
                quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
                quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
                quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
            }
        }
    }
}

void World::setFinish()
{
    is_finished = true;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &world_textures.getResource(Textures::ID::WorldBackground);
    target.draw(background_sprite, states);

    states.texture = &world_textures.getResource(Textures::ID::WorldTiles);
    target.draw(world_vertices, states);
}