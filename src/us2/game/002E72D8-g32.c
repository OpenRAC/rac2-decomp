/* func_US2_002E72D8, the USA v2.00 copy of func_002E64A0: the same C, where each piece's render
 * field is also set in the flags test (cleared with its flags raised, else the model's value).
 * In its own unit (flags in config/cflags.txt: -O2 -G32 -Wa,-G32 -ffunction-sections): the 16-byte
 * vectors below are reached through $gp. The third copy's source stays a block-scoped pointer: its
 * longer lifetime is what makes loop hoist it with the two stack addresses.
 */
#include "common.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    char header[0x10];
    float position[4];
    char pad20[4];
    char *model;
    char pad28[12];
    unsigned short flags;
    char pad36[0x32];
    char *state;
    char pad6c[0x2c];
    int render;
    char pad9c[0x20];
    unsigned char blocked;
    char padbd[3];
    float basis[3][4];
    float previous[4];
} Object;

typedef struct {
    float position[4];
    char gap[0x50];
    float focus[4];
} HeroPosition;

typedef struct {
    char prefix[0x80];
    HeroPosition hero;
    char gapF0[0x24c];
    Object *selected;
    int count;
    char gap344[0x1f4c];
    int collision;
} HeroGlobals;

typedef int Quad __attribute__((mode(TI)));

extern Object *g_equipment_pieces[];
extern char D_00214970[], D_00214978[];
extern int g_current_game_mode[] __attribute__((sda));
extern int D_001A8BB0_gp SDATA(D_001A8BB0);
extern int g_current_map_index[] __attribute__((sda));
extern float D_001ABF84 __attribute__((sda)), D_001ABF88 __attribute__((sda)), D_001ABF8C __attribute__((sda));
extern char D_001ABF18[16] __attribute__((sda)), D_001ABF28[16] __attribute__((sda));
extern char D_001ABF38[16] __attribute__((sda)), D_001ABF48[16] __attribute__((sda));
extern char D_001ABF58[16] __attribute__((sda)), D_001ABF68[16] __attribute__((sda));
extern char D_001ABF78[16] __attribute__((sda));
extern HeroGlobals g_hero_state;


