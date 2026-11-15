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

extern HeroTimerState g_hero_state;
extern int g_frame_l00_counter;

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

extern TimerPadState g_pad_state;
extern unsigned char *D_L00_001FACE0[];
extern unsigned char D_L00_0025BC60[];
extern int D_L00_001A8F00_abs __asm__("D_L00_001A8F00");
extern float D_L00_001B18E0, D_L00_001B18E4;
/* The equipment flag at 0x1A7AFF: a small-data object at a nonzero offset, length 2 for reorg. */
extern unsigned char D_001A7A70[] __attribute__((sda));
extern void hero_ease_lean_to_upright(void), hero_queue_glow_draw_routine(void), hero_update_landing_slide(void), hero_record_play_counters(void);
extern int FastDecTimer(void *), math_fast_float_d(void *);
extern void vec_clear_128(void *);
extern int moby_is_in_special_class_range(void *), math_random_int_below(int);
extern void FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void part_queue_impact_effect(void *, int, int, void *, void *, float);
extern void FastVecAdd(void *, void *, void *), FastVecScale(void *, void *, float);
extern float cam_get_view_space_height(void *), FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern void hero_build_relative_point(void *, int, float, float, float), hero_apply_mode_transform_reversed(void *, void *, float);

/* Corresponds to RAC1 update_hero_timers_and_reach_state in
 * src/overlays/shared/hero_vehicle_and_collision.c. */
/* Counts up the hero's many timers each frame, and tracks how long the hero stands still. It also
 * pushes the hero away from nearby objects and updates the reach distance. */
void hero_l00_update_timers(void) {
    unsigned char *moby, *pos, *hero;
    float sum[4], delta[4];
    int i, count, history_index, first_index, second_index;
    if (!g_hero_state.tilt_disabled) hero_ease_lean_to_upright();
    {
        int state = g_hero_state.state_frames+1;
        int control = g_hero_state.control_mode_frames+1;
        int step = g_hero_state.step_frames+1;
        int animation = g_hero_state.animation_frames+1;
        g_hero_state.state_frames = state;
        g_hero_state.control_mode_frames = control;
        g_hero_state.step_frames = step;
        g_hero_state.animation_frames = animation;
    }
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1E0);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1DC);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1D2);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1E4);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1F8);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1FE);
    math_fast_float_d(((unsigned char *)&g_hero_state)+0x1D4);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x210);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1D0);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1F4);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1F6);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x204);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x206);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1F0);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1EC);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1EE);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x208);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x200);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x20E);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x20A);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x214);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x212);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1FC);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x216);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1FA);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x218);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1F2);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x21A);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x21C);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1DE);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x1E6);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x222);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x224);
    FastDecTimer(((unsigned char *)&g_hero_state)+0x226);

    if (!(g_pad_state.held&4)) g_hero_state.field_20C = 0;
    if (g_hero_state.field_21C) hero_queue_glow_draw_routine();
    if (g_hero_state.item_animation_active) g_hero_state.item_animation_frames++;
    else g_hero_state.item_animation_frames = 0;
    if (g_pad_state.no_direction) {
        g_hero_state.stick_held_frames = 0;
        g_hero_state.stick_idle_frames++;
    }
    else {
        g_hero_state.stick_idle_frames = 0;
        g_hero_state.stick_held_frames++;
    }
    if (g_hero_state.field_22C3 && !g_hero_state.field_229C && g_hero_state.field_340 && g_hero_state.field_170<0.0016666668f && g_hero_state.field_184<0.0016666668f) qcopy(((unsigned char *)&g_hero_state)+0x80, ((unsigned char *)&g_hero_state)+0x2030);
    if (g_hero_state.field_1454) g_hero_state.field_1E8 = 0;
    else g_hero_state.field_1E8++;
    if (!D_L00_001A8F00_abs) {
        if (D_L00_001B18E0>0) g_hero_state.field_22A++;
        else g_hero_state.field_22A = 0;
        if (g_hero_state.field_22A>120) {
            D_L00_001B18E0 = 0;
            g_hero_state.field_22A = 0;
        }
        if (D_L00_001B18E4>0) g_hero_state.field_228++;
        else g_hero_state.field_228 = 0;
        if (g_hero_state.field_228>120) {
            g_hero_state.field_228 = 0;
            D_L00_001B18E4 = 0;
        }
    }
    if (g_hero_state.field_224) {
        for (i = 0;(moby = D_L00_001FACE0[i]) != 0;i++) {
            if (moby_is_in_special_class_range(moby) || (moby && BP(moby, 0x24) && BS(BP(moby, 0x24), 0x46) == 22)) {
                if ((g_frame_l00_counter&7) == (((int)moby>>8)&7) || !math_random_int_below(4)) {
                    hero = (unsigned char *)&g_hero_state+0x80;
                    pos = moby+0x10;
                    if (fast_vec_dist(hero, pos)<15.37f) {
                        FastVecSub(sum, pos, hero);
                        vec_scale_to_length(sum, sum, 1.7f);
                        part_queue_impact_effect(moby, g_hero_state.field_2290, 0x4000000, hero, sum, 1.0f);
                    }
                }
            }
        }
    }
    for (i = 0;i<4;i++) math_fast_float_d(D_L00_0025BC60+i*0x70);
    g_hero_state.current_path_dist = 9999.0f;
    if (g_hero_state.field_34E && cam_get_view_space_height(((unsigned char *)&g_hero_state)+0xF0)<0) {
        if (g_hero_state.pos_history_count != 32) goto history_done;
        vec_clear_128(sum);
        count = 8;
        for (i = 0;i<count;) {
            history_index = g_hero_state.pos_history_index-i;
            first_index = (history_index+31)%32;
            second_index = (history_index+30)%32;
            FastVecSub(delta, ((unsigned char *)&g_hero_state)+0x1D90+first_index*16, ((unsigned char *)&g_hero_state)+0x1D90+second_index*16);
            i++;
            FastVecAdd(sum, sum, delta);
        }
        FastVecScale(sum, sum, 1.0f/(float)count);
        if (FastVecLength(sum)<0.016666668f) {
            g_hero_state.still_frames++;
            goto history_done;
        }
    }
    g_hero_state.still_frames = 0;
