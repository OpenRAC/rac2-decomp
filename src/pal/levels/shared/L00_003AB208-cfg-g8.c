#include "names.h"
/* func_PAL_L00_003AB208, the PAL copy of func_L00_003A7AF0: the same C, where 0.1f becomes 0.4166667f and both arms scale for 50 Hz. */
#include "common.h"
extern float g_lancer_horizontal_arc __attribute__((section(".data")));
extern float g_lancer_range __attribute__((section(".data")));
extern float g_lancer_vertical_arc __attribute__((section(".data")));
extern float ref_L00_003A7AF0_00 __attribute__((sda));
extern int g_lancer_state_int __attribute__((sda));
extern int g_other_weapon_state_int __attribute__((sda));
extern int AcquireEntitySlot(char *, int, void *);
extern char *level_get_slot_body(int, int);
extern char *mem_round_up_to_16(int);

/* Sets up a lancer shot: timers, colour, an entity slot with 16 sample buffers and the aim arcs (PAL: 50 Hz timings). */
void lancer_init_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    int local[4];
    int value, i;
    int index;
    int *table;
    int kind;
    float range;
    *(short *)(state + 4) = -1;
    *(float *)(state + 12) = 0.4166667f;
    *(int *)(state + 0) = 0;
    *(short *)(state + 6) = 0;
    *(short *)(state + 16) = 0;
    *(int *)(state + 8) = 0;
    *(int *)(state + 36) = -1;
    *(int *)(state + 40) = 0;
    *(int *)(state + 44) = 0;
    *(int *)(state + 48) = 0;
    *(int *)(state + 60) = -1;
    if (*(short *)(object + 0xAA) == 1490)
        *(int *)(state + 52) = ((s32)(g_lancer_state_int) * 5 + 2) / 6;
    else
        *(int *)(state + 52) = ((s32)(g_other_weapon_state_int) * 5 + 2) / 6;
    *(unsigned int *)(object + 0x78) = 0xFF0020FF;
    index = AcquireEntitySlot(object, 0, local);
    *(short *)(state + 18) = index;
    if (local[0] == 0) {
        table = (int *)level_get_slot_body(*(short *)(object + 0xAA), (short)index);
        value = mem_round_up_to_16((int)(table + 16));
        for (i = 0; i < 16; i++) {
            table[i] = value;
            value += 640;
        }
    }
    kind = *(short *)(object + 0xAA);
    g_lancer_horizontal_arc = 0.104719766f;
    range = 30.0f;
    if (kind == 1490) {
        range = 20.0f;
        g_lancer_range = range;
    } else {
        ref_L00_003A7AF0_00 = range;
    }
    g_lancer_vertical_arc = 0.104719766f;
}
