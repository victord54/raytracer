#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

struct Sphere : public Hittable
{
    Point3 center;
    float radius;

    Sphere() {}
    Sphere(Point3 center, float radius) : center(center), radius(radius) {}

    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const override
    {
        Vec3 oc = r.origin - center;
        float a = dot(r.direction, r.direction);
        float b = 2.0 * dot(oc, r.direction);
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return false;
        }
        float t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (t < t_min || t > t_max)
        {
            t = (-b + sqrt(discriminant)) / (2.0 * a);
            if (t < t_min || t > t_max)
            {
                return false;
            }
        }
        rec.t = t;
        rec.p = r.at(t);
        rec.normal = (rec.p - center) / radius;
        return true;
    }
};

#endif