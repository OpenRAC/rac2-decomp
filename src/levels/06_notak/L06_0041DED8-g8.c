#include "include_asm.h"
#include "common.h"

extern char *D_L06_001B281C __attribute__((sda));

extern u8 *D_L06_001FB3A0[];
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern int math_random_int_range(int, int);
extern int PlayMobySound(int, int, char *);
extern int g_current_map_index;
extern unsigned char D_0019B2E8[];
extern char *g_path_list[];
extern float path_l01_compute_segment_lengths(char *);
extern void mem_clear(char *, int, int);
extern int actor_choose_path_goal(char *);
extern int moby_apply_damage_to_object(char *, char *, int);
extern void trigger_linked_object(char *);
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals g_hero_state;
extern char D_L06_00188660[], D_L06_001B9840[];
extern char D_L06_002AA500[], D_L06_00257CC0[], D_L06_002DF000[], D_L06_00257FC0[], D_L06_002DF060[];
extern int D_L06_001B1858[] SDATA(D_L06_001B1858);
extern int D_L06_001B187C SDATA(D_L06_001B187C);
extern int D_L06_001B1880 SDATA(D_L06_001B1880);
extern void effect_pool_clear(void), gfx_add_draw_callback_third(void);
extern int snd_start_in_slot(int, int, char *);
extern void snd_stop_voice(int);
extern void water_init_object(void *), water_update_controller(void *), water_advance_controller_state(void *), water_update_ripple_patches(void *);
extern void water_add_splash_entry(char *, float);
extern float math_fabs(float);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int IsPointInCuboid(char *, int);
typedef struct {
    int kind, count; char *items, *models, *data; int *states; char *aux, *more;
    int *a, *b; unsigned char *owner; void (*update)(void), (*callback)(void);
} Context;

/* Marks every actor in the object's group as alerted. */
void actor_alert_group(u8 *moby)
{
    char *moby_base;
    u8 *id_cursor;
    u8 *id_list;

    if (moby[0x21] == 0xFF)
        return;
    id_list = D_L06_001FB3A0[moby[0x21]];
    if (id_list == 0)
        return;
    id_cursor = id_list;
    moby_base = D_L06_001B281C;
    for (;;) {
        char *other = moby_base + ((*(unsigned short *)id_cursor & 0x7FFF) << 8);

        if (*(signed char *)(other + 0x20) >= 0) {
            if (*(short *)(other + 0xAA) == 0xBBA /* moby class 3002 */) {
                *(int *)(*(char **)(other + 0x68) + 0x258) = 1;
            }
        }
        if (*(short *)id_cursor < 0)
            break;
        id_cursor += 2;
    }
}

