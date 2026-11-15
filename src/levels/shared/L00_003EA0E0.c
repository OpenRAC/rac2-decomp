#include "include_asm.h"
#include "names.h"

extern int D_L00_001A8F00 __attribute__((sda));
extern void gfx_set_clamped_view_distance(float value);
extern float math_fabs(float value);
extern char D_L00_001D9F00[];
extern char D_L00_001DA860[];
int kilonoid_spawn(char *a, char *b);
int SpawnCB2Moby(char *a, char *b);
void func_L00_0035F180(char *a, int b, int c, char *d, int e);

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern int g_synthenoid_slots[] __attribute__((sda));

extern void get_moby_joint_matrices(char *p, int one, int *w, char *out);

extern void func_00282D30_3(char *a, char *out, float f);

extern void func_00282CC0_4(char *a, char *b, char *c);

extern void func_00283098_2(char *a, char *b, char *c);

extern void func_002FDBD8_4(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern int IsPointInCuboid(void *, int);

extern int level_get_difficulty_scaled(int);

extern void STUB_printf(void *, ...);

extern unsigned char g_hero_position[];

extern unsigned char D_0019B2E8[];

extern int g_current_map_index __attribute__((sda));

extern int D_001A7A10 __attribute__((sda));

extern int D_001A7A14 __attribute__((sda));

extern int D_L00_001C5480[][3];

extern int D_L00_001C5540[][3];

extern char D_L00_001B0700[];

extern char g_camera_l00_position[];

extern void FastVecSub(char *, char *, char *);

extern float mat_fast_helper_a(float, float);

extern float math_random_float_range(float, float);

extern float math_random_signed_float_range(float, float);

extern int FloatToInt(float);

extern float FastAddRotations(float, float);

extern void vec_build_spherical_offset(float *, float, float, float);

extern void part_spawn_burst(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);

/* Measured partial layouts; original type and game roles are unknown. */

/* scales a float field by 1/1024, passes a caller word and two 16/48-byte scratch buffers to a four-argument helper, then forwards the second buffer with the scaled float to one helper and two sub-objects of the same parameter to three more helpers */
/* Finds where a point on a moving part of an object is in the world. */
void moby_get_attachment_point(char *moby, int jointIndex, char *outPoint, char *localPoint)
{
    char jointMatrices[48];
    char tempBuffer[16];
    int lookup;
    float scale;

    scale = *(float *)(moby + 44) * 0.0009765625f;
    lookup = jointIndex;
    get_moby_joint_matrices(moby, 1, &lookup, jointMatrices);
    func_00282D30_3(outPoint, tempBuffer, scale);
    func_00282CC0_4(outPoint, outPoint, localPoint);
    func_00283098_2(outPoint, outPoint, moby + 192);
    func_00282CC0_4(outPoint, outPoint, moby + 16);
}

/* Slides an object back and forth along one axis and shrinks it near both ends. */
void sweeping_scale_update(char *moby)
{
    float posY;
    float absPosY;
    float distFromEnd;
    float nearEnd;
    float sizeFactor;
    int *modelInfo;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x32) = 0xAF0;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned char *)(moby + 0x20) = 1;
        gfx_set_clamped_view_distance(3000.0f);
    }
    if (*(unsigned char *)(moby + 0x20) != 1)
        return;
    if (D_L00_001A8F00 == 2)
        return;

    posY = *(float *)(moby + 0x14);
    posY = posY - 1.6666667f;
    *(float *)(moby + 0x14) = posY;
    absPosY = math_fabs(posY);

    distFromEnd = 3000.0f - absPosY;
    nearEnd = 750.0f - distFromEnd;
    sizeFactor = 1.0f - nearEnd * (1.0f / 750.0f);
    if (sizeFactor > 3.0f)
        sizeFactor = 3.0f;
    if (sizeFactor < 0.0f)
        sizeFactor = 0.0f;

    modelInfo = *(int **)(moby + 0x24);
    *(float *)(moby + 0x2C) = *(float *)((char *)modelInfo + 0x24) * sizeFactor;
    if (*(float *)(moby + 0x14) <= -3000.0f)
        *(float *)(moby + 0x14) = 3000.0f;
}


