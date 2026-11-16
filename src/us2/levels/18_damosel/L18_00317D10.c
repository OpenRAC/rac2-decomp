#include "names.h"
/* func_US2_L18_00317D10, the USA v2.00 copy of func_L18_003170F8: the same scene update, where
 * class 0xFA0's effect is skipped while D_001A79F0 is 0x33.  That test adds a constant to the
 * object scan, and the wording below follows from loop.c's movable threshold (61, less 3 per
 * move, times savings and lifetime, against the loop's insn count).  v1.01's unit needs
 * -fmove-all-movables; this one does not, because retail hoists 0x33 only in the second loop pass,
 * after the scan pointer's init.
 *
 * The scan loop's bottom test reads the count through `scene`, set in the body.  That makes 49
 * insns rather than 51, so the first pass takes 0xFA0 and leaves 0x33.  The entry test compares
 * `i`, as a for loop's does: combine then reissues `i = 0` without its REG_EQUAL note, and `i` is
 * not given a doubled live length that would lose it $s1 to the scan pointer.
 *
 * In the timed-explosion loop, `timing` and `spots` are set first and the two times held in
 * locals, for the lifetimes that carry those constants past the first pass's threshold.  With the
 * table address hoisted there, `spot` is reduced in the first pass, `j` only counts by the second,
 * and the second pass reverses it. */
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
    int camera_relative;
    float shake;
} ExplosionSpot;

typedef struct {
    unsigned char pad00[0x140];
    float position[4];
    unsigned char pad150[0x10];
    float shake;
    int pad164, shake_time, shake_timer;
    unsigned char pad170[0x10];
    float secondary_shake;
    int pad184, secondary_shake_time;
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
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(void *, void *, unsigned int, unsigned int, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* Per-frame update of the Damosel scene: tweaks a few kinds of objects, then in the final sequence sets off timed explosions with optional camera shake (USA v2.00 copy). */
void UpdateDamoselTimedExplosions_us2(void)
{
    float position[4] __attribute__((aligned(16)));
    int i, j, k, timer;
    unsigned char *object, *state;
    SceneMoby *moby;
    ExplosionSpot *spot, *spots;
    Scene18 *scene, *timing;
    int shake_time, secondary_shake_time;

    anim_start_startup_animations();
    i = 0;
    if (i < g_scene_movables_state.count) do {
        scene = &g_scene_movables_state;
        object = scene->objects[i];
        if (object && *(short *)(object + 0xAA) == 0xE29) {
            *(unsigned short *)(object + 0x34) |= 0x800;
        }
        if (*(short *)(object + 0xAA) == 0xD54) {
            UpdateEquipmentPieces(object);
        }
        if (object && *(short *)(object + 0xAA) == MOBY_CLASS_TV_SCREENS && g_current_map_index != 0x33) {
            state = *(unsigned char **)(object + 0x68);
            if (state) {
                math_store_angle_update_result(object, state + 0xC, 0x80AAAAD2, 0x80396464, 0.06108653545379639f);
            }
        }
        i++;
    } while (i < scene->count);
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
        timing = &g_scene_movables_state;
        spots = g_explosion_spots;
        timer = timing->timer;
        spot = &spots[j];
        if (timer == spot->time) {
            qcopy(position, spot->position);
            if (spot->camera_relative) {
                matrix_mul_vec3(position, position, g_hero_l18_state_extra.matrix);
                FastVecAdd(position, position, g_hero_l18_state_extra.position);
            }
            SpawnExplosion(position, 0, 25, 20, 20, 20, 45, 1, spot->scale, 20.0f, 1, 1, 0, 0);
            if (spot->shake > 0.0f) {
                shake_time = 55;
                secondary_shake_time = 70;
                g_hero_l18_state_extra.shake_time = shake_time;
                g_hero_l18_state_extra.secondary_shake_time = secondary_shake_time;
                g_hero_l18_state_extra.shake_timer = 0;
                g_hero_l18_state_extra.shake = spot->shake * 0.08f;
                g_hero_l18_state_extra.secondary_shake = spot->shake * 0.07f;
            }
        }
    }
}
