#include "include_asm.h"
#include "common.h"
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern char g_sound_state[];
extern void gfx_draw_scrolling_surface_quad(void *);
extern char D_L14_001B9500[];
extern char D_0018A0E0[];
extern void VU1_addGSregister(unsigned int, unsigned long);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);

extern char g_hero_position[];
extern char D_L14_001A8F20[] __attribute__((sda));
/* The same entity-base pointer is read both absolutely and through $gp. */
extern char *D_L14_001B259C_gp SDATA(D_L14_001B259C);
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));
extern int moby_count_group_not_in_state(int, int);
extern float vec_distance_xy(void *, void *);
extern int flag_is_third_pending_set(void *);
extern int IsPointInCuboid(void *, int);
extern void anim_start_blended(void *, int, int, int);
extern int coll_test_point(void *, float, int, void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(void *);


typedef int PrisonQword __attribute__((mode(TI)));
typedef struct { PrisonQword v[4]; } PrisonMatrix;
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long long mode;
    char pad[24];
} PrisonQuad;
extern PrisonMatrix D_L14_001B1A00;


typedef struct { char pad[0x20]; float rate[4]; unsigned int start[4]; unsigned int end[4]; int timer[4]; float angle[4]; } PrisonVisualState;
extern void gfx_draw_rotated_billboard(void *, int, int, int, float, float, float);
extern float math_wrap_angle_full_turn(float);
extern void part_draw_spark_quads(void *);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern void PlayMobySound(int, int, void *);
extern int math_fast_float_d(void *);
extern void group_sync_counter(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void enemy_attach_turn_child_parts(void *, void *, int, void *, float);
extern void value_set_and_smooth(void *, void *, int, int, float);

extern char D_L14_001BF980[];

extern void func_00282F20_2(void *out, void *in, float scale);

extern void func_00282CC0_6(void *out, void *in1, void *in2);

extern int CollLine(void *a, void *b, int mode, void *self, int flag);

extern void func_00282D30_6(void *out, void *in, float scale);

/* Help-message (subtitle) history: how often each message was shown, when, and in which levels. */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;

typedef struct {
    char pad[4];
    unsigned char level;
    char rest[0xDB];
} PrisonGadget;

typedef struct {
    int zone[4];
    int row;
    int hintZone;
    int count;
    int pad1C;
    int target;
    char *moby;
    int active;
} PrisonHelpState;

extern SubtitleHistory g_subtitle_history[];
extern unsigned char g_item_slot_to_record[];
extern unsigned char D_00139630;
extern u8 D_0019B2E8[];
extern PrisonGadget D_L14_002686F0[];
extern int D_L14_001A8F00 __attribute__((sda));
extern short D_L14_001B22E0[] __attribute__((sda));
extern unsigned int D_001A7390 __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern int subtitle_request_voice_line(int, int);
extern int flag_is_byte_set(void);
extern int menu_seek_chain_entry(int, int);
extern void gfx_run_screen_update_steps(int);
extern void moby_rotate_about_point(void *, void *, float, float, float);

/* True once the gadget in slot 10 has been upgraded. */
static inline int prisonGadgetUpgraded(void)
{
    int level = (D_L14_002686F0 + g_item_slot_to_record[10])->level;

    return level >= 2;
}

/* Shows help message MSG unless its history entry IDX says it was shown in the last 18 seconds. */
static inline void prisonHelpTimed(int msg, int idx)
{
    if (D_001A7390 - g_subtitle_history[idx].time > 1080 || !g_subtitle_history[idx].time)
        subtitle_request_voice_line(msg, idx);
    else if (g_subtitle_history[idx].time < D_001A7390)
        g_subtitle_history[idx].time = D_001A7390;
}

/* The first time only records history entry IDX as seen in this level; later times show MSG. */
static inline void prisonHelp(int msg, int idx)
{
    if (g_subtitle_history[idx].count) {
        prisonHelpTimed(msg, idx);
    } else {
        g_subtitle_history[idx].count++;
        if (g_subtitle_history[idx].time < D_001A7390)
            g_subtitle_history[idx].time = D_001A7390;
        g_subtitle_history[idx].levels = (g_subtitle_history[idx].levels | (1u << g_current_map_index)) | 0x80000000u;
    }
}

/* Drives the prison's help prompts: links the target moby, plays the hints at the trigger zones
   and records which help messages were already shown. */
void help_prompt_update(char *obj)
{
    PrisonHelpState *st = *(PrisonHelpState **)(obj + 0x68);
    float vel[4] __attribute__((aligned(16)));

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(short *)(obj + 0x96) = 0;
        *(unsigned char *)(obj + 0x30) = 0xFF;
        if (st->target >= 0)
            st->moby = D_L14_001B259C_direct + (st->target << 8);
        else
            st->moby = 0;
        if (!prisonGadgetUpgraded()) {
            if (st->moby)
                st->active = 1;
            else
                st->active = 0;
        } else {
            if (st->moby) {
                *(unsigned short *)(st->moby + 0x34) |= 1;
                st->moby[0x31] = 0;
            }
            st->active = 0;
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(obj))
            st->count = 0;
        if (IsPointInCuboid(g_hero_position, st->zone[0])) {
            if (!prisonGadgetUpgraded())
                moby_set_state(obj, 2, -1);
        }
        if (st->active) {
            qcopy(vel, D_L14_001A8F20);
            vel[1] -= 0.1f;
            moby_rotate_about_point(st->moby, vel, 0.05f, 0.0f, 0.0f);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj))
            st->count = 0;
        if (D_L14_001A8F00 != 2 && st->count >= 6) {
            if (flag_is_byte_set())
                menu_seek_chain_entry(10, 5);
            else
                menu_seek_chain_entry(10, 2);
            gfx_run_screen_update_steps(2);
            if (st->moby) {
                *(unsigned short *)(st->moby + 0x34) |= 1;
                st->moby[0x31] = 0;
            }
            st->active = 0;
            moby_set_state(obj, 1, -1);
        }
        break;
    }

    if (IsPointInCuboid(g_hero_position, st->zone[1]) && !(D_00139630 & 2))
        prisonHelpTimed(0xA2C, 131);
    if (IsPointInCuboid(g_hero_position, st->zone[2])) {
        prisonHelp(0xA09, 96);
        g_subtitle_history[97].count = 0xFFFF;
    }
    if (IsPointInCuboid(g_hero_position, st->zone[3]) && D_L14_001B22E0[2])
        prisonHelp(0xA0A, 97);
    if (IsPointInCuboid(g_hero_position, st->hintZone) && !(D_0019B2E8[st->row + g_current_map_index * 16] & 0x80) &&
        g_subtitle_history[94].count < 2)
        prisonHelp(0xA07, 94);
    st->count++;
}


