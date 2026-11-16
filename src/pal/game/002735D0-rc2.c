#include "include_asm.h"

#include "common.h"
extern s8 g_cam_mode_table[];
extern s8 coll_convert_packed_points_to_vectors(void *, s8 *, s32);
extern int moby_get_joint_matrix(void *, s8 *, s8 *, s16);
extern s32 target_seeker_update_pal(void *);
extern s32 cam_moby_update_colliding_pal(void *);
extern s32 stub_return_one_a(void *);
extern s32 stub_return_one_b(void *);
extern s32 FastDecTimer(void *);
extern s32 g_game_time;

s32 cam_moby_update_pal(void *arg0) {
    s8 loc[0x210];
    s8 *s0;
    s32 s2;
    u32 sel;
    f32 f;

    static void *tgt[] = {&&case02, &&case02, &&case4, &&case5, &&case13, &&case13};

    s0 = (*(s8 **)((s8 *)(arg0) + (0x68)));
    s2 = 0;
    sel = (*(u8 *)((s8 *)(s0) + (0x5D)));
    if (sel >= 6) {
        goto done;
    }
    {
        s8 *tb = g_cam_mode_table;

        goto *(void *)*(s32 *)(tb + sel * 4);
    }

case02:
    if ((*(u8 *)((s8 *)(s0) + (0x5D))) == 0) {
        (*(s8 *)((s8 *)(s0) + (0x58))) = coll_convert_packed_points_to_vectors(arg0, loc, 0x20);
    } else {
        moby_get_joint_matrix(arg0, loc + 0x200, loc, (*(s16 *)((s8 *)(s0) + (0x36))));
    }
    (*(s8 **)((s8 *)(s0) + (0x30))) = loc;
    s2 = target_seeker_update_pal(arg0);
    if (!((*(u8 *)((s8 *)(s0) + (0x5C))) == 0 && (g_game_time & 3) != 0)) {
        s2 = (FastDecTimer(s0 + 0x34) != 0) ? 1 : s2;
    }
    (*(s8 **)((s8 *)(s0) + (0x30))) = 0;
    goto done;

case4:
    s2 = stub_return_one_a(arg0);
    goto done;

case5:
    s2 = stub_return_one_b(arg0);
    goto done;

case13:
    s2 = cam_moby_update_colliding_pal(arg0);
    s2 = (FastDecTimer(s0 + 0x34) != 0) ? 1 : s2;
    goto done;

done:
    f = (*(f32 *)((s8 *)(arg0) + (0x10)));
    if (f < 2.0f || f > 1021.0f) {
        return 1;
    }
    f = (*(f32 *)((s8 *)(arg0) + (0x14)));
    if (f < 2.0f || f > 1021.0f) {
        return 1;
    }
    f = (*(f32 *)((s8 *)(arg0) + (0x18)));
    if (f < 2.0f || f > 1021.0f) {
        return 1;
    }
    return s2;
}
