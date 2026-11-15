#include "common.h"

typedef unsigned int PlatformQuad __attribute__((mode(TI)));
typedef union { PlatformQuad q; float f[4]; } PlatformVector;
typedef struct { int paths[5]; } PlatformPathRow;
typedef struct {
    u8 pad0[0x3E];
    u16 flags3E;
    u8 pad40[0x50 - 0x40];
    u8 motion[0x8C - 0x50];
    int flags8C;
    float progress;
    int point;
    float field98, pitchSpeed, yawSpeed;
    int selection, sound, enabled;
    int triggers[5];
    int entryPaths[5];
    int middlePaths[5];
    int exitPaths[5];
    u8 pad100[0x114 - 0x100];
    int field114;
    float field118, field11C, field120, field124;
    int path128;
    float startHeight;
} PlatformVars;
typedef struct {
    u8 pad0[0x10];
    PlatformVector position;
    u8 state;
    u8 pad21[0x30 - 0x21];
    u8 opacity, field31;
    short timer;
    u16 flags;
    u8 pad36[0x68 - 0x36];
    PlatformVars *vars;
    u8 pad6C[0x98 - 0x6C];
    int animation;
    u8 pad9C[0xB0 - 0x9C];
    u8 group, fieldB1;
    u16 uid;
    u8 padB4[0xBC - 0xB4];
    u8 choice;
    u8 padBD[0xF0 - 0xBD];
    PlatformVector rotation;
} PlatformMoby;
typedef struct {
    int count;
    u8 pad04[0xC];
    PlatformVector points[2];
} PlatformPath;
extern PlatformPath *g_path_l17_table[];
extern int D_L17_001B0340 __attribute__((sda));
extern float D_L17_001B034C __attribute__((sda));
extern float D_L17_001B0354 __attribute__((sda));
typedef struct {
    u8 pad0[0x212];
    short mode212, mode214;
    u8 pad216[0x33C - 0x216];
    u8 *groundObject;
    u8 pad340[0x34E - 0x340];
    short mode34E;
} PlatformHero;
extern PlatformHero g_hero_state;
extern float g_hero_position[];
extern char *D_0018A15C NOT_SDA;
extern int g_current_map_index;
extern u8 D_0019B4A8[], D_0019B2E8[];
/* The level's save record: one collected flag per object id from 0x464. */
typedef struct { u8 pad[0x464]; u8 collected[0]; } L17SaveState;
extern L17SaveState D_L17_0021EBB0;
extern int D_00138324 NOT_SDA;
extern u8 D_L17_001DBF82[];
extern char g_sound_state[];
extern int ride_platform_is_carrying(void *);
extern void table_set_entry_field(void *, int);
extern void effect_create_timed(void *, void *, int, u32, int, int, int, float);
extern float mat_fast_helper_a(float, float);
extern void moby_mark_spawned(void *);
extern void ride_platform_select_entry(void *);
extern int ride_platform_move_along_path(void *, int, void *);
extern int platform_move_along_path_with_sound(void *, int, void *);
extern int platform_is_object_under_player(void *);
extern void platform_attach_path_to_transform(void *);
extern float math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern void TryClaimNotice(int, int, int);
extern float fast_vec_dist(void *, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void snd_stop_voice(int);
extern void platform_update_bob_sway(void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

static __inline__ void stopSound(u8 *object, PlatformVars *data)
{
    char *sound;

    if (data->sound != -1) {
        sound = g_sound_state + data->sound * 0x70;
        if (*(u8 **)(sound + 0x88) == object && *(u8 *)(sound + 0x74))
            snd_stop_voice(data->sound);
    }
    data->sound = -1;
}

/* Updates a ride platform. State 1 idles until triggered; states 3 and 8 wait for input bit 0x10
   from the player standing on it; the others follow its entry, middle or exit path, chosen by
   moby->choice, forwards or back, and stop its sound on the way. */
void UpdateRidePlatform(u8 *object)
{
    PlatformVector oldPosition, oldRotation, delta;
    PlatformMoby *moby = (PlatformMoby *)object;
    PlatformVars *data = moby->vars;

    u16 id;
    PlatformPathRow *exitRow;
    table_set_entry_field(object, ride_platform_is_carrying(object));
    data->flags8C |= 1;
    data->flags3E |= 8;
    if (D_L17_001B0340) {
        int i;
        for (i = 0; i < g_path_l17_table[data->entryPaths[0]]->count; i++)
            effect_create_timed(&g_path_l17_table[data->entryPaths[0]]->points[i],
                              object, 4, 0x800000FF, 0x7F, 2, 0xFF, 0.333f);
        for (i = 0; i < g_path_l17_table[data->middlePaths[0]]->count; i++)
            effect_create_timed(&g_path_l17_table[data->middlePaths[0]]->points[i],
                              object, 4, 0x8000FF00, 0x7F, 2, 0xFF, 0.333f);
        for (i = 0; i < g_path_l17_table[data->exitPaths[0]]->count; i++)
            effect_create_timed(&g_path_l17_table[data->exitPaths[0]]->points[i],
                              object, 4, 0x80FF0000, 0x7F, 2, 0xFF, 0.333f);
    }
    qcopy(&oldPosition, &moby->position);
    qcopy(&oldRotation, &moby->rotation);
    switch (moby->state) {
    case 0:
        if (data->entryPaths[0] != -1) {
            PlatformPath *path = g_path_l17_table[data->entryPaths[0]];
            qcopy(&moby->position, &path->points[0]);
            moby->rotation.f[2] = mat_fast_helper_a(path->points[1].f[0] - moby->position.f[0],
                                           path->points[1].f[1] - moby->position.f[1]);
        } else if (data->middlePaths[0] != -1) {
            PlatformPath *path = g_path_l17_table[data->middlePaths[0]];
            qcopy(&moby->position, &path->points[0]);
            moby->rotation.f[2] = mat_fast_helper_a(path->points[1].f[0] - moby->position.f[0],
                                           path->points[1].f[1] - moby->position.f[1]);
        }
        moby->timer = 0;
        moby->opacity = 0xFF;
        data->selection = -1;
        data->sound = -1;
        moby->state = 1;
        moby->flags = (moby->flags | 0x41) & 0xEFFF;
        moby->animation = 0;
        id = moby->uid;
        if (D_L17_0021EBB0.collected[(s16)id]) goto destroy;
        {
            int packed = D_0019B4A8[((s16)id >> 1) + (g_current_map_index << 10)];
            if ((id & 1) ? ((packed >> 4) & 7) : (packed & 7)) {
        destroy:
                moby_mark_spawned(object);
                return;
            }
        }
        break;
    case 1: {
        int i;
        if (data->enabled && (D_0019B2E8[moby->group + (g_current_map_index << 4)] & 0x80)) {
            for (i = 0; i < 5; i++) {
                if (data->triggers[i] != -1 || data->selection == i)
                    ride_platform_select_entry(object);
            }
        }
        break;
    }
    case 2:
        if (data->entryPaths[moby->choice] == -1 ||
            ride_platform_move_along_path(object, data->entryPaths[moby->choice], &data->sound)) {
            moby->state = 3;
            data->field114 = -1;
            data->startHeight = moby->position.f[2];
        }
        break;
    case 3:
        math_approach_target_with_direction_mode(&moby->rotation.f[1], 0.0f, &data->pitchSpeed,
                     D_L17_001B034C * 4.848137450608192e-06f,
                     D_L17_001B034C * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        math_approach_target_with_direction_mode(&moby->rotation, 0.0f, &data->yawSpeed,
                     D_L17_001B0354 * 4.848137450608192e-06f,
                     D_L17_001B0354 * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        if (g_hero_state.groundObject == object && g_hero_state.mode34E == 0) {
            TryClaimNotice(10, 0x27ED, 1);
            if (D_00138324 & 0x10) {
                data->progress = 0;
                moby->state = 4;
                data->point = 1;
            }
        } else ride_platform_select_entry(object);
        goto updateSound;
    case 4:
        moby->state = 5;
        stopSound(object, data);
        break;
    case 5:
        if (platform_is_object_under_player(object)) {
            g_hero_state.mode212 = 4;
            g_hero_state.mode214 = 4;
        }
        if (ride_platform_move_along_path(object, data->middlePaths[moby->choice], &data->sound))
            moby->state = 6;
        else platform_attach_path_to_transform(object);
        break;
    case 6:
        math_approach_target_with_direction_mode(&moby->rotation.f[1], 0.0f, &data->pitchSpeed,
                     D_L17_001B034C * 4.848137450608192e-06f,
                     D_L17_001B034C * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        math_approach_target_with_direction_mode(&moby->rotation, 0.0f, &data->yawSpeed,
                     D_L17_001B0354 * 4.848137450608192e-06f,
                     D_L17_001B0354 * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        exitRow = (PlatformPathRow *)data->exitPaths;
        if (exitRow->paths[moby->choice] != -1 &&
            fast_vec_dist(&moby->position, g_hero_position) > 15.0f) {
            moby->state = 7;
            data->point = 1;
        } else if (exitRow->paths[moby->choice] == -1 && D_0018A15C != (char *)object)
            moby->state = 1;
        goto updateSound;
    case 8:
        math_approach_target_with_direction_mode(&moby->rotation.f[1], 0.0f, &data->pitchSpeed,
                     D_L17_001B034C * 4.848137450608192e-06f,
                     D_L17_001B034C * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        math_approach_target_with_direction_mode(&moby->rotation, 0.0f, &data->yawSpeed,
                     D_L17_001B0354 * 4.848137450608192e-06f,
                     D_L17_001B0354 * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        if (g_hero_state.groundObject == object && g_hero_state.mode34E == 0) {
            TryClaimNotice(10, 0x27ED, 1);
            if (D_00138324 & 0x10) {
                data->progress = 0;
                moby->state = 9;
                data->point = g_path_l17_table[data->middlePaths[moby->choice]]->count - 2;
            }
        }
updateSound:
        if (!snd_is_voice_playing_for_owner(object, data->sound) && D_L17_001DBF82[0] != 0xFF)
            data->sound = snd_play_from_class_bank(1, 4, object, 0x922);
        break;
    case 9:
        moby->state = 10;
        stopSound(object, data);
        break;
    case 10:
        if (platform_is_object_under_player(object)) {
            g_hero_state.mode212 = 4;
            g_hero_state.mode214 = 4;
        }
        if (platform_move_along_path_with_sound(object, data->middlePaths[moby->choice], &data->sound))
            moby->state = 6;
        break;
    case 7:
        if (ride_platform_move_along_path(object, data->exitPaths[moby->choice], &data->sound)) {
            moby->timer = 0;
            moby->state = 1;
            moby->animation = 0;
        }
        break;
    }
    platform_update_bob_sway(object);
    FastVecSub(&delta, &moby->position, &oldPosition);
    mat_combine_and_store(data->motion, &delta, &oldRotation, &moby->rotation);
}
