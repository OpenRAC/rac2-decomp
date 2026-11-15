#include "common.h"

/* A moby class header, as far as func_L10_00417CE0 writes it. */
typedef struct {
    u8 pad00[0x24];
    f32 scale;                  /* 0x24: default scale */
    u8 pad28[0x3C - 0x28];
    f32 f3C;                    /* 0x3C */
    u8 pad40[0x48 - 0x40];
    f32 *f48;                   /* 0x48 */
} MobyClass;

/* The moby, as far as func_L10_00417CE0 reads it. */
typedef struct {
    u8 pad00[0x10];
    f32 position[4];            /* 0x10 */
    u8 pad20[0x24 - 0x20];
    MobyClass *mclass;          /* 0x24 */
    u8 pad28[0x2C - 0x28];
    f32 scale;                  /* 0x2C */
    u8 updateDistance;          /* 0x30 */
    u8 pad31;
    u16 drawDistance;           /* 0x32 */
    u16 flags;                  /* 0x34 */
    u8 pad36[0x68 - 0x36];
    void *vars;                 /* 0x68: the instance data */
    u8 pad6C[0xC0 - 0x6C];
    f32 rotation[3][4];         /* 0xC0: rows of the rotation matrix */
} Moby;

/* A joint manipulator, as RAC1's Manipulator: func_0029F978 attaches it to a joint of a
   moby, whose transform it then sets. */
typedef struct {
    u8 joint;                   /* 0x00 */
    u8 attached;                /* 0x01 */
    u8 scaleOn;                 /* 0x02 */
    u8 absolute;                /* 0x03 */
    s32 jointId;                /* 0x04 */
    void *next;                 /* 0x08: the moby's next manipulator */
    f32 interp;                 /* 0x0C */
    f32 rotation[4];            /* 0x10: a quaternion (func_L10_00418088) */
    f32 scale[4];               /* 0x20 */
    f32 translation[4];         /* 0x30 */
} Manipulator;

/* The instance data of the moby that carries the class 0xF86 mobies. */
typedef struct {
    u8 pad000[0x2F0];
    Manipulator manips[4];      /* 0x2F0: two per side, side 1 first */
} CarrierVars;

/* The instance data of a class 0xF86 moby. */
typedef struct {
    f32 aim[4];                 /* 0x00: aim direction (func_L10_00418088) */
    Moby *parent;               /* 0x10 */
    s32 side;                   /* 0x14 */
    Moby *follower;             /* 0x18: the class 0x134F moby that follows it */
} AttachedVars;

extern void func_00282C88(void *);
extern Moby *func_0029EFD0(s32 oClass);
extern void func_00283360(void *);
extern void func_0029FCC0(Moby *moby, s32 joint, f32 *position);
extern void func_0029F978(Moby *moby, s32 joint, Manipulator *manip);
extern void func_002A0F48(Moby *moby);

typedef int TI128 __attribute__((mode(TI)));

extern u8 *func_002ED688(u8 *);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);

