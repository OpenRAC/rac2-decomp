#include "common.h"
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern unsigned char *D_L00_001B1E9C __attribute__((sda));
extern void func_002A7750(char *, int, int);
extern void func_002B0A68(char *, int, void *, unsigned char, float, float, float, float);
extern void func_002E5CF8(int, int, char *);
extern void func_0029F338(char *);

void func_L00_003827E0(char *obj) {
    char *child;
    char *table;
    unsigned int value;
    union { TI128 q; float f[4]; } words;

    child = *(char **)(obj + 0x68);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_002A7750(obj, 1, -1);
        return;
    case 1:
        if (*(int *)(child + 4) > 0 && *(int *)(child + 8) > 0) {
            table = D_L00_001B1E9C + (*(int *)(child + 4) << 8);
            if (table == 0 || (value = *(unsigned char *)(table + 0x20)) == 0xFE || value == 0xFD) {
                func_002A7750(obj, 2, -1);
            } else {
                table = D_L00_001B1E9C + (*(int *)(child + 8) << 8);
                if (table == 0 || (value = *(unsigned char *)(table + 0x20)) == 0xFE || value == 0xFD) func_002A7750(obj, 2, -1);
            }
        }
        return;
    case 2:
        words.q = 0;
        words.f[1] = 0.10000001f;
        func_002B0A68(obj, 1, &words, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, obj);
        func_0029F338(obj);
        return;
    default:
        return;
    }
}
