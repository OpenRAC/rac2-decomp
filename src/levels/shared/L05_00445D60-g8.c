#include "common.h"

typedef struct { s16 vertex, texture; } SpriteIndex;
typedef struct {
    float points[4][4];
    u32 colors[4];
    float uv[4][2];
    u64 primitive, texture, tag, blend;
} SpritePacket;
extern int D_001A79F0;
extern unsigned char D_L05_001B96C0[];
extern float D_L05_002B8850[][4];
extern float D_L05_002B88E0[][2];
/* One table: retail addresses its vertex fields through $gp and its texture fields absolutely. */
extern SpriteIndex D_L05_001B1C40[4][4] MACRO_ADDR;
extern SpriteIndex indices_gp[4][4] SDATA(D_L05_001B1C40);
extern int D_L05_001B1C80 SDATA(D_L05_001B1C80);
extern int D_L05_001B1C84 SDATA(D_L05_001B1C84);
extern int D_L05_001B1C88 SDATA(D_L05_001B1C88);
extern int D_L05_001B1C8C SDATA(D_L05_001B1C8C);
extern int D_L05_001B1C90 SDATA(D_L05_001B1C90);
extern u32 D_L05_001B1C94 SDATA(D_L05_001B1C94);
extern float D_L05_001B1C98 SDATA(D_L05_001B1C98);
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

/* Draws the object's four textured quads, each with four corners taken from the index table,
   in a basis facing the camera. */
/* Draws the ship's aiming mark as four small sprites facing the camera. */
void func_L05_00445D60(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    SpritePacket packet;
    float matrix[4][4];
    int i, j;
    u64 blend;
    if (gCurrentMapIndex == 20)
        packet.texture = GetEffectTextureDescriptor(65);
    else
        packet.texture = GetEffectTextureDescriptor(63);
    packet.tag = 0xFF9000000260ULL;
    blend = (u64)D_L05_001B1C80;
    blend |= (u64)D_L05_001B1C84 << 2;
    blend |= (u64)D_L05_001B1C88 << 4;
    blend |= (u64)D_L05_001B1C8C << 6;
    blend |= (u64)D_L05_001B1C90 << 32;
    packet.blend = blend;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = D_L05_001B1C94;
    packet.primitive = 0;
    qcopy(matrix[3], state + 0x20);
    FastVecSub(matrix[0], D_L05_001B96C0, matrix[3]);
    vec_scale_to_length(matrix[0], matrix[0], 1.0f);
    FastVecCross(matrix[1], matrix[0], D_L05_001B96C0 + 0x250);
    vec_scale_to_length(matrix[1], matrix[1], 1.0f);
    FastVecCross(matrix[2], matrix[1], matrix[0]);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int vertex = indices_gp[i][j].vertex;
            int texture = D_L05_001B1C40[i][j].texture;
            FastVecScale(packet.points[j], D_L05_002B8850[vertex], D_L05_001B1C98);
            packet.uv[j][0] = D_L05_002B88E0[texture][0];
            packet.uv[j][1] = D_L05_002B88E0[texture][1];
        }
        draw_world_quad(&packet, matrix, 0);
    }
}
