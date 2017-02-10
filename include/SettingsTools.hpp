#ifndef XAL_SETTINGSTOOLS_HPP
#define XAL_SETTINGSTOOLS_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <JSONTools.hpp>

namespace XAL {
    namespace SettingsTools {
        inline bool applyWindowSettings(sf::RenderWindow &window) {
            auto jsonObj = JSONTools::parseJSONFromFile("data/settings.json");

            auto windowJson = jsonObj["window"];

            window.create({static_cast<uint>(windowJson["resolution"][0]), static_cast<uint>(windowJson["resolution"][1])}, "");

            return true;
        }
    }
}

#endif // XAL_SETTINGSTOOLS_HPP
