#include "names.h"
/* func_L00_00408E58 has a unit of its own for -g: the entry pointer and the
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

extern void moby_init_first_frame(char *);
extern void ref_L00_00408E58_00(int, int);
extern void anim_start_blended_with_flags(char *, int, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_helper_b(void *);
extern void mem_fast_helper_b(void *, int);
extern int math_fast_float_d(void *);
extern int get_ammo(int);
extern void start_equipped_item_animation(void);
extern int slot_copy_records_to_free(void *);
extern void PlayMobySound(int, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern char *spark_effect_spawn(void *, int, char *);
extern void func_002E6EF8(void (*)(char *), char *);
extern void gfx_draw_screen_flash_fade(char *);
extern void ReleaseDeadOrExpiredSlots(char *);
extern void SelectBestTargetInCone(void *, void *, int *, void *, int, int, float, float, float, float, float, int, int);
extern char *moby_get_private_value_0(char *);
extern void SetDeathBits(char *, int, int);
extern void func_00310440(char *);
extern void weapon_spend_ammo(int, int);

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

extern int D_L00_001A8F00;
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001B0F90 __attribute__((sda));
extern unsigned char D_00139593 __attribute__((nosda));
extern RateEntry g_weapon_l00_table[];
extern float D_L00_0025C64C __attribute__((nosda));
extern char D_L00_0029FBE0[];
extern char D_L00_001B8FF0[];

#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define B(p, n) (*(unsigned char *)((char *)(p) + (n)))

/* Per-frame update of a charging weapon: it charges, fires a pulse that damages everything in range and plays a sound for the hits. */
void charging_weapon_update(char *object)
{
    char *vars = *(char **)(object + 104);
    int base[4] __attribute__((aligned(16)));
    int v[4] __attribute__((aligned(16)));
    int out[4] __attribute__((aligned(16)));
    char *list[32];
    struct {
        int count;
        int *timer;
    } hits;
    int i;

    moby_init_first_frame(object);
    if (g_hero_state.state == 1) {
        ref_L00_00408E58_00(29, 1);
    }
    if (B(object, 0x31)) {
        D_L00_0025C64C = 0.1f;
    }
    if (B(object, 0x42) == B(object, 0x43) && (B(object, 0x60) & 2)) {
        anim_start_blended_with_flags(object, 1, 0, 2, 0);
    }
    FastVecAdd(base, base, object + 16);
    vec_fast_helper_b(vars);
    if (B(object, 32) == 1) {
        if (D_L00_001A8F00 || g_hero_state.disabled || !(D_00138324 & g_hero_state.mask) || g_hero_state.level < 23) {
            return;
        }
        if (get_ammo(-1)) {
            start_equipped_item_animation();
            I(vars, 24) = slot_copy_records_to_free(D_L00_0029FBE0);
            B(object, 32) = 2;
            I(vars, 4) = D_L00_001B0F90;
        } else {
            PlayMobySound(4, 0, object);
        }
        {
            RateEntry *entry = &g_weapon_l00_table[D_00139593];
            F(vars, 0) = 1.0f / entry->rate;
        }
    } else if (B(object, 32) == 2) {
        if (math_fast_float_d(vars + 16)) {
            B(object, 32) = 4;
            I(vars, 16) = 30;
            I(vars, 20) = 0;
        }
        if (I(vars, 16) == 10) {
            anim_start_blended_with_flags(object, 2, 0, 3, 0);
            PlayMobySound(1, 0, object);
        }
    } else if (B(object, 32) == 4) {
        if (math_fast_float_d(vars + 16)) {
            B(object, 32) = 5;
            I(vars, 20) = 0;
            I(vars, 16) = 30;
            anim_start_blended_with_flags(object, 3, 0, 3, 0);
        } else if (!I(vars, 20)) {
            qcopy(v, g_hero_state.object + 0xc0);
            vec_scale_to_length(v, v, 1.0f);
            FastVecAdd(out, base, v);
            spark_effect_spawn(out, 1, object);
            I(vars, 20) = 1;
        }
    } else if (B(object, 32) == 5) {
        if (math_fast_float_d(vars + 8)) {
            B(object, 32) = 3;
            I(vars, 8) = 64;
            anim_start_blended_with_flags(object, 4, 0, 3, 0);
        } else {
            func_002E6EF8(gfx_draw_screen_flash_fade, object);
        }
    } else if (B(object, 32) == 3) {
        int done = 0;

        qcopy(v, D_L00_001B8FF0);
        hits.timer = (int *)(vars + 4);
        mem_fast_helper_b(list, 128);
        ReleaseDeadOrExpiredSlots(object);
        SelectBestTargetInCone(object + 16, v, &hits.count, list, 32, 0, 3.1415929794311523f, 1.047197699546814f, 40.0f, 0.0f,
                      0.0f, 0, 0);
        for (i = 0; i < hits.count; i++) {
            char *p;
            int active;

            qcopy_nc(out, list[i] + 16);
            p = moby_get_private_value_0(list[i]);
            active = 1;
            if (p) {
                F(out, 8) += F(p, 16) * 1.5f;
                if (F(p, 0) > 100.0f) {
                    active = 0;
                }
            }
            if (list[i] && B(list[i], 32) != 254 && B(list[i], 32) != 253) {
                if (*(short *)(list[i] + 0xaa) == 0xa8d /* Swamp Monster I Arm */) {
                    B(list[i], 0x95) = 9;
                }
                if (*(short *)(list[i] + 0xaa) == 0xa8e /* Swamp Monster I Eye */) {
                    B(list[i], 0x95) = 7;
                }
                if (*(short *)(list[i] + 0xaa) == 0x1002 /* Desert Dune Monster */) {
                    B(list[i], 32) = 7;
                }
            }
            if (active) {
                if ((p && B(p, 14) == 1) || B(p, 14) == 2) {
                    spark_effect_spawn(out, 0, 0);
                    I(vars, 28)++;
                    SetDeathBits(list[i], 0, 3);
                    B(p, 14) = 2;
                } else if (p && B(p, 14) != 3) {
                    spark_effect_spawn(out, 0, 0);
                    I(vars, 28)++;
                    SetDeathBits(list[i], 0, 3);
                    func_00310440(list[i]);
                }
            } else {
                F(p, 0) -= 20.0f;
                if (F(p, 0) < 0.0f) {
                    F(p, 0) = 0.0f;
                }
            }
        }
        done = math_fast_float_d(hits.timer);
        if (done) {
            if (I(vars, 28)) {
                PlayMobySound(2, 0, object);
            } else {
                PlayMobySound(3, 0, object);
            }
            I(vars, 28) = 0;
            B(object, 32) = 0;
            weapon_spend_ammo(-1, 1);
        }
    }
}
