#include "include_asm.h"

#include "common.h"
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern char g_hero_state[];
extern char *D_L19_001B1EAC __attribute__((sda));
extern float D_L19_001B1E94 __attribute__((sda));
extern float D_L19_001B1E98 __attribute__((sda));
extern float D_L19_001B1E9C __attribute__((sda));
extern float D_L19_001B1EA4 __attribute__((sda));
extern float D_L19_001B1EA8 __attribute__((sda));
extern int D_L19_001B258C;
extern char D_L19_001B9A40[];
extern int IsPointInCuboid(char *, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(float *, float *, char *);
extern char *func_PAL_L00_002D7850(int);
extern void cam_end_override(char *);
extern void FastVecSub(char *, float *, char *);

/* Per-frame update of the carried-object marker: arms it, tracks a linked flag, and while the hero is in state 0x31 places and sizes the marker from the grabbed object's bounds. */
void func_PAL_L19_004281A8(char *obj) {
    float a[4];
    float b[4];
    char *hero_ptr;

    int *link = FLD(obj, int *, 0x68);

    switch (FLD(obj, u8, 0x20)) {
    case 0:
        D_L19_001B1EAC = 0;
        FLD(obj, u8, 0x20) = 1;
        FLD(obj, u8, 0x30) = 0xFF;
        return;
    case 1:
        if (link[0] != -1) {
            if (IsPointInCuboid(D_L19_001B9A40, link[0]) != 0) {
                D_L19_001B258C = 2;
            } else if (D_L19_001B258C == 2) {
                D_L19_001B258C = 0;
            }
        }
        break;
    default:
        return;
    }
    if (FLD(g_hero_state, int, 0x2294) == 0x31 && (hero_ptr = FLD(g_hero_state, char *, 0x1830)) != 0) {
        vec_build_spherical_offset(a, D_L19_001B1E94, FLD(hero_ptr, float, 0xF8), -FLD(hero_ptr, float, 0xF4) * 0.5f);
        FastVecAdd(b, a, FLD(g_hero_state, char *, 0x1830) + 0x10);
        if (D_L19_001B1EAC == 0) {
            D_L19_001B1EAC = func_PAL_L00_002D7850(5);
            if (D_L19_001B1EAC == 0) {
                return;
            }
        }
        if (FLD(FLD(g_hero_state, char *, 0x1830), s16, 0xAA) == 0x905) {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E98;
            FLD(D_L19_001B1EAC, float, 0xC) = -1.0f;
            FLD(D_L19_001B1EAC, float, 8) = -1.0f;
        } else {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E9C;
            FLD(D_L19_001B1EAC, float, 0xC) = D_L19_001B1EA4;
            FLD(D_L19_001B1EAC, float, 8) = D_L19_001B1EA8;
        }
        FLD(D_L19_001B1EAC, u8, 0x1F) = 1;
        FastVecSub(D_L19_001B1EAC + 0x20, b, D_L19_001B9A40);
        return;
    }
    if (D_L19_001B1EAC != 0) {
        cam_end_override(D_L19_001B1EAC);
        D_L19_001B1EAC = 0;
    }
}

extern int D_L19_001A8F00 __attribute__((sda));
extern u8 D_001A7BDC[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern char *D_L19_001B2B0C[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern char g_hero_position[];
extern char D_L19_001BFC40[];
extern void moby_reset_matching_effects(char *a0);
extern void moby_mark_spawned(char *a0);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_reset_vars_defaults(char *a0);
extern s32 IsPointInCuboid(char *a0, s32 a1);
extern s32 req_push_queue(char *a0, s32 a1);
extern void level_apply_index_for_key(char *a0);
extern s32 req_launch_queued(char *a0);
extern s32 game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(s32 a0);
extern void func_PAL_002AFC10(s32 a0);
extern void func_PAL_L00_002B9CD8(char *a0, char *a1, s32 a2, s32 a3);
extern void moby_mark_table_entry_flagged(s32 a0);
extern void level_capture_checkpoint_state(char *a0, char *a1);
extern int MemcardSave(s32 a0, s32 a1);

void func_PAL_L19_00429220(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    u8 id;

    moby_reset_matching_effects(a0);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        if (D_001A7BDC[0] != 0) {
            moby_mark_spawned(a0);
        } else {
            moby_set_state(a0, 1, -1);
            moby_reset_vars_defaults(a0);
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(s1 + 0x120)) != 0) {
            if (req_push_queue(D_L19_001BFC40, 0x96) != 0) {
                req_push_queue(D_L19_001BFC40, 0x14);
                req_push_queue(D_L19_001BFC40, 0x97);
                level_apply_index_for_key(a0);
                req_launch_queued(D_L19_001BFC40);
                moby_set_state(a0, 2, -1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            *(u8 *)(a0 + 0x31) = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (game_is_either_mode_two() == 0) {
            D_L19_001B2724[1] = 0;
            moby_mark_flag_and_append_to_list(0x14);
            func_PAL_002AFC10(0x14);
            func_PAL_L00_002B9CD8(D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x30,
                        D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(u8 *)(a0 + 0x31) = 1;
            if (*(u8 *)(a0 + 0xB0) != 0xFF) {
                id = *(u8 *)(a0 + 0xB0);
                if ((D_0019B2E8[id + (g_current_map_index[0] << 4)] & 0x80) == 0)
                    moby_mark_table_entry_flagged(id);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                MemcardSave(0, -1);
            } else {
                MemcardSave(0, -1);
            }
            moby_mark_spawned(a0);
        }
        break;
    }
}
