#include "include_asm.h"

#include "common.h"
extern char *D_L02_001B359C __attribute__((sda));
extern char *D_L02_001FC060[];
extern int func_002A8508(int, int);
extern float func_00283B98(float, float);
extern u32 func_L01_0031BC68(float, u32, u32);
extern void func_002A0468(void *, u32, int, int, int);
extern u8 *D_L02_001B359C_tbl[] __asm__("D_L02_001B359C") __attribute__((sda));
extern float func_00283B98(float, float);

/* Advances the group's pulse phase by pi/30, tints every moby of the object's group
   (and the child of each 0x873 moby) blue in state 7 or dim otherwise, then sets the
   pulsing color between COLOR1 and COLOR2 on the group's 0xAF9-0xAFD, 0xB03 and 0x873
   mobys. */
void func_PAL_L02_003C8FB0(char *obj, u32 color1, u32 color2) {
    char *vars = *(char **)(obj + 0x68);
    u16 *list;
    char *moby;
    char *child;

    if (func_002A8508(*(u8 *)(obj + 0x21), -1) < 2)
        return;
    list = (u16 *)D_L02_001FC060[*(u8 *)(obj + 0x21)];
    *(float *)(vars + 0x128) = func_00283B98(*(float *)(vars + 0x128), 0.12566373f);
    do {
        moby = D_L02_001B359C + ((*list & 0x7FFF) << 8);
        if (*(u8 *)(obj + 0x20) == 7) {
            if (*(short *)(moby + 0xAA) != 0x896) {
                func_002A0468(moby, func_L01_0031BC68(*(float *)(vars + 0x128), 0x5050DD, 0x505050),
                              14, 14, 14);
                if (*(short *)(moby + 0xAA) == 0x873) {
                    child = *(char **)(moby + 0x68);
                    func_002A0468(*(void **)(child + 0x1C),
                                  func_L01_0031BC68(*(float *)(vars + 0x128), 0x5050DD, 0x505050),
                                  14, 14, 14);
                }
            }
        } else if (*(short *)(moby + 0xAA) != 0x896) {
            func_002A0468(moby, 0x505010, 14, 14, 14);
            if (*(short *)(moby + 0xAA) == 0x873)
                func_002A0468(*(void **)(*(char **)(moby + 0x68) + 0x1C), 0x505010, 14, 14, 14);
        }
        if (*(short *)(moby + 0xAA) == 0xAF9 || *(short *)(moby + 0xAA) == 0xAFA ||
            *(short *)(moby + 0xAA) == 0xAFB || *(short *)(moby + 0xAA) == 0xAFD ||
            *(short *)(moby + 0xAA) == 0xAFC || *(short *)(moby + 0xAA) == 0xB03 ||
            *(short *)(moby + 0xAA) == 0x873) {
            if (*(short *)(moby + 0xAA) == 0x873) {
                child = *(char **)(moby + 0x68);
                *(u32 *)(*(char **)(child + 0x1C) + 0x78) =
                    func_L01_0031BC68(*(float *)(vars + 0x128), color1, color2);
            } else {
                *(u32 *)(moby + 0x78) = func_L01_0031BC68(*(float *)(vars + 0x128), color1, color2);
            }
        }
    } while ((short)*list++ >= 0);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L02_003C91F0);

