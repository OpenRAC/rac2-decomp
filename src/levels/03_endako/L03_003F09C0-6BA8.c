/* func_L03_003F6BA8: needs -g (nop pairs before div.s) and -fmove-all-movables (loop.c must hoist the edge constant 2, or combine folds the movz into a shift). */
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
        int k;
        for (k = 0; k < 4; ++k) {
            /* x and y of vertex k in packets 1 and 3 (36 floats a packet) */
            float *a = (float *)packets + k * 4;
            a[36] = -a[36];
            a[37] = -a[37];
            a[108] = -a[108];
            a[109] = -a[109];
        }
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
    {
        int k;
        for (k = 0; k < 2; ++k) {
            func_00283098(&packets[k].vertices[2], &packets[k].vertices[2], rotation);
            func_00283098(&packets[k].vertices[3], &packets[k].vertices[3], rotation);
        }
    }
    func_00283738(squared, rotation, rotation);
    alpha = 1.0f / D_L03_001B11D0;
    for (i = 0; i < 32; ++i) {
        int edge = (i & 1) ? 2 : 0;
        for (j = 0; j < 4; ++j) {
            int color;
            func_00283098(&packets[j].vertices[edge], &packets[j].vertices[edge], squared);
            func_00283098(&packets[j].vertices[edge+1], &packets[j].vertices[edge+1], squared);
            color = packets[j].colors[edge];
            packets[j].colors[edge] = func_00283D38(color, color & 0xffffff, alpha);
            color = packets[j].colors[edge+1];
            packets[j].colors[edge+1] = func_00283D38(color, color & 0xffffff, alpha);
            func_00280B90(&packets[j], matrix, 1);
        }
    }
}
