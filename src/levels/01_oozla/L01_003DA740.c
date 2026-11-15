#include "common.h"

typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *g_moby_l01_table __attribute__((sda));
extern u8 *D_L01_001FE180[] NOT_SDA;
extern f32 vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, f32);
extern s32 point_in_path_xy(void *, void *, s32);
extern f32 math_random_float_range(f32,f32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void vec_build_spherical_offset(void *, f32, f32, f32);
extern s32 coll_sweep_from_object(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 coll_cast_object_line(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern s32 func_001163B0(void);
extern s32 FloatToInt(f32);
extern u8 *part_spawn_trail(void *, void *, void *, u32, u32, s32, s32, s32, s32);


extern void muckdweller_mark_nearby_objects(u8 *, void *, void *);
extern void moby_follow_attached(void *, void *);
extern void muckdweller_clear_marked_objects(void **, s32 *);
extern s32 moby_l01_turn_toward_target(void *, void *);
extern void enemy_update_wander_heading(void *, void *, void *);

extern s32 func_310648();

extern f32 func_310580(f32 x, f32 y);

extern s32 func_310528(s32 a, s32 b);

extern f32 func_2E3A48(f32 x);

extern f32 func_2E3A60(f32 x);

extern void func_2E3470(void *a, void *b, void *c);

extern void func_32EF38(void *buf, s32 a1, s32 a2, s32 a3, f32 x, f32 y);

extern void memset(void *buf, s32 value, s32 count);

extern s32 coll_process_hit(f32 radius, void *pos, s32 flag, void *obj, s32 arg);

/* The level's table of the records the spawner looks through. */
extern u32 D_L01_001C3980[];

/* func_L01_003DA740 is in L01_003DA740-particles-g8.c. */

/* func_L01_003DAB98 is in L01_003DAB98-g8.c. */

/* func_L01_003DAE58 is in L01_003DAE58.c. */

/* Scatters the measured primitive around the object, a1 times. */

/* func_L01_003DBCB8 is defined in L01_003DBCB8-qcopy-barrier.c. */

/* func_L01_003DBF38 is defined in L01_003DBF38-qcopy-barrier.c. */

/* Aims at the target and spews fire-like sparks and smoke, and lights up the spot it hits. */
void muckdweller_fire_spit_shot(u8 *obj, s32 skip) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 end[4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    f32 acceleration[4] __attribute__((aligned(16)));
    f32 particlePos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 angle, yaw, distance, height;
    u8 *particle;

    distance = vec_distance_xy(obj + 0x10, *(u8 **)(state + 0x2F0) + 0x10);
    height = *(f32 *)(*(u8 **)(state + 0x2F0) + 0x18) - *(f32 *)(obj + 0x18);
    angle = fast_subtract_rotations(mat_fast_helper_a(distance, height), *(f32 *)(obj + 0xF4));
    if (angle > 0.3490659f) angle = 0.3490659f;
    else if (angle < -0.3490659f) angle = -0.3490659f;
    angle = FastAddRotations(angle, *(f32 *)(obj + 0xF4));
    yaw = *(f32 *)(obj + 0xF8);

    moby_transform_joint_to_world(obj, 0, pos);
    vec_scale_to_length(tmp, obj + 0xC0, -0.4f);
    FastVecAdd(pos, pos, tmp);
    vec_scale_to_length(tmp, obj + 0xE0, 0.3f);
    FastVecAdd(pos, pos, tmp);

    if (*(s16 *)(*(u8 **)(state + 0x2F0) + 0xAA) == 0xB1A) {
        coll_sweep_from_object(obj, pos, 1.0f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
        return;
    }

    particle = *(u8 **)(state + 0x3F0);
    if (particle) {
        if (particle[0] == 2 && particle[1] != 0x80) {
            distance = vec_distance_xy(pos, particle + 0x10);
            if (*(f32 *)(state + 0x3F4) < distance) *(f32 *)(state + 0x3F4) = distance;
        } else {
            *(u8 **)(state + 0x3F0) = 0;
            *(f32 *)(state + 0x3F4) = 3.0f;
        }
        vec_build_spherical_offset(end, *(f32 *)(state + 0x3F4), yaw, angle);
        FastVecAdd(end, end, pos);
        coll_cast_object_line(obj, pos, end, (f32)state[0x34], 0x4000001, 1.0f, 0, 1, 0);
        coll_sweep_from_object(obj, end, 0.3f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
    }
    if (skip) return;

    {
        s32 i, count = 2, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned;

        velocity[3] = 0.2f;
        acceleration[3] = 1.0f;
        for (i = 0; i < count; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x50608040;
            color2 = 0x10608040;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x30304020;
                color2 = 0x30304020;
            }
            qcopy(particlePos, pos);
            particlePos[0] += math_random_float_range(-0.18f, 0.18f);
            particlePos[1] += math_random_float_range(-0.18f, 0.18f);
            particlePos[2] += math_random_float_range(-0.18f, 0.18f);
            vec_build_spherical_offset(velocity, 0.15f, yaw, angle);
            velocity[2] += math_random_float_range(0.0075000003f, 0.009166667f);
            vec_build_spherical_offset(acceleration, 0.008333334f,
                          FastAddRotations(yaw, math_random_float_range(-9.0f, 9.0f) * 0.017453294f), angle);
            acceleration[2] += math_random_float_range(-0.030000001f, -0.03666667f);
            life = FloatToInt(math_random_float_range(2.0f, 4.0f));
            size = FloatToInt(math_random_float_range(20.0f, 24.0f));
            duration = FloatToInt(math_random_float_range(30.0f, 36.0f));
            spawned = part_spawn_trail(particlePos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned) {
                if (!*(u8 **)(state + 0x3F0)) *(u8 **)(state + 0x3F0) = spawned;
                if (variant) spawned[3] = 0x48;
            }
        }
    }
    {
        s32 i, count = 3, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned = 0;

        velocity[3] = 0.05f;
        acceleration[3] = 0.09f;
        for (i = 0; i < count; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x8050FF30;
            color2 = 0x3050FF30;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x80306000;
                color2 = 0x30304000;
            }
            qcopy(particlePos, pos);
            particlePos[0] += math_random_float_range(-0.24f, 0.24f);
            particlePos[1] += math_random_float_range(-0.24f, 0.24f);
            particlePos[2] += math_random_float_range(-0.24f, 0.24f);
            vec_build_spherical_offset(velocity, 0.16666667f,
                          FastAddRotations(yaw, math_random_float_range(-18.0f, 18.0f) * 0.017453294f), angle);
            velocity[2] += math_random_float_range(0.0058333334f, 0.012500001f);
            vec_build_spherical_offset(acceleration, 0.008333334f,
                          FastAddRotations(yaw, math_random_float_range(-4.0f, 4.0f) * 0.017453294f), angle);
            acceleration[2] += math_random_float_range(-0.014f, -0.030000001f);
            life = FloatToInt(math_random_float_range(2.0f, 4.0f));
            size = FloatToInt(math_random_float_range(20.0f, 24.0f));
            duration = FloatToInt(math_random_float_range(100.0f, 120.00001f));
            spawned = part_spawn_trail(particlePos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned && variant) spawned[3] = 0x48;
        }
    }
}

/* func_L01_003DC838 is defined in L01_003DA740-g8.c (this unit has no $gp access for it). */

/* Marks the records of type 0xA26 the object finds and collects them in a1. */
/* Finds nearby objects of one kind, marks them and remembers up to 16 of them. */
void muckdweller_mark_nearby_objects(u8 *obj, void *recordsOut, void *countOut) {
    s32 i;
    s32 foundCount;
    u32 **out = recordsOut;
    s32 *count = countOut;

    memset(out, 0, 4);
    *count = 0;
    foundCount = coll_process_hit(3.0f, obj + 0x10, 1, obj, 0);
    if (foundCount <= 0)
        return;
    for (i = 0; i < foundCount; i++) {
        if (D_L01_001C3980[i] == 0)
            continue;
        if (*(s16 *)(D_L01_001C3980[i] + 0xAA) != 0xA26)
            continue;
        *(s32 *)(D_L01_001C3980[i] + 0x9C) = 1;
        *(u8 *)(D_L01_001C3980[i] + 0xBC) = 1;
        out[*count] = D_L01_001C3980[i];
        *count = *count + 1;
        if (*count >= 16)
            return;
    }
}

/* Clears the mark on every object that was collected before. */
void muckdweller_clear_marked_objects(void **records, s32 *countPtr) {
    s32 i;

    for (i = 0; i < *countPtr; i++) {
        *(s32 *)((u8 *)*records + 0x9C) = 0;
        records++;
    }
}


/* Slides the object towards the thing it is attached to, or snaps it back to a fallback spot. */
void moby_follow_attached(void *mobyArg, void *fallback) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    u8 *obj = mobyArg;
    u8 *state = *(u8 **)(obj+0x68);
    u8 *target;
    u8 *path;
    s32 index = *(s32 *)(state+0x410);
    if (index != -1) {
        target = (u8 *)&g_moby_l01_table[index];
        if (!target) return;
        if (*(s16 *)(target+0xAA) == 0xA56) {
            if (vec_distance_xy(obj+0x10,target+0x10)>1.0f) {
                FastVecSub(delta,obj+0x10,target+0x10);
                vec_scale_to_length(delta,delta,1.0f);
                FastVecAdd(pos,target+0x10,delta);
            } else qcopy(pos,obj+0x10);
            if (pos[2] < *(f32 *)(target+0x18)+0.01f)
                pos[2] = *(f32 *)(target+0x18)+0.011f;
        } else if (*(s16 *)(target+0xAA) == 0xA53) {
            matrix_from_basis_rows(matrix,target+0xC0);
            FastVecSub(delta,obj+0x10,target+0x10);
            transform_vector(delta,delta,matrix);
            if (delta[0]>2.0f) delta[0]=2.0f;
            else if (delta[0]<-2.0f) delta[0]=-2.0f;
            if (delta[1]>5.0f) delta[1]=5.0f;
            else if(delta[1]<-5.0f) delta[1]=-5.0f;
            if (delta[2]<0.01f) delta[2]=0.01f;
            matrix_mul_vec3(delta,delta,target+0xC0);
            FastVecAdd(pos,target+0x10,delta);
        } else qcopy(pos,obj+0x10);
        FastVecSub(delta,pos,obj+0x10);
        vec_fast_divide_helper(delta,delta,0.10000000894069671631f);
        FastVecAdd(obj+0x10,obj+0x10,delta);
        if (*(f32 *)(obj+0x18)<pos[2]) *(f32 *)(obj+0x18)=pos[2]+0.001f;
    } else {
        s32 pathIndex=*(s32 *)(state+0x1FC);
        if(pathIndex!=-1) {
            path=D_L01_001FE180[pathIndex];
            if(path && !point_in_path_xy(obj+0x10,path+0x10,*(s32 *)path)) qcopy(obj+0x10,fallback);
        }
        {
            u8 *other = *(u8 **)(state + 0x248);
            if (other && (*(s16 *)(other + 0xAA) == 0xA56 ||
                          *(s16 *)(other + 0xAA) == 0xA53))
                *(s32 *)(state + 0x410) = (AttachObject *)other - g_moby_l01_table;
        }
    }
}






/* func_L01_003DD3A0 is in L01_003DD3A0.c. */

/* func_L01_003DD6A8 */
extern void gfx_update_color_fade(void *, void *);

extern void FastDecTimer(void *);

extern s32 math_fast_float_d(void *);

extern void value_set_and_smooth(void *, void *, s32, s32, f32);

/* Counts timers down for this object and wraps up its extra update work. */
void muckdweller_tick_timers(u8 *moby)
{
    u32 value;
    u8 *vars = *(u8 **)(moby + 0x68);

    gfx_update_color_fade(moby, vars + 0x100);
    value = *(u16 *)(moby + 0x96);
    if (value <= 0xFFFE) {
        *(u16 *)(moby + 0x96) = value + 1;
    }
    FastDecTimer(vars + 0x3D8);
    math_fast_float_d(vars + 0x404);
    FastDecTimer(vars + 0x3D6);
    value = *(s16 *)(vars + 0x3DA);
    if (value != 0) {
        *(u16 *)(vars + 0x3D6) = 0x168;
        *(s16 *)(vars + 0x3DA) = 0;
    }
    value_set_and_smooth(moby, vars + 0x300, 1, 1, 1.8f);
}

/* func_L01_003E8ED8 is in L01_003E8ED8-g8.c. */

/* func_L01_003EC0C0 and func_L01_00405300 (L01_003DA740-pose.c): the moby
   eases from the pose it had when it started to entry `index` of the
   D_L01_001B264C table (0x80-byte entries). Struct (not cast) accesses matter:
   GCC only lets the table pointer's load pass the store of an angle when that
   store is a structure field, as retail's loads are scheduled. */
typedef struct {
    unsigned char pad00[0x30];
    float position[4];              /* 0x30 */
    unsigned char pad40[0x30];
    float rotation[4];              /* 0x70 */
} PoseRecord;
typedef struct {
    unsigned char pad00[0x20];
    float track[4];                 /* 0x20 */
    unsigned char pad30[0x2C];
    int flags;                      /* 0x5C */
    float start_position[4];        /* 0x60 */
    float start_rotation[4];        /* 0x70 */
    int index;                      /* 0x80 */
    float duration;                 /* 0x84 */
    float t;                        /* 0x88 */
    int link;                       /* 0x8C */
    int sound;                      /* 0x90 */
} PoseMotion;
typedef struct {
    unsigned char pad00[0x10];
    float position[4];              /* 0x10 */
    unsigned char state;            /* 0x20 */
    unsigned char pad21[0x13];
    unsigned short flags;           /* 0x34 */
    unsigned char pad36[0x32];
    PoseMotion *vars;               /* 0x68 */
    unsigned char pad6C[0x3C];
    unsigned char hit_slot;         /* 0xA8 */
    unsigned char padA9[0x13];
    unsigned char command;          /* 0xBC */
    unsigned char padBD[0x33];
    float rotation[4];              /* 0xF0 */
} PoseMoby;
extern PoseRecord *D_L01_001B264C MACRO_ADDR;
extern unsigned char g_sound_state[];
extern float math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *, void *, float);
extern float math_move_angle_toward_target(float, float, float);
extern void moby_set_state(void *, int, int);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);