extern int D_L06_001B2838;
extern char *D_L06_001B2480;
extern float D_L06_001B1090 __attribute__((sda));
extern char D_L06_002E20C8[];
extern char D_L06_002E2128[];
extern void STUB_printf(const char *, ...);
extern void math_trap_always(void);
extern int FloatToInt(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
/* Alerts the actors in the object's group and tells its marker objects to light up. */
extern void actor_alert_group_and_markers(u8 *);
extern void moby_l06_explode_and_remove(char *);
extern void SetDeathBits(void *, int, int);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void moby_mark_spawned(void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);

/* A Notak enemy's update (spawn-time setup, then the shared distance, target and ground
   checks). The fields are indexed through typed pointers so their MEMs are in-struct: the
   sda and table loads after the angle call may then move above the word stores, as in
   retail. The setup's store order is the one that gives retail's schedule and FP registers. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void notak_enemy_update(u8 *moby)
{
    u8 *v = *(u8 **)(moby + 0x68);
    int hit_result;

    if (moby[0x20] == 0) {
        char *path_record;

        if (D_L06_001B2838 < moby[0x21]) {
            STUB_printf(D_L06_002E20C8);
            STUB_printf(D_L06_002E2128);
            math_trap_always();
        }
        moby[0x30] = 0x40;
        qcopy(v + 0x2E0, moby + 0x10);
        F(0x324) = 1.0f;
        B(0x48) = FloatToInt(15.0f);
        B(0x4A) = FloatToInt(4.8f);
        H(0x88) = 0;
        B(0x60) = 8;
        I(0x98) = 3;
        F(0x108) = 0.5f;
        F(0x80) = 0.2f;
        F(0x84) = 0.2f;
        B(0x28) = 3;
        F(0x30) = 0.333f;
        F(0x8C) = 0.4f;
        F(0x100) = F(0x324) * 0.6f;
        F(0x134) = 0.05f;
        F(0x104) = F(0x324) * 0.5f;
        F(0x10C) = 0.5f;
        I(0x138) |= 0x80;
        F(0x110) = 1.57079649f;
        F(0x130) = 0.52359885f;
        F(0x1DC) = math_random_signed_float_range(18.0f, 22.0f) * 0.0174532942f;
        B(0x1E8) = 7;
        B(0x1E9) = 6;
        H(0x1E2) = 120;
        H(0x1E4) = 180;
        F(0x1D4) = 3.0f;
        F(0x1D0) = D_L06_001B1090 * 0.0166666675f;
        path_record = D_L06_001B2480 + I(0x210) * 0x30;
        if (*(short *)(path_record + 0x30) != 0)
            I(0x13C) = **(int **)(path_record + 0x3C);
        F(0x328) = math_random_angle();
        if (I(0x214) != 0) {
            *(int *)(moby + 0x98) = 0;
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
            moby_set_state((char *)moby, 9, 4);
            if (moby[0x43] != 10)
                anim_start_blended((char *)moby, 10, 0, 0);
        } else {
            moby_set_state((char *)moby, 1, 0);
            if (moby[0x43] != 0)
                anim_start_blended((char *)moby, 0, 0, 0);
        }
    }
    if (moby[0x31] != 0 && fast_vec_dist(moby + 0x10, D_L06_001B9840) < 24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 0x16;
    }
    hit_result = moby_apply_damage_to_object((char *)moby, (char *)(v + 0x50), 0);
    if (hit_result != 0) {
        actor_alert_group_and_markers(moby);
        if (hit_result >= 4)
            moby_l06_explode_and_remove((char *)moby);
    }
    if (*(float *)(moby + 0x18) < 48.0f) {
        SetDeathBits(moby, 0, 3);
        part_spawn_explosion_with_sparks(moby, moby + 0x10, -1, 1.0f, 13.0f);
        moby_mark_spawned(moby);
    } else if (moby[0x95] != 3 && moby[0x95] != 4) {
        H(0x314) = weapon_select_aim_target(moby, I(0x210), 16.0f, 0.0f, 0, 0);
    }
}

#undef B
#undef H
#undef I
#undef F

void actor_alert_group_and_markers(u8 *arg0)
{
    char *a2;
    u8 *p;
    u8 *list;

    if (arg0[0x21] == 0xFF)
        return;
    list = D_L06_001FB3A0[arg0[0x21]];
    if (list == 0)
        return;
    p = list;
    a2 = D_L06_001B281C;
    for (;;) {
        char *q = a2 + ((*(unsigned short *)p & 0x7FFF) << 8);

        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xDB0 /* moby class 3504 */) {
                *(short *)(*(int *)(q + 0x68) + 0x316) = 1;
            }
        }
        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xBBA /* moby class 3002 */) {
                *(int *)(*(char **)(q + 0x68) + 0x258) = 1;
            }
        }
        if (*(short *)p < 0)
            break;
        p += 2;
    }
}

