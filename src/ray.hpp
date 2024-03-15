#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

struct Ray
{
    Vec3 origin;
    Vec3 direction;

    Ray() {}

    Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {
        this->direction = unitVector(direction);
    }

    Vec3 at(float t) const { return origin + direction * t; }

    float hitSphere(const Vec3 &center, float radius) const
    {
        Vec3 oc = origin - center;
        float a = dot(direction, direction);
        float b = 2.0 * dot(oc, direction);
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return -1.0;
        }
        else
        {
            return (-b - sqrt(discriminant)) / (2.0 * a);
        }
    }
};

#endif