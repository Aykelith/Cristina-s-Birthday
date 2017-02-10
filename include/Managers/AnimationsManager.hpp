#ifndef XAL_ANIMATIONSMANAGER_HPP
#define XAL_ANIMATIONSMANAGER_HPP

#include <unordered_map>
#include <vector>
#include <memory>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Game/Animation.hpp>

namespace XAL { class TextureManager; }

namespace XAL {
    class AnimationsManager {
    public:
        AnimationsManager(TextureManager& textureManager);

        Animation& addAnimation(const std::string& id, const std::string& filePath);
        Animation& getAnimation(const std::string& id) { return m_animations[id]; }

        const std::shared_ptr<sf::Texture>& getTexture(const std::string& id) const;

    private:
        static constexpr auto TEXTURES_FOLDER = "data/textures/";

    private:
        TextureManager& m_textureManager;

        std::unordered_map<std::string, Animation> m_animations;
    };
}

#endif // XAL_ANIMATIONSMANAGER_HPP
