#include "common.h"

extern int func_L01_003165E8(void *, int, int, int, int);
extern int func_001163B0(void);
extern float func_00282E80(void *, void *);
extern int func_002A77E0(int);
extern void func_L01_00337A60(void *, void *,void *,int);
extern int func_002761F8(void *, void *, int, void *, int);
extern char *D_L01_001FE180[];
extern char D_L01_001BF920[];

typedef int TI128 __attribute__((mode(TI)));

typedef struct L01_003BDF28_BUF {
    float x;
    float y;
    int z;
} L01_003BDF28_BUF;

typedef struct L01_003BC490_OBJ {
    char pad[0x10];
    TI128 f10;
} L01_003BC490_OBJ;

typedef struct L01_003BDBB0_OWNED {
    char pad0[0x250];
    void *f250;
    int f254;
} L01_003BDBB0_OWNED;

typedef struct L01_003BDBB0_OBJ {
    char pad0[0x68];
    L01_003BDBB0_OWNED *f68;
} L01_003BDBB0_OBJ;

typedef struct L01_003BE488_OWNED {
    char pad0[0x202];
    short f202;
    int f204;
} L01_003BE488_OWNED;

typedef struct L01_003BE488_OBJ {
    char pad0[0x68];
    L01_003BE488_OWNED *f68;
} L01_003BE488_OBJ;

typedef struct L01_003BFDC8_OBJ {
    char pad0[0x43];
    unsigned char f43;
    char pad1[0x48 - 0x44];
    float f48;
} L01_003BFDC8_OBJ;

extern int func_00282948(void *);

extern void func_00291450(int);

extern float func_002A7878(float, float);

extern void func_002A0F48(char *);

extern void *func_0029EFD0(int);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern char D_00189EA0[];

extern void func_L01_003BDBE8(void *);

extern float func_002A7940(void);

extern int func_002A7820(int, int);

extern void func_L01_0032EF38(void *, int, int, float, float, int);

extern void func_002A7470();

/* Picks a random spot near the moby's home position as its next move target. */
void func_L01_003BDF28(char *moby)
{
    char *mobyPtr = moby;
    char *vars = *(char **)(mobyPtr + 0x68);
    char *targetPos = vars + 0x1E0;
    L01_003BDF28_BUF offset;

    *(float *)(vars + 0x1E0) = FastSinOrCosA(RandomFloatRange(-3.1415927f, 3.1415927f)) * (float)*(unsigned char *)(vars + 0x201);
    *(float *)(vars + 0x1E4) = FastSinOrCosB(RandomFloatRange(-3.1415927f, 3.1415927f)) * (float)*(unsigned char *)(vars + 0x201);
    *(int *)(vars + 0x1E8) = 0;
    FastVecAdd(targetPos, targetPos, vars + 0x1D0);
    *(float *)(vars + 0x1E8) = *(float *)(vars + 0x1E8) + 1.7f;
    if (*(int *)(vars + 0x23C) != 0) {
        FastVecSub(&offset, targetPos, gHeroPosition);
        offset.z = 0;
        vec_scale_to_length(&offset, &offset, 8.0f);
        FastVecAdd(targetPos, targetPos, &offset);
    }
    ChooseWanderDestination(mobyPtr);
}

/* func_L01_003BB9D0 is in L01_003BB9D0-ocean-g8.c. */

/* func_L01_003BBF68 is in L01_003BBF68-g8.c. */


/* func_L01_003BC540 is in L01_003BB9D0-debris-g8.c. */

/* func_L01_003BCA38 is in L01_003BCA38.c. */

/* func_L01_003BCEC8 is in L01_003BB9D0-g8.c. */


/* func_L01_003BD410 */
/* Spawns five small splash particles near the water surface under the moby. */
void func_L01_003BD410(char *moby)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, i;

    state = *(char **)(moby + 0x68);
    for (i = 0; i < 5; i++) {
        angle = RandomAngle();
        radius = RandomFloatRange(0.0f, 0.8f);
        first = RandomFloatRange(0.0f, 1.5f);
        second = RandomFloatRange(1.5f, 5.7f);
        life = RandomIntRange(100, 180);
        position[0] = FastSinOrCosA(angle) * radius;
        position[1] = FastSinOrCosB(angle) * radius;
        position[2] = 0.0f;
        FastVecAdd(position, position, moby + 0x10);
        position[2] = *(float *)(state + 0x224) + 0.025f;
        SpawnGlowParticle_L01(position, 0x38002028, 0x2020, first, second, life);
    }
}



