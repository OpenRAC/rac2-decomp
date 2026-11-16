#include "include_asm.h"

#include "common.h"
extern u16 *g_group_ptr_table[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 g_max_l19_group_index[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern char g_moby_nibble_table[];
extern void moby_mark_spawned(u8 *);
extern struct { u8 header[0x464]; u8 entries[0]; } g_trigger_active_table;
extern s32 g_active_yeti_count __attribute__((sda));
extern s32 g_max_active_yetis __attribute__((sda));
extern s32 moby_is_in_selected_zone(void *);
extern float coll_probe_ground_height_below(void *, s32, f32);
extern float math_random_float_range(f32, f32);
extern s32 weapon_select_aim_target(u8 *, s32, f32, f32, s32, s32);
extern void func_PAL_002B15D8(u8 *, s32, void *, s32, f32, f32, f32, f32);
extern s32 PlayMobySound(s32, s32, u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 math_fast_float_d(void *);
#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = D_L19_001FB5A0[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L19_001B2A38[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L19_001FB5A0[GROUP(off)]); \
         p++)

void func_PAL_L19_0042451C(u8 *object)
{
    u8 *state;
    s32 c;

    if (moby_is_in_selected_zone(object + 0x10) == 0)
        return;
    state = *(u8 **)(object + 0x68);
    if (GROUP(0x120) == -1 ||
        (object[0xB0] != 0xFF &&
         (g_trigger_active_table.entries[(s16)*(u16 *)(object + 0xB2)] != 0 ||
          ((c = *(u8 *)(g_moby_nibble_table + (((s16) * (u16 *)(object + 0xB2) >> 1) + (g_current_map_index << 10)))),
           (*(u16 *)(object + 0xB2) & 1) ? ((c >> 4) & 7) != 0 : (c & 7) != 0)))) {
        moby_mark_spawned(object);
        return;
    }
    switch (object[0x20]) {
    case 0: {
        u16 *p;
        u8 *e;
        u8 *s;
        f32 x;

        x = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        x -= math_random_float_range(0.1f, 0.3f);
        *(s16 *)(object + 0x7C) = 0x1F;
        *(s32 *)(object + 0x48) = 0;
        *(f32 *)(object + 0x18) = x;
        FOR_EACH_ID(p, 0x120) {
            e = g_moby_l19_array[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(s16 *)(e + 0xAA) == 0x10D0) {
                s = *(u8 **)(e + 0x68);
                *(f32 *)(s + 0x22C) = *(f32 *)(state + 0x128) + 10.0f;
                *(s32 *)(s + 0x26C) = 1;
                *(s32 *)(s + 0x274) = 1;
            }
        }
        moby_set_state(object, 1, -1);
        break;
    }
    case 1: {
        u8 *e;
        f32 vec[4];
        s32 gone;

        weapon_select_aim_target(object, -1, *(f32 *)(state + 0x128), *(f32 *)(state + 0x128), 0, 0);
        gone = 0;
        if (GROUP(0x138) == -1) {
            gone = 1;
        } else {
            e = g_moby_l19_array[0] + (GROUP(0x138) << 8);
            if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD)
                gone = 1;
        }
        if (GROUP(0x64) == 1 && gone) {
            qzero(vec);
            vec[2] = 0.18f;
            *(s16 *)(object + 0x7C) = 0;
            func_PAL_002B15D8(object, 0x1F, vec, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            PlayMobySound(0, 0, object);
            moby_set_state(object, 3, -1);
        }
        break;
    }
    case 3: {
        u16 *p;
        u8 *e;
        u8 *s;
        s32 found = 0;

        FOR_EACH_ID(p, 0x120) {
            e = g_moby_l19_array[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(s16 *)(e + 0xAA) == 0x10D0) {
                s = *(u8 **)(e + 0x68);
                if (*(s32 *)(s + 0x26C) == 1) {
                    qcopy(e + 0x10, object + 0x10);
                    qcopy(s + 0x210, object + 0x10);
                    *(f32 *)(e + 0x18) = coll_probe_ground_height_below(e + 0x10, 0, 1.0f);
                    found = 1;
                    *(s32 *)(s + 0x26C) = 0;
                    *(u16 *)(e + 0x34) &= 0xFF7F;
                    break;
                }
            }
        }
        if (!found) {
            moby_set_state(object, 4, -1);
        } else {
            GROUP(0x13C) = 167;
            moby_set_state(object, 2, -1);
        }
        break;
    }
    case 2: {
        u16 *p;
        u8 *e;
        u8 *s;
        s32 n;

        weapon_select_aim_target(object, -1, *(f32 *)(state + 0x128) + 10.0f, *(f32 *)(state + 0x128), 0, 0);
        if (GROUP(0x64) == 1) {
            n = 0;
            FOR_EACH_ID(p, 0x120) {
                e = g_moby_l19_array[0] + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(s16 *)(e + 0xAA) == 0x10D0) {
                    s = *(u8 **)(e + 0x68);
                    if (*(s32 *)(s + 0x26C) == 0) {
                        if (e[0x20] != 0xFE) {
                            if (e[0x20] != 0xFD)
                                n++;
                        }
                    }
                }
            }
            if (g_active_yeti_count < g_max_active_yetis) {
                if (n < 3) {
                    if (math_fast_float_d(state + 0x13C))
                        moby_set_state(object, 3, -1);
                }
            }
        }
        break;
    }
    }
}
