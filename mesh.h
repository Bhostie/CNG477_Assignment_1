#ifndef MESH_H
#define MESH_H

#include "triangle.h"

class mesh{
    private:
        int mesh_index;
        int material_index;
        std::vector<triangle> triangles;
    public:
        mesh(){}
        mesh(int mi, int mati, std::vector<triangle> tris){
            mesh_index = mi;
            material_index = mati;
            triangles = tris;
        }
        std::vector<triangle> gettriangles(){
            return triangles;
        }
        bool hit_check(const ray& r){
            for(int i = 0; i < triangles.size(); i++){
                if(triangles[i].hit_check(r)){
                    return true;
                }
            }
            return false;
        }
};



#endif