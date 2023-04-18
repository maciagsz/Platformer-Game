#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

import Headers;
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class WorldObject : public sf::Drawable, public sf::Transformable
{
    TextureHolder worldobject_textures;

public:
    WorldObject();

    std::vector<sf::Sprite> worldobject_sprites;

    void create(Textures::ID id, sf::Vector2f pos);
    void find(sf::FloatRect);
    void remove(int);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif //!WORLDOBJECT_H