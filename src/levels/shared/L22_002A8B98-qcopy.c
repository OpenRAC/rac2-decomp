#include "common.h"

extern char D_00189E20[];
extern s32 D_001A8F00[] __attribute__((sda));

extern void func_0029F338(s32);
extern void func_0028B6C8(s32, s32);
extern void func_L00_002A53B8(void);
extern int func_0028B3D0(s32, s32, void *, void *, void *, s32, s32);
extern int func_L00_002F6B90(s32);
extern void func_L00_002A6708(void);
extern void func_L00_002D24B8(void);
extern s32 func_L00_002A4DB0(char *, s32, s32, char *);
extern int func_L22_002C9898(s32, s32);
extern char D_00302FD0[];
extern char D_00302F80[];
extern char D_003026B0[];
extern char D_001B46C0[];
extern char D_001B4CC0[];

/* Resets the hero for a restart: drops the held objects, replays the entry sequence and rebinds the player's moby. */
void func_L22_002B7328(void)
{
    char *hero = D_00189E20;
    char *hero2, *hero3;
    char *moby, *from;
    s32 mode;

    if (*(unsigned char *)(hero + 0x22B4) == 1) {
        *(s32 *)(hero + 0x24D0) = *(s32 *)(hero + 0x24CC);
        *(s32 *)(hero + 0x24CC) = *(short *)(hero + 0x24D4);
        if (*(s32 *)(hero + 0x1860) != 0) {
            func_0029F338(*(s32 *)(hero + 0x1860));
            *(s32 *)(hero + 0x1860) = 0;
        }
        if (*(s32 *)(hero + 0x1864) != 0) {
            func_0029F338(*(s32 *)(hero + 0x1864));
            *(s32 *)(hero + 0x1864) = 0;
        }
    }
    hero2 = D_00189E20;
    if (*(unsigned char *)(hero2 + 0x22B4) == 2) {
        if (*(short *)(hero2 + 0x1878) != -1) {
            set_animation_parameter(*(short *)(hero2 + 0x1878), 0);
            *(short *)(hero2 + 0x1878) = -1;
        }
    }
    func_L00_002A53B8();
    hero3 = D_00189E20;
    *(unsigned char *)(hero3 + 0x22B4) = 0;
    func_0028B3D0(0x23, 0, D_00302FD0, D_00302F80, D_003026B0, 0, 0);
    func_L00_002F6B90(3);
    if (*(char **)(hero3 + 0xC14) != 0)
        *(unsigned short *)(*(char **)(hero3 + 0xC14) + 0x34) &= 0xFFF9;
    *(s32 *)(hero3 + 0xC14) = 0;
    func_L00_002A6708();
    moby = *(char **)(hero3 + 0xC18);
    from = hero3 + 0x80;
    *(char **)(hero3 + 0x2290) = moby;
    qcopy(moby + 0x10, from);
    *(s32 *)(moby + 0x9C) = 0;
    *(float *)(hero3 + 0xC24) = 1.0f;
    func_L00_002D24B8();
    if (*(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x42) != 0xFF)
        *(s32 *)(*(char **)(hero3 + 0x2290) + 0x58) = func_L00_002A4DB0(*(char **)(hero3 + 0x2290), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x42), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x40), D_001B46C0);
    *(s32 *)(*(char **)(hero3 + 0x2290) + 0x5C) = func_L00_002A4DB0(*(char **)(hero3 + 0x2290), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x43), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x41), D_001B4CC0);
    if (*(s32 *)(hero3 + 0x2294) != 0x61 || ((mode = D_001A8F00[0]) != 2 && mode != 6))
        func_L22_002C9898(0, 1);
}
