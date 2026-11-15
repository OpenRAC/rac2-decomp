#include "common.h"

extern int FloatToInt(float);
extern void moby_store_ground_height(void *);
extern void moby_mark_spawned(void *);
extern float coll_point_depth_in_volumes(void *, int, int, int, int);
extern void path_l01_compute_segment_lengths(void *);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int func_001163B0(void);
extern void FastVecAdd(void *, void *, void *);
extern int g_current_map_index __attribute__((sda));
extern char D_0019B4A8[];

typedef int InitVector __attribute__((mode(TI)));
typedef struct {
    int f0;
    char pad4[8];
    int fC;
    char pad10[0x18];
    float f28;
    char pad2C[12];
    float f38;
} InitContext;
extern InitContext D_L08_001CA080;
typedef struct {
    u8 pad0[0x464];
    u8 flags[0];
} InitFlags;
extern InitFlags D_L08_0021EAF0;
typedef struct {
    u8 pad0[0xB0];
    u8 fB0;
    u8 padB1;
    u16 fB2;
    u8 tail[0x4C];
} InitEntry;
extern u32 D_L08_001B29DC __attribute__((sda));
extern void *D_L08_001FE7BC __attribute__((section(".data")));

typedef struct {
    u8 pad0[0x10];
    void *f10;
    u8 pad14[0x14];
    u8 f28;
    u8 f29;
    u8 pad2a[0x6];
    float f30;
    u8 pad34[0x14];
    u8 f48;
    u8 pad49[0x1];
    u8 f4A;
    u8 pad4b[0x15];
    u8 f60;
    u8 f61;
    u8 f62;
    u8 pad63[0x3];
    u8 f66;
    u8 f67;
    u8 pad68[0x2];
    u8 f6A;
    u8 pad6b[0x1];
    float f6C;
    float f70;
    float f74;
    float f78;
    float f7C;
    float f80;
    float f84;
    u16 f88;
    u8 pad8a[0x2];
    float f8C;
    u8 pad90[0x8];
    int f98;
    u8 pad9c[0xC];
    float fA8;
    float fAC;
    u8 padb0[0xC];
    u8 fBC;
    u8 fBD;
    u8 fBE;
    u8 fBF;
    u8 padc0[0x2];
    u8 fC2;
    u8 fC3;
    u8 fC4;
    u8 padc5[0x1];
    u8 fC6;
    u8 padc7[0x31];
    float fF8;
    u8 padfc[0x24];
    float f120;
    u8 pad124[0xC];
    float f130;
    u8 pad134[0x1C];
    float f150;
    u8 pad154[0x8];
    int f15C;
    u8 pad160[0x2A4];
    int f404;
    u16 f408;
    u16 f40A;
    u8 f40C;
    u8 pad40d[0x3];
    int f410;
    int f414;
    int f418;
    int f41C;
    int f420;
    int f424;
    int f428;
    int f42C;
    int f430;
    float f434;
    u8 pad438[0x18];
    int f450;
} InitState;
typedef struct {
    u8 pad0[0x18];
    float f18;
    u8 pad1c[0x8];
    char *f24;
    u8 pad28[0x4];
    float f2C;
    u8 f30;
    u8 f31;
    u8 pad32[0x2];
    u16 f34;
    u8 pad36[0xD];
    u8 f43;
    u8 pad44[0x24];
    InitState *f68;
    u8 pad6c[0x2C];
    int f98;
    u8 pad9c[0x16];
    u16 fB2;
} InitObject;

