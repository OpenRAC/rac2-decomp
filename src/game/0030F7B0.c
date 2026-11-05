#include "common.h"

/* One of the three 0xA0-byte effect slots of D_0022AA10, filled by func_00316400. */
typedef struct {
    float offset[4];            /* 0x00 */
    float rotation[4];          /* 0x10 */
    float origin[4];            /* 0x20 */
    float position[4];          /* 0x30 */
    float angle[3];             /* 0x40 */
    float speed[3];             /* 0x4C */
    float amplitude[3];         /* 0x58 */
    float angle2[3];            /* 0x64 */
    float speed2[3];            /* 0x70 */
    float amplitude2[3];        /* 0x7C */
    int fade;                   /* 0x88 */
    void *owner;                /* 0x8C: 0 for a free slot */
    char *object;               /* 0x90 */
    int timer;                  /* 0x94 */
    int duration;               /* 0x98 */
    int expired;                /* 0x9C */
} PoolEffect;

extern PoolEffect D_0022AA10[3];
extern char D_001B2520[] MACRO_ADDR;
extern float func_002A7878(float min, float max);
extern float func_002A78D8(float min, float max);
extern void func_00282C88(void *vector);
extern char *func_002AB1F0(void *object);
extern void func_002B00B0(void *object, void *out, int);
extern void func_00282D30(void *out, void *vector, float scale);

extern char *Ffc961fca_FUN_002AD0B0(char *a1);

extern void Ffc961fca_FUN_00283410(char *dst, char *src);

extern void Ffc961fca_FUN_00282CC0(char *dst, char *src, char *tail);

extern void Ffc961fca_FUN_00282CF0(char *dst, char *src, char *tail);

extern void Ffc961fca_FUN_00283698(char *dst, char *src);

extern void Ffc961fca_FUN_00283098(char *dst, char *src, char *tail);

extern void Ffc961fca_FUN_00283738(char *dst, char *src, char *tail);

typedef struct {
    char pad0[0x20];
    unsigned char state;
} Level16VendorMoby;

extern void Fc936841d_FUN_00282CF0(char *local, char *first, char *second);

extern void Fc936841d_FUN_00282CC0(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif



extern unsigned char D_0018C0DF;
extern int D_L00_002A27F0[];
extern void func_002A7470(void *, int, int, int);
extern void func_0029F338(void *);
extern void func_002A10E8(void *);

void func_00310A40(unsigned char *self)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    unsigned char *peer;
    unsigned char *data;
    int state;

    if (self == 0)
        return;
    data = *(unsigned char **)(self + 0x68);
    if (data == 0)
        return;
    peer = *(unsigned char **)data;
    if (peer == 0 || *(short *)(peer + 0xAA) != 0xD0 || peer[0x20] == 0xFE ||
        peer[0x20] == 0xFD || *(unsigned char **)(*(unsigned char **)(peer + 0x68) + 0x14) != self)
        goto destroy;
    if ((*(unsigned short *)(peer + 0x34) & 1) || D_0018C0DF != 0)
        *(unsigned short *)(self + 0x34) |= 0x41;
    else
        *(unsigned short *)(self + 0x34) &= 0xFFBE;
    state = self[0x20];
    if ((unsigned int)state < 8)
        goto *D_L00_002A27F0[state];
    goto activate_one;
c0:
    if (self[0x60] & 2) {
        if (self[0x43] != 1)
            func_002A7470(self, 1, 0, 10);
        self[0x20] = 1;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c1:
    if ((*(unsigned char **)data)[0x20] == 2) {
        if (self[0x43] != 3)
            func_002A7470(self, 3, 0, 10);
        self[0x20] = 3;
        *(float *)(self + 0x48) = 1.0f;
    } else if ((*(unsigned char **)data)[0x20] == 8) {
        if (self[0x43] != 2)
            func_002A7470(self, 2, 0, 10);
        self[0x20] = 2;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c2:
    if (!(self[0x60] & 2))
        goto finish;
destroy:
    func_0029F338(self);
    return;
c3:
    if (self[0x60] & 2) {
        if (self[0x43] != 4)
            func_002A7470(self, 4, 0, 10);
        self[0x20] = 4;
    }
    goto finish;
c4:
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 3) < 3) {
        if (self[0x43] != 5)
            func_002A7470(self, 5, 0, 10);
        self[0x20] = 5;
    }
    goto finish;
c5:
    if (self[0x60] & 2)
        *(float *)(self + 0x48) = 0.0f;
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 6) < 2) {
        *(float *)(self + 0x48) = 1.0f;
        if (self[0x43] != 7)
            func_002A7470(self, 7, 0, 10);
        self[0x20] = 7;
    }
    goto finish;
