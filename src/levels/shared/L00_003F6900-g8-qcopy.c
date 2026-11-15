#include "names.h"
typedef int EffectWord128 __attribute__((mode(TI)));
typedef union { EffectWord128 word; float xyzw[4]; } EffectVector;
typedef struct {
    EffectVector position;
    short lifetime, active;
    float inverseLifetime, phase, angularSpeed;
    float u0, v0, u1, v1;
    int reserved;
    float angle, scale;
    int tail;
} EffectRecord64;
extern char *func_L00_0032A088(int, int);
extern char *func_L00_0032A0B8(int, int);
extern int func_002A7820(int, int);
extern float func_00283CE0(int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int D_L00_001B09C4 __attribute__((sda));
extern int D_L00_001B09C8 __attribute__((sda));
extern float D_L00_001B09CC __attribute__((sda));
extern float D_L00_001B09D0 __attribute__((sda));
extern float D_L00_001B09D4 __attribute__((sda));
extern float D_L00_001B09D8 __attribute__((sda));
extern float D_L00_001B09DC __attribute__((sda));
extern float D_L00_001B09E0 __attribute__((sda));
extern float D_L00_001B09F4 __attribute__((sda));
extern float D_L00_001B09F8 __attribute__((sda));
extern float D_L00_001B09FC __attribute__((sda));
extern float D_L00_001B0A00 __attribute__((sda));

/* Adds a new spark to the bolt's pool of 120 sparks at the given position, with random life,
   spin and size. Does nothing if all slots are in use. */
void func_L00_003F6900(char *object, EffectVector *position) {
    char *state = *(char **)(object + 0x68);
    char *base = GetSlotBody(0xC04 /* Vaporizer */, *(short *)(state + 0x1A));
    EffectRecord64 *record;
    int i;
    base += *(int *)(GetSlotHeader(0xC04 /* Vaporizer */, *(short *)(state + 0x1A)) + 4);
    record = (EffectRecord64 *)base;
    for (i = 0; i < 120; i++, record++) {
        if (record->active == 0) {
            record->active = 1;
            record->position.word = position->word;
            record->lifetime = RandomIntRange(D_L00_001B09C4, D_L00_001B09C8);
            record->inverseLifetime = 1.0f / IntToFloat(record->lifetime);
            record->phase = RandomAngle();
            record->angularSpeed = RandomSignedFloatRange(D_L00_001B09CC, D_L00_001B09D0) * 0.017453294f;
            record->u0 = RandomFloatRange(D_L00_001B09D4, D_L00_001B09D8);
            record->v0 = RandomFloatRange(D_L00_001B09DC, D_L00_001B09E0);
            record->u1 = RandomFloatRange(D_L00_001B09D4, D_L00_001B09D8);
            record->v1 = RandomFloatRange(D_L00_001B09DC, D_L00_001B09E0);
            record->reserved = 0;
            record->angle = RandomFloatRange(D_L00_001B09F4, D_L00_001B09F8) * 0.017453294f;
            record->scale = RandomFloatRange(D_L00_001B09FC, D_L00_001B0A00);
            break;
        }
    }
}
