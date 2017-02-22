#ifndef XAL_ENTITY_HPP
#define XAL_ENTITY_HPP

#include <Global.hpp>

#include <string>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

#include <JSONTools.hpp>
#include <Game/Animation.hpp>

namespace XAL {
    class Entity: public sf::Drawable {
    public:
        Entity(const json& configurationJSON, Animation& animation);

        void setInitialPosition(const sf::Vector2f& pos) { m_sprite.setPosition(pos); }

        float position(bool rightPosition = false) const;
        

        void setTexture(const std::shared_ptr<sf::Texture>& texture);

        virtual void update(float dt, float gameSpeed);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        std::shared_ptr<sf::Texture> m_texture = nullptr;
        sf::Sprite m_sprite;
        std::shared_ptr<Animation> m_animation = nullptr;
    };
}

#endif // XAL_ENTITY_HPP
