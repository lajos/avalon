#ifndef AVALON_PHYSICS_UTILS_H
#define AVALON_PHYSICS_UTILS_H

#include <Box2D/Box2D.h>
#include <avalon/io/TiledMapLoader.h>

namespace avalon {
namespace physics {
namespace utils {

b2BodyType getBodyTypeFromString(const std::string& type);
avalon::io::TiledMapLoader::Callback shapeLoader(int filterCategory = 0x0001, bool isSensor = false);

} // namespace utils
} // namespace physics
} // namespace avalon

#endif /* AVALON_PHYSICS_UTILS_H */