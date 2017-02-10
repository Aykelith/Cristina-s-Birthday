#ifndef XAL_PROPSMANAGER_HPP
#define XAL_PROPSMANAGER_HPP

#include <Global.hpp>

#include <vector>
#include <unordered_map>

#include <Game/Entity.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <JSONTools.hpp>

namespace XAL { class AnimationsManager; }

namespace XAL {
    template <class T = Entity>
    class EntitiesManager: public sf::Drawable {
    public:
        EntitiesManager(AnimationsManager& animationsManager);

        void loadEntitySample(const json& configurationJSON, const std::string& id);
        void addEntity(float position, const std::string& entityID);
        virtual void update(float dt, float distance);

        void setGameSpeed(float gameSpeed) { m_gameSpeed = gameSpeed; }
        void setWindowWidth(float width) { m_windowWidth = width; }
        void setFloorYPosition(float y) { m_floorY = y; }

    protected:
        static constexpr float DISTANCE_TO_SHOW = 100.f;

        static constexpr auto ANIMATIONS_FOLDER = "data/animations/";
        static constexpr auto ANIMATIONS_EXTENSION = ".anim.json";

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        AnimationsManager& m_animationsManager;

        std::unordered_map<std::string, T> m_sampleEntities;
        std::vector<std::pair<float, std::string>> m_upcomingEntities;
        std::vector<T> m_entities;

        float m_windowWidth;
        float m_gameSpeed;
        float m_floorY;
    };
}

#include <Managers/EntitiesManager.inl>

#endif
