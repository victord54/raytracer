#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include <fstream>

#include "vec3.hpp"

struct Image
{
    int width;
    int height;
    std::vector<Color> data;

    Image(int width, int height) : width(width), height(height), data(width * height) {}

    void setPixel(int x, int y, Color color)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            data[x + y * width] = color;
        }
    }

    float getR(int x, int y) const
    {
        return data[x + y * width].x();
    }

    float getG(int x, int y) const
    {
        return data[x + y * width].y();
    }

    float getB(int x, int y) const
    {
        return data[x + y * width].z();
    }

    void save(const std::string &filename) const
    {
        std::ofstream ofs(filename);
        ofs << "P3\n"
            << width << " " << height << "\n255\n";
        for (int j = height - 1; j >= 0; j--)
        {
            for (int i = 0; i < width; i++)
            {
                ofs << static_cast<int>(255.999 * data[i + j * width].x()) << ' '
                    << static_cast<int>(255.999 * data[i + j * width].y()) << ' '
                    << static_cast<int>(255.999 * data[i + j * width].z()) << '\n';
            }
        }
        ofs.close();
    }
};

#endif