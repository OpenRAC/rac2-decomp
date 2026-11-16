#include "names.h"
/* func_PAL_L08_003DC488, the PAL copy of func_L08_003D8348: the same C, where unk_6C 0.25f becomes 0.3f,
   unk_70 0.116667f becomes 0.14000001f (x6/5), unk_78 0.00833333f becomes 0.012f (x36/25) and unk_74/unk_7C 0.00416667f
   becomes 0.006f (x36/25). */
#include "common.h"

extern int FloatToInt(float);
extern void moby_store_ground_height(void *);
extern void moby_mark_spawned(void *);
extern float coll_point_depth_in_volumes(void *, int, int, int, int);
extern float path_l01_compute_segment_lengths(void *);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int func_001163B0(void);
extern void FastVecAdd(void *, void *, void *);
extern int g_current_map_index __attribute__((sda));
extern char g_moby_nibble_table[];

typedef int InitVector __attribute__((mode(TI)));
typedef struct {
    int unk_0;
    char pad4[8];
    int unk_C;
    char pad10[0x18];
    float unk_28;
    char pad2C[12];
    float unk_38;
} InitContext;
extern InitContext g_init_context;
typedef struct {
    u8 pad0[0x464];
    u8 flags[0];
} InitFlags;
extern InitFlags g_moby_spawn_state_flags_b;
typedef struct {
    u8 pad0[0xB0];
    u8 unk_B0;
    u8 padB1;
    u16 unk_B2;
    u8 tail[0x4C];
} InitEntry;
extern u32 g_moby_array __attribute__((sda));
extern void *g_path_segment_list __attribute__((section(".data")));

typedef struct {
    u8 pad0[0x10];
    void *unk_10;
    u8 pad14[0x14];
    u8 unk_28;
    u8 unk_29;
    u8 pad2a[0x6];
    float unk_30;
    u8 pad34[0x14];
    u8 unk_48;
    u8 pad49[0x1];
    u8 unk_4A;
    u8 pad4b[0x15];
    u8 unk_60;
    u8 unk_61;
    u8 unk_62;
    u8 pad63[0x3];
    u8 unk_66;
    u8 unk_67;
    u8 pad68[0x2];
    u8 unk_6A;
    u8 pad6b[0x1];
    float unk_6C;
    float unk_70;
    float unk_74;
    float unk_78;
    float unk_7C;
    float unk_80;
    float unk_84;
    u16 unk_88;
    u8 pad8a[0x2];
    float unk_8C;
    u8 pad90[0x8];
    int unk_98;
    u8 pad9c[0xC];
    float unk_A8;
    float unk_AC;
    u8 padb0[0xC];
    u8 unk_BC;
    u8 unk_BD;
    u8 unk_BE;
    u8 unk_BF;
    u8 padc0[0x2];
    u8 unk_C2;
    u8 unk_C3;
    u8 unk_C4;
    u8 padc5[0x1];
    u8 unk_C6;
    u8 padc7[0x31];
    float unk_F8;
    u8 padfc[0x24];
    float unk_120;
    u8 pad124[0xC];
    float unk_130;
    u8 pad134[0x1C];
    float unk_150;
    u8 pad154[0x8];
    int unk_15C;
    u8 pad160[0x2A4];
    int unk_404;
    u16 unk_408;
    u16 unk_40A;
    u8 unk_40C;
    u8 pad40d[0x3];
    int unk_410;
    int unk_414;
    int unk_418;
    int unk_41C;
    int unk_420;
    int unk_424;
    int unk_428;
    int unk_42C;
    int unk_430;
    float unk_434;
    u8 pad438[0x18];
    int unk_450;
} InitState;
typedef struct {
    u8 pad0[0x18];
    float unk_18;
    u8 pad1c[0x8];
    char *unk_24;
    u8 pad28[0x4];
    float unk_2C;
    u8 unk_30;
    u8 unk_31;
    u8 pad32[0x2];
    u16 unk_34;
    u8 pad36[0xD];
    u8 unk_43;
    u8 pad44[0x24];
    InitState *unk_68;
    u8 pad6c[0x2C];
    int unk_98;
    u8 pad9c[0x16];
    u16 unk_B2;
} InitObject;