/* func_L00_003EA540 is defined in its own unit. */

/* shared native body of family 5a97ab89858c */
/* Sets a flat picture packet to its starting values. */
void gfx_init_quad_packet(char *quadPacket)
{
    *(long long *)(quadPacket + 112) = 0;
    *(float *)(quadPacket + 8) = -1.0f;
    *(float *)(quadPacket + 24) = 1.0f;
    *(float *)(quadPacket + 40) = -1.0f;
    *(float *)(quadPacket + 56) = 1.0f;
    *(float *)(quadPacket + 4) = -1.0f;
    *(float *)(quadPacket + 36) = 1.0f;
    *(float *)(quadPacket + 52) = 1.0f;
    *(int *)(quadPacket + 0) = 0;
    *(int *)(quadPacket + 16) = 0;
    *(int *)(quadPacket + 32) = 0;
    *(int *)(quadPacket + 48) = 0;
    *(float *)(quadPacket + 12) = 1.0f;
    *(float *)(quadPacket + 28) = 1.0f;
    *(float *)(quadPacket + 44) = 1.0f;
    *(long long *)(quadPacket + 128) = 0x0000FF9000000260LL;
    *(float *)(quadPacket + 20) = -1.0f;
    *(float *)(quadPacket + 60) = 1.0f;
}

typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;
extern void func_3EA860(char *);
extern int func_2E67A0(int);
extern float func_2EE7A8(float, float);
extern float func_2EE2E8(char *, char *);
extern float func_31A888(void);
extern void func_2EE970(char *, char *);
extern void func_2EE178(char *, char *, float);
extern void func_2EAC30(char *, char *, int);

/* Builds one aim/render packet: resets the work record, fills the colour and the blend words,
   takes the two aim angles from the level's aim vector, turns them into the packet's orientation
   and scales the packet's four basis vectors by the caller's alpha. */
void gfx_draw_aimed_glow_sprite(char *unused, char *position, int color, float alpha)
{
    unsigned char work[0xE0];
    float yaw;
    float pitch;

    func_3EA860((char *)work);
    *(int *)(work + 0x50) = 0;
    *(int *)(work + 0x54) = 0;
    *(int *)(work + 0x58) = 0;
    *(float *)(work + 0x5C) = 1.0f;
    *(float *)(work + 0x60) = 1.0f;
    *(int *)(work + 0x64) = 0;
    *(float *)(work + 0x68) = 1.0f;
    *(float *)(work + 0x6C) = 1.0f;
    *(long long *)(work + 0x78) = func_2E67A0(0x2C);
    *(long long *)(work + 0x80) = 0x0000FF9000000260LL;
    *(long long *)(work + 0x88) = 0x0000008000000048LL;
    *(int *)(work + 0x4C) = color;
    *(int *)(work + 0x48) = color;
    *(int *)(work + 0x44) = color;
    *(int *)(work + 0x40) = color;
    *(long long *)(work + 0x70) = 0;
    *(int *)(work + 0xDC) = 0;

    yaw = func_2EE7A8(D_L00_001B8C80.x_140 - *(float *)(position + 0),
                        D_L00_001B8C80.y_144 - *(float *)(position + 4));
    *(float *)(work + 0xD8) = yaw;

    pitch = func_2EE7A8(func_2EE2E8(position, &D_L00_001B8C80.x_140),
                         D_L00_001B8C80.z_148 - *(float *)(position + 8));
    *(float *)(work + 0xD4) = -pitch;
    *(float *)(work + 0xD0) = func_31A888();
    func_2EE970((char *)work + 0x90, (char *)work + 0xD0);

    *(float *)(work + 0xC0) = *(float *)(position + 0);
    *(float *)(work + 0xC4) = *(float *)(position + 4);
    *(float *)(work + 0xC8) = *(float *)(position + 8);
    *(float *)(work + 0xCC) = 1.0f;
    func_2EE178((char *)work, (char *)work, alpha);
    func_2EE178((char *)work + 16, (char *)work + 16, alpha);
    func_2EE178((char *)work + 32, (char *)work + 32, alpha);
    func_2EE178((char *)work + 48, (char *)work + 48, alpha);
    func_2EAC30((char *)work, (char *)work + 0x90, 0);
}

