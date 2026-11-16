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
extern void lightning_bolt_build_jittered_pal(char *object, char *state);

/* Redraws each lightning arc owned by this object and adds glow sprites while the arc is idle. */
void lightning_arcs_update_owned_pal(char *moby)
{
    Ent_411F48 *entry;
    int i;

    for (i = 0; i < 0x30; i++) {
        entry = &ref_L00_00411F48_00[i];
        if (entry->sub.owner == moby) {
            lightning_bolt_build_jittered_pal(moby, (char *)entry);
            if (entry->sub.busy == 0) {
                gfx_draw_billboard_quad(&entry->sub, 0x31, (math_random_int_range(0x50, 0x60) << 24) | 0x103080, 1, 0.5f, 0.1f, math_random_angle());
                gfx_draw_billboard_quad(&entry->sub, 0x31, (math_random_int_range(0x50, 0x60) << 24) | 0xFFFFFF, 1, 0.5f, 0.1f, math_random_angle());
            }
        }
    }
}

