#include "common.h"

extern int D_L14_001B17D8 __attribute__((sda));
extern int D_L14_001B17DC;
extern int D_001A72E0;

extern int FastTweenColor(int a, int b, float c);
extern void func_385CB8(unsigned int reg, unsigned long value);
extern void func_3030C0(int, int, int, int, int, int);

/* Plays one sound effect derived from the owner's state block and then queues the level jingle. */
void searchlight_draw_glow(char *self)
{
    char *state;
    int blend_color;

    state = *(char **)(self + 0x68);
    blend_color = FastTweenColor(D_L14_001B17D8, D_L14_001B17DC, *(float *)state);
    func_385CB8(0x42, 0x8000000044UL);
    func_3030C0(0, 0, 600, 500, blend_color, 0);
    func_385CB8(0x4E, 0x1000000UL | (D_001A72E0 >> 13));
}

extern float D_L14_001B17B8 __attribute__((sda));
extern float D_L14_001B17BC __attribute__((sda));

extern char g_hero_position[];

extern void *cam_alloc_override_slot(int size);

extern void cam_end_override(void *block);

extern int IsPointInCuboid(void *, int);

typedef struct {
    float x;
    float y;
} EffectPair;

/* Scans the four slot words at state+0x20; at the first one that is set and passes func_002ACBC8,
   makes sure the pool record at state+0x14 exists and writes D_L14_001B17B8/BC into its first two
   floats. If none passes, frees the record. */
void part_update_slot_triggered_record(char *self)
{
    char *state = *(char **)(self + 0x68);
    int *slot = (int *)(state + 0x20);
    int i;

    for (i = 0; i < 4; i++, slot++) {
        if (*slot != -1 && IsPointInCuboid(g_hero_position, *slot) != 0) {
            if (*(EffectPair **)(state + 0x14) == 0) {
                *(EffectPair **)(state + 0x14) = cam_alloc_override_slot(5);
            }
            (*(EffectPair **)(state + 0x14))->x = D_L14_001B17B8;
            (*(EffectPair **)(state + 0x14))->y = D_L14_001B17BC;
            return;
        }
    }

    if (*(EffectPair **)(state + 0x14) != 0) {
        cam_end_override(*(EffectPair **)(state + 0x14));
        *(EffectPair **)(state + 0x14) = 0;
    }
}

/* The light object: state byte, an update flag, the visibility flags, its state block,
   a frame counter and a word cleared when it shuts down. */
typedef struct PrisonLight {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x10];
    u8 update;           /* 0x31 */
    u8 pad32[2];
    u16 flags;           /* 0x34 */
    u8 pad36[0x32];
    struct PrisonLightState *vars; /* 0x68 */
    u8 pad6C[0x2A];
    u16 frames;          /* 0x96 */
    u32 pending;         /* 0x98 */
} PrisonLight;

/* Its state block: the beam level, the done flag and the sound slot. */
typedef struct PrisonLightState {
    float level;         /* 0x0 */
    int done;            /* 0x4 */
    int sound;           /* 0x8 */
} PrisonLightState;

/* A sound slot as seen from D_00188660 plus 0x70 per slot number. */
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern char g_sound_state[];
extern unsigned char D_0018C0D4 NOT_SDA;
extern char D_L14_001B17E0[], D_L14_001B1800[];
extern int D_L14_001B20C8;
extern int D_L14_001B17C0 SDATA(D_L14_001B17C0);
extern float D_L14_001B17C4 SDATA(D_L14_001B17C4);
extern float D_L14_001B17C8 SDATA(D_L14_001B17C8);
extern float D_L14_001B17D0 SDATA(D_L14_001B17D0);
extern float D_L14_001B17D4 MACRO_ADDR;

