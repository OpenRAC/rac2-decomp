#include "common.h"
typedef unsigned int Quad5070 __attribute__((mode(TI)));
typedef struct DrawPacket5070 {
    Quad5070 position[4];
    u32 rgba[4];
    float uv[4][2];
    u64 state[4];
} DrawPacket5070;
extern int D_L07_001B0A80[] __attribute__((sda));
extern int D_L07_001B0A80_gp[] SDATA(D_L07_001B0A80);
extern float D_L07_001B0A60[][2] SDATA(D_L07_001B0A60);
extern float D_L07_0029F5B0[][4];
extern void copy_matrix_rotation(void *, void *);
extern void euler_rotation_basis(void *, void *);
extern int PulseColor(float, int, int);
extern int FastTweenColor(float, int, int);
extern void FillQuadPacket(DrawPacket5070 *, int, int, void *, void *, int);
extern void gfx_transform_and_draw_entries(DrawPacket5070 *, int, void *, int, void *);
/* Build two packets and submit them. The frame has room for a third: retail reserves 0x1B0 bytes,
   exactly 3 * sizeof(DrawPacket5070), contiguous from $sp + 0, and uses only the first two. */
/* Draws a glowing disc at the object's position, with colours that change with its state. */
void entity_draw_glow_disc(char *actor)
{
    DrawPacket5070 packets[3];
    float rotation[12] __attribute__((aligned(16)));
    float world[16] __attribute__((aligned(16)));
    float angle[4] __attribute__((aligned(16)));
    char *state = *(char **)(actor + 0x68);
    int colour;
    copy_matrix_rotation(world, actor + 0xc0);
    qcopy(world + 12, actor + 0x10);
    world[15] = 1.0f;
    *(Quad5070 *)angle = 0;
    angle[2] = 0.19634955f;
    euler_rotation_basis(rotation, angle);
    colour = PulseColor(*(float *)(state + 0x1c), D_L07_001B0A80_gp[0], D_L07_001B0A80[1]);
    colour = FastTweenColor(*(float *)(state + 0x18), colour & 0xffffff, colour);
    FillQuadPacket(&packets[0], 5, colour, D_L07_001B0A60, D_L07_0029F5B0[0], 1);
    FillQuadPacket(&packets[1], 5, colour, D_L07_001B0A60, D_L07_0029F5B0[4], 1);
    gfx_transform_and_draw_entries(packets, 2, rotation, 32, world);
}