/* func_L00_003EAA58 is defined in L00_003EAA58.c. */

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
/* Draws the effect for the Miniturret Glove when its flag is on. */
void miniturret_glove_draw(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_4(1.0f, context, context->vector_10, 0);
    }
}

/* Updates a collectible pickup: when the player touches it, it is marked as collected and the counters go up. */
void collectible_pickup_update(char *object) {
    int *state = *(int **)(object + 0x68);
    int result, index, shift;
    unsigned char *entry;

    if (!IsPointInCuboid(g_hero_position, state[1]))
        return;
    g_hero_position[0x2246] = *(unsigned char *)(object + 0xB0);
    if (state[2])
        return;
    if ((D_0019B2E8[*(unsigned char *)(object + 0xB0) + g_current_map_index * 16] >>
         (*(unsigned char *)(object + 0xB1) * 2)) & 3)
        return;
    state[2] = 1;
    result = level_get_difficulty_scaled(*(unsigned char *)(object + 0xB0));
    index = (*(unsigned char *)(object + 0xB0) & 15) + g_current_map_index * 16;
    shift = (*(unsigned char *)(object + 0xB1) & 3) * 2;
    entry = D_0019B2E8 + index;
    if (!((*entry >> shift) & 3)) {
        *entry = (*entry & ~(3 << shift)) | (result << shift);
        D_001A7A10 += D_L00_001C5480[*(unsigned char *)(object + 0xB0) & 15]
                                   [*(unsigned char *)(object + 0xB1) & 3];
        D_001A7A14 += D_L00_001C5540[*(unsigned char *)(object + 0xB0) & 15]
                                   [*(unsigned char *)(object + 0xB1) & 3];
    }
    STUB_printf(D_L00_001B0700,
        D_L00_001C5480[*(unsigned char *)(object + 0xB0)][*(unsigned char *)(object + 0xB1)],
        D_L00_001C5540[*(unsigned char *)(object + 0xB0)][*(unsigned char *)(object + 0xB1)]);
}

extern int D_L00_001C9340;

extern void BuildObjectAttachmentTransforms(char *, void *, int, int, int, int, int, int);

extern void moby_mark_spawned(char *);

extern void euler_rotation_basis(void *, void *);

extern float math_fast_sin_or_cos_b(float);

extern void math_update_wrapped_angle_offset(char *, void *, void *, float, float, float);

extern void moby_scale_owner_words_by_angles(char *, float, void *, float, void *, float);

extern void multiply_matrix3x3(void *, void *, void *);

extern void mat_get_euler_angles(void *, void *);

extern void moby_update_attached_transforms(char *, void *);

typedef struct {
    long long id;
    int flags;
    int level;
    float angles[3];
    int mode;
    float firstAngle;
    float firstVelocity;
    float secondAngle;
    float secondVelocity;
    float firstSpeed;
    float firstStep;
    float secondSpeed;
    float secondStep;
    char entries[0x4A];
    unsigned char present;
    char pad_8B[2];
    unsigned char update;
} L00_003EB0C0_State;

