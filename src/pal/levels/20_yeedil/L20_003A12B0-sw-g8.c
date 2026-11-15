#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
extern void moby_set_state(char *, int, int);
extern void func_PAL_L20_003A1538(char *);
extern void func_PAL_L20_003A16B8(char *);
extern s32 flag_set_first_pending(char *);
extern void func_PAL_002A7E68(char *, s32, s32, s32);
extern void moby_transform_joint_to_world(char *, s32, char *);
extern void moby_transform_joint_point(char *, s32, char *);
extern void vec_scale_to_length(char *, char *, float);
extern char *func_PAL_L09_003B20E8(char *, char *, char *, s32, s32, float, float, float, float);
extern void FastVecSub(char *, void *, char *);
extern char *func_PAL_0032F3B8(char *, char *, char *, float);
extern void func_PAL_002A7650(char *, s32, s32);
extern void moby_mark_spawned(char *);
extern int D_L20_001A8F00;
extern int D_L20_001BDCF0 __attribute__((nosda));
extern int D_L20_001B2AC8;
extern void *D_L20_001B9FC0[];
extern float D_L20_001AED04 __attribute__((sda));
extern float D_L20_001AED08 __attribute__((sda));
extern u8 D_0019B2E8[] __attribute__((nosda));
extern u8 D_L20_001B2DE0[] __attribute__((nosda));
extern s32 g_current_map_index __attribute__((sda));

void func_PAL_L20_003A12B0(char *arg0)
{
    char bufA[0x10];
    char bufB[0x40];
    char bufC[0x10];
    char *state;

    state = *(char **)(arg0 + 0x68);
    func_PAL_L20_003A1538(arg0);
    if (D_L20_001A8F00 == 2 && D_L20_001BDCF0 >= 5) {
        moby_mark_spawned(arg0);
        return;
    }
    switch (*(u8 *)(arg0 + 0x20)) {
    case 2:
        if (flag_set_first_pending(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 0)
            func_PAL_002A7E68(arg0, 0, 0, 0x8);
        if (*(u8 *)(arg0 + 0x31) != 0 && *(u16 *)(arg0 + 0x96) >= 0x97)
            moby_set_state(arg0, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 1)
            func_PAL_002A7E68(arg0, 1, 0, 0xC);
        if ((D_L20_001B2AC8 & 0xF) == (((int)arg0 >> 8) & 0xF)) {
            moby_transform_joint_to_world(arg0, 2, bufA);
            moby_transform_joint_point(arg0, 2, bufB);
            vec_scale_to_length(bufC, bufB, D_L20_001AED04 * 0.020000001f);
            func_PAL_L09_003B20E8(bufA, arg0, bufC, 1, 1, (float)*(u8 *)(state + 0x34),
                              D_L20_001AED08, 1.0f, 1.0f);
        }
        if (*(u8 *)(arg0 + 0x31) == 0 || *(u16 *)(arg0 + 0x96) >= 0x97)
            moby_set_state(arg0, 2, -1);
        break;
    case 4:
        if (flag_set_first_pending(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 2)
            func_PAL_002A7E68(arg0, 2, 0, 0x8);
        if (*(u8 *)(arg0 + 0x60) & 0x2)
            moby_set_state(arg0, 2, -1);
        break;
    case 5:
        FastVecSub(bufA, D_L20_001B9FC0, arg0 + 0x10);
        vec_scale_to_length(bufA, bufA, 1.0f);
        func_PAL_0032F3B8(arg0, arg0 + 0x10, bufA, 0.0f);
        func_PAL_002A7650(arg0, 0, 3);
        moby_mark_spawned(arg0);
        return;
    default:
        break;
    case 1:
        return;
    }
    func_PAL_L20_003A16B8(arg0);
}
