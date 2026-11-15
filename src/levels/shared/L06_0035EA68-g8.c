#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
extern char D_L06_001AF6A0[], D_L06_001AF6E0[];
typedef struct {
    char x[10];
} Sequence;
extern Sequence D_L06_001AF700;
extern int D_001A79F0;
extern u8 D_0018C0D4 NOT_SDA;
extern float D_L06_001AF620 __attribute__((sda));
extern char D_L06_001B9840[];
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    char *owner;
} Effect;
extern u8 D_00188660[];
extern void func_0026FEB8(char *, ...);
extern void func_0029F338(char *);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern int func_00283CF0(float);
extern float func_00282C10(float);
extern float func_00282E48(void *, void *);
extern int func_00283DB8(void *, float);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L06_003E57E8(void);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282948(void *);
extern void func_002E59F8(int);
typedef struct {
    float radius;
    int count;
    float step;
    int valid;
    u8 order[0x20];
    int effect;
    int timer;
} Data;

typedef struct {
    char pad0[0x20];
    u8 state;
    char pad21[0xF];
    u8 mode;
    char pad31[3];
    u16 flags;
    char pad36[0x32];
    Data *data;
    char pad6C[0x8C];
    float angle;
} Object;

extern char D_L06_001AFFA0[], D_L06_001AFFE0[];
extern Sequence D_L06_001B0000;
extern float D_L06_001AFF20 __attribute__((sda));
extern void func_L06_004009B8(void);

/* Updates moby class 1067, a flowing ribbon of glowing strips. It picks a random order for the strips, plays a hum, and starts drawing the ribbon when the player is near. */
void func_L06_003E5428(char *obj) {
    Object *moby = (Object *)obj;
    Data *data = moby->data;
    /* State 0's shuffle and state 2's sphere share their temporary storage. */
    union {
        Sequence seq;
        Quad q;
        float f[4];
    } buffer;
    if (data->valid == -1) {
        STUB_printf(D_L06_001AF6A0);
        STUB_printf(D_L06_001AF6E0, *(short *)(obj + 0xB2));
        MarkMobySpawned(obj);
    }
    switch (moby->state) {
    case 0: {
        int i, j, k;
        float sphereRadius;
        if (gCurrentMapIndex == 10 && D_0018C0D4 == 1) {
            MarkMobySpawned(obj);
            break;
        }
        buffer.seq = D_L06_001AF700;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < RandomIntBelow(9); j++) {
                u8 tmp = buffer.seq.x[j + 1];
                buffer.seq.x[j + 1] = buffer.seq.x[j];
                buffer.seq.x[j] = tmp;
            }
        }
        for (k = 0; k < data->count; k++)
            data->order[k] = buffer.seq.x[k];
        sphereRadius = FastAddRotations(moby->angle, 1.5707964897155762f);
        moby->mode = 0x60;
        moby->state = 1;
        moby->angle = sphereRadius;
        data->effect = -1;
        data->timer = FloatToInt(D_L06_001AF620 * 60.0f);
        moby->flags |= 0x41;
        break;
    }
    case 1: {
        float sphereRadius, halfHeight;
        float sphere[4];
        sphereRadius = data->radius * 0.5f;
        halfHeight = (float)data->count * data->step * 0.5f;
        *(Quad *)sphere = *(Quad *)(obj + 0x10);
        sphere[2] += halfHeight;
        sphere[3] = square_root(halfHeight * halfHeight + sphereRadius * sphereRadius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f) {
            if ((float)FastMathHelperA(sphere, 80.0f) >= 0.0f)
                AddDrawCallbackToList3(DrawRibbonEffect_L06, obj);
        }
        if (!IsVoicePlayingForOwner(obj, data->effect))
            data->effect = PlayMobySound(0, 4, obj);
        break;
    }
    case 2: {
        int i;
        float sphereRadius, halfHeight;
        FastFloatHelperD(&data->timer);
        i = data->effect;
        if (i != -1) {
            Effect *soundEffect = (Effect *)(gSoundState + i * 0x70);
            if (soundEffect->owner == obj && soundEffect->active)
                StopSoundVoice(i);
        }
        data->effect = -1;
        sphereRadius = data->radius * 0.5f;
        halfHeight = (float)data->count * data->step * 0.5f;
        buffer.q = *(Quad *)(obj + 0x10);
        buffer.f[2] += halfHeight;
        buffer.f[3] = square_root(halfHeight * halfHeight + sphereRadius * sphereRadius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f &&
            (float)FastMathHelperA(&buffer, 80.0f) >= 0.0f)
            AddDrawCallbackToList3(DrawRibbonEffect_L06, obj);
        break;
    }
    }
}

