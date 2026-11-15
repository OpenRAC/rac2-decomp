#include "common.h"

typedef struct {
    f32 rot[4];
    void *parent;
    f32 scale;
    f32 spinAngle;
    f32 spinSpeed;
    f32 sizeFactor;
    s32 extraArg;
} Pvar_3280C8;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[2];
    u8 f23;
    u8 pad24[8];
    f32 size;
    u8 f30;
    u8 f31;
    s16 f32;
    u16 flags;
    u8 pad36[2];
    s64 f38;
    u8 pad40[0x28];
    Pvar_3280C8 *pvar;
} Moby_3280C8;

extern Moby_3280C8 *func_0029EFD0(int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);

/* Spawn class 0xB7F at a position, owned by a parent, with a random spin. */
Moby_3280C8 *func_003280C8(Moby_3280C8 *parent, f32 *rot, f32 *pos, s32 unused, s32 extraValue, f32 scale)
{
    Moby_3280C8 *moby = CreateMoby(0xB7F /* moby class 2943 */);
    if (moby != 0) {
        Pvar_3280C8 *vars;
        moby->f30 = 0xFF;
        moby->f32 = 0xFF;
        moby->f31 = 1;
        moby->state = 0;
        moby->f38 = parent->f38;
        qcopy(moby->pos, pos);
        vars = moby->pvar;
        qcopy(vars->rot, rot);
        vars->parent = parent;
        vars->scale = scale;
        vars->spinAngle = RandomAngle();
        vars->spinSpeed = RandomFloatRange(0.20943955f, 0.6283186f);
        vars->sizeFactor = 1.0f;
        vars->extraArg = extraValue;
        moby->f23 = 0x5D;
        moby->flags |= 0x100;
        moby->size = RandomFloatRange(0.01f, 0.0125f) * vars->sizeFactor;
    }
    return moby;
}
