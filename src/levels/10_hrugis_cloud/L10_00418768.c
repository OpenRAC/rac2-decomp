#include "common.h"

/* func_L10_00418768 needs -fstrict-aliasing (config/cflags.txt): retail loads the record
   table base D_001B251C ahead of the state reload at +0x144, which the scheduler may only
   do when the pointer load is known not to alias the int store to the record before it.
   `one` is measured: retail keeps 1 in $s0 across the func_0037D390 call. */

extern u8 *D_001B251C __attribute__((sda));
extern u8 D_L10_00188660[];

extern u8 *func_0037B670(u8 *arg0);
extern void hrugis_init_flying_piece(u8 *arg0);
extern void func_00308AF8(u8 *a0);
extern void func_0037BC48(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern u8 *func_0037BA88(u8 *arg0);
extern void func_0037DFB8(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern void func_00373410(s32 a0);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern void func_0037D7A0(u8 *a0, s32 a1, f32 f12);
extern void hrugis_start_timed_effect(u8 *arg0);
extern s32 func_0037D6E0(u8 *a0);
extern void func_0037D528(u8 *a0);
extern void func_003087A0(u8 *a0);
extern void part_spawn_small_tail_trail(u8 *arg0);
extern void snd_stop_moby_effect(u8 *arg0);

/* Per-frame update of the class 3982 ship: on the first frame it starts up, afterwards it plays
   its hit reaction, keeps its sound effect alive and leaves trail marks. */
void mission_target_ship_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *actor;
    u8 *record;
    s32 effectId;
    s32 tmp[4];
    s32 one;

    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        if (func_0037B670(moby) == 0)
            return;
        hrugis_init_flying_piece(moby);
        func_00308AF8((u8 *)tmp);
        if (*(s32 *)(vars + 0x264) != 0)
            func_0037BC48(moby, (s32)snd_stop_moby_effect, 0, 0);
        return;
    }
    actor = func_0037BA88(moby);
    if (*(s32 *)(actor + 0x110) == 0)
        return;
    func_0037DFB8(moby);
    one = 1;
    if (func_0037D390(moby, 0, 0, 0) == one) {
        effectId = *(s32 *)(vars + 0x26C);
        if (effectId != -1) {
            record = D_L10_00188660 + effectId * 0x70;
            if (*(u8 **)(record + 0x88) == moby && record[0x74] != 0)
                func_00373410(effectId);
        }
        *(s32 *)(vars + 0x26C) = -1;
        func_003737B8(2, 0, moby, 0xF8E);
    }
    func_0037D7A0(moby, 0, 176.0f);
    if (*(s32 *)(actor + 0x110) == 1) {
        if (*(s32 *)(vars + 0x260) != -1) {
            *(s32 *)(actor + 0x11C) = *(s32 *)(actor + 0x110);
            *(u8 **)(actor + 0x120) = D_001B251C + (*(s32 *)(vars + 0x260) << 8);
        }
        if (*(s32 *)(actor + 0x104) != 0)
            hrugis_start_timed_effect(moby);
        if (func_0037D6E0(moby) != 0)
            func_0037D528(moby);
        func_003087A0(vars + 0x268);
        part_spawn_small_tail_trail(moby);
    }
    record = D_L10_00188660 + *(s32 *)(vars + 0x26C) * 0x70;
    if (*(u8 **)(record + 0x88) != moby || record[0x74] == 0)
        *(s32 *)(vars + 0x26C) = func_003737B8(0, 6, moby, 0xF8E);
}
