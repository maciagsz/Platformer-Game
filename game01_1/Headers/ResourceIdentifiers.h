#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

import Headers;

namespace Textures
{
    enum ID
    {
        WorldBackground,
        WorldTiles,
        PlayerDefault,
        Bush1,
        Bush2,
        Crate,
        Mushroom,
        Sign,
        Stone,
        Tree1,
        Tree2,
        TitleScreenBackground,
        ButtonNormal,
        ButtonSelected,
        ButtonPressed,
        TextureCount
    };
}

namespace Fonts
{
    enum ID
    {
        MenuFont,
        TitleFont,
        Score,
        FontCount
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

//typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
//typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif // RESOURCEIDENTIFIERS_HPP
