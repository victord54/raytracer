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

    void setPixel(int x, int y, float r, float g, float b);

    float getR(int x, int y) const;

    float getG(int x, int y) const;

    float getB(int x, int y) const;

    void save(const std::string &filename) const;
};