#include"triangle.h"

triangle::triangle(int ti, int mi, Vector3f pi1, Vector3f pi2, Vector3f pi3){
    triangle_index = ti;
    material_index = mi;
    p1 = pi1;
    p2 = pi2;
    p3 = pi3;
}

bool triangle::hit_check(const ray& r){
    Vector3f p1_p2 = p2 - p1;
    Vector3f p1_p3 = p3 - p1;
    Vector3f normal = p1_p2.cross(p1_p3); // Compute the triangle norma
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

float triangle::determinant(Vector3f pi1, Vector3f pi2, Vector3f pi3){
    Matrix3f matrix;
    matrix << pi1.x(),  pi2.x(),  pi3.x(),
              pi1.y(),  pi2.y(),  pi3.y(),
              pi1.z(),  pi2.z(),  pi3.z();
    return matrix.determinant();
}