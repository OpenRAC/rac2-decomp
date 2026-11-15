#include "common.h"

extern char D_00189EA0[];
extern char *D_L16_001B2B1C;

extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(char *, int);
extern int func_002A8508(int, int);

/* Waits for its linked object or trigger, then wakes the eight targets it lists. */
void func_L16_0041C990(char *obj) {
    int *p = *(int **)(obj + 0x68);
    int i;
    char *first;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (p[1] == -1 && p[2] == -1) {
            func_002A7750(obj, 4, -1);
        } else if (p[1] != -1) {
            func_002A7750(obj, 1, -1);
        } else {
            func_002A7750(obj, 2, -1);
        }
        break;
    case 1:
        first = D_L16_001B2B1C + (p[0] << 8);
        if (first == 0 || *(u8 *)(first + 0x20) == 0xFE || *(u8 *)(first + 0x20) == 0xFD) {
            if (IsPointInCuboid(D_00189EA0, p[1]) != 0) {
                for (i = 0; i < 8; i++) {
                    if (p[4 + i] != -1) {
                        char *entry = D_L16_001B2B1C + (p[4 + i] << 8);
                        if (*(s16 *)(entry + 0xAA) == 0xEA3) {
                            *(int *)(*(char **)(entry + 0x68) + 0x24C) = 1;
                        } else {
                            *(u8 *)(entry + 0xBC) = 1;
                        }
                    }
                }
                func_002A7750(obj, 4, -1);
            }
        }
        break;
    case 2:
        if (func_002A8508(p[2], -1) == 0) {
            for (i = 0; i < 8; i++) {
                if (p[4 + i] != -1) {
                    char *entry = D_L16_001B2B1C + (p[4] << 8);
                    if (*(s16 *)(entry + 0xAA) == 0xEA3) {
                        *(int *)(*(char **)(entry + 0x68) + 0x24C) = 1;
                    } else {
                        *(u8 *)(entry + 0xBC) = 1;
                    }
                }
            }
            func_002A7750(obj, 4, -1);
        }
        break;
    case 3:
    case 4:
        break;
    }
}