/* Updates an object made of several parts that spin, and keeps its parts turning. */
void rotating_parts_update(char *self)
{
    float angles[4];
    char rotation[48];
    L00_003EB0C0_State *st = *(L00_003EB0C0_State **)(self + 0x68);
    int i;
    int isLast;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (st->id == -1)
            break;
        {
            /* An int, not a byte constant: reload would otherwise reuse the -1 still in $v0. */
            int alpha = 255;
            *(unsigned char *)(self + 0x30) = alpha;
        }
        BuildObjectAttachmentTransforms(self, st->entries, 0x50, *((int *)&st->id + 1), *(int *)&st->id, st->flags, 7, 0);
        if (!st->present) {
            moby_mark_spawned(self);
            break;
        }
        if (!st->mode) {
            st->update = 1;
            *(unsigned short *)(self + 0x34) |= 0x104;
            euler_rotation_basis(self + 0xC0, self + 0xF0);
        }
        if (st->firstAngle != 0.0f)
            st->firstAngle *= 0.01745329424738884f;
        st->firstVelocity = math_fast_sin_or_cos_b(st->firstAngle) * st->firstSpeed;
        self[0x20] = 1;
        break;
    case 1:
        if (D_L00_001C9340 != st->level)
            break;
        if (st->firstStep > 0.0f)
            math_update_wrapped_angle_offset(self, &st->firstAngle, &st->firstVelocity, st->firstSpeed,
                          st->firstStep * 0.0002908882452175021f, -1.0f);
        if (st->secondStep > 0.0f) {
            moby_scale_owner_words_by_angles(self, st->secondSpeed * 0.01745329424738884f, &st->secondAngle,
                          st->secondStep * 0.0002908882452175021f, &st->secondVelocity, 0.00581776537001133f);
            if (st->update)
                euler_rotation_basis(self + 0xC0, self + 0xF0);
        }
        if (!st->mode) {
            angles[0] = st->angles[0] * 0.0002908882452175021f;
            angles[1] = st->angles[1] * 0.0002908882452175021f;
            angles[2] = st->angles[2] * 0.0002908882452175021f;
            euler_rotation_basis(rotation, angles);
            multiply_matrix3x3(self + 0xC0, self + 0xC0, rotation);
            if (st->secondStep > 0.0f)
                mat_get_euler_angles(self + 0xC0, self + 0xF0);
        } else {
            i = 0;
            do {
                angles[0] = st->angles[0] * 0.0002908882452175021f;
                angles[1] = st->angles[1] * 0.0002908882452175021f;
                angles[2] = st->angles[2] * 0.0002908882452175021f;
                euler_rotation_basis(rotation, angles);
                multiply_matrix3x3(st->entries + i * 0x50, st->entries + i * 0x50, rotation);
                isLast = *(unsigned char *)(st->entries + i * 0x50 + 0x4A);
                i++;
            } while (isLast != 1);
        }
        moby_update_attached_transforms(self, st->entries);
        break;
    }
}

extern int moby_count_group_not_in_state(int, int);

extern unsigned char *D_L00_001B1E9C __attribute__((sda));

extern int D_L00_001FA920[];

extern int D_L00_001B0720[];

extern int D_L00_001B0738[];

/* Four-id switch: wait for the resident check, flip bit 0x43 of every record the first
   list of each of the four ids names and arm D_L00_001B0720; wait again, clear those bits
   and arm D_L00_001B0738. */
/* Switches a group of objects on and off in two steps, waiting for the level data each time. */
void object_group_toggle_update(char *self)
{
    int i;
    char *state = *(char **)(self + 0x68);

    if (*(unsigned char *)(self + 0x20) == 0) {
        if (IsPointInCuboid(g_hero_position, *(int *)(state + 0x10)))
            *(unsigned char *)(self + 0x20) = 1;
    }
    if (*(unsigned char *)(self + 0x20) == 1) {
        int i;
        for (i = 0; i < 4; i++) {
            int groupId;
            unsigned short *idList;
            char *entry;
            char *records;
            char *row;

            row = (char *)state + i * 4;
            groupId = *(int *)row;
            if (D_L00_001FA920[groupId] == 0)
                continue;
            if (moby_count_group_not_in_state(groupId, -1) < 2)
                continue;
            records = D_L00_001B1E9C;
            idList = (unsigned short *)D_L00_001FA920[*(int *)(state + i * 4)];
            do {
                entry = records + (*idList & 0x7FFF) * 256;
                *(unsigned short *)(entry + 0x34) |= 0x43;
            } while ((short)*idList++ >= 0);
        }
        STUB_printf(D_L00_001B0720);
        *(unsigned char *)(self + 0x20) = 2;
    }
    if (*(unsigned char *)(self + 0x20) == 2) {
        if (IsPointInCuboid(g_hero_position, *(int *)(state + 0x10)) == 0)
            *(unsigned char *)(self + 0x20) = 3;
    }
    if (*(unsigned char *)(self + 0x20) == 3) {
        int i;
        for (i = 0; i < 4; i++) {
            int groupId;
            unsigned short *idList;
            char *entry;
            char *records;
            char *row;

            row = (char *)state + i * 4;
            groupId = *(int *)row;
            if (D_L00_001FA920[groupId] == 0)
                continue;
            if (moby_count_group_not_in_state(groupId, -1) < 2)
                continue;
            records = D_L00_001B1E9C;
            idList = (unsigned short *)D_L00_001FA920[*(int *)(state + i * 4)];
            do {
                entry = records + (*idList & 0x7FFF) * 256;
                *(unsigned short *)(entry + 0x34) &= 0xFFBC;
            } while ((short)*idList++ >= 0);
        }
        STUB_printf(D_L00_001B0738);
        *(unsigned char *)(self + 0x20) = 0;
    }
}