/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
unsigned int moby_get_owner_vars_word(unsigned int owner)
{
    unsigned int vars;
    unsigned int value;

    vars = *(unsigned int *)(owner + 0x68);
    value = *(unsigned int *)(vars + 0x18);
    return value;
}

/* Normalises and combines two temporary vectors from a state block, dispatches on the combined result and conditionally scales the output vector. */
void path_compute_probe_direction(char *self, char *out_dir, int keep_direction)
{
    float a[4];
    float b[4];

    func_00282F20_2(a, self + 224, 0.1f);
    func_00282F20_2(b, self + 224, -3.0f);
    func_00282CC0_6(a, a, self + 16);
    func_00282CC0_6(b, b, self + 16);

    if (CollLine(a, b, 2, self, 0))
        func_00282F20_2(out_dir, D_L14_001BF980, 1.0f);
    else
        func_00282F20_2(out_dir, self + 224, -1.0f);

    if (keep_direction == 0)
        func_00282D30_6(out_dir, out_dir, -1.0f);
}

extern unsigned char *g_moby_l14_pool __attribute__((sda));
extern void route_init_pool_record(void *);
extern int path_find_route_node_containing_point(void *, void *, int, int *);

typedef struct {
    int id;
    unsigned char links[4];
    unsigned char pad08[24];
} PrisonGraphNode;

typedef struct {
    unsigned char pad00[0x80];
    PrisonGraphNode nodes[32];
    int count;
} PrisonGraphState;

/* Looks up the graph nodes of first and second and, when they differ, sets (or with clear,
   clears) bit 7 of the link between them in both nodes' four link bytes. The links of node 0
   serve as the base for both scans, and both scans read the two ids from their stack slots. */
void path_set_link_blocked_flag(int index, void *first, void *second, int clear) {
    unsigned char *self = g_moby_l14_pool + index * 256;
    PrisonGraphState *state = *(PrisonGraphState **)(self + 0x68);
    int id0, id1;
    int i;
    unsigned char *links;
    unsigned char *entry;

    if (!self[0x20])
        route_init_pool_record(self);
    id0 = id1 = -1;
    if (path_find_route_node_containing_point(first, state->nodes, state->count, &id0)) {
        if (path_find_route_node_containing_point(second, state->nodes, state->count, &id1)) {
            if (id0 != id1) {
                links = state->nodes[0].links;
                i = 0;
                do {
                    entry = &links[id0 * sizeof(PrisonGraphNode) + i];
                    if ((*entry & 127) == id1) {
                        if (clear)
                            *entry &= 127;
                        else
                            *entry |= 128;
                        break;
                    }
                    ++i;
                } while (i < 4);
                i = 0;
                do {
                    entry = &links[id1 * sizeof(PrisonGraphNode) + i];
                    if ((*entry & 127) == id0) {
                        if (clear)
                            *entry &= 127;
                        else
                            *entry |= 128;
                        break;
                    }
                    ++i;
                } while (i < 4);
            }
        }
    }
}

/* func_L14_00421BC0 is in L14_003F4F98-f7-g8.c. */

/* func_L14_004221D8 is defined in L14_003F4F98-ribbon-g8.c (it reaches data through $gp and needs -frac2-qcopy). */


/* func_L14_004228C0 is defined in L14_003F4F98-g8.c. */

