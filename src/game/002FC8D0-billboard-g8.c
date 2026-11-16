#include "common.h"

/* func_002FDBD8 (from 002FC8D0.c): two textured quads at ORIGIN, turned to face
   DIRECTION and spun in opposite senses, drawn with textures 17 and 18.  Its own
   -G8 unit, as for func_002FD828 and func_002FDF40. */

extern int g_game_mode NOT_SDA;
extern int ref_L00_002FDBD8_00;
extern int ref_L00_002FDBD8_01[] __attribute__((sda));
extern int ref_L00_002FDBD8_02[2] __attribute__((sda));
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern float math_fast_float_g(float);
extern void euler_to_matrix(float *, float *);
extern void multiply_matrix(float *, float *, float *);
extern u64 GetEffectTextureDescriptor(int);
extern void FastVecScale(float *, float *, float);
extern void draw_world_quad(void *, float *, int);
typedef struct {
    float corners[4][4];
    int colors[4];
    float tex[8];
    u64 zero, texture, blend, test;
} DrawPacketDB;

/* Draws two flat glowing squares that face a given direction and spin in opposite ways. */
void part_draw_spinning_billboard_pair(float *origin, float *direction, float scale, int *colors)
{
    DrawPacketDB packet;
    float transform[16];
    float rotation[16];
    float angles[4];
    float spin[4];
    int n, i, odd;
    if ((unsigned int)(g_game_mode - 23) < 2 || g_game_mode == 27 ||
        g_game_mode == 25 || g_game_mode == 26 || g_game_mode == 111 ||
        g_game_mode == 98 || ref_L00_002FDBD8_00 == 2) return;
    n = 0;
    do {
        odd = n & 1;
        angles[0] = FastAddRotations(-mat_fast_helper_a(square_root(direction[0]*direction[0] + direction[2]*direction[2]), direction[1]), 1.57079637f);
        angles[1] = mat_fast_helper_a(direction[2], direction[0]);
        angles[2] = 0;
        angles[3] = 0;
        spin[0] = 0;
        {
            /* Two degrees per tick of the counter, mirrored on odd passes. */
            float turn = math_fast_float_g(IntToFloat(ref_L00_002FDBD8_01[0] % 180) * 0.0349065885f);
            if (odd)
                turn = -turn;
            spin[1] = turn;
        }
        spin[2] = 0;
        spin[3] = 0;
        euler_to_matrix(rotation, spin);
        euler_to_matrix(transform, angles);
        multiply_matrix(transform, transform, rotation);
        qcopy(transform + 12, origin);
        {
            int off;
            int color;
            int *p;
            /* The colour comes from the caller's table or the default pair; both arms
               keep the byte offset in one variable and add it to the table address. */
            if (!colors) {
                off = n * 4;
                color = *(int *)(off + (int)ref_L00_002FDBD8_02);
                n++;
                for (i = 3; i >= 0; i--)
                    packet.colors[i] = color;
            } else {
                i = 3;
                off = n * 4;
                color = *(int *)(off + (int)colors);
                n++;
                p = packet.colors;
                for (; i >= 0; i--)
                    *p++ = color;
            }
        }
        packet.texture = GetEffectTextureDescriptor(odd ? 18 : 17);
        packet.blend = 0xFF9000000260ULL;
        packet.test = 0x8000000044ULL;
        packet.zero = 0;
        packet.corners[0][0] = -1.0f; packet.corners[0][1] = 0; packet.corners[0][2] = 1.0f; packet.corners[0][3] = 1.0f;
        packet.corners[1][0] = 1.0f; packet.corners[1][1] = 0; packet.corners[1][2] = 1.0f; packet.corners[1][3] = 1.0f;
        packet.corners[2][0] = -1.0f; packet.corners[2][1] = 0; packet.corners[2][2] = -1.0f; packet.corners[2][3] = 1.0f;
        packet.corners[3][0] = 1.0f; packet.corners[3][1] = 0; packet.corners[3][2] = -1.0f; packet.corners[3][3] = 1.0f;
        FastVecScale(packet.corners[0], packet.corners[0], scale);
        FastVecScale(packet.corners[1], packet.corners[1], scale);
        FastVecScale(packet.corners[2], packet.corners[2], scale);
        FastVecScale(packet.corners[3], packet.corners[3], scale);
        packet.tex[0] = 0; packet.tex[1] = 1; packet.tex[2] = 1; packet.tex[3] = 1;
        packet.tex[4] = 0; packet.tex[5] = 0; packet.tex[6] = 1; packet.tex[7] = 0;
        draw_world_quad(&packet, transform, 1);
    } while (n < 2);
}
