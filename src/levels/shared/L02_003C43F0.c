#include "include_asm.h"
#include "common.h"


extern void vec_clear_128(void *);
extern void vec_random_direction(void *, float, float);

typedef int TI128 __attribute__((mode(TI)));

extern void moby_mark_spawned(void *);

struct CD758Object {
    char pad0[0x10];
    float pos[4];
    char pad1[0x48];
    struct CD758Data *data;
    char pad2[0x84];
    float angles[3];
};

struct CD758Data {
    char pad[0x370];
    char *other;
};

extern int FastDecTimer(void *);

extern void FastVecSub(float *, const float *, const float *);

extern void vec_transform_by_object_or_given(unsigned char *, unsigned char *, unsigned char *, int);

extern float mat_fast_helper_a(float, float);

extern float vec_length_xy(char *);

extern float math_random_float_range(float, float);

extern float math_random_angle(void);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern void FastVecAdd(void *, void *, void *);

extern void moby_update_eased_node(void *, void *, int, float, float);

extern void value_set_and_smooth(void *, void *, int, float, int);

extern void vec_subtract_vec4(void *, void *, void *);

extern void vec_scale_to_length(char *, char *, float);

extern float FastVecDot(void *, void *);

extern char *g_route_polygons[];

extern char *g_moby_l02_pool __attribute__((sda));

extern char *g_entity_group_lists[];

extern float func_00283C80_3(float, float);

extern float func_00283B98_12(float, float);

extern float func_00283BE0_7(float, float);

extern void func_002833F0_2(void *, void *);

extern int snd_play_from_class_bank(int, int, void *, int);

extern void moby_transform_joint_to_world(char *, int, void *);

extern void *func_801234F0(float);

extern void STUB_printf(void *, int, int, int, int);

extern void hero_start_target_state(void *, int, float);

extern char D_L02_001AFE38[];

extern void SetDeathBits(void *, int, int);

extern void data_set_small_value_and_refresh(int, int);

extern f32 fade_reduce_value(float);

extern int PadPressedWithin(int, int, int);

extern void moby_set_state(void *, int, int);

extern s32 snd_resume_music_stream(void);

extern void anim_start_blended(void *, int, int, int);

extern void UpdateRotatingBouncingEffect(void);

extern void gfx_add_draw_callback_third(void *, void *);

extern void part_spawn_fading_spark(void);

extern int moby_aim_at_target_offset(char *, char *);

extern int moby_l01_turn_toward_target(char *, char *);

extern int moby_turn_toward_target_and_step(char *, float *, float);

extern struct S_001A63A8 g_music_state;

extern int D_L02_001A8FF0 __attribute__((sda));

extern void moby_set_controller_speed_limits(void *, float, float, float, float);

extern long long GetEffectTextureDescriptor(char *);

extern float vec_distance_xy(void *, void *);

extern int IsPointInCuboid(void *, int);

/* The level's three trigger boxes and the point they hold. */
extern char D_L02_001AFEA0[];

extern char g_hero_position[];

extern void euler_to_matrix(float *, float *);

extern void draw_world_quad(char *, float *, int);

/* The emitter table in the boot's resident memory, a ring of 0x70-byte records. */
extern unsigned char g_sound_state[];

/* The level's own emitter counter, in the level's data. */
extern int D_L02_001B3FD8 __attribute__((sda));

extern void platform_init(void *);

extern void part_spawn_puff_at_moby(void *);

extern void moby_push_nearby_sideways(void *);

extern void moby_update_attached_transforms(void *, void *);

extern void multiply_matrix3x3(void *, void *, void *);

extern void copy_matrix_rotation(void *, void *);

extern void mat_get_euler_angles(float *, float *);

extern int PlayMobySound(int, int, char *);

extern int snd_is_voice_playing_for_owner(int, int);

extern void snd_stop_voice(int);

extern int math_fast_float_d(void *);

/* The packet reset, which the levels place in two copies: the one this function calls
   differs from level to level. */
extern void ref_L02_003FFC48_00(char *);

/* The vector scaler, in two copies as well. */
extern void ref_L02_003FFC48_01(char *, float);

struct S_001A63A8 {
    char pad0[0x6C];
    short f6C;
    char pad1[4];
    short f72;
};

struct Sub {
    float f0;
    int f4;
    int p8;
    int p12;
    int p16;
    int f20;
};

struct Elem {
    char pad[104];
    struct Sub *sub;
    char pad2[140];
    float f248;
};

struct G {
    char pad[192];
    struct Elem *arr[22];
    int count;
};

struct Outer {
    char pad[104];
    struct G *g;
};

/* The aim vector the L02 aiming helpers read, at 0x001BA3C0. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L02AimVector;

extern L02AimVector D_L02_001BA3C0;

typedef int BatchA_A17_s32;

typedef short BatchA_A17_BatchAs16;

/* func_L02_003C43F0 is defined in L02_003C43F0-menu-g8.c. */

/* Walks an inline array of element pointers; for each element whose sub-object flag at +4 is zero it rewrites a 270-degree angle to -90, scales it by pi/180, compares a helper result against 0.001 and routes it through one of two pi/2 helpers, toggles the flag, then calls a two-pointer helper with element+192 and element+240. */
/* Flips each element in the list to the opposite turn direction and turns it a quarter turn. Then it plays a sound for the first element. */
void moby_flip_element_turn_directions(struct Outer *outer)
{
    struct G *list = outer->g;
    int i;

    for (i = 0; i < list->count; i++) {
        struct Sub *sub = list->arr[i]->sub;

        if (sub->f4 == 0) {
            if (sub->f0 == 270.0f)
                sub->f0 = -90.0f;
            if (func_00283C80_3(list->arr[i]->f248, sub->f0 * 1.7453294247388839721680e-02f)
                < 1.0000000474974513053894e-03f)
                list->arr[i]->f248 = func_00283B98_12(list->arr[i]->f248, 1.5707964897155761718750e+00f);
            else
                list->arr[i]->f248 = func_00283BE0_7(list->arr[i]->f248, 1.5707964897155761718750e+00f);
            sub->f20 = !sub->f20;
            func_002833F0_2((char *)list->arr[i] + 192, (char *)list->arr[i] + 240);
        }
    }
    if (list->count != 0)
        snd_play_from_class_bank(1, 0, list->arr[0], 2198);
}