history_done:
    hero_update_landing_slide();
    if (g_hero_state.mode == 1) hero_build_relative_point((unsigned char *)&g_hero_state+0xE0, 1, 0, 0, 0.4f);
    else hero_build_relative_point((unsigned char *)&g_hero_state+0xE0, 1, 0, 0, 0.7f);
    if (!(g_frame_l00_counter&3)) {
        if (g_hero_state.mode == 1) {
            g_hero_state.reach_distance = 2.125f;
            g_hero_state.reach_height = 1.25f;
        }
        else if (D_001A7A70[0x8F]) {
            g_hero_state.reach_distance = 14;
            g_hero_state.reach_height = 4.5f;
        }
        else {
            g_hero_state.reach_distance = 4.25f;
            g_hero_state.reach_height = 2.25f;
        }
    }
    if (g_hero_state.field_31C<4) {
        qcopy(((unsigned char *)&g_hero_state)+0xD0, ((unsigned char *)&g_hero_state)+0x2D0);
        hero_apply_mode_transform_reversed(((unsigned char *)&g_hero_state)+0xD0, ((unsigned char *)&g_hero_state)+0xD0, 0.5f);
    }
    else qcopy(((unsigned char *)&g_hero_state)+0xD0, ((unsigned char *)&g_hero_state)+0xE0);
    {
        unsigned char *heldMoby = g_hero_state.field_5C0;
        if (heldMoby) {
            if (!(BU(heldMoby, 0x34)&0x1000) || heldMoby == g_hero_state.field_33C) g_hero_state.field_5C0 = 0;
            if (g_hero_state.field_5C0 && g_hero_state.field_1248 != 46) g_hero_state.field_5C0 = 0;
        }
    }
    if (g_hero_state.field_88<1) hero_record_play_counters();
}
