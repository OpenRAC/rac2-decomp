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
int func_L10_0037CC20(void) {
    return (int)r1_D_0012F86C_0037CC20;
}



void func_L10_003F6110(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    u8 *s2 = (u8 *)func_0037BA88(arg0);

    *(s32 *)(s2 + 0x148) = 2;
    func_0037CCB0(arg0, 1);
    *(f32 *)(s1 + 0x180) = 2.0f;
    arg0[0x20] = 1;
    arg0[0x30] = 0xFF;
    *(u16 *)(arg0 + 0x32) = 0x1FF;
    *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) | 0x100;
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*(u8 **)(arg0 + 0x24) + 0x24) * 4.1f;
    *(s32 *)(s2 + 0x14C) = 0;
    *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) & 0xEFFF;
}

/* func_L10_003F61C8 is in L10_003170D0-beam.c. */

INCLUDE_ASM("asm/levels", func_L10_00415A50);

/* func_L10_004166E8 is in L10_004166E8-g8-dbg.c. */

void func_L10_00417040(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);

    *(s32 *)((u8 *)func_0037BA88(arg0) + 0x148) = 0x1E;
    func_0037CCB0(arg0, 1);
    *(f32 *)(s1 + 0x180) = 30.0f;
    arg0[0x20] = 1;
    arg0[0x30] = 0xFF;
    *(u16 *)(arg0 + 0x32) = 0x1FF;
    *(f32 *)(s1 + 0x2BC) = func_00335320();
    *(f32 *)(s1 + 0x2B8) = *(f32 *)(arg0 + 0x18);
    *(s32 *)(s1 + 0x2C0) = 0;
    *(s32 *)(s1 + 0x2C4) = 0;
    *(s32 *)(s1 + 0x2C8) = 0;
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*(u8 **)(arg0 + 0x24) + 0x24) * 6.4f;
    *(s32 *)(s1 + 0x2E4) = 0x21C;
    *(s32 *)(s1 + 0x2D0) = 0;
    *(s32 *)(s1 + 0x2CC) = 0;
    *(u16 *)(arg0 + 0x7C) = 0xFF;
}

/* func_L10_004170F8 is in L10_003170D0-path-g8.c. */

/* func_L10_004174C8 is in L10_003170D0-g8.c: it only comes out right with -G8. */

void func_L10_004175C8(u8 *arg0) {
    u8 *s = *(u8 **)(arg0 + 0x68);

    switch (arg0[0x20]) {
    case 1:
        *(f32 *)(s + 0x2CC) = *(f32 *)(s + 0x2CC) + 3.87851e-05f;
        *(f32 *)(s + 0x2D0) = *(f32 *)(s + 0x2D0) + 3.87851e-05f;
        if (*(f32 *)(s + 0x2CC) > 0.023271061f)
            *(f32 *)(s + 0x2CC) = 0.023271061f;
        if (*(f32 *)(s + 0x2D0) > 0.011635531f)
            *(f32 *)(s + 0x2D0) = 0.011635531f;
        break;
    case 2:
        *(f32 *)(s + 0x2CC) = *(f32 *)(s + 0x2CC) - 5.8177648e-05f;
        *(f32 *)(s + 0x2D0) = *(f32 *)(s + 0x2D0) - 5.8177648e-05f;
        if (*(f32 *)(s + 0x2CC) < 0.0f)
            *(f32 *)(s + 0x2CC) = 0.0f;
        if (*(f32 *)(s + 0x2D0) < 0.0f)
            *(f32 *)(s + 0x2D0) = 0.0f;
        break;
    }
}



/* func_L10_00417A38 uses the profile in L10_003170D0-qcopy.c. */

void func_L10_00417C40(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    u32 st = arg0[0x20];
    s32 a, b, c;
    u8 *v;

    switch (st) {
    case 0:
        arg0[0x20] = 1;
        /* fall through */
    case 1:
        func_0032CBD0(*(u8 **)(s1 + 0x10), &a, &b, &c);
        func_0032CBA0(arg0, a, b, c);
        break;
    default:
        return;
    }
    func_L10_00417F30(arg0);
    v = (u8 *)func_0037BA88(*(u8 **)(s1 + 0x10));
    if (*(s32 *)(v + 0x120) != 0)
        func_L10_00418088(arg0);
}

