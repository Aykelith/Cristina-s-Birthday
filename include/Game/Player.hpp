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

        bool isAttacking() const { return false; }
        float getHairPosition() const { return getPosition().y; }

        void setFloorPosition(float pos) { m_floorPosition = pos; }
        void setGameSpeed(float speed) { m_gameSpeed = speed; }

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        static constexpr float MAXIM_JUMP_HEIGHT = 200.f;
        static constexpr float JUMP_SPEED = 4.f;

    private:
        sf::RectangleShape m_sprite;

        bool m_maxJumpReached = false;
        bool m_onGround = true;

        float m_gameSpeed;
        float m_floorPosition;
    };
}

#endif
