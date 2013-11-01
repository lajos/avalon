#ifndef AVALON_IO_TILEDMAPLOADER_H
#define AVALON_IO_TILEDMAPLOADER_H

#include "cocos2d.h"

namespace avalon { namespace physics { class Box2dContainer; } }

namespace avalon {
namespace io {

class TiledMapLoader
{
public:
    using Dictionary = std::unordered_map<std::string, std::string>;
    struct Configuration
    {
        const Dictionary& settings;
        const std::string& layer;
        cocos2d::TMXTiledMap& map;
        avalon::physics::Box2dContainer* box2dContainer;
    };
    using Callback = std::function<void(const Configuration&)>;

private:
    std::unordered_map<int, Callback> gidFactories;
    std::unordered_map<std::string, Callback> nameFactories;
    avalon::physics::Box2dContainer* box2dContainer = nullptr;
    const std::string mapFileName;

    bool isFiltered(const std::string& name, const std::list<std::string>& filter = {});
    void loadGidFactories(cocos2d::TMXTiledMap& map);
    void loadNamedFactories(cocos2d::TMXTiledMap& map);
    
public:
    explicit TiledMapLoader(const std::string& mapFileName);
    std::shared_ptr<cocos2d::TMXTiledMap> load();
    void registerCallbackForName(const std::string& name, const Callback& callback, const std::list<std::string>& layerFilter = {});
    void setBox2dContainer(avalon::physics::Box2dContainer& container);

    template<typename T>
    void registerObjectForGID(const int gid, const std::list<std::string>& layerFilter = {})
    {
        gidFactories[gid] = [this, layerFilter](const Configuration& config)
        {
            if (!isFiltered(config.layer, layerFilter)) {
                auto newObject = T::create();
                newObject->onConfiguration(config);
                config.map.addChild(newObject);
            }
        };
    }

    template<typename T>
    void registerObjectForName(const std::string& name, const std::list<std::string>& layerFilter = {})
    {
        nameFactories[name] = [this, layerFilter](const Configuration& config)
        {
            if (!isFiltered(config.layer, layerFilter)) {
                auto newObject = T::create();
                newObject->onConfiguration(config);
                config.map.addChild(newObject);
            }
        };
    }
};

} // namespace io
} // namespace avalon

#endif /* AVALON_IO_TILEDMAPLOADER_H */