/* Creates the class 0xF86 moby that hangs from parent on the given side, with a class
   0x134F moby following it. The parent's two manipulators for that side take the new
   moby's joint 0 and 1 positions, made local (joint 1 relative to joint 0) and in model
   units, and are attached to those joints. Returns the new moby, or 0. */
Moby *func_L10_00417CE0(Moby *parent, s32 side)
{
    CarrierVars *parentVars = parent->vars;
    Moby *moby = func_0029EFD0(0xF86);
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
        func_00283360(moby->rotation);

        if (side) {
            first = &parentVars->manips[0];
            second = &parentVars->manips[1];
        } else {
            first = &parentVars->manips[2];
            second = &parentVars->manips[3];
        }
        func_0029FCC0(moby, 0, first->translation);
        func_0029FCC0(moby, 1, second->translation);
        func_00282CF0(first->translation, first->translation, moby->position);
        func_00282CF0(second->translation, second->translation, moby->position);
        func_00282CF0(second->translation, second->translation, first->translation);
        func_00282D30(first->translation, first->translation, (1.0f / moby->scale) * 1024.0f);
        func_00282D30(second->translation, second->translation, (1.0f / moby->scale) * 1024.0f);
        func_0029F978(moby, 0, first);
        func_0029F978(moby, 1, second);
        first->translation[3] = 1.0f;
        first->interp = 1.0f;
        first->absolute = 1;
        second->translation[3] = 1.0f;
        second->interp = 1.0f;
        second->absolute = 1;

        func_L10_00417F30((u8 *)moby);
        func_002A0F48(moby);
        func_00282C88(vars->aim);
        vars->aim[0] = 1.0f;

        vars->follower = func_0029EFD0(0x134F);
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


void func_L10_00417F30(u8 *arg0)
{
    u8 *s2 = *(u8 **)(arg0 + 0x68);
    u8 *q;
    s32 st = *(s32 *)(s2 + 0x14);
    f32 v[4];
    f32 w[12];

    if (st != 0) {
        if (st == 1) {
            u8 *p = *(u8 **)(s2 + 0x10);
            qcopy(arg0 + 0xC0, p + 0xC0);
            qcopy(arg0 + 0xD0, p + 0xD0);
            qcopy(arg0 + 0xE0, p + 0xE0);
            qcopy(arg0 + 0x10, p + 0x10);
        }
    } else {
        u8 *p = *(u8 **)(s2 + 0x10);
        func_00308BB8(v, p + 0xC0, func_00309138(1.5707963705062866f));
        v[3] = func_00309120(1.5707963705062866f);
        func_003098F8(v, w);
        func_003096D8(arg0 + 0xC0, w, *(u8 **)(s2 + 0x10) + 0xC0);
        qcopy(arg0 + 0x10, *(u8 **)(s2 + 0x10) + 0x10);
    }
    q = *(u8 **)(s2 + 0x18);
    if (q != 0) {
        qcopy(q + 0xC0, arg0 + 0xC0);
        qcopy(q + 0xD0, arg0 + 0xD0);
        qcopy(q + 0xE0, arg0 + 0xE0);
        qcopy(q + 0x10, arg0 + 0x10);
    }
}


void func_L10_00418088(u8 *arg0) {
    u8 *state = *(u8 **)(arg0 + 0x68);
    f32 x[4] __attribute__((aligned(16)));
    f32 y[4] __attribute__((aligned(16)));
    f32 z[4] __attribute__((aligned(16)));
    f32 qa[4] __attribute__((aligned(16)));
    f32 qb[4] __attribute__((aligned(16)));
    f32 ma[16] __attribute__((aligned(16)));
    f32 mb[16] __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    u8 *info;
    u8 *a, *b;
    f32 angle, dot;
    *(TI128 *)x = 0; *(TI128 *)y = 0; *(TI128 *)z = 0;
    *(TI128 *)qa = 0; *(TI128 *)qb = 0;
    x[0]=1.0f; y[2]=1.0f; z[1]=1.0f; qa[2]=1.0f; qb[1]=1.0f;
    info = (u8 *)func_002ED688(*(u8 **)(state + 0x10));
    if (*(s32 *)(state + 0x14)) {
        a = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x2F0;
        b = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x330;
    } else {
        a = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x370;
        b = *(u8 **)(*(u8 **)(state + 0x10) + 0x68) + 0x3B0;
    }
    func_00283098(x,x,arg0+0xC0);
    func_00283098(y,y,arg0+0xC0);
    func_00283098(z,z,arg0+0xC0);
    func_0029FC20(arg0,0,ma);
    func_0029FC20(arg0,1,mb);
    if (func_00282E48(ma+12, *(u8 **)(info+0x120)+0x10) <= 24.0f)
        qcopy(dir, state);
    else {
        func_00282CF0((u8 *)dir,D_L10_001B9680,(u8 *)(ma+12));
        qcopy(state, dir);
    }
    dot = func_00282DB0(dir,y);
    func_00282D30((u8 *)tmp,(u8 *)y,dot);
    func_00282CF0((u8 *)dir,(u8 *)dir,(u8 *)tmp);
    func_00282F20(dir,dir,1.0f);
    angle = (1.57079637f-func_002831B0(func_00282DB0(x,dir)))*0.5f;
    if (func_00282DB0(dir,z)>0.0f) angle=-angle;
    func_00282D30(a+0x10,(u8 *)qa,func_00283198(angle));
    *(f32 *)(a+0x1C)=func_00283180(angle);
    func_00282CF0((u8 *)dir,D_L10_001B9680,(u8 *)(mb+12));
    dot = func_00282DB0(dir,y);
    func_00282D30((u8 *)tmp,(u8 *)y,dot);
    func_00282CF0((u8 *)dir,(u8 *)dir,(u8 *)tmp);
    func_00282F20(dir,x,func_00282DF0(dir));
    func_00282CC0((u8 *)dir,(u8 *)tmp,(u8 *)dir);
    func_00282F20(dir,dir,1.0f);
    dot=func_00282DB0(dir,y);
    if(dot<=-0.3f) dot=-0.3f;
    else if(dot>0.3f) dot=0.3f;
    angle=(1.57079637f-func_002831B0(dot))*0.5f;
    func_00282D30(b+0x10,(u8 *)qb,-func_00283198(angle));
    *(f32 *)(b+0x1C)=func_00283180(angle);
}

/* Update step of the cloud object: the state byte at +0x20 picks the step (0 re-arms the
   object and queues its effect, 1 spawns it), and the object's own record in the shared
   table D_00188660 is then looked up before its effect of kind 0xF8D is created. */
void func_L10_00418400(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 state = s0[0x20];
    u8 *p;

    switch (state) {
    case 0:
        s0[0x30] = 0xFF;
        if (func_L00_00367720() == 0)
            return;
        func_L10_004184F0(s0);
        if (*(s32 *)(s1 + 0x264) != 0)
            func_L05_00379E60(s0, (s32)func_L00_003FC100, 0, 0);
        break;
    case 1:
        func_L05_0037B538(s0, 0, 1, 1);
        func_L10_00418588(s0);
        break;
    }
    p = D_00188660 + *(s32 *)(s1 + 0x268) * 0x70;
    if (*(u8 **)(p + 0x88) == s0 && p[0x74] != 0)
        return;
    *(s32 *)(s1 + 0x268) = func_002E5DA0(0, 6, s0, 0xF8D);
}

/* Sets the cloud puff up: the builder's record gets state 2, the effect is
   started, the object's own state and flags are written and its timer is set. */
void func_L10_004184F0(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    u8 *s0 = (u8 *)func_0037BA88(arg0);

    *(s32 *)(s0 + 0x148) = 2;
    func_0037CCB0(arg0, 1);
    *(s32 *)(s1 + 0x268) = -1;
    *(f32 *)(s1 + 0x180) = 2.0f;
    arg0[0x20] = 1;
    arg0[0x30] = 0xFF;
    *(u16 *)(arg0 + 0x32) = 0x1FF;
    *(u16 *)(arg0 + 0x34) |= 0x100;
    *(f32 *)(arg0 + 0x2C) = 0.16f;
}


/* func_L10_00418768 is in L10_00418768.c. */


void func_L10_00418968(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x68);
    s32 id = *(s32 *)(s0 + 0x26C);

    if (id != -1) {
        u8 *p = D_L10_00188660 + id * 0x70;

        if (*(u8 **)(p + 0x88) == arg0 && *(u8 *)(p + 0x74) != 0)
            func_00373410(id);
    }
    *(s32 *)(s0 + 0x26C) = -1;
}

extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern u8 *D_001B2614 __attribute__((sda));

void func_L10_004189D8(u8 *arg0) {
    u8 *s2 = *(u8 **)(arg0 + 0x68);
    u8 *table;
    f32 a, b, c;

    arg0[0x20] = 1;
    *(u16 *)(arg0 + 0x34) |= 0x100;
    *(s32 *)((u8 *)func_0037BA88(arg0) + 0x148) = 10;
    func_0037CCB0(arg0, 1);
    table = D_001B2614 + *(s32 *)D_L10_00221CD0 * 128;
    *(s32 *)(s2 + 0x26C) = -1;
    *(f32 *)(s2 + 0x180) = 10.0f;
    *(s32 *)(s2 + 0x268) = 0;
    *(f32 *)(arg0 + 0x2C) = 0.04f;
    a = func_002A7878(0.0f, *(f32 *)table);
    b = func_002A7940();
    c = func_002A7940();
    func_002AF000(arg0 + 0x10, a, b, c);
    func_00282CC0(arg0 + 0x10, table + 0x30, arg0 + 0x10);
}

/* arms one timed effect slot and records it in the state word, skipping out while the
   object is inactive */
void func_L10_00418AD8(u8 *arg0) {
    u8 *state = *(u8 **)(arg0 + 0x68);
    u8 *p = (u8 *)func_0037BA88(arg0);
    if (p == 0) return;
    if (*(s32 *)(p + 0x120) == 0) return;
    if (*(s32 *)(state + 0x268) != 0) return;
    func_0037BD88(arg0, 0x60000080, 1, 0, 0, -1, 0, 0.8f, 2.0f, 1.0f, 1.3f);
    if (func_003351C0(3) != 0) {
        func_003737B8(1, 0, arg0, 0xF8E);
    }
    *(s32 *)(state + 0x268) = 0x1E;
}