/* The id-list walks below read D_L06_001B281C as a bare symbol (a second name for the 4-byte
   `sda` pointer above, declared as a 12-byte array so the assembler keeps its loads absolute),
   while D_L06_001B2838 is a plain int: its `.extern` comes last in the file, which leaves a load
   in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern unsigned char *D_L06_001B281C_base[3] __asm__("D_L06_001B281C") __attribute__((sda));
extern int D_L06_001B2838;
extern int D_L06_001B2348;

/* Overlays for an owner (L06Obj) and the state block it points to (L06Cfg); only the fields the
   next two functions touch are named. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L06Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L06Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L06Obj;

typedef struct {
    int a;
    int b;
} L06ColorPair;

extern void marker_draw_group(L06Obj *);
extern L06ColorPair D_L06_001B1098[];
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void moby_transform_joint_point(void *moby, int joint, void *out);
extern void gfx_add_draw_callback_first(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   colour pair and, when its stamp is not the current one, refreshes every live class-0xDB0
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L06_00444300 for the owner. */
void marker_update_pulse(L06Obj *self)
{
    L06Cfg *vars = self->cfg;
    L06ColorPair colors = D_L06_001B1098[0];
    unsigned short *id_cursor;
    L06Obj *entity;
    L06Cfg *entity_vars;
    float angle;
    float blend;

    angle = FastAddRotations(vars->angle, 0.20943954f);
    vars->angle = angle;
    blend = math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f;
    vars->blend = blend;
    self->tint = FastTweenColor(colors.a, colors.b, blend);
    if (vars->stamp != D_L06_001B2348) {
        for (id_cursor = (unsigned short *)D_L06_001FB3A0[self->group];
             self->group != 0xFF && self->group <= D_L06_001B2838 && id_cursor != 0 &&
             ((id_cursor != 0 && (short)id_cursor[-1] >= 0) || id_cursor == (unsigned short *)D_L06_001FB3A0[self->group]);
             id_cursor++) {
            entity = (L06Obj *)(D_L06_001B281C_base[0] + ((*id_cursor & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (entity->live != 0) {
                if (entity->cls == 0xDB0 /* moby class 3504 */) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (entity->kind != 0xFE) {
                        if (entity->kind != 0xFD) {
                            entity_vars = entity->cfg;
                            moby_transform_joint_point(entity, 0, &entity_vars->vec);
                            entity_vars->stamp = D_L06_001B2348;
                        }
                    }
                }
            }
        }
        gfx_add_draw_callback_first((void *)marker_draw_group, self);
    }
}

/* D_L06_001B10A0 is only used for its address, taken through $gp. D_L06_001B10B0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
extern int D_L06_001B10A0 __attribute__((sda));
extern int D_L06_001B10B0[2];
extern void FastVecScale(void *out, void *in, float scale);
extern void transform_vector(void *a, void *b, void *c);
extern void gfx_l00_draw_billboard_quad(void *buf, int color, float f12, float f13);

/* For every live class-0xDB0 entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the colour pair
   blended by the entity's pulse. */
void marker_draw_group(L06Obj *self)
{
    unsigned short *p;
    unsigned short *q;
    L06Obj *e;
    L06Cfg *s0;
    float buf[4];

    if (self->group == 0xFF)
        return;
    q = (unsigned short *)D_L06_001FB3A0[self->group];
    if (q == 0)
        return;
    for (p = q; self->group != 0xFF && self->group <= D_L06_001B2838 && p != 0 &&
                ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)D_L06_001FB3A0[self->group]);
         p++) {
        e = (L06Obj *)(D_L06_001B281C_base[0] + ((*p & 0x7FFF) << 8));
        if (e == 0)
            break;
        if (e->live != 0) {
            if (e->cls == 0xDB0 /* moby class 3504 */) {
                if (e->kind != 0xFE) {
                    if (e->kind != 0xFD) {
                        s0 = e->cfg;
                        FastVecScale(buf, &D_L06_001B10A0, s0->scale);
                        transform_vector(buf, buf, &s0->vec);
                        gfx_l00_draw_billboard_quad(buf,
                                          FastTweenColor(D_L06_001B10B0[0], D_L06_001B10B0[1],
                                                        s0->blend),
                                          s0->scale * 0.2f, 0.08f);
                    }
                }
            }
        }
    }
}

/* The level's three turn angles, in degrees (37, 41 and 70); the step below turns them into
   radians per frame. The first one is read through $gp, the other two absolutely. */
extern float D_L06_001B18D0 __attribute__((sda));
extern float D_L06_001B18D4;
extern float D_L06_001B18D8;

extern float func_32E5D0(float, float);
extern void func_32DE28(void *, void *);
extern void func_32DA88(void *, void *, void *);
extern void func_32D650(char *, char *, float);
extern void func_32D5C8(char *, char *, char *);
extern void moby_init_between_points(u8 *, void *, void *);

/* Turns the owner's three angles by the level's step, then walks the owner's eight records:
   each gets a fresh object, scaled and blended against the owner's own axes. `axes` is the
   scratch area func_32DE28 fills; its first vector is the one the objects are given. */
