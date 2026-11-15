#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct {
    char x[10];
} Sequence;
extern Sequence D_L06_001AF700;
extern int g_current_map_index;
extern u8 D_0018C0D4 NOT_SDA;
extern char D_L06_001B9840[];
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    char *owner;
} Effect;
extern u8 g_sound_state[];
extern void STUB_printf(char *, ...);
extern void moby_mark_spawned(char *);
extern int math_random_int_below(int);
extern float FastAddRotations(float, float);
extern int FloatToInt(float);
extern float square_root(float);
extern float fast_vec_dist(void *, void *);
extern int math_fast_helper_a(void *, float);
extern void gfx_add_draw_callback_third(void *, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern int math_fast_float_d(void *);
extern void snd_stop_voice(int);
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
extern void func_PAL_L06_004046D8(void);

extern char D_L06_001AF6A0[], D_L06_001AF6E0[];
extern float D_L06_001AF620 __attribute__((sda));

void func_PAL_L06_004042F8(char *obj) {
    Object *m = (Object *)obj;
    Data *data = m->data;
    /* State 0's shuffle and state 2's sphere share their temporary storage. */
    union {
        Sequence seq;
        Quad q;
        float f[4];
    } buffer;
    if (data->valid == -1) {
        STUB_printf(D_L06_001AF6A0);
        STUB_printf(D_L06_001AF6E0, *(short *)(obj + 0xB2));
        moby_mark_spawned(obj);
    }
    switch (m->state) {
    case 0: {
        int i, j, k;
        float r;
        if (g_current_map_index == 10 && D_0018C0D4 == 1) {
            moby_mark_spawned(obj);
            break;
        }
        buffer.seq = D_L06_001AF700;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < math_random_int_below(9); j++) {
                u8 b = buffer.seq.x[j + 1];
                buffer.seq.x[j + 1] = buffer.seq.x[j];
                buffer.seq.x[j] = b;
            }
        }
        for (k = 0; k < data->count; k++)
            data->order[k] = buffer.seq.x[k];
        r = FastAddRotations(m->angle, 1.5707964897155762f);
        m->mode = 0xFF;
        m->state = 1;
        m->angle = r;
        data->effect = -1;
        data->timer = ((s32)(FloatToInt(D_L06_001AF620 * 60.0f)) * 5 + 2) / 6;
        m->flags |= 0x41;
        break;
    }
    case 1: {
        float r, h;
        float sphere[4];
        r = data->radius * 0.5f;
        h = (float)data->count * data->step * 0.5f;
        *(Quad *)sphere = *(Quad *)(obj + 0x10);
        sphere[2] += h;
        sphere[3] = square_root(h * h + r * r);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f) {
            if ((float)math_fast_helper_a(sphere, 80.0f) >= 0.0f)
                gfx_add_draw_callback_third(func_PAL_L06_004046D8, obj);
        }
        if (!snd_is_voice_playing_for_owner(obj, data->effect))
            data->effect = PlayMobySound(0, 4, obj);
        break;
    }
    case 2: {
        int i;
        float r, h;
        math_fast_float_d(&data->timer);
        i = data->effect;
        if (i != -1) {
            Effect *e = (Effect *)(g_sound_state + i * 0x70);
            if (e->owner == obj && e->active)
                snd_stop_voice(i);
        }
        data->effect = -1;
        r = data->radius * 0.5f;
        h = (float)data->count * data->step * 0.5f;
        buffer.q = *(Quad *)(obj + 0x10);
        buffer.f[2] += h;
        buffer.f[3] = square_root(h * h + r * r);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f &&
            (float)math_fast_helper_a(&buffer, 80.0f) >= 0.0f)
            gfx_add_draw_callback_third(func_PAL_L06_004046D8, obj);
        break;
    }
    }
}


