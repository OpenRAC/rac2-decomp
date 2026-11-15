#include "include_asm.h"
#include "names.h"
extern int D_L18_001A79F0;
extern int D_L18_001A8F00;
extern void protopet_init(void *);
extern void protopet_check_hit_target(void *);
extern void protopet_run_state_machine(void *);
extern void enemy_update_move_by_type(void *);
extern void protopet_update_step(void *);

void func_PAL_L18_003F9170(char *a0)
{
    char *s0 = a0;
    unsigned char v;

    if (D_L18_001A79F0 == 0x13) {
        if (D_L18_001A8F00 == 2) {
            *(int *)(s0 + 0x98) = 0;
            *(unsigned short *)(s0 + 0x34) = (*(unsigned short *)(s0 + 0x34) | 0x41) & 0xEFFF;
        } else {
            char *p = *(char **)(s0 + 0x24);

            *(unsigned short *)(s0 + 0x34) = (*(unsigned short *)(s0 + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(s0 + 0x98) = *(int *)(p + 0x10);
        }
    }
    v = *(unsigned char *)(s0 + 0x20);
    if (v == 0) {
        protopet_init(s0);
    } else if (v != 1 && v != 0x13) {
        protopet_check_hit_target(s0);
        protopet_run_state_machine(s0);
        enemy_update_move_by_type(s0);
        protopet_update_step(s0);
    }
}
