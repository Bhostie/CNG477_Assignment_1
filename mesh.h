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
        int get_material_index();
        Vector3f getHitPoint(const ray& r);
        Vector3f get_color(vector<PointLight>& plList, const ray& r, Material& material, Vector3f ambientLight);
        Vector3f get_ambient_color(Material& material, Vector3f ambientLight);
};

#endif