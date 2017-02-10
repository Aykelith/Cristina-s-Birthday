#ifndef XAL_PLAYER_HPP
#define XAL_PLAYER_HPP

#include <Global.hpp>

#include <JSONTools.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace XAL {
    class Player: public sf::Drawable, public sf::Transformable {
    public:
        Player() = default;
        void load(const json& configurationJSON);

        void update(float dt);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape m_sprite;
    };
}

#endif
