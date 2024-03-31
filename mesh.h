#ifndef MESH_H
#define MESH_H

class mesh{
    private:
        int mesh_index;
        int material_index;
        std::vector<triangle> triangles;
    public:
        mesh(){}
        mesh(int mi, int mati, std::vector<triangle> tris);
        std::vector<triangle> gettriangles();
        bool hit_check(const ray& r);
};

#endif