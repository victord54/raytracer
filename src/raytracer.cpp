#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

#include "image.hpp"
#include "vec3.hpp"

int main(int argc, char const *argv[])
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    const int width = 1280;
    const float aspectRatio = 16.0 / 9.0;

    Image image(1280, static_cast<int>(width / aspectRatio));

#pragma omp parallel for
    for (int j = 0; j < image.height; j++)
    {
        for (int i = 0; i < image.width; i++)
        {
            float r = float(i) / float(image.width);
            float g = float(j) / float(image.height);
            float b = 0.25;
            image.setPixel(i, j, r, g, b);
        }
    }

    image.save("output.ppm");

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0 << " seconds" << std::endl;
    return 0;
}
