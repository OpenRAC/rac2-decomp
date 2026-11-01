#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;
typedef struct Ent {
    unsigned char pad00[0x31];
    unsigned char f31;
    unsigned char pad32[2];
    unsigned short f34;
    unsigned char pad36[0x98 - 0x36];
    int f98;
} Ent;
extern unsigned int D_L02_001FC060[];
extern char *D_L02_001B359C;
extern int D_L02_001B35B8 __attribute__((sda));
extern int D_L02_001A9048;
extern float D_L02_001AEF50 __attribute__((sda));
extern float D_L02_001AEE50[2] __attribute__((sda));
extern float D_L02_001AEE48[2] __attribute__((sda));
extern float D_L02_001AEE40[2] __attribute__((sda));
extern int D_L02_001AEE70 __attribute__((sda));
extern float func_00283198(float x);
extern float func_00283B98(float a, float b);
extern float func_00283BE0(float a, float b);
extern void func_002C9828(int *path, int seg, void *pos, void *rot, int flags, float t);
extern int func_002A9640(void *e, int a1, int a2);
extern void func_PAL_L00_0032C328(void *a0, void *a1, void *a2, void *a3, int t0, int t1, int t2, int t3,
                              int s0, int s1, int s2);
extern void func_L01_0031A278(char *a0, float *a1, float f12, float f13, float f14);
extern void func_002E5CF8(int a0, int a1, void *a2);
extern void func_PAL_002AC718(void *a0, float f12, void *a1, float f13, void *a2, float f14, int a3,
                          float f15, int t0, int t1, float f16, float f17, int t2, float f18,
                          int t3, int s0, int s1, int s2, int s3);
extern void func_002AA2E8(float *p, float a, float b);
extern void func_PAL_L02_0038FDC0(void *e);
extern void func_PAL_L02_00390950(void *e);
extern void func_002A0F48(void *e);

/* Walks the group's entity list: each one moves along the path object (func_002C9828), turns its
   angle and advances its phase; a hit by the player while it is active switches it off and spawns
   the debris (func_PAL_L00_0032C328, func_PAL_002AC718); a live one tilts toward its turning speed
   (func_002AA2E8) and runs the level's two update calls. */
void func_PAL_L02_0038F970(unsigned char *arg0) {
    unsigned char *o = *(unsigned char **)(arg0 + 0x68);
    int *path = *(int **)(o + 0x60);
    float range = (float)*path;
    float step = *(float *)(o + 0x14);
    int seg = *(short *)(o + 0x70);
    float rate = D_L02_001AEF50 * 0.0003490659f;
    unsigned short *q;
    unsigned char *e;
    unsigned char *s1;
    float prev;
    float h;

    q = (unsigned short *)D_L02_001FC060[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[arg0[0x21]])) {
        e = (unsigned char *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        s1 = *(unsigned char **)(e + 0x68);
        prev = *(float *)(e + 0xF8);
        h = *(float *)(s1 + 0x10) + *(float *)(s1 + 0x7C) * func_00283198(*(float *)(s1 + 0x80));
        if (range <= h)
            h -= range;
        else if (h < 0.0f)
            h += range;
        func_002C9828(path, seg, e + 0x10, e + 0xF0, 0, h);
        *(float *)(s1 + 0x68) = func_00283B98(*(float *)(s1 + 0x68), *(float *)(s1 + 0x6C));
        *(float *)(e + 0x18) += func_00283198(*(float *)(s1 + 0x68));
        *(float *)(s1 + 0x10) += step;
        if (range <= *(float *)(s1 + 0x10))
            *(float *)(s1 + 0x10) -= range;
        *(float *)(s1 + 0x80) = func_00283B98(*(float *)(s1 + 0x80), *(float *)(s1 + 0x84));
        if (func_002A9640(e, 0x4010000, 0) != 0) {
            if (e[0x31] != 0) {
                Vec4 dir;
                float pos[4] __attribute__((aligned(16)));

                ((Ent *)e)->f31 = 0;
                ((Ent *)e)->f34 |= 1;
                ((Ent *)e)->f98 = 0;
                D_L02_001A9048++;
                func_PAL_L00_0032C328(e, D_L02_001AEE50, D_L02_001AEE48, D_L02_001AEE40, 0x3F, 2,
                                  D_L02_001AEE70, 0, 0xFFFF, 0xFF, 0);
                dir.q = 0;
                dir.f[2] = 0.060000002f;
                func_L01_0031A278((char *)e, pos, 0.0f, 0.0f, 0.0f);
                if (*(short *)(e + 0xAA) == 0x1290)
                    func_002E5CF8(0, 0, e);
                if (*(short *)(e + 0xAA) == 0x134B)
                    func_002E5CF8(0, 0, e);
                if (*(short *)(e + 0xAA) == 0xB15)
                    func_002E5CF8(1, 0, e);
                if (*(short *)(e + 0xAA) == 0xB13)
                    func_002E5CF8(1, 0, e);
                func_PAL_002AC718(e, 0.0f, &dir, 0.0f, pos, 5.0f, 0x23, 2.5f, 8, 0x10, 0.0f, 3.0f, -1,
                              15.0f, 1, 10, -1, 0, 0x810001);
            }
        }
        e[0xA8] = 0xFF;
        if (e[0x31] != 0) {
            if ((*(unsigned short *)(e + 0x34) ^ 1) & 1) {
                h = -func_00283BE0(*(float *)(e + 0xF8), prev) * 50.0f;
                if (0.78539824f < h)
                    h = 0.78539824f;
                if (h < -0.78539824f)
                    h = -0.78539824f;
                func_002AA2E8((float *)(e + 0xF0), h, rate);
                if (*(short *)(s1 + 0x72) != 0)
                    func_PAL_L02_0038FDC0(e);
                func_PAL_L02_00390950(e);
            }
        }
        func_002A0F48(e);
        q++;
    }
}
