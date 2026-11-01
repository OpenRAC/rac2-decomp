#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad[0x1A0];
    unsigned int f1A0;
    unsigned int f1A4;
} D00138180_Flags;
extern D00138180_Flags D_00138180;
extern int D_001A79F0;
extern char D_00189E20[];
extern char *D_001B2D1C __attribute__((sda));
extern void func_002A7470(void *, int, int, int);
extern void func_L00_0042A500(int);
extern void func_002B0C28(int, int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L30_003BE678(char *);

void func_US2_L30_003BE9F8(char *object) {
    char *g;
    char *state = *(char **)(object + 0x68);
    int id;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0) {
            *(unsigned char *)(object + 0x20) = 1;
            if (*(unsigned char *)(object + 0x43) != 0)
                func_002A7470(object, 0, 0, 5);
        } else {
            *(unsigned char *)(object + 0x20) = 3;
            if (*(unsigned char *)(object + 0x43) != 2)
                func_002A7470(object, 2, 0, 5);
        }
        break;
    case 1:
        break;
    case 2:
        if (*(unsigned char *)(object + 0x60) & 2) {
            *(unsigned char *)(object + 0x20) = 5;
            if (*(unsigned char *)(object + 0x43) != 2)
                func_002A7470(object, 2, 0, 5);
            if (*(int *)(state + 0xC) != -1)
                func_L00_0042A500(*(int *)(state + 0xC));
        }
        break;
    case 3:
        id = -1;
        if (D_001A79F0 != 0x15 && D_001A79F0 != 0x1E) {
            switch (*(int *)(state + 8)) {
            case 0:
                id = 0x12EE;
                break;
            case 1:
                id = 0x12EF;
                break;
            }
        } else {
            id = 0x133F;
        }
        g = D_00189E20;
        if (*(char **)(g + 0x33C) == object && *(int *)(g + 0x340) != 0) {
            func_002B0C28(8, id, 1);
            if (D_00138180.f1A4 & 0x10) {
                char *s0 = D_001B2D1C + (*(int *)state << 8);

                func_L30_003BE678(s0);
                func_L00_002B9D60(s0 + 0x10, s0 + 0xF0, 0x6F, 1);
                *(unsigned char *)(g + 0x22B5) = 1;
            }
        }
        break;
    case 4:
        break;
    case 5: {
        char *h = D_00189E20;

        if (*(int *)(h + 0x2294) == 0x6F) {
            *(unsigned char *)(h + 0x22B5) = 0;
            func_L00_002B9D60(h + 0x80, h + 0x90, 0, 0);
        }
        *(unsigned char *)(object + 0x20) = 3;
        break;
    }
    }
}