/* func_L00_003EB610 is defined in L00_003EB610-g16.c. */


/* func_L00_003EB8E8 is defined in L00_003EB8E8-g8.c. */


/* func_L00_003EC078 is defined in L00_003EC078-zero-ti-por-g8.c. */


/* Clears the four Synthenoid slots. */
void synthenoid_clear_slots(void)
{
    int i;

    for (i = 3; i >= 0; i--)
        g_synthenoid_slots[i] = 0;
}

typedef struct { char pad[0x2290]; char *tbl; } Rac2Native_003ECB38_ConstBlock;

/* Calls the four table-driven float helpers over a 16-byte scratch record and a
   second record at +0x10, then when the probe result is not zero computes
   pi/2 - fn(angle / probe) and hands obj+0xF8, the third parameter and the
   three incoming floats to the renderer helper; original game role is unknown. */
/* Works out the angle toward a target and turns a part of the object to it. */
void moby_aim_part_at_target(char *obj, void *rec, char *mob, float fa, float fb, float fc)
{
    extern void func_2EE138(void *, void *, void *);
    extern float func_2EE1F8(char *, char *);
    extern void func_2EE178(char *, char *, float);
    extern float func_2EE238(char *);
    extern float func_2EE710(float);
    extern void func_31DE50(char *, float, char *, float, float, float, int);
    extern Rac2Native_003ECB38_ConstBlock g_hero_state;

    char delta[0x10];
    char upPart[0x10];
    float zero;
    float angle;
    float length;
    float upDot;

    zero = 0.0f;

    func_2EE138(delta, rec, obj + 0x10);

    upDot = func_2EE1F8(delta, g_hero_state.tbl + 0xE0);
    func_2EE178(upPart, g_hero_state.tbl + 0xE0, upDot);
    func_2EE138(delta, delta, upPart);

    angle = func_2EE1F8(delta, g_hero_state.tbl + 0xC0);
    length = func_2EE238(delta);
    if (length == zero)
        return;
    angle = 1.57079637050628662f - func_2EE710(angle / length);
    if (func_2EE1F8(delta, g_hero_state.tbl + 0xD0) < zero)
        angle = -angle;

    func_31DE50(obj + 0xF8, angle, mob, fa, fb, fc, 0);
}

extern Rac2Native_003ECB38_ConstBlock g_hero_state;

/* Tries to create a Kilonoid or Synthenoid at a place, and starts a fallback effect if it cannot. */
void synthenoid_spawn_or_kilonoid(char *spawnPos, int classId)
{
    int spawned = 0;
    int i;
    char *pos;
    int cls;

    i = 0;
    pos = spawnPos;
    cls = classId;
    do {
        if (cls == 0xB02 /* Kilonoid */) {
            if (kilonoid_spawn(g_hero_state.tbl, pos) != 0)
                spawned = 1;
        } else {
            if (SpawnCB2Moby(g_hero_state.tbl, pos) != 0)
                spawned = 1;
        }
    } while (++i < 4);
    if (spawned != 0)
        return;
    func_L00_0035F180((char *)(*(int *)(*(int *)(D_L00_001D9F00 + *(unsigned char *)(D_L00_001DA860 + cls) * 4) + 0x28) + 0xC0),
                      0, 0, (char *)g_hero_position, 0x400);
}



