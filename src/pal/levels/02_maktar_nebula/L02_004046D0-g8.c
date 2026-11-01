#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float func_00283CE0(int), func_00283180(float), func_00283198(float), func_00283B98(float, float);
extern float func_002A7878(float, float), func_002A7940(void);
extern int func_002A7820(int, int);
extern void *func_L02_003FC098(char *);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00281DE8(void *, int, int, int);
extern void func_00280B90(void *, int, int);
extern void func_L02_003FFC48(void *, int, float, float, int, int, int);
extern float D_L02_001BA500[4];
extern float D_L02_001B148C[];
extern float D_L02_001B14BC[];
extern int D_L02_001B14A8 __attribute__((sda));
extern int D_L02_001B14AC __attribute__((sda));
extern int D_L02_001B14E4 __attribute__((sda));
extern int D_L02_001B14E8 __attribute__((sda));
extern int D_L02_001B14C0 __attribute__((sda));
extern float D_L02_001B14B0 __attribute__((sda));
extern float D_L02_001B14B8 __attribute__((sda));
extern float D_L02_001B14C4 __attribute__((sda));
extern float D_L02_001B14C8 __attribute__((sda));
extern float D_L02_001B14CC __attribute__((sda));
extern float D_L02_001B14D0 __attribute__((sda));
extern float D_L02_001B14D4 __attribute__((sda));
extern float D_L02_001B14D8 __attribute__((sda));
extern float D_L02_001B14DC __attribute__((sda));
extern float D_L02_001B14E0 __attribute__((sda));
extern float D_L02_001B1488[] SDATA(D_L02_001B1488);

/* Draws two passes of each radial strip and two facing quads at its inner end.
   UVs scroll over time while the complete set rotates. */
void func_PAL_L02_004046D0(char *obj) {
    float center[4], inner[4], outer[4], axis[4], ni[4], no[4];
    struct { float v[4][4]; unsigned color[4]; float uv[4][2]; char rest[32]; } quad;
    float temp[4];
    char *state=*(char **)(obj + 0x68);
    float angle=*(float *)(state + 0xDC);
    float step=6.283185482025146484375f / func_00283CE0(D_L02_001B14C0);
    float alpha, size, halfSize;
    unsigned color;
    int i, j, kind;
    qcopy(center, func_L02_003FC098(obj));
    center[2]-=D_L02_001B14D8;
    for (i = 0; i < D_L02_001B14C0; i++) {
        qcopy(inner, center);
        inner[0]+=D_L02_001B14C8*func_00283180(angle);
        inner[1]+=D_L02_001B14C8*func_00283198(angle);
        qcopy(outer, center);
        outer[0]+=D_L02_001B14CC*func_00283180(angle);
        outer[1]+=D_L02_001B14CC*func_00283198(angle);
        func_00282CF0(axis, inner, outer);
        func_00282CF0(ni, inner, D_L02_001BA500);
        func_00282CF0(no, outer, D_L02_001BA500);
        func_00282DD8(ni, ni, axis);
        func_00282DD8(no, no, axis);
        func_00282F20(ni, ni, D_L02_001B14D0);
        func_00282F20(no, no, D_L02_001B14D0);
        func_00281DE8(&quad, 0x17, 1, 0x80);
        alpha=func_002A7878(D_L02_001B14B8, D_L02_001B14BC[0]);
        color=(D_L02_001B14A8 & 0xFFFFFF) | ((int)(alpha*(float)(int)((unsigned)D_L02_001B14A8>>24))<<24);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=color;
        for (j = 0; j < 4; j++) {
            quad.uv[j][0]=D_L02_001B1488[j*2]+*(float *)(state + 0xE0);
            quad.uv[j][1]=D_L02_001B148C[j*2];
        }
        func_00282CF0(temp, inner, ni);
        *(TI128 *)(quad.v[0])=*(TI128 *)(temp);
        func_00282CC0(temp, inner, ni);
        *(TI128 *)(quad.v[1])=*(TI128 *)(temp);
        func_00282CF0(temp, outer, no);
        *(TI128 *)(quad.v[2])=*(TI128 *)(temp);
        func_00282CC0(temp, outer, no);
        *(TI128 *)(quad.v[3])=*(TI128 *)(temp);
        func_00280B90(&quad, 0, 0);
        func_00282F20(ni, ni, D_L02_001B14D4);
        func_00282F20(no, no, D_L02_001B14D4);
        func_00282CF0(temp, inner, ni);
        *(TI128 *)(quad.v[0])=*(TI128 *)(temp);
        func_00282CC0(temp, inner, ni);
        *(TI128 *)(quad.v[1])=*(TI128 *)(temp);
        func_00282CF0(temp, outer, no);
        *(TI128 *)(quad.v[2])=*(TI128 *)(temp);
        func_00282CC0(temp, outer, no);
        *(TI128 *)(quad.v[3])=*(TI128 *)(temp);
        func_00281DE8(&quad, 0x2B, 1, 0x80);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=D_L02_001B14AC;
        func_00280B90(&quad, 0, 0);
        size=func_002A7878(D_L02_001B14DC, D_L02_001B14E0);
        halfSize=size*0.5f;
        kind=func_002A7820(0x50, 0x60);
        alpha=func_002A7940();
        func_L02_003FFC48(inner, D_L02_001B14E4, halfSize, alpha, kind, 0x31, 2);
        size*=0.7f;
        kind=func_002A7820(8, 0x16);
        alpha=func_002A7940();
        func_L02_003FFC48(inner, D_L02_001B14E8, size, alpha, kind, 0xB, 2);
        angle=func_00283B98(angle, step);
    }
    *(float *)(state + 0xE0)+=D_L02_001B14B0;
    if (*(float *)(state + 0xE0)>1.0f) *(float *)(state + 0xE0)-=2.0f;
    if (*(float *)(state + 0xE0)<-1.0f) *(float *)(state + 0xE0)+=2.0f;
    *(float *)(state + 0xDC)+=D_L02_001B14C4*0.0003490659f;
    if (*(float *)(state + 0xDC)>step) *(float *)(state + 0xDC)=0;
}
