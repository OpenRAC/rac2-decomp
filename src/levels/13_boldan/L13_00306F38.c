#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;

extern f32 func_2F9748(f32, f32);
extern s32 func_32A4D0(u8 *, s32);
extern s32 func_31A718(u8 *);
extern s32 func_3248E0(u8 *, s32, s32);
extern void func_337400(s32, s32);
extern s32 func_2AF870(u8 *);
extern void func_327D00(f32 *, f32 *, f32, f32, f32, f32);
extern char g_hero_position[];
extern f32 D_L13_001B2568 __attribute__((sda));
extern u32 D_L13_001B291C[] __attribute__((sda));
extern u8 D_L13_001B1E60[];
extern void func_2F8A20(u8 *, u8 *, f32);
extern u8 D_0019B2E8[];
extern s32 g_current_map_index __attribute__((sda));
extern u8 *D_L13_001B2A0C __attribute__((sda));
extern u8 *D_L13_001B291C_2;
extern u8 g_hero_state[];

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0x68 - 0x36];
    unsigned int p68;
    unsigned char pad6C[0xAA - 0x6C];
    short type;
} Mob_L13_00306F38;

typedef struct {
    unsigned char pad00[0x30];
    int mode;
    unsigned char pad34[0x44 - 0x34];
    short count;
    unsigned char pad46[0x18C - 0x46];
    Mob_L13_00306F38 *mobs[1];
} MobList_L13_00306F38;

extern MobList_L13_00306F38 ref_L13_00306F38_00;
extern int g_current_map_index __attribute__((sda));
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
typedef struct { unsigned char pad[0x7C]; short f7C; } Obj_L13_00306F38;

/* Walks the level's list of mobs like func_L02_00300CE8; when the game state is 0xD and the
   list's word at +0x30 is 0 or 1 it sets the 0x7C halfword of two of the list's objects. */
/* Sets up the level's objects each load: shows some, runs setup on others, and prepares two special ones. */
void boldan_init_level_objects(void) {
    int i;

    anim_start_startup_animations();
    for (i = 0; i < ref_L13_00306F38_00.count; i++) {
        Mob_L13_00306F38 *mob = ref_L13_00306F38_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29)
            mob->flags |= 0x800;
        if (mob->type == 0xD54)
            UpdateEquipmentPieces(mob);
        if (mob != 0 && mob->type == 0xFA0 && mob->p68 != 0)
            math_store_angle_update_result(mob, (unsigned char *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.0610865355f);
    }
    if (g_current_map_index == 0xD) {
        switch (ref_L13_00306F38_00.mode) {
        case 0:
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x1A0))->f7C = 7;
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x1A4))->f7C = 7;
            break;
        case 1:
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x19C))->f7C = 7;
            (*(Obj_L13_00306F38 **)((char *)&ref_L13_00306F38_00 + 0x1A0))->f7C = 7;
            break;
        }
    }
}




/* func_L13_0035E890 is in ../shared/L13_0035E890-init-g8.c; v2.00/PAL also use it in Notak. */

/* func_L13_0038C328 is in the -g8 sibling (L13_00306F38-g8.c): it addresses its
   three globals through $gp. */

/* Toggles between two states each time the player enters a trigger box, calling a switch action each time. */
void toggle_switch_trigger_boxes_update(u8 *moby) {
    s32 *vars = *(s32 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        func_3248E0(moby, 1, -1);
        break;
    case 1:
        if (func_32A4D0(g_hero_position, vars[0]) != 0) {
            func_337400(vars[4], vars[6]);
            func_3248E0(moby, 2, -1);
        }
        break;
    case 2:
        if (func_32A4D0(g_hero_position, vars[1]) != 0) {
            func_337400(vars[5], vars[7]);
            func_3248E0(moby, 1, -1);
        }
        break;
    }
}

/* func_L13_00397600 is in L13_00397600.c. */

/* func_L13_00397A18 is in L13_00397A18.c. */



/* Spins the object a small step around its vertical axis each frame. */
void moby_spin_yaw(u8 *moby) {
    *(f32 *)(moby + 0xF4) = func_2F9748(*(f32 *)(moby + 0xF4), 0.017453296f);
}

