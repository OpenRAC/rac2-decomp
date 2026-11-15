#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; s32 i[4]; } Vec;
typedef struct {
    u8 pad00[0x10];
    Vec position;
    u8 pad20[0x10];
    u8 opacity;
    u8 pad31;
    s16 mode;
    u16 flags;
    u8 pad36[0x8A];
    Vec forward;
    Vec right;
    Vec up;
} GateMoby;
typedef struct { s32 count; s32 pad04[3]; Vec points[1]; } GatePath;
typedef struct { s32 count; u8 pad04[0x28]; s32 reset; u8 pad30[8]; s32 path; } FeltzinState;
extern s32 D_L05_001B1364 __attribute__((sda));
extern GateMoby *D_L05_001B13B4 __attribute__((sda));
extern GateMoby *D_L05_001B13B8 __attribute__((sda));
extern s32 D_L05_001B13BC __attribute__((sda));
extern f32 D_L05_001B13C0 __attribute__((sda));
extern f32 D_L05_001B13C4 __attribute__((sda));
extern s32 D_L05_001B13C8 __attribute__((sda));
extern s32 D_L05_001B13CC __attribute__((sda));
extern s32 D_L05_001B13D0 __attribute__((sda));
extern s32 D_L05_001B13E4 __attribute__((sda));
extern u8 D_L05_001B3550[] MACRO_ADDR;
extern FeltzinState D_L05_00221D10;
extern u8 D_L05_001B96C0[];
extern GatePath *D_L05_001FE380[];
extern u8 *D_L05_001B251C;
extern s32 g_current_map_index;
extern u8 D_0019B278[];
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_b(s32 a0);
extern void hero_set_state_value_a(s32 a0);
extern void moby_mark_spawned(void *moby);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(u8 *a0, s32 a1);
extern GateMoby *CreateMoby(s32 oclass);
extern u8 *level_find_object_by_class_id(s32 a0);
extern s32 level_get_saved_value_b(u8 *a0);
extern void func_US2_L05_00422530(u8 *actor, s32 mission);
extern void func_US2_L05_00422780(u8 *a0, s32 a1);
extern void FastVecSub(void *dst, void *a, void *b);
extern void FastVecCross(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, f32 scale);
extern f32 FastVecDot(void *a, void *b);
extern f32 fast_vec_dist(void *a, void *b);
extern void hero_add_clamped_stat(f32 a0);
extern void snd_play_from_class_bank(s32 a0, s32 a1, void *a2, s32 a3);
extern void effect_set_enabled(void *moby, s32 a1);
extern void effect_set_color(void *moby, u32 color);
extern s32 pickup_spawn_if_not_taken(void *pos, s32 a1, s32 a2, s32 a3);

/* Mission 3 of the Feltzin dispatcher: gates (class 0x114A) are spawned along the selected path,
   two at a time, each facing along the path. When the player's or the second tracked position's
   dot product with the current gate's forward axis turns positive (and differs from last frame's),
   a pass within 1.25 units of the gate scores, otherwise the miss count rises and the next gate
   takes over. Twelve misses or func_L00_0042B730 fail the mission; once no gate is left, the
   reward is paid through func_US2_L05_00422530. */
