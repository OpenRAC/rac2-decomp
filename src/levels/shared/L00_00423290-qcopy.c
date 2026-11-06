#include "common.h"
/* Camera id/state fields are independently observed at the same offsets
 * as the public RAC1 Camera prefix (origin/main 1d8228cc). */
typedef struct {
    unsigned char bytes00[0x70];
    char *state;
    unsigned char bytes74[0x12];
    short id;
} CameraInitPrefix;
extern unsigned char D_00189E20[];


#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif

extern void func_00282CF0_2(void *b, void *c, void *d);

extern void func_00282CC0(void *c, void *c2, void *s);

extern void func_00282D30(void *dst, void *src, float k);

extern float func_00282DB0_1(char *local, char *p);

extern void func_00282C88(void *a);





void func_L00_00423290(CameraInitPrefix *camera)
{
    char *obj;
    char *v60;
    char *vB0;
    char *vF0;
    char *v160;
    char *hero;
    char *pos;
    char *hpos;
    V4_F0fba48d3 *dst;
    char buf0[16];
    char buf1[16];

    if (camera->id != 0)
        return;

    hero = (char *)D_00189E20 + 0x2C0;
    pos = camera->state;
    v160 = pos + 0x160;
    v60 = pos + 0x60;
    obj = pos;
    pos = buf0;

    func_00282D30(pos, hero, -1.0f);
    /* The hero's position, 0x240 below the facing direction the call above uses. */
    hpos = hero - 0x240;
    *(V4_F0fba48d3 *)v60 = *(V4_F0fba48d3 *)hpos;
    dst = (V4_F0fba48d3 *)(obj + 0xC0);
    *dst = *(V4_F0fba48d3 *)v60;
    vB0 = obj + 0xB0;
    vF0 = obj + 0xF0;
    func_00282D30(obj + 0x70, buf0, func_00282DB0_1(v60, buf0));
    func_00282C88(obj + 0xD0);
    func_00282C88(obj + 0xE0);
    func_00282C88(obj + 0x100);
    func_00282D30(buf1, buf0, *(float *)(v160 + 0x30));
    func_00282CC0(vB0, buf1, v60);
    func_00282D30(buf1, buf0, *(float *)(v60 + 0xB0));
    func_00282CC0(vF0, buf1, v60);
    dst = (V4_F0fba48d3 *)(obj + 0xA0);
    *dst = *(V4_F0fba48d3 *)vF0;
    func_00282CF0_2(v160, (char *)camera + 0x30, vB0);
    dst = (V4_F0fba48d3 *)(obj + 0x170);
    *dst = *(V4_F0fba48d3 *)v160;
    *(V4_F0fba48d3 *)obj = *(V4_F0fba48d3 *)((char *)camera + 0x30);
    func_00282CC0(obj + 0x210, vB0, v160);
    *(int *)(obj + 0x240) = 0;
}
