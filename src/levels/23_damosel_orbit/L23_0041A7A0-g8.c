/* func_L23_0041A7A0 is a unit of its own: it mixes $gp and absolute accesses to the same globals
 * (MACRO_ADDR declarations), which would conflict with the declarations in L23_00416388-g8.c. */

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_L23_001B3788 MACRO_ADDR;
extern float D_L23_001B378C MACRO_ADDR;
extern float D_L23_001B159C __attribute__((sda));
extern float D_L23_001B15A0 __attribute__((sda));
extern int D_L23_001B15A4 __attribute__((sda));
extern int D_L23_001B150C __attribute__((sda));
extern int D_L23_001B1560 __attribute__((sda));
extern int D_L23_001B1418 __attribute__((sda));
extern float D_L23_001B1598 __attribute__((sda));
extern short D_L23_001B146C __attribute__((sda));
extern float D_L23_001B1578 __attribute__((sda));
extern float D_L23_001B157C __attribute__((sda));
extern float D_L23_001B1500 __attribute__((sda));
extern float D_L23_001B1504 __attribute__((sda));
extern float D_L23_001B1508 __attribute__((sda));
extern unsigned char D_L23_001B1510 __attribute__((sda));
extern unsigned char D_L23_001B1514 __attribute__((sda));
extern float D_L23_001B1518 __attribute__((sda));
extern float D_L23_001B151C __attribute__((sda));
extern float D_L23_001B1520 __attribute__((sda));
extern float D_L23_001B1524 __attribute__((sda));
extern short D_L23_001B1528 __attribute__((sda));
extern short D_L23_001B152C __attribute__((sda));
extern int D_L23_001B1530 __attribute__((sda));
extern int D_L23_001B1534 __attribute__((sda));
extern unsigned char D_L23_001B1538 __attribute__((sda));
extern unsigned char D_L23_001B153C __attribute__((sda));
extern float D_L23_001B1540 __attribute__((sda));
extern float D_L23_001B1544 __attribute__((sda));
extern float D_L23_001B1548 __attribute__((sda));
extern float D_L23_001B154C __attribute__((sda));
extern short D_L23_001B1550 __attribute__((sda));
extern short D_L23_001B1554 __attribute__((sda));
extern int D_L23_001B1558 __attribute__((sda));
extern int D_L23_001B155C __attribute__((sda));
extern Quad D_L23_001B37A0 MACRO_ADDR;
extern Quad D_L23_001B37B0[4] MACRO_ADDR;
extern Quad D_L23_001B3760 MACRO_ADDR;
extern char *D_L23_001B3790[4] MACRO_ADDR;
extern float D_L23_001B36A4;
extern char *D_L23_00259380[8][3];
extern int D_L23_00259320[8][3];
extern Quad D_L23_002593E0[8][3];
struct PlayerView {
    unsigned char pad[0x80];
    Quad position;
    unsigned char gap[0x2200];
    char *object;
};
extern struct PlayerView D_00189E20;
extern int func_00282948(int *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, char *);
extern void func_L23_0041E290(char *);
extern void func_00291450(int);
extern void func_L23_0041A648(char *);
extern float func_002A7878(float, float);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_L23_00418650(char *, float);
extern float func_00283B98(float, float);
extern void func_002833F0(char *, char *);
extern void func_00283738(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_L23_0041AFE8(char *, char *, char *, Quad *, int *);
extern void func_0029FCC0(char *, int, char *);
extern void *func_L23_004256F0(unsigned char *, unsigned char *, unsigned char *, unsigned char, unsigned char, short, short, float, float, float, float, int, int, int, int, int);
extern float func_00282E48(char *, char *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_L23_0041E5B0(unsigned char *, int, int, Quad *, float *, int);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002A7820(int, int);
extern int func_002761F8(void *, void *, int, void *, void *);

/* Update the radial field, its linked effects and player contact response. */
void func_L23_0041A7A0(char *object) {
    struct {
        Quad vertex[8], scaled[2], axes[3], euler, matrix[3], blast, position;
    } local;
    struct HitView {
        Quad result;
        char *owner;
        unsigned int flags;
        unsigned char kind, mode;
        unsigned short ownerClass;
        float radius;
        int value;
    } hit;
    char *state = *(char **)(object + 0x68);
    float x, y, z, random;
    int i, j, contactIndex;
    if (*(int *)(state + 0x5B0) == 0) {
        D_L23_001B378C = D_L23_001B159C;
        D_L23_001B15A0 = FloatAbs(D_L23_001B15A0);
        D_L23_001B3788 = D_L23_001B15A4;
        PlayMobySound(5, 0, object);
    } else {
        if (D_L23_001B3788) {
            FastFloatHelperD(&D_L23_001B3788);
            RestartBossBeamEffect(object);
        } else {
            if (D_L23_001B150C != -1) FreePointLight(D_L23_001B150C);
        }
        if (D_L23_001B3788 < D_L23_001B15A4 / 2) {
            D_L23_001B378C = D_L23_001B378C + D_L23_001B15A0;
            if (D_L23_001B1598 < D_L23_001B378C) D_L23_001B378C = D_L23_001B1598;
        }
    }
    if (D_L23_001B1560) ReleaseBossEffectHandles(object);
    if (D_L23_001B1418 == -1) D_L23_001B1418 = PlayMobySound(1, 4, object);
    if (D_L23_001B1598 * 0.5f < D_L23_001B378C) {
        char *joint;
        if (D_L23_001B146C != -1) FreePointLight(D_L23_001B146C);
        joint = state + 0x3E0;
        x = RandomFloatRange(0.0f, 0.5f) + 0.7f;
        y = RandomFloatRange(0.0f, 0.5f) + 1.0f;
        z = RandomFloatRange(0.0f, 0.55f) + 1.0f;
        D_L23_001B146C = AllocateEffectSlot_L00_2(joint, 35.0f, 0.0f, x, y, z);
    }
    *(int *)(state + 0x5B0) = 1;
    qcopy_nc(&D_L23_001B37A0,object+16);
    ProjectPointOntoPlanetSurface((char *)&D_L23_001B37A0, D_L23_001B157C);
    qcopy_nc(&local.axes[0],(object + 0xC0));
    qcopy_nc(&local.axes[1],(object + 0xD0));
    qcopy_nc(&local.axes[2],(object + 0xE0));
    random = RandomFloatRange(0.98f, 1.02f);
    *(float *)(state + 0x380) = FastAddRotations(*(float *)(state + 0x380), D_L23_001B1578 * random * 0.00029088825f);
    qzero_nc(&local.euler);
    ((float *)&local.euler)[2] = *(float *)(state + 0x380);
    euler_rotation_basis((char *)local.matrix, (char *)&local.euler);
    multiply_matrix3x3((char *)local.axes, (char *)local.axes, (char *)local.matrix);
    qcopy_nc(&local.scaled[0],&local.axes[0]);
    qcopy_nc(&local.scaled[1],&local.axes[1]);
    FastVecScale((char *)&local.scaled[0], (char *)&local.scaled[0], D_L23_001B36A4);
    FastVecScale((char *)&local.scaled[1], (char *)&local.scaled[1], D_L23_001B36A4);
    qcopy_nc(&local.vertex[0],&local.scaled[0]);
    FastVecScale((char *)&local.vertex[4], (char *)&local.vertex[0], -1.0f);
    FastVecAdd((char *)&local.vertex[1], (char *)&local.scaled[0], (char *)&local.scaled[1]);
    FastVecScale((char *)&local.vertex[1], (char *)&local.vertex[1], 0.5f);
    qcopy_nc(&local.vertex[2],&local.scaled[1]);
    FastVecAdd((char *)&local.vertex[3], (char *)&local.scaled[1], (char *)&local.vertex[4]);
    FastVecScale((char *)&local.vertex[3], (char *)&local.vertex[3], 0.5f);
    FastVecScale((char *)&local.vertex[5], (char *)&local.vertex[1], -1.0f);
    FastVecScale((char *)&local.vertex[6], (char *)&local.vertex[2], -1.0f);
    FastVecScale((char *)&local.vertex[7], (char *)&local.vertex[3], -1.0f);
    for (i = 0; i < 8; i++) {
        FastVecAdd((char *)&local.vertex[i], (char *)&local.vertex[i], (char *)&D_L23_001B37A0);
        ProjectPointOntoPlanetSurface((char *)&local.vertex[i], D_L23_001B157C);
        SpawnFieldBeamSegments(object, (char *)&D_L23_001B37A0, (char *)&local.vertex[i], D_L23_002593E0[i], D_L23_00259320[i]);
    }
    for (i = 0; i < 4; i++) {
        TransformMobyJointToWorld(object, i + 26, (char *)&D_L23_001B37B0[i]);
        if (!D_L23_001B3790[i]) D_L23_001B3790[i] = CreateRibbonTrail(
            (unsigned char *)&D_L23_001B37A0, (unsigned char *)object, (unsigned char *)&D_L23_001B37B0[i],
            D_L23_001B1538, D_L23_001B153C, D_L23_001B1550, D_L23_001B1554,
            D_L23_001B1540, D_L23_001B1544, D_L23_001B1548, D_L23_001B154C, D_L23_001B1558, D_L23_001B155C, 0, -1, 0);
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 3; j++) {
            if (!D_L23_00259380[i][j]) {
                if (i == 0) D_L23_00259380[0][j] = CreateRibbonTrail(
                    (unsigned char *)&D_L23_002593E0[7][j], (unsigned char *)object, (unsigned char *)&D_L23_002593E0[0][j],
                    D_L23_001B1510, D_L23_001B1514, D_L23_001B1528, D_L23_001B152C,
                    D_L23_001B1518, D_L23_001B151C, D_L23_001B1520, D_L23_001B1524, D_L23_001B1530, D_L23_001B1534, 1, -1, 1);
                else D_L23_00259380[i][j] = CreateRibbonTrail(
                    (unsigned char *)&D_L23_002593E0[i - 1][j], (unsigned char *)object, (unsigned char *)&D_L23_002593E0[i][j],
                    D_L23_001B1510, D_L23_001B1514, D_L23_001B1528, D_L23_001B152C,
                    D_L23_001B1518, D_L23_001B151C, D_L23_001B1520, D_L23_001B1524, D_L23_001B1530, D_L23_001B1534, 1, -1, 1);
            }
        }
    }
    if (D_L23_001B378C != D_L23_001B1598) return;
    if (fast_vec_dist((char *)&gHeroState.position, (char *)&D_L23_001B3760) < D_L23_001B1500) {
        if ((*(float *)(state + 0x5C0) < D_L23_001B1504) && !*(int *)(state + 0x5C4)) {
            FastVecScale((char *)&local.blast, gHeroState.object + 0xE0, 3.0f);
            FastVecAdd((char *)&local.blast, (char *)&local.blast, (char *)&gHeroState.position);
            SpawnExplosion(&local.blast, 1, 35, 20, 20, 15, 25, 1, 2.5f, 20.0f, 0, 1, 0, 0);
            local.position = *(Quad *)(object + 16);
            PlayEffectOnTarget((unsigned char *)object, 3, (int)D_L23_001B1508, &local.position, 0, 1);
            *(int *)(state + 0x5C4) = 25;
            PlaySoundFromClassBank(2, 0, gHeroState.object, 0xF7F);
        }
    }
    if (*(int *)(state + 0x5C4)) FastFloatHelperD((int *)(state+0x5C4));
    i = RandomIntRange(1, 4);
    if ((*(unsigned short *)(object + 0x96) & ((1U << i) - 1)) == 0) {
        hit.owner = object;
        hit.flags = 0x8B0000;
        hit.radius = 10.0f;
        hit.value = 0;
        hit.kind = 3;
        hit.mode = 3;
        hit.ownerClass = *(unsigned short *)(object + 0xAA);
        /* contactIndex + -1, not - 1: the negative index wraps in sizetype, so table-16 stays its own
         * constant and cse does not rebuild it from the table address (use_related_value). */
        for (contactIndex = 1; contactIndex < 3; contactIndex++) {
            CollLine(&D_L23_002593E0[0][contactIndex + -1], &D_L23_002593E0[0][contactIndex], 0, 0, &hit);
        }
    }
}
