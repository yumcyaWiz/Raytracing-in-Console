#include <iostream>
#include <cmath>
#include <string>
#include "vec3.h"
#include "ray.h"


const int W = 50;
const int H = 50;


bool sphereIntersection(const Ray& ray, const Vec3& center, float radius, float& tHit) {
    float b = dot(ray.origin - center, ray.direction);
    float c = (ray.origin - center).length2() - radius*radius;
    float D = b*b - c;
    if(D < 0)
        return false;
    float t0 = -b - std::sqrt(D);
    float t1 = -b + std::sqrt(D);
    if(t1 < 0)
        return false;
    tHit = t0;
    if(tHit < 0)
        tHit = t1;
    return true;
}


std::string grayscale(int i) {
    return "\e[48;5;" + std::to_string(i + 232) + "m \e[0m";
}


int main() {
    Vec3 camPos(0);
    Vec3 camForward(0, 0, -1);
    Vec3 camRight(1, 0, 0);
    Vec3 camUp(0, 1, 0);
    float imageDist = 1.0;

    Vec3 center(0, 0, -2);
    float radius = 1.0;

    Vec3 lightDir = Vec3(1, 1, 1).normalize();

    for(int i = 0; i < W; i++) {
        for(int j = 0; j < H; j++) {
            float u = (2.0*i - W)/H;
            float v = (2.0*j - H)/H;
            Vec3 rayDir = (imageDist*camForward + u*camRight + v*camUp).normalize();
            Ray ray(camPos, rayDir);
            float tHit = 0.0;
            if(sphereIntersection(ray, center, radius, tHit)) {
                Vec3 hitPos = ray(tHit);
                Vec3 hitNormal = (hitPos - center).normalize();
                float intensity = std::max(dot(hitNormal, lightDir), 0.0f);
                int intensity_int = std::floor(24.5*intensity);
                std::cout << grayscale(intensity_int);
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
}
