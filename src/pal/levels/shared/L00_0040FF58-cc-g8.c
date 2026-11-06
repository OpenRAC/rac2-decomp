/* func_PAL_L00_0040FF58, the PAL copy of func_L00_0040B398: the same C, where scale D_L00_001B2D50[g]. */
#include "common.h"

/* Allocates a record and tags it released-empty; returns it, or zero when the allocation failed. */
typedef struct {
    char reserved00[0x18];
    int active;
    char reserved1C[0x14];
} SettingSlot;

typedef struct {
    float amount;
    float scale;
    int kind;
    float multiplier;
} SettingRow;

typedef struct { SettingRow rows[238]; } SettingsBank;

extern SettingSlot D_L00_00256620[30];
extern SettingsBank D_L00_002592C0;

typedef float Vector[4] __attribute__((aligned(16)));

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
typedef struct ScaleRecord {
    char pad00[0x50];
    float value;
    char pad54[0x8c];
} ScaleRecord;
extern ScaleRecord D_L00_00262570[];

typedef struct PlayerState {
    /* 0x0000 */ char pad0000[0x750];
    /* 0x0750 */ Vector up;
    /* 0x0760 */ Vector forward;
    /* 0x0770 */ char pad0770[0x1b20];
    /* 0x2290 */ char *object;
    /* 0x2294 */ int mode;
    /* 0x2298 */ char pad2298[0x254];
    /* 0x24EC */ short orientation;
} PlayerState;
extern PlayerState D_00189E20;

extern Vector D_L00_001B8FF0[3];   /* camera basis rows */
    /* camera position */
    /* collision hit point */
/* Spawns a projectile (moby 0xED7) from owner at position, aimed at target or along the view. */
extern int func_00282978(void *);
extern void func_L00_0031AA28(void *, void *, void *, void *, void *, float);
extern short D_L00_001B2D40[] __attribute__((sda));
extern short D_L00_001B2D48[] __attribute__((sda));
extern short D_L00_001B2D50[] __attribute__((sda));
extern float D_0018BE30[4];
extern float D_L00_001B100C __attribute__((sda));
extern float D_L00_001B1004 __attribute__((sda));
extern Vector D_L00_002563A0[][10];

void func_PAL_L00_0040FF58(char *object)
{
    Vector p, delta, out, diffs[10];
    char *state = *(char **)(object + 0x68);
    int g, i, j, k, l, n;

    for (g = 0; g < 4; g++) {
        if (func_00282978(&D_L00_001B2D40[g])) {
            D_L00_001B2D48[g] = 0;
            D_L00_001B2D40[g] = (((int)(D_L00_001B2D50[g]) * 5 + 2) / 6);
            qcopy(p, state + 0x30);
            p[0] += func_002A7878(-0.5f, 0.5f);
            p[1] += func_002A7878(-0.5f, 0.5f);
            p[2] += func_002A7878(-0.5f, 0.5f);
            func_00282CF0(delta, p, D_0018BE30);
            func_00282F20(delta, delta, D_L00_001B100C);
            func_00282CC0(delta, p, delta);
            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9)
                    t = 1.0f;
                func_L00_0031AA28(out, D_0018BE30, p, state + 0x40, delta, t);
                qcopy(D_L00_002563A0[g][i], out);
            }
        } else {
            for (j = 1; j < 10; j++) {
                func_00282CF0(diffs[j], D_L00_002563A0[g][j], (&((Vector *)D_L00_002563A0)[g * 10 + j])[-1]);
                diffs[j][0] += func_002A78D8(0.0f, 0.05f);
                diffs[j][1] += func_002A78D8(0.0f, 0.05f);
                diffs[j][2] += func_002A78D8(0.0f, 0.05f);
            }
            qcopy(D_L00_002563A0[g][0], D_0018BE30);
            for (k = 1; k < 10; k++)
                func_00282CC0(D_L00_002563A0[g][k], (&((Vector *)D_L00_002563A0)[g * 10 + k])[-1], diffs[k]);
        }
        for (l = 2; l < 9; l++) {
            qcopy(p, D_L00_002563A0[0][l]);
            p[0] += func_002A78D8(0.0f, D_L00_001B1004);
            p[1] += func_002A78D8(0.0f, D_L00_001B1004);
            p[2] += func_002A78D8(0.0f, D_L00_001B1004);
            qcopy(D_L00_002563A0[1][l], p);
        }
        for (n = 2; n < 9; n++) {
            qcopy(p, D_L00_002563A0[0][n]);
            p[0] += func_002A78D8(0.0f, D_L00_001B1004);
            p[1] += func_002A78D8(0.0f, D_L00_001B1004);
            p[2] += func_002A78D8(0.0f, D_L00_001B1004);
            qcopy(D_L00_002563A0[2][n], p);
        }
        for (i = 2; i < 9; i++) {
            qcopy(p, D_L00_002563A0[0][i]);
            p[0] += func_002A78D8(0.0f, D_L00_001B1004);
            p[1] += func_002A78D8(0.0f, D_L00_001B1004);
            p[2] += func_002A78D8(0.0f, D_L00_001B1004);
            qcopy(D_L00_002563A0[3][i], p);
        }
    }
}
