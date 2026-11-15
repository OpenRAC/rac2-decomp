#include "common.h"

#ifndef RAC2_T_TI128_33F90
#define RAC2_T_TI128_33F90
typedef int TI128_33F90 __attribute__((mode(TI)));
#endif

extern void *func_002B9030(int);

extern int func_002A77E0(int);
extern int func_00283CF0(float);

extern void func_00282CF0(char *dst, char *first, char *second);

extern unsigned char *D_L00_001FE98C;

/* Allocates the 0x13 object, fills its flags and its two 16-byte copies, and runs the
   two bound helpers over the record at +0x20. */
typedef union { TI128_33F90 q; float f[4]; } EffectVector;
/* The observed header and three complete vectors form a known 64-byte prefix. */
typedef struct {
    u8 b0,b1,b2,b3;
    int word4;
    u8 b8,b9;
    u16 fieldA;
    int wordC;
    EffectVector position, difference, endpoint;
} EffectPrefix;

/* Spawns a short streak effect running between two points. */
void *func_L00_00333F90(EffectVector *position, EffectVector *a1)
{
    EffectPrefix *record = AllocParticle(0x13);
    EffectVector *endpoint;
    EffectVector *difference;
    int packed;
    if (record) {
        packed = (RandomIntBelow(6) * 6 + 0x40) | 0x78404000;
        record->word4 = packed;
        record->wordC = packed;
        record->b9 = FloatToInt(2.0f) + 0x20;
        record->b3 = 0x48;
        record->b1 = 3;
        record->b2 = *D_L00_001FE98C;
        qcopy(&record->position, position);
        endpoint = &record->endpoint;
        qcopy(endpoint, a1);
        difference = &record->difference;
        FastVecSub((char *)difference, (char *)position, (char *)endpoint);
        FastVecSub((char *)difference, (char *)difference, (char *)endpoint);
        endpoint->f[3] = 6.0f;
        record->position.f[3] = 0.09f;
        record->difference.f[3] = 0.5f;
    }
    return record;
}
