#include "include_asm.h"
#include "names.h"


/* func_PAL_L12_00418BD8, the PAL copy of func_L12_00413CE0: the same C, with the value
   stored in f2E0 scaled to 50 Hz. A unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

extern u16 *g_moby_l12_group_lists[];

/* The path-follower state of an entity: the record fields the nearest-entity hand-over touches. */
typedef struct {
    u8 pad00[0x2B0];
    s32 f2B0;
    s32 f2B4;
    s32 f2B8;
    s32 f2BC;
    s32 f2C0;
    u8 pad2C4[0x2D0 - 0x2C4];
    s32 f2D0;
    s32 f2D4;
    u8 pad2D8[0x2DC - 0x2D8];
    s32 f2DC;
    u16 f2E0;
    u8 pad2E2[0x2EA - 0x2E2];
    u8 f2EA;
    u8 pad2EB[0x302 - 0x2EB];
    u8 f302;
    u8 f303;
} PathState;

extern u8 *D_L12_001B2E9C_base[3] __asm__("D_L12_001B2E9C") __attribute__((sda));

extern s32 g_moby_l12_group_count;

extern s32 g_guard_cooldown_max __attribute__((sda));

extern u8 *g_path_zone_table[];

extern f32 vec_distance_xy(void *a, void *b);

/* Hands the object's path state to the nearest eligible entity of its group. */
void path_hand_state_to_nearest_pal(u8 *moby)
{
    PathState *state = *(PathState **)(moby + 0x68);
    u8 *nearest;
    f32 nearest_dist;
    f32 vec[4];
    u16 *list_entry;
    u8 *other;
    PathState *other_state;
    f32 dist;

    if (state->f2C0 != -1) {
        *(TI128 *)vec = *(TI128 *)(g_path_zone_table[state->f2C0] + 0x10);
        nearest = 0;
        nearest_dist = 100000.0f;
        for (list_entry = g_moby_l12_group_lists[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= g_moby_l12_group_count && list_entry != 0 &&
             ((list_entry != 0 && (s16)list_entry[-1] >= 0) || list_entry == g_moby_l12_group_lists[moby[0x21]]);
             list_entry++) {
            other = D_L12_001B2E9C_base[0] + ((*list_entry & 0x7FFF) << 8);
            if (other == 0)
                break;
            other_state = *(PathState **)(other + 0x68);
            dist = vec_distance_xy(other + 0x10, vec);
            if (other_state != 0 && (other_state->f302 & 1)) {
                if (dist < nearest_dist) {
                    nearest_dist = dist;
                    nearest = other;
                }
            }
        }
        if (nearest != 0) {
            PathState *dest_state = *(PathState **)(nearest + 0x68);

            dest_state->f2B0 = state->f2B0;
            dest_state->f2B4 = state->f2B4;
            dest_state->f2B8 = state->f2B8;
            dest_state->f2BC = state->f2BC;
            dest_state->f2C0 = state->f2C0;
            dest_state->f2D0 = state->f2D0;
            dest_state->f2D4 = state->f2D4;
            dest_state->f2E0 = ((s32)g_guard_cooldown_max * 5 + 2) / 6;
            dest_state->f2DC = state->f2C0;
            dest_state->f2EA = 1;
            dest_state->f302 = 2;
            dest_state->f303 = state->f303;
        }
    }
}