/* Spins a ring of eight objects around the owner by turning its three angles each frame. */
void object_ring_spin_update(char *moby)
{
    float axes[12];
    float v0[4];
    float v1[4];
    char *vars = *(char **)(moby + 0x68);
    char *point_ptr = vars + 0xA0;
    char *obj_ptr = vars + 0x80;
    char *center = moby + 0x10;
    float step = 0.000290888245f;
    float one = 1.0f;
    float two = 2.0f;
    int i;

    *(float *)(vars + 0x120) = func_32E5D0(*(float *)(vars + 0x120), D_L06_001B18D0 * step);
    *(float *)(vars + 0x124) = func_32E5D0(*(float *)(vars + 0x124), D_L06_001B18D4 * step);
    *(float *)(vars + 0x128) = func_32E5D0(*(float *)(vars + 0x128), D_L06_001B18D8 * step);
    func_32DE28(axes, vars + 0x120);
    for (i = 7; i >= 0; i--) {
        func_32DA88(v0, point_ptr, axes);
        point_ptr += 0x10;
        func_32D650((char *)v0, (char *)v0, 3.0f);
        func_32D650((char *)v1, (char *)v0, 3.3333335f);
        func_32D5C8((char *)v0, (char *)v0, center);
        func_32D5C8((char *)v1, (char *)v1, center);
        v0[3] = one;
        v1[3] = two;
        moby_init_between_points(*(u8 **)obj_ptr, v0, v1);
        obj_ptr += 4;
    }
}

/* Sets up the path follower the first time, then handles its hits and keeps its turning in step. */
int follower_init_and_check_hits(unsigned char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int hit_result, old_mode;
    if (moby[0x20] == 0) {
        if ((D_0019B2E8[moby[0xB0] + (g_current_map_index << 4)] & 0x80) && *(int *)(vars + 0x33C)) return 1;
        *(int *)(vars + 0x2AC) = 0;
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(int *)(vars + 0x254) = -1;
        *(int *)(vars + 0xA8) = 3;
        vars[0x70] = 7; vars[0x71] = 5; vars[0x72] = 6; vars[0x76] = 6; vars[0x77] = 6;
        *(float *)(vars + 0x7C) = 0.10000000894f;
        *(int *)(vars + 0x80) = 0;
        *(float *)(vars + 0x84) = 0.00416666688398f;
        *(float *)(vars + 0x88) = 0.00833333376795f;
        *(float *)(vars + 0x8C) = 0.00416666688398f;
        *(float *)(vars + 0x90) = 2.5f; *(int *)(vars + 0x94) = 0;
        *(float *)(vars + 0x9C) = .4f;
        vars[0xCC] = 4; vars[0xCD] = 8; vars[0xCE] = 4; vars[0xCF] = 8;
        vars[0xD2] = 4; vars[0xD3] = 8; vars[0xD4] = 0; vars[0xD6] = 1;
        *(float *)(vars + 0x2A8) = *(unsigned char *)(vars + 0x34);
        vars[0x28] = 3;
        *(int *)(vars + 0x30) = 0; *(int *)(vars + 0x258) = 0; *(int *)(vars + 0x26C) = 0;
        qzero(vars + 0x230);
        qcopy(vars + 0x220, g_path_list[*(int *)(vars + 0x274)] + 0x10);
        moby_set_state((char *)moby, 1, 0);
        if (moby[0x43] != 1) anim_start_blended((char *)moby, 1, 0, 0);
        moby[0x30] = 0x80; *(short *)(moby + 0x32) = 0x80;
        path_l01_compute_segment_lengths(g_path_list[*(int *)(vars + 0x274)]);
        path_l01_compute_segment_lengths(g_path_list[*(int *)(vars + 0x270)]);
        mem_clear(vars + 0x2B0, 0, 0x80);
    }
    *(int *)(vars + 0x258) = actor_choose_path_goal((char *)moby);
    *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24);
    old_mode = moby[0x95];
    hit_result = moby_apply_damage_to_object((char *)moby, vars + 0x60, 0);
    if (hit_result) {
        trigger_linked_object((char *)moby);
        if (hit_result < 4) PlayMobySound(2, 0, (char *)moby);
        if (old_mode == 1) *(int *)(vars + 0x24C) = math_random_int_range(300, 360);
        if ((unsigned int)(hit_result - 4) < 2) moby_set_state((char *)moby, 8, -1);
    }
    if (*(unsigned short *)(vars + 0x98) & 3) *(int *)(moby + 0x98) = 0;
    math_update_wrapped_angle_offset((char *)moby, vars + 0x280, vars + 0x284, .3f, .02327106148f, -1);
    moby_scale_owner_words_by_angles((char *)moby, vars + 0x288, vars + 0x28C, .1047197655f, .005235988647f, .006108653265982866f);
    return 0;
}

