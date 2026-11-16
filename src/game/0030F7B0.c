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

extern PoolEffect g_pool_effect_slots[3];
extern char g_emitter_origin[] MACRO_ADDR;
extern float math_random_float_range(float min, float max);
extern float math_random_signed_float_range(float min, float max);
extern void vec_clear_128(void *vector);
extern char *moby_get_private_value_0(void *object);
extern void gravity_get_dir_at_object(void *object, void *out, int);
extern void FastVecScale(void *out, void *vector, float scale);

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



extern unsigned char g_swingshot_peer_flag;
extern int D_L00_002A27F0[];
extern void anim_start_blended(void *, int, int, int);
extern void moby_mark_spawned(void *);
extern void func_002A10E8(void *);

/* Updates the Swingshot hook. It copies the Swingshot's state into matching animations and removes itself when the Swingshot is gone. */
void swingshot_hook_update(unsigned char *self)
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
    if (peer == 0 || *(short *)(peer + 0xAA) != MOBY_CLASS_SWINGSHOT || peer[0x20] == 0xFE ||
        peer[0x20] == 0xFD || *(unsigned char **)(*(unsigned char **)(peer + 0x68) + 0x14) != self)
        goto destroy;
    if ((*(unsigned short *)(peer + 0x34) & 1) || g_swingshot_peer_flag != 0)
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
            anim_start_blended(self, 1, 0, 10);
        self[0x20] = 1;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c1:
    if ((*(unsigned char **)data)[0x20] == 2) {
        if (self[0x43] != 3)
            anim_start_blended(self, 3, 0, 10);
        self[0x20] = 3;
        *(float *)(self + 0x48) = 1.0f;
    } else if ((*(unsigned char **)data)[0x20] == 8) {
        if (self[0x43] != 2)
            anim_start_blended(self, 2, 0, 10);
        self[0x20] = 2;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c2:
    if (!(self[0x60] & 2))
        goto finish;
destroy:
    moby_mark_spawned(self);
    return;
c3:
    if (self[0x60] & 2) {
        if (self[0x43] != 4)
            anim_start_blended(self, 4, 0, 10);
        self[0x20] = 4;
    }
    goto finish;
c4:
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 3) < 3) {
        if (self[0x43] != 5)
            anim_start_blended(self, 5, 0, 10);
        self[0x20] = 5;
    }
    goto finish;
c5:
    if (self[0x60] & 2)
        *(float *)(self + 0x48) = 0.0f;
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 6) < 2) {
        *(float *)(self + 0x48) = 1.0f;
        if (self[0x43] != 7)
            anim_start_blended(self, 7, 0, 10);
        self[0x20] = 7;
    }
    goto finish;
c7:
    if (!(self[0x60] & 2))
        goto finish;
activate_one:
    if (self[0x43] != 1)
        anim_start_blended(self, 1, 0, 10);
    self[0x20] = 1;
c6:
finish:
    func_002A10E8(self);
}

extern char *g_turret_target_moby __attribute__((sda));
extern float g_tick_time_scale[] __attribute__((sda));
extern void moby_carry_with_surface(char *, char *);
extern int cam_moby_update(unsigned char *);
extern int math_random_int_below(int);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void moby_mark_spawned(void *);

/* Waits to be hit or set off at random, then fades out and removes itself. */
void moby_fade_out_update(unsigned char *self)
{
    if (g_turret_target_moby != 0)
        moby_carry_with_surface((char *)self, g_turret_target_moby);
    switch (self[0x20]) {
    case 0:
        if (cam_moby_update(self) != 0 ||
            (g_tick_time_scale[0] > 0.949999988079071044921875f && math_random_int_below(10) == 0)) {
            moby_set_state(self, 1, -1);
            *(unsigned short *)(self + 0x34) |= 0x2800;
        }
        break;
    case 1:
        cam_moby_update(self);
        if (self[0x23] < 2)
            moby_mark_spawned(self);
        else
            self[0x23] -= 2;
        break;
    }
}


