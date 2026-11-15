#include "names.h"
extern unsigned char *D_L05_001B2528;
extern void func_0029F338(void *);

/* Retire each active object belonging to this effect family. */
void func_L05_0037B108(void) {
    unsigned char *object = D_L05_001B2528;
    int kind;
    while (object) {
        kind = *(short *)(object + 0xAA);
        if (kind == 0x1173 || kind == 0x12D8 || kind == 0x974 || kind == 0x1161 ||
            kind == 0x1182 || kind == 0x1191 || kind == 0x10F9 || kind == 0x946 ||
            kind == 0x10CF || kind == 0x117C || kind == 0x117D || kind == 0x117F)
            MarkMobySpawned(object);
        object = *(unsigned char **)(object + 0x28);
    }
}
