#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x80];
    char position[0x10];
    char pad90[0x33C - 0x90];
    char *object;
    int active;
    char pad344[0x22B4 - 0x344];
    unsigned char mode;
    char pad22B5[0x24FC - 0x22B5];
    unsigned short flag;
} EndakoPlayerState;
typedef struct {
    char pad0[6];
    unsigned char first;
    unsigned char second;
    char pad8[0xA2 - 8];
    unsigned char seen;
} EndakoFlags;
typedef struct {
    char pad0[0x30];
    char position[0x10];
    char pad40[0x30];
    char rotation[0x10];
} EndakoPlacement;
extern EndakoPlayerState g_hero_state;
extern EndakoFlags D_001395B8;
extern char D_0019B2E8[];
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern int g_current_map_index, D_L03_001A8F00;
extern char *D_L03_001B2A1C;
extern EndakoPlacement *D_L03_001B2B0C;
extern char D_L03_001BFB80[];
extern char D_L03_001B0650[] SDATA(D_L03_001B0650);
extern float D_L03_001B0664, D_L03_001B0668;
extern void moby_set_state(), script_queue_keyed_request(), moby_init_child_from_parent(), anim_start_immediate();
extern void func_002A0F48(), state_set_flag_one(), func_PAL_L02_003294D8(), moby_set_group_enabled();
extern void func_PAL_L00_002B9CD8(), hero_reset_carried_objects(), moby_mark_spawned(), moby_mark_table_entry_flagged();
extern void game_set_stored_value_pair(), func_PAL_002F6C18();
extern s32 req_launch_queued();
extern void func_PAL_L03_003D61B8(), func_PAL_L03_003D6298(), func_PAL_L03_003D6150();
extern char *CreateMoby();
extern int IsPointInCuboid(), req_push_queue(), flag_is_third_pending_set();
extern float FastAddRotations(float, float), math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
#define I(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(unsigned short *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

