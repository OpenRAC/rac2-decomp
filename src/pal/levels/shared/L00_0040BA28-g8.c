#include "common.h"

/* func_PAL_L00_0040BA28, the PAL copy of func_L00_00406FB0: the same C, where each scroll speed
 * is scaled by 1.2f for 50 Hz. */

extern float D_L00_001B0E6C __attribute__((sda)), D_L00_001B0E70 __attribute__((sda));
extern float D_L00_001B0E74 __attribute__((sda)), D_L00_001B0E78 __attribute__((sda));
extern float D_L00_001B0E7C __attribute__((sda)), D_L00_001B0E80 __attribute__((sda));
extern float D_L00_001B0E84 __attribute__((sda));
extern int D_L00_001B0EDC __attribute__((sda)), D_L00_001B0EE0 __attribute__((sda));
extern float D_L00_001B0EE4 __attribute__((sda)), D_L00_001B0EE8 __attribute__((sda)), D_L00_001B0EEC __attribute__((sda));
extern int D_L00_001B0EF4 __attribute__((sda)), D_L00_001B0EF8 __attribute__((sda));
extern float D_L00_001B0EFC __attribute__((sda)), D_L00_001B0F00 __attribute__((sda));
extern int D_L00_001B0F04 __attribute__((sda)), D_L00_001B0F08 __attribute__((sda)), D_L00_001B0F0C __attribute__((sda));
extern char D_L00_00254B20[], D_L00_00254BE0[];
extern float D_L00_00254CA0[][20][4], D_L00_00254B60[][20][4];

typedef struct {
    int word;
    unsigned char state;
    char pad[219];
} StripState;

extern char D_001395B0[], D_L00_001B8DC0[];
extern StripState D_L00_00262570[];

extern void func_L00_004073D8(void *, int, int, int, float, float, float, int);
extern void func_L00_004079C8(void *), func_L00_00407C18(void *);
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00280B90(void *, int, int);

typedef struct {
    float x, y, z, w;
} BeamVertex __attribute__((aligned(16)));

typedef struct {
    BeamVertex q[4];
    unsigned int colors[4];
    struct {
        float x0, y0, x1, y1, x2, y2, x3, y3;
    } uv;
    u64 tags[4];
} BeamPacket;

/* Scrolls the textures, draws the two halo ribbons and two child effects, then draws rows
 * 2 to 11 of a 20-column ring mesh, culling faces turned from the camera; each face is drawn
 * twice with its own scrolling V. Same mesh loop as RAC1's suck_beam_draw_mesh. */
void func_PAL_L00_0040BA28(char *arg)
{
    BeamPacket packet;
    float e[4], f[4], g[4], h[4];
    float x, y, z;
    int color, i, j;

    D_L00_001B0EFC -= D_L00_001B0F00 * 1.2f;
    if (D_L00_001B0EFC <= -8.0f) D_L00_001B0EFC += 8.0f;
    func_L00_004073D8(D_L00_00254B20, D_L00_001B0EDC, D_L00_001B0EE0, 12, D_L00_001B0EE4, D_L00_001B0EE8, D_L00_001B0EEC, D_L00_001B0EF4);
    func_L00_004073D8(D_L00_00254BE0, D_L00_001B0EDC, D_L00_001B0EE0, 12, D_L00_001B0EE4, D_L00_001B0EE8, D_L00_001B0EEC, D_L00_001B0EF8);
    func_L00_004079C8(arg);
    func_L00_00407C18(arg);
    color = D_L00_00262570[(unsigned char)D_001395B0[0]].state ? D_L00_001B0F08 : D_L00_001B0F04;
    packet.tags[1] = func_0027C878(D_L00_001B0F0C);
    packet.tags[2] = 0xff9000000260ULL;
    packet.tags[3] = 0x8000000048ULL;
    packet.tags[0] = 0;
    x = D_L00_001B0E74;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    D_L00_001B0E74 -= D_L00_001B0E78 * 1.2f;
    if (D_L00_001B0E74 <= -8.0f) D_L00_001B0E74 += 8.0f;
    D_L00_001B0E7C -= D_L00_001B0E84 * 1.2f;
    if (D_L00_001B0E7C <= -7.0f) D_L00_001B0E7C += 7.0f;
    D_L00_001B0E80 += D_L00_001B0E84 * 1.2f;
    if (D_L00_001B0E80 >= 5.0f) D_L00_001B0E80 -= 5.0f;
    for (i = 2; i < 12; i++) {
        y = D_L00_001B0E7C;
        z = D_L00_001B0E80;
        for (j = 0; j < 20; j++) {
            qcopy(&packet.q[0], D_L00_00254CA0[i][j]);
            qcopy(&packet.q[1], D_L00_00254CA0[i][(j + 1) % 20]);
            qcopy(&packet.q[2], D_L00_00254B60[i][j]);
            qcopy(&packet.q[3], D_L00_00254B60[i][(j + 1) % 20]);
            func_00282CF0(e, &packet.q[0], &packet.q[1]);
            func_00282CF0(f, &packet.q[2], &packet.q[1]);
            func_00282DD8(g, f, e);
            func_00282CF0(h, &packet.q[1], D_L00_001B8DC0);
            if (func_00282DB0(g, h) >= 0.0f) {
                y += D_L00_001B0E70;
                z += D_L00_001B0E70;
                continue;
            }
            if (i == 11) {
                packet.colors[0] = packet.colors[1] = D_L00_001B0F04 & 0xffffff;
            }
            packet.uv.x1 = packet.uv.x0 = x;
            packet.uv.y0 = packet.uv.y2 = y;
            packet.uv.y1 = y + D_L00_001B0E70;
            packet.uv.x2 = x - D_L00_001B0E6C;
            packet.uv.x3 = x - D_L00_001B0E6C;
            packet.uv.y3 = y + D_L00_001B0E70;
            y += D_L00_001B0E70;
            func_00280B90(&packet.q[0], 0, 0);
            packet.uv.x1 = packet.uv.x0 = x;
            packet.uv.y0 = packet.uv.y2 = z;
            packet.uv.y1 = z + D_L00_001B0E70;
            packet.uv.x2 = x - D_L00_001B0E6C;
            packet.uv.x3 = x - D_L00_001B0E6C;
            packet.uv.y3 = z + D_L00_001B0E70;
            z += D_L00_001B0E70;
            func_00280B90(&packet.q[0], 0, 0);
        }
        x += D_L00_001B0E6C;
    }
}
