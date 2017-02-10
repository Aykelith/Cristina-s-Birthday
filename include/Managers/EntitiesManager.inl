#include <Managers/AnimationsManager.hpp>

#include <Debug/Stream.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace XAL {
    template <class T>
    EntitiesManager<T>::EntitiesManager(AnimationsManager& animationsManager)
    : m_animationsManager { animationsManager }
    { }

    template <class T>
    void EntitiesManager<T>::loadEntitySample(const json& configurationJSON, const std::string& id) {
        std::string animationFile = configurationJSON["animation"];
        std::string animationFilePath = ANIMATIONS_FOLDER + animationFile + ANIMATIONS_EXTENSION;
        auto& animation = m_animationsManager.addAnimation(id, animationFilePath);

        m_sampleEntities.emplace(std::make_pair(id, T(configurationJSON, animation)));
        m_sampleEntities.at(id).setTexture(m_animationsManager.getTexture(id));
    }

    template <class T>
    void EntitiesManager<T>::addEntity(float position, const std::string& entityID) {
        m_upcomingEntities.emplace_back(position, entityID);
    }

    template <class T>
    void EntitiesManager<T>::update(float dt, float distance) {
        for (auto it = m_upcomingEntities.begin(); it != m_upcomingEntities.end(); ) {
            if (it->first > distance + DISTANCE_TO_SHOW) {
                break;
            } else {
                m_entities.push_back(m_sampleEntities.at(it->second));
                m_entities.back().setInitialPosition({m_windowWidth + it->first - distance, m_floorY});

                it = m_upcomingEntities.erase(it);
            }
        }

        for (auto it = m_entities.begin(); it != m_entities.end(); ) {
            it->update(dt, m_gameSpeed);

            if (it->position(true) < 0) {
                it = m_entities.erase(it);
            } else {
                ++it;
            }
        }
    }

    template <class T>
    void EntitiesManager<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (const auto& entity : m_entities) {
            target.draw(entity, states);
        }
    }
}