/* Sets up a sheep or herd animal when it loads: picks its starting pose and speeds, and removes it if its save flags say it has already been dealt with (PAL: 50 Hz timings). */
void herd_animal_init_pal(InitObject *object)
{
    InitState *state = object->unk_68;
    float position[4], value;
    int handle;
    unsigned short flag;
    int bits;
    state->unk_48 = FloatToInt(15.0f);
    state->unk_4A = FloatToInt(9.6f);
    state->unk_29 = 1;
    if (g_init_context.unk_C) {
        if (object->unk_18 < g_init_context.unk_28 && g_init_context.unk_0 == 1)
            return;
        if (object->unk_18 > g_init_context.unk_28 && g_init_context.unk_0 == 0)
            return;
        if (g_init_context.unk_C == 2) {
            if (object->unk_18 > g_init_context.unk_38 && g_init_context.unk_0 == 1)
                return;
            if (object->unk_18 < g_init_context.unk_38 && g_init_context.unk_0 == 2)
                return;
        }
    }
    handle = state->unk_404;
    if (handle != -1) {
        /* Entries are 0x100 bytes; the global holds their base address. */
        handle = g_moby_array + (handle << 8);
        if (((InitEntry *)handle)->unk_B0 != 255) {
            flag = ((InitEntry *)handle)->unk_B2;
            if (g_moby_spawn_state_flags_b.flags[(short)flag] ||
                ((bits = (u8)g_moby_nibble_table[((short)flag >> 1) + (g_current_map_index << 10)]),
                 (flag & 1) ? (bits >> 4) & 7 : bits & 7)) {
                unsigned short object_flag = object->unk_B2;
                bits = (u8)g_moby_nibble_table[((short)object_flag >> 1) + (g_current_map_index << 10)];
                if ((object_flag & 1) ? (bits >> 4) & 7 : bits & 7) {
                    moby_mark_spawned(object);
                    return;
                }
            }
        }
    }
    qcopy_nc((char *)state + 0x3E0, (char *)object + 0x10);
    moby_store_ground_height(object);
    state->unk_408 = object->unk_30;
    *(InitVector *)position = *(InitVector *)((char *)object + 0x10);
    value = coll_point_depth_in_volumes(position, state->unk_410, state->unk_418, state->unk_414, -1);
    if (value > 0)
        object->unk_30 = FloatToInt(value + 2.0f);
    state->unk_408 = state->unk_40A = object->unk_30;
    *(InitVector *)position = *(InitVector *)((char *)object + 0x10);
    value = coll_point_depth_in_volumes(position, state->unk_41C, state->unk_424, state->unk_420, -1);
    if (value > 0)
        state->unk_408 = FloatToInt(value + 2.0f);
    if (state->unk_428 == -1)
        path_l01_compute_segment_lengths(g_path_segment_list);
    state->unk_88 = 0;
    state->unk_6A = 0;
    state->unk_98 = -1;
    state->unk_10 = (char *)state + 0x50;
    state->unk_60 = 9;
    state->unk_62 = state->unk_61 = 12;
    state->unk_66 = 13;
    state->unk_67 = 10;
    state->unk_6C = 0.3f;
    state->unk_70 = 0.14000001f;
    state->unk_78 = 0.012f;
    state->unk_7C = state->unk_74 = 0.006f;
    state->unk_84 = state->unk_80 = 0.8f;
    state->unk_8C = 0.4f;
    state->unk_BE = state->unk_BC = 2;
    state->unk_BF = state->unk_BD = 8;
    state->unk_C2 = 4;
    state->unk_C3 = 14;
    state->unk_A8 = 0.1f;
    state->unk_AC = 0.3f;
    state->unk_F8 = 0;
    state->unk_28 = 1;
    state->unk_30 = 0.2f;
    state->unk_C6 = 0;
    state->unk_C4 = 0;
    state->unk_430 = 0;
    if (state->unk_42C != -1)
        state->unk_15C = state->unk_42C;
    else
        state->unk_15C = state->unk_428;
    state->unk_150 = 0.0872664749622345f;
    state->unk_120 = 0.7f;
    state->unk_130 = 0.7853982448577881f;
    qcopy((char *)state + 0x3F0, (char *)object + 0x10);
    state->unk_450 = 0;
    switch (state->unk_40C) {
    case 0:
        object->unk_18 = state->unk_434;
        qcopy_nc((char *)state + 0x3E0, (char *)object + 0x10);
        qzero_nc((char *)state + 0x1C0);
        if (object->unk_43 != 11)
            anim_start_blended(object, 11, 0, 2);
        moby_set_state(object, 1, -1);
        object->unk_31 = 0;
        object->unk_98 = 0;
        object->unk_34 = (object->unk_34 & 0xEFFF) | 1;
        break;
    case 1:
    case 3:
        object->unk_18 = state->unk_434;
        qcopy_nc((char *)state + 0x3E0, (char *)object + 0x10);
        qzero_nc((char *)state + 0x1C0);
        if (object->unk_43 != (func_001163B0() & 1))
            anim_start_blended(object, func_001163B0() & 1, 0, 2);
        moby_set_state(object, 6, -1);
        object->unk_31 = 1;
        object->unk_34 = (object->unk_34 | 0x1000) & 0xFFFE;
        break;
    case 2:
        qzero_nc((char *)state + 0x1C0);
        FastVecAdd((char *)object + 0x10, (char *)object + 0x10, (char *)state + 0xD0);
        qcopy_nc((char *)state + 0x3E0, (char *)object + 0x10);
        if (object->unk_43 != 14)
            anim_start_blended(object, 14, 0, 2);
        object->unk_2C = *(float *)(object->unk_24 + 0x24) * 0.5f;
        object->unk_31 = 1;
        object->unk_34 = (object->unk_34 | 0x1000) & 0xFFFE;
        moby_set_state(object, 4, -1);
        break;
    }
}
