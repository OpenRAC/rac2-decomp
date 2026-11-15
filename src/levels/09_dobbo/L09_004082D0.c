#include "common.h"

extern s32 D_L09_001B2388 MACRO_ADDR;
extern char D_L09_00189EA0[];
extern char D_L09_001B9A00[];
extern s32 func_325E78(char *a0, s32 a1);
extern void func_L09_00408250(char *a0, char *a1, s32 a2, s32 a3);
extern void func_L09_004081F0(char *a0, s32 a1, char *a2, s32 a3);
typedef int TQ_L09_004082D0 __attribute__((mode(TI)));

/* Decides whether the object is on (state 0: any of its four ids passes func_325E78 against one
   of two positions; state 1: always) and, when that changed or +0x20 is still clear, records it
   and passes it to the ids of both of its lists. */
void func_L09_004082D0(u8 *obj) {
    char *vars;
    s32 *secondList;
    s32 i;
    s32 flag;
    s32 state;
    s32 v;
    TQ_L09_004082D0 buf;

    if (D_L09_001B2388 >= 5) {
        vars = *(char **)(obj + 0x68);
        obj[0x30] = 0xFF;
        flag = 0;
        if (*(s8 *)(vars + 0xBE) != 0) {
            qcopy(&buf, D_L09_001B9A00);
        } else {
            qcopy(&buf, D_L09_00189EA0);
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
        secondList = (s32 *)(vars + 0x84);
        for (i = 0; i < 29; i++) {
            s32 id = ((s32 *)(vars + 0x10))[i];
            if (id != -1) {
                ApplySettingToMobyGroup(obj, vars, id, flag);
            }
        }
        for (i = 0; i < 14; i++) {
            s32 id = secondList[i];
            if (id != -1) {
                ApplySettingToMobyByIndex(obj, id, vars, flag);
            }
        }
    }
}
