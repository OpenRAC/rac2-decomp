#include "common.h"

typedef struct YeedilEffectState {
    char pad00[0x30];
    int mode;
    int frame;
    char pad38[0x154];
    char *first;
    int unused190;
    char *second;
} YeedilEffectState;
extern YeedilEffectState D_L20_001BDCC0;
extern int D_L20_001A8F00[] __attribute__((sda));
extern void func_0032C700(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void func_0029FCC0(void *, int, void *);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002A77E0(int);
extern void func_002BE278(void *, void *, int, float);

extern void *func_0029EFD0(int);

extern float func_002A89A8(void *, int, float);

extern void func_002833F0(void *, void *);

/* Updates a spark-spraying effect (moby class 3882) during a Yeedil scene. At a set moment it fires a burst, then it keeps
 * shooting sparks from a scene object while the scene runs. */
void func_L20_0039AA98(unsigned char *object)
{
    float position[4], velocity[4];
    float speed, heading, tilt;
    YeedilEffectState *state;

    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xFF;
        object[0x20] = 1;
        break;
    case 1:
        if (D_L20_001A8F00[0] != 2)
            break;
        state = &D_L20_001BDCC0;
        if (state->mode != 7)
            break;
        if (state->frame == 157)
            SpawnExplosion(state->second + 0x10, 1, 40, 20, 30, 40, 50, 1,
                          1, 1, 0, 0, 1.5f, 20.0f);
        if ((unsigned int)(state->frame - 171) < 149) {
            TransformMobyJointToWorld(state->first, 0, position);
            position[2] += 0.03f;
            speed = RandomFloatRange(0.028333336114883423f, 0.05000000447034836f);
            heading = RandomAngle();
            tilt = RandomFloatRange(0.523598849773407f, 2.6179940700531006f);
            BuildSphericalOffset(velocity, speed, heading, tilt);
            if (RandomIntBelow(2))
                SpawnWhiteFlashParticle(position, velocity, 0, RandomFloatRange(1470.0f, 7350.0f));
        }
        break;
    }
}

/* func_L20_002DEBE0 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */

/* func_L20_00310E38 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */

extern unsigned char D_L20_001DBA60[];

extern void *D_L20_001DB100[];

extern void func_0029F390(void *);

extern void func_002A0F48(void *);

/* Turns a moby into another class: copies the new class settings (animation, size, collision) from the class tables. */
void func_L20_00330A68(void *moby, int classId)
{
    unsigned char *typeData;
    unsigned char *typeData2;
    unsigned char *typeData3;
    int extraValue;

    *(short *)(moby + 0xAA) = (short)classId;
    *(unsigned char *)(moby + 0x22) = D_L20_001DBA60[(short)classId];
    *(void **)(moby + 0x24) = D_L20_001DB100[*(unsigned char *)(moby + 0x22)];
    update_moby_animation_state(moby);
    typeData = *(unsigned char **)(moby + 0x24);
    *(unsigned char *)(moby + 0x62) = typeData[0xE];
    *(float *)(moby + 0x2C) = *(float *)(typeData + 0x24);
    *(int *)(moby + 0x98) = *(int *)(typeData + 0x10);
    *(unsigned char *)(moby + 0x61) = 0xFF;
    if (typeData) {
        extraValue = *(int *)(typeData + 0x40);
        if (extraValue) {
            *(unsigned short *)(moby + 0x34) |= 0x10;
            *(int *)(moby + 0x78) = *(int *)(typeData + 0x40);
        }
        typeData2 = *(unsigned char **)(moby + 0x24);
        if (typeData2[0xF]) {
            *(unsigned char *)(moby + 0x6F) = 0x18;
            *(unsigned short *)(moby + 0x34) |= 0x400;
            *(int *)(moby + 0x70) = 0;
            *(int *)(moby + 0x74) = 0;
            *(unsigned char *)(moby + 0xBD) = 0;
        }
        typeData3 = *(unsigned char * volatile *)(moby + 0x24);
        if (typeData3[6]) {
            *(unsigned char *)(moby + 0x63) = 0x18;
        }
    }
    func_002A0F48(moby);
}

/* Catalogue defect: the row's first two words (0x0036AE68 `sw $t3,0x40($v1)` /
   `nop`) sit after the previous function's `jr $ra` (0x0036AE5C) and are
   unreachable; the eight bytes at 0x0036AE70 (`addiu $sp,$sp,0x20` / `nop`)
   are the stub row this level's splitter cuts out of a function (74 of them
   in level 20, e.g. at 0x00308688), so the real body starts at 0x0036AE78
   and is 272 bytes: a leaf function with no frame, no saved register and
   `jr $ra` at 0x0036AF80.  It reaches data through $gp twice (0x0036AF0C
   and 0x0036AF58, both `lw $a0,-0x4800($gp)` -> 0x001AA7F0), so it belongs
   in the -G8 unit once the row is split. */
/* func_L20_0036AE68 is defined in L20_0036AE68-g8.c (it reads its list through $gp). */

extern void func_L00_002F3478(void);

extern void func_002B49E0(int a, int b, int c, int d, int e);

extern int D_L20_001FFE40[];

extern int D_L20_001A8FDC __attribute__((sda));

extern int D_L20_00294F98;

/* Sets up a Yeedil scene: runs the common setup, stores a scene table and starts the scene. */
void func_L20_0036E720(void)
{
    int *base;
    int *other;

    ClearFirstLevelTableEntry();
    base = D_L20_001FFE40;
    other = &D_L20_00294F98;
    *(int *)(base + 0x40) = (int)other;
    *(int *)(base + 0x41) = 0xB;
    D_L20_001A8FDC = 1;
    BeginSlotRequest(3, 1, 0xB, 0, 0);
}

/* Creates the glowing effect object (moby class 4802) on an owner at a given spot and hands back the new object. */
char *func_L20_0039BDF0(void *owner, void *position, int param1, int param2)
{
    char *effect;
    int posAddr;
    int zeroAddr;
    char *ownerRef;

    effect = (char *)CreateMoby(0x12C2 /* moby class 4802 */);
    if (effect) {
        *(int *)(effect + 0xB8) = (int)owner;
        *(unsigned char *)(effect + 0x30) = 0xFF;
        posAddr = (int)effect + 0x10;
        qcopy((void *)posAddr, position);
        *(int *)(owner + 0x98) = 0;
        *(float *)(effect + 0x18) = *(float *)(effect + 0x18) + 2.0f;
        *(float *)(effect + 0x18) = ProbeGroundHeightBelow((void *)posAddr, 0, 0.5f);
        ownerRef = *(char **)(effect + 0xB8);
        *(int *)(ownerRef + 0x98) = *(int *)(*(int *)(ownerRef + 0x24) + 0x10);
        zeroAddr = (int)effect + 0xF0;
        qzero_nc((void *)zeroAddr);
        euler_rotation_basis((void *)((int)effect + 0xC0), (void *)((int)effect + 0xF0));
        {
            int *vars = *(int **)(effect + 0x68);
            vars[1] = param1;
            vars[2] = param2;
        }
    }
    return effect;
}


/* func_L20_0039BB18 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */

/* func_L20_0039BEC8 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */
