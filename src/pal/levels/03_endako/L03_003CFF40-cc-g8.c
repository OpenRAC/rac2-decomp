#include "names.h"
/* func_PAL_L03_003CFF40, the PAL copy of func_L03_003CBE58: the same C, where scale D_L03_001B0438; wrap D_L03_001B0438 (((int)({e}) * 5 + 2) / 6); lit 1.6964601f becomes 2.035752f. */

#include "common.h"

extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
/* case 0 makes the object opaque and moves it to state 1; case 1 scrolls the three
   offsets in its vars by the table's rates per frame (wrapping below -1) and queues
   its draw callback with the object as argument (AddDrawCallback in rac1-decomp) */
/* spawns the actor and seeds its aim from the caller's vector */
/* func_L03_003D18F8 is defined in L03_003D18F8-g8.c. */

/* The object the level's state points at: the retail writes six floats, a run
   of bytes and shorts, and two counters into it. */
typedef struct {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u8  b18;
    u8  b19;
    u16 h1A;
    u16 pad1C;
    u8  b1E;
    u8  b1F;
    u8  pad20[0x10];
    u16 h30;
    u16 h32;
    s32 i34;
} L03_003D21F8_Obj;

/* The object pointer is small data (the retail reaches it through $gp in
   ordinary flow, not only in a delay slot), the state word is not: the retail
   reads it with an absolute lui/%lo pair and clears it from a delay slot. */
extern L03_003D21F8_Obj *g_camera_override_slot __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(char *a0, char *a1, char *a2);
extern void matrix_from_basis_rows(char *a0, char *a1);
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern void snd_stop_voice(s32 a0);
extern void moby_set_state_in_list(int a0, int a1);
extern u8  *g_moby_record_base;
extern u8   g_sound_state[];
extern s32  g_ant_bridge_divisor __attribute__((sda));
extern f32  g_ant_bridge_angle_limit __attribute__((sda));

/* The actor's per-frame update: state 0 spawns it and aims, state 2 looks the
   target up, states 3 and 4 turn it by a rate that decays; every other state
   does nothing.  The actor's angle is at 0xF4, its rate at 0x74 of the state. */
void ant_bridge_update_pal(char *moby)
{
    char *obj = moby;
    char *vars = *(char **)(obj + 0x68);
    char buf[0x40];
    char *offset_ptr;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (*(s32 *)(vars + 0x70) != -1) {
            moby_set_state(obj, 2, -1);
            offset_ptr = vars + 0x60;
            FastVecSub(offset_ptr, g_moby_record_base + *(s32 *)(vars + 0x70) * 0x100 + 0x10, obj + 0x10);
            *(s32 *)(vars + 0x7C) = -1;
            *(s32 *)(vars + 0x78) = 0;
            matrix_from_basis_rows(buf, obj + 0xC0);
            matrix_mul_vec3(offset_ptr, offset_ptr, buf);
        } else {
            moby_set_state(obj, 1, -1);
        }
        break;
    case 2: {
        char *slot;

        if (flag_is_third_pending_set(g_moby_record_base + *(s32 *)(vars + 0x70) * 0x100) == 0) {
            break;
        }
        slot = g_sound_state + *(s32 *)(vars + 0x7C) * 0x70;
        if (*(char **)(slot + 0x88) != obj || *(u8 *)(slot + 0x74) == 0) {
            *(s32 *)(vars + 0x7C) = PlayMobySound(0, 4, obj);
        }
        moby_set_state_in_list(*(u8 *)(obj + 0x21), 4);
        moby_set_state(obj, 3, -1);
        break;
    }
    case 3: {
        char *slot;
        char *target_pos;
        f32 angle;
        f32 rate;

        *(f32 *)(vars + 0x74) = *(f32 *)(vars + 0x74)
            + (*(f32 *)(obj + 0xF4) / (f32)(((int)(g_ant_bridge_divisor) * 5 + 2) / 6) + 0.00013962637f);
        angle = *(f32 *)(obj + 0xF4) + *(f32 *)(vars + 0x74);
        *(f32 *)(obj + 0xF4) = angle;
        if (1.69646013f < angle) {
            if (*(s32 *)(vars + 0x78) < 5) {
                if (*(s32 *)(vars + 0x7C) != -1) {
                    slot = g_sound_state + *(s32 *)(vars + 0x7C) * 0x70;
                    if (*(char **)(slot + 0x88) == obj && *(u8 *)(slot + 0x74) != 0) {
                        snd_stop_voice(*(s32 *)(vars + 0x7C));
                    }
                }
                *(s32 *)(vars + 0x7C) = -1;
                PlayMobySound(1, 0, obj);
                (*(s32 *)(vars + 0x78))++;
            }
            *(f32 *)(obj + 0xF4) = 1.69646013f;
            rate = *(f32 *)(vars + 0x74);
            if (0.0006981318f < rate) {
                *(f32 *)(vars + 0x74) = rate * -0.5f;
            } else {
                *(s32 *)(vars + 0x74) = 0;    /* the retail stores the word, not the float */
                moby_set_state(obj, 5, -1);
            }
        }
        target_pos = g_moby_record_base + *(s32 *)(vars + 0x70) * 0x100 + 0x10;
        matrix_mul_vec3(target_pos, vars + 0x60, obj + 0xC0);
        FastVecAdd(target_pos, target_pos, obj + 0x10);
        break;
    }
    case 4: {
        f32 angle_limit;
        f32 angle;
        f32 rate;

        angle_limit = g_ant_bridge_angle_limit * 3.14159274f;
        *(f32 *)(vars + 0x74) = *(f32 *)(vars + 0x74)
            + (*(f32 *)(obj + 0xF4) / (f32)(((int)(g_ant_bridge_divisor) * 5 + 2) / 6) + 0.00013962637f);
        angle = *(f32 *)(obj + 0xF4) + *(f32 *)(vars + 0x74);
        *(f32 *)(obj + 0xF4) = angle;
        if (angle_limit < angle) {
            *(f32 *)(obj + 0xF4) = angle_limit;
            rate = *(f32 *)(vars + 0x74);
            if (0.0006981318f < rate) {
                *(f32 *)(vars + 0x74) = rate * -0.5f;
            } else {
                *(s32 *)(vars + 0x74) = 0;    /* the retail stores the word, not the float */
                moby_set_state(obj, 5, -1);
            }
        }
        break;
    }
    }
}

/* case 0 spawns the object and points the actor at it; case 1 clears the
   object while the state word still reads zero, and clears the word otherwise */
typedef struct {
    u32 field00;
    u8 pad04[0xC];
} L03_22C8Entry;

extern L03_22C8Entry *g_path_l03_entry_table[];
extern void moby_set_state(char *moby, s32 a1, s32 a2);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
