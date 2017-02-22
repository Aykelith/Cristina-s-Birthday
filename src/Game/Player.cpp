#include <Game/Player.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <Debug/Stream.hpp>

namespace XAL {
    void Player::load(const json& configurationJSON) {
        m_sprite.setSize({50.f, 100.f});
        m_sprite.setFillColor(sf::Color::Green);

        m_sprite.setOrigin(m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height);
    }

    void Player::update(float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_onGround) {
            m_onGround = false;
        }

        if (!m_onGround) {
            auto pos = getPosition();
            if (!m_maxJumpReached) {
                if (getPosition().y > MAXIM_JUMP_HEIGHT) {
                    setPosition(pos.x, pos.y - dt * JUMP_SPEED * m_gameSpeed);
                } else {
                    m_maxJumpReached = true;
                }
            } else {
                setPosition(pos.x, pos.y + dt * JUMP_SPEED * m_gameSpeed);

                if (getPosition().y >= m_floorPosition) {
                    setPosition(pos.x, m_floorPosition);
                    m_onGround = true;
                    m_maxJumpReached = false;
                }
            }
        }
    }

    void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
    }
}
