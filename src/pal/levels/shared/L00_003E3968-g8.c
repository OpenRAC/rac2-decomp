/* func_PAL_L00_003E3968, the PAL copy of func_L00_003DF710: the same C, where func_002ABBB8
   becomes func_PAL_002AC718. */
#include "include_asm.h"
#include "common.h"

struct BFObject {
    char pad[0x30];
    unsigned char field_30;
    unsigned char field_31;
    unsigned short field_32;
};

extern struct BFPlayer { char pad[0xbf8]; char *target; } g_hero_state NOT_SDA;

extern float FastAddRotations(float, float);
extern void vec_clear_128(void *);
extern void euler_rotation_basis(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void make_hit_descriptor(void *, int, int, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern int coll_sweep_from_object(int, float, void *, int, float, float, int, int, int);
extern void moby_set_state(void *, int, int);
extern void moby_transform_point_by_attachment(void *, int, void *, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void moby_transform_point_and_rotation_by_parent(void *, int, void *, void *, void *, void *);
extern void moby_get_parent_transformed_point(void *, int, void *, void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int,
                          float, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void part_spawn_bursts_at_moby(void *);
extern int D_L00_001BF218 NOT_SDA;
extern int D_L00_001B0518 __attribute__((sda));
extern char D_L00_001A8F20[] MACRO_ADDR;

/* state 0: advances the object by its data's velocity; a collision deals damage and destroys it unless
   D_L00_001BF218 equals the data's type, otherwise it spawns three trail particles and grows its scale
   factor; state 1: spawns an explosion and deletes the object */
void func_PAL_L00_003E3968(char *object)
{
    float scale[4];
    float next[4];
    char query[48];
    float velocity[4];
    float zero[4];
    float pos[4];
    char *data = *(char **)(object + 0x68);
    float size0, size1, size2, spread;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(float *)(data + 0x18) = FastAddRotations(*(float *)(data + 0x18), *(float *)(data + 0x1c));
        vec_clear_128(scale);
        scale[1] = *(float *)(data + 0x18) * 0.25f;
        scale[0] = *(float *)(data + 0x18) * 0.5f;
        scale[2] = *(float *)(data + 0x18);
        euler_rotation_basis(object + 0xc0, scale);
        FastVecAdd(next, object + 0x10, data);
        make_hit_descriptor(query, *(int *)(data + 0x10), 1, data, *(float *)(data + 0x14));
        *(unsigned short *)(query + 0x1a) = *(unsigned short *)(object + 0xaa);
        if (CollLine(object + 0x10, next, 0, object, query) || coll_test_point(object + 0x10, 0, object, 0.3f)) {
            if (D_L00_001BF218) {
                if (D_L00_001BF218 != *(int *)(data + 0x10)) {
                    coll_sweep_from_object(*(int *)(data + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(data + 0x14), 0, 0, 1, 0);
                    moby_set_state(object, 1, -1);
                    return;
                }
            } else {
                coll_sweep_from_object(*(int *)(data + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(data + 0x14), 0, 0, 1, 0);
                moby_set_state(object, 1, -1);
                return;
            }
        }
        qcopy(object + 0x10, next);
        FastVecScale(velocity, data, -0.5f);
        vec_clear_128(zero);
        if (*(int *)(data + 0x24)) {
            moby_transform_point_by_attachment(object, *(int *)(data + 0x24), object + 0x10, pos);
            FastVecAdd(velocity, velocity, pos);
        }
        size0 = math_random_float_range(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = math_random_float_range(0.2f, 0.4f);
        part_spawn_gravity_fade(object + 0x10, velocity, 5, D_L00_001B0518, 3, 0x4f, 0, size0,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        qcopy(pos, object + 0x10);
        pos[0] += math_random_signed_float_range(0.0f, 0.15f);
        pos[1] += math_random_signed_float_range(0.0f, 0.15f);
        pos[2] += math_random_signed_float_range(0.0f, 0.15f);
        size1 = math_random_float_range(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = math_random_float_range(0.1f, 0.3f);
        part_spawn_gravity_fade(pos, velocity, 5, D_L00_001B0518, 7, 0x5f, 0, size1,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        pos[0] += math_random_signed_float_range(0.0f, 0.15f);
        pos[1] += math_random_signed_float_range(0.0f, 0.15f);
        pos[2] += math_random_signed_float_range(0.0f, 0.15f);
        size2 = math_random_float_range(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = math_random_float_range(0.2f, 0.4f);
        part_spawn_gravity_fade(pos, velocity, 5, D_L00_001B0518, 12, 0x7f, 0, size2,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        if (*(int *)(data + 0x24)) {
            moby_transform_point_and_rotation_by_parent(object, *(int *)(data + 0x24), object + 0x10, object + 0xf0, object + 0x10, object + 0xf0);
            moby_get_parent_transformed_point(object, *(int *)(data + 0x24), data, data);
        }
        break;
    case 1:
        func_PAL_002AC718(object, D_L00_001A8F20, object + 0x10, 0.0f, 0.0f, 10, 0, 16, 0.0f, 0.0f, 9.0f, 1.0f, -1,
                      15.0f, 0, 9, -1, 0, 0x810001);
        moby_mark_spawned(object);
        return;
    }
    if (*(float *)(data + 0x20) < 1.0f)
        *(float *)(data + 0x20) += 0.025f;
    *(float *)(object + 0x2c) = math_random_float_range(0.01f, 0.0125f) * *(float *)(data + 0x20);
    gfx_add_draw_callback_third(part_spawn_bursts_at_moby, object);
}