/* Waits for its command byte, then starts its sound 0 with flag 4 (the slot
   kept in `sound`) and eases into its table pose; at the end stops that sound
   if the slot still belongs to it and plays its sound 1. */
void pose_ease_update(PoseMoby *m)
{
    float position[4], rotation[4], delta[4];
    PoseMotion *p = m->vars;
    float blend;

    qcopy(position, m->position);
    qcopy(rotation, m->rotation);
    switch (m->state) {
    case 0:
        p->sound = -1;
        p->t = 0.0f;
        p->flags |= 1;
        qcopy(p->start_position, m->position);
        qcopy(p->start_rotation, m->rotation);
        moby_set_state(m, 1, -1);
        break;
    case 1:
        if (m->command) {
            p->sound = PlayMobySound(0, 4, m);
            moby_set_state(m, 2, -1);
        }
        m->hit_slot = 255;
        break;
    case 2:
        p->t += 1.0f / p->duration;
        if (p->t > 1.0f) p->t = 1.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(p->t * 3.1415927f)) * 0.5f;
        FastVecSub(delta, D_L01_001B264C[p->index].position, p->start_position);
        FastVecScale(delta, delta, blend);
        FastVecAdd(m->position, p->start_position, delta);
        m->rotation[2] = math_move_angle_toward_target(p->start_rotation[2], D_L01_001B264C[p->index].rotation[2], blend);
        m->rotation[1] = math_move_angle_toward_target(p->start_rotation[1], D_L01_001B264C[p->index].rotation[1], blend);
        m->rotation[0] = math_move_angle_toward_target(p->start_rotation[0], D_L01_001B264C[p->index].rotation[0], blend);
        if (p->t >= 1.0f) {
            int handle = p->sound;
            if (handle != -1) {
                unsigned char *slot = g_sound_state + handle * 0x70;
                if (*(void **)(slot + 0x88) == m && slot[0x74])
                    snd_stop_voice(handle);
                p->sound = -1;
            }
            PlayMobySound(1, 0, m);
            moby_set_state(m, 3, -1);
        }
        break;
    }
    if (m->state < 3) {
        FastVecSub(delta, m->position, position);
        mat_combine_and_store(p->track, delta, rotation, m->rotation);
    }
}