/* func_L14_004229A0 is defined in L14_003F4F98-ribbon-g8.c. */

extern void func_423000();
extern void func_423240();
extern void func_423358();
extern void func_423B30();
extern void func_423BD8();

/* Sets the actor up on its first frame, then updates it and its animations every frame. */
void space_l14_tourist_update(char *self)
{
    if (*(unsigned char *)(self + 0x20) == 0) {
        func_423000(self);
    } else {
        func_423240(self);
        func_423358(self);
        func_423B30(self);
        func_423BD8(self);
    }
}

/* func_L14_00423000 is defined in L14_00423000-qcopy.c (it needs the quadword-copy profile). */

/* func_L14_00423358 lives in L14_00423358-g8.c (small-data accesses). */

extern void moby_step_at_own_position_factor(char *object, float factor);

extern void moby_step_at_own_position(char *object);

extern void moby_step_controller(char *object, char *bone, float factor);

extern void moby_turn_toward_target_and_step(char *object, char *bone, float factor);

/* The level's own jump table (the label of the data blob at 0x002AA360). */
extern void *jtbl_002AA360[];

/* Dispatches on the owner's animation step and plays the matching bone animation. */
void actor_play_bone_anim(char *object)
{
    static void * volatile tab[] = { &&cA, &&cC };
    char *state;
    unsigned int sel;

    sel = *(unsigned char *)(object + 0x42) - 1;
    state = *(char **)(object + 0x68);
    if (sel < 19) {
        goto *jtbl_002AA360[sel];
    }
    goto end;
cA:
    if (*(short *)(state + 0x776) != 0) {
        moby_step_at_own_position_factor(object, *(float *)(state + 0x744));
    } else {
        moby_step_at_own_position(object);
    }
    goto out;
cC:
    if (*(short *)(state + 0x77A) != 0) {
        moby_step_controller(object, state + 0x700, *(float *)(state + 0x768));
    } else {
        moby_turn_toward_target_and_step(object, state + 0x700, *(float *)(state + 0x740));
    }
out:
end:
    return;
}

extern char D_L14_001B9500[];

extern void func_80326928(char *a0, void *a1);

extern void func_8032AA20(char *a0, void *a1, int a2, float a3, float a4);

extern float func_802F5DF8(char *a0, void *a1);

extern void func_803240F8(char *a0);

/* Restarts the owner's animation: two timed fades, the counter, then the panic state. */
void actor_restart_anim(char *self)
{
    char *vars;
    float fade_limit;
    float fade_speed;

    vars = *(char **)(self + 0x68);
    fade_speed = 0.03f;
    fade_limit = 0.3f;
    func_80326928(self, vars + 0x50);
    func_8032AA20(self, vars + 0x680, 1, fade_speed, fade_limit);
    func_8032AA20(self, vars + 0x600, 0, fade_speed, fade_limit);
    if (*(unsigned short *)(self + 0x96) <= 0xFFFE)
        *(unsigned short *)(self + 0x96) = *(unsigned short *)(self + 0x96) + 1;
    *(unsigned short *)(vars + 0x776) = 0;
    *(unsigned short *)(vars + 0x778) = 0;
    *(unsigned short *)(vars + 0x77A) = 0;
    if (*(unsigned char *)(self + 0x31) != 0) {
        if (func_802F5DF8(self + 0x10, D_L14_001B9500) < 24.0f) {
            func_803240F8(self);
            *(unsigned char *)(self + 0x6F) = 0x16;
        }
    }
}

extern void func_318ED0();
extern void func_2F5C68();
extern float func_2F62F0(float a, float b);
extern float func_2F5DB0(float *p);

/* Turns the actor to face a target point and works out how far to tilt its head. */
void actor_aim_at_target(char *self, int target_pos)
{
    float to_target[4];
    char *vars;
    float angle;

    vars = *(char **)(self + 0x68);
    *(unsigned short *)(vars + 0x776) = 1;
    func_318ED0(self, 2, to_target);
    func_2F5C68(to_target, target_pos, to_target);
    angle = func_2F62F0(to_target[0], to_target[1]);
    *(float *)(vars + 0x744) = angle;
    angle = func_2F5DB0(to_target);
    angle = -func_2F62F0(angle, to_target[2]) * 0.5f;
    *(float *)(vars + 0x6E4) = angle;
    *(float *)(vars + 0x664) = angle;
}

/* func_L14_00423E50 is defined in L14_00423E50-gu.c (it needs -frac2-gcse-unsplit-edges). */


typedef struct {
    char pad00[0x18];
    int exitTrigger;            /* 0x18 */
    int enterTrigger;           /* 0x1C */
    char pad20[0x10];
    int gateCamera;             /* 0x30 */
    int doorCamera;             /* 0x34 */
    int pad38;
    int lift;                   /* 0x3C: entity index */
    int panel;                  /* 0x40: entity index */
    int beam;                   /* 0x44: entity index */
    int guard;                  /* 0x48: entity index */
    int switchEntity;           /* 0x4C: entity index */
    int door;                   /* 0x50: entity index */
    int text54, text58, text5C; /* 0x54..0x5C */
    int zone60;                 /* 0x60 */
    int text64;                 /* 0x64 */
    float volume;               /* 0x68 */
    int fadeTimer;              /* 0x6C */
    int nextState;              /* 0x70 */
    int waitTimer;              /* 0x74 */
    int fadeLength;             /* 0x78 */
    int music7C, music80, music84, music88; /* 0x7C..0x88 */
    int frames;                 /* 0x8C */
} PrisonLiftState;

