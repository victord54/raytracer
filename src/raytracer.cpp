#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

#include "image.hpp"
#include "vec3.hpp"
#include "ray.hpp"

Color color(Ray r)
{
    float t = r.hitSphere(Point3(0, 0, -1), 0.5);
    if (t > 0)
    {
        Vec3 N = unitVector(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    t = 0.5 * (r.direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
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
