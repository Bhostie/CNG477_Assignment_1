#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>

#include"Eigen/Dense"
#include "pointlight.h"
#include "camera.h"
using Eigen::Vector3f;
using std::vector;

class sphere{
    private:
        int sphere_index;
        int material_index;
        Vector3f center;
        double radius;
    public:
        sphere(){}
        sphere(int si, int mi, Vector3f C, double R);
        Vector3f getcenter();
        double getradius();
        int get_material_index();

        bool hit_check(const ray& r);
        Vector3f getHitPoint(const ray& r);
        Vector3f get_normal(const Vector3f& p) const;
        float getHitPointDistance(const ray& r);

        Vector3f get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight);
        Vector3f get_ambient_color(Material& material, Vector3f ambientLight);
        

};

#endif