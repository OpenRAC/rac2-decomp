/* func_PAL_L18_00318BE0, the PAL copy of func_L18_003170F8: per-frame update of Damosel's scene.
 * The object scan is the one in func_L05_00314E28, with a level test added to its last case; then,
 * in mode 4, a 13-entry table sets off an explosion, with an optional camera shake, when the scene
 * timer reaches an entry's time, scaled for 50 Hz.
 *
 * Unlike the USA copy this one needs no -fmove-all-movables: the scale makes the spot loop too long
 * for loop.c to hoist everything, and retail stops at 0.08f, leaving 58 and 0.07f in the loop.  That
 * takes the shake stores in channel order, and the scene, table and id locals, whose longer
 * lifetimes let loop.c hoist those values in its first pass. */
#include "common.h"

typedef struct {
    unsigned char pad00[0x30];
    int mode, timer;
    unsigned char pad38[0xC];
    short count;
    unsigned char pad46[0x146];
    unsigned char *objects[256];
} Scene18;

typedef struct {
    unsigned char pad00[0x34];
    unsigned short flags;
    unsigned char pad36[0xCA];
} SceneMoby;

typedef struct {
    float position[4];
    int time;
    float scale;
    int cameraRelative;
    float shake;
} ExplosionSpot;

typedef struct {
    unsigned char pad00[0x140];
    float position[4];
    unsigned char pad150[0x10];
    float shake;
    int pad164, shakeTime, shakeTimer;
    unsigned char pad170[0x10];
    float secondaryShake;
    int pad184, secondaryShakeTime;
    unsigned char pad18C[0x370 - 0x18C];
    float matrix[12];
} SceneCamera;

extern Scene18 g_scene_movables_state;
extern int g_current_map_index __attribute__((sda));
extern SceneMoby *g_moby_l18_table MACRO_ADDR;
extern SceneMoby *g_moby_l18_table_end MACRO_ADDR;
extern SceneCamera g_hero_l18_state_extra;
extern ExplosionSpot g_explosion_spots[];

extern void anim_start_startup_animations(void);
extern void update_equipment_pieces_pal(void *);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

void damosel_update_timed_explosions_pal(void)
{
    float position[4] __attribute__((aligned(16)));
    int i, j, k;
    unsigned char *object, *state;
    SceneMoby *moby;
    ExplosionSpot *spot, *table;
    Scene18 *scene;

    anim_start_startup_animations();
    for (i = 0; i < g_scene_movables_state.count; i++) {
        object = g_scene_movables_state.objects[i];
        if (object && *(short *)(object + 0xAA) == 0xE29) {
            *(unsigned short *)(object + 0x34) |= 0x800;
        }
        if (*(short *)(object + 0xAA) == 0xD54) {
            update_equipment_pieces_pal(object);
        }
        if (object) {
            int type = MOBY_CLASS_TV_SCREENS;

            if (*(short *)(object + 0xAA) == type && g_current_map_index != 51) {
                state = *(unsigned char **)(object + 0x68);
                if (state) {
                    math_store_angle_update_result(object, state + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
                }
            }
        }
    }
    if (g_current_map_index != 18 || g_scene_movables_state.mode != 4) {
        return;
    }
    if (g_scene_movables_state.timer == 1) {
        for (k = 0; &g_moby_l18_table[k] < g_moby_l18_table_end; k++) {
            moby = &g_moby_l18_table[k];
            moby->flags |= 0x41;
        }
    }
    for (j = 0; j < 13; j++) {
        scene = &g_scene_movables_state;
        table = g_explosion_spots;
        spot = &table[j];
        if (scene->timer == (((int)(spot->time) * 5 + 2) / 6)) {
            qcopy(position, spot->position);
            if (spot->cameraRelative) {
                matrix_mul_vec3(position, position, g_hero_l18_state_extra.matrix);
                FastVecAdd(position, position, g_hero_l18_state_extra.position);
            }
            SpawnExplosion_pal(position, 0, 25, 20, 20, 20, 45, 1, spot->scale, 20.0f, 1, 1, 0, 0);
            if (spot->shake > 0.0f) {
                g_hero_l18_state_extra.shakeTime = 46;
                g_hero_l18_state_extra.shake = spot->shake * 0.08f;
                g_hero_l18_state_extra.shakeTimer = 0;
                g_hero_l18_state_extra.secondaryShakeTime = 58;
                g_hero_l18_state_extra.secondaryShake = spot->shake * 0.07f;
            }
        }
    }
}
