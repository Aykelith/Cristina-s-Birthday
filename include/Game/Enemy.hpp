#ifndef XAL_ENEMY_HPP
#define XAL_ENEMY_HPP

#include <string>

#include <Game/Entity.hpp>

namespace XAL {
    class Enemy: public Entity {
    public:
        Enemy(const json& configurationJSON, Animation& animation);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void configure(const json& configurationJSON);
    };
}

#endif // XAL_ENEMY_HPP