/* Runs a group of effect objects for the owner: sets them up, updates each step and hides them when the hero is too close. */
void effect_group_update(unsigned char *moby)
{
    char *vars;
    Context context;
    float position[4];
    int count, id, allowed;
    unsigned char *player = g_hero_state.player;
    if (player && *(short *)(player + 0xAA) == 0x45 /* moby class 69 */ && player[0x20] != 254 && player[0x20] != 253 && g_hero_state.mode == 49) return;
    vars = *(char **)(moby + 0x68);
    if (!vars) return;
    count = 1;
    if (*(int *)(vars + 0x18) != -1) count = D_L06_001B1858[*(int *)(vars + 0x18)];
    count += *(int *)(vars + 0x10);
    context.kind = 48; context.count = count;
    context.a = &D_L06_001B187C; context.b = &D_L06_001B1880;
    context.items = D_L06_002AA500; context.models = D_L06_00257CC0; context.data = D_L06_002DF000;
    context.states = D_L06_001B1858; context.aux = D_L06_00257FC0; context.more = D_L06_002DF060;
    context.update = effect_pool_clear; context.callback = gfx_add_draw_callback_third;
    context.owner = moby;
    if (*(unsigned char *)(vars + 0x14) == 0 && *(int *)(vars + 0x18) != -1) {
        char *firstTarget = D_L06_00188660 + *(int *)(vars + 0x38) * 0x70;
        if (*(unsigned char **)(firstTarget + 0x88) != moby || *(unsigned char *)(firstTarget + 0x74) == 0)
            *(int *)(vars + 0x38) = snd_start_in_slot(20, 4, (char *)moby);
    } else {
        id = *(int *)(vars + 0x38);
        if (id != -1) {
            char *secondTarget = D_L06_00188660 + id * 0x70;
            if (*(unsigned char **)(secondTarget + 0x88) == moby && *(unsigned char *)(secondTarget + 0x74)) snd_stop_voice(id);
        }
        *(int *)(vars + 0x38) = -1;
    }
    switch (moby[0x20]) {
    case 0:
        water_init_object(&context);
        water_add_splash_entry((char *)moby, *(float *)(vars + 0x34));
        if (*(int *)(vars + 0x28) != -1) {
            int alpha = 255;

            moby[0x30] = alpha;
        }
        /* fall through */
    case 1:
        water_update_controller(&context);
        break;
    case 2:
        water_advance_controller_state(&context);
        if (math_fabs(*(float *)(moby + 0x18) - *(float *)(vars + 0x2C)) <= 2 && *(int *)(vars + 0x18) != -1)
            math_step_value_toward_target((char *)moby + 0x18, vars + 0x30, *(float *)(vars + 0x2C), .0016666667070239782f, .0016666667070239782f, .10000000894f);
        break;
    }
    water_update_ripple_patches(&context);
    if (*(int *)(vars + 0x28) != -1 && !IsPointInCuboid(D_L06_001B9840, *(int *)(vars + 0x28))) {
        allowed = 1;
        if (*(int *)(D_L06_001B9840 + 0x2C0)) {
            qcopy(position, D_L06_001B9840);
            position[2] = *(float *)vars;
            if (IsPointInCuboid((char *)position, *(int *)(vars + 0x28))) allowed = 0;
        }
        if (allowed) {
            for (id = *(int *)(vars + 0x10); id < context.count; ++id)
                *(short *)(context.items + id * 0x1190 + 0x1E) = 0;
        }
    }
}
