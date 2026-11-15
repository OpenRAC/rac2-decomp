#include "common.h"
typedef struct {
    unsigned char pad_0[0x88];
    float field_88;
    unsigned char pad_8C[0xE4];
    float field_170;
    unsigned char pad_174[0x10];
    float field_184;
    unsigned char pad_188[0x30];
    int state_frames;
    int control_mode_frames;
    int step_frames;
    int animation_frames;
    int stick_held_frames;
    int stick_idle_frames;
    unsigned char pad_1D0[0x8];
    int item_animation_frames;
    unsigned char pad_1DC[0x4];
    short field_1E0;
    unsigned char pad_1E2[0x6];
    int field_1E8;
    unsigned char pad_1EC[0x16];
    short still_frames;
    unsigned char pad_204[0x8];
    short field_20C;
    unsigned char pad_20E[0xE];
    short field_21C;
    unsigned char pad_21E[0x6];
    short field_224;
    unsigned char pad_226[0x2];
    short field_228;
    short field_22A;
    unsigned char pad_22C[0xF0];
    float field_31C;
    unsigned char pad_320[0x1C];
    unsigned char * field_33C;
    int field_340;
    unsigned char pad_344[0xA];
    short field_34E;
    unsigned char pad_350[0x270];
    unsigned char * field_5C0;
    unsigned char pad_5C4[0xC84];
    int field_1248;
    unsigned char pad_124C[0x208];
    short field_1454;
    unsigned char pad_1456[0xE3A];
    int field_2290;
    int field_2294;
    unsigned char pad_2298[0x4];
    int field_229C;
    unsigned char pad_22A0[0x14];
    unsigned char mode;
    unsigned char pad_22B5[0x3];
    unsigned char item_animation_active;
    unsigned char pad_22B9[0x4];
    unsigned char tilt_disabled;
    unsigned char pad_22BE[0x5];
    unsigned char field_22C3;
    unsigned char pad_22C4[0x100];
    int pos_history_index;
    int pos_history_count;
    unsigned char pad_23CC[0xD8];
    float reach_distance;
    float reach_height;
    unsigned char pad_24AC[0x20];
    int field_24CC;
    unsigned char pad_24D0[0xC];
    float current_path_dist;
} HeroTimerState;

extern HeroTimerState D_00189E20;
extern int D_L00_001B19C8;

#define BS(p, o) (*(short *)((p)+(o)))
#define BU(p, o) (*(unsigned short *)((p)+(o)))
#define BP(p, o) (*(unsigned char **)((p)+(o)))

typedef struct {
    unsigned char pad[0x1A0];
    int held;
    int pressed;
    unsigned char pad1[0x2C];
    int no_direction;
} TimerPadState;

extern TimerPadState D_00138180;
extern unsigned char *D_L00_001FACE0[];
extern unsigned char D_L00_0025BC60[];
extern int D_L00_001A8F00_abs __asm__("D_L00_001A8F00");
extern float D_L00_001B18E0, D_L00_001B18E4;
/* The equipment flag at 0x1A7AFF: a small-data object at a nonzero offset, length 2 for reorg. */
extern unsigned char D_001A7A70[] __attribute__((sda));
extern void func_L00_002B9380(void), func_L00_002A7A10(void), func_L00_002C3838(void), func_L00_002B30E8(void);
extern int func_00282978(void *), func_00282948(void *);
extern void func_00282C88(void *);
extern int func_002ABB78(void *), func_002A77E0(int);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float);
extern int func_002A8F70(void *, int, int, void *, void *, float);
extern void func_00282CC0(void *, void *, void *), func_00282D30(void *, void *, float);
extern float func_L00_002D3B00(void *), func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_L00_002D36E0(void *, int, float, float, float), func_L00_002D3778(void *, void *, float);

/* Corresponds to RAC1 update_hero_timers_and_reach_state in
 * src/overlays/shared/hero_vehicle_and_collision.c. */
/* Counts up the hero's many timers each frame, and tracks how long the hero stands still. It also
 * pushes the hero away from nearby objects and updates the reach distance. */
