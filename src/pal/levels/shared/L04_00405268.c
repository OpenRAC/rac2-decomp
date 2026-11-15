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
void func_PAL_L04_00406B68(unsigned char *object, unsigned char *state) {
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

void func_PAL_L04_00406D90(unsigned char *m) {
    unsigned char *s = *(unsigned char **)(m + 0x68);
    float f;
    unsigned char *o;
    s[0xA2] = s[0x9C];
    *(Q16_B0e5d8f83 *)(m+0x10) = *(Q16_B0e5d8f83 *)(s+0xB0);
    *(Q16_B0e5d8f83 *)(m+0xF0) = *(Q16_B0e5d8f83 *)(s+0xC0);
    s[0xA0] = 0;
    f = IntToFloat(s[0xA2]-1);
    *(float *)(s+0x134) = 0.44300002f - f * 0.014f - (1.0f - (float)*(int *)(s+0x1A8)*0.1f)*0.040000003f;
    *(int *)(s+0x138)=0;
    *(int *)(s+0x158)=0;
    *(int *)(s+0x13C)=0;
    *(short *)(s+0x142)=0;
    *(short *)(s+0x140)=0;
    *(int *)(s+0x160)=0;
    *(int *)(s+0x24C)=0;
    if (*(int *)(s+0x54)==-1) *(char **)(s+0x110)=g_route_path_table[*(int *)(s+0x50)];
    else *(char **)(s+0x110)=g_route_path_table[*(int *)(s+0x54)];
    *(float *)(s+0xA8)=5.0f;
    *(float *)(s+0x1F8)=1.0f;
    *(int *)(s+0xAC)=0;
    *(int *)(s+0x114)=0;
    *(int *)(s+0x118)=0;
    *(int *)(s+0x128)=0;
    *(int *)(s+0x12C)=0;
    *(int *)(s+0x130)=0;
    *(int *)(s+0x244)=0;
    *(int *)(s+0x1F4)=0;
    *(int *)(s+0x144)=0;
    s[0xA4]=0; s[0xA5]=0; *(short *)(s+0xA6)=0;
    *(int *)(s+0x154)=0;
    *(int *)(s+0x150)=0;
    *(int *)(s+0x148)=0;
    *(int *)(s+0x178)=0;
    *(int *)(s+0x248)=0;
    *(int *)(s+0x14C)=0;
    *(int *)(s+0x15C)=0;
    s[0xA1]=0;
    qzero(s+0xD0); qzero(s+0xE0); qzero(s+0x100);
    o=*(unsigned char **)(s+0x110);
    anim_sample_key_track(o,s+0x114,s+0x118,s+0xF0,*(float *)(s+0xA8),*(float *)(o+0x1C));
    *(float *)(s+0x16C)=func_002A7878_range(-1.5f,1.5f);
    *(int *)(s+0x174)=FloatToInt((func_002A7878_range(3.0f,6.0f)*300.0f + 2.0f) * 0.16666667f);
    *(int *)(s+0x170)=0;
    *(int *)(m+0x98)=*(int *)(*(unsigned char **)(m+0x24)+0x10);
    *(unsigned short *)(m+0x34)=(*(unsigned short *)(m+0x34)&0xFFBE)|0x1400;
    if (!*(void **)(s+0x8C)) {
        *(void **)(s+0x8C)=moby_spawn_at_parent_pose(m,(void *)0x8EF,0.25f);
        if (!*(void **)(s+0x8C)) goto done;
    }
    {
    unsigned char *child=*(unsigned char **)(s+0x8C);
    *(unsigned short *)(child+0x34)&=0xFFBE;
    }
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0x10)=*(Q16_B0e5d8f83 *)(m+0x10);
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0xF0)=*(Q16_B0e5d8f83 *)(m+0xF0);
    (*(unsigned char **)(s+0x8C))[0x30]=0;
    func_PAL_002A0F68(*(void **)(s+0x8C));
    func_002A0F48(*(void **)(s+0x8C));
done:
    *(short *)(s+0x17E)=0; *(short *)(s+0x17C)=-1;
    *(int *)(s+0x180)=0; m[0x20]=2;
    *(int *)(s+0x120)=-1;
    *(int *)(s+0x240)=*(int *)(s+0x1C0)=*(int *)(s+0x124)=
    *(int *)(s+0x11C)=*(int *)(s+0x1AC)=*(int *)(s+0x1A0)=*(int *)(s+0x19C)=0;
}