extern void SpawnEquipmentPieces(void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_init_controller_params(void *, void *, int, int, void *, void *, void *, void *, void *, void *, void *);
extern void scale_vector(void *, void *, float);
extern int math_fast_helper_a(void *, float);
extern float vec_distance_xy(void *, void *);
extern int CollLine(void *, void *, int, int, int);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void moby_transform_joint_point(void *, int, void *), moby_transform_joint_to_world(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *), mat_get_euler_angles(void *, void *), func_002A10E8(void *);
extern void mat_combine_and_store(void *, void *, void *, void *), moby_update_sway(void *, void *, void *);

/* Spawns the equipment pieces if needed, then makes each piece follow the base object. */
void func_US2_002E72D8(Object *object)
{
    float p[4], old[4], matrix[16], previous[4], delta[4], offset[4];
    char *target;
    int i, j;
    unsigned char blocked;

    if (!g_equipment_pieces[0]) {
        SpawnEquipmentPieces(object);
        if (!g_current_game_mode[0]) {
            float height = coll_probe_ground_height_below(object->position, 0, 0.5f);
            if (height != 0.0f)
                object->position[2] = height + D_001ABF84;
            D_001ABF88 = object->position[2];
        }
        moby_init_controller_params(object, D_00214970, 0, 0, D_001ABF48, D_001ABF58, D_001ABF18, D_001ABF78,
                      D_001ABF68, D_001ABF28, D_001ABF38);
    }
    target = 0;
    if (!g_current_game_mode[0]) {
        scale_vector(p, object, 0.0009765625f);
        p[3] += 1.0f;
        if (math_fast_helper_a(p, 50.0f) == -1)
            return;
        if (!D_001A8BB0_gp) {
            blocked = 0;
            if (vec_distance_xy(object->position, ((char *)&g_hero_state.hero)) < 6.0f) {
                if (object->blocked) {
                    qcopy(p, ((char *)&g_hero_state.hero) + 0x60);
                    p[2] += 2.0f;
                    if (CollLine(((char *)&g_hero_state.hero) + 0x60, p, 0, g_hero_state.collision, 0))
                        blocked = 1;
                    else {
                        FastVecSub(old, object->position, ((char *)&g_hero_state.hero));
                        old[2] = 0;
                        vec_scale_to_length(old, old, 0.4f);
                        FastVecAdd(p, p, old);
                        blocked = CollLine(((char *)&g_hero_state.hero) + 0x60, p, 0, g_hero_state.collision, 0) != 0;
                    }
                } else {
                    qcopy(p, ((char *)&g_hero_state.hero) + 0x60);
                    p[2] += 2.0f;
                    blocked = CollLine(((char *)&g_hero_state.hero) + 0x60, p, 0, *(int *)(((char *)&g_hero_state.hero) + 0x2210), 0) != 0;
                }
            }
            object->blocked = blocked;
            if (object->blocked)
                math_step_value_toward_target(D_00214978, &D_001ABF8C, D_001ABF88 + 0.75f, 0.00055555557f, 0.00055555557f, 0.0166666675f);
            else
                math_step_value_toward_target(D_00214978, &D_001ABF8C, D_001ABF88, 0.00055555557f, 0.00055555557f, 0.0166666675f);
        }
    }
    moby_transform_joint_point(object, 1, matrix);
    moby_transform_joint_to_world(object, 1, p);
    for (i = 0; g_equipment_pieces[i]; i++) {
        if (object->flags & 1) {
            g_equipment_pieces[i]->render = 0;
            g_equipment_pieces[i]->flags |= 0x41;
        } else {
            g_equipment_pieces[i]->flags &= 0xFFBE;
            g_equipment_pieces[i]->render = *(int *)(g_equipment_pieces[i]->model + 0x10);
        }
        {
            Object *part = g_equipment_pieces[i];
            qcopy(old, part->position);
            qcopy(previous, part->previous);
            {
                float *from = object->position;
                qcopy(part->position, from);
            }
        }
        for (j = 0; j < 3; j++) {
            g_equipment_pieces[i]->basis[j][0] = matrix[j * 4];
            g_equipment_pieces[i]->basis[j][1] = matrix[j * 4 + 1];
            g_equipment_pieces[i]->basis[j][2] = matrix[j * 4 + 2];
        }
        if (g_current_game_mode[0] == 2 && g_current_map_index[0] == 5) {
            *(Quad *)offset = 0;
            offset[0] = -0.3372f;
            offset[1] = -0.5364f;
            offset[2] = -1.79489f;
            matrix_mul_vec3(offset, offset, g_equipment_pieces[i]->basis);
            FastVecAdd(delta, p, offset);
            qcopy(g_equipment_pieces[i]->position, delta);
        }
        mat_get_euler_angles(g_equipment_pieces[i]->basis, g_equipment_pieces[i]->previous);
        func_002A10E8(g_equipment_pieces[i]);
        {
            char *state = g_equipment_pieces[i]->state;
            FastVecSub(delta, g_equipment_pieces[i]->position, old);
            mat_combine_and_store(state + 0x20, delta, previous, g_equipment_pieces[i]->previous);
        }
        if (g_hero_state.count >= 2 && g_hero_state.selected == g_equipment_pieces[i])
            target = ((char *)&g_hero_state.hero);
        if (g_current_game_mode[0]) {
            g_equipment_pieces[i]->render = 0;
            object->render = 0;
        } else if (object->render)
            g_equipment_pieces[i]->render = *(int *)(g_equipment_pieces[i]->model + 0x10);
    }
    if (!g_current_game_mode[0])
        moby_update_sway(object, D_00214970, target);
}
