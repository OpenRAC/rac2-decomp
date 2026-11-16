#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_003EED30, the PAL copy of func_L00_003EAA58: the same C, where 0.25f becomes 0.3f,
   0.00305556f becomes 0.0044f, and the 50 Hz counts 40, 20 and 10 become 33, 17 and 8. */
extern void miniturret_glove_draw_pal();
/* Partial resident state layout measured from this handler's accesses. */
typedef struct {
    char p0[0xBF8];
    int field_BF8;
    char p1[0x1230 - 0xBFC];
    int field_1230;
    char p2[0x1240 - 0x1234];
    int field_1240;
    char p3[0x1450 - 0x1244];
    int field_1450;
    char p4[0x2294 - 0x1454];
    int field_2294;
    char p5[0x22BC - 0x2298];
    unsigned char field_22BC;
    char p6[0x2534 - 0x22BD];
    int field_2534;
} HeroState;
extern HeroState g_hero_state;

extern char g_pad_state[];
extern void CalculateAimedLaunchVelocity(void *, void *, float, float, float, float, int, int);
extern void moby_transform_joint_to_world(char *, int, void *);
extern int coll_trace_projectile_to_impact_pal(void *, void *, void *, void *, char *, int, int, float);
extern int math_fast_float_d(void *), weapon_spend_ammo(int, int);
extern void func_PAL_L00_002AF458(void), cancel_hero_item_animation_pal(void), ref_L00_003EAA58_00(void *, char *);
extern int PlayMobySound(int, int, char *);
extern char *func_PAL_L00_0038ACC8(void *, void *);
void miniturret_l00_glove_update_pal(char *self)
{
    char a[16], b[16];
    char *bp;
    char *st = *(char **)(self + 0x68);
    int ready;
    float scale;
    char *shot;
    moby_transform_joint_to_world(self, 0, a);
    bp = b;
    scale = g_hero_state.field_2294 == 29 ? 11.0f : 4.5f;
    CalculateAimedLaunchVelocity(bp, a, 1.5f, scale, 0.3f, 0.0044f, 0, 0);
    *(int *)(st + 0x24) = coll_trace_projectile_to_impact_pal(a, bp, st, st + 0x10, self, 0, 0, 0.0044f);
    ready = 1;
    if (g_hero_state.field_2294 == 29) {
        if (!math_fast_float_d(&g_hero_state.field_2534)) ready = 0;
    } else g_hero_state.field_2534 = 33;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(st + 0x24) = 0;
        /* Fall through. */
    case 1:
        if ((*(int *)(g_pad_state + 0x1A4) & g_hero_state.field_1230) &&
            !g_hero_state.field_22BC && ready) {
            if (weapon_spend_ammo(-1, 1)) {
                func_PAL_L00_002AF458();
                self[0x20] = 2;
                *(int *)(st + 0x20) = 17;
            } else PlayMobySound(2, 0, self);
        }
        break;
    case 2:
        if (math_fast_float_d(st + 0x20)) {
            PlayMobySound(0, 0, self);
            shot = func_PAL_L00_0038ACC8(a, bp);
            *(char **)(shot + 0xB8) = self;
            cancel_hero_item_animation_pal();
            self[0x20] = 3;
            *(int *)(st + 0x20) = 8;
        }
        break;
    case 3:
        if (math_fast_float_d(st + 0x20)) self[0x20] = 1;
        break;
    }
    ref_L00_003EAA58_00(miniturret_glove_draw_pal, self);
}

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;
extern void func_002FDBD8_4(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void miniturret_glove_draw_pal(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_4(1.0f, context, context->vector_10, 0);
    }
}

