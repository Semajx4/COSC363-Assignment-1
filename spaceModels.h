//spaceModels.h
//James Suddaby
#include <vector>
struct Vertex {
    float x, y, z; // Position
    float s, t;    // Texture coordinates
};
void floor();
void skybox(float D);
void spaceShip();
void spiral();
void loadTexture();
void skyDome(const std::vector<Vertex>& vertices, int slices, int stacks);
