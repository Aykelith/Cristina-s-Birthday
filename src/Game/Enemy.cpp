#include <Game/Enemy.hpp>

#include <JSONTools.hpp>

namespace XAL {
    Enemy::Enemy(const json& configurationJSON, Animation& animation)
    : Entity { configurationJSON, animation }
    {
        
    }

    void Enemy::configure(const json& configurationJSON) {

    }

    void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        Entity::draw(target, states);
    }
}