/* Moves the first object along with the moving surface the second one stands on, so it keeps its place on it. */
void moby_carry_with_surface(char *o0, char *o1)
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
extern int math_random_int_below(int);
extern void moby_mark_spawned(void *);
extern void FastVecAdd(void *,void *,void *);
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
extern int g_slot_play_counters[] MACRO_ADDR;
extern char g_collision_hit[];
#define HIT (*(SupportHit *)D_001BAF80)
extern SupportPath *g_path_table[];
extern float FastAddRotations(float,float);
extern int CollLine(void *,void *,int,void *,int);
extern int moby_is_in_special_class_range(void *);
extern char *moby_get_private_value_2(void *);
extern int moby_get_attachment_rotation_angles(void *,void *,void *,void *,void *,void *);
extern int GetFirstMobyInGroup(void *,int,int,int);
extern int GetNextMobyInGroup(void *,void *,int,int);
extern void math_trap_always(void);
extern float fast_vec_dist(void *,void *);
void GroundAttachedUpdate(SupportMoby *moby) {
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
        if (moby->oclass == MOBY_CLASS_CRATE && math_random_int_below(2) != 0 && moby->rotation[0] == 0.0f && moby->rotation[1] == 0.0f) {
            moby->rotation[2] = FastAddRotations(moby->rotation[2], 1.5707964897155762f);
        }
        if ((moby->oclass == MOBY_CLASS_NANOTECH_CRATE || moby->oclass == MOBY_CLASS_PURPLE_NANOTECH_CRATE) && moby->mission != 0xFF && g_slot_play_counters[moby->mission] < vars->death_count) {
            moby_mark_spawned(moby);
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
        if (CollLine(&probe_top, &probe_bottom, 2, 0, 0) == 0) {
            vars->support = 0;
            return;
        }
        if (HIT.moby == 0) {
            moby->position.z = HIT.point_z;
            vars->support = 0;
            return;
        }
        if (moby_is_in_special_class_range(HIT.moby) != 0) return;
        vars->support = 0;
        vars->flags |= 8;
        if (moby_get_private_value_2(HIT.moby) != 0) {
            if (moby != 0) moby->occlusion = 0x7F80;
            moby_get_attachment_rotation_angles(member, HIT.moby, &moby->position, &moby->rotation[0], &vars->link_pos, &vars->link_rot);
            vars->stack_level = 0;
            vars->standing_on = HIT.moby;
        }
        return;
    }

    GetFirstMobyInGroup(&moby, group, 0, 0);
    while (moby != 0) {
        vars = moby->vars;
        if (moby_is_in_special_class_range(moby) != 0) {
            if (moby->oclass == MOBY_CLASS_CRATE && math_random_int_below(2) != 0 && moby->rotation[0] == 0.0f && moby->rotation[1] == 0.0f) {
                moby->rotation[2] = FastAddRotations(moby->rotation[2], 1.5707964897155762f);
            }
            if ((moby->oclass == MOBY_CLASS_NANOTECH_CRATE || moby->oclass == MOBY_CLASS_PURPLE_NANOTECH_CRATE) && moby->mission != 0xFF && g_slot_play_counters[moby->mission] < vars->death_count) {
                moby_mark_spawned(moby);
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
                if (CollLine(&probe_top, &probe_bottom, 2, 0, 0) == 0) {
                    vars->support = 0;
                } else {
                    if (HIT.moby == 0) {
                        moby->position.z = HIT.point_z;
                        vars->support = 0;
                    } else if (moby_is_in_special_class_range(HIT.moby) == 0 && (u16)(HIT.moby->oclass - 0x128) >= 2) {
                        vars->support = 0;
                        moby->update_distance = 0xFF;
                        vars->flags |= 8;
                    } else if (HIT.moby->vars == 0) {
                        vars->support = 0;
                    } else if (HIT.moby->group != moby->group) {
                        vars->support = 0;
                    } else if (moby_is_in_special_class_range(HIT.moby) != 0) {
                        vars->support = HIT.moby;
                        src3 = &moby->position;
                        below = HIT.moby;
                        qcopy_nc(src3, &below->position);
                        FastVecAdd(src3, src3, &below->offset);
                        vars = HIT.moby->vars;
                        if (moby_is_in_special_class_range(moby) != 0) {
                            vars->above = moby;
                        } else {
                            math_trap_always();
                            vars->above = 0;
                        }
                    } else {
                        vars->support = 0;
                        moby->position.z = HIT.point_z;
                    }
                }
            }
        }
        GetNextMobyInGroup(&moby, moby, 0, 0);
    }

    GetFirstMobyInGroup(&member, group, 0, 0);
    while (member != 0) {
        vars = member->vars;
        if (moby_is_in_special_class_range(member) != 0 && vars->support == 0) {
            src4 = &member->position;
            qcopy_nc(&probe_up, src4);
            qcopy_nc(&probe_down, src4);
            probe_up.z += vars->height * 0.5f;
            probe_down.z = 0.1f;
            if (CollLine(&probe_up, &probe_down, 2, moby, 0) != 0) {
                if (HIT.moby != 0 && moby_get_private_value_2(HIT.moby) != 0) {
                    if (moby != 0) moby->occlusion = 0x7F80;
                    moby_get_attachment_rotation_angles(member, HIT.moby, &member->position, &member->rotation[0], &vars->link_pos, &vars->link_rot);
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
                if ((vars->hC6 != 0 || (moby->oclass == MOBY_CLASS_NANOTECH_CRATE || moby->oclass == MOBY_CLASS_PURPLE_NANOTECH_CRATE)) && vars->above != 0 && vars->route_index != -1) {
                    route = g_path_table[vars->route_index];
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
                            for (i = 0; i < g_path_table[vars->route_index]->count; i++) {
                                g_path_table[vars->route_index]->entries[i].state = 0;
                            }
                        }
                    }
                }
            }
        }
        GetNextMobyInGroup(&member, member, 0, 0);
    }

    GetFirstMobyInGroup(&moby, group, 0, 0);
    while (moby != 0) {
        if (moby_is_in_special_class_range(moby) != 0) {
            GetNextMobyInGroup(&other, moby, 0, 0);
            while (other != 0) {
                if (moby_is_in_special_class_range(other) != 0) {
                    fast_vec_dist(&moby->position, &other->position);
                }
                GetNextMobyInGroup(&other, other, 0, 0);
            }
        }
        GetNextMobyInGroup(&moby, moby, 0, 0);
    }
}

