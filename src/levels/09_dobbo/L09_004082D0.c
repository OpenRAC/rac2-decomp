#include "common.h"

extern s32 g_frame_l09_counter MACRO_ADDR;
extern char g_dobbo_target_point[];
extern char g_camera_l09_position[];
extern s32 func_325E78(char *a0, s32 a1);
extern void dobbo_apply_setting_group(char *a0, char *a1, s32 a2, s32 a3);
extern void dobbo_apply_setting_by_index(char *a0, s32 a1, char *a2, s32 a3);
typedef int TQ_L09_004082D0 __attribute__((mode(TI)));

/* Decides whether the object is on (state 0: any of its four ids passes func_325E78 against one
   of two positions; state 1: always) and, when that changed or +0x20 is still clear, records it
   and passes it to the ids of both of its lists. */
void trigger_switch_update(u8 *obj) {
    char *vars;
    s32 *second_list;
    s32 i;
    s32 flag;
    s32 state;
    s32 v;
    TQ_L09_004082D0 buf;

    if (g_frame_l09_counter >= 5) {
        vars = *(char **)(obj + 0x68);
        obj[0x30] = 0xFF;
        flag = 0;
        if (*(s8 *)(vars + 0xBE) != 0) {
            qcopy(&buf, g_camera_l09_position);
        } else {
            qcopy(&buf, g_dobbo_target_point);
        }
        state = obj[0x95];
        if (state == 0) {
            for (i = 0; i < 4; i++) {
                v = ((s32 *)vars)[i];
                if (v != -1) {
                    if (func_325E78((char *)&buf, v) != 0) {
                        flag = 1;
                        break;
                    }
                }
            }
        } else {
            flag = 0;
            if (state == 1) {
                v = 1;
                flag = v;
            }
        }
        if (flag) {
            if (obj[0xBC] == 0)
                goto update;
        } else {
            if (obj[0xBC] != 0)
                goto update;
        }
        if (obj[0x20] != 0)
            return;
update:
        if (flag)
            obj[0xBC] = 1;
        else
            obj[0xBC] = 0;
        obj[0x20] = obj[0xBC] + 1;
        second_list = (s32 *)(vars + 0x84);
        for (i = 0; i < 29; i++) {
            s32 id = ((s32 *)(vars + 0x10))[i];
            if (id != -1) {
                dobbo_apply_setting_group(obj, vars, id, flag);
            }
        }
        for (i = 0; i < 14; i++) {
            s32 id = second_list[i];
            if (id != -1) {
                dobbo_apply_setting_by_index(obj, id, vars, flag);
            }
        }
    }
}
