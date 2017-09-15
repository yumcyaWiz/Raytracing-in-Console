#ifndef RAY_H
#define RAY_H
#include <iostream>
#include "vec3.h"
class Ray {
    public:
        Vec3 origin;
        Vec3 direction;
        Ray() {};
        Ray(const Vec3& o, const Vec3& d) {
            origin = o;
            direction = d;
        };
        Vec3 operator()(float t) const {
            return origin + t*direction;
        };
};
std::ostream& operator<<(std::ostream& stream, const Ray& r) {
    stream << "Origin:" << r.origin << " Direction:" << r.direction << std::endl;
}
#endif
