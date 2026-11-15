#include "names.h"
/* func_PAL_L00_0042C190, the PAL copy of func_L00_00426C78: the same C, where the count limit
   7 becomes 6, the timer 30 becomes 25, and the time record is scaled to 50 Hz. */
#include "common.h"
extern float FastVecDot(char *, char *);
extern float FastVecLength(char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_angle_helper(float);
extern void FastVecScale(char *, char *, float);
extern void FastVecSub(char *, char *, char *);
extern char *FindIntersectingGridPrimitive(char *, float);
extern void cam_set_strength_and_steer(char *, float, float);
extern void cam_reset_default(void);
extern void FastDecTimer(char *);
typedef struct { char *table; } Table_b0898;
extern Table_b0898 D_L00_001B1844[] __attribute__((section(".sdata")));
extern int ref_L00_00426C78_00 __attribute__((sda));
extern char *g_follow_camera_object __attribute__((section(".data")));
extern char g_hero_position[];
extern unsigned int D_001A7390[] __attribute__((section(".sdata")));
extern int g_current_map_index[] __attribute__((section(".sdata")));
typedef struct {
 char pad[0x98]; float angle; char pad9c[0x2290-0x9C]; char *owner;
 char pad2294[0x24A0-0x2294]; int identity;
} Global_6C78;
extern Global_6C78 D_00189E20_6C78;
typedef struct { char pad[0x190]; char *owner; char pad194[0x3C]; char axis[16]; } Global_6C78B;
extern Global_6C78B D_L00_001B8C80_6C78;
typedef struct { char pad[0x198]; unsigned short count; char pad19a[2]; unsigned int time; unsigned int flags; } Global_6C78C;
extern Global_6C78C D_0018C750_6C78;

typedef struct { char pad[0x20]; short count, active, timer; } TransitionState;
typedef int CameraQuad __attribute__((mode(TI)));
int func_PAL_L00_0042C190(char *a, char *b)
{
    float temp[4] __attribute__((aligned(16)));
    char v1[16] __attribute__((aligned(16)));
    char v2[16] __attribute__((aligned(16)));
    TransitionState *p = *(TransitionState **)(D_L00_001B1844[0].table + *(short *)(a + 0x84)*32 + 28);
    char *owner;
    char *hit;
    int type;
    int otherType, ownerType;
    float len, dot;
    if (ref_L00_00426C78_00) { ref_L00_00426C78_00 = 0; return 0; }
    type = D_00189E20_6C78.identity;
    { int identity = *(short *)(a + 0x86);
    ref_L00_00426C78_00 = 0;
    if (type == identity || type == 0x51) {
        owner = g_follow_camera_object;
        otherType = *(short *)(b + 0x86);
        if (!(otherType == 0 || otherType == 10 || otherType == 14 || otherType == 2)) goto clear;
        ownerType = *(short *)(owner + 0x86);
        if (!(ownerType == 0 || ownerType == 10 || ownerType == 14 || ownerType == 2)) goto clear;
        *(CameraQuad *)temp = *(CameraQuad *)g_hero_position;
        hit = FindIntersectingGridPrimitive((char *)temp, 0.25f);
        if (hit && (*(int *)(hit + 0x18) & 1)) return 0;
        p->timer = 0;
        p->active = 1;
        p->count++;
        if (p->count >= 6) {
            if (*(short *)(owner + 0x86) == 0) *(char *)(a + 0x7C) = 5;
            return 1;
        }
        temp[0] = math_fast_sin_or_cos_a(D_00189E20_6C78.angle);
        temp[1] = math_fast_sin_or_cos_b(D_00189E20_6C78.angle);
        temp[2] = 0;
        cam_set_strength_and_steer((char *)temp, 0.06981317698955536f, temp[2]);
        goto timer;
clear:
        p->count = 0;
        p->active = 0;
        goto timer;
    }
    }
    p->count = 0;
    if (p->active == 0) goto timer;
    p->active = 0;
    if (*(short *)(D_L00_001B8C80_6C78.owner + 0x86) != 0) goto timer;
    if (D_0018C750_6C78.count < 65535) ++D_0018C750_6C78.count;
    if (((int)D_001A7390[0] * 5 + 2) / 6 > D_0018C750_6C78.time) D_0018C750_6C78.time = ((int)D_001A7390[0] * 5 + 2) / 6;
    D_0018C750_6C78.flags = (D_0018C750_6C78.flags | (1U << g_current_map_index[0])) | 0x80000000U;
    dot = FastVecDot(D_L00_001B8C80_6C78.axis, D_L00_001B8C80_6C78.owner);
    FastVecScale((char *)temp, D_L00_001B8C80_6C78.axis, dot);
    FastVecSub(v1, D_L00_001B8C80_6C78.owner, (char *)temp);
    dot = FastVecDot(D_L00_001B8C80_6C78.axis, D_00189E20_6C78.owner + 0xC0);
    FastVecScale((char *)temp, D_L00_001B8C80_6C78.axis, dot);
    FastVecSub(v2, D_00189E20_6C78.owner + 0xC0, (char *)temp);
    len = FastVecLength(v2);
    if (len != 0.0f) {
        len *= FastVecLength(v1);
    }
    if (len != 0.0f) {
        dot = math_fast_angle_helper(FastVecDot(v2, v1) / len);
        if (1.3962636f <= 1.5707964f - dot) { cam_reset_default(); return 0; }
    }
    p->timer = 25;
timer:
    if (p->timer) {
        FastDecTimer((char *)&p->timer);
        temp[0] = math_fast_sin_or_cos_a(D_00189E20_6C78.angle);
        temp[1] = math_fast_sin_or_cos_b(D_00189E20_6C78.angle);
        temp[2] = 0;
        cam_set_strength_and_steer((char *)temp, 0.13962635397911072f, temp[2]);
    }
    return 0;
}
