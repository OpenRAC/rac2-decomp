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
extern void func_31B920(), func_32F140(), func_32AA20(), func_31B568();
extern void func_313E40(), func_368958(), func_324168(), func_31C988();
extern void func_2BEE78(), func_2B8510(), func_311758(), func_313378();
extern void func_2F5158(), func_371D60(), func_371D70();
extern void clank_scene_finish(), console_remote_view_cleanup(), object_restore_linked_after_scene();
extern char *func_3113F0();
extern int func_321988(), func_2F5010(), func_32AB10();
extern float func_2F0000(float, float), func_2EF5C0(float);
extern int func_2F01A0(int, int, float);

#define I(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(unsigned short *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

/* Per-frame update of moby class 2568: a switch that plays a Clank scene, spawns Clank and tracks which scene stage the hero has seen. */
void clank_scene_switch_update(char *moby)
{
    char *vars = P(moby, 0x68);
    int state = B(moby, 0x20);

    switch (state) {
    case 0: {
        char *spawned;

        B(moby, 0x30) = 255;
        if (!(B(D_0019B2E8, B(moby, 0xB0) + (g_current_map_index << 4)) & 128)) {
            if (g_hero_state.mode == 1) {
                func_31B920(moby, 2, -1);
                func_32F140(I(vars, 0x20), -1);
            } else {
                func_31B920(moby, 1, -1);
                {
                    char *existing = D_L03_001B2A1C + (I(vars, 0) << 8);
                    I(existing, 0x98) = 0;
                    H(existing, 0x34) = (H(existing, 0x34) | 0x41) & ~0x1000;
                }
                spawned = func_3113F0(MOBY_CLASS_CLANK);
                func_32AA20(spawned, moby);
                qcopy_nc(spawned + 0x10, D_L03_001B2B0C[I(vars, 4)].position);
                qcopy_nc(spawned + 0xF0, D_L03_001B2B0C[I(vars, 4)].rotation);
                H(spawned, 0x32) = 0x30;
                H(spawned, 0x34) |= 2;
                func_31B568(spawned, 0x13, 0);
                I(spawned, 0x98) = 0;
                qcopy_nc(spawned + 0x10, D_L03_001B0650);
                F(spawned, 0xF4) = D_L03_001B0664;
                F(spawned, 0xF8) = D_L03_001B0668;
                func_313E40(spawned);
                P(vars, 0x2C) = spawned;
                if (D_001395B8.first) {
                    func_368958();
                    func_324168(I(vars, 0x18), I(vars, 0x1C));
                }
            }
            func_31C988(I(vars, 0xC), 1);
            g_hero_state.flag = 1;
        } else {
            if (!D_001395B8.seen) {
                func_368958();
                func_2BEE78(moby + 0x10, moby + 0xF0, 0, 1);
            }
            if (g_hero_state.mode == 1) {
                func_32F140(I(vars, 0x24), -1);
                func_2B8510(0);
                func_311758(D_L03_001B2A1C + (I(vars, 0) << 8));
                func_313378(B(moby, 0xB0));
                func_2BEE78(moby + 0x10, moby + 0xF0, 0, 1);
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
            func_31C988(I(vars, 8), 1);
            func_31C988(I(vars, 0xC), 0);
            func_311758(moby);
        }
        return;
    }
    case 1:
        if (!D_001395B8.first
            && func_321988(g_hero_state.position, I(vars, 4))
            && func_2F5010(D_L03_001BFB80, 0x31)) {
            func_2F5158(D_L03_001BFB80);
            func_371D60(object_restore_linked_after_scene, moby);
            D_001395B8.first = state;
        }
        if (D_L03_001A8F00 != 2) {
            {
                u32 timer = H(P(vars, 0x2C), 0x96);
                u32 old = timer++;
                H(P(vars, 0x2C), 0x96) = timer;
                if (old >= 4) {
                    H(P(vars, 0x2C), 0x34) &= ~0x41;
                    H(P(vars, 0x2C), 0x34) |= 0x1000;
                    I(P(vars, 0x2C), 0x98) = I(P(P(vars, 0x2C), 0x24), 0x10);
                }
            }
        } else {
            H(P(vars, 0x2C), 0x34) |= 0x41;
            H(P(vars, 0x2C), 0x34) &= ~0x1000;
            I(P(vars, 0x2C), 0x98) = 0;
        }
        if (func_32AB10(moby)) {
            H(P(vars, 0x2C), 0x34) |= 0x41;
            H(P(vars, 0x2C), 0x34) &= ~0x1000;
            I(P(vars, 0x2C), 0x98) = 0;
            if (D_001395B8.second)
                clank_scene_finish(moby);
            else if (func_2F5010(D_L03_001BFB80, 0x32)) {
                func_2F5158(D_L03_001BFB80);
                func_371D60(clank_scene_finish, moby);
            }
            func_371D70();
            func_31B920(moby, 2, -1);
            return;
        } else if (g_hero_state.mode == 1) {
            char *spawned;

            func_32F140(I(vars, 0x20), -1);
            spawned = D_L03_001B2A1C + (I(vars, 0) << 8);
            H(spawned, 0x34) = (H(spawned, 0x34) & ~0x41) | 0x1000;
            I(spawned, 0x98) = I(P(spawned, 0x24), 0x10);
            H(P(vars, 0x2C), 0x34) |= 0x41;
            H(P(vars, 0x2C), 0x34) &= ~0x1000;
            I(P(vars, 0x2C), 0x98) = 0;
            func_31B920(moby, 2, -1);
            return;
        }
        return;
    case 2:
        if (g_hero_state.object == moby && g_hero_state.active) {
            func_31C988(I(vars, 8), 1);
            func_31C988(I(vars, 0xC), 0);
            if (func_2F5010(D_L03_001BFB80, 0x33)) {
                func_2F5158(D_L03_001BFB80);
                func_371D60(console_remote_view_cleanup, moby);
                func_31B920(moby, 3, -1);
            }
            return;
        }
        break;
    default:
        return;
    }
    {
        F(vars, 0x30) = func_2F0000(F(vars, 0x30), 0.10762865096330643f);
        state = func_2F01A0(0x808C8C8C, 0x80282828,
            func_2EF5C0(F(vars, 0x30)) * 0.5f + 0.5f);
        I(moby, 0x78) = func_2F01A0(I(moby, 0x78), state, 0.15f);
    }
}
