#include "include_asm.h"

#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
typedef union { Q16_B0e5d8f83 q; float f[4]; } EffectVector;
typedef struct { EffectVector row[4]; } EffectMatrix4;
extern int GetFirstMobyInGroup(unsigned char **, int, int, int);
extern int GetNextMobyInGroup(unsigned char **, unsigned char *, int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, char *);
extern float ApproachValue(float *, float, float);
extern int FastDecTimer(short *);

/* Blend the nearby pressure-surface contact using a full64-byte inverse matrix. */
void racer_update_boost_pad_contact_pal(unsigned char *object, unsigned char *state) {
    EffectVector delta;
    EffectMatrix4 inverse;
    unsigned char *nearby;
    unsigned char *contact;
    int kind;
    float distance;
    if (*(int *)(state + 0x80) == -1) return;
    GetFirstMobyInGroup(&nearby, *(int *)(state + 0x80), 0, 0);
    while (nearby) {
        kind = *(short *)(nearby + 0xAA);
        if (kind == 0x474 || kind == 0xCEF) {
            FastVecSub(&delta, nearby + 0x10, object + 0x10);
            distance = FastVecDot(&delta, &delta);
            if (!(20.0f < distance)) {
                set_identity_matrix(&inverse);
                matrix_from_basis_rows(&inverse, nearby + 0xC0);
                transform_vector(&delta, &delta, &inverse);
                if (math_fabs(delta.f[0]) < 2.8f && math_fabs(delta.f[1]) < 1.25f && math_fabs(delta.f[2]) < 1.5f) {
                    contact = *(unsigned char **)(nearby + 0x68);
                    if (*(short *)(state + 0x140) == 0 && (*(unsigned char **)(state + 0x164))[0x20] != 3)
                        PlayMobySound(0, 0, (char *)nearby);
                    *(unsigned short *)(state + 0x140) = *(unsigned short *)contact;
                }
            }
        }
        GetNextMobyInGroup(&nearby, nearby, 0, 0);
    }
    if (*(short *)(state + 0x140) != 0) {
        *(short *)(state + 0x142) = 1;
        ApproachValue((float *)(state + 0x13C), 0.120000005f, 0.008f);
        if (*(short *)(state + 0x140)) FastDecTimer((short *)(state + 0x140));
    } else {
        *(short *)(state + 0x142) = 0;
        ApproachValue((float *)(state + 0x13C), 0.0f, 0.004f);
    }
}


/* func_PAL_L04_00406D90, the PAL copy of func_L04_004029D8: the same C, where the rates become
   per-50 Hz-frame values (0.3691667f to 0.443f, 0.0116667f to 0.014f, 0.0333333f to 0.04f), the
   timer's 60.0f becomes the scaled (x * 300.0f + 2.0f) * 0.16666667f, and func_002A05A8 becomes
   func_PAL_002A0F68. */
extern float IntToFloat(int);
extern char *g_route_path_table[];
extern void anim_sample_key_track(void *, void *, void *, void *, float, float);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *a0);
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int FloatToInt(float);
extern void *moby_spawn_at_parent_pose(unsigned char *a0, void *a1, float f12);

void racer_reset_for_race_pal(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float rank_step;
    unsigned char *route;
    vars[0xA2] = vars[0x9C];
    *(Q16_B0e5d8f83 *)(moby+0x10) = *(Q16_B0e5d8f83 *)(vars+0xB0);
    *(Q16_B0e5d8f83 *)(moby+0xF0) = *(Q16_B0e5d8f83 *)(vars+0xC0);
    vars[0xA0] = 0;
    rank_step = IntToFloat(vars[0xA2]-1);
    *(float *)(vars+0x134) = 0.44300002f - rank_step * 0.014f - (1.0f - (float)*(int *)(vars+0x1A8)*0.1f)*0.040000003f;
    *(int *)(vars+0x138)=0;
    *(int *)(vars+0x158)=0;
    *(int *)(vars+0x13C)=0;
    *(short *)(vars+0x142)=0;
    *(short *)(vars+0x140)=0;
    *(int *)(vars+0x160)=0;
    *(int *)(vars+0x24C)=0;
    if (*(int *)(vars+0x54)==-1) *(char **)(vars+0x110)=g_route_path_table[*(int *)(vars+0x50)];
    else *(char **)(vars+0x110)=g_route_path_table[*(int *)(vars+0x54)];
    *(float *)(vars+0xA8)=5.0f;
    *(float *)(vars+0x1F8)=1.0f;
    *(int *)(vars+0xAC)=0;
    *(int *)(vars+0x114)=0;
    *(int *)(vars+0x118)=0;
    *(int *)(vars+0x128)=0;
    *(int *)(vars+0x12C)=0;
    *(int *)(vars+0x130)=0;
    *(int *)(vars+0x244)=0;
    *(int *)(vars+0x1F4)=0;
    *(int *)(vars+0x144)=0;
    vars[0xA4]=0; vars[0xA5]=0; *(short *)(vars+0xA6)=0;
    *(int *)(vars+0x154)=0;
    *(int *)(vars+0x150)=0;
    *(int *)(vars+0x148)=0;
    *(int *)(vars+0x178)=0;
    *(int *)(vars+0x248)=0;
    *(int *)(vars+0x14C)=0;
    *(int *)(vars+0x15C)=0;
    vars[0xA1]=0;
    qzero(vars+0xD0); qzero(vars+0xE0); qzero(vars+0x100);
    route=*(unsigned char **)(vars+0x110);
    anim_sample_key_track(route,vars+0x114,vars+0x118,vars+0xF0,*(float *)(vars+0xA8),*(float *)(route+0x1C));
    *(float *)(vars+0x16C)=func_002A7878_range(-1.5f,1.5f);
    *(int *)(vars+0x174)=FloatToInt((func_002A7878_range(3.0f,6.0f)*300.0f + 2.0f) * 0.16666667f);
    *(int *)(vars+0x170)=0;
    *(int *)(moby+0x98)=*(int *)(*(unsigned char **)(moby+0x24)+0x10);
    *(unsigned short *)(moby+0x34)=(*(unsigned short *)(moby+0x34)&0xFFBE)|0x1400;
    if (!*(void **)(vars+0x8C)) {
        *(void **)(vars+0x8C)=moby_spawn_at_parent_pose(moby,(void *)MOBY_CLASS_ENEMY_HOVERBIKE_RACER,0.25f);
        if (!*(void **)(vars+0x8C)) goto done;
    }
    {
    unsigned char *child=*(unsigned char **)(vars+0x8C);
    *(unsigned short *)(child+0x34)&=0xFFBE;
    }
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(vars+0x8C)+0x10)=*(Q16_B0e5d8f83 *)(moby+0x10);
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(vars+0x8C)+0xF0)=*(Q16_B0e5d8f83 *)(moby+0xF0);
    (*(unsigned char **)(vars+0x8C))[0x30]=0;
    func_PAL_002A0F68(*(void **)(vars+0x8C));
    func_002A0F48(*(void **)(vars+0x8C));
done:
    *(short *)(vars+0x17E)=0; *(short *)(vars+0x17C)=-1;
    *(int *)(vars+0x180)=0; moby[0x20]=2;
    *(int *)(vars+0x120)=-1;
    *(int *)(vars+0x240)=*(int *)(vars+0x1C0)=*(int *)(vars+0x124)=
    *(int *)(vars+0x11C)=*(int *)(vars+0x1AC)=*(int *)(vars+0x1A0)=*(int *)(vars+0x19C)=0;
}
