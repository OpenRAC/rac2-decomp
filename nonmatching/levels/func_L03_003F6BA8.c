/* Retained bounded near miss, 2026-10-28: five forms, best728/736 bytes.
 * Default indexed form720 bytes; real packet/color/vertex cursors plus-g
 * reach728 and retain the real350-byte frame. Pure pointer-loop form spills
 * an endpoint and reaches732 with360 frame. -fno-schedule-insns ties728.
 * Final retained source guards the four field cursors after their last use,
 * keeping unused pointers inside the owning packet array; this is748 bytes.
 * No extra read/write, volatile, artificial barrier or invented padding is
 * used to force a saved-register role. Reopen on genuine packet cursor and
 * mirrored-template base lifetimes plus dead endpoint increment elimination.
 * Full extents arepacket4*144, rotations48+48, objectbasis64, Euler16.
 * The verified packet initializer defines every packet byte from vertex64,
 * UV32,color32-bit inputs and state32 before any transform/render consume.
 */
#include "common.h"

typedef int BeamQuad __attribute__((mode(TI)));
struct QuadPacket { BeamQuad vertices[4]; int colors[4]; float uv[4][2]; long state70, state78, state80, state88; };
extern void func_0029FC20(char *, int, char *);
extern void func_L02_002EF968(struct QuadPacket *, int, int, float (*)[2], BeamQuad *, int);
extern void func_00282C88(BeamQuad *);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern void func_00280B90(void *, void *, int);
extern int D_L03_001B1108 SDATA(D_L03_001B1108);
extern int D_L03_001B110C __attribute__((sda));
extern int D_L03_001B1138 SDATA(D_L03_001B1138);
extern int D_L03_001B1140 __attribute__((sda));
extern int D_L03_001B113C __attribute__((sda)), D_L03_001B1144 __attribute__((sda));
extern float D_L03_001B1118[][2] SDATA(D_L03_001B1118);
extern BeamQuad D_L03_001B1150[] SDATA(D_L03_001B1150);
extern BeamQuad D_L03_001B1190[] SDATA(D_L03_001B1190);
extern float D_L03_001B11D0 SDATA(D_L03_001B11D0);

/* Four complete144-byte draw packets, two48-byte rotation bases, the actual
 *64-byte object basis and one initialized16-byte Euler vector. Both template
 * reads cover64 bytes; UV reads cover32. No adjacent-vector pseudo-matrix. */
void func_L03_003F6BA8(char *object)
{
    float euler[4], rotation[3][4], squared[3][4], matrix[4][4];
    struct QuadPacket packets[4];
    int i, j;
    float alpha;
    func_0029FC20(object, 7, (char *)matrix);
    func_L02_002EF968(&packets[0], D_L03_001B1108, D_L03_001B1138, D_L03_001B1118, D_L03_001B1150, 1);
    func_L02_002EF968(&packets[1], D_L03_001B1108, D_L03_001B1138, D_L03_001B1118, D_L03_001B1150, 1);
    func_L02_002EF968(&packets[2], D_L03_001B110C, D_L03_001B1140, D_L03_001B1118, D_L03_001B1190, 1);
    func_L02_002EF968(&packets[3], D_L03_001B110C, D_L03_001B1140, D_L03_001B1118, D_L03_001B1190, 1);
    {
        float *mirror = (float *)packets;
        i = 3;
        do {
            mirror[36] = -mirror[36];
            mirror[37] = -mirror[37];
            mirror[108] = -mirror[108];
            mirror[109] = -mirror[109];
            mirror += 4;
        } while (--i >= 0);
    }
    packets[0].colors[3] = D_L03_001B113C;
    packets[0].colors[1] = D_L03_001B113C;
    packets[1].colors[3] = D_L03_001B113C;
    packets[1].colors[1] = D_L03_001B113C;
    packets[2].colors[3] = D_L03_001B1144;
    packets[2].colors[1] = D_L03_001B1144;
    packets[3].colors[3] = D_L03_001B1144;
    packets[3].colors[1] = D_L03_001B1144;
    func_00282C88((BeamQuad *)euler);
    euler[2] = 0.09817477f;
    func_002833F0(rotation, euler);
    for (i = 0; i < 2; ++i) {
        func_00283098(&packets[i].vertices[2], &packets[i].vertices[2], rotation);
        func_00283098(&packets[i].vertices[3], &packets[i].vertices[3], rotation);
    }
    func_00283738(squared, rotation, rotation);
    alpha = 1.0f / D_L03_001B11D0;
    i = 0;
    do {
        int edge = (i & 1) ? 2 : 0;
        int next = i+1;
        struct QuadPacket *packet = packets;
        BeamQuad *first = &packets[0].vertices[edge];
        BeamQuad *second = &packets[0].vertices[edge+1];
        int *first_color = &packets[0].colors[edge];
        int *second_color = &packets[0].colors[edge+1];
        for (j = 0; j < 4; ++j) {
            int color;
            func_00283098(first, first, squared);
            func_00283098(second, second, squared);
            color = *first_color;
            *first_color = func_00283D38(color, color & 0xffffff, alpha);
            color = *second_color;
            *second_color = func_00283D38(color, color & 0xffffff, alpha);
            func_00280B90(packet, matrix, 1);
            if (j != 3) {
                first = (BeamQuad *)((char *)first + sizeof(struct QuadPacket));
                second = (BeamQuad *)((char *)second + sizeof(struct QuadPacket));
                first_color = (int *)((char *)first_color + sizeof(struct QuadPacket));
                second_color = (int *)((char *)second_color + sizeof(struct QuadPacket));
            }
            ++packet;
        }
        i = next;
    } while (i < 32);
}
