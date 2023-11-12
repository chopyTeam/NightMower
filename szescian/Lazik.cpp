#include "Lazik.h"
#include "Core.h"
#include "Wheel.h"
#include "Axle.h"
#include "Handle.h"
#include "Reflector.h"
#include <string>
#include <iostream>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "v1.0.6/tinyobjloader-tinyobjloader-de948f1/tiny_obj_loader.h"

Lazik::Lazik(int xSize, int ySize, int zSize)
{
    this->xSize = xSize;
    this->ySize = zSize; // zamiana z Y na Z �eby by� nie na boku
    this->zSize = ySize;
}

void loadObjFile(const std::string& filename, std::vector<float>& vertices)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);
        }
    }
}

void Lazik::draw(int x, int y, int z)
{
    Core core(this->xSize * 1.2, this->ySize, this->zSize * 1.5);
    Wheel wheel(x, y, z);
    Axle axle(x, y, z);
    Handle handle(x, y, z);
    Reflector reflector(x, y, z);

    handle.draw(x - this->xSize + 10, y - 10 + 3 * this->ySize, z, this->zSize);
    core.draw(x, y, z);
    axle.draw(x + 4 + this->xSize / 2, y, z);
    axle.draw(x - 4 - this->xSize / 2, y, z);
    axle.draw(x, y, z);
    wheel.draw(x, 0, x - this->ySize - 12);
    wheel.draw(x, 0, x + this->ySize + 12, 1);
    wheel.draw(x + 4 + this->xSize / 2, 0, x - this->ySize - 12);
    wheel.draw(x + 4 + this->xSize / 2, 0, x + this->ySize + 12, 1);
    wheel.draw(x - 4 - this->xSize / 2, 0, x - this->ySize - 12);
    wheel.draw(x - 4 - this->xSize / 2, 0, x + this->ySize + 12, 1);
    for (int z = -2; z < 2; z++) {
        reflector.draw(x + 5 + this->xSize / 2, y + 3 + this->ySize, z * 8 + 4);
    }

    // Render loaded 3D model
    std::vector<float> vertices;
    loadObjFile("untitled.obj", vertices);
    glBegin(GL_TRIANGLES);
    glColor3f(1.000, 0.078, 0.576);
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glVertex3f(5*vertices[i], 5*(vertices[i + 1])+27, 5*vertices[i + 2]);
    }
    glEnd();

}
