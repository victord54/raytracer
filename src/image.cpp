#include "image.hpp"
#include "vec3.hpp"

void Image::setPixel(int x, int y, float r, float g, float b)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        data[x + y * width] = Color(r, g, b);
    }
}

float Image::getR(int x, int y) const
{
    return data[x + y * width].x;
}

float Image::getG(int x, int y) const
{
    return data[x + y * width].y;
}

float Image::getB(int x, int y) const
{
    return data[x + y * width].z;
}

void Image::save(const std::string &filename) const
{
    std::ofstream ofs(filename);
    ofs << "P3\n"
        << width << " " << height << "\n255\n";
for (int j = height - 1; j >= 0; j--)
{
    for (int i = 0; i < width; i++)
    {
        ofs << static_cast<int>(255.999 * data[i + j * width].x) << ' '
            << static_cast<int>(255.999 * data[i + j * width].y) << ' '
            << static_cast<int>(255.999 * data[i + j * width].z) << '\n';
    }
}
    ofs.close();
}