void func_PAL_L03_003D5B68(char *obj)
{
    char *v = P(obj, 0x68);
    int state = B(obj, 0x20);

    switch (state) {
    case 0: {
        char *p;

        B(obj, 0x30) = 255;
        if (!(B(D_0019B2E8, B(obj, 0xB0) + (g_current_map_index << 4)) & 128)) {
            if (g_hero_state.mode == 1) {
                moby_set_state(obj, 2, -1);
                script_queue_keyed_request(I(v, 0x20), -1);
            } else {
                moby_set_state(obj, 1, -1);
                {
                    char *existing = D_L03_001B2A1C + (I(v, 0) << 8);
                    I(existing, 0x98) = 0;
                    H(existing, 0x34) = (H(existing, 0x34) | 0x41) & ~0x1000;
                }
                p = CreateMoby(0x57);
                moby_init_child_from_parent(p, obj);
                qcopy_nc(p + 0x10, D_L03_001B2B0C[I(v, 4)].position);
                qcopy_nc(p + 0xF0, D_L03_001B2B0C[I(v, 4)].rotation);
                H(p, 0x32) = 0x30;
                H(p, 0x34) |= 2;
                anim_start_immediate(p, 0x13, 0);
                I(p, 0x98) = 0;
                qcopy_nc(p + 0x10, D_L03_001B0650);
                F(p, 0xF4) = D_L03_001B0664;
                F(p, 0xF8) = D_L03_001B0668;
                func_002A0F48(p);
                P(v, 0x2C) = p;
                if (D_001395B8.first) {
                    state_set_flag_one();
                    func_PAL_L02_003294D8(I(v, 0x18), I(v, 0x1C));
                }
            }
            moby_set_group_enabled(I(v, 0xC), 1);
            g_hero_state.flag = 1;
        } else {
            if (!D_001395B8.seen) {
                state_set_flag_one();
                func_PAL_L00_002B9CD8(obj + 0x10, obj + 0xF0, 0, 1);
            }
            if (g_hero_state.mode == 1) {
                script_queue_keyed_request(I(v, 0x24), -1);
                hero_reset_carried_objects(0);
                moby_mark_spawned(D_L03_001B2A1C + (I(v, 0) << 8));
                moby_mark_table_entry_flagged(B(obj, 0xB0));
                func_PAL_L00_002B9CD8(obj + 0x10, obj + 0xF0, 0, 1);
            }
            /* Resident flag bytes, 8 bytes further on in USA v2.00. A symbol-plus-offset
               .sdata address is neither split nor a one-insn operand, so each store stays
               retail's lui $at/sb macro (see L00_002CAB08.c). */
            g_item_owned_flags[2] = 1;
            g_item_owned_flags[0x3A] = 1;
            g_item_owned_flags[3] = 1;
            g_item_owned_flags[0x3B] = 1;
            g_item_owned_flags[4] = 1;
            g_item_owned_flags[0x3C] = 1;
            g_hero_state.flag = 0;
            moby_set_group_enabled(I(v, 8), 1);
            moby_set_group_enabled(I(v, 0xC), 0);
            moby_mark_spawned(obj);
        }
        return;
    }
    case 1:
        if (!D_001395B8.first
            && IsPointInCuboid(g_hero_state.position, I(v, 4))
            && req_push_queue(D_L03_001BFB80, 0x31)) {
            req_launch_queued(D_L03_001BFB80);
            game_set_stored_value_pair(func_PAL_L03_003D6150, obj);
            D_001395B8.first = state;
        }
        if (D_L03_001A8F00 != 2) {
            {
                u32 timer = H(P(v, 0x2C), 0x96);
                u32 old = timer++;
                H(P(v, 0x2C), 0x96) = timer;
                if (old >= 4) {
                    H(P(v, 0x2C), 0x34) &= ~0x41;
                    H(P(v, 0x2C), 0x34) |= 0x1000;
                    I(P(v, 0x2C), 0x98) = I(P(P(v, 0x2C), 0x24), 0x10);
                }
            }
        } else {
            H(P(v, 0x2C), 0x34) |= 0x41;
            H(P(v, 0x2C), 0x34) &= ~0x1000;
            I(P(v, 0x2C), 0x98) = 0;
        }
        if (flag_is_third_pending_set(obj)) {
            H(P(v, 0x2C), 0x34) |= 0x41;
            H(P(v, 0x2C), 0x34) &= ~0x1000;
            I(P(v, 0x2C), 0x98) = 0;
            if (D_001395B8.second)
                func_PAL_L03_003D61B8(obj);
            else if (req_push_queue(D_L03_001BFB80, 0x32)) {
                req_launch_queued(D_L03_001BFB80);
                game_set_stored_value_pair(func_PAL_L03_003D61B8, obj);
            }
            func_PAL_002F6C18();
            moby_set_state(obj, 2, -1);
            return;
        } else if (g_hero_state.mode == 1) {
            char *p;

            script_queue_keyed_request(I(v, 0x20), -1);
            p = D_L03_001B2A1C + (I(v, 0) << 8);
            H(p, 0x34) = (H(p, 0x34) & ~0x41) | 0x1000;
            I(p, 0x98) = I(P(p, 0x24), 0x10);
            H(P(v, 0x2C), 0x34) |= 0x41;
            H(P(v, 0x2C), 0x34) &= ~0x1000;
            I(P(v, 0x2C), 0x98) = 0;
            moby_set_state(obj, 2, -1);
            return;
        }
        return;
    case 2:
        if (g_hero_state.object == obj && g_hero_state.active) {
            moby_set_group_enabled(I(v, 8), 1);
            moby_set_group_enabled(I(v, 0xC), 0);
            if (req_push_queue(D_L03_001BFB80, 0x33)) {
                req_launch_queued(D_L03_001BFB80);
                game_set_stored_value_pair(func_PAL_L03_003D6298, obj);
                moby_set_state(obj, 3, -1);
            }
            return;
        }
        break;
    default:
        return;
    }
    {
        F(v, 0x30) = FastAddRotations(F(v, 0x30), 0.12915438f);
        state = FastTweenColor(0x808C8C8C, 0x80282828,
            math_fast_sin_or_cos_b(F(v, 0x30)) * 0.5f + 0.5f);
        I(obj, 0x78) = FastTweenColor(I(obj, 0x78), state, 0.18f);
    }
}
