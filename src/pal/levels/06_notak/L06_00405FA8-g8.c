#include "include_asm.h"
#include "common.h"
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int,
                               int, int, int);
extern void moby_compute_local_point(char *, float *, float, float, float);
extern void part_emit_rings(char *);
extern void moby_mark_spawned(void *);
extern float D_L06_001B0020 __attribute__((sda));
extern float D_L06_001B0028 __attribute__((sda));
extern float D_L06_001B0030 __attribute__((sda));
extern int D_L06_001B0050 __attribute__((sda));

/* a moby's three states: idle, hit, and gone */
void func_PAL_L06_004061B8(char *a0)
{
    char *s0 = a0;
    char *s1;
    float buf[4];

    s1 = *(char **)(s0 + 0x68);

    switch (*(unsigned char *)(s0 + 0x20)) {
    case 0:
        if (*(int *)(s1 + 4) != 0)
            *(unsigned short *)(s0 + 0x34) |= 0x8000;
        moby_set_state(s0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(s0, 0x4010000, 0) != 0) {
            if (*(int *)s1 == 0)
                moby_set_state(s0, 2, -1);
        }
        *(unsigned char *)(s0 + 0xA8) = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces(s0, &D_L06_001B0030, &D_L06_001B0028, &D_L06_001B0020,
                          0xFFFF, 0, D_L06_001B0050, 6, 0xFFFF, 0xFF, 0);
        moby_compute_local_point(s0, buf, 1.0f, 1.0f, 3.0f);
        part_emit_rings(s0);
        moby_mark_spawned(s0);
        break;
    }
}
