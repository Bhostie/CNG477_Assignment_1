#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>
#include"Eigen/Dense"
#include "pointlight.h"
#include "ray.h"
using Eigen::Vector3f;
using Eigen::Matrix3f;
using std::vector;

/*
#Triangle: A triangle will be represented with a material index and its vertex positions.  
- In the first line under the tag, triangle index will be given.  
- In the second line under the tag, material index of the triangle will be given. You will 
assume that the triangle is built by the material to which the index corresponds while 
rendering.  
- In the third line under the tag, vertex indexes corresponding to vertexes of the triangles will 
be given as three integers. You will use coordinates of the vertexes listed under the tag 
#VertexList Note that the indices will be given in counter clockwise order from which you 
can extract the frontface and backface information of the triangle.  
- There may be multiple triangles in the scene. You have to take into account all of them 
while rendering. You can use their indexes to differentiate between them, same index will 
not be defined for more than one triangle. 
*/

class triangle{
    private:
        int triangle_index;
        int material_index;
        Vector3f p1;
        Vector3f p2;
        Vector3f p3;
    public:
        triangle(){}
        triangle(int ti, int mi, Vector3f pi1, Vector3f pi2, Vector3f pi3);
        bool hit_check(const ray& r);
        bool hit_checkOLD(const ray& r);
        float determinant(Vector3f pi1, Vector3f pi2, Vector3f pi3);
        Vector3f getHitPoint(const ray& r);
        float getHitPointDistance(const ray& r);
        int get_material_index();
        Vector3f get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight);
        Vector3f get_ambient_color(Material& material, Vector3f ambientLight);
};

#endif