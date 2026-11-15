/*
 * func_PAL_L02_003D3388, the PAL copy of func_L00_003C27A0: the same C at 50 Hz (rates scaled by 6/5), with a
 * saved Z at 0x1FB4 passed to func_002AEE70 where USA v1.01 passes -1.0f, and 7 for 8 in func_L00_00323448's call.
 */
#include "common.h"

typedef int Rac2TI128 __attribute__((mode(TI)));

typedef struct Vec_L00_003C27A0 {
    Rac2TI128 v;
} Vec_L00_003C27A0;

typedef struct State_L00_003C27A0 {
    f32 home[4];        /* 0x00 */
    s32 group;          /* 0x10 */
    s32 group_b;        /* 0x14 */
    s32 x18;            /* 0x18 */
    f32 spin;           /* 0x1C */
    f32 x20;            /* 0x20 */
    f32 x24;            /* 0x24 */
    f32 x28;            /* 0x28 */
    f32 x2C;            /* 0x2C */
    f32 x30;            /* 0x30 */
    f32 x34;            /* 0x34 */
    f32 x38;            /* 0x38 */
    f32 x3C;            /* 0x3C */
    s32 gate;           /* 0x40 */
    f32 x44;            /* 0x44 */
    s32 spawn;          /* 0x48 */
    u8 *moby;           /* 0x4C */
    u8 pad50[0x58 - 0x50];
    f32 angle;          /* 0x58 */
    u8 pad5C[0x70 - 0x5C];
    u8 track[0x1FB0 - 0x70];    /* 0x70 */
    u8 *target;         /* 0x1FB0 */
    f32 base_z;         /* 0x1FB4 */
} State_L00_003C27A0;

