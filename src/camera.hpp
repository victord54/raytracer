#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"

struct Camera
{
    Point3 origin;
    Point3 lowerLeftCorner;
    float viewportWidth;
    float viewportHeight;

    Camera(float aspectRatio)
    {
        origin = Point3(0, 0, 0);
        lowerLeftCorner = Point3(-2, -1, -1);
        viewportWidth = 4;
        viewportHeight = viewportWidth / aspectRatio;
    }

    Ray getRay(float u, float v) const
    {
        return Ray(origin, lowerLeftCorner + Vec3(u * viewportWidth, v * viewportHeight, 0) - origin);
    }
};


#endif