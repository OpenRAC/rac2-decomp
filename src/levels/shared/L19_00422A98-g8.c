#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern char g_hero_state[];
extern char *D_L19_001B1EAC __attribute__((sda));
extern float D_L19_001B1E94 __attribute__((sda));
extern float D_L19_001B1E98 __attribute__((sda));
extern float D_L19_001B1E9C __attribute__((sda));
extern float D_L19_001B1EA4 __attribute__((sda));
extern float D_L19_001B1EA8 __attribute__((sda));
extern int D_L19_001B258C;
extern char D_L19_001B9A40[];

extern int IsPointInCuboid(char *, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(float *, float *, char *);
extern char *cam_alloc_override_slot(int);
extern void cam_end_override(char *);
extern void FastVecSub(char *, float *, char *);

/* Per-frame update of the carried-object marker: arms it, tracks markerOffset linked flag, and while the hero is in state 0x31 places and sizes the marker from the grabbed object's bounds. */
void carried_marker_update(char *obj) {
    float markerOffset[4];
    float markerPos[4];
    char *heldObject;

    int *vars = FLD(obj, int *, 0x68);

    switch (FLD(obj, u8, 0x20)) {
    case 0:
        D_L19_001B1EAC = 0;
        FLD(obj, u8, 0x20) = 1;
        FLD(obj, u8, 0x30) = 0xFF;
        return;
    case 1:
        if (vars[0] != -1) {
            if (IsPointInCuboid(D_L19_001B9A40, vars[0]) != 0) {
                D_L19_001B258C = 2;
            } else if (D_L19_001B258C == 2) {
                D_L19_001B258C = 0;
            }
        }
        break;
    default:
        return;
    }
    if (FLD(g_hero_state, int, 0x2294) == 0x31 && (heldObject = FLD(g_hero_state, char *, 0x1830)) != 0) {
        vec_build_spherical_offset(markerOffset, D_L19_001B1E94, FLD(heldObject, float, 0xF8), -FLD(heldObject, float, 0xF4) * 0.5f);
        FastVecAdd(markerPos, markerOffset, FLD(g_hero_state, char *, 0x1830) + 0x10);
        if (D_L19_001B1EAC == 0) {
            D_L19_001B1EAC = cam_alloc_override_slot(5);
            if (D_L19_001B1EAC == 0) {
                return;
            }
        }
        if (FLD(FLD(g_hero_state, char *, 0x1830), s16, 0xAA) == 0x905 /* Glider */) {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E98;
            FLD(D_L19_001B1EAC, float, 0xC) = -1.0f;
            FLD(D_L19_001B1EAC, float, 8) = -1.0f;
        } else {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E9C;
            FLD(D_L19_001B1EAC, float, 0xC) = D_L19_001B1EA4;
            FLD(D_L19_001B1EAC, float, 8) = D_L19_001B1EA8;
        }
        FLD(D_L19_001B1EAC, u8, 0x1F) = 1;
        FastVecSub(D_L19_001B1EAC + 0x20, markerPos, D_L19_001B9A40);
        return;
    }
    if (D_L19_001B1EAC != 0) {
        cam_end_override(D_L19_001B1EAC);
        D_L19_001B1EAC = 0;
    }
}
