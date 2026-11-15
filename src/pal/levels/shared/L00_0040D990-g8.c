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

extern void func_PAL_L00_0040DF78(char *);
extern void ref_L00_00408E58_00(int, int);
extern void anim_start_blended_with_flags(char *, int, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_helper_b(void *);
extern void mem_fast_helper_b(void *, int);
extern int math_fast_float_d(void *);
extern int get_ammo(int);
extern void func_PAL_L00_002AF458(void);
extern int slot_copy_records_to_free(void *);
extern void PlayMobySound(int, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern char *func_PAL_L00_0041C0E0(void *, int, char *);
extern void func_002E6EF8(void (*)(char *), char *);
extern void gfx_draw_screen_flash_fade(char *);
extern void ReleaseDeadOrExpiredSlots(char *);
extern void SelectBestTargetInCone(void *, void *, int *, void *, int, int, float, float, float, float, float, int, int);
extern char *moby_get_private_value_0(char *);
extern void func_PAL_002A7650(char *, int, int);
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

void func_PAL_L00_0040D990(char *o)
{
    char *q = *(char **)(o + 104);
    int base[4] __attribute__((aligned(16)));
    int v[4] __attribute__((aligned(16)));
    int out[4] __attribute__((aligned(16)));
    char *list[32];
    struct {
        int count;
        int *timer;
    } hits;
    int i;

    func_PAL_L00_0040DF78(o);
    if (g_hero_state.state == 1) {
        ref_L00_00408E58_00(29, 1);
    }
    if (B(o, 0x31)) {
        D_L00_0025C64C = 0.1f;
    }
    if (B(o, 0x42) == B(o, 0x43) && (B(o, 0x60) & 2)) {
        anim_start_blended_with_flags(o, 1, 0, 2, 0);
    }
    FastVecAdd(base, base, o + 16);
    vec_fast_helper_b(q);
    if (B(o, 32) == 1) {
        if (D_L00_001A8F00 || g_hero_state.disabled || !(D_00138324 & g_hero_state.mask) || g_hero_state.level < 19) {
            return;
        }
        if (get_ammo(-1)) {
            func_PAL_L00_002AF458();
            I(q, 24) = slot_copy_records_to_free(D_L00_0029FBE0);
            B(o, 32) = 2;
            I(q, 4) = (((int)(D_L00_001B0F90) * 5 + 2) / 6);
        } else {
            PlayMobySound(4, 0, o);
        }
        {
            RateEntry *entry = &g_weapon_l00_table[D_00139593];
            F(q, 0) = 1.0f / entry->rate;
        }
    } else if (B(o, 32) == 2) {
        if (math_fast_float_d(q + 16)) {
            B(o, 32) = 4;
            I(q, 16) = 25;
            I(q, 20) = 0;
        }
        if (I(q, 16) == 8) {
            anim_start_blended_with_flags(o, 2, 0, 2, 0);
            PlayMobySound(1, 0, o);
        }
    } else if (B(o, 32) == 4) {
        if (math_fast_float_d(q + 16)) {
            B(o, 32) = 5;
            I(q, 20) = 0;
            I(q, 16) = 25;
            anim_start_blended_with_flags(o, 3, 0, 2, 0);
        } else if (!I(q, 20)) {
            qcopy(v, g_hero_state.object + 0xc0);
            vec_scale_to_length(v, v, 1.0f);
            FastVecAdd(out, base, v);
            func_PAL_L00_0041C0E0(out, 1, o);
            I(q, 20) = 1;
        }
    } else if (B(o, 32) == 5) {
        if (math_fast_float_d(q + 8)) {
            B(o, 32) = 3;
            I(q, 8) = 53;
            anim_start_blended_with_flags(o, 4, 0, 2, 0);
        } else {
            func_002E6EF8(gfx_draw_screen_flash_fade, o);
        }
    } else if (B(o, 32) == 3) {
        int done = 0;

        qcopy(v, D_L00_001B8FF0);
        hits.timer = (int *)(q + 4);
        mem_fast_helper_b(list, 128);
        ReleaseDeadOrExpiredSlots(o);
        SelectBestTargetInCone(o + 16, v, &hits.count, list, 32, 0, 3.1415929794311523f, 1.047197699546814f, 40.0f, 0.0f,
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
                if ((p && B(p, 14) == 1) || B(p, 14) == 2) {
                    func_PAL_L00_0041C0E0(out, 0, 0);
                    I(q, 28)++;
                    func_PAL_002A7650(list[i], 0, 3);
                    B(p, 14) = 2;
                } else if (p && B(p, 14) != 3) {
                    func_PAL_L00_0041C0E0(out, 0, 0);
                    I(q, 28)++;
                    func_PAL_002A7650(list[i], 0, 3);
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
            if (I(q, 28)) {
                PlayMobySound(2, 0, o);
            } else {
                PlayMobySound(3, 0, o);
            }
            I(q, 28) = 0;
            B(o, 32) = 0;
            weapon_spend_ammo(-1, 1);
        }
    }
}
