#include "include_asm.h"
#include "names.h"
typedef signed int s32;
typedef unsigned char u8;
extern s32 func_003351C0(s32 mode);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern u8 *func_0037B670(u8 *arg0);
extern s32 func_003062A0(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_00335200(s32 a0, s32 a1);
extern void cloud_puff_init(u8 *arg0);
extern void part_spawn_large_tail_trail(u8 *arg0);
extern int state_get_stored_pointer_value(void);
extern void moby_l00_update_empty_4(void);
extern void level_append_object(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 moby_process_collision_hit(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 snd_play_from_class_bank(s32 index, s32 value, u8 *object, s32 kind);
extern s32 func_0037D6E0(u8 *a0);
extern u8 *D_L10_0020B1E0[];
extern u8 *D_001B251C;
extern u8 D_L10_00265BA0[];
extern u8 D_L10_00188660[];
extern u8 D_L10_00221CD0[];
extern u8 g_sound_state[];
extern s32 D_001B0F44 __attribute__((sda));
extern s32 D_001B0F48 __attribute__((sda));

/* Update step of the cloud object: the state byte at +0x20 picks the step (0 re-arms the
   object and queues its effect, 1 spawns it), and the object's own record in the shared
   table D_00188660 is then looked up before its effect of kind 0xF8D is created. */
extern void moby_handler_empty(void);
void func_PAL_L10_0041D1B0(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 state = s0[0x20];
    u8 *p;

    switch (state) {
    case 0:
        s0[0x30] = 0xFF;
        if (state_get_stored_pointer_value() == 0)
            return;
        cloud_puff_init(s0);
        if (*(s32 *)(s1 + 0x264) != 0)
            level_append_object(s0, (s32)moby_handler_empty, 0, 0);
        break;
    case 1:
        moby_process_collision_hit(s0, 0, 1, 1);
        part_spawn_large_tail_trail(s0);
        break;
    }
    p = g_sound_state + *(s32 *)(s1 + 0x268) * 0x70;
    if (*(u8 **)(p + 0x88) == s0 && p[0x74] != 0)
        return;
    *(s32 *)(s1 + 0x268) = snd_play_from_class_bank(0, 6, s0, 0xF8D);
}
