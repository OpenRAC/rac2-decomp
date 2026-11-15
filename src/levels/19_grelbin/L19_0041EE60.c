#include "common.h"

extern u16 *D_L19_001FB5A0[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern char D_0019B4A8[];

extern void moby_mark_spawned(u8 *);

extern struct { u8 header[0x464]; u8 entries[0]; } D_L19_0021EA30;
extern s32 g_active_yeti_count __attribute__((sda));
extern s32 g_max_active_yetis __attribute__((sda));

extern s32 moby_is_in_selected_zone(void *);
extern float coll_probe_ground_height_below(void *, s32, f32);
extern float math_random_float_range(f32, f32);
extern s32 weapon_select_aim_target(u8 *, s32, f32, f32, s32, s32);
extern void part_spawn_masked_debris(u8 *, s32, void *, s32, f32, f32, f32, f32);
extern s32 PlayMobySound(s32, s32, u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 math_fast_float_d(void *);

#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = D_L19_001FB5A0[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L19_001B2A38[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L19_001FB5A0[GROUP(off)]); \
         p++)

/* Controls a group of Y.E.T.I.s kept at this spot. It lets them out one at a time while fewer than the allowed number are active. */
void yeti_group_spawner_update(u8 *moby)
{
    u8 *state;
    s32 savedCount;

    if (moby_is_in_selected_zone(moby + 0x10) == 0)
        return;
    state = *(u8 **)(moby + 0x68);
    if (GROUP(0x120) == -1 ||
        (moby[0xB0] != 0xFF &&
         (D_L19_0021EA30.entries[(s16)*(u16 *)(moby + 0xB2)] != 0 ||
          ((savedCount = *(u8 *)(D_0019B4A8 + (((s16) * (u16 *)(moby + 0xB2) >> 1) + (g_current_map_index << 10)))),
           (*(u16 *)(moby + 0xB2) & 1) ? ((savedCount >> 4) & 7) != 0 : (savedCount & 7) != 0)))) {
        moby_mark_spawned(moby);
        return;
    }
    switch (moby[0x20]) {
    case 0: {
        u16 *p;
        u8 *otherMoby;
        u8 *otherVars;
        f32 groundHeight;

        groundHeight = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        groundHeight -= math_random_float_range(0.1f, 0.3f);
        *(s16 *)(moby + 0x7C) = 0x1F;
        *(s32 *)(moby + 0x48) = 0;
        *(f32 *)(moby + 0x18) = groundHeight;
        FOR_EACH_ID(p, 0x120) {
            otherMoby = g_moby_l19_array[0] + ((*p & 0x7FFF) << 8);
            if (otherMoby == 0)
                break;
            if (*(s16 *)(otherMoby + 0xAA) == 0x10D0 /* Y.E.T.I. */) {
                otherVars = *(u8 **)(otherMoby + 0x68);
                *(f32 *)(otherVars + 0x22C) = *(f32 *)(state + 0x128) + 10.0f;
                *(s32 *)(otherVars + 0x26C) = 1;
                *(s32 *)(otherVars + 0x274) = 1;
            }
        }
        moby_set_state(moby, 1, -1);
        break;
    }
    case 1: {
        u8 *otherMoby;
        f32 burstVec[4];
        s32 gone;

        weapon_select_aim_target(moby, -1, *(f32 *)(state + 0x128), *(f32 *)(state + 0x128), 0, 0);
        gone = 0;
        if (GROUP(0x138) == -1) {
            gone = 1;
        } else {
            otherMoby = g_moby_l19_array[0] + (GROUP(0x138) << 8);
            if (otherMoby == 0 || otherMoby[0x20] == 0xFE || otherMoby[0x20] == 0xFD)
                gone = 1;
        }
        if (GROUP(0x64) == 1 && gone) {
            qzero(burstVec);
            burstVec[2] = 0.15f;
            *(s16 *)(moby + 0x7C) = 0;
            part_spawn_masked_debris(moby, 0x1F, burstVec, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            PlayMobySound(0, 0, moby);
            moby_set_state(moby, 3, -1);
        }
        break;
    }
    case 3: {
        u16 *p;
        u8 *otherMoby;
        u8 *otherVars;
        s32 found = 0;

        FOR_EACH_ID(p, 0x120) {
            otherMoby = g_moby_l19_array[0] + ((*p & 0x7FFF) << 8);
            if (otherMoby == 0)
                break;
            if (*(s16 *)(otherMoby + 0xAA) == 0x10D0 /* Y.E.T.I. */) {
                otherVars = *(u8 **)(otherMoby + 0x68);
                if (*(s32 *)(otherVars + 0x26C) == 1) {
                    qcopy(otherMoby + 0x10, moby + 0x10);
                    qcopy(otherVars + 0x210, moby + 0x10);
                    *(f32 *)(otherMoby + 0x18) = coll_probe_ground_height_below(otherMoby + 0x10, 0, 1.0f);
                    found = 1;
                    *(s32 *)(otherVars + 0x26C) = 0;
                    *(u16 *)(otherMoby + 0x34) &= 0xFF7F;
                    break;
                }
            }
        }
        if (!found) {
            moby_set_state(moby, 4, -1);
        } else {
            GROUP(0x13C) = 200;
            moby_set_state(moby, 2, -1);
        }
        break;
    }
    case 2: {
        u16 *p;
        u8 *otherMoby;
        u8 *otherVars;
        s32 idleCount;

        weapon_select_aim_target(moby, -1, *(f32 *)(state + 0x128) + 10.0f, *(f32 *)(state + 0x128), 0, 0);
        if (GROUP(0x64) == 1) {
            idleCount = 0;
            FOR_EACH_ID(p, 0x120) {
                otherMoby = g_moby_l19_array[0] + ((*p & 0x7FFF) << 8);
                if (otherMoby == 0)
                    break;
                if (*(s16 *)(otherMoby + 0xAA) == 0x10D0 /* Y.E.T.I. */) {
                    otherVars = *(u8 **)(otherMoby + 0x68);
                    if (*(s32 *)(otherVars + 0x26C) == 0) {
                        if (otherMoby[0x20] != 0xFE) {
                            if (otherMoby[0x20] != 0xFD)
                                idleCount++;
                        }
                    }
                }
            }
            if (g_active_yeti_count < g_max_active_yetis) {
                if (idleCount < 3) {
                    if (math_fast_float_d(state + 0x13C))
                        moby_set_state(moby, 3, -1);
                }
            }
        }
        break;
    }
    }
}
