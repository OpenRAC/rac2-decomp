/* func_PAL_L02_0038ECC0, the PAL copy of func_L02_0038BD00: the same C, where the frame time becomes
   0.020000001f, the spin scale 0.0003490659f, and the random u76 is scaled by 5/6. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

struct Object {
    char pad0[0x20];
    u8 state, group;
    u16 pad22;
    char *model;
    int pad28;
    float scale;
    u8 flags30;
    u8 pad31;
    u16 flags32, flags34;
    char pad36[0x32];
    void *data;
    char pad6c[0x3e];
    short kind;
};

struct Rail {
    int count;
    int unused[3];
    float point[0][4];
};

struct PrivateData {
    int railIndex;
    float f04, f08;
    int i0c;
    float position, step;
    int i18, i1c;
    float vector20[4];
    float primary[3][4];
    struct Rail *rail;
    int i64;
    float f68, f6c;
    u16 closed, enabled, u74, u76;
    float scale, spacing, phase, speed;
    int i88;
    char pad8c[0x14];
    float secondary[3][4];
};

extern short *g_entity_group_lists[];
extern struct Rail *g_route_polygons[];
extern char *g_moby_l02_pool __attribute__((section(".sdata")));
extern int g_current_map_index;
/* Two random ranges, each read as a lower and an upper bound. */
extern int g_spin_time_range[] __attribute__((sda));
extern float g_spin_rate_range[] __attribute__((sda));
extern float g_matrix_template_rows[3][4];
extern float g_vector_pair_template_a[2][4];
extern float g_vector_pair_template_b[2][4];
extern float g_vector_pair_template_c[2][4];
extern float g_vector_pair_template_d[2][4];
extern float g_vector_pair_template_e[2][4];
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void vec_clear_128(void *);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_range(int, int);
extern void FastVecScale(void *, void *, float);

/* Shuffles the group's members and spaces them out along the rail with random speeds and phases
   (PAL: 50 Hz timings). */
