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

/* Sets up a new Lancer-class (or similar) object: clears its state, picks its sound table and sets the turn rates. */
void lancer_init(char *object)
{
    char *state = *(char **)(object + 0x68);
    int local[4];
    int value, i;
    int index;
    int *table;
    int kind;
    float range;
    *(short *)(state + 4) = -1;
    *(float *)(state + 12) = 0.1f;
    *(int *)(state + 0) = 0;
    *(short *)(state + 6) = 0;
    *(short *)(state + 16) = 0;
    *(int *)(state + 8) = 0;
    *(int *)(state + 36) = -1;
    *(int *)(state + 40) = 0;
    *(int *)(state + 44) = 0;
    *(int *)(state + 48) = 0;
    *(int *)(state + 60) = -1;
    if (*(short *)(object + 0xAA) == MOBY_CLASS_LANCER)
        *(int *)(state + 52) = g_lancer_state_int;
    else
        *(int *)(state + 52) = g_other_weapon_state_int;
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
    if (kind == MOBY_CLASS_LANCER) {
        range = 20.0f;
        g_lancer_range = range;
    } else {
        ref_L00_003A7AF0_00 = range;
    }
    g_lancer_vertical_arc = 0.104719766f;
}
