#ifndef XAL_MAP_HPP
#define XAL_MAP_HPP

#include <Global.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

#include <Managers/TextureManager.hpp>
#include <Managers/AnimationsManager.hpp>
#include <Managers/EnemiesManager.hpp>

namespace XAL {
    class Map: public sf::Drawable {
    public:
        Map() = default;
        void load(const json& configurationJSON, const sf::Vector2u& windowSize);

        void update(float dt);

        void setGameSpeed(float gameSpeed);

        float getFloorPosition() const { return m_floor.getPosition().y; }

    private:
        static constexpr auto CONFIGURATIONS_FOLDER = "data/entities/";
        static constexpr auto CONFIGURATIONS_EXTENSION = ".json";

        static constexpr float FLOOR_SCREEN_PERCENT = 0.15f;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        TextureManager m_textureManager;
        AnimationsManager m_animationsManager = AnimationsManager(m_textureManager);

        sf::Sprite m_terrain;
        sf::RectangleShape m_floor;

        EnemiesManager m_enemiesManager = EnemiesManager(m_animationsManager);
        EntitiesManager<> m_propsManager = EntitiesManager<>(m_animationsManager);

        float m_distance;
        float m_gameSpeed;
    };
}

#endif // XAL_MAP_HPP
