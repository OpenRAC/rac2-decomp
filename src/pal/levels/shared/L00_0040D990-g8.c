#include "names.h"
/* func_PAL_L00_0040D990, the PAL copy of func_L00_00408E58: the same C with the 50 Hz timers and the
 * lower level test.
 *
 * It has a unit of its own for -g: the entry pointer and the
 * division are two statements, so the second one's line label sits before the
 * lwc1 and the assembler pads one nop in front of div.s (the division floor,
 * docs/build/compiler-notes.md).
 *
 * done starts at 0 and takes the timer's result after the loop. Its value is
 * then equal to i's at the loop guard and it outlives i, so cse keeps it as the
 * canonical register there: the guard tests done, and i is cleared separately.
 * count and timer share a stack record, which keeps the timer's address out of a
 * register that would be issued ahead of the list's address. D_L00_001A8F00 is
 * declared plain: its macro load uses one register for the lui and the lw. */
#include "common.h"

extern void moby_init_first_frame_pal(char *);
extern void ref_L00_00408E58_00(int, int);
extern void anim_start_blended_with_flags(char *, int, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern int vec_fast_helper_b(void *);
extern void mem_fast_helper_b(void *, int);
extern int math_fast_float_d(void *);
extern int get_ammo(int);
extern void start_equipped_item_animation_pal(void);
extern int slot_copy_records_to_free(void *);
extern int PlayMobySound(int, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern char *spark_effect_spawn_pal(void *, int, char *);
extern void func_002E6EF8(void (*)(char *), char *);
extern void gfx_draw_screen_flash_fade(char *);
extern void ReleaseDeadOrExpiredSlots(char *);
extern char *SelectBestTargetInCone(void *, void *, int *, void *, int, int, float, float, float, float, float, int, int);
extern char *moby_get_private_value_0(char *);
extern void SetDeathBits_pal(char *, int, int);
extern void func_00310440(char *);
extern int weapon_spend_ammo(int, int);

extern struct {
    char pad0[0x1230];
    int mask;
    char pad1234[0xc];
    int level;
    char pad1244[0x104c];
    char *object;
    int state;
    char pad2298[0x24];
    unsigned char disabled;
} D_00189E20;

typedef struct {
    char pad[0x54];
    float rate;
    char pad58[0xe0 - 0x58];
} RateEntry;

extern int g_game_l00_mode;
extern int g_pad_held_flags __attribute__((nosda));
extern int g_charging_weapon_initial_value __attribute__((sda));
extern unsigned char g_charging_weapon_index __attribute__((nosda));
extern RateEntry g_weapon_l00_table[];
extern float g_weapon_effect_scale __attribute__((nosda));
extern char g_charging_weapon_sound_records[];
extern char g_cam_follow_matrix[];

#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define B(p, n) (*(unsigned char *)((char *)(p) + (n)))

/* Per-frame update of a charging weapon: it charges, fires a pulse that damages everything in range and plays a sound for the hits. (PAL: 50 Hz timings) */
void charging_weapon_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 104);
    int base[4] __attribute__((aligned(16)));
    int v[4] __attribute__((aligned(16)));
    int out[4] __attribute__((aligned(16)));
    char *list[32];
    struct {
        int count;
        int *timer;
    } hits;
    int i;

    moby_init_first_frame_pal(moby);
    if (g_hero_state.state == 1) {
        ref_L00_00408E58_00(29, 1);
    }
    if (B(moby, 0x31)) {
        g_weapon_effect_scale = 0.1f;
    }
    if (B(moby, 0x42) == B(moby, 0x43) && (B(moby, 0x60) & 2)) {
        anim_start_blended_with_flags(moby, 1, 0, 2, 0);
    }
    FastVecAdd(base, base, moby + 16);
    vec_fast_helper_b(vars);
    if (B(moby, 32) == 1) {
        if (g_game_l00_mode || g_hero_state.disabled || !(g_pad_held_flags & g_hero_state.mask) || g_hero_state.level < 19) {
            return;
        }
        if (get_ammo(-1)) {
            start_equipped_item_animation_pal();
            I(vars, 24) = slot_copy_records_to_free(g_charging_weapon_sound_records);
            B(moby, 32) = 2;
            I(vars, 4) = (((int)(g_charging_weapon_initial_value) * 5 + 2) / 6);
        } else {
            PlayMobySound(4, 0, moby);
        }
        {
            RateEntry *entry = &g_weapon_l00_table[g_charging_weapon_index];
            F(vars, 0) = 1.0f / entry->rate;
        }
    } else if (B(moby, 32) == 2) {
        if (math_fast_float_d(vars + 16)) {
            B(moby, 32) = 4;
            I(vars, 16) = 25;
            I(vars, 20) = 0;
        }
        if (I(vars, 16) == 8) {
            anim_start_blended_with_flags(moby, 2, 0, 2, 0);
            PlayMobySound(1, 0, moby);
        }
    } else if (B(moby, 32) == 4) {
        if (math_fast_float_d(vars + 16)) {
            B(moby, 32) = 5;
            I(vars, 20) = 0;
            I(vars, 16) = 25;
            anim_start_blended_with_flags(moby, 3, 0, 2, 0);
        } else if (!I(vars, 20)) {
            qcopy(v, g_hero_state.object + 0xc0);
            vec_scale_to_length(v, v, 1.0f);
            FastVecAdd(out, base, v);
            spark_effect_spawn_pal(out, 1, moby);
            I(vars, 20) = 1;
        }
    } else if (B(moby, 32) == 5) {
        if (math_fast_float_d(vars + 8)) {
            B(moby, 32) = 3;
            I(vars, 8) = 53;
            anim_start_blended_with_flags(moby, 4, 0, 2, 0);
        } else {
            func_002E6EF8(gfx_draw_screen_flash_fade, moby);
        }
    } else if (B(moby, 32) == 3) {
        int done = 0;

        qcopy(v, g_cam_follow_matrix);
        hits.timer = (int *)(vars + 4);
        mem_fast_helper_b(list, 128);
        ReleaseDeadOrExpiredSlots(moby);
        SelectBestTargetInCone(moby + 16, v, &hits.count, list, 32, 0, 3.1415929794311523f, 1.047197699546814f, 40.0f, 0.0f,
                      0.0f, 0, 0);
        for (i = 0; i < hits.count; i++) {
            char *target_vars;
            int active;

            qcopy_nc(out, list[i] + 16);
            target_vars = moby_get_private_value_0(list[i]);
            active = 1;
            if (target_vars) {
                F(out, 8) += F(target_vars, 16) * 1.5f;
                if (F(target_vars, 0) > 100.0f) {
                    active = 0;
                }
            }
            if (list[i] && B(list[i], 32) != 254 && B(list[i], 32) != 253) {
                if (*(short *)(list[i] + 0xaa) == 0xa8d) {
                    B(list[i], 0x95) = 9;
                }
                if (*(short *)(list[i] + 0xaa) == 0xa8e) {
                    B(list[i], 0x95) = 7;
                }
                if (*(short *)(list[i] + 0xaa) == 0x1002) {
                    B(list[i], 32) = 7;
                }
            }
            if (active) {
                if ((target_vars && B(target_vars, 14) == 1) || B(target_vars, 14) == 2) {
                    spark_effect_spawn_pal(out, 0, 0);
                    I(vars, 28)++;
                    SetDeathBits_pal(list[i], 0, 3);
                    B(target_vars, 14) = 2;
                } else if (target_vars && B(target_vars, 14) != 3) {
                    spark_effect_spawn_pal(out, 0, 0);
                    I(vars, 28)++;
                    SetDeathBits_pal(list[i], 0, 3);
                    func_00310440(list[i]);
                }
            } else {
                F(target_vars, 0) -= 20.0f;
                if (F(target_vars, 0) < 0.0f) {
                    F(target_vars, 0) = 0.0f;
                }
            }
        }
        done = math_fast_float_d(hits.timer);
        if (done) {
            if (I(vars, 28)) {
                PlayMobySound(2, 0, moby);
            } else {
                PlayMobySound(3, 0, moby);
            }
            I(vars, 28) = 0;
            B(moby, 32) = 0;
            weapon_spend_ammo(-1, 1);
        }
    }
}