extern void moby_set_state(void *self, int state, int mode);
extern void *part_find_owned_effect_slot(void *a0, int a1, int a2);
extern int flag_is_third_pending_set(void *);
extern int PlayMobySound(int a, int b, void *self);
extern void snd_stop_voice(int);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern float ApproachValue(float *, float, float);
extern void moby_mark_spawned(void *a0);
extern void level_l00_call_module_handler_with_arg_9(int, int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void part_spawn_spark_side(void *);

/* A prison searchlight: waits for the alarm, sweeps while it lasts, then fades out. */
/* Updates the prison searchlight: waits for the alarm, sweeps its beam, then fades out. */
void searchlight_update(PrisonLight *object)
{
    PrisonLightState *state = object->vars;
    float angle, denominator;
    int period, ticks;
    unsigned int counter, previous;
    unsigned short flags;

    switch (object->state) {
    case 0:
        moby_set_state(object, 1, -1);
        state->sound = -1;
        break;
    case 1:
        if (D_0018C0D4 != 1)
            break;
        if (object->update)
            part_spawn_spark_side(object);
        if (part_find_owned_effect_slot(object, 0x10000, 0) || flag_is_third_pending_set(object)) {
            level_l00_call_module_handler_with_arg_9((int)D_L14_001B17E0, 240);
            moby_set_state(object, 2, -1);
        }
        if (((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->owner != object || !((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->active)
            state->sound = PlayMobySound(0, 4, object);
        break;
    case 2:
        ticks = D_L14_001B20C8;
        period = D_L14_001B17C0;
        angle = IntToFloat(ticks % period);
        denominator = IntToFloat(period);
        angle *= 6.2831855f;
        angle /= denominator;
        angle = math_fast_sin_or_cos_b(angle - 3.1415927f);
        ApproachValue(&state->level, D_L14_001B17C4 * angle + D_L14_001B17C8, D_L14_001B17D0 * 0.016666668f);
        gfx_add_draw_callback_first((void *)searchlight_draw_glow, object);
        counter = object->frames;
        previous = counter++;
        object->frames = counter;
        if (previous >= 181)
            state->done = 1;
        if (state->sound != -1 && ((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->owner == object && ((PrisonSoundAnchor *)(g_sound_state + state->sound * 112))->active)
            snd_stop_voice(state->sound);
        state->sound = -1;
        if (!D_0018C0D4) {
            level_l00_call_module_handler_with_arg_9((int)D_L14_001B1800, 240);
            flags = object->flags;
            object->pending = 0;
            flags |= 0x41;
            flags &= 0xefff;
            object->flags = flags;
            moby_set_state(object, 3, -1);
        }
        break;
    case 3:
        gfx_add_draw_callback_first((void *)searchlight_draw_glow, object);
        ApproachValue(&state->level, 0.0f, D_L14_001B17D4 * 0.016666668f);
        if (state->level == 0.0f)
            moby_mark_spawned(object);
        break;
    }
}

extern float D_L14_001B16B0 __attribute__((sda));
extern int moby_apply_damage_to_object(char *a0, char *a1, int a2);
extern void part_spawn_explosion_with_sparks(char *a0, char *a1, float f12, float f13, int a2);
extern void SetDeathBits(char *a0, int a1, int a2);

/* Resets the moby's scale when its model says so, then lets it fall or die. */
/* Updates a falling object that dies when it runs out of health or drops too low, and fixes the size of its Protopet child. */
void protopet_holder_update(char *moby)
{
    char *moby_alias = moby;
    char *state;
    char *child_model;
    char *child;

    state = *(char **)(moby_alias + 0x68);
    child = (char *)part_find_owned_effect_slot(moby, 0x10000, 1);
    if (child != 0) {
        child_model = *(char **)(child + 0x20);
        if (child_model != 0 && *(short *)(child_model + 0xAA) == MOBY_CLASS_PROTOPET) {
            if (*(unsigned char *)(moby_alias + 0x31) == 0)
                *(float *)(child + 0x2C) = 0.0f;
            else
                *(float *)(child + 0x2C) = 1.0f;
        }
    }
    moby_apply_damage_to_object(moby_alias, state + 0x60, 0);
    if (*(float *)(state + 0x20) <= 0.0f) {
        part_spawn_explosion_with_sparks(moby_alias, moby_alias + 0x10, 1.0f, 13.0f, -1);
        SetDeathBits(moby_alias, 0, 3);
        moby_mark_spawned(moby_alias);
    } else if (*(float *)(moby_alias + 0x18) < D_L14_001B16B0) {
        SetDeathBits(moby_alias, 0, 3);
        moby_mark_spawned(moby_alias);
    }
}

extern float D_L14_001B1678 __attribute__((sda));
extern float D_L14_001B167C __attribute__((sda));
extern int D_L14_001B1660 __attribute__((sda));
extern int D_L14_001B1668 __attribute__((sda));
extern int D_L14_001B1690 __attribute__((sda));
extern int D_L14_001B1694 __attribute__((sda));
extern float D_L14_001B1698 __attribute__((sda));
extern float D_L14_001B169C __attribute__((sda));
extern float D_L14_001B16A0 __attribute__((sda));
extern float D_L14_001B16A4 __attribute__((sda));
extern char D_L14_002594F0[][0x280];
extern void DrawPrisonScrollingRibbonWithHalo(char *, char *, int, int, int, float, float, float);

/* Draws the two glowing ribbons of the moby, scrolling the texture a little each frame. */
void gfx_draw_ribbon_pair(char *object) {
    char *state = *(char **)(object + 0x68);

    D_L14_001B1678 -= D_L14_001B167C;
    if (D_L14_001B1678 <= -8.0f)
        D_L14_001B1678 += 8.0f;
    DrawPrisonScrollingRibbonWithHalo(object, D_L14_002594F0[*(int *)(state + 0x38)],
        D_L14_001B1660, D_L14_001B1668, *(int *)(state + 0x2C) - 2,
        *(float *)(state + 0x40), *(float *)(state + 0x44), D_L14_001B16A0);
    DrawPrisonScrollingRibbonWithHalo(object, D_L14_002594F0[*(int *)(state + 0x38)] + 0x140,
        D_L14_001B1690, D_L14_001B1694, *(int *)(state + 0x2C),
        D_L14_001B1698, D_L14_001B169C, D_L14_001B16A4);
}

extern int g_moby_l14_pool __attribute__((sda));

extern int hero_is_current_selected_id(char *self);
extern void moby_set_flag_bit(int table, int mode);
extern int flag_set_first_pending(char *self);
extern float FastAddRotations(float a, float b);
extern float math_fast_sin_or_cos_b(float a);
extern int FastTweenColor(int a, int b, float c);

/* Steps the owner's state block, then blends the two colours its state asks for. */
void pulsing_tint_update(char *self)
{
    char *v = *(char **)(self + 0x68);
    int c1 = 0x808C8C8C;
    int c2 = 0x80282828;
    int idx;
    float f;
    int r;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (hero_is_current_selected_id(self) != 0) {
            idx = *(int *)(v + 0);
            if (idx != -1) {
                moby_set_flag_bit(g_moby_l14_pool + (idx << 8), 1);
            }
            moby_set_state(self, 1, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(self) != 0) {
            PlayMobySound(0, 0, self);
        }
        c1 = 0x80468CDC;
        c2 = 0x801E78AA;
        break;
    }
    f = FastAddRotations(*(float *)(v + 4), 0.10762865f);
    *(float *)(v + 4) = f;
    r = FastTweenColor(c1, c2, math_fast_sin_or_cos_b(f) * 0.5f + 0.5f);
    *(int *)(self + 0x78) = FastTweenColor(*(int *)(self + 0x78), r, 0.15f);
}

/* The id-list walks below (func_L14_00426D18, func_L14_00428A08, func_L14_00428BA0) read
   D_L14_001B259C as a bare symbol, while the `sda` int above reaches the same word through $gp.
   The assembler takes the last `.extern` size it has seen: the second name's 12 bytes (bare
   `lui`/`lw`) must come after the 4 bytes of the int's, so these functions follow
   func_L14_00409B20. D_L14_001B25B8 is a plain int: its `.extern` comes last in the file, which
   leaves a load in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern unsigned short *g_group_entity_lists[];
extern int D_L14_001B25B8;
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));

/* Sets the flag bit (+0xBE, 4) of every entity in the id list the state's group word names,
   unless the word is -1. */
void moby_activate_group_entities(char *self)
{
    char *state = *(char **)(self + 0x68);
    unsigned short *p;
    unsigned char *e;

    if (state != 0 && *(int *)(state + 0x38) != -1) {
        for (p = g_group_entity_lists[*(int *)(state + 0x38)];
             (*(int *)(state + 0x38) & 0xFF) != 0xFF && *(int *)(state + 0x38) <= D_L14_001B25B8 &&
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[*(int *)(state + 0x38)]);
             p++) {
            e = D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            moby_set_flag_bit((int)e, 1);
        }
    }
}

/* Overlays for an owner (L14Obj) and the state block it points to (L14Cfg); only the fields the
   next two functions touch are named. Typed member accesses are what give retail's order of the
   compare's two loads (the scalar global first): with `*(int *)(p + off)` casts the field load
   is scheduled ahead of it. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L14Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L14Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L14Obj;

typedef struct {
    int a;
    int b;
} L14ColorPair;

extern void group_marker_draw(L14Obj *);
extern L14ColorPair D_L14_001B18C0[];
extern void moby_transform_joint_point(void *moby, int joint, void *out);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   first colour pair and, when its stamp is not the current one, refreshes every live class-0x112B
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L14_00428BA0 for the owner. */
void group_marker_update_pulse(L14Obj *self)
{
    L14Cfg *state = self->cfg;
    L14ColorPair colors = D_L14_001B18C0[0];
    unsigned short *p;
    L14Obj *e;
    L14Cfg *s0;
    float angle;
    float blend;

    angle = FastAddRotations(state->angle, 0.20943954f);
    state->angle = angle;
    blend = math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = FastTweenColor(colors.a, colors.b, blend);
    if (state->stamp != D_L14_001B20C8) {
        for (p = g_group_entity_lists[self->group];
             self->group != 0xFF && self->group <= D_L14_001B25B8 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[self->group]);
             p++) {
            e = (L14Obj *)(D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->live != 0) {
                if (e->cls == 0x112B /* moby class 4395 */) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (e->kind != 0xFE) {
                        if (e->kind != 0xFD) {
                            s0 = e->cfg;
                            moby_transform_joint_point(e, 0, &s0->vec);
                            s0->stamp = D_L14_001B20C8;
                        }
                    }
                }
            }
        }
        gfx_add_draw_callback_first((void *)group_marker_draw, self);
    }
}

/* D_L14_001B18D0 is only used for its address, taken through $gp. D_L14_001B18E0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
extern int D_L14_001B18D0 __attribute__((sda));
extern int D_L14_001B18E0[2];
extern void FastVecScale(void *out, void *in, float scale);
extern void transform_vector(void *a, void *b, void *c);
extern void gfx_l00_draw_billboard_quad(void *buf, int color, float f12, float f13);

/* For every live class-0x112B entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the second colour
   pair blended by the entity's pulse. */
void group_marker_draw(L14Obj *self)
{
    unsigned short *p;
    unsigned short *q;
    L14Obj *e;
    L14Cfg *s0;
    float buf[4];

    if (self->group == 0xFF)
        return;
    q = g_group_entity_lists[self->group];
    if (q == 0)
        return;
    for (p = q; self->group != 0xFF && self->group <= D_L14_001B25B8 && p != 0 &&
                ((p != 0 && (short)p[-1] >= 0) || p == g_group_entity_lists[self->group]);
         p++) {
        e = (L14Obj *)(D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8));
        if (e == 0)
            break;
        if (e->live != 0) {
            if (e->cls == 0x112B /* moby class 4395 */) {
                if (e->kind != 0xFE) {
                    if (e->kind != 0xFD) {
                        s0 = e->cfg;
                        FastVecScale(buf, &D_L14_001B18D0, s0->scale);
                        transform_vector(buf, buf, &s0->vec);
                        gfx_l00_draw_billboard_quad(buf,
                                          FastTweenColor(D_L14_001B18E0[0], D_L14_001B18E0[1],
                                                        s0->blend),
                                          s0->scale * 0.2f, 0.08f);
                    }
                }
            }
        }
    }
}