void func_US2_L05_00422E88(u8 *actor)
{
    struct { Vec up, pos, toward, away; } v;
    u8 *state = *(u8 **)(actor + 0x68);
    GatePath *path;
    GateMoby *gate;
    u8 *player;
    u8 **objects;
    s32 found;
    s32 n;
    f32 dotPlayer, dotOther;

    v.up.q = 0;
    v.up.f[2] = 1.0f;
    if (!D_L05_001B1364) {
        D_L05_001B13B4 = 0;
        D_L05_001B13B8 = 0;
        D_L05_001B13C0 = -1.0f;
        D_L05_001B13C4 = -1.0f;
        D_L05_001B13C8 = 0;
        D_L05_001B13CC = 0;
        D_L05_001B13D0 = 0;
        D_L05_001B1364 = 1;
        *(s32 *)D_L05_001B3550 = 0;
        D_L05_00221D10.reset = 0;
        music_Unpause();
        if (D_L05_001B13BC) {
            moby_mark_spawned((void *)D_L05_001B13BC);
        }
        entry_init_all_registered();
        D_L05_001B13BC = 0;
        hero_set_state_value_b(1);
        D_L05_00221D10.path = *(s32 *)(state + 0x20);
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        found = level_get_saved_value();
        for (n = 0; n < found; n++) {
            if (*(s16 *)(objects[n] + 0xAA) == 0xF82) {
                entry_spawn_list_objects_with_flag(objects[n], 1);
            }
        }
        path = D_L05_001FE380[*(s32 *)(state + 0x20)];
        while ((!D_L05_001B13B4 || !D_L05_001B13B8) && D_L05_001B13CC != path->count) {
            if (path->points[D_L05_001B13CC].f[3] != -1.0f) {
                gate = CreateMoby(0x114A);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                if (!D_L05_001B13B4) {
                    D_L05_001B13B4 = gate;
                } else {
                    D_L05_001B13B8 = gate;
                }
                if (D_L05_001B13CC == path->count - 1) {
                    FastVecSub(&gate->forward, &path->points[D_L05_001B13CC - 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1.0f);
                } else {
                    FastVecSub(&gate->forward, &path->points[D_L05_001B13CC + 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1.0f);
                }
                FastVecCross(&gate->right, &gate->forward, &v.up);
                vec_scale_to_length(&gate->right, &gate->right, 1.0f);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[D_L05_001B13CC]);
                gate->position.i[3] = 0;
            }
            D_L05_001B13CC++;
        }
    }
    if (!D_L05_001B13B4 && !D_L05_001B13B8 && !D_L05_001B13E4) {
        func_US2_L05_00422530(actor, 3);
        return;
    }
    if (level_get_saved_value_b(level_find_object_by_class_id(0xF82))) {
        D_L05_001B13E4 = 1;
        func_US2_L05_00422780(actor, 3);
        entry_init_all_registered();
    } else if (D_L05_001B13D0 >= 12) {
        D_L05_001B13E4 = 1;
        func_US2_L05_00422780(actor, 3);
        entry_init_all_registered();
    }
    if (D_L05_001B13E4) {
        return;
    }
    if (++*(s32 *)D_L05_001B3550 < 2) {
        return;
    }
    player = D_L05_001B251C + (*(s32 *)(state + 0x24) << 8);
    qcopy(&v.pos, D_L05_001B96C0);
    FastVecSub(&v.away, &v.pos, &D_L05_001B13B4->position);
    vec_scale_to_length(&v.away, &v.away, 1.0f);
    FastVecSub(&v.toward, player + 0x10, &D_L05_001B13B4->position);
    vec_scale_to_length(&v.toward, &v.toward, 1.0f);
    dotPlayer = FastVecDot(&D_L05_001B13B4->forward, &v.toward);
    dotOther = FastVecDot(&D_L05_001B13B4->forward, &v.away);
    if ((dotPlayer != D_L05_001B13C0 && dotPlayer > 0)
        || (dotOther != D_L05_001B13C4 && dotOther > 0)) {
        path = D_L05_001FE380[*(s32 *)(state + 0x20)];
        if (fast_vec_dist(&v.pos, &D_L05_001B13B4->position) <= 1.25f
            || fast_vec_dist(player + 0x10, &D_L05_001B13B4->position) <= 1.25f) {
            hero_add_clamped_stat(0.5f);
            snd_play_from_class_bank(15, 0, actor, 0xFBF);
        } else {
            hero_add_clamped_stat(-0.75f);
            D_L05_001B13D0++;
        }
        moby_mark_spawned((void *)D_L05_001B13B4);
        D_L05_001B13B4 = D_L05_001B13B8;
        D_L05_001B13B8 = 0;
        while (!D_L05_001B13B8 && D_L05_001B13CC != path->count) {
            if (path->points[D_L05_001B13CC].f[3] != -1.0f) {
                gate = CreateMoby(0x114A);
                gate->opacity = 255;
                gate->mode = 0x1FF;
                gate->flags |= 0x100;
                D_L05_001B13B8 = gate;
                if (D_L05_001B13CC == path->count - 1) {
                    FastVecSub(&gate->forward, &path->points[D_L05_001B13CC - 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1.0f);
                } else {
                    FastVecSub(&gate->forward, &path->points[D_L05_001B13CC + 1],
                                  &path->points[D_L05_001B13CC]);
                    gate->forward.i[3] = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1.0f);
                }
                FastVecCross(&gate->right, &gate->forward, &v.up);
                vec_scale_to_length(&gate->right, &gate->right, 1.0f);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, &path->points[D_L05_001B13CC]);
                gate->position.i[3] = 0;
            }
            D_L05_001B13CC++;
        }
    }
    D_L05_001B13C0 = dotPlayer;
    D_L05_001B13C4 = dotOther;
    if (D_L05_001B13B4) {
        effect_set_enabled((void *)D_L05_001B13B4, 1);
        if (D_L05_001B13B8) {
            effect_set_color((void *)D_L05_001B13B4, 0x40008000);
        } else {
            effect_set_color((void *)D_L05_001B13B4, 0x4000C6FF);
        }
    }
    if (D_L05_001B13B8) {
        effect_set_enabled((void *)D_L05_001B13B8, 1);
        effect_set_color((void *)D_L05_001B13B8, 0x40808000);
    } else if (!D_L05_001B13D0 && !D_L05_001B13BC && !D_0019B278[g_current_map_index * 4]) {
        D_L05_001B13BC = pickup_spawn_if_not_taken(&D_L05_001B13B4->position, 0, -1, -1);
    }
}
