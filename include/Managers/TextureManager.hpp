#ifndef XAL_TEXTUREMANAGER_HPP
#define XAL_TEXTUREMANAGER_HPP

#include <Global.hpp>
#include <Debug/Stream.hpp>

#include <unordered_map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>

namespace XAL {
    class TextureManager {
    public:
        TextureManager() = default;

        bool load(const std::string& id, const std::string& filepath) {
            //auto textureHandler = m_textures.emplace(std::make_pair(id, sf::Texture())).first->second;
            //return textureHandler.loadFromFile(filepath);

            sf::Texture t;
            auto s = t.loadFromFile(filepath);
            m_textures[id] = std::make_shared<sf::Texture>(t);
            return s;
        }

        const std::shared_ptr<sf::Texture>& get(const std::string& id) const {
            xalDebug() << "id:" << id << " size:" << m_textures.at(id)->getSize();
            return m_textures.at(id);
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
    };
}

#endif // XAL_TEXTUREMANAGER_HPP