/* The 0x100-byte entity record (PrisonEntity, declared further down), with only the
   fields this function uses. */
typedef struct {
    char pad00[0x24];
    char *info;                 /* 0x24 */
    char pad28[0xC];
    unsigned short flags;       /* 0x34 */
    char pad36[0x62];
    int target;                 /* 0x98 */
} PrisonLiftEntity;

extern char *D_L14_001B268C __attribute__((sda));
extern int D_L14_001FF4A4;
extern char D_L14_001B17A0[];
extern u8 D_0019B2E8[];
extern char g_hero_position[];
extern u8 g_hero_state[];
extern int g_current_map_index __attribute__((sda));
extern int D_001A7A00 __attribute__((sda));
extern int D_001A8F00 __attribute__((sda));
extern int D_L14_001A8FB0 __attribute__((sda));
extern int D_L14_001A8FB4 __attribute__((sda));
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char D_001A7B30[] __attribute__((sda));
extern short D_001A63F0[];
extern int D_00138324;
extern u8 D_001395E1;

extern int IsPointInCuboid(void *, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void moby_activate_group_entities(void *);
extern void moby_set_flag_bit(void *, int);
extern int level_l00_call_module_handler_with_arg_10(int, int);
extern int flag_set_first_pending(void *);
extern void SetHeroMode(int, int, void *);
extern void script_queue_keyed_request(int, int);
extern void part_update_slot_triggered_record(void *);
extern int guard_is_defeated(void *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern void hero_reset_carried_objects(int); /* the parameter is unused */
extern int lift_is_moving(void *);
extern void lift_request_start(void *);
extern void moby_mark_spawned(void *);
extern void lift_set_moving_state(void *);
extern void moby_set_state(void *, int, int);
extern void hero_l00_set_action(int, int);
extern int math_fast_float_d(void *);
extern float math_fast_sin_or_cos_b(float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void snd_queue_level_jingle(char *);

/* Runs the prison lift scene: waits for the player, rides the lift, shows the guard and panel text, switches the music and opens the door. */
void lift_scene_update(unsigned char *moby) {
    PrisonLiftState *state = *(PrisonLiftState **)(moby + 0x68);
    unsigned char *lift = g_moby_l14_pool + state->lift * 256;
    unsigned char *panel = g_moby_l14_pool + state->panel * 256;
    unsigned char *guard = g_moby_l14_pool + state->guard * 256;
    PrisonQword pos;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        state->fadeLength = 0x7D;
        if (D_0019B2E8[state->text5C + g_current_map_index * 16] & 0x80) {
            if (IsPointInCuboid(g_hero_position, state->enterTrigger)) {
                hero_reset_position_and_direction(D_L14_001B268C + state->doorCamera * 128 + 0x30,
                                  D_L14_001B268C + state->doorCamera * 128 + 0x70, 0, 1);
                *(short *)(g_hero_position + 0x247C) = 0;
                g_item_owned_flags[2] = 1;
                D_001A7B30[2] = 1;
                g_item_owned_flags[3] = 1;
                D_001A7B30[3] = 1;
            }
            if (D_0019B2E8[state->zone60 + g_current_map_index * 16] & 0x80) {
                moby_activate_group_entities(moby);
                moby_set_flag_bit(g_moby_l14_pool + state->door * 256, 1);
            }
            moby_set_state(moby, 7, -1);
        } else {
            *(short *)(g_hero_position + 0x247C) = 1;
            g_item_owned_flags[2] = 0;
            D_001A7B30[2] = 0;
            g_item_owned_flags[3] = 0;
            D_001A7B30[3] = 0;
            if (D_0019B2E8[state->text58 + g_current_map_index * 16] & 0x80) {
                moby_activate_group_entities(moby);
                moby_set_state(moby, 5, -1);
            } else if (D_0019B2E8[state->text64 + g_current_map_index * 16] & 0x80) {
                moby_activate_group_entities(moby);
                moby_set_state(moby, 4, -1);
            } else if (D_0019B2E8[state->text54 + g_current_map_index * 16] & 0x80) {
                moby_set_state(moby, 3, -1);
            } else if (D_L14_001FF4A4 != 0) {
                moby_set_state(moby, 1, -1);
            } else {
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, state->enterTrigger)) {
            level_l00_call_module_handler_with_arg_10((int)D_L14_001B17A0, 1);
            D_L14_001A8FB0 = 2;
            D_L14_001A8FB4 = 8;
            if (D_00138324 & 0x10)
                moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            unsigned char *liftNow = g_moby_l14_pool + state->lift * 256;
            hero_reset_position_and_direction(liftNow + 0x10, liftNow + 0xF0, 0x6F, 1);
            SetHeroMode(1, 0x3F, liftNow);
            if (D_001A63F0[0] != state->music7C)
                script_queue_keyed_request(state->music7C, state->music88);
        }
        part_update_slot_triggered_record(moby);
        if (guard_is_defeated(guard)) {
            D_001395E1 = 1;
            moby_mark_table_entry_flagged(state->text54);
            level_capture_checkpoint_state(moby + 0xF0, moby + 0xF0);
            state->nextState = 3;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            hero_reset_carried_objects(0);
            hero_reset_position_and_direction(moby + 0x10, moby + 0xF0, 0, 1);
            moby_activate_group_entities(moby);
            *(int *)(g_hero_state + 0x24CC) = D_001A7A00;
            if (D_001A63F0[0] != state->music80)
                script_queue_keyed_request(state->music80, state->music88);
        }
        if (lift_is_moving(g_moby_l14_pool + state->panel * 256)) {
            moby_mark_table_entry_flagged(state->text64);
            level_capture_checkpoint_state(guard + 0x10, guard + 0xF0);
            state->nextState = 4;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            PrisonLiftEntity *beam;
            lift_request_start(panel);
            if (guard != 0 && guard[0x20] != 0xFE && guard[0x20] != 0xFD)
                moby_mark_spawned(guard);
            beam = (PrisonLiftEntity *)(g_moby_l14_pool + state->beam * 256);
            beam->target = 0;
            beam->flags = (beam->flags | 0x41) & ~0x1000;
            hero_reset_position_and_direction(guard + 0x10, guard + 0xF0, 0x6F, 1);
            SetHeroMode(1, 0x3F, lift);
            if (D_001A63F0[0] != state->music7C)
                script_queue_keyed_request(state->music7C, state->music88);
        }
        part_update_slot_triggered_record(moby);
        if (IsPointInCuboid(g_hero_position, state->exitTrigger)) {
            moby_mark_table_entry_flagged(state->text58);
            level_capture_checkpoint_state(&pos, panel + 0xF0);
            state->nextState = 5;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            PrisonLiftEntity *beam;
            moby_mark_spawned(lift);
            beam = (PrisonLiftEntity *)(g_moby_l14_pool + state->beam * 256);
            beam->flags = (beam->flags & ~0x41) | 0x1000;
            beam->target = *(int *)(beam->info + 0x10);
            qcopy(&pos, D_L14_001B268C + state->gateCamera * 128 + 0x30);
            if (g_hero_state[0x22B4] == 1)
                hero_reset_carried_objects(0);
            hero_reset_position_and_direction(&pos, D_L14_001B268C + state->gateCamera * 128 + 0x70, 0, 1);
            lift_set_moving_state(panel);
            *(int *)(g_hero_state + 0x24CC) = D_001A7A00;
            if (D_001A63F0[0] != state->music80)
                script_queue_keyed_request(state->music80, state->music88);
        }
        if (D_001A8F00 != 2 && g_moby_l14_pool[state->switchEntity * 256 + 0x20] > 0x80) {
            moby_mark_table_entry_flagged(state->text5C);
            level_capture_checkpoint_state(D_L14_001B268C + state->doorCamera * 128 + 0x30,
                          D_L14_001B268C + state->doorCamera * 128 + 0x70);
            g_item_owned_flags[2] = 1;
            D_001A7B30[2] = 1;
            g_item_owned_flags[3] = 1;
            D_001A7B30[3] = 1;
            *(short *)(g_hero_position + 0x247C) = 0;
            moby_set_state(moby, 7, -1);
        }
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            state->waitTimer = state->fadeLength;
            state->fadeTimer = state->fadeLength * 2;
            hero_l00_set_action(0x6F, 1);
        }
        if (math_fast_float_d(&state->waitTimer))
            moby_set_state(moby, state->nextState, -1);
        break;
    case 7:
        if (flag_set_first_pending(moby))
            state->frames = 0;
        if (D_001A8F00 != 2 && state->frames >= 6 && D_001A63F0[0] != state->music84)
            script_queue_keyed_request(state->music84, state->music88);
        state->frames++;
        break;
    default:
        break;
    }
    if (state->fadeTimer != 0) {
        math_fast_float_d(&state->fadeTimer);
        state->volume = math_fast_sin_or_cos_b((float)state->fadeTimer * 1.5707964f / (float)state->fadeLength);
        gfx_add_draw_callback_third((void (*)(void *))snd_queue_level_jingle, moby);
    }
}

/* func_L14_00426D18 lives in the -g8 sibling file (it reads a count through $gp). */

extern short g_screen_adjust_offsets[];

extern void func_385CB8(unsigned int reg, unsigned long value);

extern void func_2EF6D8(int, int, int, int, int);

/* Queues the level jingle for the owner with the volume its state block asks for. */
void snd_queue_level_jingle(char *self)
{
    char *vars;
    int fade_color;

    vars = *(char **)(self + 0x68);
    fade_color = ((int)((1.0f - *(float *)(vars + 0x68)) * 128.0f)) << 24;
    func_385CB8(0x42, 9);
    func_2EF6D8(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], fade_color);
}


