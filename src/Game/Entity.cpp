#include <Game/Entity.hpp>

#include <Debug/Stream.hpp>
#include <JSONTools.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace XAL {
    Entity::Entity(const json& configurationJSON, Animation& animation)
    : m_animation { &animation }
    {

    }

    float Entity::position(bool rightPosition) const {
        return (rightPosition) ? m_sprite.getPosition().x + m_sprite.getOrigin().x : m_sprite.getPosition().x - m_sprite.getOrigin().x;
    }

    void Entity::setTexture(const std::shared_ptr<sf::Texture>& texture) {
        m_texture = texture;
        m_sprite.setTexture(*m_texture);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height);
    }

    void Entity::update(float dt, float gameSpeed) {
        m_sprite.setPosition(m_sprite.getPosition().x - dt * gameSpeed, m_sprite.getPosition().y);
        m_sprite.setTextureRect(m_animation->animate(dt));
    }

    void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_sprite, states);
    }
}
