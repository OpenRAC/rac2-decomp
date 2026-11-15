#include "include_asm.h"
#include "names.h"


typedef struct {
    char pad0[0x7C];
    char *owner;
    char pad80[0x88 - 0x80];
    int busy;
} Sub_411F48;
typedef struct {
    char pad0[0x30];
    Sub_411F48 sub;
    char pad[0xD0 - 0x30 - sizeof(Sub_411F48)];
} Ent_411F48;
extern Ent_411F48 ref_L00_00411F48_00[];
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);
extern void func_PAL_L00_004170B0(char *object, char *state);

void func_PAL_L00_00416DC8(char *a0)
{
    Ent_411F48 *e;
    int i;

    for (i = 0; i < 0x30; i++) {
        e = &ref_L00_00411F48_00[i];
        if (e->sub.owner == a0) {
            func_PAL_L00_004170B0(a0, (char *)e);
            if (e->sub.busy == 0) {
                gfx_draw_billboard_quad(&e->sub, 0x31, (math_random_int_range(0x50, 0x60) << 24) | 0x103080, 1, 0.5f, 0.1f, math_random_angle());
                gfx_draw_billboard_quad(&e->sub, 0x31, (math_random_int_range(0x50, 0x60) << 24) | 0xFFFFFF, 1, 0.5f, 0.1f, math_random_angle());
            }
        }
    }
}