c7:
    if (!(self[0x60] & 2))
        goto finish;
activate_one:
    if (self[0x43] != 1)
        func_002A7470(self, 1, 0, 10);
    self[0x20] = 1;
c6:
finish:
    func_002A10E8(self);
}

extern char *D_001AD7EC __attribute__((sda));
extern float D_001B1690[] __attribute__((sda));
extern void func_00310D78(char *, char *);
extern int func_00273B70(unsigned char *);
extern int func_002A77E0(int);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void func_0029F338(void *);

void func_00310C88(unsigned char *self)
{
    if (D_001AD7EC != 0)
        func_00310D78((char *)self, D_001AD7EC);
    switch (self[0x20]) {
    case 0:
        if (func_00273B70(self) != 0 ||
            (D_001B1690[0] > 0.949999988079071044921875f && func_002A77E0(10) == 0)) {
            func_002A7750(self, 1, -1);
            *(unsigned short *)(self + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_00273B70(self);
        if (self[0x23] < 2)
            func_0029F338(self);
        else
            self[0x23] -= 2;
        break;
    }
}


void func_00310D78(char *o0, char *o1)
{
    char b0[64];
    char b1[64];
    char b2[64];
    char *r = Ffc961fca_FUN_002AD0B0(o1);

    if (r == 0)
        return;
    Ffc961fca_FUN_00283410(b0, r);
    Ffc961fca_FUN_00282CC0(o0 + 16, o0 + 16, r + 16);
    Ffc961fca_FUN_00282CF0(o0 + 16, o0 + 16, o1 + 16);
    if ((*(int *)(r + 60) & 2) != 0) {
        Ffc961fca_FUN_00283410(b2, r + 32);
        Ffc961fca_FUN_00283698(b1, b2);
        Ffc961fca_FUN_00283098(o0 + 16, o0 + 16, b1);
        Ffc961fca_FUN_00283098(o0 + 16, o0 + 16, o1 + 192);
    } else {
        Ffc961fca_FUN_00283098(o0 + 16, o0 + 16, b0);
    }
    Ffc961fca_FUN_00282CC0(o0 + 16, o0 + 16, o1 + 16);
    Ffc961fca_FUN_00283738(o0 + 192, b0, o0 + 192);
}

/* func_00310E98 is in 0030F7B0-update.c. */

/* func_003116E8: per-frame update of ground-attached crates and their stacks, after RAC1's
 * ground_attached_update (OpenRAC/rac1-decomp, GPL-3.0); RAC2 adds class 0x200 and drops iCC.
 * The group==255 path passes the uninitialized member slot, as retail and RAC1 do. */
extern int func_002A77E0(int);
extern void func_0029F338(void *);
extern void func_00282CC0(void *,void *,void *);
typedef struct SupportMoby SupportMoby;
typedef struct SupportVars SupportVars;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) SupportVector;
struct SupportMoby {
    char pad0[0x10];
    SupportVector position;
    unsigned char state, group;
    char pad22[0x30-0x22];
    unsigned char update_distance;
    char pad31[5];
    unsigned short occlusion;
    char pad38[0x68-0x38];
    SupportVars *vars;
    char pad6C[0xAA-0x6C];
    short oclass;
    unsigned short model;
    char padAE[2];
    unsigned char mission;
    char padB1[0xE0-0xB1];
    SupportVector offset;
    float rotation[3];
};
struct SupportVars {
    char pad0[0xA0];
    SupportMoby *above, *support;
    int padA8;
    int flags;
    float height;
    char padB4[0xC0-0xB4];
    int route_index;
    unsigned short model;
    short hC6;
    int padC8, iCC;
    SupportVector link_pos, link_rot;
    SupportMoby *standing_on;
    float stack_level;
    int death_count;
};
typedef struct {
    char pad0[0x18];
    SupportMoby *moby;
    char pad1C[0x28-0x1C];
    float point_z;
} SupportHit;
typedef struct { int pad[3], state; } SupportPathEntry;
typedef struct { int count, pad[3]; SupportPathEntry entries[1]; } SupportPath;
extern int D_001A73E0[] MACRO_ADDR;
extern char D_001BAF80[];
#define HIT (*(SupportHit *)D_001BAF80)
extern SupportPath *D_001F1700[];
extern float func_00283B98(float,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern int func_002ABB78(void *);
extern char *func_002AD0B0(void *);
extern void func_002AD5F8(void *,void *,void *,void *,void *,void *);
extern int func_002A8600(void *,int,int,int);
extern int func_002A86E8(void *,void *,int,int);
extern void func_00282A28(void);
extern float func_00282E48(void *,void *);
void func_003116E8(SupportMoby *moby) {
    SupportVector probe_top;
    SupportVector probe_bottom;
    SupportVector probe_up;
    SupportVector probe_down;
    SupportMoby *member;
    SupportMoby *other;
    SupportVars *vars;
    SupportVars *below_vars;
    SupportVector *src1, *src2, *src3, *src4;
    SupportPath *route;
    s32 group, flags_before, i, member_flags;
    SupportMoby *below;

    vars = moby->vars;
    group = moby->group;
    vars->flags |= 4;
    if (group == 0xFF) {
        if (moby->oclass == 0x1F4 && func_002A77E0(2) != 0 && moby->rotation[0] == 0.0f && moby->rotation[1] == 0.0f) {
            moby->rotation[2] = func_00283B98(moby->rotation[2], 1.5707964897155762f);
        }
        if ((moby->oclass == 0x1F5 || moby->oclass == 0x200) && moby->mission != 0xFF && D_001A73E0[moby->mission] < vars->death_count) {
            func_0029F338(moby);
            return;
        }
        flags_before = vars->flags;
        vars->model = moby->model;
        vars->height = 1.0f;
        vars->flags = flags_before | 1;
        src1 = &moby->position;
        qcopy_nc(&probe_top, src1);
        qcopy_nc(&probe_bottom, src1);
        probe_top.z += 0.5f;
        probe_bottom.z = 0.1f;
        if (func_002761F8(&probe_top, &probe_bottom, 2, 0, 0) == 0) {
            vars->support = 0;
            return;
        }
        if (HIT.moby == 0) {
            moby->position.z = HIT.point_z;
            vars->support = 0;
            return;
        }
        if (func_002ABB78(HIT.moby) != 0) return;
        vars->support = 0;
        vars->flags |= 8;
        if (func_002AD0B0(HIT.moby) != 0) {
            if (moby != 0) moby->occlusion = 0x7F80;
            func_002AD5F8(member, HIT.moby, &moby->position, &moby->rotation[0], &vars->link_pos, &vars->link_rot);
            vars->stack_level = 0;
            vars->standing_on = HIT.moby;
        }
        return;
    }

    func_002A8600(&moby, group, 0, 0);
    while (moby != 0) {
        vars = moby->vars;
        if (func_002ABB78(moby) != 0) {
            if (moby->oclass == 0x1F4 && func_002A77E0(2) != 0 && moby->rotation[0] == 0.0f && moby->rotation[1] == 0.0f) {
                moby->rotation[2] = func_00283B98(moby->rotation[2], 1.5707964897155762f);
            }
            if ((moby->oclass == 0x1F5 || moby->oclass == 0x200) && moby->mission != 0xFF && D_001A73E0[moby->mission] < vars->death_count) {
                func_0029F338(moby);
            } else {
                member_flags = vars->flags;
                vars->model = moby->model;
                vars->height = 1.0f;
                vars->flags = member_flags | 1;
                src2 = &moby->position;
                qcopy_nc(&probe_top, src2);
                qcopy_nc(&probe_bottom, src2);
                probe_top.z += 0.5f;
                probe_bottom.z = 0.1f;
                if (func_002761F8(&probe_top, &probe_bottom, 2, 0, 0) == 0) {
                    vars->support = 0;
                } else {
                    if (HIT.moby == 0) {
                        moby->position.z = HIT.point_z;
                        vars->support = 0;
                    } else if (func_002ABB78(HIT.moby) == 0 && (u16)(HIT.moby->oclass - 0x128) >= 2) {
                        vars->support = 0;
                        moby->update_distance = 0xFF;
                        vars->flags |= 8;
                    } else if (HIT.moby->vars == 0) {
                        vars->support = 0;
                    } else if (HIT.moby->group != moby->group) {
                        vars->support = 0;
                    } else if (func_002ABB78(HIT.moby) != 0) {
                        vars->support = HIT.moby;
                        src3 = &moby->position;
                        below = HIT.moby;
                        qcopy_nc(src3, &below->position);
                        func_00282CC0(src3, src3, &below->offset);
                        vars = HIT.moby->vars;
                        if (func_002ABB78(moby) != 0) {
                            vars->above = moby;
                        } else {
                            func_00282A28();
                            vars->above = 0;
                        }
                    } else {
                        vars->support = 0;
                        moby->position.z = HIT.point_z;
                    }
                }
            }
        }
        func_002A86E8(&moby, moby, 0, 0);
    }

    func_002A8600(&member, group, 0, 0);
    while (member != 0) {
        vars = member->vars;
        if (func_002ABB78(member) != 0 && vars->support == 0) {
            src4 = &member->position;
            qcopy_nc(&probe_up, src4);
            qcopy_nc(&probe_down, src4);
            probe_up.z += vars->height * 0.5f;
            probe_down.z = 0.1f;
            if (func_002761F8(&probe_up, &probe_down, 2, moby, 0) != 0) {
                if (HIT.moby != 0 && func_002AD0B0(HIT.moby) != 0) {
                    if (moby != 0) moby->occlusion = 0x7F80;
                    func_002AD5F8(member, HIT.moby, &member->position, &member->rotation[0], &vars->link_pos, &vars->link_rot);
                    vars->stack_level = 0;
                    vars->standing_on = HIT.moby;
                    vars->flags |= 8;
                }
            }
            for (moby = member; moby != 0; moby = vars->above) {
                vars = moby->vars;
                if (vars->support != 0) below_vars = vars->support->vars;
                else below_vars = 0;
                if (below_vars != 0) {
                    if (below_vars->standing_on != 0) {
                        moby->update_distance = 0xFF;
                        vars->flags |= 8;
                        qcopy_nc(&vars->link_pos, &below_vars->link_pos);
                        qcopy_nc(&vars->link_rot, &below_vars->link_rot);
                        vars->standing_on = below_vars->standing_on;
                        vars->stack_level = below_vars->stack_level + 1.0f;
                    }
                }
                if ((vars->hC6 != 0 || (moby->oclass == 0x1F5 || moby->oclass == 0x200)) && vars->above != 0 && vars->route_index != -1) {
                    route = D_001F1700[vars->route_index];
                    if (route->count == 0) {
                        vars->route_index = -1;
                    } else {
                        s32 entry_state = route->entries[0].state;
                        if (entry_state == 1 || entry_state == 3) {
                            vars->route_index = -1;
                        } else if (entry_state == 0x111) {
                            vars->route_index = -1;
                        } else if ((u32)(entry_state - 0x11) < 0x100) {
                            if (entry_state - 0x10 >= route->count) {
                                vars->route_index = -1;
                            } else {
                                route->entries[0].state = entry_state + 1;
                            }
                        } else {
                            route->entries[0].state = 0x11;
                            for (i = 0; i < D_001F1700[vars->route_index]->count; i++) {
                                D_001F1700[vars->route_index]->entries[i].state = 0;
                            }
                        }
                    }
                }
            }
        }
        func_002A86E8(&member, member, 0, 0);
    }

    func_002A8600(&moby, group, 0, 0);
    while (moby != 0) {
        if (func_002ABB78(moby) != 0) {
            func_002A86E8(&other, moby, 0, 0);
            while (other != 0) {
                if (func_002ABB78(other) != 0) {
                    func_00282E48(&moby->position, &other->position);
                }
                func_002A86E8(&other, other, 0, 0);
            }
        }
        func_002A86E8(&moby, moby, 0, 0);
    }
}

/* func_00311F70 is in 0030F7B0-loot-g8.c. */

/* func_003120C8 is in 0030F7B0-death-g8.c. */


/* func_00312600 is in 0030F7B0-crate-g8.c. */

int func_00312B58(Level16VendorMoby *moby) {
    return moby->state == 6;
}






int func_00312E10(unsigned char *p) { return p[0x20] == 1; }



/* func_00312EB0 is defined in 00312EB0-qcopy.c. */

/* func_00313210 is in 0030F7B0-g16.c. */

extern char D_L00_0023A670[][16];
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

typedef struct { char pad[0x30]; char *entries[1]; } SolEmitterData;

void func_00313548(unsigned char *object, float *out, int index)
{
    char local[16];
    char *data = *(char **)(object + 0x68);
    char *entry;
    func_002ACEC0(local, D_L00_0023A670[index], data + 0x20, *(float *)(data + 0x2C));
    entry = ((SolEmitterData *)data)->entries[index];
    if (entry && object[0x20] == 2)
        func_00282F20(local, local, *(float *)(entry + 0x28));
    func_00282CC0(out, data + 0x10, local);
    out[2] += *(float *)data;
}


/* func_00313678 uses the profile in 0030F7B0-qcopy.c. */

INCLUDE_ASM("asm/game", func_003136D0);

/* func_003146C0 is in 0030F7B0-ball-g8.c. */


/* func_00314FD0 is in 0030F7B0-throw.c. */


/* func_003158A8 uses the profile in 0030F7B0-spawn.c. */

/* func_003159D0 is defined in 0030F7B0-thrown.c. */

/* func_00315C78 is in 0030F7B0-nearest.c. */


/* func_00316248 is in 0030F7B0-g8.c. */

/* Fills the first free effect slot for owner: random angles, speeds and amplitudes, a timer
 * of duration frames, and the object's position as the start (offset when it has a record). */
void func_00316400(void *owner, char *object, int duration)
{
    PoolEffect *pool = D_0022AA10;
    int i = 0;
    const char *origin = D_001B2520;
    PoolEffect *effect;
    float displacement[4] __attribute__((aligned(16)));
    char *info;

    for (; i < 3; i++) {
        effect = &pool[i];
        if (effect->owner != 0)
            continue;

        effect->owner = owner;
        qcopy(effect->origin, origin);
        effect->angle[0] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle[1] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle[2] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle2[0] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle2[1] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle2[2] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->speed[0] = func_002A78D8(0.001f, 0.005f);
        effect->speed[1] = func_002A78D8(0.001f, 0.005f);
        effect->speed[2] = func_002A78D8(0.001f, 0.005f);
        effect->speed2[0] = func_002A78D8(0.001f, 0.005f);
        effect->speed2[1] = func_002A78D8(0.001f, 0.005f);
        effect->speed2[2] = func_002A78D8(0.001f, 0.005f);
        effect->amplitude[0] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude[1] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude[2] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[0] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[1] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[2] = func_002A7878(3.25f, 4.75f) * 0.5f;
        func_00282C88(effect->offset);
        func_00282C88(effect->rotation);
        effect->timer = duration;
        effect->duration = duration;
        effect->fade = 15;
        effect->object = object;
        effect->expired = 0;

        info = func_002AB1F0(object);
        if (info != 0) {
            func_002B00B0(object, displacement, 1);
            func_00282D30(displacement, displacement, *(float *)(info + 16));
            func_00282CC0(effect->position, displacement, object + 16);
        } else {
            char *source = object + 16;

            qcopy(effect->position, source);
        }
        break;
    }
}

INCLUDE_ASM("asm/game", func_003166C8);


void func_00316B40(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* func_00316BC8 is defined in 00316BC8-qcopy.c. */

void func_00316DA0(Vec16_Fc936841d *object, int index)
{
    char local[16];

    Fc936841d_FUN_00282CF0(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    Fc936841d_FUN_00282CC0((char *)&object[index - 1], (char *)&object[index - 2], local);
}