/* Updates moby class 2208, another flowing ribbon of glowing strips. It works like the first one but uses its own settings and drawing. */
void func_L06_004005F8(char *obj) {
    Object *moby = (Object *)obj;
    Data *data = moby->data;
    /* State 0's shuffle and state 2's sphere share their temporary storage. */
    union {
        Sequence seq;
        Quad q;
        float f[4];
    } buffer;
    if (data->valid == -1) {
        STUB_printf(D_L06_001AFFA0);
        STUB_printf(D_L06_001AFFE0, *(short *)(obj + 0xB2));
        MarkMobySpawned(obj);
    }
    switch (moby->state) {
    case 0: {
        int i, j, k;
        float sphereRadius;
        if (gCurrentMapIndex == 10 && D_0018C0D4 == 1) {
            MarkMobySpawned(obj);
            break;
        }
        buffer.seq = D_L06_001B0000;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < RandomIntBelow(9); j++) {
                u8 tmp = buffer.seq.x[j + 1];
                buffer.seq.x[j + 1] = buffer.seq.x[j];
                buffer.seq.x[j] = tmp;
            }
        }
        for (k = 0; k < data->count; k++)
            data->order[k] = buffer.seq.x[k];
        sphereRadius = FastAddRotations(moby->angle, 1.5707964897155762f);
        moby->mode = 0xFF;
        moby->state = 1;
        moby->angle = sphereRadius;
        data->effect = -1;
        data->timer = FloatToInt(D_L06_001AFF20 * 60.0f);
        moby->flags |= 0x41;
        break;
    }
    case 1: {
        float sphereRadius, halfHeight;
        float sphere[4];
        sphereRadius = data->radius * 0.5f;
        halfHeight = (float)data->count * data->step * 0.5f;
        *(Quad *)sphere = *(Quad *)(obj + 0x10);
        sphere[2] += halfHeight;
        sphere[3] = square_root(halfHeight * halfHeight + sphereRadius * sphereRadius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f) {
            if ((float)FastMathHelperA(sphere, 80.0f) >= 0.0f)
                AddDrawCallbackToList3(DrawRippleGrid, obj);
        }
        if (!IsVoicePlayingForOwner(obj, data->effect))
            data->effect = PlayMobySound(0, 4, obj);
        break;
    }
    case 2: {
        int i;
        float sphereRadius, halfHeight;
        FastFloatHelperD(&data->timer);
        i = data->effect;
        if (i != -1) {
            Effect *soundEffect = (Effect *)(gSoundState + i * 0x70);
            if (soundEffect->owner == obj && soundEffect->active)
                StopSoundVoice(i);
        }
        data->effect = -1;
        sphereRadius = data->radius * 0.5f;
        halfHeight = (float)data->count * data->step * 0.5f;
        buffer.q = *(Quad *)(obj + 0x10);
        buffer.f[2] += halfHeight;
        buffer.f[3] = square_root(halfHeight * halfHeight + sphereRadius * sphereRadius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f &&
            (float)FastMathHelperA(&buffer, 80.0f) >= 0.0f)
            AddDrawCallbackToList3(DrawRippleGrid, obj);
        break;
    }
    }
}
