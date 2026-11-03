/* func_00333048: an explosion's sparks, pushed particles, ring effect and area hit.
 * In the hit loop the packet's vector is normalized before func_002A8C00 fills it, as
 * retail does at +0x36C: nothing writes sp+0x40 before that call (the slot is not shared),
 * and func_002A8C00 overwrites the whole vector from `direction` without reading it, so the
 * normalize result is dead. Its own -G8 unit (default -O2 -G8 -ffunction-sections).
 */
#include "common.h"
extern void func_00282F20(void *, void *, float);
typedef int TI128_333048 __attribute__((mode(TI)));

typedef struct {
    int model;
    unsigned char kind;
    unsigned char pad05[0x47];
    short f4C;
    unsigned char pad4E[0x92];
} ClassRecord333048;

/* The hit description func_002A8E20 applies to a moby. */
typedef struct {
    float vector[4];
    char pad10[8];
    unsigned char type;
    unsigned char source;
    short oclass;
    char pad1C[4];
    int flag;
    char pad24[0xC];
} HitInfo333048;

extern unsigned char D_00139568[];
extern ClassRecord333048 D_00239BA0[];
extern char D_001B5200[];
extern short D_001B1CF0[] __attribute__((sda));
extern int D_001AD7EC;
extern char *D_001BF000[];
extern float D_001B0C30 __attribute__((sda));
extern float D_001B0C34 __attribute__((sda));
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_002BDBC0(void *, void *, int, int, int, float);
extern float func_00283248(float, float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern unsigned char *func_002C7E28(void *, void *, int);
extern void func_002ACAD0(void *, short *);
extern void *func_0032C700(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern int func_00277F48(void *, int, void *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_0029F338(void *);

/* The class slot table: D_00139568 maps a slot to its class record. */
static inline int func_00333048_kind(int index)
{
    ClassRecord333048 *record = &D_00239BA0[D_00139568[index]];
    return record->model != 0 && record->kind == 3;
}

/* func_00333048: thirty sparks around the moby, fifty particles pushed away from the
   point at D_001B5200+0x140, a ring effect, then a hit on every moby in range. The ring prototype is
   interleaved as (pointer, float, float, ints...): the EE passes the two floats in $f12/$f13
   either way, and this order gives retail's argument scheduling. */
void func_00333048(char *object)
{
    float direction[4] __attribute__((aligned(16)));
    float spark[4] __attribute__((aligned(16)));
    HitInfo333048 hit __attribute__((aligned(16)));
    float distance;
    float yaw;
    float angle;
    int i;
    int j;
    int k;
    int count;
    char *camera;

    func_002E5CF8(3, 0, (int *)object);
    for (i = 0; i < 30; i++) {
        distance = func_002A7878(0.0f, 0.37f);
        yaw = func_002A7940();
        func_002AF000(spark, distance, yaw, func_002A7940());
        spark[2] += func_002A7878(0.35f, 0.6f);
        func_00282CC0(spark, spark, object + 0x10);
        distance = func_002A7878(0.0016666668f, 0.016666668f);
        yaw = func_002A7940();
        func_002AF000(direction, distance, yaw, func_002A7940());
        func_002BDBC0(spark, direction, 0x4F20507F, 0x102F, func_002A7820(30, 57), 150000.0f);
    }
    camera = D_001B5200;
    for (j = 0; j < 50; j++) {
        angle = func_00283248(*(float *)(camera + 0x140) - *(float *)(object + 0x10),
                              *(float *)(camera + 0x144) - *(float *)(object + 0x14));
        func_00283CF0(func_002A78D8(1.0f, 2.0f));
        direction[0] = *(float *)(object + 0x10) + func_002A78D8(0.0f, 0.15f);
        direction[1] = *(float *)(object + 0x14) + func_002A78D8(0.0f, 0.15f);
        direction[2] = *(float *)(object + 0x18) + func_002A78D8(0.0f, 0.15f);
        distance = D_001B0C30;
        angle = func_00283B98(angle, func_002A78D8(0.0f, -1.5707965f));
        spark[0] = func_00283180(angle) * 0.016666668f * distance;
        spark[1] = func_00283198(angle) * 0.016666668f * distance;
        distance = D_001B0C34;
        spark[2] = distance * 0.016666668f;
        func_002C7E28(direction, spark, 0x140);
    }
    func_002ACAD0(object, D_001B1CF0);
    func_0032C700(object + 0x10, 1.0f, 20.0f, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, D_001AD7EC);
    count = func_00277F48(object + 0x10, 0, object, 0, 3.0f);
    if (count > 0) {
        char **list = D_001BF000;
        k = count;
        do {
            char *moby = *list;
            if (*(short *)(*(char **)(moby + 0x24) + 0x46) == 5
                || (*(unsigned short *)(moby + 0x34) & 0x4000)) {
                float radius;
                func_00282CF0(direction, moby + 0x10, object + 0x10);
                func_00282F20(direction, direction, 1.0f);
                func_00282F20(hit.vector, hit.vector, 1.0f);
                radius = 10.0f;
                if (func_00333048_kind(0x10))
                    radius = 55.0f;
                func_002A8C00(hit.vector, object, 0x810000, direction, radius);
                *(TI128_333048 *)hit.vector = *(TI128_333048 *)direction;
                hit.vector[3] = 5627.9248f;
                hit.source = 3;
                hit.flag = 1;
                hit.type = 5;
                hit.oclass = *(short *)(moby + 0xAA);
                func_002A8E20(moby, &hit);
            }
            list++;
        } while (--k);
    }
    func_0029F338(object);
}