/* func_L01_003BD6B0 is in L01_003BD6B0-g8.c. */

typedef struct {
    char pad0[0x280];
    int f280;
    int f284;
} L01_003BDB28_STATE;

extern void func_002A8598(int, int);

/* Switches on the linked trigger groups of the moby and flags it as triggered. */
void func_L01_003BDB28(char *moby)
{
    L01_003BDB28_STATE *vars = *(L01_003BDB28_STATE **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x21) != 0xFF) {
        SetByteOnGroupMobys(*(unsigned char *)(moby + 0x21), 1);
    }
    if (vars->f280 != -1) {
        SetByteOnGroupMobys(vars->f280, 1);
    }
    if (vars->f284 != -1) {
        SetByteOnGroupMobys(vars->f280, 1);
    }
    *(unsigned char *)(moby + 0xBC) = 1;
}

/* func_L01_003BDBB0 */

/* Gives back the attack slot the moby was using, so another enemy can attack. */
void func_L01_003BDBB0(L01_003BDBB0_OBJ *moby)
{
    L01_003BDBB0_OWNED *vars = moby->f68;

    if (vars->f254 != 0) {
        FastFloatHelperD(vars->f250);
        vars->f254 = 0;
    }
}

/* Chooses where the moby should fly next, keeping the spot clear of walls and away from the moby's own position. */
void func_L01_003BDBE8(void *object)
{
    char *moby = object;
    char *vars = *(char **)(moby + 0x68);
    int index = -1;
    float offset, coordinate;

    if (*(unsigned char *)(moby + 0x20) < 7) {
        index = (*(int *)(vars + 0x214) != -1) ? *(int *)(vars + 0x214) : *(int *)(vars + 0x210);
    } else {
        index = *(int *)(vars + 0x210);
    }
    *(int *)(vars + 0xCC) = index;
    if (!TestPointAgainstShapes(vars + 0x1E0, index, *(int *)(vars + 0x218), *(int *)(vars + 0x21C), -1)) {
        if ((Rand() & 1) || *(int *)(vars + 0x114) != 1 || *(int *)(vars + 0x23C)) {
            if (vec_distance_xy(vars + 0x1E0, moby + 0x10) < 0.5f || !RandomIntBelow(1)) {
                qcopy(vars + 0x1E0, vars + 0x1D0);
                *(float *)(vars + 0x1E8) += 1.7f;
            }
            ClosestPointOnPolygonEdge(vars + 0x1E0, vars + 0x1E0, D_L01_001FE180[index] + 0x10, *(int *)D_L01_001FE180[index]);
        } else {
            *(float *)(vars + 0x1E0) = FastSinOrCosA(RandomFloatRange(-3.1415927f, 3.1415927f)) * 1.2f;
            *(float *)(vars + 0x1E4) = FastSinOrCosB(RandomFloatRange(-3.1415927f, 3.1415927f)) * 1.2f;
            *(int *)(vars + 0x1E8) = 0;
            FastVecAdd(vars + 0x1E0, vars + 0x1E0, gHeroPosition);
            *(float *)(vars + 0x1E8) += 1.7f;
            ClosestPointOnPolygonEdge(vars + 0x1E0, vars + 0x1E0, D_L01_001FE180[index] + 0x10, *(int *)D_L01_001FE180[index]);
        }
        if ((*(int *)(vars + 0x23C) && vec_distance_xy(vars + 0x1E0, gHeroPosition) < 3.0f) || vec_distance_xy(vars + 0x1E0, moby + 0x10) < 0.5f) {
            offset = RandomFloatRange(3.0f, 5.0f);
            coordinate = *(float *)(vars + 0x1E0);
            *(float *)(vars + 0x1E0) = (Rand() & 1) ? coordinate - offset : coordinate + offset;
            offset = RandomFloatRange(3.0f, 5.0f);
            coordinate = *(float *)(vars + 0x1E4);
            *(float *)(vars + 0x1E4) = (Rand() & 1) ? coordinate - offset : coordinate + offset;
        }
    }
    if (CollLine(moby + 0x10, vars + 0x1E0, 2, moby, 0)) {
        FastVecSub(vars + 0x1E0, gCollLineHitPoint, vars + 0x1E0);
        vec_scale_to_length(vars + 0x1E0, vars + 0x1E0, 2.0f);
        FastVecAdd(vars + 0x1E0, vars + 0x1E0, gCollLineHitPoint);
    }
}

