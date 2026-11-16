#include "common.h"

extern void gfx_convert_float_pair_bias_coords(void *, int *, int *, int);
extern char *moby_get_private_value_0(u8 *);
extern int subtract_integer_with_clamp(int);
extern float IntToFloat(int);
extern float fast_vec_dist(void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern u8 *g_target_l05_list[];
typedef struct { int object_class, screen_range; float world_range; } TargetRule;
extern TargetRule g_lock_target_rules[];
extern float D_L05_001B1B1C_gp SDATA(D_L05_001B1B1C);
extern float D_L05_001B1B18_gp SDATA(D_L05_001B1B18);
extern int g_current_map_index[] __attribute__((sda));
extern float g_origin_vec[];
extern int g_feltzin_mission_index[] __attribute__((sda));

static __inline__ int target_class(u8 *object)
{
    if (object && *(u8 **)(object + 0x24))
        return *(s16 *)(*(u8 **)(object + 0x24) + 0x46);
    return 0;
}

/* Grid outputs are four separate 32-bit words. The rule table has real 12-byte
 * rows terminated by class -1; neither rule nor object-list extent is invented.
 * The parameter accessor returns a 32-bit target address, matching its C def. */
/* Finds the next enemy the ship can lock onto, one close enough and in clear view. Returns it, or zero if there is none. */
u8 *ship_find_lock_target(void *position, u8 **excluded, u8 *current)
{
    int source_x, source_y, target_x, target_y;
    int i, kind, range;
    float dx, dy, distance;
    u8 **cursor, *object, *parameters;
    int level_id;
    int n, j;

    gfx_convert_float_pair_bias_coords(position, &source_x, &source_y, 0);
    cursor = g_target_l05_list;
    while ((object = *cursor) != 0) {
        if (!object[0x31])
            goto next;
        parameters = (u8 *)moby_get_private_value_0(object);
        if (!parameters || *(float *)parameters <= 0.0f)
            goto next;
        kind = target_class(object);
        if (kind != 5 && kind != 15)
            goto next;
        if (excluded) {
            for (n = 0; excluded[n] && object != excluded[n]; n++) {}
            if (excluded[n])
                goto next;
        }
        gfx_convert_float_pair_bias_coords(object + 0x10, &target_x, &target_y, 0);
        dx = IntToFloat(subtract_integer_with_clamp(target_x - source_x));
        dy = IntToFloat(subtract_integer_with_clamp(target_y - source_y));
        do {
            range = 40;
            i = 0;
scan1:
            if (g_lock_target_rules[i].object_class == -1)
                goto scan1_done;
            if (*(s16 *)(object + 0xAA) == g_lock_target_rules[i].object_class) {
                range = g_lock_target_rules[i].screen_range;
                break;
            }
            i++;
            goto scan1;
        } while (0);
scan1_done:
        if (!(dx < D_L05_001B1B1C_gp + (float)range) || !(dy < D_L05_001B1B1C_gp + (float)range))
            goto next;
        distance = D_L05_001B1B18_gp;
        do {
            j = 0;
            level_id = g_current_map_index[0];
scan2:
            if (g_lock_target_rules[j].object_class == -1)
                goto scan2_done;
            if (g_lock_target_rules[j].object_class == *(s16 *)(object + 0xAA)) {
                distance = g_lock_target_rules[j].world_range;
                break;
            }
            j++;
            goto scan2;
        } while (0);
scan2_done:
        if (level_id != 20 && distance < fast_vec_dist(g_origin_vec, object + 0x10))
            goto next;
        if (current && current == object && g_feltzin_mission_index[0] % 3 != 0)
            return object;
        if (!CollLine(g_origin_vec, object + 0x10, 16, object, 0))
            return object;
next:
        cursor++;
    }
    return 0;
}
