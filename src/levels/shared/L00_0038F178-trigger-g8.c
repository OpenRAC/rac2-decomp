#include "common.h"
extern int g_frame_l00_counter;
extern unsigned char D_0018C0D4 NOT_SDA;
extern u32 D_0018C0BC NOT_SDA;
extern int D_0018C0B4 NOT_SDA;
extern int g_current_map_index;
extern unsigned char D_0019B2E8[], D_0019B4A8[];
typedef struct { char pad[0x464]; u8 disabled[1]; } TriggerTable;
extern TriggerTable D_L00_0021D140, D_L00_0021DDB0;
extern float g_hero_position[4];
extern char *D_L00_001AF440 __attribute__((sda));
extern void cam_reset_entry(int arg0);
extern int math_fast_float_d(int *), IsPointInCuboid(void *, int);
extern void moby_mark_table_entry_flagged(unsigned int);
extern float coll_probe_ground_height_below(void *, int, float), math_fabs(float);
extern void level_capture_checkpoint_state(void *, void *), value_set_entry_by_index(int, int);
/* Applies a regional activation trigger and records its checkpoint flags. */
void checkpoint_trigger_update(char *actor) {
    int *state = *(int **)(actor + 0x68);
    unsigned long long flags;
    unsigned short id;
    unsigned char *packed;
    int bits;
    int active;
    float point[4];
    if (*(u8 *)(actor + 0x30) < 0x20) *(u8 *)(actor + 0x30) = 0x20;
    if (g_frame_l00_counter == 0 && state[5] != -1) cam_reset_entry(state[5]);
    {
        int currentFlags = state[2];
        int disabled = currentFlags & 8;
        flags = currentFlags;
        if (disabled) return;
    }
    if (*(u8 *)(actor + 0xBC) == 0) {
        *(u8 *)(actor + 0xBC) = 1;
        state[7] = 0;
        state[8] = 0;
        return;
    }
    if (state[6] != -1 && !(D_0019B2E8[state[6] + g_current_map_index * 16] & 0x80)) return;
    if ((flags & 2) && D_0018C0D4 != 1) return;
    if ((flags & 4) && D_0018C0D4 != 3 && D_0018C0D4 != 0) return;
    if ((flags & 16) && D_0018C0BC > 1 && D_0018C0BC != 9) return;
    if ((flags & 32) && D_0018C0B4 == 49) return;
    if (state[3] == 2 && math_fast_float_d(state + 8)) state[3] = 0;
    active = IsPointInCuboid(g_hero_position, state[0]);
    if (active) goto activate;
    {
        unsigned short triggerId = *(u16 *)(actor + 0xB2);
        if (D_L00_0021DDB0.disabled[(short)triggerId]) goto activate;
        bits = D_0019B4A8[((short)triggerId >> 1) + g_current_map_index * 0x400];
        if (triggerId & 1) {
            if ((bits >> 4) & 7) goto activate;
            goto inactive;
        }
        if (!(bits & 7)) goto inactive;
    }
activate:
    {
        if (state[3] && (state[4] == 0 || state[8] != 0)) goto finish;
        state[3] = 1;
        moby_mark_table_entry_flagged(*(u8 *)(actor + 0xB0));
        qcopy(point, (actor + 0x10));
        point[2] = coll_probe_ground_height_below(point, 0, 0.5f);
        if (math_fabs(*(float *)(actor + 0x18) - point[2]) > 2.0f) point[2] = *(float *)(actor + 0x18);
        level_capture_checkpoint_state(point, actor + 0xF0);
        D_L00_0021D140.disabled[*(short *)(actor + 0xB2)] = 0;
        D_L00_0021DDB0.disabled[*(short *)(actor + 0xB2)] = 0;
        id = *(u16 *)(actor + 0xB2);
        {
            int index = (short)id >> 1;
            index += g_current_map_index * 0x400;
            packed = D_0019B4A8 + index;
        }
        bits = *packed;
        {
            int value = bits & 0xF8;
            if (id & 1) value = bits & 0x8F;
            *packed = value;
        }
        if (state[9] && D_L00_001AF440 != actor) {
            value_set_entry_by_index(0x2F36, 90);
            D_L00_001AF440 = actor;
        }
        state[8] = 900;
        goto finish;
    }
inactive:
    if (state[3]) state[3] = 2;
finish:
    if (*(u8 *)(actor + 0x20) == 0 && (D_0019B2E8[*(u8 *)(actor + 0xB0) + g_current_map_index * 16] & 0x80)) *(u8 *)(actor + 0x20) = 1;
}
