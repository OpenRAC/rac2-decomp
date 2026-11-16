#include "common.h"
typedef int Quad0792 __attribute__((mode(TI)));
typedef struct Ctl_003A47E8 { int f0, f4, f8, fC; } Ctl_003A47E8;
extern int g_space_ship_max_health[] MACRO_ADDR;
extern Ctl_003A47E8 *g_space_ship_pickup_slots[] MACRO_ADDR;
extern char *g_pickup_slot_table[3][60];
extern float g_planet_radius __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern float gravity_get_center_distance(void *);

/* Looks for the nearest spawned pickup that the ship needs and is close enough. Copies its position to the output and returns 1 if found. */
int pickup_find_nearest_needed(char *obj, Quad0792 *out) {
    int count = g_space_ship_max_health[0];
    Ctl_003A47E8 *ctl = g_space_ship_pickup_slots[0];
    int flags = 0, found = 0, i, bit;
    float best;
    char *state = *(char **)(obj + 0x68);
    if (ctl->f8 <= 2) flags |= 2;
    if (ctl->fC <= 0) flags |= 2;
    if (*(float *)(state + 0x20) < (float)(count - count / 6)) flags |= 1;
    best = 30.0f;
    for (bit = 1, i = 0; i < 3; i++, bit <<= 1) {
        if (flags & bit) {
            int n;
            char **slot = g_pickup_slot_table[i];
            for (n = 49; n >= 0; n--, slot++) {
                if (*slot) {
                    float dist = fast_vec_dist(*slot + 0x10, obj + 0x10);
                    if (dist < best && gravity_get_center_distance(*slot + 0x10) - g_planet_radius < 3.0f) {
                        qcopy_nc(out, *slot + 0x10);
                        best = dist;
                        found = 1;
                    }
                }
            }
        }
    }
    return found;
}