void init_rail_group_members_pal(struct Object *owner, int group) {
    float vectors[6][4];
    struct PrivateData *data;
    struct Object *object;
    struct Rail *rail;
    short *cursor;
    int total, i, j, index;
    float scale;
    float (*source)[4];
    float (*destination)[4];
    float (*scaled)[4];
    float segment_inverse_length, end_distance, spacing, speed, rail_count, numerator;

    cursor = g_entity_group_lists[group];
    if (!cursor)
        return;
    data = owner->data;
    owner->flags30 = 0xFF;
    rail = g_route_polygons[data->railIndex];
    segment_inverse_length = 1.0f / fast_vec_dist(rail->point[0], rail->point[1]);
    rail_count = (float)rail->count;
    end_distance = fast_vec_dist(rail->point[0], rail->point[rail->count - 1]);
    data->closed = end_distance < 5.0f;
    data->rail = rail;
    data->step = data->f08 * (segment_inverse_length * 0.020000001f);
    cursor = g_entity_group_lists[group];
    i = 0;
    total = 1;
    while (!(cursor[i] & 0x8000)) {
        if (i > 0) {
            short temporary;
            j = math_random_int_below(i);
            temporary = cursor[j];
            cursor[j] = cursor[i];
            cursor[i] = temporary;
        }
        i++;
        total++;
    }
    spacing = ((float)rail->count * 0.4f) / (float)total;
    speed = (data->step * 0.25f) / spacing;
    cursor = g_entity_group_lists[group];
    index = total - 1;
    do {
        object = (struct Object *)((char *)g_moby_l02_pool + (*cursor & 0x7FFF) * 256);
        data = object->data;
        if (object != owner)
            object->flags34 |= 2;
        numerator = IntToFloat(index);
        data->position = numerator / IntToFloat(total) * rail_count;
        data->spacing = spacing;
        data->speed = speed * math_random_float_range(0.75f, 1.25f);
        data->phase = math_random_angle();
        data->enabled = 1;
        vec_clear_128(data->vector20);
        data->vector20[2] = data->f04 * math_random_signed_float_range(0.5f, 1.0f);
        data->u76 = ((s32)math_random_int_range(g_spin_time_range[0], g_spin_time_range[1]) * 5 + 2) / 6;
        data->f68 = math_random_angle();
        data->f6c = math_random_signed_float_range(g_spin_rate_range[0], g_spin_rate_range[1]) * 0.0003490659f;
        scale = object->scale / *(float *)(object->model + 0x24);
        data->i18 = -1;
        data->i1c = 0;
        data->i88 = 0;
        data->scale = scale;
        if (object->kind == 0x9B0) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            *(TI128 *)vectors[2] = 0;
            vectors[0][0] = -2.0999999046325684f;
            vectors[0][1] = 0.75f;
            vectors[0][2] = 0.8600000143051147f;
            vectors[1][0] = -2.0999999046325684f;
            vectors[1][1] = -0.75f;
            vectors[1][2] = 0.8600000143051147f;
            vectors[2][0] = -3.0f;
            vectors[2][2] = -0.6700000166893005f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            FastVecScale(vectors[2], vectors[2], data->scale);
            qcopy(data->primary[2], vectors[2]);
            {
                TI128 copy0, copy1, copy2;
                copy0 = *(TI128 *)g_matrix_template_rows[0];
                *(TI128 *)vectors[3] = copy0;
                copy1 = *(TI128 *)g_matrix_template_rows[1];
                *(TI128 *)vectors[4] = copy1;
                copy2 = *(TI128 *)g_matrix_template_rows[2];
                *(TI128 *)vectors[5] = copy2;
            }
            source = &vectors[3];
            destination = data->secondary;
            for (k = 2; k >= 0; k--) {
                FastVecScale(destination, source, data->scale);
                destination++;
                source++;
            }
        }
        if (object->kind == 0x9B7) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -3.7179999351501465f;
            vectors[0][2] = 0.7770000100135803f;
            vectors[1][0] = -3.7179999351501465f;
            vectors[1][2] = -0.8989999890327454f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            {
                TI128 copy0 = *(TI128 *)g_vector_pair_template_a[0];
                TI128 copy1 = *(TI128 *)g_vector_pair_template_a[1];
                *(TI128 *)vectors[2] = copy0;
                *(TI128 *)vectors[3] = copy1;
            }
            source = &vectors[2];
            destination = data->secondary;
            for (k = 1; k >= 0; k--) {
                FastVecScale(destination, source, data->scale);
                destination++;
                source++;
            }
        }
        if (object->kind == 0xB15) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -2.424999952316284f;
            vectors[0][1] = 3.364300012588501f;
            vectors[0][2] = 0.9300000071525574f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -2.424999952316284f;
            vectors[1][1] = -3.005000114440918f;
            vectors[1][2] = 0.9300000071525574f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            {
                TI128 copy0 = *(TI128 *)g_vector_pair_template_b[0];
                TI128 copy1 = *(TI128 *)g_vector_pair_template_b[1];
                *(TI128 *)vectors[2] = copy0;
                *(TI128 *)vectors[3] = copy1;
            }
            source = &vectors[2];
            destination = data->secondary;
            for (k = 1; k >= 0; k--) {
                FastVecScale(destination, source, data->scale);
                destination++;
                source++;
            }
        }
        if (object->kind == 0x134B) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -0.2930000126361847f;
            vectors[0][1] = 0.22200000286102295f;
            vectors[0][2] = -0.14900000393390656f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -0.2930000126361847f;
            vectors[1][1] = -0.22200000286102295f;
            vectors[1][2] = -0.14900000393390656f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            {
                TI128 copy0 = *(TI128 *)g_vector_pair_template_c[0];
                TI128 copy1 = *(TI128 *)g_vector_pair_template_c[1];
                *(TI128 *)vectors[2] = copy0;
                *(TI128 *)vectors[3] = copy1;
            }
            source = &vectors[2];
            destination = data->secondary;
            for (k = 1; k >= 0; k--) {
                FastVecScale(destination, source, data->scale);
                destination++;
                source++;
            }
        }
        if (object->kind == 0xB13) {
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -3.677999973297119f;
            vectors[0][1] = 0.8080000281333923f;
            vectors[0][2] = 0.10000000149011612f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -3.677999973297119f;
            vectors[1][1] = -0.8080000281333923f;
            vectors[1][2] = 0.10000000149011612f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
        }
        if (object->kind == 0xD5C) {
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -3.677999973297119f;
            vectors[0][1] = 0.8080000281333923f;
            vectors[0][2] = 0.10000000149011612f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -3.677999973297119f;
            vectors[1][1] = -0.8080000281333923f;
            vectors[1][2] = 0.10000000149011612f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
        }
        if (object->kind == 0x127D) {
            int k;
            float (*walker)[4];
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -0.16500000655651093f;
            vectors[0][1] = 0.699999988079071f;
            vectors[0][2] = -0.16099999845027924f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -0.16500000655651093f;
            vectors[1][1] = -0.699999988079071f;
            vectors[1][2] = -0.16099999845027924f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            scaled = &vectors[2];
            walker = scaled;
            k = 0;
            destination = data->secondary;
            for (; k < 2; k++) {
                qcopy(vectors[k + 2], data->primary[k]);
                FastVecScale(destination, walker, data->scale);
                walker++;
                destination++;
            }
        }
        if (object->kind == 0x128B) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -0.003000000026077032f;
            vectors[0][1] = 0.8429999947547913f;
            vectors[0][2] = -0.30300000309944153f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -0.003000000026077032f;
            vectors[1][1] = -0.8429999947547913f;
            vectors[1][2] = -0.30300000309944153f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            {
                TI128 copy0 = *(TI128 *)g_vector_pair_template_d[0];
                TI128 copy1 = *(TI128 *)g_vector_pair_template_d[1];
                *(TI128 *)vectors[2] = copy0;
                *(TI128 *)vectors[3] = copy1;
            }
            source = &vectors[2];
            destination = data->secondary;
            for (k = 1; k >= 0; k--) {
                FastVecScale(destination, source, data->scale);
                destination++;
                source++;
            }
        }
        if (object->kind == 0x1290) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            *(TI128 *)vectors[2] = 0;
            vectors[0][0] = -0.8230000138282776f;
            vectors[0][1] = 0.6980000138282776f;
            vectors[0][2] = -0.21899999678134918f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -0.8230000138282776f;
            vectors[1][1] = -0.6980000138282776f;
            vectors[1][2] = -0.21899999678134918f;
            vectors[1][3] = 1.0f;
            vectors[2][0] = -1.3760000467300415f;
            vectors[2][2] = 0.20800000429153442f;
            vectors[2][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            FastVecScale(vectors[2], vectors[2], data->scale);
            qcopy(data->primary[2], vectors[2]);
            scaled = &vectors[3];
            source = scaled;
            k = 0;
            destination = data->secondary;
            for (; k < 3; k++) {
                qcopy(vectors[k + 3], data->primary[k]);
                FastVecScale(destination, source, data->scale);
                source++;
                destination++;
            }
        }
        if (object->kind == 0x1340) {
            int k;
            *(TI128 *)vectors[0] = 0;
            *(TI128 *)vectors[1] = 0;
            vectors[0][0] = -0.2150000035762787f;
            vectors[0][1] = 2.131999969482422f;
            vectors[0][2] = -0.3190000057220459f;
            vectors[0][3] = 1.0f;
            vectors[1][0] = -0.2150000035762787f;
            vectors[1][1] = -2.131999969482422f;
            vectors[1][2] = -0.3190000057220459f;
            vectors[1][3] = 1.0f;
            FastVecScale(vectors[0], vectors[0], data->scale);
            qcopy(data->primary[0], vectors[0]);
            FastVecScale(vectors[1], vectors[1], data->scale);
            qcopy(data->primary[1], vectors[1]);
            {
                TI128 copy0 = *(TI128 *)g_vector_pair_template_e[0];
                TI128 copy1 = *(TI128 *)g_vector_pair_template_e[1];
                *(TI128 *)vectors[2] = copy0;
                *(TI128 *)vectors[3] = copy1;
            }
            source = &vectors[2];
            destination = data->secondary;
            for (k = 1; k >= 0; k--) {
                FastVecScale(destination, source, data->scale);
                destination++;
                source++;
            }
        }
        object->state = 1;
        if (g_current_map_index != 3)
            object->flags32 = 0xBE;
        index--;
    } while ((short)*cursor++ >= 0);
}
