#include "include_asm.h"

#include "common.h"
extern void func_L01_003EE8E0(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002A7398(char *, int, int);
extern int func_00282948(char *);
extern const int D_L01_001B0D10 __attribute__((sda));
extern const int D_L01_001B0D14 __attribute__((sda));
extern int func_00282948(char *);

/* brings the ring out of the ground, then lets it spin and hand itself over */
void func_PAL_L01_003F2FCC(char *a0)
{
    char *s1;

    s1 = *(char **)(a0 + 0x68);
    func_L01_003EE8E0(a0);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(float *)(a0 + 0x18) = *(float *)(a0 + 0x18) + 1.0f;
        *(float *)(s1 + 0x14) = *(float *)(a0 + 0xF0);
        *(unsigned char *)(a0 + 0x20) = 1;
        if (*(unsigned char *)(a0 + 0x43) != 0)
            func_PAL_002A7E68(a0, 0, 0, 0xA);
        *(int *)(s1 + 0x50) = 0;
        *(unsigned short *)(a0 + 0x34) |= 0x1000;
        break;
    case 1:
        if ((*(unsigned char *)(a0 + 0x60) & 2) != 0) {
            if (*(unsigned char *)(a0 + 0x43) != 0)
                func_002A7398(a0, 0, 0);
        }
        if (*(unsigned char *)(a0 + 0xBC) == 0)
            break;
        *(unsigned short *)(a0 + 0x34) &= 0xEFFF;
        func_002A7398(a0, 1, 0);
        if (*(int *)(s1 + 0x0) != 0) {
            *(int *)(s1 + 0x10) = 8;
            *(unsigned char *)(a0 + 0x20) = 2;
            *(int *)(s1 + 0xC) = ((s32)(*(int *)(s1 + 0x4)) * 5 + 2) / 6;
        } else {
            *(unsigned char *)(a0 + 0x20) = 2;
            *(int *)(a0 + 0x78) = D_L01_001B0D14;
            *(int *)(s1 + 0xC) = 0;
        }
        break;
    case 2:
        if (*(int *)(s1 + 0x0) != 0) {
            if (func_00282948(s1 + 0x10) != 0) {
                if (*(int *)(a0 + 0x78) == D_L01_001B0D10)
                    *(int *)(a0 + 0x78) = D_L01_001B0D14;
                else
                    *(int *)(a0 + 0x78) = D_L01_001B0D10;
                *(int *)(s1 + 0x10) = 8;
            }
            if (func_00282948(s1 + 0xC) != 0)
                *(unsigned char *)(a0 + 0xBC) = 0;
        }
        if ((*(unsigned char *)(a0 + 0x60) & 2) != 0) {
            if (*(unsigned char *)(a0 + 0x43) == 1)
                func_002A7398(a0, 2, 0);
        }
        if (*(unsigned char *)(a0 + 0xBC) != 0)
            break;
        if ((*(unsigned char *)(a0 + 0x60) & 2) != 0) {
            *(unsigned short *)(a0 + 0x34) |= 0x1000;
            func_002A7398(a0, 3, 0);
            *(unsigned char *)(a0 + 0x20) = 1;
            *(int *)(a0 + 0x78) = D_L01_001B0D10;
        }
        break;
    }
}
