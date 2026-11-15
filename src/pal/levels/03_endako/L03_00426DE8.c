#include "include_asm.h"
#include "common.h"

extern char D_L03_00259A30[];
extern void level_init_pending_slot(u8 *, char *);
extern void level_append_record_to_table(char *, s32, s32, float);
extern void moby_update_transform_history_followers(char *, s32);
extern void level_release_slot_list(char *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 cam_moby_update(u8 *);
extern void moby_mark_spawned(void *);

void func_PAL_L03_00426DE8(u8 *obj)
{
    u8 *p = *(u8 **)(obj + 0x68);
    char *tbl;
    s32 n;
    s32 index;
    s32 k;

    switch (obj[0x20]) {
    case 0:
        index = *(s16 *)(p + 0x36);
        n = 0x150;
        tbl = D_L03_00259A30;
        level_init_pending_slot(obj, &tbl[index * n]);
        level_append_record_to_table(&tbl[*(s16 *)(p + 0x36) * n], 0x28, 2, 0.0f);
        level_append_record_to_table(&tbl[*(s16 *)(p + 0x36) * n], 0x14, 4, 0.0f);
        level_append_record_to_table(&tbl[*(s16 *)(p + 0x36) * n], 0xA, 6, 0.0f);
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        k = 0x150;
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * k];
        moby_update_transform_history_followers(tbl, 0);
        n = cam_moby_update(obj);
        if (n != 0) {
            moby_set_state(obj, 2, -1);
            *(u16 *)(obj + 0x34) |= 0x2800;
        }
        break;
    case 2:
        cam_moby_update(obj);
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * 0x150];
        level_release_slot_list(tbl);
        if (obj[0x23] < 2) {
            moby_mark_spawned(obj);
        } else {
            obj[0x23] -= 2;
        }
        break;
    }
}
