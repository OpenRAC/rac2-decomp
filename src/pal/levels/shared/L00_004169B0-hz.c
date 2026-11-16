#include "names.h"
/* func_PAL_L00_004169B0, the PAL copy of func_L00_00411B30: the same C, where 0.033333335f becomes
   0.040000003f; func_L00_00412928 becomes func_PAL_L00_004177A8. */
#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;

#include "include_asm.h"

#ifndef RAC2_T_NODE16_F23626AD8
typedef struct Node16_F23626ad8 Node16_F23626ad8;
#endif

#ifndef RAC2_T_NODE104_F23626AD8
typedef struct Node104_F23626ad8 Node104_F23626ad8;
#endif

#ifndef RAC2_T_NODE24_F23626AD8
typedef struct Node24_F23626ad8 Node24_F23626ad8;
#endif

struct Node16_F23626ad8 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_F23626ad8 {
    unsigned char pad0[16];
    Node16_F23626ad8 *p16;
};

struct Node24_F23626ad8 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_F23626ad8 *p104;
};

#ifndef RAC2_T_OBJ_F23626AD8
typedef struct Obj_F23626ad8 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[16];
    Node24_F23626ad8 *f24;
} Obj_F23626ad8;
#endif

extern void cam_compute_view_direction(char *a0, void *a1, int a2);

extern void FastVecScale(void *a0, void *a1, float f12);

extern char g_tumbling_piece_records[];
extern char *moby_get_private_value_0(char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), IntToFloat(int);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern int math_fast_float_d(void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void part_emit_spark_particle_pairs_pal(void *, int, int);
/* Moves each of this object's 48 flying pieces toward its target. When a piece arrives it hits the target with damage and sparks, and the piece is freed (PAL: 50 Hz hit speed). */
void tumbling_pieces_update_pal(char *moby)
{
    Vector128 offset_vec[1];
    char hit_event[48];
    char *record, *active_record, *link_data, *current_pos, *start_pos;
    int i;
    float fraction, amount;
    for (i = 0; i < 48; i++) {
        record = g_tumbling_piece_records + i * 0xd0;
        if (*(char **)(record + 0xac) != moby) continue;
        current_pos = record + 0x20;
        qcopy(current_pos, record + 0x40);
        if (*(char **)(record + 0xb4)) {
            link_data = moby_get_private_value_0(*(char **)(record + 0xb4));
            if (link_data) {
                cam_compute_view_direction(*(char **)(record + 0xb4) + 0x10, offset_vec, 1);
                FastVecScale(offset_vec, offset_vec, *(float *)(link_data + 0x10));
                FastVecAdd(offset_vec, offset_vec, *(char **)(record + 0xb4) + 0x10);
                FastVecAdd(current_pos, offset_vec, current_pos);
            } else qcopy(current_pos, *(char **)(record + 0xb4) + 0x10);
        }
        if (*(int *)(record + 0xb8)) {
            *(float *)(record + 96) = FastAddRotations(*(float *)(record + 96), *(float *)(record + 108) * 100.0f);
            *(float *)(record + 100) = FastAddRotations(*(float *)(record + 100), *(float *)(record + 112) * 100.0f);
            *(float *)(record + 104) = FastAddRotations(*(float *)(record + 104), *(float *)(record + 116) * 100.0f);
            *(float *)(record + 132) = FastAddRotations(*(float *)(record + 132), *(float *)(record + 144) * 100.0f);
            *(float *)(record + 136) = FastAddRotations(*(float *)(record + 136), *(float *)(record + 148) * 100.0f);
            *(float *)(record + 140) = FastAddRotations(*(float *)(record + 140), *(float *)(record + 152) * 100.0f);
        } else {
            *(float *)(record + 96) = FastAddRotations(*(float *)(record + 96), *(float *)(record + 108));
            *(float *)(record + 100) = FastAddRotations(*(float *)(record + 100), *(float *)(record + 112));
            *(float *)(record + 104) = FastAddRotations(*(float *)(record + 104), *(float *)(record + 116));
            *(float *)(record + 132) = FastAddRotations(*(float *)(record + 132), *(float *)(record + 144));
            *(float *)(record + 136) = FastAddRotations(*(float *)(record + 136), *(float *)(record + 148));
            *(float *)(record + 140) = FastAddRotations(*(float *)(record + 140), *(float *)(record + 152));
        }
        *(float *)(record + 0) = math_fast_sin_or_cos_a(*(float *)(record + 96)) * *(float *)(record + 120);
        *(float *)(record + 4) = math_fast_sin_or_cos_b(*(float *)(record + 100)) * *(float *)(record + 124);
        *(float *)(record + 8) = -math_fast_sin_or_cos_b(*(float *)(record + 104)) * *(float *)(record + 128);
        *(float *)(record + 16) = math_fast_sin_or_cos_a(*(float *)(record + 132)) * *(float *)(record + 156);
        *(float *)(record + 20) = math_fast_sin_or_cos_b(*(float *)(record + 136)) * *(float *)(record + 160);
        *(float *)(record + 24) = -math_fast_sin_or_cos_b(*(float *)(record + 140)) * *(float *)(record + 164);
        qcopy(record + 0x30, record + 0x50);
        if (*(char **)(record + 0xb0)) {
            link_data = moby_get_private_value_0(*(char **)(record + 0xb0));
            if (link_data) {
                cam_compute_view_direction(*(char **)(record + 0xb0) + 0x10, offset_vec, 1);
                FastVecScale(offset_vec, offset_vec, *(float *)(link_data + 0x10));
                FastVecAdd(offset_vec, offset_vec, *(char **)(record + 0xb0) + 0x10);
                FastVecAdd(record + 0x30, offset_vec, record + 0x30);
            } else qcopy(record + 0x30, *(char **)(record + 0xb0) + 0x10);
        }
        current_pos = record + 0x30;
        active_record = record;
        fraction = IntToFloat(*(int *)(active_record + 0xb8));
        fraction /= IntToFloat(*(int *)(active_record + 0xbc));
        start_pos = active_record + 0x20;
        lerp_vector(current_pos, start_pos, current_pos, 1.0f - fraction);
        if (!math_fast_float_d(active_record + 0xb8)) continue;
        if (*(int *)(*(char **)(active_record + 0xb0) + 0x98) && !*(int *)(active_record + 0xc0) && *(int *)(active_record + 0xc4)) {
            FastVecSub(offset_vec, current_pos, start_pos);
            vec_scale_to_length(offset_vec, offset_vec, 0.040000003f);
            amount = *(float *)(active_record + 0xc8);
            *(int *)(moby + 0xb8) = *(int *)(*(char **)(active_record + 0xcc) + 0x20);
            make_hit_descriptor(hit_event, moby, 0x210000, offset_vec, amount);
            hit_event[0x18] = 5;
            hit_event[0x19] = 3;
            *(short *)(hit_event + 0x1a) = *(short *)(moby + 0xaa);
            QueueMobyImpact(*(char **)(active_record + 0xb0), hit_event);
            *(int *)(active_record + 0xc0) = 1;
            part_emit_spark_particle_pairs_pal(current_pos, 10, 1);
        }
        if (math_fast_float_d(active_record + 0xa8)) *(int *)(active_record + 0xac) = 0;
    }
}