/* func_00311F70 is in 0030F7B0-loot-g8.c. */

/* func_003120C8 is in 0030F7B0-death-g8.c. */


/* func_00312600 is in 0030F7B0-crate-g8.c. */

/* Returns 1 when the object is in state 6. */
int moby_is_state_six(Level16VendorMoby *moby) {
    return moby->state == 6;
}






/* Returns 1 when the object is in state 1. */
int moby_is_state_one(unsigned char *p) { return p[0x20] == 1; }



/* func_00312EB0 is defined in 00312EB0-qcopy.c. */

/* func_00313210 is in 0030F7B0-g16.c. */

extern char g_nanotech_ball_axes[][16];
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

typedef struct { char pad[0x30]; char *entries[1]; } SolEmitterData;

/* Finds the position of one of the emitter's slots, turned by the emitter's angle and lifted by its height. */
void emitter_get_slot_position(unsigned char *object, float *out, int index)
{
    char local[16];
    char *data = *(char **)(object + 0x68);
    char *entry;
    math_apply_axis_rotation_to_quat(local, g_nanotech_ball_axes[index], data + 0x20, *(float *)(data + 0x2C));
    entry = ((SolEmitterData *)data)->entries[index];
    if (entry && object[0x20] == 2)
        vec_scale_to_length(local, local, *(float *)(entry + 0x28));
    FastVecAdd(out, data + 0x10, local);
    out[2] += *(float *)data;
}


/* func_00313678 uses the profile in 0030F7B0-qcopy.c. */

/* func_003136D0 is in 0030F7B0-ball-sw-g8.c. */

/* func_003146C0 is in 0030F7B0-ball-g8.c. */


/* func_00314FD0 is in 0030F7B0-throw.c. */


/* func_003158A8 uses the profile in 0030F7B0-spawn.c. */

/* func_003159D0 is defined in 0030F7B0-thrown.c. */

/* func_00315C78 is in 0030F7B0-nearest.c. */


/* func_00316248 is in 0030F7B0-g8.c. */

/* Fills the first free effect slot for owner: random angles, speeds and amplitudes, a timer
 * of duration frames, and the object's position as the start (offset when it has a record). */
void AllocEffectSlot(void *owner, char *object, int duration)
{
    PoolEffect *pool = g_pool_effect_slots;
    int i = 0;
    const char *origin = g_emitter_origin;
    PoolEffect *effect;
    float displacement[4] __attribute__((aligned(16)));
    char *info;

    for (; i < 3; i++) {
        effect = &pool[i];
        if (effect->owner != 0)
            continue;

        effect->owner = owner;
        qcopy(effect->origin, origin);
        effect->angle[0] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle[1] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle[2] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle2[0] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle2[1] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle2[2] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->speed[0] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed[1] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed[2] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed2[0] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed2[1] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed2[2] = math_random_signed_float_range(0.001f, 0.005f);
        effect->amplitude[0] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude[1] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude[2] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[0] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[1] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[2] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        vec_clear_128(effect->offset);
        vec_clear_128(effect->rotation);
        effect->timer = duration;
        effect->duration = duration;
        effect->fade = 15;
        effect->object = object;
        effect->expired = 0;

        info = moby_get_private_value_0(object);
        if (info != 0) {
            gravity_get_dir_at_object(object, displacement, 1);
            FastVecScale(displacement, displacement, *(float *)(info + 16));
            FastVecAdd(effect->position, displacement, object + 16);
        } else {
            char *source = object + 16;

            qcopy(effect->position, source);
        }
        break;
    }
}

extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void lerp_vector(void *, void *, void *, float);
extern float IntToFloat(int);
extern int math_fast_float_d(void *);

/* Advances the owner's effect slots. p is set only after the owner test, in the block of the
 * origin copy: there p + 0x20 is not anticipatable, so gcse leaves the last call's own address
 * instead of keeping it in a saved register. */
void UpdateEffectSlots(void *owner)
{
    int i;
    PoolEffect *p, *slot;
    char *info;
    char local[16] __attribute__((aligned(16)));
    float ratio;
    for (i = 0; i < 3; i++) {
        slot = &g_pool_effect_slots[i];
        if (slot->owner != owner) continue;
        p = slot;
        qcopy(p->origin, g_emitter_origin);
        if (p->timer) {
            p->angle[0] = FastAddRotations(p->angle[0], p->speed[0] * 100.0f);
            p->angle[1] = FastAddRotations(p->angle[1], p->speed[1] * 100.0f);
            p->angle[2] = FastAddRotations(p->angle[2], p->speed[2] * 100.0f);
            p->angle2[0] = FastAddRotations(p->angle2[0], p->speed2[0] * 100.0f);
            p->angle2[1] = FastAddRotations(p->angle2[1], p->speed2[1] * 100.0f);
            p->angle2[2] = FastAddRotations(p->angle2[2], p->speed2[2] * 100.0f);
        } else {
            p->angle[0] = FastAddRotations(p->angle[0], p->speed[0] * 50.0f);
            p->angle[1] = FastAddRotations(p->angle[1], p->speed[1] * 50.0f);
            p->angle[2] = FastAddRotations(p->angle[2], p->speed[2] * 50.0f);
            p->angle2[0] = FastAddRotations(p->angle2[0], p->speed2[0] * 50.0f);
            p->angle2[1] = FastAddRotations(p->angle2[1], p->speed2[1] * 50.0f);
            p->angle2[2] = FastAddRotations(p->angle2[2], p->speed2[2] * 50.0f);
        }
        p->offset[0] = math_fast_sin_or_cos_a(p->angle[0]) * p->amplitude[0];
        p->offset[1] = math_fast_sin_or_cos_b(p->angle[1]) * p->amplitude[1];
        p->offset[2] = -math_fast_sin_or_cos_b(p->angle[2]) * p->amplitude[2];
        p->rotation[0] = math_fast_sin_or_cos_a(p->angle2[0]) * p->amplitude2[0];
        p->rotation[1] = math_fast_sin_or_cos_b(p->angle2[1]) * p->amplitude2[1];
        p->rotation[2] = -math_fast_sin_or_cos_b(p->angle2[2]) * p->amplitude2[2];
        if (p->object) {
            info = moby_get_private_value_0(p->object);
            if (info) {
                gravity_get_dir_at_object(p->object, local, 1);
                FastVecScale(local, local, *(float *)(info + 16));
                FastVecAdd(p->position, local, p->object + 16);
            } else {
                qcopy(p->position, p->object + 16);
            }
            ratio = IntToFloat(p->timer);
            ratio /= IntToFloat(p->duration);
            lerp_vector(p->position, p->origin, p->position, 1.0f - ratio);
        }
        if (math_fast_float_d(&p->timer)) {
            if (!p->expired) p->expired = 1;
            if (math_fast_float_d(&p->fade)) p->owner = 0;
        }
    }
}


/* Fills a draw packet with its default corner positions, colors and settings. */
void gfx_init_draw_packet_defaults(char *p)
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

/* Adds one more point to the end of a curve by continuing the direction of the last two points. */
void gfx_extrapolate_curve_end(Vec16_Fc936841d *object, int index)
{
    char local[16];

    Fc936841d_FUN_00282CF0(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    Fc936841d_FUN_00282CC0((char *)&object[index - 1], (char *)&object[index - 2], local);
}
