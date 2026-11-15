#include "common.h"

/* func_0030F7B0: follower state machine (22 states) chasing the hero's
 * targets at 0xAA4/0xAD4/0xB10.  -g gives the pre-div.s nop pair (line
 * label floor); the 5/7 divisor is a conditional move after the call. */

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

typedef struct {
    u8 pad0[0x14];
    u8 *target;
    f32 f18;
    f32 f1C;
    f32 f20;
} FollowVars;

extern char D_00189E20[];
extern u32 D_00138320;

extern unsigned int func_0026F710(int);
extern unsigned int func_0026F748(int, int);
extern void func_0026F768(int, int, float);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_0027CDC8(void (*)(char *), char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7470(void *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern s32 func_00310960(s32 arg0, f32 fparg0);
extern void func_0030F408(char *);


/* Updates the Swingshot each frame. Its hook follows the hero's target, flies out to it, pulls the hero along, and lets go when the swing ends. */
void func_0030F7B0(u8 *self)
{
    FollowVars *vars;
    u8 *hookVars;
    f32 dist;
    f32 v1[4];
    f32 v2[4];

    if (((Hero *)gHeroState)->i[0x2294 / 4] == 1)
        EmptyStubF748(0x1D, 1);
    vars = *(FollowVars **)(self + 0x68);
    if (vars == 0)
        return;
    hookVars = 0;
    if (vars->target == 0) {
        vars->target = (u8 *)SpawnSwingshotHook((s32)self, 0.8000001f);
        if (vars->target == 0)
            goto have;
    }
    hookVars = *(u8 **)(vars->target + 0x68);
have:
    if ((((Hero *)gHeroState)->i[0x2294 / 4] == 1 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x1D) && ((Hero *)gHeroState)->i[0x1B8 / 4] >= 2) {
        AddMobyMarker(self, 1.0f, 0xFF0000FF, 0, 0x24, 0.0f, -1, 90.0f, 4);
        if (((Hero *)gHeroState)->i[0xAA8 / 4] != 0 && ((Hero *)gHeroState)->ptr[0xAA4 / 4] != 0)
            AddMobyMarker(self, 1.4f, 0xFFFF0000, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10, 0x24, 0.0f, -1, 90.0f, 4);
        else if (((Hero *)gHeroState)->ptr[0xAD0 / 4] != 0)
            AddMobyMarker(self, 1.4f, 0xFFFF0000, ((Hero *)gHeroState)->ptr[0xAD0 / 4] + 0x10, 0x24, 0.0f, -1, 90.0f, 4);
    }

    switch (self[0x20]) {
    case 0:
    case 1:
        if (self[0x60] & 2) {
            if (self[0x43] != 1)
                StartAnimationBlended(self, 1, 0, 10);
            self[0x20] = 1;
        }
        if (vars->target != 0) {
            u8 *t;
            TransformMobyJointToWorld(self, 0, vars->target + 0x10);
            t = vars->target;
            *(TI128 *)(t + 0xC0) = *(TI128 *)(self + 0xC0);
            *(TI128 *)(t + 0xD0) = *(TI128 *)(self + 0xD0);
            *(TI128 *)(t + 0xE0) = *(TI128 *)(self + 0xE0);
        }
        if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x23 || (((Hero *)gHeroState)->i[0x229C / 4] == 0xF && ((Hero *)gHeroState)->i[0x684 / 4] != 0)) {
            if (hookVars != 0) {
                vars->f20 = 0.28f;
                vars->f1C = 1.0f;
                vars->f18 = 0.0f;
                *(f32 *)(hookVars + 4) = 0.8000001f;
                if (self[0x43] != 3)
                    StartAnimationBlended(self, 3, 0, 10);
                PlayMobySound(0, 0, (char *)self);
                self[0x20] = 2;
            }
        } else if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x8A) {
            if (hookVars != 0) {
                vars->f20 = 0.28f;
                vars->f1C = 1.0f;
                vars->f18 = 0.0f;
                *(f32 *)(hookVars + 4) = 0.8000001f;
                if (self[0x43] != 3)
                    StartAnimationBlended(self, 3, 0, 10);
                PlayMobySound(0, 0, (char *)self);
                self[0x20] = 0xF;
            }
        } else if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x2B) {
            if (hookVars != 0) {
                f32 d = fast_vec_dist(((Hero *)gHeroState)->ptr[0xAD4 / 4] + 0x10, vars->target + 0x10);
                int n = 7;
                if (((Hero *)gHeroState)->i[0x1240 / 4] <= 0x1D)
                    n = 5;
                *(f32 *)(hookVars + 4) = d / (f32)n;
                vars->f20 = 0.28f;
                vars->f1C = 1.0f;
                vars->f18 = 0.0f;
                if (self[0x43] != 3)
                    StartAnimationBlended(self, 3, 0, 10);
                PlayMobySound(0, 0, (char *)self);
                self[0x20] = 9;
            }
        }
        break;
    case 2:
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        FastVecSub(v1, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10, vars->target + 0x10);
        dist = *(f32 *)(hookVars + 4);
        dist += FastVecLength(&((Hero *)gHeroState)->b[0x150]);
        if (((Hero *)gHeroState)->i[0x229C / 4] == 0xF) {
            dist += ((Hero *)gHeroState)->f[0x644 / 4];
        } else if ((((Hero *)gHeroState)->i[0x22A4 / 4] == 4 || ((Hero *)gHeroState)->i[0x22A4 / 4] == 2) && ((Hero *)gHeroState)->f[0x31C / 4] > 2.0f) {
            dist = 0.8000001f;
        }
        qcopy(v2, &((Hero *)gHeroState)->q[0x80 / 16]);
        v2[2] += 0.5f;
        if (CollLine(v2, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)gHeroState)->f[0x31C / 4] > 0.5f) {
                EmptyStubF748(6, 1);
            } else {
                EmptyStubF748(0, 0);
                EmptyStubF768(EmptyStubF710(0), 0, 14.0f);
            }
            self[0x20] = 6;
        } else if (dist < fast_vec_dist(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10)) {
            vec_scale_to_length(v1, v1, dist);
            FastVecAdd(vars->target + 0x10, vars->target + 0x10, v1);
        } else {
            qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10);
            self[0x20] = 3;
        }
        break;
    case 3:
        PlayMobySound(1, 0, (char *)self);
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10);
        self[0x20] = 4;
        break;
    case 4:
        TransformMobyJointToWorld(self, 0, v1);
        qcopy(v1, &((Hero *)gHeroState)->q[0x80 / 16]);
        v1[2] += 0.5f;
        if (CollLine(v1, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)gHeroState)->h[0x34E / 2] != 0) {
                EmptyStubF748(6, 1);
            } else {
                EmptyStubF748(0, 1);
            }
            self[0x20] = 6;
        } else {
            if ((self[0x60] & 2) && self[0x43] != 4)
                StartAnimationBlended(self, 4, 0, 10);
            RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
            vars->f20 = vars->f20 * 0.9f;
            vars->f18 = vars->f18 + 0.6981318f;
            if (vars->f20 < 0.16800001f) {
                ((Hero *)gHeroState)->i[0x684 / 4] = 0;
                if (vars->target != 0 && fast_vec_dist(vars->target + 0x10, &((Hero *)gHeroState)->q[0x80 / 16]) > 3.5f) {
                    if ((D_00138320 & ((Hero *)gHeroState)->u[0x1230 / 4]) == 0) {
                        ((Hero *)gHeroState)->i[0xAC8 / 4] = 1;
                        EmptyStubF748(0, 0);
                        EmptyStubF768(EmptyStubF710(0), 0, 14.0f);
                        self[0x20] = 6;
                    } else {
                        PlayMobySound(2, 0, (char *)self);
                        if (((Hero *)gHeroState)->i[0xAB8 / 4] != 0) {
                            EmptyStubF748(0x25, 1);
                        } else {
                            EmptyStubF748(0x24, 1);
                        }
                        self[0x20] = 5;
                    }
                } else {
                    EmptyStubF748(0, 1);
                    self[0x20] = 6;
                }
            }
        }
        break;
    case 5:
        qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xAA4 / 4] + 0x10);
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        vars->f20 = vars->f20 * 0.9f;
        vars->f18 = vars->f18 + 0.6981318f;
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        if (((Hero *)gHeroState)->i[0x2294 / 4] != 0x24 && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x25)
            self[0x20] = 6;
        break;
    case 6:
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        *(f32 *)(hookVars + 4) = 1.3333334f;
        self[0x20] = 7;
        break;
    case 7:
        TransformMobyJointToWorld(self, 0, v2);
        FastVecSub(v1, v2, vars->target + 0x10);
        dist = *(f32 *)(hookVars + 4);
        dist += FastVecLength(&((Hero *)gHeroState)->b[0x150]);
        if (dist < fast_vec_dist(vars->target + 0x10, v2)) {
            vec_scale_to_length(v1, v1, dist);
            FastVecAdd(vars->target + 0x10, vars->target + 0x10, v1);
            RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        } else {
            qcopy(vars->target + 0x10, v2);
            if (self[0x43] != 1)
                StartAnimationBlended(self, 1, 0, 10);
            self[0x20] = 1;
        }
        break;
    case 9:
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        FastVecSub(v1, ((Hero *)gHeroState)->ptr[0xAD4 / 4] + 0x10, vars->target + 0x10);
        if (*(f32 *)(hookVars + 4) < FastVecLength(v1)) {
            vec_scale_to_length(v1, v1, *(f32 *)(hookVars + 4));
            FastVecAdd(vars->target + 0x10, vars->target + 0x10, v1);
        } else {
            qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xAD4 / 4] + 0x10);
            self[0x20] = 0xB;
            PlayMobySound(1, 0, (char *)self);
        }
        break;
    case 10:
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        self[0x20] = 0xB;
        break;
    case 11:
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        vars->f20 = vars->f20 * 0.39999998f;
        vars->f18 = vars->f18 + 0.6981318f;
        if (vars->f20 < 0.16800001f) {
            ((Hero *)gHeroState)->h[0xADC / 2] = 1;
            self[0x20] = 0xC;
        }
        break;
    case 12:
        if (((Hero *)gHeroState)->ptr[0xAD4 / 4] != 0)
            qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xAD4 / 4] + 0x10);
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        vars->f20 = vars->f20 * 0.39999998f;
        vars->f18 = vars->f18 + 0.6981318f;
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        if (((Hero *)gHeroState)->i[0x2294 / 4] != 0x2B)
            self[0x20] = 0xD;
        break;
    case 13:
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        *(f32 *)(hookVars + 4) = 1.3333334f;
        self[0x20] = 0xE;
        break;
    case 14:
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        TransformMobyJointToWorld(self, 0, v2);
        FastVecSub(v1, v2, vars->target + 0x10);
        if (*(f32 *)(hookVars + 4) < fast_vec_dist(vars->target + 0x10, v2)) {
            vec_scale_to_length(v1, v1, *(f32 *)(hookVars + 4));
            FastVecAdd(vars->target + 0x10, vars->target + 0x10, v1);
            RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        } else {
            qcopy(vars->target + 0x10, v2);
            if (self[0x43] != 1)
                StartAnimationBlended(self, 1, 0, 10);
            self[0x20] = 1;
        }
        if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x2B && hookVars != 0) {
            *(f32 *)(hookVars + 4) = fast_vec_dist(((Hero *)gHeroState)->ptr[0xAD4 / 4] + 0x10, vars->target + 0x10) * 0.1f;
            vars->f1C = 1.0f;
            vars->f20 = 0.0f;
            vars->f18 = 0.0f;
            if (self[0x43] != 3)
                StartAnimationBlended(self, 3, 0, 10);
            self[0x20] = 9;
        }
        break;
    case 15:
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        qcopy(v1, &((Hero *)gHeroState)->q[0x80 / 16]);
        v1[2] += 0.5f;
        if (CollLine(v1, ((Hero *)gHeroState)->ptr[0xB10 / 4] + 0x10, 2, 0, 0) != 0) {
            if (((Hero *)gHeroState)->f[0x31C / 4] > 0.5f) {
                EmptyStubF748(6, 1);
            } else {
                EmptyStubF748(0, 0);
                EmptyStubF768(EmptyStubF710(0), 0, 14.0f);
            }
            self[0x20] = 0x13;
        } else {
            FastVecSub(v2, ((Hero *)gHeroState)->ptr[0xB10 / 4] + 0x10, vars->target + 0x10);
            if (*(f32 *)(hookVars + 4) < FastVecLength(v2)) {
                vec_scale_to_length(v2, v2, *(f32 *)(hookVars + 4));
                FastVecAdd(vars->target + 0x10, vars->target + 0x10, v2);
            } else {
                qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xB10 / 4] + 0x10);
                self[0x20] = 0x11;
                PlayMobySound(1, 0, (char *)self);
            }
        }
        break;
    case 16:
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        self[0x20] = 0x11;
        break;
    case 17:
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        vars->f20 = vars->f20 * 0.39999998f;
        vars->f18 = vars->f18 + 0.6981318f;
        if (vars->f20 < 0.16800001f) {
            ((Hero *)gHeroState)->i[0xB1C / 4] = 1;
            self[0x20] = 0x12;
        }
        break;
    case 18:
        if (((Hero *)gHeroState)->ptr[0xB10 / 4] != 0)
            qcopy(vars->target + 0x10, ((Hero *)gHeroState)->ptr[0xB10 / 4] + 0x10);
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        vars->f20 = vars->f20 * 0.39999998f;
        vars->f18 = vars->f18 + 0.6981318f;
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        if (((Hero *)gHeroState)->i[0x229C / 4] != 0x21)
            self[0x20] = 0x13;
        break;
    case 19:
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        *(f32 *)(hookVars + 4) = 1.3333334f;
        self[0x20] = 0x14;
        break;
    case 20:
        if ((self[0x60] & 2) && self[0x43] != 4)
            StartAnimationBlended(self, 4, 0, 10);
        TransformMobyJointToWorld(self, 0, v2);
        FastVecSub(v1, v2, vars->target + 0x10);
        if (*(f32 *)(hookVars + 4) < fast_vec_dist(vars->target + 0x10, v2)) {
            vec_scale_to_length(v1, v1, *(f32 *)(hookVars + 4));
            FastVecAdd(vars->target + 0x10, vars->target + 0x10, v1);
            RegisterWorldDrawCallback(DrawWavyLinkStrip_0030F408, (char *)self);
        } else {
            qcopy(vars->target + 0x10, v2);
            if (self[0x43] != 1)
                StartAnimationBlended(self, 1, 0, 10);
            self[0x20] = 1;
        }
        if (((Hero *)gHeroState)->i[0x229C / 4] == 0x21 && hookVars != 0) {
            *(f32 *)(hookVars + 4) = fast_vec_dist(((Hero *)gHeroState)->ptr[0xB10 / 4] + 0x10, vars->target + 0x10) * 0.1f;
            vars->f1C = 1.0f;
            vars->f20 = 0.0f;
            vars->f18 = 0.0f;
            if (self[0x43] != 3)
                StartAnimationBlended(self, 3, 0, 10);
            self[0x20] = 0xF;
        }
        break;
    case 21:
    default:
        break;
    }
}
