/* func_PAL_L00_003FAD60, the PAL copy of func_L00_003F6900: the same C, where scale func_002A7820(D_L00_001B09C4, D_L00_001B09C8). */
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

void func_PAL_L00_003FAD60(char *object, EffectVector *position) {
    char *state = *(char **)(object + 0x68);
    char *base = func_L00_0032A088(0xC04, *(short *)(state + 0x1A));
    EffectRecord64 *record;
    int i;
    base += *(int *)(func_L00_0032A0B8(0xC04, *(short *)(state + 0x1A)) + 4);
    record = (EffectRecord64 *)base;
    for (i = 0; i < 120; i++, record++) {
        if (record->active == 0) {
            record->active = 1;
            record->position.word = position->word;
            record->lifetime = (((int)(func_002A7820(D_L00_001B09C4, D_L00_001B09C8)) * 5 + 2) / 6);
            record->inverseLifetime = 1.0f / func_00283CE0(record->lifetime);
            record->phase = func_002A7940();
            record->angularSpeed = func_002A78D8(D_L00_001B09CC, D_L00_001B09D0) * 0.017453294f;
            record->u0 = func_002A7878(D_L00_001B09D4, D_L00_001B09D8);
            record->v0 = func_002A7878(D_L00_001B09DC, D_L00_001B09E0);
            record->u1 = func_002A7878(D_L00_001B09D4, D_L00_001B09D8);
            record->v1 = func_002A7878(D_L00_001B09DC, D_L00_001B09E0);
            record->reserved = 0;
            record->angle = func_002A7878(D_L00_001B09F4, D_L00_001B09F8) * 0.017453294f;
            record->scale = func_002A7878(D_L00_001B09FC, D_L00_001B0A00);
            break;
        }
    }
}