/* func_L01_003ECCF8 */
extern f32 FastAddRotations(f32, f32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FloatToInt(f32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
typedef struct { u8 pad[0x80]; f32 pos[4]; u8 pad90[0x2AC]; u8 *object; s32 active; } PlayerECC;
extern PlayerECC g_hero_state;
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 D_0019B4A8[];
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021E4B0;

/* Pulses the object's grey colour until the player touches it (save nibble counter at
   D_0019B4A8) or its id is already collected; then marks it and its linked record active
   and plays sound 0x8A1 once. */
void collectible_marker_update(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 dist;
    s32 shade;
    u16 id;
    u32 color;
    if (!state) return;
    *(f32 *)(state + 4) = FastAddRotations(*(f32 *)(state + 4), 0.10471977293491364f);
    if (obj[0x20] == 0) {
        moby_transform_joint_to_world(obj, 0, pos);
        dist = vec_distance_xy(g_hero_state.pos, pos);
        *(s32 *)(state + 8) = 0;
        if (g_hero_state.object == obj && g_hero_state.active && dist < 0.5f) {
            u16 objectId;
            objectId = *(u16 *)(obj + 0xB2);
            if (objectId & 1) {
                if (((D_0019B4A8[((s16)objectId >> 1) + (g_current_map_index[0] << 10)] >> 4) & 7) != 7)
                    D_0019B4A8[((s16)objectId >> 1) + (g_current_map_index[0] << 10)] += 16;
            } else {
                if ((D_0019B4A8[((s16)objectId >> 1) + (g_current_map_index[0] << 10)] & 7) != 7)
                    D_0019B4A8[((s16)objectId >> 1) + (g_current_map_index[0] << 10)] += 1;
            }
        }
        if (obj[0xB0] != 255) {
            s32 nibble;
            id = *(u16 *)(obj + 0xB2);
            if (D_L01_0021E4B0.collected[(s16)id] != 0) goto activate;
            nibble = D_0019B4A8[((s16)id >> 1) + (g_current_map_index[0] << 10)];
            if ((id & 1) ? ((nibble >> 4) & 7) : (nibble & 7)) {
activate:
                obj[0x20] = 1;
                obj[0xBC] = 1;
                if (*(s32 *)state != -1) g_moby_l01_table[*(s32 *)state].data[0xBC] = 1;
            }
        }
        shade = FloatToInt((math_fast_sin_or_cos_b(*(f32 *)(state + 4)) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128) shade = 128;
        else if (shade < 32) shade = 32;
        color = (shade << 8) | 0x80000000;
        *(u32 *)(obj + 0x78) = (shade << 16) | color | shade;
    } else {
        if (!*(s32 *)(state + 8)) {
            snd_play_from_class_bank(0, 0, obj, 0x8A1);
            *(s32 *)(state + 8) = 1;
        }
        *(u32 *)(obj + 0x78) = 0x80208010;
    }
}

/* func_L01_00405300 is in L01_003DA740-pose.c. */

/* func_L01_0040EED0 is in L01_0040EED0-g8.c. */

/* func_L01_0040F118 is in L01_0040F118-g8.c. */

/* Wakes the object on its first update by making it fully visible and switching state. */
void moby_wake_on_first_update(u8 *moby) {
    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x30) = 0xFF;
        *(u8 *)(moby + 0x20) = 1;
    }
}

/* func_L01_0040F360 is in L01_0040F360-g8.c. */

/* func_L01_0040F5A8 is in L01_0040F5A8-g8.c. */

/* func_L01_0040F958 is in L01_003DA740-destruct.c. */

/* func_L01_00410AD0 is in L01_003DA740-f7-g8.c. */

/* func_L01_00412E00 is defined in L01_00412E00-flags-g8.c. */

/* func_L01_00412F18 is defined in L01_00412F18-g8.c. */

/* func_L01_00416440 is in L01_00416440-g8.c. */



/* func_L01_00416C08 is in L01_003DA740-rings-g8.c. */

/* func_L01_00416E78 is in L01_00416E78-camera.c. */

/* func_L01_004171C8 is in L01_004171C8-g8.c. */

/* Sets two flag bits on the object. */
void moby_set_flag_bits(u8 *moby) {
    *(u16 *)(moby + 0x34) |= 0x802;
}

/* func_L01_0041C970 is in L01_003DA740-g8.c. */

/* func_L01_0042C540 is in L01_003DA740-campath-g8.c. */

/* func_L01_0042C8D8 is in L01_0042C8D8-g8.c. */

/* func_L01_0042CE78 */
typedef struct L01_0042CE78_ENTRY {
    char pad0[0x38];
    u8 f38;
    u8 f39;
} L01_0042CE78_ENTRY;

typedef struct L01_0042CE78_OBJ {
    char pad0[0x84];
    s16 f84;
} L01_0042CE78_OBJ;

extern u8 *D_L01_001B1F04 __attribute__((sda));

extern s32 cam_is_hero_in_trigger(void *);

/* Tells whether the camera path is done (-1), blocked (1) or still free (0). */
s32 cam_get_path_status(L01_0042CE78_OBJ *camera, u8 *other)
{
    L01_0042CE78_ENTRY *entry = *(L01_0042CE78_ENTRY **)(D_L01_001B1F04 + camera->f84 * 0x20 + 0x1C);
    s32 result;

    if (entry->f39 != 0) {
        result = -1;
    } else if (entry->f38 != 0) {
        result = 1;
    } else if (other != 0 && *(s16 *)(other + 0x7E) == 0) {
        result = 0;
    } else {
        if (cam_is_hero_in_trigger(camera) != 0) {
            goto one;
        }
        goto zero;
    one:
        result = 1;
        return result;
    zero:
        result = 0;
        return result;
    }
    return result;
}
