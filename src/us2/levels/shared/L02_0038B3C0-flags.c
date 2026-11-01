#include "include_asm.h"

#include "common.h"
extern int D_001A79F0[] __attribute__((sda));
extern char *D_L02_001B35A8[] __attribute__((sda));
extern int D_L02_001AEC78 SDATA(D_L02_001AEC78);
extern int D_L02_001B30C8[] __attribute__((sda));
extern unsigned char D_001A7A6E __attribute__((nosda));
extern unsigned char D_001A7A75 __attribute__((nosda));
extern int D_L02_001A903C __attribute__((nosda));
extern void func_002A7750(void *, int, int);
extern void func_002E5E58(int, int, int);
extern void func_US2_002B1880(int, int);

void func_US2_L02_0038B458(unsigned char *object) {
    int state = object[0x20];
    switch (state) {
    case 2:
        break;
    case 0:
        object[0x30] = 0xFF;
        if (D_001A79F0[0] == 2) {
            char *entry;
            int kind;
            for (entry = D_L02_001B35A8[0]; entry; entry = *(char **)(entry + 0x28)) {
                kind = *(short *)(entry + 0xAA);
                if ((kind == 0xA9C || kind == 0xD0D || kind == 0xAA4 || kind == 0xE93 || kind == 0x1259) && *(float *)(entry + 0x18) < 400.0f)
                    ++D_L02_001AEC78;
            }
        } else if (D_001A79F0[0] == 3) {
            char *entry;
            int kind;
            int n;
            entry = D_L02_001B35A8[0];
            if (entry) {
                n = D_L02_001AEC78;
                do {
                    kind = *(unsigned short *)(entry + 0xAA);
                    if ((unsigned)(kind - 0xF37) < 2 || (short)kind == 0xF3E)
                        ++n;
                    entry = *(char **)(entry + 0x28);
                } while (entry);
                D_L02_001AEC78 = n;
            }
        }
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (D_001A79F0[0] == 2) {
            if (D_L02_001B30C8[0] == 2) D_L02_001AEC78 = 0x71;
            if (D_L02_001AEC78 >= 11 || D_001A7A6E) return;
            D_001A7A6E = state;
            func_002E5E58(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L02_001A903C = state;
        } else if (D_001A79F0[0] == 3) {
            if (D_L02_001B30C8[0] == 2) D_L02_001AEC78 = 0x70;
            if (D_L02_001AEC78 >= 12 || D_001A7A75) return;
            D_001A7A75 = state;
            func_002E5E58(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L02_001A903C = state;
        }
        break;
    }
}
