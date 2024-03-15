#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

#include "image.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"

Color color(Ray r)
{
    Sphere sphere(Point3(0.0, 0.0, -1.0), 0.5);
    Sphere sphere2(Point3(0.0, -100.5, -1.0), 100);
    HitRecord rec;
    HittableList world;
    world.add(&sphere);
    world.add(&sphere2);
    if (world.hit(r, 0, INFINITY, rec))
    {
        return 0.5 * Color(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        Vec3 unitDirection = unitVector(r.direction);
        float t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1.0);
    
    }
}

int main(int argc, char const *argv[])
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    const int width = 1280;
    const float aspectRatio = 16.0 / 9.0;

    Image image(1280, static_cast<int>(width / aspectRatio));

    Point3 lowerLeftCorner(-2, -1, -1);
    float viewportWidth = 4;
    float viewportHeight = viewportWidth / aspectRatio;

    Point3 origin(0, 0, 0);

#pragma omp parallel for
    for (int j = 0; j < image.height; j++)
    {
        for (int i = 0; i < image.width; i++)
        {
            float u = float(i) / (image.width);
            float v = float(j) / (image.height);

            Ray r(origin, lowerLeftCorner + Vec3(u * viewportWidth, v * viewportHeight, 0) - origin);
            Color col = color(r);

            image.setPixel(i, j, col);
        }
    }

    image.save("output.ppm");

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << " seconds" << std::endl;
    return 0;
}
