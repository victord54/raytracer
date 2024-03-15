#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <random>

#include "image.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "camera.hpp"

Color render(Ray r)
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

    int ns = 1; // Number of samples per pixel

    Image image(width, static_cast<int>(width / aspectRatio));

#pragma omp parallel for
    for (int j = 0; j < image.height; j++)
    {
        for (int i = 0; i < image.width; i++)
        {
            Color col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                // Normalize the pixel coordinates
                float rand1 = float(std::rand()) / RAND_MAX; // Random number between 0 and 1
                float rand2 = float(std::rand()) / RAND_MAX; // Random number between 0 and 1
                if (ns == 1)
                {
                    rand1 = 0.0;
                    rand2 = 0.0;
                }
                float u = float(i + rand1) / (image.width);
                float v = float(j + rand2) / (image.height);

                Camera camera(aspectRatio);

                Ray r = camera.getRay(u, v);
                col += render(r);
            }
            col /= float(ns);
            image.setPixel(i, j, col);
        }
    }

    image.save("output.ppm");

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << " seconds" << std::endl;
    return 0;
}