INCLUDE_ASM("asm/levels", func_L10_00419188);

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

void func_L10_0041EC10(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    f32 f;
    u8 *p;
    s32 mode;

    switch (arg0[0x20]) {
    case 0:
        arg0[0x30] = 0xFF;
        if (func_0037B670() != 0) {
            func_L10_0041ED50(arg0);
            if (*(s32 *)(s1 + 0x264) != 0) {
                func_0037BC48(arg0, (s32)func_L00_00414018, (s32)func_L10_0041EE00, 0);
            }
            *(f32 *)(s1 + 0x268) = func_00335320();
        }
        break;
    case 1:
        p = func_0037BA88(arg0);
        mode = D_001A79F0[0];
        *(s32 *)((u8 *)p + 0x14C) = 0;
        if (mode == 10 && func_L10_00423780() == 2) {
            *(u16 *)(arg0 + 0x34) |= 0x1000;
        } else {
            *(u16 *)(arg0 + 0x34) &= 0xEFFF;
        }
        func_0037D390(arg0, 0, 0, 0);
        f = func_00309B38(*(f32 *)(s1 + 0x268), 0.10471977f);
        *(f32 *)(s1 + 0x268) = f;
        *(s32 *)(arg0 + 0x78) = func_00283D38(0x20202020, -1, (func_00309120(f) + 1.0f) * 0.5f);
        break;
    }
}

void func_L10_0041ED50(u8 *arg0) {
    u8 *s3 = *(u8 **)(arg0 + 0x68);
    u8 *s1 = (u8 *)func_0037BA88(arg0);

    *(s32 *)(s1 + 0x148) = 1;
    func_0037CCB0(arg0, 1);
    *(s32 *)(s1 + 0x14C) = 0;
    *(f32 *)(s3 + 0x180) = 1.0f;
    arg0[0x30] = 0xFF;
    arg0[0x20] = 1;
    *(u16 *)(arg0 + 0x32) = 0x1FF;
    *(u16 *)(arg0 + 0x34) |= 0x100;
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*(u8 **)(arg0 + 0x24) + 0x24) * 4.1f;
}


/* func_L10_00421288 is in L10_003170D0-state-g8.c. */

INCLUDE_ASM("asm/levels", func_L10_00421790);

INCLUDE_ASM("asm/levels", func_L10_004227A0);

INCLUDE_ASM("asm/levels", func_L10_00423500);

/* func_L10_00423788 is in L10_003170D0-collision.c. */

INCLUDE_ASM("asm/levels", func_L10_004239A0);

/* func_L10_00423DC8 is in L10_00423DC8-g8.c. */