/* Spins the object a small step around its vertical axis each frame. */
void moby_spin_yaw_alt(u8 *moby) {
    *(f32 *)(moby + 0xF4) = func_2F9748(*(f32 *)(moby + 0xF4), 0.017453296f);
}

/* Spins the object around its vertical axis each frame, a little faster. */
void moby_spin_yaw_fast(u8 *moby) {
    *(f32 *)(moby + 0xF4) = func_2F9748(*(f32 *)(moby + 0xF4), 0.029088825f);
}

/* Spins the object a small step around its vertical axis each frame. */
void moby_spin_yaw_slow(u8 *moby) {
    *(f32 *)(moby + 0xF4) = func_2F9748(*(f32 *)(moby + 0xF4), 0.017453296f);
}

/* Spins the object a small step around its vertical axis each frame. */
void moby_spin_yaw_small(u8 *moby) {
    *(f32 *)(moby + 0xF4) = func_2F9748(*(f32 *)(moby + 0xF4), 0.017453296f);
}

/* func_L13_003E8850 is in L13_003E8850.c. */

/* func_L13_003EFD58 is in L13_003EFD58.c. */

/* func_L13_003FE420 is in the -gate sibling. */

/* The level's lift platform: it picks its next state from the neighbour it hangs on,
   then drives the platform through it. func_002AAA00 takes two pointers, four floats
   (radians) and an integer, in that order. */
extern f32 vec_distance_xy(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern void math_approach_target_with_direction_mode(void *, void *, f32, f32, f32, f32, s32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);

/* Lift arm that tilts down when the player is near or presses the control, then slides back after a short wait. */
void lift_arm_tilt_down_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 step[4];

    if (*(s32 *)vars != 0) {
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 8.0f) {
            if (moby[0x20] == 0) {
                moby[0x20] = 1;
            }
        }
    } else if (*(s32 *)(vars + 8) != 0) {
        if (fast_vec_dist(moby + 0x10, g_hero_position) < 8.0f) {
            if (moby[0x20] == 0) {
                if (*(s16 *)(g_hero_position + 0x2C8) == 1) {
                    moby[0x20] = 2;
                }
            }
        }
    } else {
        if (moby[0x20] == 0) {
            *(u32 *)(moby + 0x98) = 0;
            moby[0x20] = 3;
        }
    }

    if (moby[0x20] == 1) {
        math_approach_target_with_direction_mode(moby + 0xF8, vars + 4, -0.78539824f, 0.0017453295f, 0.0017453295f, 0.0349065922f, 0);
    }
    if (moby[0x20] == 2) {
        math_approach_target_with_direction_mode(moby + 0xF8, vars + 4, -1.5707965f, 0.0017453295f, 0.0017453295f, 0.0349065922f, 0);
    }
    if (moby[0x20] == 4) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
        vec_scale_to_length(step, moby + 0xD0, -0.16666667f);
        FastVecAdd(moby + 0x10, moby + 0x10, step);
        if (*(u16 *)(moby + 0x96) >= 11) {
            *(u16 *)(moby + 0x96) = 0;
            moby[0x20] = 5;
        }
    }
    if (moby[0x20] == 5) {
        u32 ticks = *(u16 *)(moby + 0x96) + 1;

        *(u16 *)(moby + 0x96) = ticks;
        if ((u16)ticks >= 31) {
            *(u16 *)(moby + 0x96) = 0;
            moby[0x20] = 6;
        }
    }
    if (moby[0x20] == 6) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
        vec_scale_to_length(step, moby + 0xD0, 0.16666667f);
        FastVecAdd(moby + 0x10, moby + 0x10, step);
        if (*(u16 *)(moby + 0x96) >= 11) {
            moby[0x20] = 0;
        }
    }
}

