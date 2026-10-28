/* functional: high. Same calls and stores as retail with the same arguments; only statement order and registers differ. */
#include "common.h"
extern char D_0010FFC0[];
extern unsigned short D_0010FFB0[];
extern char D_00100080[];
extern int D_001B169C;
extern char *D_001B22A8;
extern int D_001B16B4;
extern int D_001B16B0;
extern char *D_001B1B50;
extern int D_001B1B58;
extern int D_001B22AC;
extern int D_001B1B80;
extern int D_001A72D0;
extern int D_001A72D4;
extern void func_002FC410(unsigned int, unsigned int);
extern void func_002FC070(int);
extern void func_002FC560(unsigned int, unsigned long long);

void func_002A0250(void)
{
    char *p;

    func_002FC410((unsigned int)D_0010FFC0, D_0010FFB0[0]);
    D_001B169C = 6;
    func_002FC070((int)D_00100080);
    func_002FC560(0x47, 0x5360B);
    p = D_001B22A8;
    D_001B1B50 = p;
    D_001B22AC = D_001B16B4 + 0xFFFF0000;
    D_001B1B58 = D_001B16B0;
    D_001A72D0 = D_001A72D4;
    D_001B22A8 = p + 0x10;
    D_001B1B80 = 0;
}