/* func_L01_003BE058 is in L01_003BB9D0-steer.c. */

/* func_L01_003BE488 */

/* Turns off the moby's glow light and clears its light slot. */
void func_L01_003BE488(L01_003BE488_OBJ *moby)
{
    L01_003BE488_OWNED *vars = moby->f68;

    if (vars->f202 != -1) {
        vars->f204 = 0;
        FreePointLight(vars->f202);
        vars->f202 = -1;
    }
}

typedef struct L01_003BE4D0_OBJ {
    char pad0[0x20];
    unsigned char f20;
    char pad21[0x68 - 0x21];
    struct L01_003BE4D0_STATE *f68;
    char pad6C[0x96 - 0x6C];
    unsigned short f96;
    char pad98[0xBC - 0x98];
    unsigned char fBC;
} L01_003BE4D0_OBJ;

typedef struct L01_003BE4D0_STATE {
    char pad0[0x114];
    int f114;
    char pad118[0x230 - 0x118];
    int timer230;
    char pad234[0x238 - 0x234];
    int timer238;
    int timer23C;
    char pad240[0x290 - 0x240];
    int f290;
} L01_003BE4D0_STATE;

extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A0488(void *, int, int, int);
extern int func_002E4600(unsigned int, unsigned int, float);

/* Counts down the moby's timers and fades its colour towards the glow colour or back to dark. */
void func_L01_003BE4D0(L01_003BE4D0_OBJ *moby)
{
    L01_003BE4D0_STATE *vars = moby->f68;
    int red, green, blue;
    unsigned int target;
    int color;

    if (moby->fBC != 0) {
        moby->fBC = 0;
        if (vars->timer238 < 200) {
            vars->timer238 = RandomIntRange(300, 360);
        }
    }
    if (vars->f114 != 1) {
        FastFloatHelperD(&vars->timer238);
    }
    if (moby->f96 <= 0xFFFD) {
        moby->f96 = moby->f96 + 1;
    }
    FastFloatHelperD(&vars->timer230);
    FastFloatHelperD(&vars->timer23C);
    /* Pack the current colour as 0x80BBGGRR, then blend it towards the target. */
    get_moby_color(moby, &red, &green, &blue);
    {
        unsigned int alpha_green = (green << 8) | 0x80000000u;
        unsigned int alpha_blue_green = (blue << 16) | alpha_green;
        color = alpha_blue_green | red;
    }
    if (vars->f290 != 0 && moby->f20 < 9) {
        target = 0x8040E0F0;
        color = func_002E4600(color, target, 0.05f);
    } else {
        target = 0x00404040;
        color = func_002E4600(color, target, 0.08f);
    }
    red = color & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = (color >> 16) & 0xFF;
    set_moby_color(moby, red, green, blue);
}

/* func_L01_003BE628 is in L01_003BE628.c. */

/* func_L01_003BFDC8 */

/* Switches the moby to a new animation when it is not already playing it and sets its animation speed. */
void func_L01_003BFDC8(L01_003BFDC8_OBJ *moby, int animIndex, int unusedParam, int blendFrames)
{
    L01_003BFDC8_OBJ *obj = moby;

    if (obj->f43 != animIndex) {
        StartAnimationBlended(moby);
    }
    if (animIndex != 12) {
        obj->f48 = 0.6666667f;
    }
    if ((unsigned int)(animIndex - 6) < 3) {
        obj->f48 = obj->f48 * 1.25f;
    }
}

/* func_L01_003BFE48 is in L01_003BFE48-g8.c. */

/* func_L01_003C01C0 is in L01_003C01C0-g8.c. */

/* func_L01_003C0408 is in L01_003C0408-g8.c. */

/* func_L01_003C08A0 is in L01_003C08A0.c. */


/* func_L01_003C2680 is in L01_003C2680-g8.c. */


/* func_L01_003C97D8 is in L01_003C97D8-draw.c. */

/* func_L01_003C9D00 is in L01_003C9D00.c. */
