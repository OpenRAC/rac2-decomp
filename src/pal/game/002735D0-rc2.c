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

s32 cam_moby_update_pal(void *moby) {
    s8 loc[0x210];
    s8 *vars;
    s32 result;
    u32 sel;
    f32 coord;

    static void *tgt[] = {&&case02, &&case02, &&case4, &&case5, &&case13, &&case13};

    vars = (*(s8 **)((s8 *)(moby) + (0x68)));
    result = 0;
    sel = (*(u8 *)((s8 *)(vars) + (0x5D)));
    if (sel >= 6) {
        goto done;
    }
    {
        s8 *tb = g_cam_mode_table;

        goto *(void *)*(s32 *)(tb + sel * 4);
    }

case02:
    if ((*(u8 *)((s8 *)(vars) + (0x5D))) == 0) {
        (*(s8 *)((s8 *)(vars) + (0x58))) = coll_convert_packed_points_to_vectors(moby, loc, 0x20);
    } else {
        moby_get_joint_matrix(moby, loc + 0x200, loc, (*(s16 *)((s8 *)(vars) + (0x36))));
    }
    (*(s8 **)((s8 *)(vars) + (0x30))) = loc;
    result = target_seeker_update_pal(moby);
    if (!((*(u8 *)((s8 *)(vars) + (0x5C))) == 0 && (g_game_time & 3) != 0)) {
        result = (FastDecTimer(vars + 0x34) != 0) ? 1 : result;
    }
    (*(s8 **)((s8 *)(vars) + (0x30))) = 0;
    goto done;

case4:
    result = stub_return_one_a(moby);
    goto done;

case5:
    result = stub_return_one_b(moby);
    goto done;

case13:
    result = cam_moby_update_colliding_pal(moby);
    result = (FastDecTimer(vars + 0x34) != 0) ? 1 : result;
    goto done;

done:
    coord = (*(f32 *)((s8 *)(moby) + (0x10)));
    if (coord < 2.0f || coord > 1021.0f) {
        return 1;
    }
    coord = (*(f32 *)((s8 *)(moby) + (0x14)));
    if (coord < 2.0f || coord > 1021.0f) {
        return 1;
    }
    coord = (*(f32 *)((s8 *)(moby) + (0x18)));
    if (coord < 2.0f || coord > 1021.0f) {
        return 1;
    }
    return result;
}
