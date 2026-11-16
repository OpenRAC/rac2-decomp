#include "include_asm.h"
#include "names.h"

/* Small-data file: these bodies reach their globals through $gp / the
 * one-instruction model, so they only reproduce at -G8. */

extern unsigned char g_flying_enemy_spawn_blocked[] __attribute__((sda));
extern int *g_space_ship_pickup_slots[4] __attribute__((sda));
extern int g_space_ship_owner_moby __attribute__((sda));

extern void ref_L22_003A1E50_00(char *, char *);
extern void ref_L22_003A1E50_01(void *);
extern void ref_L22_003A3C70_00(void *, int, int, int);

void moby_update_timed(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    unsigned short *ageCounter;
    ref_L22_003A1E50_00(moby, vars + 0x50);
    ageCounter = (unsigned short *)(moby + 0x96);
    if (*ageCounter <= 0xFFFE) (*ageCounter)++;
    if (*(int *)(vars + 0x37C) != 0) *(int *)(vars + 0x37C) = *(int *)(vars + 0x37C) - 1;
    ref_L22_003A1E50_01(vars + 0x464);
    ref_L22_003A1E50_01(g_flying_enemy_spawn_blocked);
}

/* Counts down a timer in the first entry of a small table until it reaches zero. */
void table_decrement_timer(void) {
    int *p = g_space_ship_pickup_slots[0];
    if (p[3] > 0) p[3] = p[3] - 1;
}

/* Forwards two values, with a fixed zero, to a helper on the stored object. */
void stored_object_forward(int a0, int a1) {
    ref_L22_003A3C70_00(g_space_ship_owner_moby, a0, a1, 0);
}

/* ---- 0x003A48F8 / 0x003A4C68: the same scan of the small-data table at
 * $gp+0x3C0, bounded by the count at 0x001B2AD4 (absolute, hence `nosda`).
 * No guard in the source: retail's leading `blez` is the loop's own entry
 * test, which is what splits the count between $v0 (the load) and $a2 (the
 * loop's bound copy). ---- */

extern int g_space_ship_lane_count __attribute__((nosda));
extern int g_lane_slot_list[1] __attribute__((sda));

/* Returns 0 when the key is in the list, 1 when it is not. */
int list_is_key_missing(int key) {
    int i;
    for (i = 0; i < g_space_ship_lane_count; i++) {
        if (g_lane_slot_list[i] == key) return 0;
    }
    return 1;
}

/* The same scan, looking for the second argument and reporting the opposite
 * way. */
int list_has_key(int unused, int key) {
    int i;
    for (i = 0; i < g_space_ship_lane_count; i++) {
        if (g_lane_slot_list[i] == key) return 1;
    }
    return 0;
}

/* ---- 0x003A45F0: the orbit's own update. ---- */

/* The six level words the update reads: the same addresses in every program
 * that carries the function, so they keep their level-22 names. */
extern float g_orbit_param_a __attribute__((sda));
extern float g_orbit_param_b __attribute__((sda));
extern float g_orbit_param_c __attribute__((sda));
extern float g_orbit_param_d __attribute__((sda));
extern float g_orbit_param_e __attribute__((sda));
extern float g_orbit_param_f __attribute__((sda));

/* The two boot helpers the update calls; each sits at its own address in
 * every program that carries the function. */
extern void ref_L22_003A45F0_00(void *, float, float, float, float); /* func_002B60B0 */
extern void ref_L22_003A45F0_01(void *, int, int, int);               /* func_002A7470 */

/* One turn of the orbit: the first flag bit runs the object's own update, the
 * second one hands the result over to the child object. */
void orbit_update(char *moby, int newState, int stateArg1, int stateArg2, int flags, float defaultScale) {
    char *obj = moby;
    char *vars = *(char **)(moby + 0x68);
    char *child;
    float scale;
    float p0;
    float p1;
    float p2;
    float p3;
    float g0;
    float g1;

    if (flags & 1) {
        if (*(short *)(vars + 0x34E) == 0) {
            *(int *)(vars + 0x3EC) = *(unsigned char *)(obj + 0x43);
            if (newState == 11) {
                p0 = g_orbit_param_c * 0.00027777778f;
                p1 = g_orbit_param_d * 0.016666668f;
                p2 = g_orbit_param_e * 4.8481374e-06f;
                p3 = g_orbit_param_f * 0.00029088825f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.5f;
                *(float *)(vars + 0x138) = 0.5f;
            } else {
                p0 = g_orbit_param_a * 0.00027777778f;
                p1 = g_orbit_param_b * 0.016666668f;
                p2 = g_orbit_param_e * 4.8481374e-06f;
                p3 = g_orbit_param_f * 0.00029088825f;
                ref_L22_003A45F0_00(obj, p0, p1, p2, p3);
                *(float *)(obj + 0x48) = 1.3f;
                *(float *)(vars + 0x138) = 0.33333334f;
            }

            g0 = *(float *)(vars + 0x128);
            g1 = *(float *)(vars + 0x134);
            g0 = g0 + g0;
            g1 = g1 * 8.0f;
            *(float *)(vars + 0x128) = g0;
            *(float *)(vars + 0x134) = g1;
            if (*(unsigned char *)(obj + 0x43) != newState) {
                ref_L22_003A45F0_01(obj, newState, stateArg1, stateArg2);
            }
        }
    }
    if (*(short *)(vars + 0x34C) != 0) {
        return;
    }
    if (*(unsigned char *)(obj + 0x43) < 11 || *(unsigned char *)(obj + 0x43) > 12) {
        *(float *)(obj + 0x48) = defaultScale;
    }
    scale = *(float *)(obj + 0x48);
    *(float *)(*(char **)(vars + 0x440) + 0x48) = scale;
    if (flags & 2) {
        child = *(char **)(vars + 0x440);
        if (child != 0) {
            ref_L22_003A45F0_01(child, newState, stateArg1, stateArg2);
        }
    }
}

/* ---- 0x003A3B50: spawn one object of a random kind. ---- */

typedef struct Hero3B50 {
    unsigned char pad[0x43];
    unsigned char state;
} Hero3B50;

/* In .data, so that -G8 keeps the split lui/lw the entry block allocates around. */
extern Hero3B50 *g_hero_moby __attribute__((section(".data")));
extern int g_pickup_slot_table[3][60];
/* The target object: the same $gp slot in both levels, under a name each level binds itself. */
extern int ref_L22_003A3B50_00 __attribute__((sda));
extern int math_random_int_below(int);
extern int pickup_spawn_in_free_slot(char *, char *, int, int);

/* Picks a kind at random (one of two when the hero's or the target's state says so), scans that
 * kind's row of 50 slots and spawns the object at POS. */
void SpawnRandomKindAt(char *pos, int arg) {
    int kindCount;
    int mode = 0;
    int i;
    int *row;

    kindCount = 3;
    if (g_hero_moby->state == 6 || ((Hero3B50 *)ref_L22_003A3B50_00)->state == 4) kindCount = 2;
    switch (math_random_int_below(kindCount)) {
    case 0:
        mode = 1;
        break;
    case 1:
        mode = 2;
        break;
    case 2:
        mode = 0;
        break;
    }
    row = g_pickup_slot_table[mode];
    i = 0;
    if (*row != 0) {
        int *slot = row;
        do {
            i++;
            if (i > 0x31) break;
            slot++;
            if (*slot == 0) break;
        } while (i != 0x31);
    }
    pickup_spawn_in_free_slot((char *)ref_L22_003A3B50_00, pos, mode, arg);
}
