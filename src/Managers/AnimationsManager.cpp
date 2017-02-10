#include <Managers/AnimationsManager.hpp>

#include <Managers/TextureManager.hpp>
#include <JSONTools.hpp>
#include <Debug/Stream.hpp>

namespace XAL {
    AnimationsManager::AnimationsManager(TextureManager& textureManager)
    : m_textureManager { textureManager }
    { }

    Animation& AnimationsManager::addAnimation(const std::string& id, const std::string& filePath) {
        auto configurationJSON = JSONTools::parseJSONFromFile(filePath);

        std::string path = configurationJSON["texture"];
        auto texturePath = TEXTURES_FOLDER + path;

        bool success = m_textureManager.load(id, texturePath);

        xalDebug() << "AnimationsManager::addAnimation(): id:" << id << " texture_load:" << success << " texture_path:" << texturePath;
        if (success) xalDebug() << "\ttexture_size:" << m_textureManager.get(id)->getSize();

        Animation animation;

        auto framesJSON  = configurationJSON["frames"];
        for (const auto& frameJSON : framesJSON) {
            Frame frame;
            frame.time = frameJSON[0];

            const auto& rectJSON = frameJSON[1];
            frame.rect = sf::IntRect(rectJSON[0], rectJSON[1], rectJSON[2], rectJSON[3]);

            animation.frames.push_back(frame);
        }

        m_animations[id] = animation;
        return m_animations[id];
    }

    const std::shared_ptr<sf::Texture>& AnimationsManager::getTexture(const std::string& id) const {
        return m_textureManager.get(id);
    }
}
