#include "names.h"
/* func_L07_003F8C38 (152 bytes): finds the controller's group member, takes the object's
   frame position, and hands both to func_L07_003F6C40 with the record's scale + 0.5. The
   record table pointer is read with the absolute macro (MACRO_ADDR), and func_002E5CF8
   returns a value. */
#include "common.h"


typedef struct { u8 pad38[0x38]; f32 f38; u8 rest[128 - 0x3C]; } SibRec128;
extern SibRec128 *g_shooter_mount_table MACRO_ADDR;
extern u8 *moby_find_active_in_group(u8 *a);
extern void homing_bomb_init(u8 *a, u8 *b, void *c, f32 d);
extern void moby_transform_joint_to_world(u8 *a, s32 b, void *c);
extern int PlayMobySound(int, int, char *);

void group_spawn_member_effect(u8 *moby)
{
    u8 *member;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 frame_pos[16];

    member = moby_find_active_in_group(*(u8 **)(vars + 0x184));
    if (member == 0)
        return;
    moby_transform_joint_to_world(moby, 0, frame_pos);
    PlayMobySound(5, 0, (char *)moby);
    homing_bomb_init(member, moby, frame_pos, g_shooter_mount_table[*(s32 *)(vars + 0x174)].f38 + 0.5f);
}