extern s32 D_L00_001C9340 __attribute__((nosda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u16 **D_L00_001A9014;
extern u16 *D_L00_001FA920[];
extern u8 *D_L00_001B1E9C;
extern u8 *D_L00_001B251C;
extern u8 *D_L00_001B2514;
extern s16 D_L00_00226900[];
extern Vec_L00_003C27A0 D_L00_001AFEB0[] __attribute__((sda));
extern Vec_L00_003C27A0 D_L00_001AFEA0 __attribute__((sda));
extern s32 D_L00_001AFE98[2] __attribute__((sda));
extern s32 D_L00_001AFE90[2] __attribute__((sda));

extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(void *, void *);
extern void BuildObjectAttachmentTransforms(void *, void *, s32, s32, s32, s32, s32, s32);
extern void level_set_record_payload_by_key(void *, int, int, void *);
extern void vec_clear_128(void *);
extern float mat_fast_helper_a(float, float);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern void euler_rotation_basis(void *, void *);
extern float math_fabs(float);
extern void func_PAL_L00_0032C600(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern void func_PAL_L00_00323918(void *, s32, s32, s32, s32, s32, float);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern void part_spawn_random_spark_rays(char *, char *, float, float);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern s32 PlayMobySound(s32, s32, void *);
extern void moby_mark_spawned(void *);
extern s32 math_fast_helper_a(void *, float);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void moby_update_attached_transforms(void *, void *);

void func_PAL_L02_003D3388(u8 *self)
{
    State_L00_003C27A0 *st = *(State_L00_003C27A0 **)(self + 0x68);
    Vec_L00_003C27A0 cols[2];
    Vec_L00_003C27A0 here;
    u16 *p;
    u16 *q;
    u16 *r;
    u16 *t;
    u8 *e;
    u8 *f;
    u8 *rec;
    u8 *spot;
    u8 *moby;
    s32 id;
    s32 i;

    if (st->gate >= 0 && D_L00_001C9340 != st->gate)
        return;
    switch (self[0x20]) {
    case 0:
        if (*(long long *)&st->group == -1)
            break;
        {
            u8 stamp = 0xFF;
            self[0x30] = stamp;
        }
        if (st->spawn != 0) {
            moby = CreateMoby(0xE9B);
            st->moby = moby;
            if (moby != 0) {
                moby_init_child_from_parent(moby, self);
                *(u16 *)(st->moby + 0x34) |= 0x41;
                *(u16 *)(st->moby + 0x34) |= 0x5000;
            }
        }
        BuildObjectAttachmentTransforms(self, st->track, 100, st->group_b, st->group, st->x18, 7, 0);
        if (g_current_map_index[0] == 2 && st->group_b != -1) {
            p = D_L00_001FA920[st->group_b];
            do {
                id = *p & 0x7FFF;
                level_set_record_payload_by_key(st->track, 0, id, *(u8 **)(D_L00_001B1E9C + (id << 8) + 0x68) + 0x50);
            } while ((s16)*p++ >= 0);
        }
        if (st->moby != 0) {
            vec_clear_128(st->moby + 0xF0);
            st->target = 0;
            for (q = D_L00_001A9014[st->group];
                 q != 0 && ((s16)q[-1] >= 0 || q == D_L00_001A9014[st->group]); q++) {
                e = D_L00_001B251C + ((*q & 0x7FFF) << 6);
                if (e == 0)
                    break;
                rec = D_L00_001B2514 + ((*q & 0x7FFF) << 5);
                if (D_L00_00226900[rec[0x1D]] == 0xAB6) {
                    st->target = e;
                    break;
                }
            }
        }
        qcopy_nc(st->home, self + 0x10);
        st->home[3] = st->x44;
        st->base_z = *(f32 *)(self + 0x18);
        self[0x20] = 1;
        break;
    case 1:
        if (st->moby != 0 && (e = st->target) != 0) {
            qcopy_nc(st->moby + 0x10, e + 0x30);
            *(f32 *)(st->moby + 0xF8) = mat_fast_helper_a(*(f32 *)e, *(f32 *)(e + 4));
            if (part_find_owned_effect_slot(st->moby, 0x10000, 0) != 0) {
                *(f32 *)(st->moby + 0x2C) = *(f32 *)(*(u8 **)(st->moby + 0x24) + 0x24) * 1.35f;
                euler_rotation_basis(st->moby + 0xC0, st->moby + 0xF0);
                if (math_fabs(*(f32 *)(st->moby + 0xF8)) > 1.6f) {
                    qcopy_nc(&cols[0], D_L00_001AFEB0);
                    qcopy_nc(&cols[1], &D_L00_001AFEA0);
                } else {
                    qcopy_nc(&cols[0], &D_L00_001AFEA0);
                    qcopy_nc(&cols[1], D_L00_001AFEB0);
                }
                func_PAL_L00_0032C600(st->moby, cols, D_L00_001AFE98, D_L00_001AFE90, 0, 0, -1, 1, 0xFFFE, 0xFF, 0);
                func_PAL_L00_00323918(st->moby, 30, 50, 2, -1, math_random_int_range(3, 5), 0.0f);
                snd_play_from_class_bank(0, 0, st->moby, 0xE9B);
                here = *(Vec_L00_003C27A0 *)(self + 0x10);
                part_spawn_random_spark_rays((char *)st->moby, (char *)&here, 1.5f, 0.14000002f);
                func_PAL_L00_003FB330(st->moby + 0x10, 0, 25, 20, 20, 20, 45, 0, 0.85f, 20.0f, 1, 0, 0, 0);
                for (r = D_L00_001A9014[st->group];
                     r != 0 && ((s16)r[-1] >= 0 || r == D_L00_001A9014[st->group]); r++) {
                    spot = D_L00_001B2514 + ((*r & 0x7FFF) << 5);
                    if (spot == 0)
                        break;
                    spot[0x1C] = 0;
                }
                for (t = D_L00_001A9014[st->group];
                     t != 0 && ((s16)t[-1] >= 0 || t == D_L00_001A9014[st->group]); t++) {
                    f = D_L00_001B251C + ((*t & 0x7FFF) << 6);
                    if (f == 0)
                        break;
                    for (i = 0; i < 3; i++) {
                        qzero_nc(f);
                        f += 16;
                    }
                }
                PlayMobySound(0, 0, st->moby);
                moby_mark_spawned(st->moby);
                moby_mark_spawned(self);
                return;
            }
        }
        if (math_fast_helper_a(st, 500.0f) == -1)
            return;
        if (st->x34 > 0.0f)
            math_update_wrapped_angle_offset(self, &st->x20, &st->x24, st->x30, st->x34 * 0.0003490659f, st->base_z);
        if (st->x3C > 0.0f)
            moby_scale_owner_words_by_angles(self, &st->x28, &st->x2C, st->x38 * 0.017453294f, st->x3C * 0.0003490659f,
                          0.0069813184f);
        *(f32 *)(self + 0xF8) = FastAddRotations(*(f32 *)(self + 0xF8), st->spin * 0.0003490659f);
        st->angle = FastAddRotations(st->angle, st->spin * 0.0003490659f);
        moby_update_attached_transforms(self, st->track);
        break;
    }
}
