#include <Managers/EnemiesManager.hpp>

#include <Debug/Stream.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace XAL {
    EnemiesManager::EnemiesManager(AnimationsManager& animationsManager)
    : EntitiesManager { animationsManager }
    { }

    void EnemiesManager::update(float dt, float distance) {
        for (auto it = m_upcomingEntities.begin(); it != m_upcomingEntities.end(); ) {
            if (it->first > distance + DISTANCE_TO_SHOW) {
                break;
            } else {
                xalDebug() << "EnemiesManager(): update(): new enemy with pos" << it->first << " lower than" << distance + DISTANCE_TO_SHOW;
                m_entities.push_back(m_sampleEntities.at(it->second));
                m_entities.back().setInitialPosition({m_windowWidth + it->first - distance, m_floorY});

                xalDebug() << "at position" << m_entities.back().position();
                it = m_upcomingEntities.erase(it);
            }
        }

        for (auto it = m_entities.begin(); it != m_entities.end(); ) {
            it->update(dt, m_gameSpeed);
            bool needDelete = m_updateFunction(*it);

            if (needDelete || it->position(true) < 0) {
                it = m_entities.erase(it);
            } else {
                ++it;
            }
        }
    }
}