/* func_L14_00426F28 is defined in L14_003F4F98-g8.c (it reaches data through $gp). */


/* func_L14_00427250 lives in the -g8 sibling file (it reaches a global through $gp). */


/* func_L14_004281D0 is defined in L14_004281D0-g8.c (it reaches data through $gp and needs the quadword-copy profile). */

extern unsigned char *g_group_entity_lists[];

/* The same global as D_L14_001B259C, under a second name: this access is
   $gp-relative, that one absolute. */
extern unsigned char *D_L14_001B259C_1 __attribute__((sda));

/* Walks the 0x7FFF-masked id list at table[index] and flags class 0x112B entries. */
void group_marker_alert_guards(unsigned char *self)
{
    unsigned char *base;
    unsigned char *p;
    unsigned short *q;
    char *entity;

    if (self[0x21] == 0xFF)
        return;
    p = g_group_entity_lists[self[0x21]];
    if (p == 0)
        return;
    q = (unsigned short *)p;
    base = D_L14_001B259C_1;
    for (;;) {
        entity = (char *)(base + ((*q & 0x7FFF) << 8));
        if ((signed char)entity[0x20] >= 0) {
            if (*(signed short *)(entity + 0xAA) == 0x112B /* moby class 4395 */) {
                *(unsigned short *)(*(unsigned int *)(entity + 0x68) + 0x316) = 1;
            }
        }
        if ((signed short)*q < 0)
            break;
        q++;
    }
}