/* Sets up a sheep or herd animal when it loads: picks its starting pose and speeds, and removes it if its save flags say it has already been dealt with. */
void herd_animal_init(InitObject *object)
{
    InitState *vars = object->f68;
    float position[4], depth;
    int linked_entry;
    unsigned short linked_flag;
    int flag_bits;
    vars->f48 = FloatToInt(15.0f);
    vars->f4A = FloatToInt(9.6f);
    vars->f29 = 1;
    if (D_L08_001CA080.fC) {
        if (object->f18 < D_L08_001CA080.f28 && D_L08_001CA080.f0 == 1)
            return;
        if (object->f18 > D_L08_001CA080.f28 && D_L08_001CA080.f0 == 0)
            return;
        if (D_L08_001CA080.fC == 2) {
            if (object->f18 > D_L08_001CA080.f38 && D_L08_001CA080.f0 == 1)
                return;
            if (object->f18 < D_L08_001CA080.f38 && D_L08_001CA080.f0 == 2)
                return;
        }
    }
    linked_entry = vars->f404;
    if (linked_entry != -1) {
        /* Entries are 0x100 bytes; the global holds their base address. */
        linked_entry = D_L08_001B29DC + (linked_entry << 8);
        if (((InitEntry *)linked_entry)->fB0 != 255) {
            linked_flag = ((InitEntry *)linked_entry)->fB2;
            if (D_L08_0021EAF0.flags[(short)linked_flag] ||
                ((flag_bits = (u8)D_0019B4A8[((short)linked_flag >> 1) + (g_current_map_index << 10)]),
                 (linked_flag & 1) ? (flag_bits >> 4) & 7 : flag_bits & 7)) {
                unsigned short saved_flag = object->fB2;
                flag_bits = (u8)D_0019B4A8[((short)saved_flag >> 1) + (g_current_map_index << 10)];
                if ((saved_flag & 1) ? (flag_bits >> 4) & 7 : flag_bits & 7) {
                    moby_mark_spawned(object);
                    return;
                }
            }
        }
    }
    qcopy_nc((char *)vars + 0x3E0, (char *)object + 0x10);
    moby_store_ground_height(object);
    vars->f408 = object->f30;
    *(InitVector *)position = *(InitVector *)((char *)object + 0x10);
    depth = coll_point_depth_in_volumes(position, vars->f410, vars->f418, vars->f414, -1);
    if (depth > 0)
        object->f30 = FloatToInt(depth + 2.0f);
    vars->f408 = vars->f40A = object->f30;
    *(InitVector *)position = *(InitVector *)((char *)object + 0x10);
    depth = coll_point_depth_in_volumes(position, vars->f41C, vars->f424, vars->f420, -1);
    if (depth > 0)
        vars->f408 = FloatToInt(depth + 2.0f);
    if (vars->f428 == -1)
        path_l01_compute_segment_lengths(D_L08_001FE7BC);
    vars->f88 = 0;
    vars->f6A = 0;
    vars->f98 = -1;
    vars->f10 = (char *)vars + 0x50;
    vars->f60 = 9;
    vars->f62 = vars->f61 = 12;
    vars->f66 = 13;
    vars->f67 = 10;
    vars->f6C = 0.25f;
    vars->f70 = 0.11666667461395264f;
    vars->f78 = 0.008333333767950535f;
    vars->f7C = vars->f74 = 0.004166666883975267f;
    vars->f84 = vars->f80 = 0.8f;
    vars->f8C = 0.4f;
    vars->fBE = vars->fBC = 2;
    vars->fBF = vars->fBD = 8;
    vars->fC2 = 4;
    vars->fC3 = 14;
    vars->fA8 = 0.1f;
    vars->fAC = 0.3f;
    vars->fF8 = 0;
    vars->f28 = 1;
    vars->f30 = 0.2f;
    vars->fC6 = 0;
    vars->fC4 = 0;
    vars->f430 = 0;
    if (vars->f42C != -1)
        vars->f15C = vars->f42C;
    else
        vars->f15C = vars->f428;
    vars->f150 = 0.0872664749622345f;
    vars->f120 = 0.7f;
    vars->f130 = 0.7853982448577881f;
    qcopy((char *)vars + 0x3F0, (char *)object + 0x10);
    vars->f450 = 0;
    switch (vars->f40C) {
    case 0:
        object->f18 = vars->f434;
        qcopy_nc((char *)vars + 0x3E0, (char *)object + 0x10);
        qzero_nc((char *)vars + 0x1C0);
        if (object->f43 != 11)
            anim_start_blended(object, 11, 0, 2);
        moby_set_state(object, 1, -1);
        object->f31 = 0;
        object->f98 = 0;
        object->f34 = (object->f34 & 0xEFFF) | 1;
        break;
    case 1:
    case 3:
        object->f18 = vars->f434;
        qcopy_nc((char *)vars + 0x3E0, (char *)object + 0x10);
        qzero_nc((char *)vars + 0x1C0);
        if (object->f43 != (func_001163B0() & 1))
            anim_start_blended(object, func_001163B0() & 1, 0, 2);
        moby_set_state(object, 6, -1);
        object->f31 = 1;
        object->f34 = (object->f34 | 0x1000) & 0xFFFE;
        break;
    case 2:
        qzero_nc((char *)vars + 0x1C0);
        FastVecAdd((char *)object + 0x10, (char *)object + 0x10, (char *)vars + 0xD0);
        qcopy_nc((char *)vars + 0x3E0, (char *)object + 0x10);
        if (object->f43 != 14)
            anim_start_blended(object, 14, 0, 2);
        object->f2C = *(float *)(object->f24 + 0x24) * 0.5f;
        object->f31 = 1;
        object->f34 = (object->f34 | 0x1000) & 0xFFFE;
        moby_set_state(object, 4, -1);
        break;
    }
}
