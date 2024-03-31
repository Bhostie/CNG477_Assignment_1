#include "triangle.h"
#include"mesh.h"


mesh::mesh(int mi, int mati, std::vector<triangle> tris){
    mesh_index = mi;
    material_index = mati;
    triangles = tris;
}

std::vector<triangle> mesh::gettriangles(){
    return triangles;
}
bool mesh::hit_check(const ray& r){
    for(int i = 0; i < triangles.size(); i++){
        if(triangles[i].hit_check(r)){
            return true;
        }
    }
    return false;
}

int mesh::get_material_index(){
    return material_index;
}
Vector3f mesh::getHitPoint(const ray& r){
    
    for(int i = 0; i < triangles.size(); i++){
        if(triangles[i].hit_check(r)){
            return triangles[i].getHitPoint(r);
        }
    }
    return Vector3f(0,0,0);
}
Vector3f mesh::get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight){
    for(int i = 0; i < triangles.size(); i++){
        if(triangles[i].hit_check(r)){
            return triangles[i].get_color(plList, r, material, ambientLight);
        }
    }
    return Vector3f(0,0,0);
}
Vector3f mesh::get_ambient_color(Material& material, Vector3f ambientLight){
    return material.get_ambientColor().cwiseProduct(ambientLight);
}
