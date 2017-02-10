#include <Game/Map.hpp>

#include <JSONTools.hpp>
#include <RandomPropGenerator.hpp>

#include <Debug/Stream.hpp>

namespace XAL {
    void Map::load(const json& configurationJSON, const sf::Vector2u& windowSize) {

        float floorHeight = static_cast<float>(windowSize.y) * FLOOR_SCREEN_PERCENT;
        m_floor.setSize({static_cast<float>(windowSize.x), floorHeight});
        m_floor.setPosition(0.f, static_cast<float>(windowSize.y) - floorHeight);
        m_floor.setFillColor(sf::Color::Red);
        xalDebug() << "Map::load(): floorHeight:" << floorHeight;

        m_enemiesManager.setWindowWidth(windowSize.x);
        m_propsManager.setWindowWidth(windowSize.x);

        m_distance = windowSize.x;

        uint totalDistance = 0.f;

        m_enemiesManager.setFloorYPosition(m_floor.getPosition().y);
        m_propsManager.setFloorYPosition(m_floor.getPosition().y);

        auto enemiesJSON = configurationJSON["enemies"];

        auto enemiesTypesJSON = enemiesJSON["types"];
        for (const std::string& enemyTypeJSON : enemiesTypesJSON) {
            auto configurationPath = CONFIGURATIONS_FOLDER + enemyTypeJSON + CONFIGURATIONS_EXTENSION;

            xalDebug() << "Map::load(): Enemy Texture:" << configurationPath;

            m_enemiesManager.loadEntitySample(JSONTools::parseJSONFromFile(configurationPath), enemyTypeJSON);
        }

        auto enemiesListJSON = enemiesJSON["list"];
        for (const auto& enemyJSON : enemiesListJSON) {
            uint position = enemyJSON["position"];
            std::string type = enemyJSON["type"];

            xalDebug() << "Map::load(): enemy { type:" << type << ", position:" << position << "}";

            totalDistance = position;

            m_enemiesManager.addEntity(position, type);
        }

        totalDistance += 100.f;

        RandomPropGenerator propGenerator;
        propGenerator.setTotalDistance(totalDistance);

        auto propsListJSON = configurationJSON["props"];
        for (const auto& propJSON : propsListJSON) {
            std::string type = propJSON["type"];
            uint distance = propJSON["distance"];
            uint stack_size = propJSON["stack_size"];

            auto configurationPath = CONFIGURATIONS_FOLDER + type + CONFIGURATIONS_EXTENSION;

            //xalDebug() << "Map::load(): prop { type:" << type << ", rarity:" << rarity << "} calc:" << totalDistance * rarity;

            m_propsManager.loadEntitySample(JSONTools::parseJSONFromFile(configurationPath), type);

            propGenerator.setSettings(distance, stack_size, 40);

            int position = propGenerator.generateNextPosition();
            while (position != -1) {
                xalDebug() << "New prop type:" << type << " at " << position;
                if (position != 0) {
                    m_propsManager.addEntity(position, type);
                }

                position = propGenerator.generateNextPosition();
            }
        }

        xalDebug() << "Map::load(): finished";
    }

    void Map::update(float dt) {
        m_distance += dt * m_gameSpeed;
        m_enemiesManager.update(dt, m_distance);
        m_propsManager.update(dt, m_distance);
    }

    void Map::setGameSpeed(float gameSpeed) {
        m_gameSpeed = gameSpeed;

        m_enemiesManager.setGameSpeed(gameSpeed);
        m_propsManager.setGameSpeed(gameSpeed);
    }

    void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_floor, states);
        target.draw(m_propsManager, states);
        target.draw(m_enemiesManager, states);
    }
}