/* Lift arm that tilts up when the player is near or presses the control, then slides back after a short wait. */
void lift_arm_tilt_up_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 step[4];

    if (*(s32 *)vars != 0) {
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 8.0f) {
            if (moby[0x20] == 0) {
                moby[0x20] = 1;
            }
        }
    } else if (*(s32 *)(vars + 8) != 0) {
        if (fast_vec_dist(moby + 0x10, g_hero_position) < 8.0f) {
            if (moby[0x20] == 0) {
                if (*(s16 *)(g_hero_position + 0x2C8) == 1) {
                    moby[0x20] = 2;
                }
            }
        }
    } else {
        if (moby[0x20] == 0) {
            *(u32 *)(moby + 0x98) = 0;
            moby[0x20] = 3;
        }
    }

    if (moby[0x20] == 1) {
        math_approach_target_with_direction_mode(moby + 0xF8, vars + 4, 2.3561947345733643f, 0.0017453295f, 0.0017453295f, 0.0349065922f, 0);
    }
    if (moby[0x20] == 2) {
        math_approach_target_with_direction_mode(moby + 0xF8, vars + 4, 1.5707965f, 0.0017453295f, 0.0017453295f, 0.0349065922f, 0);
    }
    if (moby[0x20] == 4) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
        vec_scale_to_length(step, moby + 0xD0, 0.16666667f);
        FastVecAdd(moby + 0x10, moby + 0x10, step);
        if (*(u16 *)(moby + 0x96) >= 11) {
            *(u16 *)(moby + 0x96) = 0;
            moby[0x20] = 5;
        }
    }
    if (moby[0x20] == 5) {
        u32 ticks = *(u16 *)(moby + 0x96) + 1;

        *(u16 *)(moby + 0x96) = ticks;
        if ((u16)ticks >= 31) {
            *(u16 *)(moby + 0x96) = 0;
            moby[0x20] = 6;
        }
    }
    if (moby[0x20] == 6) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
        vec_scale_to_length(step, moby + 0xD0, -0.16666667f);
        FastVecAdd(moby + 0x10, moby + 0x10, step);
        if (*(u16 *)(moby + 0x96) >= 11) {
            moby[0x20] = 0;
        }
    }
}

/* func_L13_004067F8 is in L13_004067F8-g8.c. */


/* Sets a camera distance value depending on which of two trigger boxes the player is in. */
void cam_set_value_from_trigger_boxes(u8 *moby) {
    s32 *vars = *(s32 **)(moby + 0x68);
    u8 *base = g_hero_position;
    if (func_32A4D0(base, vars[0]) != 0) D_L13_001B2568 = 30.0f;
    if (func_32A4D0(base, vars[1]) != 0) D_L13_001B2568 = 95.0f;
}

/* func_L13_0041BDA8 is in L13_0041BDA8.c. */

/* func_L13_0041CD18 is in L13_00306F38-f7-g8.c. */



/* The object's five states, state 0 to 4. The dispatch reads the level's own jump table
   (the five-word table in the level's data at 0x2ADD00); `cases` only keeps the labels alive. */