void func_L00_002C30B0(void) {
    unsigned char *moby, *pos, *hero;
    float sum[4], delta[4];
    int i, count, history_index, first_index, second_index;
    if (!gHeroState.tilt_disabled) EaseHeroLeanToUpright();
    {
        int state = gHeroState.state_frames+1;
        int control = gHeroState.control_mode_frames+1;
        int step = gHeroState.step_frames+1;
        int animation = gHeroState.animation_frames+1;
        gHeroState.state_frames = state;
        gHeroState.control_mode_frames = control;
        gHeroState.step_frames = step;
        gHeroState.animation_frames = animation;
    }
    FastDecTimer(((unsigned char *)&gHeroState)+0x1E0);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1DC);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1D2);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1E4);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1F8);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1FE);
    FastFloatHelperD(((unsigned char *)&gHeroState)+0x1D4);
    FastDecTimer(((unsigned char *)&gHeroState)+0x210);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1D0);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1F4);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1F6);
    FastDecTimer(((unsigned char *)&gHeroState)+0x204);
    FastDecTimer(((unsigned char *)&gHeroState)+0x206);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1F0);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1EC);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1EE);
    FastDecTimer(((unsigned char *)&gHeroState)+0x208);
    FastDecTimer(((unsigned char *)&gHeroState)+0x200);
    FastDecTimer(((unsigned char *)&gHeroState)+0x20E);
    FastDecTimer(((unsigned char *)&gHeroState)+0x20A);
    FastDecTimer(((unsigned char *)&gHeroState)+0x214);
    FastDecTimer(((unsigned char *)&gHeroState)+0x212);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1FC);
    FastDecTimer(((unsigned char *)&gHeroState)+0x216);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1FA);
    FastDecTimer(((unsigned char *)&gHeroState)+0x218);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1F2);
    FastDecTimer(((unsigned char *)&gHeroState)+0x21A);
    FastDecTimer(((unsigned char *)&gHeroState)+0x21C);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1DE);
    FastDecTimer(((unsigned char *)&gHeroState)+0x1E6);
    FastDecTimer(((unsigned char *)&gHeroState)+0x222);
    FastDecTimer(((unsigned char *)&gHeroState)+0x224);
    FastDecTimer(((unsigned char *)&gHeroState)+0x226);

    if (!(gPadState.held&4)) gHeroState.field_20C = 0;
    if (gHeroState.field_21C) QueueHeroGlowDrawRoutine();
    if (gHeroState.item_animation_active) gHeroState.item_animation_frames++;
    else gHeroState.item_animation_frames = 0;
    if (gPadState.no_direction) {
        gHeroState.stick_held_frames = 0;
        gHeroState.stick_idle_frames++;
    }
    else {
        gHeroState.stick_idle_frames = 0;
        gHeroState.stick_held_frames++;
    }
    if (gHeroState.field_22C3 && !gHeroState.field_229C && gHeroState.field_340 && gHeroState.field_170<0.0016666668f && gHeroState.field_184<0.0016666668f) qcopy(((unsigned char *)&gHeroState)+0x80, ((unsigned char *)&gHeroState)+0x2030);
    if (gHeroState.field_1454) gHeroState.field_1E8 = 0;
    else gHeroState.field_1E8++;
    if (!D_L00_001A8F00_abs) {
        if (D_L00_001B18E0>0) gHeroState.field_22A++;
        else gHeroState.field_22A = 0;
        if (gHeroState.field_22A>120) {
            D_L00_001B18E0 = 0;
            gHeroState.field_22A = 0;
        }
        if (D_L00_001B18E4>0) gHeroState.field_228++;
        else gHeroState.field_228 = 0;
        if (gHeroState.field_228>120) {
            gHeroState.field_228 = 0;
            D_L00_001B18E4 = 0;
        }
    }
    if (gHeroState.field_224) {
        for (i = 0;(moby = D_L00_001FACE0[i]) != 0;i++) {
            if (IsMobyInSpecialClassRange(moby) || (moby && BP(moby, 0x24) && BS(BP(moby, 0x24), 0x46) == 22)) {
                if ((gFrameCounter_L00&7) == (((int)moby>>8)&7) || !RandomIntBelow(4)) {
                    hero = (unsigned char *)&gHeroState+0x80;
                    pos = moby+0x10;
                    if (fast_vec_dist(hero, pos)<15.37f) {
                        FastVecSub(sum, pos, hero);
                        vec_scale_to_length(sum, sum, 1.7f);
                        QueueImpactEffect(moby, gHeroState.field_2290, 0x4000000, hero, sum, 1.0f);
                    }
                }
            }
        }
    }
    for (i = 0;i<4;i++) FastFloatHelperD(D_L00_0025BC60+i*0x70);
    gHeroState.current_path_dist = 9999.0f;
    if (gHeroState.field_34E && GetViewSpaceHeight(((unsigned char *)&gHeroState)+0xF0)<0) {
        if (gHeroState.pos_history_count != 32) goto history_done;
        ClearVector128(sum);
        count = 8;
        for (i = 0;i<count;) {
            history_index = gHeroState.pos_history_index-i;
            first_index = (history_index+31)%32;
            second_index = (history_index+30)%32;
            FastVecSub(delta, ((unsigned char *)&gHeroState)+0x1D90+first_index*16, ((unsigned char *)&gHeroState)+0x1D90+second_index*16);
            i++;
            FastVecAdd(sum, sum, delta);
        }
        FastVecScale(sum, sum, 1.0f/(float)count);
        if (FastVecLength(sum)<0.016666668f) {
            gHeroState.still_frames++;
            goto history_done;
        }
    }
    gHeroState.still_frames = 0;
history_done:
    UpdateHeroLandingSlide();
    if (gHeroState.mode == 1) BuildHeroRelativePoint((unsigned char *)&gHeroState+0xE0, 1, 0, 0, 0.4f);
    else BuildHeroRelativePoint((unsigned char *)&gHeroState+0xE0, 1, 0, 0, 0.7f);
    if (!(gFrameCounter_L00&3)) {
        if (gHeroState.mode == 1) {
            gHeroState.reach_distance = 2.125f;
            gHeroState.reach_height = 1.25f;
        }
        else if (D_001A7A70[0x8F]) {
            gHeroState.reach_distance = 14;
            gHeroState.reach_height = 4.5f;
        }
        else {
            gHeroState.reach_distance = 4.25f;
            gHeroState.reach_height = 2.25f;
        }
    }
    if (gHeroState.field_31C<4) {
        qcopy(((unsigned char *)&gHeroState)+0xD0, ((unsigned char *)&gHeroState)+0x2D0);
        ApplyHeroModeTransformReversed(((unsigned char *)&gHeroState)+0xD0, ((unsigned char *)&gHeroState)+0xD0, 0.5f);
    }
    else qcopy(((unsigned char *)&gHeroState)+0xD0, ((unsigned char *)&gHeroState)+0xE0);
    {
        unsigned char *heldMoby = gHeroState.field_5C0;
        if (heldMoby) {
            if (!(BU(heldMoby, 0x34)&0x1000) || heldMoby == gHeroState.field_33C) gHeroState.field_5C0 = 0;
            if (gHeroState.field_5C0 && gHeroState.field_1248 != 46) gHeroState.field_5C0 = 0;
        }
    }
    if (gHeroState.field_88<1) RecordHeroPlayCounters();
}
