#include "../Headers/WorldObject.h"

WorldObject::WorldObject()
{
	worldobject_textures.loadResource(Textures::ID::Bush1, "Resources/textures/worldobjects/bush1.png");
	worldobject_textures.loadResource(Textures::ID::Bush2, "Resources/textures/worldobjects/bush2.png");
	worldobject_textures.loadResource(Textures::ID::Crate, "Resources/textures/worldobjects/crate.png");
	worldobject_textures.loadResource(Textures::ID::Mushroom, "Resources/textures/worldobjects/mushroom.png");
	worldobject_textures.loadResource(Textures::ID::Sign, "Resources/textures/worldobjects/sign.png");
	worldobject_textures.loadResource(Textures::ID::Stone, "Resources/textures/worldobjects/stone.png");
	worldobject_textures.loadResource(Textures::ID::Tree1, "Resources/textures/worldobjects/tree1.png");
	worldobject_textures.loadResource(Textures::ID::Tree2, "Resources/textures/worldobjects/tree2.png");
}

void WorldObject::create(Textures::ID id, sf::Vector2f pos)
{
	sf::Sprite sprite;
	sprite.setTexture(worldobject_textures.getResource(id));
	sprite.setPosition(pos);
	worldobject_sprites.push_back(sprite);
}

void WorldObject::find(sf::FloatRect bounds)
{
	auto it = std::find_if(worldobject_sprites.begin(), worldobject_sprites.end(), [&](const sf::Sprite& sprite)
		{
			return sprite.getGlobalBounds() == bounds;
		});
}

void WorldObject::remove(int id)
{
	worldobject_sprites.erase(worldobject_sprites.begin() + id);
}

void WorldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : worldobject_sprites)
		target.draw(i, states);
}