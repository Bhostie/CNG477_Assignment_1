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
Vector3f triangle::getHitPoint(const ray& r){
    Vector3f p1_p2 = p2 - p1;
    Vector3f p1_p3 = p3 - p1;
    Vector3f normal = p1_p2.cross(p1_p3); // Compute the triangle normal
    float detA = r.direction().dot(normal);
    float invDetA = 1.0f / detA;
    Vector3f p1_to_origin = r.origin() - p1;
    float beta = invDetA * p1_to_origin.dot(p1_p3.cross(r.direction()));
    float gamma = invDetA * r.direction().dot(p1_p2.cross(p1_to_origin));
    float alpha = 1 - beta - gamma;
    return alpha * p1 + beta * p2 + gamma * p3;
}

int triangle::get_material_index(){
    return material_index;
}

float triangle::getHitPointDistance(const ray& r){
    Vector3f p1_p2 = p2 - p1;
    Vector3f p1_p3 = p3 - p1;
    Vector3f normal = p1_p2.cross(p1_p3); // Compute the triangle normal
    float detA = r.direction().dot(normal);
    float invDetA = 1.0f / detA;
    Vector3f p1_to_origin = r.origin() - p1;
    float beta = invDetA * p1_to_origin.dot(p1_p3.cross(r.direction()));
    float gamma = invDetA * r.direction().dot(p1_p2.cross(p1_to_origin));
    float alpha = 1 - beta - gamma;
    return r.origin().norm() + alpha * p1.norm() + beta * p2.norm() + gamma * p3.norm();
}

Vector3f triangle::get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight){
    Vector3f hitPoint = getHitPoint(r);
    Vector3f normal = (p2 - p1).cross(p3 - p1).normalized();
    Vector3f color = Vector3f(0, 0, 0); // color of the pixel
    // handling ambient light
    color += material.get_ambientColor().cwiseProduct(ambientLight);
    Vector3f view = r.direction().normalized();
    Vector3f ambient = material.get_ambientColor().cwiseProduct(ambientLight);
    Vector3f diffuseColor = material.get_diffuseColor();
    Vector3f specularColor = material.get_specularColor();
    float phongExponent = material.get_phongExponent();
    Vector3f mirrorColor = material.get_mirrorColor();
    for (int i = 0; i < plList.size(); i++) {
        PointLight pl = plList[i];
        // Direction of the light
        Vector3f lightDir = pl.get_direction(hitPoint);
        // Intensity of the light
        Vector3f lightIntensity = pl.get_intensity();
        // Distance between the light and the hit point
        float distance = pl.get_distance(hitPoint);
        // Diffuse color
        float diff = std::max(0.0f, normal.dot(lightDir));
        Vector3f diffuse = diff * diffuseColor.cwiseProduct(lightIntensity / (distance * distance));
        // Specular color
        Vector3f halfwayDir = (lightDir - view).normalized();
        float spec = std::pow(std::max(0.0f, normal.dot(halfwayDir)), phongExponent);
        Vector3f specular = spec * specularColor*255;
        // Adding diffuse and specular color to the pixel color
        color += (diffuse + specular);
    }
    return color;
}

Vector3f triangle::get_ambient_color(Material& material, Vector3f ambientLight){
    return material.get_ambientColor().cwiseProduct(ambientLight);
}