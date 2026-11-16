#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int TI_F41eb487e __attribute__((mode(TI)));
extern char D_00189E20_5[];
extern void hero_update_lean_reference_pal(void);
extern void hero_rotate_matrix(float, float, float);
extern float math_approach_with_velocity(float *position, float target, float *velocity,
                          float acceleration, float damping, float limit, int direction);

/* Eases the hero's lean back toward upright in most states, or runs the full lean update in modes 1 and 2. */
void hero_ease_lean_to_upright_pal(void)
{
    char *base = (char *)&D_00189E20_5;
    TI_F41eb487e v;
    int mode;
    int x;

    mode = *(u8 *)(base + 0x22C3);
    if (*(short *)(base + 0x218) != 0)
        mode = 1;

    if (mode == 0) {
        x = *(int *)(base + 0x2294);
        if ((u32)(x - 0x24) < 2)
            return;
        if (*(int *)(base + 0x229C) == 0x11 || *(int *)(base + 0x229C) == 0x15 ||
            *(int *)(base + 0x229C) == 0x16 || *(int *)(base + 0x229C) == 0x1F)
            return;
        if (x == 0x74 || x == 0x30 || x == 0x2C || x == 0x2B)
            return;
        v = *(TI_F41eb487e *)(base + 0x90);
        math_approach_with_velocity((float *)&v, 0.0f, (float *)(base + 0xA0), 0.0216f, 0.43200004f, 0.10471977f, 0);
        math_approach_with_velocity((float *)&v + 1, 0.0f, (float *)(base + 0xA4), 0.0216f, 0.43200004f, 0.10471977f, 0);
        hero_rotate_matrix(*(float *)(base + 0xA0), *(float *)(base + 0xA4), 0.0f);
        return;
    }
    if (mode < 0)
        return;
    if (mode >= 3)
        return;
    hero_update_lean_reference_pal();
}