/* func_L14_00428A08 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_00428BA0 lives in the -g8 sibling file (it reads two globals through $gp). */

/* func_L14_00428E68 is defined in L14_00428E68-g8.c. */

/* func_L14_004295D0 is defined in L14_004295D0-g8.c (it reaches data through $gp). */

/* Keeps the actor's walking animation in step with how far it moved this frame. */
void actor_update_walk_motion(unsigned char *self) {
    unsigned char *state = *(unsigned char **)(self + 0x68);
    float delta[4] __attribute__((aligned(16)));
    math_fast_float_d(state + 0x30c);
    math_fast_float_d(state + 0x310);
    if (*(unsigned short *)(self + 0x96) < 65535)
        ++*(unsigned short *)(self + 0x96);
    group_sync_counter(self, state + 0x308);
    FastVecSub(delta, self + 0x10, state + 0x2d0);
    qcopy(state + 0x2d0, self + 0x10);
    if (self[0x95] == 1) {
        *(float *)(state + 0x2fc) = FastAddRotations(*(float *)(state + 0x2fc), 0.2094395459f);
        enemy_attach_turn_child_parts(self, state + 0x300, 1, delta, *(float *)(state + 0x2fc));
    } else {
        *(float *)(state + 0x2fc) = FastAddRotations(*(float *)(state + 0x2fc), 0.01163553074002266f);
        enemy_attach_turn_child_parts(self, state + 0x300, 0, delta, *(float *)(state + 0x2fc));
    }
    value_set_and_smooth(self, state + 0x230, 7, 1, 2.0f);
}


extern void *func_801234F0(float scale);

extern long long func_80131430(long long value);

extern long long func_80122B00(long long a, long long b);

extern void *func_80122DA8(void *a, long long b);

extern float func_80123298(long long a);

extern void func_80321F58(char *a0, int a1, int a2);

/* Fills the owner's screen slot with the width the display state reports. */
void hud_init_display_width_value(char *self)
{
    char *vars;
    void *operand;
    long long result;

    vars = *(char **)(self + 0x68);
    if (*(unsigned char *)(self + 0x20) != 0)
        return;
    operand = func_801234F0(*(float *)(self + 0xC));
    result = func_80131430(0x4000000000000000LL);
    result = func_80122B00(result, 0x4090000000000000LL);
    result = func_80122DA8(operand, result);
    *(float *)(vars + 0x10) = func_80123298(result);
    func_80321F58(self, 1, -1);
}

/* func_L14_0042FB10 is defined in L14_0042FB10-effect-g8.c. */

/* Per-object state of the sliding gate (func_L14_0042FDA8). */
typedef struct {
    int linked[4];
    int f10;
    int f14;
    int f18;
    int group;
} PrisonGateState;

/* A 0x100-byte entity record. */
typedef struct {
    char pad00[0x10];
    float pos[4];
    u8 mode;
    char pad21[3];
    int *next;
    char pad28[0xC];
    u16 flags;
    char pad36[0xD];
    u8 anim;
    char pad44[0x1C];
    u8 animFlags;
    char pad61[7];
    PrisonGateState *state;
    char pad6C[0xC];
    int f78;
    char pad7C[0x19];
    u8 f95;
    char pad96[2];
    int f98;
    char pad9C[0x5C];
    float angle;
    char padFC[4];
} PrisonEntity;

