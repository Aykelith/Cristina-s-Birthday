#include <Game/Player.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace XAL {
    void Player::load(const json& configurationJSON) {
        m_sprite.setSize({50.f, 100.f});
        m_sprite.setFillColor(sf::Color::Green);

        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height);
    }

    void Player::update(float dt) {

    }

    void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
    }
}
