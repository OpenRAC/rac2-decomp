#include "include_asm.h"

#include "common.h"
typedef struct {
    char prefix[24];
    unsigned char field_18, field_19;
    unsigned short id;
    char tail[20];
} EffectHitPacket;
typedef struct {
    char prefix[0x70];
    float scale;
    char tail[0x6C];
} EffectMaterialEntry;
typedef struct { int x, y, z; } EffectAngles;
typedef struct {
    char pad00[0x34];
    int timer;
    char pad38[0x4C - 0x38];
    float intensity;
    int f50;
    int f54;
    int f58;
    int light_index;
} EffectState;
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char phase;
    char pad21[0x68 - 0x21];
    EffectState *state;
    char pad6C[0xAA - 0x6C];
    unsigned short id;
    char padAC[0xB8 - 0xAC];
    int f_B8;
    char padBC[0xC0 - 0xBC];
    float f_C0[4];
} EffectObject;
typedef struct {
    unsigned char prefix[0x1C];
    unsigned char index;
} EffectMaterialSelector;
extern EffectAngles D_L00_001AFDA8;
extern EffectMaterialSelector D_00139568;
extern EffectMaterialEntry D_L00_00262570[];
extern int D_L00_001AFDA0 __attribute__((sda));
extern char *func_PAL_L00_003BEE68(EffectObject *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern void func_PAL_0032F0B8(void *, int, int);
extern void func_002AF580(void *, float, void *, float, float, float, void *,
                          void *, int, int, float, int, void *);
extern int func_L00_0037DD80(void *, void *);
extern void func_L00_0037DD18(void *, void *, int);
extern void func_PAL_L00_003BF548(void *, void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern void func_00282C88(void *);
extern void func_002C2210(void *, float, float, int, unsigned int, int, int,
                          void *, float, int);
extern void func_002FE8D8(void *, void *);
extern void func_PAL_L00_003C11A0(void *, void *, int, int);
extern void func_002FEE50(int);
extern void func_L00_0037E0C0(void *);
extern void func_00291450(int);
extern void func_0029F338(void *);
extern void func_PAL_L00_003BF7F8(void *);
extern void func_L00_003BCC10(void *);
extern void ref_L00_003BAC30_00(void *, EffectObject *);
extern void func_PAL_L00_003BF2F8(void *);

/* Updates motion and hits, then shrinks, emits particles and releases resources. */
void func_PAL_L01_003BA750(EffectObject *self)
{
    EffectAngles angles;
    char *hits[16];
    char vector[16];
    EffectHitPacket packet;
    int count;
    EffectState *state = self->state;
    char *result;
    int i;
    int handle;
    int material;
    EffectMaterialEntry *entry;
    float scale;
    float ratio;

    angles = D_L00_001AFDA8;
    switch (self->phase) {
    case 0:
    case 1:
        state->intensity += (0.6f - state->intensity) * 0.125f;
        result = func_PAL_L00_003BEE68(self);
        if (result) {
            qcopy(vector, state);
            func_00282F20(vector, vector, 0.040000003f);
            material = D_00139568.index;
            entry = D_L00_00262570 + material;
            scale = entry->scale;
            func_002A8C00(&packet, self, 0x210000, scale, vector);
            packet.field_18 = 1;
            packet.field_19 = 3;
            packet.id = self->id;
            func_002A8E20(result, &packet);
            func_PAL_0032F0B8(result, 0x3E, self->f_B8);
        }
        func_002AF580(self->position, 6.2831855f, self->f_C0, 6.2831855f, 15.0f, 0.0f,
                      &count, hits, 15, 0, 0.0f, 0, &angles);
        for (i = 0; i < count; i++) {
            if (state->f54 < 15 && func_L00_0037DD80(self, hits[i])) {
                func_L00_0037DD18(self, hits[i], 120);
                func_PAL_L00_003BF548(self, hits[i], 10);
                func_002E5CF8(0, 0, self);
            }
        }
        if (func_00282948(&state->timer)) {
            self->phase = 2;
            state->timer = 33;
        }
        break;
    case 2:
        func_PAL_L00_003BEE68(self);
        ratio = func_00283CE0(state->timer) / func_00283CE0(40);
        state->intensity = ratio * 0.5900000333786011f + 0.01f;
        self->position[0] += func_002A7878(-0.1f, 0.1f);
        self->position[1] += func_002A7878(-0.1f, 0.1f);
        self->position[2] += func_002A7878(-0.1f, 0.1f);
        func_00282C88(vector);
        func_002C2210(self->position, 0.15f, 1.5f, 50, 0x4FFF0000, 0, 2, vector, 0.002f, 1);
        func_002C2210(self->position, 0.125f, 1.25f, 50, 0x7FFFFFFF, 0, 2, vector, 0.002f, 1);
        if (func_00282948(&state->timer))
            self->phase = 3;
        break;
    case 3:
        if (state->f54 == 0 && state->f58 == 0) {
            func_002FE8D8(self->position, &packet);
            func_PAL_L00_003C11A0(self->position, &packet, 6, 0x72FF);
            func_PAL_L00_003C11A0(self->position, &packet, 6, 0xFF0000);
            func_002FEE50(state->f50);
            func_L00_0037E0C0(self);
            handle = state->light_index;
            D_L00_001AFDA0--;
            if (handle != -1)
                func_00291450(handle);
            func_0029F338(self);
            return;
        }
        break;
    }
    func_PAL_L00_003BF7F8(self);
    func_L00_003BCC10(self);
    ref_L00_003BAC30_00(func_PAL_L00_003BF2F8, self);
}