/* Clears the three pointer-list flags, updates their counters and copies the vectors. */
/* Defined in L02_003C4848-helpers.c. */

extern char g_camera_l02_position[];
/* Two-float interface of the range RNG; other callers in this unit use an older declaration. */
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);

/* Emits paired particles with opposite spin and randomized velocities. */
void part_l02_spawn_spinning_pairs(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)g_camera_l02_position, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.0166666675f;
        FastVecAdd(origin, pos, offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 60, size * 0.1f, size, 0xDDFF1010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 60, size * 0.07f, size * 0.7f, 0xDDFF1010, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}

/* Reads three angles through a helper, bends the object's own angle at +0xF8 into the same
   range, converts all four and hands them to the four-argument report, then applies the
   same bend to the local angles. */
/* Reads the object's angles and shows them on the debug display. */
void moby_show_angles_debug(char *moby)
{
    char *obj = moby;
    float angles[4];
    float bent_angle;

    moby_transform_joint_to_world(moby, 1, angles);
    /* retail holds 0x40490FD0 here; this spelling is what the rebuilt assembler reads to
       those bits */
    bent_angle = func_00283B98_12(*(float *)(obj + 0xF8), 3.14159f);
    STUB_printf(D_L02_001AFE38, func_801234F0(angles[0]), func_801234F0(angles[1]),
                  func_801234F0(angles[2]), func_801234F0(bent_angle));
    hero_start_target_state(angles, 0, bent_angle);
}

/* The level's three trigger boxes, each a lower and an upper bound, and the point they hold:
   the point has to lie inside every box. */
struct L02Box {
    float lo;
    float hi;
};

struct L02Boxes {
    struct L02Box b[3];
};

