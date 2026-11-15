#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern char D_00189E20[];
extern char *D_L19_001B1EAC __attribute__((sda));
extern float D_L19_001B1E94 __attribute__((sda));
extern float D_L19_001B1E98 __attribute__((sda));
extern float D_L19_001B1E9C __attribute__((sda));
extern float D_L19_001B1EA4 __attribute__((sda));
extern float D_L19_001B1EA8 __attribute__((sda));
extern int D_L19_001B258C;
extern char D_L19_001B9A40[];

extern int func_002ACBC8(char *, int);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, char *);
extern char *func_L00_002D70A0(int);
extern void func_L00_002D7140(char *);
extern void func_00282CF0(char *, float *, char *);

/* Per-frame update of the carried-object marker: arms it, tracks a linked flag, and while the hero is in state 0x31 places and sizes the marker from the grabbed object's bounds. */
void func_L19_00422A98(char *obj) {
    float a[4];
    float b[4];
    char *hero_ptr;

    int *link = FLD(obj, int *, 0x68);

    switch (FLD(obj, u8, 0x20)) {
    case 0:
        D_L19_001B1EAC = 0;
        FLD(obj, u8, 0x20) = 1;
        FLD(obj, u8, 0x30) = 0xFF;
        return;
    case 1:
        if (link[0] != -1) {
            if (IsPointInCuboid(D_L19_001B9A40, link[0]) != 0) {
                D_L19_001B258C = 2;
            } else if (D_L19_001B258C == 2) {
                D_L19_001B258C = 0;
            }
        }
        break;
    default:
        return;
    }
    if (FLD(D_00189E20, int, 0x2294) == 0x31 && (hero_ptr = FLD(D_00189E20, char *, 0x1830)) != 0) {
        func_002AF000(a, D_L19_001B1E94, FLD(hero_ptr, float, 0xF8), -FLD(hero_ptr, float, 0xF4) * 0.5f);
        FastVecAdd(b, a, FLD(D_00189E20, char *, 0x1830) + 0x10);
        if (D_L19_001B1EAC == 0) {
            D_L19_001B1EAC = func_L00_002D70A0(5);
            if (D_L19_001B1EAC == 0) {
                return;
            }
        }
        if (FLD(FLD(D_00189E20, char *, 0x1830), s16, 0xAA) == 0x905) {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E98;
            FLD(D_L19_001B1EAC, float, 0xC) = -1.0f;
            FLD(D_L19_001B1EAC, float, 8) = -1.0f;
        } else {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E9C;
            FLD(D_L19_001B1EAC, float, 0xC) = D_L19_001B1EA4;
            FLD(D_L19_001B1EAC, float, 8) = D_L19_001B1EA8;
        }
        FLD(D_L19_001B1EAC, u8, 0x1F) = 1;
        FastVecSub(D_L19_001B1EAC + 0x20, b, D_L19_001B9A40);
        return;
    }
    if (D_L19_001B1EAC != 0) {
        func_L00_002D7140(D_L19_001B1EAC);
        D_L19_001B1EAC = 0;
    }
}