/* func_L00_003ED198 is defined in L00_003EA0E0-seeker.c. */


extern void FastVecSub(char *local, char *first, char *second);

extern float mat_fast_helper_a(float a, float b);

extern void FastVecScale(char *dst, char *src, float scale);

extern float math_random_float_range(float a, float b);

extern float math_random_signed_float_range(float a, float b);

extern int FloatToInt(float f);

extern float IntToFloat(int v);

extern float FastAddRotations(float a, float b);

extern void vec_build_spherical_offset(float *p, float a, float b, float c);

extern char *SpawnSpinningSparkParticle(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);

extern void part_spawn_burst(float *out, float *dir, int a, int b, unsigned int color, int id,
                           float fa, float fb, float fc, float fd, float fe);

extern char g_camera_l00_position[];

extern char D_0018A0E0[];

/* Twenty times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   scale the hero facing direction by a random small amount, spawn a particle at the point
   jittered by a random amount on each axis and fill the new record's fields, then spawn a
   second particle along a random direction with a random magnitude; the original game role
   is unknown. */
/* Throws out a burst of sparks and puffs from a point. */
void part_l00_spawn_impact_spark_burst(float *origin)
{
    float toCamera[4];
    float direction[4];
    float spawnPos[4];
    float ang;
    float scale;
    float mag;
    float angle;
    float randomValue;
    int id;
    int i;
    char *particle;
    char *extra;

    FastVecSub((char *)toCamera, g_camera_l00_position, (char *)origin);
    ang = mat_fast_helper_a(toCamera[0], toCamera[1]);

    for (i = 19; i >= 0; i--) {
        randomValue = math_random_float_range(0.2f, 3.0f);
        FastVecScale((char *)direction, D_0018A0E0, -(randomValue * 0.01666666753590107f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        randomValue = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        spawnPos[0] = origin[0] + math_random_signed_float_range(0.0f, 0.2f);
        spawnPos[1] = origin[1] + math_random_signed_float_range(0.0f, 0.2f);
        spawnPos[2] = origin[2] + math_random_signed_float_range(0.0f, 0.2f);
        particle = SpawnSpinningSparkParticle((char *)spawnPos, 0.0f, 1.0f, 1.01f, randomValue, id, (char *)direction, 0x7F202020, 1);
        if (particle != 0) {
            extra = particle + 32;
            *(unsigned char *)(particle + 3) = 0x44;
            *(short *)(particle + 10) = 0x5A;
            *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(extra + 0x1C) = IntToFloat(5);
            *(int *)(extra + 4) = 3;
            *(unsigned char *)(extra + 0xA) = 0x30;
            *(unsigned char *)(extra + 0xB) = *(unsigned char *)(particle + 10);
        }
        scale = math_random_float_range(1.0f, 2.0f);
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(direction, scale * 0.01666666753590107f, angle, mag);
        spawnPos[0] = origin[0] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[1] = origin[1] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[2] = origin[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst(spawnPos, direction, 30, 127, 0x007F7F7F, id,
                      math_random_float_range(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}

/* Twenty rounds: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a
   random small amount on each axis and hand the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
/* Throws out a burst of small sparks from a point. */
void part_spawn_small_spark_burst(float *origin)
{
    float toCamera[4];
    float direction[4];
    float spawnPos[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    FastVecSub((char *)toCamera, g_camera_l00_position, (char *)origin);
    ang = mat_fast_helper_a(toCamera[0], toCamera[1]);

    for (i = 19; i >= 0; i--) {
        scale = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        math_random_float_range(0.05f, 0.2f);
        speed = 210000.0f;
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(direction, scale * 0.01666666753590107f, angle, mag);
        spawnPos[0] = origin[0] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[1] = origin[1] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[2] = origin[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst(spawnPos, direction, 30, 127, 0x007F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}