struct L02Vec {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* Checks if the player is close to the object and inside its three boxes. Returns 1 when the player is in the zone. */
int moby_is_hero_inside_trigger_boxes(char *moby)
{
    struct L02Boxes box;
    struct L02Vec vec;
    void *vars;
    float distance;

    box = *(struct L02Boxes *)D_L02_001AFEA0;
    vars = *(void **)(moby + 0x68);
    distance = vec_distance_xy(moby + 0x10, g_hero_position);
    if (distance > 24.0f)
        return 0;
    if (*(int *)((char *)vars + 4) != -1)
        return IsPointInCuboid(g_hero_position, *(int *)((char *)vars + 4));
    FastVecSub((float *)&vec, (float *)g_hero_position, (float *)(moby + 0x10));
    vec_transform_by_object_or_given((unsigned char *)moby, (unsigned char *)&vec, (unsigned char *)&vec, 0);
    if (vec.x >= box.b[0].lo && vec.x <= box.b[0].hi &&
        vec.y >= box.b[1].lo && vec.y <= box.b[1].hi &&
        vec.z >= box.b[2].lo && vec.z <= box.b[2].hi)
        return 1;
    return 0;
}

extern int moby_count_group_not_in_state(int, int);
extern float FastAddRotations(float, float);
/* (a, b, phase) with its float first: the EE passes each bank in order. */
extern u32 PulseColor(float, u32, u32);
extern void gfx_pack_render_command_fields(void *, u32, int, int, int);

/* Advances the group's pulse phase by pi/30, tints every moby of the object's group
   (and the child of each 0x873 moby) blue in state 7 or dim otherwise, then sets the
   pulsing color between COLOR1 and COLOR2 on the group's 0xAF9-0xAFD, 0xB03 and 0x873
   mobys. */
/* Makes a group of objects glow and pulse between two colors. In state 7 they glow blue, otherwise they stay dim. */
void PulseGroupMobyColors(char *obj, u32 color1, u32 color2) {
    char *vars = *(char **)(obj + 0x68);
    u16 *list;
    char *moby;
    char *child;

    if (moby_count_group_not_in_state(*(u8 *)(obj + 0x21), -1) < 2)
        return;
    list = (u16 *)g_entity_group_lists[*(u8 *)(obj + 0x21)];
    *(float *)(vars + 0x128) = FastAddRotations(*(float *)(vars + 0x128), 0.104719772f);
    do {
        moby = g_moby_l02_pool + ((*list & 0x7FFF) << 8);
        if (*(u8 *)(obj + 0x20) == 7) {
            if (*(short *)(moby + 0xAA) != 0x896 /* moby class 2198 */) {
                gfx_pack_render_command_fields(moby, PulseColor(*(float *)(vars + 0x128), 0x5050DD, 0x505050),
                              14, 14, 14);
                if (*(short *)(moby + 0xAA) == 0x873) {
                    child = *(char **)(moby + 0x68);
                    gfx_pack_render_command_fields(*(void **)(child + 0x1C),
                                  PulseColor(*(float *)(vars + 0x128), 0x5050DD, 0x505050),
                                  14, 14, 14);
                }
            }
        } else if (*(short *)(moby + 0xAA) != 0x896 /* moby class 2198 */) {
            gfx_pack_render_command_fields(moby, 0x505010, 14, 14, 14);
            if (*(short *)(moby + 0xAA) == 0x873)
                gfx_pack_render_command_fields(*(void **)(*(char **)(moby + 0x68) + 0x1C), 0x505010, 14, 14, 14);
        }
        if (*(short *)(moby + 0xAA) == 0xAF9 || *(short *)(moby + 0xAA) == 0xAFA ||
            *(short *)(moby + 0xAA) == 0xAFB || *(short *)(moby + 0xAA) == 0xAFD ||
            *(short *)(moby + 0xAA) == 0xAFC || *(short *)(moby + 0xAA) == 0xB03 ||
            *(short *)(moby + 0xAA) == 0x873) {
            if (*(short *)(moby + 0xAA) == 0x873) {
                child = *(char **)(moby + 0x68);
                *(u32 *)(*(char **)(child + 0x1C) + 0x78) =
                    PulseColor(*(float *)(vars + 0x128), color1, color2);
            } else {
                *(u32 *)(moby + 0x78) = PulseColor(*(float *)(vars + 0x128), color1, color2);
            }
        }
    } while ((short)*list++ >= 0);
}

/* Defined in L02_003C5438.c. */

/* Defined in L02_003C9D78-g8.c. */

/* Defined in L02_003C9ED0-nsr.c. */

/* Defined in L02_003CA0A8-g8.c. */

/* Defined in L02_003CA280-g8.c. */

/* Defined in L02_003C43F0-cc7b0-g8.c. */

/* The zero vector the boot keeps for the shared helper. */
extern float D_00189F00[];

/* Works out how far to turn left or right and up or down to face the player. The turn amounts are limited to a small range. */
void turret_l02_aim_at_hero(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    TI128 v[2];
    float yaw;
    float pitch;

    qcopy(&v[1], self + 0x10);
    *(float *)((char *)&v[1] + 8) += 1.0f;
    if (*(unsigned char *)(self + 0x20) == 0xB) {
        FastVecSub((float *)&v[0], (float *)(vars + 0x360), (float *)&v[1]);
    } else {
        FastVecSub((float *)&v[0], D_00189F00, (float *)&v[1]);
    }
    vec_transform_by_object_or_given((unsigned char *)self, (unsigned char *)&v[0],
                 (unsigned char *)&v[0], 0);
    yaw = mat_fast_helper_a(*(float *)&v[0], *(float *)((char *)&v[0] + 4));
    if (yaw > 0.7853982448577881f)
        yaw = 0.7853982448577881f;
    else if (yaw < -0.7853982448577881f)
        yaw = -0.7853982448577881f;
    *(float *)(vars + 0x278) = yaw;
    pitch = vec_length_xy((char *)&v[0]);
    pitch = -mat_fast_helper_a(pitch, *(float *)((char *)&v[0] + 8));
    if (pitch > 0.523598849773407f)
        pitch = 0.523598849773407f;
    else if (pitch < -0.523598849773407f)
        pitch = -0.523598849773407f;
    *(float *)(vars + 0x2F4) = pitch;
}

/* func_L02_003CCFE8 is defined in L02_003C43F0-g8.c (the -G8 profile reproduces its
   placement-table address reloads; the body itself reads no $gp data). */


extern int D_L02_001B35B8 __attribute__((sda));
extern float fast_vec_dist(void *, void *);

struct L02NearObject {
    char pad[0x21];
    unsigned char group;
};

struct L02NearBlock {
    char pad[0x378];
    unsigned short f378;
};

/* Finds the entity of the object's group nearest to the player (within 1000.0), then adds
   0x19 to the +0x378 timer of every other entity of the group. */
/* Finds the object of the group that is nearest to the player. All the other objects of the group get a longer wait timer. */
void moby_delay_group_except_nearest(struct L02NearObject *owner)
{
    unsigned short *group_list;
    unsigned short *cursor;
    unsigned short *cursor2;
    char *entity;
    char *nearest;
    struct L02NearBlock *vars;
    float min_dist;
    float dist;

    if (owner->group == 0xFF)
        return;
    group_list = (unsigned short *)g_entity_group_lists[owner->group];
    if (group_list == 0)
        return;
    nearest = 0;
    min_dist = 1000.0f;
    cursor = group_list;
    while (owner->group != 0xFF && owner->group <= D_L02_001B35B8 && cursor != 0 &&
           ((cursor != 0 && (short)cursor[-1] >= 0) || cursor == (unsigned short *)g_entity_group_lists[owner->group])) {
        entity = g_moby_l02_pool + ((*cursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        dist = fast_vec_dist(entity + 0x10, g_hero_position);
        if (dist < min_dist) {
            min_dist = dist;
            nearest = entity;
        }
        cursor++;
    }
    if (nearest != 0) {
        for (cursor2 = (unsigned short *)g_entity_group_lists[owner->group];
             owner->group != 0xFF && owner->group <= D_L02_001B35B8 && cursor2 != 0 &&
             ((cursor2 != 0 && (short)cursor2[-1] >= 0) ||
              cursor2 == (unsigned short *)g_entity_group_lists[owner->group]);
             cursor2++) {
            entity = g_moby_l02_pool + ((*cursor2 & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (entity != nearest) {
                vars = *(struct L02NearBlock **)(entity + 0x68);
                vars->f378 += 0x19;
            }
        }
    }
}

typedef int L02Word;

extern L02Word D_L02_001B35B8 __attribute__((sda));
extern int math_random_int_range(int, int);

struct L02GroupObject {
    char pad[0x21];
    unsigned char group;
};

struct L02GroupEntityObj {
    char pad[0x378];
    short f378;
};

struct L02GroupEntity {
    char pad[0x68];
    struct L02GroupEntityObj *obj;
};

/* Gives every entity of the object's group a random timer between 0x1E and 0x5A at +0x378
   of its private block. */
/* Gives every object in the group a random wait timer. */
void moby_randomize_group_timers(struct L02GroupObject *owner)
{
    unsigned short *group_list;
    unsigned short *cursor;
    struct L02GroupEntity *entity;

    if (owner->group == 0xFF)
        return;
    group_list = (unsigned short *)g_entity_group_lists[owner->group];
    if (group_list != 0) {
        cursor = group_list;
        while (owner->group != 0xFF && owner->group <= D_L02_001B35B8 && cursor != 0 &&
               ((cursor != 0 && (short)cursor[-1] >= 0) ||
                cursor == (unsigned short *)g_entity_group_lists[owner->group])) {
            struct L02GroupEntityObj *vars;

            entity = (struct L02GroupEntity *)(g_moby_l02_pool + ((*cursor & 0x7FFF) << 8));
            if (entity == 0)
                break;
            vars = entity->obj;
            cursor++;
            vars->f378 = math_random_int_range(0x1E, 0x5A);
        }
    }
}

/* Removes the owner when its timer expires; otherwise replaces a mismatched child
   kind and restores the owner's saved position and state. */

extern int D_L02_001B35B8 __attribute__((sda));

/* Sets every entity of the object's group to state 1 with a 0xB4 timer. */
/* Puts every object in the group into the same state with a three second timer. */
void moby_set_group_state_timer(unsigned char *owner) {
    unsigned short *cursor;
    char *entity;

    if (owner[0x21] == 0xFF)
        return;
    cursor = (unsigned short *)g_entity_group_lists[owner[0x21]];
    while (owner[0x21] != 0xFF && owner[0x21] <= D_L02_001B35B8 && cursor != 0 &&
           ((cursor != 0 && (short)cursor[-1] >= 0) || cursor == (unsigned short *)g_entity_group_lists[owner[0x21]])) {
        char *vars;

        entity = g_moby_l02_pool + ((*cursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        vars = *(char **)(entity + 0x68);
        *(unsigned short *)(vars + 0x382) = 1;
        *(unsigned short *)(vars + 0x386) = 0xB4;
        cursor++;
    }
}

extern int g_current_map_index[] __attribute__((sda));
extern char *D_L02_001B3200 __attribute__((sda));
extern char D_L02_001B3210[] __attribute__((sda));
extern float coll_get_ground_distance_below(void *, void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void chickenbot_alert_group(void *);
extern int weapon_select_aim_target(void *, int, float, float, int, int);
extern void cam_compute_view_direction(void *, void *, int);

/* Sets up an enemy when it first appears, with its speed, size and turn limits. Then it checks hits and plays its starting animation. */
void enemy_init(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    char *entry;
    int hit;
    if (*(unsigned char *)(obj + 0x20) == 0) {
        if (g_current_map_index[0] == 26) {
            if (D_L02_001A8FF0 == 0) return;
            coll_get_ground_distance_below(obj + 0x10, obj, obj + 0x10);
            *(short *)(vars + 0x338) = 1;
            *(int *)(obj + 0x9c) = 3;
            *(unsigned short *)(obj + 0x34) |= 0x100;
            *(float *)(vars + 0x90) = fast_vec_dist(obj + 0x10, D_L02_001B3210) - 1.5f;
        } else {
            *(int *)(obj + 0x9c) = 12;
            *(float *)(vars + 0x90) = *(float *)(obj + 0x18) - 1.0f;
        }
        if (*(int *)(vars + 0x210) == -1) {
            moby_mark_spawned(obj);
            return;
        }
        entry = D_L02_001B3200 + *(int *)(vars + 0x210) * 0x30;
        if (*(short *)(entry + 0x30)) {
            *(int *)(vars + 0x13c) = *(int *)(vars + 0x218) = **(int **)(entry + 0x3c);
        } else *(int *)(vars + 0x218) = -1;
        *(float *)(vars + 0x324) = func_002A7878_range(1.0f, 1.332999945f);
        *(float *)(obj + 0x2c) = *(float *)(*(char **)(obj + 0x24) + 0x24) * *(float *)(vars + 0x324);
        *(char *)(vars + 0x48) = FloatToInt(15.0f);
        *(char *)(vars + 0x4a) = FloatToInt(6.4f);
        *(int *)(vars + 0x98) = 3;
        *(float *)(vars + 0x80) = 0.2f;
        *(float *)(vars + 0x84) = 0.2f;
        *(float *)(vars + 0x8c) = 0.4f;
        *(float *)(vars + 0x108) = 0.4f;
        *(float *)(vars + 0x134) = 0.05f;
        *(char *)(vars + 0x60) = 11;
        *(char *)(vars + 0x28) = 3;
        *(float *)(vars + 0x30) = 0.3330000043f;
        *(float *)(vars + 0x104) = *(float *)(vars + 0x324) * 0.2f;
        *(float *)(vars + 0x100) = *(float *)(vars + 0x324) * 0.3f;
        *(float *)(vars + 0x10c) = 0.4f;
        *(float *)(vars + 0x110) = 1.57079649f;
        *(float *)(vars + 0x130) = 0.52359885f;
        *(int *)(vars + 0x138) |= 0x280;
        *(float *)(vars + 0x1dc) = math_random_signed_float_range(18.0f, 22.0f) * 0.01745329425f;
        *(short *)(vars + 0x1e2) = 120;
        *(short *)(vars + 0x1e4) = 180;
        *(char *)(vars + 0x1e8) = 7;
        *(char *)(vars + 0x1e9) = 6;
        *(float *)(vars + 0x1d4) = 3.0f;
        *(float *)(vars + 0x1d0) = 0.06666667014f;
        *(float *)(vars + 0x328) = math_random_angle();
        if (*(int *)(vars + 0x214)) {
            *(int *)(obj + 0x98) = 0;
            *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xefff;
            moby_set_state(obj, 13, 4);
            if (*(unsigned char *)(obj + 0x43) != 10) anim_start_blended(obj, 10, 0, 0);
        } else {
            moby_set_state(obj, 1, 0);
            if (*(unsigned char *)(obj + 0x43)) anim_start_blended(obj, 0, 0, 0);
        }
        qcopy(vars + 0x2e0, obj + 0x10);
    }
    if (*(unsigned char *)(obj + 0x31) && fast_vec_dist(obj + 0x10, g_camera_l02_position) < 24.0f) {
        moby_update_ground_check(obj);
        *(char *)(obj + 0x6f) = 22;
    }
    hit = moby_apply_damage_to_object(obj, vars + 0x50, 0);
    if (hit) {
        chickenbot_alert_group(obj);
        if (hit >= 4) moby_set_state(obj, 12, -1);
    }
    if ((unsigned int)(*(unsigned char *)(obj + 0x95) - 3) >= 2)
        *(short *)(vars + 0x314) = weapon_select_aim_target(obj, *(int *)(vars + 0x210), 16.0f, 0.0f, 0, 0);
    if (*(short *)(vars + 0x338)) cam_compute_view_direction(obj + 0x10, vars + 0x300, 0);
}


/* Runs the kind's entry hook: the first when the level flag is set, the second when the third
   argument is clear, the third with the object's own angle otherwise. */
/* Runs one of three movement helpers on the object, depending on the level flag and the mode. */
int moby_run_entry_hook_by_mode(char *moby, char *target, int mode) {
    char *vars = *(char **)(moby + 0x68);
    int result;

    if (D_L02_001A8FF0)
        result = moby_aim_at_target_offset(moby, target);
    else if (mode == 0)
        result = moby_l01_turn_toward_target(moby, target);
    else
        result = moby_turn_toward_target_and_step(moby, (float *)target, *(float *)(vars + 0x31C));
    return result;
}

/* Clears the two angle words at +0x310 and +0x312 and counts up the +0x96 word, then runs the
   two placement helpers on the sub-object at +0x260. */
/* Resets the object's turn values and counts up a frame counter. Then it moves the object with two helpers. */
void moby_reset_turn_place(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *sub_obj;
    unsigned short counter;

    FastDecTimer(vars + 0x310);
    FastDecTimer(vars + 0x312);
    counter = *(unsigned short *)(moby + 0x96);
    if (counter <= 0xFFFE)
        *(unsigned short *)(moby + 0x96) = counter + 1;
    sub_obj = vars + 0x260;
    moby_update_eased_node(moby, sub_obj, 0, 0.03f, 0.3000000119209289550781250f);
    value_set_and_smooth(moby, sub_obj, 0, 1.79999995231628417968750f, 1);
}

/* Defined in L02_003CEA28.c. */

/* The entity pool base and the highest group id once more, as the `sda` arrays the twin walk
   func_L02_003CD5B0 reads (02_maktar_nebula/L02_002ED7B0.c): read as X[0] they give retail's
   rotated loop; func_L02_003CD8C0 above reads the same two words as scalars. */
extern u8 *D_L02_001B359C_tbl[] __asm__("D_L02_001B359C") __attribute__((sda));
extern int D_L02_001B35B8_tbl[] __asm__("D_L02_001B35B8") __attribute__((sda));

/* Returns the first entity of the group whose state byte is 0xD, or 0. */
u8 *moby_find_group_in_state_13(int group) {
    u16 *cursor;
    u8 *entity;

    for (cursor = (u16 *)g_entity_group_lists[group];
         (u8)group != 0xFF && group <= D_L02_001B35B8_tbl[0] && cursor != 0 &&
         ((s16)cursor[-1] >= 0 || cursor == (u16 *)g_entity_group_lists[group]);
         cursor++) {
        entity = D_L02_001B359C_tbl[0] + ((*cursor & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 0xD)
            return entity;
    }
    return 0;
}

/* Reads the object's basis, clamps its pitch and yaw, and stores them back. */
void turret_clamp_aim_yaw_pitch(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float offset[4];
    float yaw;
    float pitch;

    FastVecSub(offset, (const float *)(vars + 0x1F0), (const float *)(moby + 0x10));
    vec_transform_by_object_or_given((unsigned char *)moby, (unsigned char *)offset, (unsigned char *)offset, 0);
    yaw = mat_fast_helper_a(offset[0], offset[1]);
    *(float *)(vars + 0x2C0) = yaw;
    if (yaw > 0.7853982448577881f)
        *(float *)(vars + 0x2C0) = 0.7853982448577881f;
    else if (yaw < -0.7853982448577881f)
        *(float *)(vars + 0x2C0) = -0.7853982448577881f;
    pitch = -mat_fast_helper_a(vec_length_xy((char *)offset), offset[2]);
    *(float *)(vars + 0x2C8) = pitch;
    if (pitch > 0.523598849773407f)
        *(float *)(vars + 0x2C8) = 0.523598849773407f;
    else if (pitch < -0.523598849773407f)
        *(float *)(vars + 0x2C8) = -0.523598849773407f;
}

extern int coll_check_object_inside_polygon(unsigned char *object);

/* Moves the object to a new place and facing, and switches it to its next state. It only works when the object is in state 0xD. */
void moby_teleport_to_new_pose(char *moby, char *new_pos, char *new_dir)
{
    union { TI128 q; float f[4]; } vectors[2];
    TI128 *p0 = &vectors[0].q;
    TI128 *p1 = &vectors[1].q;
    char *vars;
    unsigned short flags;

    vectors[0].q = *(TI128 *)new_pos;
    vectors[1].q = *(TI128 *)new_dir;
    vars = *(char **)(moby + 0x68);
    if (*(unsigned char *)(moby + 0x20) != 0xD)
        return;
    flags = *(unsigned short *)(moby + 0x34);
    flags &= 0xFFBE;
    flags |= 0x1000;
    *(unsigned short *)(moby + 0x34) = flags;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    moby_set_state((u8 *)moby, 0xE, -1);
    qcopy(moby + 0x10, p0);
    *(float *)(moby + 0xF8) = mat_fast_helper_a(vectors[1].f[0], ((float *)p1)[1]);
    coll_check_object_inside_polygon((unsigned char *)moby);
    qcopy(vars + 0x1A0, p1);
    *(int *)(vars + 0x124) = 0;
    *(int *)(vars + 0x120) = 0;
    *(int *)(vars + 0x138) |= 0x11;
}

/* The callback func_L02_003CEE40 registers; its body is the INCLUDE_ASM below. */
extern void chickenbot_emit_sparks(char *);

extern int g_frame_l02_counter __attribute__((sda));

struct L02PairWord {
    int a;
    int b;
};

extern struct L02PairWord D_L02_001B00C0;

extern float FastAddRotations(float, float);

extern int FastTweenColor(int, int, float);

extern void moby_transform_joint_point(char *, int, void *);

extern void gfx_add_draw_callback_first(void *, void *);

/* The kind's private block, at +0x68 of the object and of each entity. */
struct L02Kind330 {
    char pad[0x328];
    float f328;
    float f32C;
    int f330;
};

struct L02Kind330Entity {
    char pad0[0x20];
    unsigned char state;
    char pad1[0x10];
    unsigned char f31;
    char pad2[0x36];
    struct L02Kind330 *obj;
    char pad3[0x3E];
    short type;
};

struct L02Kind330Object {
    char pad0[0x21];
    unsigned char group;
    char pad1[0x46];
    struct L02Kind330 *obj;
    char pad2[0x0C];
    int f78;
};

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L02_001B30C8 differs from the object's word at +0x330, walks the object's group
   and refreshes every live entity of kind 0xA4E, then registers func_L02_003CEFD8. */
void chickenbot_update_group_pulse_color(struct L02Kind330Object *owner) {
    struct L02Kind330 *vars = owner->obj;
    struct L02PairWord color_pair = D_L02_001B00C0;
    float phase;
    unsigned short *cursor;
    struct L02Kind330Entity *entity;
    struct L02Kind330 *ent_vars;

    phase = FastAddRotations(vars->f328, 0.20943954586982727f);
    vars->f328 = phase;
    phase = math_fast_sin_or_cos_b(phase);
    vars->f32C = phase * 0.5f + 0.5f;
    owner->f78 = FastTweenColor(color_pair.a, color_pair.b, vars->f32C);
    if (vars->f330 != g_frame_l02_counter) {
        for (cursor = (unsigned short *)g_entity_group_lists[owner->group];
             owner->group != 0xFF && owner->group <= D_L02_001B35B8 && cursor != 0 &&
             ((cursor != 0 && (short)cursor[-1] >= 0) || cursor == (unsigned short *)g_entity_group_lists[owner->group]);
             cursor++) {
            entity = (struct L02Kind330Entity *)(g_moby_l02_pool + ((*cursor & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (entity->f31 != 0 && entity->type == MOBY_CLASS_MEGACORP_CHICKENBOT && entity->state != 0xFE && entity->state != 0xFD) {
                ent_vars = entity->obj;
                moby_transform_joint_point((char *)entity, 0, (char *)ent_vars + 0x220);
                ent_vars->f330 = g_frame_l02_counter;
            }
        }
        gfx_add_draw_callback_first((void *)chickenbot_emit_sparks, owner);
    }
}

/* func_L02_003CEFD8 is in L02_003CEFD8.c. */

typedef struct {
    f32 x;
    f32 y;
} L02Pair_CF1B8;

typedef struct {
    s32 a;
    s32 b;
} L02Range_CF1B8;

extern L02Pair_CF1B8 D_L02_001B00D0;
extern L02Pair_CF1B8 D_L02_001B00D8;
extern L02Range_CF1B8 D_L02_001B00E0;
typedef struct {
    L02Range_CF1B8 r[2];
} L02Ranges_CF1B8;

extern L02Ranges_CF1B8 D_L02_001B00E8;

extern void vec_clear_128(void *);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern void vec_random_direction(void *, float, float);

/* Spawns two small effect puffs at the object, one on the spot and one a little below. */
void part_spawn_two_puffs(u8 *self)
{
    L02Pair_CF1B8 speed = D_L02_001B00D0;
    L02Pair_CF1B8 size = D_L02_001B00D8;
    L02Range_CF1B8 kind = D_L02_001B00E0;
    L02Ranges_CF1B8 count = D_L02_001B00E8;
    f32 vel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    s32 i;

    vec_clear_128(vel);
    part_spawn_hero_relative(self + 0x10, vel, kind.a, math_random_int_range(count.r[0].a, count.r[0].b) & 0xFF,
                  math_random_int_below(0xFF) & 0xFF, 0, size.x);
    for (i = 0; i < 1; i++) {
        vec_random_direction(pos, 0.0f, 0.5f);
        FastVecAdd(pos, pos, self + 0x10);
        vel[2] = -(math_random_float_range(speed.x, speed.y) * 0.016666668f);
        part_spawn_hero_relative(pos, vel, kind.b, math_random_int_range(count.r[1].a, count.r[1].b) & 0xFF,
                      math_random_int_below(0xFF) & 0xFF, 0, size.y);
    }
}


/* Positions A0 with four angles, then moves it kind six to kind two of length ten. */
void moby_start_anim_fast(char *moby) {
    moby_set_controller_speed_limits(moby, 0.0055555556900799274f, 0.03166666626930237f,
                  0.006981317885220051f, 0.8377581834793091f);
    moby_set_state(moby, 6, 3);
    if (*(unsigned char *)(moby + 0x43) != 2)
        anim_start_blended(moby, 2, 0, 10);
}

/* Positions A0 with four angles, then moves it kind ten to kind six of length five. */
void moby_start_anim_slow(char *moby) {
    moby_set_controller_speed_limits(moby, 0.0055555556900799274f, 0.06666667014360428f,
                  0.0034906589426100254f, 0.41887909173965454f);
    moby_set_state(moby, 10, 4);
    if (*(unsigned char *)(moby + 0x43) != 6)
        anim_start_blended(moby, 6, 0, 5);
}

/* Builds three vectors, normalises the displacement and returns its dot product. */
float vec_normalized_direction_dot(char *moby, char *target) {
    TI128 vecs[3];

    vecs[0] = *(TI128 *)target;
    vecs[1] = *(TI128 *)(moby + 0xD0);
    vec_subtract_vec4((char *)&vecs[2], (char *)&vecs[0], moby + 0x10);
    vec_scale_to_length((char *)&vecs[2], (char *)&vecs[2], 1.0f);
    return FastVecDot((char *)&vecs[1], (char *)&vecs[2]);
}

/* func_L02_003D1FA0 is in L02_003D1FA0-g8.c for its small-data accesses. */

/* func_L02_003D28E0 lives in the -g8 sibling: it reads five $gp-relative scalars. */

/* When the +0x3C counter of the object at +0x68 is clear, runs the reset, then the dispatch. */
void moby_reset_and_run_dispatch(char *moby) {
    char *self = moby;

    if (*(BatchA_A17_s32 *)(*(BatchA_A17_s32 *)(self + 0x68) + 0x3C) == 0)
        UpdateRotatingBouncingEffect();
    gfx_add_draw_callback_third((void *)part_spawn_fading_spark, self);
}

/* The level's own sound-emitter update: the kind byte at +0x20 of the object picks the
   work, the shared emitter table at D_00188660 holds the listeners. */
void snd_emitter_update(char *moby)
{
    char *self = moby;
    char *vars;
    unsigned char buf[0x40];

    vars = *(char **)(self + 0x68);
    platform_init(moby);

    switch (*(unsigned char *)(self + 0x20)) {
    case 2:
        if (*(int *)(vars + 0xBC) == 0)
            return;
        moby_set_state(self, 3, -1);
        *(int *)(vars + 0xB4) = D_L02_001B3FD8;
        break;
    case 1:
        moby_push_nearby_sideways(self);
        if (*(unsigned char *)(self + 0x31) != 0)
            part_spawn_puff_at_moby(self);
        if (*(int *)(vars + 0xBC) != 0)
            return;
        moby_set_state(self, 4, -1);
        *(int *)(vars + 0xB4) = D_L02_001B3FD8;
        break;
    case 3:
        multiply_matrix3x3(self + 0xC0, vars + 0x80, self + 0xC0);
        if (*(int *)(vars + 0xB4) == D_L02_001B3FD8)
            PlayMobySound(1, 0, self);
        copy_matrix_rotation(buf, self + 0xC0);
        mat_get_euler_angles((float *)buf, self + 0xF0);
        moby_update_attached_transforms(self, vars + 0x30);
        moby_push_nearby_sideways(self);
        math_fast_float_d(vars + 0xB4);
        if (*(int *)(vars + 0xB4) == 0)
            moby_set_state(self, 1, -1);
        if (snd_is_voice_playing_for_owner((int)self, *(short *)(vars + 0xC0)) != 0)
            return;
        *(short *)(vars + 0xC0) = PlayMobySound(0, 4, self);
        break;
    case 4:
        multiply_matrix3x3(self + 0xC0, vars + 0x80, self + 0xC0);
        copy_matrix_rotation(buf, self + 0xC0);
        mat_get_euler_angles((float *)buf, self + 0xF0);
        moby_update_attached_transforms(self, vars + 0x30);
        moby_push_nearby_sideways(self);
        math_fast_float_d(vars + 0xB4);
        if (*(int *)(vars + 0xB4) != 0)
            return;
        if (*(short *)(vars + 0xC0) != -1) {
            unsigned char *emitter = g_sound_state + *(short *)(vars + 0xC0) * 0x70;

            if (*(int *)(emitter + 0x88) == (int)self && *(unsigned char *)(emitter + 0x74) != 0)
                snd_stop_voice(*(short *)(vars + 0xC0));
        }
        *(short *)(vars + 0xC0) = -1;
        moby_set_state(self, 2, -1);
        break;
    }
}

/* Defined in L02_003D6DF8-helpers.c. */



/* Defined in L02_003D6EE0-g8.c. */

/* Defined in L02_003D7040-g8.c. */

/* func_L02_003D7140 is defined in L02_003D7140-g8.c. */

/* Returns the object's busy flag. */
int moby_get_busy_flag(char *moby) {
    return *(int *)(*(char **)(moby + 0x68) + 0xBC);
}

/* Sets the object's busy flag. */
void moby_set_busy_flag(char *moby) {
    BatchA_A17_s32 vars = (BatchA_A17_s32)*(BatchA_A17_s32 *)(moby + 0x68);
    *(BatchA_A17_s32 *)((char *)vars + 0xBC) = 1;
}

/* Clears the object's busy flag. */
void moby_clear_busy_flag(char *moby) {
    *(int *)(*(char **)(moby + 0x68) + 0xBC) = 0;
}

/* True when any of the three words at +0x10, +0x14, +0x18 of the object at +0x68 is set. */
int moby_has_free_child_slot_state2(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int result = 0;

    if (*(unsigned char *)(moby + 0x20) == 2) {
        if (*(int *)(vars + 0x10) == 0 || *(int *)(vars + 0x14) == 0 || *(int *)(vars + 0x18) == 0)
            result = 1;
    }
    return result;
}

/* True when any of the three words at +0x10, +0x14, +0x18 of the object at +0x68 is set. */
int moby_has_any_child_slot_used(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int result = 0;

    if (*(int *)(vars + 0x10) || *(int *)(vars + 0x14) || *(int *)(vars + 0x18))
        result = 1;
    return result;
}

/* Of kind two, reports whether the helper found nothing. */
int moby_is_state_two_no_children(char *moby) {
    int result = 0;

    if (*(unsigned char *)(moby + 0x20) == 2)
        result = moby_has_any_child_slot_used(moby) == 0;
    return result;
}

/* True when the first free of the three words at +0x10, +0x14, +0x18 of the object at +0x68
   exists; A1 goes there and its kind byte is set to two. */
void moby_attach_child_first_free_slot(char *owner, char *child) {
    char *vars = *(char **)(owner + 0x68);

    if (*(int *)(vars + 0x10) == 0)
        *(int *)(vars + 0x10) = (int)child;
    else if (*(int *)(vars + 0x14) == 0)
        *(int *)(vars + 0x14) = (int)child;
    else if (*(int *)(vars + 0x18) == 0)
        *(int *)(vars + 0x18) = (int)child;
    *(char *)(child + 0x20) = 2;
}

/* Resets the +0x48 float to one, then moves A0 from kind two to kind three. */
void moby_reset_scale_switch_state3(char *moby) {
    *(float *)(moby + 0x48) = 1.0f;
    if (*(unsigned char *)(moby + 0x43) != 0)
        anim_start_blended(moby, 0, 0, 0);
    moby_set_state(moby, 3, -1);
}

/* Calls the shared helper with the number 10000. */
void moby_call_helper_10000(void) {
    fade_reduce_value(10000.0f);
}

/* func_L02_003E1A40 is defined in L02_003E1A40-g8.c. */

/* func_L02_003E2150: defined in L02_003C43F0-ring-g8.c. */


/* Copies the byte at +0x40 of the object held at +0x68 over its byte at +0x25. */
void moby_copy_vars_byte_40_to_25(char *moby) {
    char *vars = (char *)*(BatchA_A17_s32 *)(moby + 0x68);

    *(unsigned char *)(vars + 0x25) = *(unsigned char *)(vars + 0x40);
}

/* Boundary suspect: the retail body at this row is an epilogue (`addiu $sp,$sp,0x50; nop;
   jr $ra; nop`), so the catalogue row starts inside the function before it. Not a function. */

/* Forwards the first argument with a null second and a third of three. */
/* Its callback callers also supply two integer slots that this body ignores. */
void moby_set_anim_type_three(void *moby, int unused_a1, int unused_a2) {
    SetDeathBits(moby, 0, 3);
}

/* The two entry scalers live in the -g8 sibling: retail reads the table through $gp. */

/* func_L02_003FE768 is in L02_003FE768-g8.c. */

/* Allocates sixteen of sixty with no owner; on success attaches A0 as kind two. */
void moby_try_alloc_enter_state2(void *moby) {
    if (PadPressedWithin(16, 60, 0))
        moby_set_state(moby, 2, -1);
}

/* Aims a 144-byte packet at the level's aim vector: the quaternion comes from the source
   point, the matrix's last row from the same point, and the packet is dispatched. */
void gfx_draw_aimed_effect_packet(char *pos, int color_low, int alpha, char *resource, int flags, float scale, float roll)
{
    char pkt[144];
    float m[16];
    float quat[4];
    long long r;

    ref_L02_003FFC48_00(pkt);
    r = GetEffectTextureDescriptor(resource);

    *(long long *)(pkt + 136) = ((long long)flags << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = color_low + (alpha << 24);
    *(int *)(pkt + 72) = color_low + (alpha << 24);
    *(int *)(pkt + 68) = color_low + (alpha << 24);
    *(int *)(pkt + 64) = color_low + (alpha << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = mat_fast_helper_a(D_L02_001BA3C0.x_140 - *(float *)(pos + 0),
                            D_L02_001BA3C0.y_144 - *(float *)(pos + 4));
    quat[1] = -mat_fast_helper_a(vec_distance_xy(pos, (void *)&D_L02_001BA3C0.x_140),
                             D_L02_001BA3C0.z_148 - *(float *)(pos + 8));
    quat[0] = roll;

    euler_to_matrix(m, quat);

    m[12] = *(float *)(pos + 0);
    m[13] = *(float *)(pos + 4);
    m[14] = *(float *)(pos + 8);
    m[15] = 1.0f;

    ref_L02_003FFC48_01(pkt, scale);
    draw_world_quad(pkt, m, 0);
}

/* Below 6000 in the low half-word, while the high one reads three. */
/* Calls a helper when the player's two values hit a certain setting. */
void moby_check_hero_values_call_helper(void) {
    if (g_music_state.f72 == 3 && g_music_state.f6C < 0x1770)
        snd_resume_music_stream();
}

/* True when the byte at +0x20 is two or more. */
int moby_is_state_at_least_2(unsigned char *moby) {
    return *(unsigned char *)(moby + 0x20) >= 2;
}


/* The pointer and the five helpers this calls sit at their own addresses in every level
   that has the function, so all six are reached under names that carry no address. */
extern char ref_L02_004012A0_00[] __attribute__((nosda));

extern void ref_L02_004012A0_01(void *, int, int, int, int, int, int, int, int, int, int,
                                int, float, float);
extern void ref_L02_004012A0_02(float *, const float *, const float *);
extern void ref_L02_004012A0_03(void *, void *, float);
extern void ref_L02_004012A0_04(void *, void *, int, int, int, int, float, float, float);
extern void ref_L02_004012A0_05(void *, void *, void *, float);

/* The kind at +0xAA decides the work: the second kind reports itself and leaves, every
   other kind turns the object's own basis, scales it and hands it on. */
void moby_update_effect_by_class(char *moby) {
    char *self = moby;
    char *vars = *(char **)(moby + 0x68);
    float v[4];
    short kind = *(short *)(moby + 0xAA);

    switch (kind) {
    case 0xB1B:
        break;
    case 0xB5A:
        ref_L02_004012A0_01(moby + 0x10, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 0.3f, 20.0f);
        return;
    }
    ref_L02_004012A0_02(v, (const float *)ref_L02_004012A0_00, moby + 0x10);
    ref_L02_004012A0_03(v, v, 1.0f);
    ref_L02_004012A0_04(moby, moby + 0x10, 0x10001, 0, 1, 0, 0.25f, *(float *)(vars + 0x6C), 1.0f);
    ref_L02_004012A0_05(moby, moby + 0x10, v, 0.0f);
}



/* Defined in L02_00401ED8-g8.c. */

/* Defined in L02_00402300-g8.c. */

/* func_L02_00402440 lives in the -g8 sibling: it reads four $gp-relative scalars. */

/* Returns the object's counter value. */
int moby_get_vars_counter(char *moby) {
    return *(short *)(*(char **)(moby + 0x68) + 0x30);
}

/* A17-ptr-store-16 freshly exact-verified under family reservation */
/* Sets the object's counter value to 1. */
void moby_set_vars_counter_to_1(char *moby) {
    BatchA_A17_s32 vars = (BatchA_A17_s32)*(BatchA_A17_s32 *)(moby + 0x68);
    *(BatchA_A17_BatchAs16 *)((char *)vars + 0x30) = 1;
}

/* Clears the object's counter value. */
void moby_clear_vars_counter(char *moby) {
    *(short *)(*(char **)(moby + 0x68) + 0x30) = 0;
}


/* Calls a helper with two small numbers. */
void moby_call_helper_two_one(void) {
    data_set_small_value_and_refresh(2, 1);
}
