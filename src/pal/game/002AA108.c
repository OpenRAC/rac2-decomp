#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern s32 func_001163B0(void);
extern f32 func_002A7940_5(void);
extern f32 func_002A7878_10(f32, f32);
extern f32 func_00283180_3 (f32);
extern s32 g_collision_hit[];
typedef struct Rec_002A96A0 {
    char pad0[4];
    short s4;
    char pad6[0x11];
    u8 b17;
    u8 *p18;
    short s1C;
} Rec_002A96A0;
typedef struct Src_002A96A0 {
    char pad0[0x20];
    u8 *p20;
    int f24;
    u8 b28;
    float f2C;
} Src_002A96A0;
extern Rec_002A96A0 *moby_get_private_value_0(s32);
extern char *moby_get_private_value_4(s32);
extern u8 moby_get_kind_slot(u8 *);

/* Tracks which target the player is aiming at and returns an updated strength value, with a short delay before switching (PAL). */
f32 moby_update_aim_target_strength_pal(s32 id, Src_002A96A0 *src) {
    Rec_002A96A0 *aim = moby_get_private_value_0(id);
    f32 strength = 0.0f;
    if (aim != 0) {
        u8 *old_target = aim->p18;
        if (old_target != 0) {
            u8 old_kind = old_target[0x20];
            if (old_kind != 0xFE) {
                if (old_kind == 0xFD) {
                    aim->s1C = 0;
                    aim->p18 = 0;
                }
            } else {
                aim->s1C = 0;
                aim->p18 = 0;
            }
        }
        {
            short timer = aim->s1C;
            if (timer != 0) {
                aim->s1C = (unsigned short)aim->s1C + 1;
                if (timer >= 0x65) {
                    aim->p18 = 0;
                    aim->s1C = 0;
                }
            }
        }
        if (src != 0) {
            u8 *new_target = src->p20;
            strength = src->f2C;
            if (new_target != 0) {
                if (aim->p18 != new_target) {
                    aim->p18 = new_target;
                    aim->b17 = moby_get_kind_slot(src->p20);
                    aim->s1C = 1;
                } else {
                    if (src->b28 == 9) {
                        if (aim->s1C < 0x32) strength = 0.0f;
                        else aim->s1C = 1;
                    } else {
                        if (aim->s1C < 8) strength = 0.0f;
                        aim->s1C = 1;
                    }
                }
            }
            if ((f32)aim->s4 <= 1.0f && strength > 0.0f && strength < 1.0f) strength = 1.0f;
            if (src->f24 & 0x100000) {
                u8 *other_state = moby_get_private_value_4(id);
                if (other_state != 0) other_state[0x18] = 1;
            } else {
                u8 *other_state = moby_get_private_value_4(id);
                if (other_state != 0) other_state[0x18] = 0;
            }
        }
    }
    return strength;
}

