//spaceModels.h
//James Suddaby
#include <vector>
struct Vertex {
    float x, y, z; // Position
    float s, t;    // Texture coordinates
};
void drawFloor(float size);
void skybox(float D);
void spaceShip();
void spiral(bool shadow);
void loadTexture();
void drawSurfaceofRevolution(const std::vector<Vertex>& vertices, int slices, int stacks);
void drawAlien(bool shadow, float theta,  bool fireBullet, float bulletHorz, float bulletVert);
