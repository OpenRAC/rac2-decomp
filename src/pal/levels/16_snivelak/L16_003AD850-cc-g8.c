#include "names.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char g_hero_state[];

#include "include_asm.h"
extern char *g_moby_instance_table;

extern char g_sound_state[];
extern int g_beam_active_flag __attribute__((sda));
extern int g_beam_done_flag __attribute__((sda));
extern int g_beam_age_limit __attribute__((sda));
extern int g_beam_blocked_flag __attribute__((sda));
extern int IsPointInCuboid(void *, int);
extern void snd_stop_voice(int);
extern int moby_count_group_not_in_state(int, int);
extern void func_PAL_L16_003ADB58(void *);
extern int FastDecTimer(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void streak_effect_update(void *);
extern void gfx_draw_electric_beam(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);

static __inline__ void clear_link(char *state)
{
    int owner = **(int **)(state + 1640);
    int index;
    char *record;
    if (owner != 0) {
        index = **(int **)(state + 1636);
        if (index != -1) {
            record = g_sound_state + index * 112;
            if (*(int *)(record + 136) == owner && *(unsigned char *)(record + 116))
                snd_stop_voice(index);
        }
        **(int **)(state + 1636) = -1;
    }
}

/* func_PAL_L16_003AD850, the PAL copy of func_L16_003AA108: the same C, with the 50 Hz scale on the two timers. */
/* Advances the object's timed activation states and maintains its linked effect. */
void func_PAL_L16_003AD850(char *object)
{
    char *state = *(char **)(object + 104);
    char *target;
    int index;
    char *record;
    if (*(unsigned char *)(object + 32) != 0) {
        if (*(unsigned char *)(object + 32) == 1) {
            target = g_moby_instance_table + *(int *)(state + 1576) * 256;
            if (target == 0 || *(unsigned char *)(target + 32) == 254 || *(unsigned char *)(target + 32) == 253) {
                if (IsPointInCuboid((&((Hero *)g_hero_state)->c[128]), *(int *)(state + 1632))) {
                    clear_link(state);
                    *(unsigned char *)(object + 32) = 2;
                    goto active;
                }
            }
        } else if (moby_count_group_not_in_state(*(int *)(state + 1580), -1)) {
            goto active;
        }
        clear_link(state);
        return;
    }
active:
    if (g_beam_active_flag)
        return;
    switch (*(unsigned char *)(object + 32)) {
    case 0:
        func_PAL_L16_003ADB58(object);
        *(short *)(state + 16) = (*(int *)(state + 12) * 5 + 2) / 6;
        *(unsigned char *)(object + 32) = 1;
        *(float *)(state + 1572) = 2.5f;
        *(short *)(state + 8) = 1;
        *(short *)(state + 10) = 1;
        **(int **)(state + 1636) = -1;
        break;
    case 1:
        break;
    case 2:
        if (FastDecTimer(state + 16)) {
            *(unsigned char *)(object + 32) = 3;
            *(short *)(state + 16) = 100;
        }
        break;
    case 3:
        if (**(int **)(state + 1640) == 0 ||
            (index = **(int **)(state + 1636), record = g_sound_state + index * 112,
             *(int *)(record + 136) != **(int **)(state + 1640)) ||
            *(unsigned char *)(record + 116) == 0) {
            **(int **)(state + 1636) = snd_play_from_class_bank(0, 4, object, 4347);
            **(char ***)(state + 1640) = object;
        }
        if (FastDecTimer(state + 16)) {
            if (*(short *)(state + 6))
                *(unsigned char *)(object + 32) = 2;
            *(short *)(state + 16) = 0;
        } else if (*(short *)(state + 18) == 0) {
            func_PAL_L16_003ADB58(object);
        }
        break;
    }
    if (*(short *)(state + 18)) {
        if (g_beam_done_flag == 0)
            streak_effect_update(object);
        if (g_beam_age_limit < *(short *)(state + 18) && g_beam_blocked_flag == 0)
            gfx_add_draw_callback_third(gfx_draw_electric_beam, object);
    }
}
