#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "hittable.hpp"

struct Material {
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const = 0;
};

struct Lambertian : public Material {
    Color albedo;

    Lambertian(const Color &a) : albedo(a) {}

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 target = rec.normal + randomUnitSphere();
        scattered = Ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
};

struct Metal : public Material {
    Color albedo;
    float fuzz;

    Metal(const Color &a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        Vec3 reflected = reflect(unitVector(r_in.direction), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * randomUnitSphere());
        attenuation = albedo;
        return dot(scattered.direction, rec.normal) > 0;
    }
};

#endif