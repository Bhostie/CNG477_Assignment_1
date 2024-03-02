#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>

#include"Eigen/Dense"
#include "ray.h"
using Eigen::Vector3f;
using Eigen::Matrix3f;

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
        triangle(int ti, int mi, Vector3f pi1, Vector3f pi2, Vector3f pi3){
            triangle_index = ti;
            material_index = mi;
            p1 = pi1;
            p2 = pi2;
            p3 = pi3;
        }

        bool hit_check(const ray& r){
        Vector3f p1_p2 = p2 - p1;
        Vector3f p1_p3 = p3 - p1;
        Vector3f normal = p1_p2.cross(p1_p3); // Compute the triangle normal

        float detA = r.direction().dot(normal);

        // Check if the ray and the triangle are parallel or nearly parallel
        if (detA > -1e-6 && detA < 1e-6)
            return false;

        float invDetA = 1.0f / detA;
        Vector3f p1_to_origin = r.origin() - p1;

        // Compute barycentric coordinates
        float beta = invDetA * p1_to_origin.dot(p1_p3.cross(r.direction()));
        float gamma = invDetA * r.direction().dot(p1_p2.cross(p1_to_origin));

        // Check if the intersection point is inside the triangle
        return (beta > 0) && (gamma > 0) && (beta + gamma < 1);
    }


        float determinant(Vector3f pi1, Vector3f pi2, Vector3f pi3){

            Matrix3f matrix;
            matrix << pi1.x(),  pi2.x(),  pi3.x(),
                      pi1.y(),  pi2.y(),  pi3.y(),
                      pi1.z(),  pi2.z(),  pi3.z();
            return matrix.determinant();
        }
};

#endif