extern void *D_L13_002ADD00[];
extern u8 g_sound_state[];
extern u8 D_L13_001B1C20[];
extern u8 D_L13_001B1C48[];
extern u16 *D_L13_001FB420[];
extern s32 D_L13_001B2938 __attribute__((sda));
extern void STUB_printf(void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 IsPointInCuboid(u8 *, s32);
extern s32 flag_set_first_pending(u8 *);
extern void snd_stop_voice(s32);
extern s32 snd_start_in_slot(s32, s32, u8 *);
extern s32 math_fast_float_d(u8 *);

/* Controls a door-like object: moves between its open and closed states and switches other objects on or off as it goes. */
void linked_l13_door_update(u8 *moby) {
    static void *cases[5] = {&&c0, &&c1, &&done, &&c3, &&c4};
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 *listEntry;
    u8 *target;
    u8 *soundSlot;
    s32 soundIndex;
    s32 soundId;
    u32 stateIndex;

    stateIndex = moby[0x20];
    if (stateIndex < 5)
        goto *D_L13_002ADD00[stateIndex];
    goto done;
c0:
    *(s32 *)(vars + 0x2C) = -1;
    if (D_L13_001FB420[*(s32 *)vars] == 0) {
        STUB_printf(D_L13_001B1C20);
        moby_mark_spawned(moby);
        return;
    }
    if (*(s32 *)(vars + 4) == -1) {
        STUB_printf(D_L13_001B1C48);
        moby_mark_spawned(moby);
        return;
    }
    *(s32 *)(vars + 0x18) = 0;
    *(s32 *)(vars + 0x14) = 0;
    *(s32 *)(vars + 0x24) = *(s32 *)(vars + 8);
    *(s32 *)(vars + 0x28) = *(s32 *)(vars + 0xC);
    moby_set_state(moby, 1, -1);
    goto done;
c1:
    if (IsPointInCuboid((u8 *)g_hero_position, *(s32 *)(vars + 0x10)) != 0)
        moby_set_state(moby, 3, -1);
    soundIndex = *(s32 *)(vars + 0x2C);
    if (soundIndex != -1) {
        soundSlot = g_sound_state + soundIndex * 0x70;
        if (*(u8 **)(soundSlot + 0x88) == moby && soundSlot[0x74] != 0)
            snd_stop_voice(soundIndex);
    }
    *(s32 *)(vars + 0x2C) = -1;
    goto done;
c3:
    flag_set_first_pending(moby);
    soundId = *(s32 *)(vars + 0x2C);
    if (soundId == -1 || *(u8 **)((soundSlot = g_sound_state + soundId * 0x70) + 0x88) != moby || soundSlot[0x74] == 0)
        *(s32 *)(vars + 0x2C) = snd_start_in_slot(0x13, 4, moby);
    if (math_fast_float_d(vars + 0x24) != 0 && *(s32 *)(vars + 0x14) == 0) {
        for (listEntry = D_L13_001FB420[*(s32 *)vars];
             (*(s32 *)vars & 0xFF) != 0xFF && *(s32 *)vars <= D_L13_001B2938 && listEntry != 0 &&
             ((listEntry != 0 && (s16)listEntry[-1] >= 0) || listEntry == D_L13_001FB420[*(s32 *)vars]);
             listEntry++) {
            target = (u8 *)D_L13_001B291C[0] + ((*listEntry & 0x7FFF) << 8);
            if (target == 0)
                break;
            if (*(s16 *)(target + 0xAA) == 0xEE7)
                *(s32 *)(*(u8 **)(target + 0x68) + 0x628) = 1;
        }
        *(s32 *)(vars + 0x14) = 1;
    }
    if (math_fast_float_d(vars + 0x28) != 0 && *(s32 *)(vars + 0x18) == 0) {
        *(s32 *)(*(u8 **)((u8 *)D_L13_001B291C[0] + (*(s32 *)(vars + 4) << 8) + 0x68) + 0x3C) = 1;
        *(s32 *)(vars + 0x18) = 1;
    }
    if (*(s32 *)(vars + 0x18) != 0 && *(s32 *)(vars + 0x14) != 0) {
        *(s32 *)(vars + 0x28) = *(s32 *)(vars + 0x1C);
        *(s32 *)(vars + 0x24) = *(s32 *)(vars + 0x20);
        moby_set_state(moby, 4, -1);
    }
    goto done;
c4:
    if (math_fast_float_d(vars + 0x24) != 0 && *(s32 *)(vars + 0x14) != 0) {
        for (listEntry = D_L13_001FB420[*(s32 *)vars];
             (*(s32 *)vars & 0xFF) != 0xFF && *(s32 *)vars <= D_L13_001B2938 && listEntry != 0 &&
             ((listEntry != 0 && (s16)listEntry[-1] >= 0) || listEntry == D_L13_001FB420[*(s32 *)vars]);
             listEntry++) {
            target = (u8 *)D_L13_001B291C[0] + ((*listEntry & 0x7FFF) << 8);
            if (target == 0)
                break;
            if (*(s16 *)(target + 0xAA) == 0xEE7)
                *(s32 *)(*(u8 **)(target + 0x68) + 0x628) = 0;
        }
        *(s32 *)(vars + 0x14) = 0;
    }
    if (math_fast_float_d(vars + 0x28) != 0 && *(s32 *)(vars + 0x18) != 0) {
        *(s32 *)(*(u8 **)((u8 *)D_L13_001B291C[0] + (*(s32 *)(vars + 4) << 8) + 0x68) + 0x3C) = 0;
        *(s32 *)(vars + 0x18) = 0;
    }
    if (*(s32 *)(vars + 0x18) == 0 && *(s32 *)(vars + 0x14) == 0) {
        *(s32 *)(vars + 0x24) = *(s32 *)(vars + 8);
        *(s32 *)(vars + 0x28) = *(s32 *)(vars + 0xC);
        moby_set_state(moby, 1, -1);
    }
done:
    return;
}

/* func_L13_004230B0 is in L13_004230B0.c. */

extern s32 IsPointInCuboid(u8 *, s32);
extern u8 D_001395B8[];

/* Marks five progress flags when the player enters four trigger boxes or another object reaches a certain state. */
void boldan_set_progress_flags_from_triggers(u8 *moby) {
    s32 *vars = *(s32 **)(moby + 0x68);
    if (IsPointInCuboid((u8 *)g_hero_position, vars[2]) != 0) {
        if (D_001395B8[0x25] == 0) {
            D_001395B8[0x25] = 1;
        }
    }
    if (IsPointInCuboid((u8 *)g_hero_position, vars[3]) != 0) {
        if (D_001395B8[0x24] == 0) {
            D_001395B8[0x24] = 1;
        }
    }
    if (IsPointInCuboid((u8 *)g_hero_position, vars[0]) != 0) {
        if (D_001395B8[0x27] == 0) {
            D_001395B8[0x27] = 1;
        }
    }
    if (IsPointInCuboid((u8 *)g_hero_position, vars[1]) != 0) {
        if (D_001395B8[0x28] == 0) {
            D_001395B8[0x28] = 1;
        }
    }
    if (*((u8 *)D_L13_001B291C[0] + (vars[4] << 8) + 0x20) == 2) {
        if (D_001395B8[0x26] == 0) {
            D_001395B8[0x26] = 1;
        }
    }
}


/* func_L13_0042BE60: the catalogue entry starts 8 bytes before the body (a stray
   "addiu $sp,$sp,0x190 ; nop" tail). Not a function start — left as retail asm. */


extern void PlayMobySound(s32, s32, u8 *);
extern void math_step_value_toward_target(f32 *, f32 *, f32, f32, f32, f32);

/* Waits for another object to reach its active state, then lifts this object up to its top height. */
void rising_l13_platform_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] == 0) {
        *(u16 *)(moby + 0x34) |= 0x800;
        *(f32 *)(vars + 0x8) = *(f32 *)(moby + 0x18);
        *(f32 *)(vars + 0x4) = *(f32 *)(moby + 0x18) - 6.0f;
        moby[0x20] = 1;
    }
    if (moby[0x20] == 1) {
        u8 v = *((u8 *)D_L13_001B291C[0] + (*(u32 *)vars << 8) + 0x20);
        if (v == 2) {
            PlayMobySound(0, 0, moby);
            moby[0x20] = v;
        }
    }
    if (moby[0x20] == 2) {
        math_step_value_toward_target((f32 *)(moby + 0x18), (f32 *)(vars + 0xC), *(f32 *)(vars + 0x4),
                      0.0016666667f, 0.0016666667f, 0.200000018f);
    }
}