/* Gate logic: opens when the player nears, is hit open by linked objects, and
   hands off to the next object when it slides clear. */
void sliding_l14_gate_update(PrisonEntity *self)
{
    float temp[4] __attribute__((aligned(16)));
    float front[4] __attribute__((aligned(16)));
    float left[4] __attribute__((aligned(16)));
    float right[4] __attribute__((aligned(16)));
    /* Passed unwritten to the left/right additions below, as retail does; the matching code needs that. */
    float offset1[4] __attribute__((aligned(16)));
    float offset2[4] __attribute__((aligned(16)));
    PrisonGateState *state = self->state;
    int i;
    int entry;
    int group;
    PrisonEntity *other;
    char *base;

    if (self->mode == 0) {
        /* Mark the group's members busy. */
        if (g_group_entity_lists[group = state->group] && moby_count_group_not_in_state(group, -1) >= 2) {
            unsigned short *list;

            list = (unsigned short *)g_group_entity_lists[state->group];
            base = D_L14_001B259C_direct;
            do {
                entry = *list;
                other = (PrisonEntity *)(base + ((entry & 0x7FFF) << 8));
                other->flags |= 0x43;
            } while ((group = (short)*list++) >= 0);
        }

        if (vec_distance_xy(&self->pos, g_hero_position) < 6.0f && flag_is_third_pending_set(self) &&
            !IsPointInCuboid(g_hero_position, state->f14) &&
            !IsPointInCuboid(g_hero_position, state->f18)) {
            self->mode = 1;
            self->f78 = 0x24C102;
            if (self->anim != 1)
                anim_start_blended(self, 1, 0, 0);
            self->f98 = 0;

            /* Release the group's members. */
            if (g_group_entity_lists[group = state->group] && moby_count_group_not_in_state(group, -1) >= 2) {
                unsigned short *list;

                list = (unsigned short *)g_group_entity_lists[state->group];
                base = D_L14_001B259C_direct;
                do {
                    entry = *list;
                    other = (PrisonEntity *)(base + ((entry & 0x7FFF) << 8));
                    other->flags &= 0xFFBC;
                } while ((group = (short)*list++) >= 0);
            }
        } else if (IsPointInCuboid(g_hero_position, state->f14)) {
            self->mode = 5;
        }

        for (i = 0; i < 4; i++) {
            int id = state->linked[i];

            if (id != -1) {
                other = (PrisonEntity *)(D_L14_001B259C_gp + (id << 8));
                if (other->f95 || (s8)other->mode < 0) {
                    if (state->f10) {
                        self->mode = 2;
                        qcopy(temp, self->pos);
                        temp[2] += 1.0f;
                        prisonStartSound(2, 0, self);
                        SpawnExplosionEffects(self, D_L14_001A8F20, temp, 0.0f, 0.0f, 10, 3, 16,
                            4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
                        return;
                    }
                    self->mode = 1;
                    if (self->anim != 1)
                        anim_start_blended(self, 1, 0, 0);
                    self->f98 = 0;
                }
            }
        }
    }

    if (self->mode == 1 && (self->animFlags & 2)) {
        self->mode = 3;
        self->f78 = 0x224C1;
        if (self->anim != 2)
            anim_start_blended(self, 2, 0, 0);
    }

    if (self->mode == 2) {
        temp[0] = math_fast_sin_or_cos_a(self->angle - 1.57079649f) * 0.3f;
        temp[1] = math_fast_sin_or_cos_b(self->angle - 1.57079649f) * 0.3f;
        temp[2] = 0;
        FastVecAdd(self->pos, self->pos, temp);
        qcopy(front, self->pos);
        qcopy(left, self->pos);
        qcopy(right, self->pos);
        front[2] += 0.75f;
        left[2] += 0.75f;
        right[2] += 0.75f;
        temp[0] = math_fast_sin_or_cos_a(self->angle) * 0.8f;
        temp[1] = math_fast_sin_or_cos_b(self->angle) * 0.8f;
        temp[2] = 0;
        temp[0] = math_fast_sin_or_cos_a(self->angle + 3.14159298f) * 0.8f;
        temp[1] = math_fast_sin_or_cos_b(self->angle + 3.14159298f) * 0.8f;
        temp[2] = 0;
        FastVecAdd(left, left, offset1);
        FastVecAdd(right, right, offset2);
        if (coll_test_point(front, 0.6f, 0, self) || coll_test_point(left, 0.68f, 0, self) || coll_test_point(right, 0.68f, 0, self)) {
            prisonStartSound(2, 0, self);
            SpawnExplosionEffects(self, D_L14_001A8F20, front, 0.0f, 0.0f, 10, 3, 16,
                4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
            moby_mark_spawned(self);
            return;
        }
    }

    if (self->mode == 3 && IsPointInCuboid(g_hero_position, state->f14)) {
        self->mode = 4;
        if (self->anim != 3)
            anim_start_blended(self, 3, 0, 0);
    }

    if (self->mode == 4 && (self->animFlags & 2)) {
        self->mode = 5;
        self->f98 = self->next[4];
        if (self->anim)
            anim_start_blended(self, 0, 0, 0);
    }
}


/* func_L14_00430410 is defined in L14_00430410-g8.c. */

extern float func_2F6DA0(float x);

/* Wraps an angle into the range of one full turn. */
float math_wrap_angle_full_turn(float x)
{
    return func_2F6DA0(x * 0.15915494f) * 6.2831855f;
}

/* Builds a camera-facing quad and rotates its texture coordinates about their center. */
void gfx_draw_rotated_billboard(void *position, int texture, int color, int mode,
                     float scale, float distance, float angle)
{
    PrisonQuad q;
    float xy[2];
    float forward[4], right[4], up[4], center[4], offset[4];
    PrisonMatrix matrix;
    float c, s;
    int i, j;
    char *u, *v;
    float (*dst)[4], (*mat)[4];

    gfx_init_quad_packet_state(&q, texture, mode, 128);
    q.mode = 5;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = color;
    q.uv[0][0] = 0; q.uv[0][1] = 0;
    q.uv[1][0] = 0; q.uv[1][1] = 1;
    q.uv[2][0] = 1; q.uv[2][1] = 0;
    q.uv[3][0] = 1; q.uv[3][1] = 1;
    c = math_fast_sin_or_cos_a(angle);
    s = math_fast_sin_or_cos_b(angle);
    /* Walk the whole packet so the final cursors remain within its storage. */
    v = (char *)&q + 0x54;
    u = (char *)&q + 0x50;
    for (i = 3; i >= 0; i--) {
        xy[0] = *(float *)u - 0.5f;
        xy[1] = *(float *)v - 0.5f;
        *(float *)u = xy[0] * c - xy[1] * s;
        *(float *)v = xy[0] * s + xy[1] * c;
        *(float *)u += 0.5f;
        u += 8;
        *(float *)v += 0.5f;
        v += 8;
    }
    qcopy(center, position);
    FastVecSub(forward, D_L14_001B9500, center);
    vec_scale_to_length(forward, forward, 1.0f);
    FastVecCross(right, forward, D_0018A0E0);
    vec_scale_to_length(right, right, 1.0f);
    FastVecCross(up, right, forward);
    FastVecScale(offset, forward, distance);
    FastVecAdd(center, center, offset);
    matrix.v[0] = D_L14_001B1A00.v[0];
    matrix.v[1] = D_L14_001B1A00.v[1];
    matrix.v[2] = D_L14_001B1A00.v[2];
    matrix.v[3] = D_L14_001B1A00.v[3];
    dst = q.pos;
    mat = (float (*)[4])&matrix;
    for (j = 3; j >= 0; j--, dst++) {
        FastVecScale(*dst, *mat, scale);
        mat++;
        transform_vector(*dst, *dst, forward);
    }
    VU1_addGSregister(0x47, 0x53001);
    draw_world_quad(&q, 0, 0);
    VU1_addGSregister(0x47, 0x5360B);
}

/* func_L14_00430B70 is defined in L14_00430B70-visual.c. */

/* func_L14_00430E08 is defined in L14_00430B70-visual.c. */

/* Distinct no-op entries: the first is called directly, the second by the moby table. */
/* Does nothing. Used where a handler is required but no update is needed. */
void level_noop_handler_a(void *object)
{
}

/* Does nothing. A second empty handler, used by the moby table. */
void level_noop_handler_b(void *object)
{
}

extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern char g_sound_state[];
extern void gfx_draw_scrolling_surface_quad(void *);

/* Plays a looping ambient sound with random pauses and draws the moby's surface every frame. */
void ambient_sound_surface_update(char *object)
{
    int *vars = *(int **)(object + 0x68);
    switch ((unsigned char)object[0x20]) {
    case 0:
        vars[10] += 63;
        vars[11] += 63;
        vars[12] += 63;
        vars[13] += 63;
        vars[14] += 63;
        vars[15] = 10;
        vars[16] = -1;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        moby_set_state(object, math_random_int_range(2, 3), -1);
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            if (vars[16] != -1 && ((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->owner == object && ((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->active)
                snd_stop_voice(vars[16]);
            vars[16] = -1;
            vars[3] = math_random_int_range(vars[0], vars[1]);
        }
        if (((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->owner != object || !((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->active)
            vars[16] = prisonStartSound(0, 4, object);
        if (math_fast_float_d(vars + 3))
            moby_set_state(object, 1, -1);
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            if (vars[16] != -1 && ((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->owner == object && ((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->active)
                snd_stop_voice(vars[16]);
            vars[16] = -1;
            vars[3] = math_random_int_range(vars[0], vars[1]);
        }
        if (((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->owner != object || !((PrisonSoundAnchor *)(g_sound_state + vars[16] * 112))->active)
            vars[16] = prisonStartSound(1, 4, object);
        if (math_fast_float_d(vars + 3))
            moby_set_state(object, 1, -1);
        break;
    }
    gfx_add_draw_callback_third(gfx_draw_scrolling_surface_quad, object);
}
