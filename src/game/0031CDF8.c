#include "common.h"

typedef struct {
    float matrix[16];
    u32 color[4];
    float uv[8];
    u64 state[4];
} __attribute__((aligned(16))) WorldQuad;

typedef struct {
    u8 prefix00[0x140];
    float position[4];
} CameraPrefix;
extern CameraPrefix D_001B5200;
extern void func_0031C8E0(char *);
extern u64 func_0027C878(int);
extern float func_00283248(float, float);
extern float func_00282E80(const void *, const void *);
extern float func_002A7940(void);
extern void func_00283410(void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282D30(void *, const void *, float);
extern void func_00280B90(const void *, const void *, int);

typedef char WorldQuadExtent[(sizeof(WorldQuad) == 0x90) ? 1 : -1];

/* The qualified 0031CB78 sibling uses the same packet and camera-facing
 * construction. This variant draws textures 5/42 with its own two colors. */
void func_0031CDF8(char *unused, char *pos, float scale, int first, int second)
{
    WorldQuad packet;
    float matrix[16] __attribute__((aligned(16)));
    float euler[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u64 texture;
    float dx, dy;

    func_0031C8E0((char *)&packet);
    packet.uv[0] = 0.0f;
    packet.uv[3] = 1.0f;
    packet.uv[4] = 1.0f;
    packet.uv[6] = 1.0f;
    packet.uv[7] = 1.0f;
    packet.uv[1] = 0.0f;
    packet.uv[2] = 0.0f;
    packet.uv[5] = 0.0f;
    texture = func_0027C878(5);
    packet.state[0] = 0;
    packet.state[1] = texture;
    packet.state[2] = 0xFF9000000260ULL;
    packet.state[3] = 0x8000000048ULL;
    dx = D_001B5200.position[0] - *(float *)pos;
    dy = D_001B5200.position[1] - *(float *)(pos + 4);
    packet.color[3] = (u32)first + 0x30000000u;
    packet.color[2] = (u32)first + 0x30000000u;
    packet.color[1] = (u32)first + 0x30000000u;
    packet.color[0] = (u32)first + 0x30000000u;
    euler[3] = 0.0f;
    euler[2] = func_00283248(dx, dy);
    euler[1] = -func_00283248(func_00282E80(pos, D_001B5200.position),
                              D_001B5200.position[2] - *(float *)(pos + 8));
    euler[0] = func_002A7940();
    func_00283410(matrix, euler);
    func_00282CF0(offset, D_001B5200.position, pos);
    func_00282F20(offset, offset, 0.5f);
    matrix[12] = *(float *)pos + offset[0];
    matrix[13] = *(float *)(pos + 4) + offset[1];
    matrix[14] = *(float *)(pos + 8) + offset[2];
    matrix[15] = 1.0f;
    func_00282D30(packet.matrix, packet.matrix, scale);
    func_00282D30(packet.matrix + 4, packet.matrix + 4, scale);
    func_00282D30(packet.matrix + 8, packet.matrix + 8, scale);
    func_00282D30(packet.matrix + 12, packet.matrix + 12, scale);
    func_00280B90(&packet, matrix, 0);
    packet.state[1] = func_0027C878(42);
    packet.color[3] = (u32)second + 0x20000000u;
    packet.color[2] = (u32)second + 0x20000000u;
    packet.color[1] = (u32)second + 0x20000000u;
    packet.color[0] = (u32)second + 0x20000000u;
    func_00282D30(packet.matrix, packet.matrix, 1.0f);
    func_00282D30(packet.matrix + 4, packet.matrix + 4, 1.0f);
    func_00282D30(packet.matrix + 8, packet.matrix + 8, 1.0f);
    func_00282D30(packet.matrix + 12, packet.matrix + 12, 1.0f);
    func_00280B90(&packet, matrix, 0);
}
