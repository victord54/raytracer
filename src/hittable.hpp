#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <vector>

#include "ray.hpp"

struct Material;

struct HitRecord
{
    float t;
    Vec3 p;
    Vec3 normal;
    Material *material;
};

struct Hittable
{
    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const = 0;
};

struct HittableList : public Hittable
{
    std::vector<Hittable *> objects;

    HittableList() {}
    HittableList(Hittable *object) { add(object); }

    void add(Hittable *object) { objects.push_back(object); }

    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const override
    {
        HitRecord tempRec;
        bool hitAnything = false;
        float closestSoFar = t_max;

        for (const Hittable *object : objects)
        {
            if (object->hit(r, t_min, closestSoFar, tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }
};

#endif