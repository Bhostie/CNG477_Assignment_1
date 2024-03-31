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