extern s32 func_2AF870(u8 *);
extern void func_327D00(f32 *, f32 *, f32, f32, f32, f32);
extern u8 D_L13_001B1E60[];

/* Waits for another object to reach its active state, then lifts this object up to its top height and starts a sound. */
void rising_platform_sound_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] == 0) {
        *(u16 *)(moby + 0x34) |= 0x800;
        *(f32 *)(vars + 0x8) = *(f32 *)(moby + 0x18);
        *(f32 *)(vars + 0x4) = *(f32 *)(moby + 0x18) - 6.0f;
        moby[0x20] = 1;
    }
    if (moby[0x20] == 1) {
        u8 v = *((u8 *)D_L13_001B291C[0] + (*(u32 *)vars << 8) + 0x20);
        if (v == 2) {
            moby[0x20] = v;
            func_2AF870(D_L13_001B1E60);
        }
    }
    if (moby[0x20] == 2) {
        func_327D00((f32 *)(moby + 0x18), (f32 *)(vars + 0xC), *(f32 *)(vars + 0x4),
                    0.0016666667f, 0.0016666667f, 0.200000018f);
    }
}

/* Separate camera activate, update and exit entries in camvtbl. */
/* Camera hook that does nothing. */
void cam_hook_noop(void *camera)
{
}

/* Camera hook that does nothing. */
void cam_hook_noop_alt(void *camera)
{
}

/* Camera hook that does nothing. */
void cam_hook_noop_extra(void *camera)
{
}
