#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

typedef struct {
    u8 pad[0x274];
    f32 f274;
    f32 f278;
    f32 f27C;
    s32 i280;
} T_001B99C0;

extern T_001B99C0 D_L16_001B99C0;

extern void anim_start_blended(void *, s32, s32, s32);

/* func_L16_002C6378 is in the sibling file L16_002C6378-decider.c (its own profile). */

/* func_L16_002D2D10: 76 bytes against retail's 88 - the divisions and the stores
   are now in retail's order, but retail's pair of `nop`s before each `div.s` is
   missing.  Deposited in nonmatching/levels/func_L16_002D2D10.c. */
/* func_L16_002D2D10 is matched in its own unit, L16_002D2D10.c. */

/* func_L16_002F60B8 is in L16_002F60B8-g8.c. */

/* func_L16_00317C90 is in the sibling file L16_00317C90.c: it needs the -g profile, whose
   line labels let the assembler reproduce the padding before its division. */

/* runs the readiness helper once when the handle is in state 1 with flag 2 set */
/* Restarts the object's animation once it is in state 1 and its ready flag is set. */
void moby_restart_anim_when_ready(u8 *object) {
    if (object[0x43] == 1 && (object[0x60] & 2) != 0) {
        anim_start_blended(object, 0, 0, 1);
    }
}


/* func_L16_003AA3F0 is in L16_003AA3F0-g8.c. */

/* func_L16_003D6D00: 368 bytes against retail's 364; the prologue, the frame layout
   and every branch target from +0x44 on are retail's, but the byte test comes out
   as the annulling `bnel` (which repeats the pointer load) instead of retail's plain
   `bnez`, and the pointer and the base land in $s0/$s2 instead of $s2/$s1.
   Deposited in nonmatching/levels/func_L16_003D6D00.c. */

/* func_L16_003E6E08 is in L16_003E6E08-g8.c (vector-copy profile). */

/* func_L16_003E70E0 is defined in L16_002C6378-g8.c (it reads $gp data). */

/* func_L16_003E7248 is defined in L16_003E7248-g8.c (it reads $gp data). */

/* func_L16_003F4FA8 is defined in L16_003F4FA8.c (vector-copy profile). */

extern void moby_set_state(char *, s32, s32);

extern s32 part_find_owned_effect_slot(char *, s32, s32);

extern void part_spawn_random_bursts_outside_box(char *);

extern void EmitParticlesOutsideCentralBox(char *);

extern void PlayMobySound(s32, s32, char *);

extern void moby_mark_spawned(char *);

/* Tears the resident down (state 0) or starts it once the readiness test passes
   (state 1), chosen by the record's own state byte. */
/* Shuts the object down in state 0, or fires off its effects once it is ready in state 1. */
void spawner_l16_update(char *object) {
    char *self = object;

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(u16 *)(self + 0x32) = 0x200;
        *(u16 *)(self + 0x34) |= 0x4000;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(self, 0x80000, 0) != 0) {
            part_spawn_random_bursts_outside_box(self);
            EmitParticlesOutsideCentralBox(self);
            PlayMobySound(0, 0, self);
            moby_mark_spawned(self);
        }
        break;
    }
}

/* func_L16_003F55A0 is in L16_003F55A0-g8.c; its division needs -g. */

/* func_L16_003F5708 is in L16_003F5708-g8.c. */
