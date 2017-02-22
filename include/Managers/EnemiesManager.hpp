#ifndef XAL_ENEMIESMANAGER_HPP
#define XAL_ENEMIESMANAGER_HPP

#include <Global.hpp>

#include <Game/Enemy.hpp>

#include <Managers/EntitiesManager.hpp>

namespace XAL { class AnimationsManager; }

namespace XAL {
    class EnemiesManager: public EntitiesManager<Enemy> {
    public:
        EnemiesManager(AnimationsManager& animationsManager);

        void setUpdateFunction(const std::function<bool(const Enemy&)>& updateFunction) { m_updateFunction = updateFunction; }
        void update(float dt, float distance);

    private:
        std::function<bool(const Enemy&)> m_updateFunction;
    };
}

#endif