extern void func_00283098(void *, void *, void *);
extern void func_0029FC20(u8 *, s32, void *);
extern f32 func_00282E48(void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_002831B0(f32);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern u8 D_L10_001B9680[];

extern u32 *func_0037BA88(u8 *arg0);
extern s32 func_003351C0(s32 mode);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern void func_0037BD88(u8 *arg0, u32 flags, s32 a, s32 b, s32 c, s32 d, s32 e,
                          f32 f0, f32 f1, f32 f2, f32 f3);
extern void func_0037CCB0(u8 *arg0, s32 a1);
extern void func_0032CBD0(u8 *arg0, s32 *a1, s32 *a2, s32 *a3);
extern void func_0032CBA0(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern f32 func_00335320(void);
extern void func_L10_00417F30(u8 *arg0);
extern void func_L10_00418088(u8 *arg0);
extern u8 *func_0037B670();
extern void func_0037BC48(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_003062A0(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_00335200(s32 a0, s32 a1);
extern void func_0032BD98(s32 a0, u8 *a1);
extern void func_0032AF78(s32 a0);
extern void func_00308BB8(f32 *a0, u8 *a1, f32 f12);
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern void func_003098F8(f32 *a0, f32 *a1);
extern void func_003096D8(u8 *a0, f32 *a1, u8 *a2);
extern void func_00308B30(u8 *a0, u8 *a1, u8 *a2);
extern void func_00335258(f32 f12, f32 f13);
extern void func_0033D090(u8 *a0, f32 f12, f32 f13, f32 f14);
extern void func_00373410(s32 a0);
extern void func_L10_004184F0(u8 *arg0);
extern void func_L10_00418588(u8 *arg0);
extern void func_L10_004189D8(u8 *arg0);
extern void func_L10_00418AD8(u8 *arg0);
extern void func_L10_00418BA0(u8 *arg0);
extern int func_L00_00367720(void);
extern void func_L00_003FC100(void);
extern void func_L05_00379E60(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L05_0037B538(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_002E5DA0(s32 index, s32 value, u8 *object, s32 kind);
extern void func_00308AF8(u8 *a0);
extern void func_0037DFB8(u8 *a0);
extern void func_0037D7A0(u8 *a0, s32 a1, f32 f12);
extern s32 func_0037D6E0(u8 *a0);
extern void func_0037D528(u8 *a0);

extern u8 *D_L10_0020B1E0[];
extern u8 *D_001B251C;
extern u8 D_L10_00265BA0[];
extern u8 D_L10_00188660[];
extern u8 D_L10_00221CD0[];
extern u8 D_00188660[];
extern s32 D_001B0F44 __attribute__((sda));
extern s32 D_001B0F48 __attribute__((sda));


/* func_L10_003170D0 is in L10_003170D0-scene-g8.c. */

/* func_L10_00317528 is in L10_003170D0-scene.c. */

#define NOT_SDA __attribute__((section(".data")))

extern void *r1_D_0012F86C_0037CC20 NOT_SDA;

/* rac1-decomp src/core/001138A8.c: func_001138A8 */
/* Returns a small number that the boss code uses to scale how fierce the boss is. */
int func_L10_0037CC20(void) {
    return (int)r1_D_0012F86C_0037CC20;
}



/* Sets up the beam moby: starts it in state 1, always drawn, and scaled up from its class. */
void func_L10_003F6110(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *heroInfo = (u8 *)func_0037BA88(moby);

    *(s32 *)(heroInfo + 0x148) = 2;
    func_0037CCB0(moby, 1);
    *(f32 *)(vars + 0x180) = 2.0f;
    moby[0x20] = 1;
    moby[0x30] = 0xFF;
    *(u16 *)(moby + 0x32) = 0x1FF;
    *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x100;
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * 4.1f;
    *(s32 *)(heroInfo + 0x14C) = 0;
    *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
}

/* func_L10_003F61C8 is in L10_003170D0-beam.c. */

/* func_L10_00415A50 is in L10_003170D0-f7-g8.c. */

/* func_L10_004166E8 is in L10_004166E8-g8-dbg.c. */

/* Sets up the Hrugis boss: starts it in state 1, always drawn, and resets its bobbing
   speeds, carried objects and timers. */
void func_L10_00417040(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    *(s32 *)((u8 *)func_0037BA88(moby) + 0x148) = 0x1E;
    func_0037CCB0(moby, 1);
    *(f32 *)(vars + 0x180) = 30.0f;
    moby[0x20] = 1;
    moby[0x30] = 0xFF;
    *(u16 *)(moby + 0x32) = 0x1FF;
    *(f32 *)(vars + 0x2BC) = func_00335320();
    *(f32 *)(vars + 0x2B8) = *(f32 *)(moby + 0x18);
    *(s32 *)(vars + 0x2C0) = 0;
    *(s32 *)(vars + 0x2C4) = 0;
    *(s32 *)(vars + 0x2C8) = 0;
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * 6.4f;
    *(s32 *)(vars + 0x2E4) = 0x21C;
    *(s32 *)(vars + 0x2D0) = 0;
    *(s32 *)(vars + 0x2CC) = 0;
    *(u16 *)(moby + 0x7C) = 0xFF;
}

/* func_L10_004170F8 is in L10_003170D0-path-g8.c. */

/* func_L10_004174C8 is in L10_003170D0-g8.c: it only comes out right with -G8. */

/* Changes how fast the boss sways: faster while in state 1, slower while in state 2. */
void func_L10_004175C8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 1:
        *(f32 *)(vars + 0x2CC) = *(f32 *)(vars + 0x2CC) + 3.87851e-05f;
        *(f32 *)(vars + 0x2D0) = *(f32 *)(vars + 0x2D0) + 3.87851e-05f;
        if (*(f32 *)(vars + 0x2CC) > 0.023271061f)
            *(f32 *)(vars + 0x2CC) = 0.023271061f;
        if (*(f32 *)(vars + 0x2D0) > 0.011635531f)
            *(f32 *)(vars + 0x2D0) = 0.011635531f;
        break;
    case 2:
        *(f32 *)(vars + 0x2CC) = *(f32 *)(vars + 0x2CC) - 5.8177648e-05f;
        *(f32 *)(vars + 0x2D0) = *(f32 *)(vars + 0x2D0) - 5.8177648e-05f;
        if (*(f32 *)(vars + 0x2CC) < 0.0f)
            *(f32 *)(vars + 0x2CC) = 0.0f;
        if (*(f32 *)(vars + 0x2D0) < 0.0f)
            *(f32 *)(vars + 0x2D0) = 0.0f;
        break;
    }
}



/* func_L10_00417A38 uses the profile in L10_003170D0-qcopy.c. */

/* Update of a hanging object carried by the boss. It copies the position of its parent and
   aims its joints at the target when the boss is active. */
void func_L10_00417C40(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u32 state = moby[0x20];
    s32 jointA, jointB, jointC;
    u8 *heroInfo;

    switch (state) {
    case 0:
        moby[0x20] = 1;
        /* fall through */
    case 1:
        func_0032CBD0(*(u8 **)(vars + 0x10), &jointA, &jointB, &jointC);
        func_0032CBA0(moby, jointA, jointB, jointC);
        break;
    default:
        return;
    }
    UpdateAttachedObjectTransform(moby);
    heroInfo = (u8 *)func_0037BA88(*(u8 **)(vars + 0x10));
    if (*(s32 *)(heroInfo + 0x120) != 0)
        AimHangingObjectJoints(moby);
}

/* Creates the class 0xF86 moby that hangs from parent on the given side, with a class
   0x134F moby following it. The parent's two manipulators for that side take the new
   moby's joint 0 and 1 positions, made local (joint 1 relative to joint 0) and in model
   units, and are attached to those joints. Returns the new moby, or 0. */
Moby *func_L10_00417CE0(Moby *parent, s32 side)
{
    CarrierVars *parentVars = parent->vars;
    Moby *moby = CreateMoby(0xF86 /* moby class 3974 */);
    AttachedVars *vars;
    Manipulator *first;
    Manipulator *second;
    MobyClass *mclass;

    if (moby != 0) {
        vars = moby->vars;
        moby->updateDistance = 0xFF;
        moby->drawDistance = 0x1FF;
        moby->flags |= 0x100;
        vars->parent = parent;
        vars->side = side;
        mclass = moby->mclass;
        moby->scale = mclass->scale * 0.8f;
        mclass->f48[3] = 18855.0f;
        mclass->f3C = 18855.0f;
        set_identity_rotation_rows(moby->rotation);

        if (side) {
            first = &parentVars->manips[0];
            second = &parentVars->manips[1];
        } else {
            first = &parentVars->manips[2];
            second = &parentVars->manips[3];
        }
        TransformMobyJointToWorld(moby, 0, first->translation);
        TransformMobyJointToWorld(moby, 1, second->translation);
        FastVecSub(first->translation, first->translation, moby->position);
        FastVecSub(second->translation, second->translation, moby->position);
        FastVecSub(second->translation, second->translation, first->translation);
        FastVecScale(first->translation, first->translation, (1.0f / moby->scale) * 1024.0f);
        FastVecScale(second->translation, second->translation, (1.0f / moby->scale) * 1024.0f);
        AttachManipulator(moby, 0, first);
        AttachManipulator(moby, 1, second);
        first->translation[3] = 1.0f;
        first->interp = 1.0f;
        first->absolute = 1;
        second->translation[3] = 1.0f;
        second->interp = 1.0f;
        second->absolute = 1;

        UpdateAttachedObjectTransform((u8 *)moby);
        func_002A0F48(moby);
        ClearVector128(vars->aim);
        vars->aim[0] = 1.0f;

        vars->follower = CreateMoby(0x134F /* moby class 4943 */);
        if (vars->follower != 0) {
            MobyClass *followerClass = vars->follower->mclass;

            followerClass->f48[3] = 18855.0f;
            followerClass->f3C = 18855.0f;
            vars->follower->updateDistance = 0xFF;
            vars->follower->drawDistance = 0x1FF;
            vars->follower->flags |= 0x100;
            vars->follower->scale = 16.0f;
        }
    }
    return moby;
}


/* Copies the parent's position and turn onto this object, then onto the object that
   follows it. */
void func_L10_00417F30(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *follower;
    s32 mode = *(s32 *)(vars + 0x14);
    f32 axis[4];
    f32 matrix[12];

    if (mode != 0) {
        if (mode == 1) {
            u8 *parent = *(u8 **)(vars + 0x10);
            qcopy(moby + 0xC0, parent + 0xC0);
            qcopy(moby + 0xD0, parent + 0xD0);
            qcopy(moby + 0xE0, parent + 0xE0);
            qcopy(moby + 0x10, parent + 0x10);
        }
    } else {
        u8 *parent = *(u8 **)(vars + 0x10);
        func_00308BB8(axis, parent + 0xC0, func_00309138(1.5707963705062866f));
        axis[3] = func_00309120(1.5707963705062866f);
        func_003098F8(axis, matrix);
        func_003096D8(moby + 0xC0, matrix, *(u8 **)(vars + 0x10) + 0xC0);
        qcopy(moby + 0x10, *(u8 **)(vars + 0x10) + 0x10);
    }
    follower = *(u8 **)(vars + 0x18);
    if (follower != 0) {
        qcopy(follower + 0xC0, moby + 0xC0);
        qcopy(follower + 0xD0, moby + 0xD0);
        qcopy(follower + 0xE0, moby + 0xE0);
        qcopy(follower + 0x10, moby + 0x10);
    }
}


/* Turns the two joints of a hanging object so they point at the target, or at the hero when
   the target is too far away. */
void func_L10_00418088(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    f32 xAxis[4] __attribute__((aligned(16)));
    f32 yAxis[4] __attribute__((aligned(16)));
    f32 zAxis[4] __attribute__((aligned(16)));
    f32 quatA[4] __attribute__((aligned(16)));
    f32 quatB[4] __attribute__((aligned(16)));
    f32 matrixA[16] __attribute__((aligned(16)));
    f32 matrixB[16] __attribute__((aligned(16)));
    f32 aimDir[4] __attribute__((aligned(16)));
    f32 temp[4] __attribute__((aligned(16)));
    u8 *heroInfo;
    u8 *manipA, *manipB;
    f32 angle, dotValue;
    *(TI128 *)xAxis = 0; *(TI128 *)yAxis = 0; *(TI128 *)zAxis = 0;
    *(TI128 *)quatA = 0; *(TI128 *)quatB = 0;
    xAxis[0]=1.0f; yAxis[2]=1.0f; zAxis[1]=1.0f; quatA[2]=1.0f; quatB[1]=1.0f;
    heroInfo = (u8 *)GetMobyMotionData(*(u8 **)(state + 0x10));
    if (*(s32 *)(state + 0x14)) {
        manipA = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x2F0;
        manipB = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x330;
    } else {
        manipA = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x370;
        manipB = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x3B0;
    }
    matrix_mul_vec3(xAxis,xAxis,moby+0xC0);
    matrix_mul_vec3(yAxis,yAxis,moby+0xC0);
    matrix_mul_vec3(zAxis,zAxis,moby+0xC0);
    TransformMobyJointPoint(moby,0,matrixA);
    TransformMobyJointPoint(moby,1,matrixB);
    if (fast_vec_dist(matrixA+12, *(u8 **)(heroInfo+0x120)+0x10) <= 24.0f)
        qcopy(aimDir, state);
    else {
        FastVecSub((u8 *)aimDir,D_L10_001B9680,(u8 *)(matrixA+12));
        qcopy(state, aimDir);
    }
    dotValue = FastVecDot(aimDir,yAxis);
    FastVecScale((u8 *)temp,(u8 *)yAxis,dotValue);
    FastVecSub((u8 *)aimDir,(u8 *)aimDir,(u8 *)temp);
    vec_scale_to_length(aimDir,aimDir,1.0f);
    angle = (1.57079637f-FastAngleHelper(FastVecDot(xAxis,aimDir)))*0.5f;
    if (FastVecDot(aimDir,zAxis)>0.0f) angle=-angle;
    FastVecScale(manipA+0x10,(u8 *)quatA,FastSinOrCosB(angle));
    *(f32 *)(manipA+0x1C)=FastSinOrCosA(angle);
    FastVecSub((u8 *)aimDir,D_L10_001B9680,(u8 *)(matrixB+12));
    dotValue = FastVecDot(aimDir,yAxis);
    FastVecScale((u8 *)temp,(u8 *)yAxis,dotValue);
    FastVecSub((u8 *)aimDir,(u8 *)aimDir,(u8 *)temp);
    vec_scale_to_length(aimDir,xAxis,FastVecLength(aimDir));
    FastVecAdd((u8 *)aimDir,(u8 *)temp,(u8 *)aimDir);
    vec_scale_to_length(aimDir,aimDir,1.0f);
    dotValue=FastVecDot(aimDir,yAxis);
    if(dotValue<=-0.3f) dotValue=-0.3f;
    else if(dotValue>0.3f) dotValue=0.3f;
    angle=(1.57079637f-FastAngleHelper(dotValue))*0.5f;
    FastVecScale(manipB+0x10,(u8 *)quatB,-FastSinOrCosB(angle));
    *(f32 *)(manipB+0x1C)=FastSinOrCosA(angle);
}

/* Update step of the cloud object: the state byte at +0x20 picks the step (0 re-arms the
   object and queues its effect, 1 spawns it), and the object's own record in the shared
   table D_00188660 is then looked up before its effect of kind 0xF8D is created. */
void func_L10_00418400(u8 *moby) {
    u8 *self = moby;
    u8 *vars = *(u8 **)(self + 0x68);
    u8 stateByte = self[0x20];
    u8 *record;

    switch (stateByte) {
    case 0:
        self[0x30] = 0xFF;
        if (GetStoredPointerValue() == 0)
            return;
        InitCloudPuffMoby(self);
        if (*(s32 *)(vars + 0x264) != 0)
            AppendLevelObject(self, (s32)EmptyHandler, 0, 0);
        break;
    case 1:
        ProcessObjectCollisionHit(self, 0, 1, 1);
        SpawnLargeTailTrailMarks(self);
        break;
    }
    record = gSoundState + *(s32 *)(vars + 0x268) * 0x70;
    if (*(u8 **)(record + 0x88) == self && record[0x74] != 0)
        return;
    *(s32 *)(vars + 0x268) = PlaySoundFromClassBank(0, 6, self, 0xF8D);
}

/* Sets the cloud puff up: the builder's record gets state 2, the effect is
   started, the object's own state and flags are written and its timer is set. */
/* Sets up the cloud puff: starts it in state 1, always drawn, and gives it a small size. */
void func_L10_004184F0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *heroInfo = (u8 *)func_0037BA88(moby);

    *(s32 *)(heroInfo + 0x148) = 2;
    func_0037CCB0(moby, 1);
    *(s32 *)(vars + 0x268) = -1;
    *(f32 *)(vars + 0x180) = 2.0f;
    moby[0x20] = 1;
    moby[0x30] = 0xFF;
    *(u16 *)(moby + 0x32) = 0x1FF;
    *(u16 *)(moby + 0x34) |= 0x100;
    *(f32 *)(moby + 0x2C) = 0.16f;
}


/* func_L10_00418768 is in L10_00418768.c. */


/* Stops the object's sound effect if it is still playing, and forgets it. */
void func_L10_00418968(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 effectId = *(s32 *)(vars + 0x26C);

    if (effectId != -1) {
        u8 *record = D_L10_00188660 + effectId * 0x70;

        if (*(u8 **)(record + 0x88) == moby && *(u8 *)(record + 0x74) != 0)
            func_00373410(effectId);
    }
    *(s32 *)(vars + 0x26C) = -1;
}

extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern u8 *D_001B2614 __attribute__((sda));

/* Sets up a small flying piece: puts it at a random spot around the chosen marker. */
void func_L10_004189D8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *spot;
    f32 distance, angleA, angleB;

    moby[0x20] = 1;
    *(u16 *)(moby + 0x34) |= 0x100;
    *(s32 *)((u8 *)func_0037BA88(moby) + 0x148) = 10;
    func_0037CCB0(moby, 1);
    spot = D_001B2614 + *(s32 *)D_L10_00221CD0 * 128;
    *(s32 *)(vars + 0x26C) = -1;
    *(f32 *)(vars + 0x180) = 10.0f;
    *(s32 *)(vars + 0x268) = 0;
    *(f32 *)(moby + 0x2C) = 0.04f;
    distance = RandomFloatRange(0.0f, *(f32 *)spot);
    angleA = RandomAngle();
    angleB = RandomAngle();
    BuildSphericalOffset(moby + 0x10, distance, angleA, angleB);
    FastVecAdd(moby + 0x10, spot + 0x30, moby + 0x10);
}

/* arms one timed effect slot and records it in the state word, skipping out while the
   object is inactive */
void func_L10_00418AD8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *heroInfo = (u8 *)func_0037BA88(moby);
    if (heroInfo == 0) return;
    if (*(s32 *)(heroInfo + 0x120) == 0) return;
    if (*(s32 *)(vars + 0x268) != 0) return;
    func_0037BD88(moby, 0x60000080, 1, 0, 0, -1, 0, 0.8f, 2.0f, 1.0f, 1.3f);
    if (func_003351C0(3) != 0) {
        func_003737B8(1, 0, moby, 0xF8E);
    }
    *(s32 *)(vars + 0x268) = 0x1E;
}


extern u32 D_L10_001FB1E0[];
extern u8 *D_001B251C_base[] __asm__("D_001B251C") __attribute__((sda));

/* Sets every moby in the group to state 2. */
void func_L10_00419188(u8 *group)
{
    u32 idList = D_L10_001FB1E0[group[0x21]];
    s16 *idPtr;
    u8 *member;

    if (idList == 0) {
        return;
    }
    idPtr = (s16 *)idList;
    do {
        member = D_001B251C_base[0] + (((*(u16 *)idPtr & 0x7FFF) << 8));
        *(member + 0x20) = 2;
    } while (*idPtr++ >= 0);
}

/* Does nothing. */
void func_L10_004191E0(void)
{
}

extern void func_L10_0041ED50(u8 *arg0);
extern void func_L10_0041EE00(u8 *arg0);
extern void func_L00_00414018(void);
extern s32 func_L00_0042C818(void);
extern u8 *func_002ED688(u8 *arg0);
extern f32 func_002A7940(void);
extern f32 func_00283180(f32 f12);
extern s32 func_00283D38(s32 a0, s32 a1, f32 f12);

/* State 0 waits for func_L00_00367720, then sets the object up (with an optional
   callback pair); state 1 sets flag 0x1000 only in level 10 while
   func_L00_0042C818 is 2, advances the phase at +0x268 by pi/30 and pulses the
   colour at +0x78 with it.  D_001A79F0 is the current level number. */
extern f32 func_00309B38(f32 f12, f32 f13);
extern void func_L10_0041ED50(u8 *arg0);
extern u8 func_L10_00423780(void);
extern s32 func_00283D38(s32 a0, s32 a1, f32 f12);
extern void func_L00_00414018(void);
extern void func_L10_0041EE00(u8 *arg0);
extern s32 D_001A79F0[] __attribute__((sda));

void func_L10_0041EC10(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 phase;
    u8 *heroInfo;
    s32 level;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (func_0037B670() != 0) {
            InitPulsingLightMoby(moby);
            if (*(s32 *)(vars + 0x264) != 0) {
                func_0037BC48(moby, (s32)NoOpCallback_L00, (s32)DrawPulsingGlowAtGroupMobies, 0);
            }
            *(f32 *)(vars + 0x268) = func_00335320();
        }
        break;
    case 1:
        heroInfo = func_0037BA88(moby);
        level = gCurrentMapIndex[0];
        *(s32 *)((u8 *)heroInfo + 0x14C) = 0;
        if (level == 10 && func_L10_00423780() == 2) {
            *(u16 *)(moby + 0x34) |= 0x1000;
        } else {
            *(u16 *)(moby + 0x34) &= 0xEFFF;
        }
        func_0037D390(moby, 0, 0, 0);
        phase = func_00309B38(*(f32 *)(vars + 0x268), 0.10471977f);
        *(f32 *)(vars + 0x268) = phase;
        *(s32 *)(moby + 0x78) = FastTweenColor(0x20202020, -1, (func_00309120(phase) + 1.0f) * 0.5f);
        break;
    }
}

/* Sets up the pulsing light: starts it in state 1, always drawn, and scaled from its class. */
void func_L10_0041ED50(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *heroInfo = (u8 *)func_0037BA88(moby);

    *(s32 *)(heroInfo + 0x148) = 1;
    func_0037CCB0(moby, 1);
    *(s32 *)(heroInfo + 0x14C) = 0;
    *(f32 *)(vars + 0x180) = 1.0f;
    moby[0x30] = 0xFF;
    moby[0x20] = 1;
    *(u16 *)(moby + 0x32) = 0x1FF;
    *(u16 *)(moby + 0x34) |= 0x100;
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * 4.1f;
}


/* func_L10_00421288 is in L10_003170D0-state-g8.c. */

/* func_L10_00421790 is in L10_00421790-g8.c. */

/* func_L10_004227A0 is defined in L10_004227A0-g8.c. */

/* func_L10_00423500 is in L10_003170D0-g8.c. */

/* func_L10_00423788 is in L10_003170D0-collision.c. */

/* func_L10_004239A0 lives in L10_004239A0-g8.c. */

/* func_L10_00423DC8 is in L10_00423DC8-g8.c. */
