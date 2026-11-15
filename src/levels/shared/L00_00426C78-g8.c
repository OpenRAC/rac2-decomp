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
extern int FastDecTimer(char *);
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
/* Checks every frame whether the hero is hitting a trigger the right way. Counts the hits, and after 7 in a row it fires the trigger. It also nudges the camera while a hit is in progress. */
int cam_check_trigger_hit(char *trigger_obj, char *other_obj)
{
    float scratch[4] __attribute__((aligned(16)));
    char dir_a[16] __attribute__((aligned(16)));
    char dir_b[16] __attribute__((aligned(16)));
    TransitionState *transition = *(TransitionState **)(D_L00_001B1844[0].table + *(short *)(trigger_obj + 0x84)*32 + 28);
    char *owner;
    char *blocker;
    int hero_identity;
    int otherType, ownerType;
    float length_product, dot_value;
    if (ref_L00_00426C78_00) { ref_L00_00426C78_00 = 0; return 0; }
    hero_identity = D_00189E20_6C78.identity;
    { int identity = *(short *)(trigger_obj + 0x86);
    ref_L00_00426C78_00 = 0;
    if (hero_identity == identity || hero_identity == 0x51) {
        owner = g_follow_camera_object;
        otherType = *(short *)(other_obj + 0x86);
        if (!(otherType == 0 || otherType == 10 || otherType == 14 || otherType == 2)) goto clear;
        ownerType = *(short *)(owner + 0x86);
        if (!(ownerType == 0 || ownerType == 10 || ownerType == 14 || ownerType == 2)) goto clear;
        *(CameraQuad *)scratch = *(CameraQuad *)g_hero_position;
        blocker = FindIntersectingGridPrimitive((char *)scratch, 0.25f);
        if (blocker && (*(int *)(blocker + 0x18) & 1)) return 0;
        transition->timer = 0;
        transition->active = 1;
        transition->count++;
        if (transition->count >= 7) {
            if (*(short *)(owner + 0x86) == 0) *(char *)(trigger_obj + 0x7C) = 5;
            return 1;
        }
        scratch[0] = math_fast_sin_or_cos_a(D_00189E20_6C78.angle);
        scratch[1] = math_fast_sin_or_cos_b(D_00189E20_6C78.angle);
        scratch[2] = 0;
        cam_set_strength_and_steer((char *)scratch, 0.06981317698955536f, scratch[2]);
        goto timer;
clear:
        transition->count = 0;
        transition->active = 0;
        goto timer;
    }
    }
    transition->count = 0;
    if (transition->active == 0) goto timer;
    transition->active = 0;
    if (*(short *)(D_L00_001B8C80_6C78.owner + 0x86) != 0) goto timer;
    if (D_0018C750_6C78.count < 65535) ++D_0018C750_6C78.count;
    if (D_001A7390[0] > D_0018C750_6C78.time) D_0018C750_6C78.time = D_001A7390[0];
    D_0018C750_6C78.flags = (D_0018C750_6C78.flags | (1U << g_current_map_index[0])) | 0x80000000U;
    dot_value = FastVecDot(D_L00_001B8C80_6C78.axis, D_L00_001B8C80_6C78.owner);
    FastVecScale((char *)scratch, D_L00_001B8C80_6C78.axis, dot_value);
    FastVecSub(dir_a, D_L00_001B8C80_6C78.owner, (char *)scratch);
    dot_value = FastVecDot(D_L00_001B8C80_6C78.axis, D_00189E20_6C78.owner + 0xC0);
    FastVecScale((char *)scratch, D_L00_001B8C80_6C78.axis, dot_value);
    FastVecSub(dir_b, D_00189E20_6C78.owner + 0xC0, (char *)scratch);
    length_product = FastVecLength(dir_b);
    if (length_product != 0.0f) {
        length_product *= FastVecLength(dir_a);
    }
    if (length_product != 0.0f) {
        do { dot_value = math_fast_angle_helper(FastVecDot(dir_b, dir_a) / length_product); } while (0);
        if (1.3962636f <= 1.5707964f - dot_value) { cam_reset_default(); return 0; }
    }
    transition->timer = 30;
timer:
    if (transition->timer) {
        FastDecTimer((char *)&transition->timer);
        scratch[0] = math_fast_sin_or_cos_a(D_00189E20_6C78.angle);
        scratch[1] = math_fast_sin_or_cos_b(D_00189E20_6C78.angle);
        scratch[2] = 0;
        cam_set_strength_and_steer((char *)scratch, 0.13962635397911072f, scratch[2]);
    }
    return 0;
}
