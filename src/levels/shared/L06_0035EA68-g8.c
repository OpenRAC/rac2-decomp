#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
extern char D_L06_001AF6A0[], D_L06_001AF6E0[];
typedef struct {
    char x[10];
} Sequence;
extern Sequence D_L06_001AF700;
extern int g_current_map_index;
extern u8 D_0018C0D4 NOT_SDA;
extern float D_L06_001AF620 __attribute__((sda));
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
extern void gfx_l06_draw_ribbon_effect(void);
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
extern void gfx_draw_ripple_grid(void);

/* Updates moby class 1067, a flowing ribbon of glowing strips. It picks a random order for the strips, plays a hum, and starts drawing the ribbon when the player is near. */
void ribbon_effect_update(char *obj) {
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
        moby_mark_spawned(obj);
    }
    switch (moby->state) {
    case 0: {
        int i, j, k;
        float sphere_radius;
        if (g_current_map_index == 10 && D_0018C0D4 == 1) {
            moby_mark_spawned(obj);
            break;
        }
        buffer.seq = D_L06_001AF700;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < math_random_int_below(9); j++) {
                u8 tmp = buffer.seq.x[j + 1];
                buffer.seq.x[j + 1] = buffer.seq.x[j];
                buffer.seq.x[j] = tmp;
            }
        }
        for (k = 0; k < data->count; k++)
            data->order[k] = buffer.seq.x[k];
        sphere_radius = FastAddRotations(moby->angle, 1.5707964897155762f);
        moby->mode = 0x60;
        moby->state = 1;
        moby->angle = sphere_radius;
        data->effect = -1;
        data->timer = FloatToInt(D_L06_001AF620 * 60.0f);
        moby->flags |= 0x41;
        break;
    }
    case 1: {
        float sphere_radius, half_height;
        float sphere[4];
        sphere_radius = data->radius * 0.5f;
        half_height = (float)data->count * data->step * 0.5f;
        *(Quad *)sphere = *(Quad *)(obj + 0x10);
        sphere[2] += half_height;
        sphere[3] = square_root(half_height * half_height + sphere_radius * sphere_radius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f) {
            if ((float)math_fast_helper_a(sphere, 80.0f) >= 0.0f)
                gfx_add_draw_callback_third(gfx_l06_draw_ribbon_effect, obj);
        }
        if (!snd_is_voice_playing_for_owner(obj, data->effect))
            data->effect = PlayMobySound(0, 4, obj);
        break;
    }
    case 2: {
        int i;
        float sphere_radius, half_height;
        math_fast_float_d(&data->timer);
        i = data->effect;
        if (i != -1) {
            Effect *sound_effect = (Effect *)(g_sound_state + i * 0x70);
            if (sound_effect->owner == obj && sound_effect->active)
                snd_stop_voice(i);
        }
        data->effect = -1;
        sphere_radius = data->radius * 0.5f;
        half_height = (float)data->count * data->step * 0.5f;
        buffer.q = *(Quad *)(obj + 0x10);
        buffer.f[2] += half_height;
        buffer.f[3] = square_root(half_height * half_height + sphere_radius * sphere_radius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f &&
            (float)math_fast_helper_a(&buffer, 80.0f) >= 0.0f)
            gfx_add_draw_callback_third(gfx_l06_draw_ribbon_effect, obj);
        break;
    }
    }
}

/* Updates moby class 2208, another flowing ribbon of glowing strips. It works like the first one but uses its own settings and drawing. */
void ribbon_effect_update_variant(char *obj) {
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
        moby_mark_spawned(obj);
    }
    switch (moby->state) {
    case 0: {
        int i, j, k;
        float sphere_radius;
        if (g_current_map_index == 10 && D_0018C0D4 == 1) {
            moby_mark_spawned(obj);
            break;
        }
        buffer.seq = D_L06_001B0000;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < math_random_int_below(9); j++) {
                u8 tmp = buffer.seq.x[j + 1];
                buffer.seq.x[j + 1] = buffer.seq.x[j];
                buffer.seq.x[j] = tmp;
            }
        }
        for (k = 0; k < data->count; k++)
            data->order[k] = buffer.seq.x[k];
        sphere_radius = FastAddRotations(moby->angle, 1.5707964897155762f);
        moby->mode = 0xFF;
        moby->state = 1;
        moby->angle = sphere_radius;
        data->effect = -1;
        data->timer = FloatToInt(D_L06_001AFF20 * 60.0f);
        moby->flags |= 0x41;
        break;
    }
    case 1: {
        float sphere_radius, half_height;
        float sphere[4];
        sphere_radius = data->radius * 0.5f;
        half_height = (float)data->count * data->step * 0.5f;
        *(Quad *)sphere = *(Quad *)(obj + 0x10);
        sphere[2] += half_height;
        sphere[3] = square_root(half_height * half_height + sphere_radius * sphere_radius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f) {
            if ((float)math_fast_helper_a(sphere, 80.0f) >= 0.0f)
                gfx_add_draw_callback_third(gfx_draw_ripple_grid, obj);
        }
        if (!snd_is_voice_playing_for_owner(obj, data->effect))
            data->effect = PlayMobySound(0, 4, obj);
        break;
    }
    case 2: {
        int i;
        float sphere_radius, half_height;
        math_fast_float_d(&data->timer);
        i = data->effect;
        if (i != -1) {
            Effect *sound_effect = (Effect *)(g_sound_state + i * 0x70);
            if (sound_effect->owner == obj && sound_effect->active)
                snd_stop_voice(i);
        }
        data->effect = -1;
        sphere_radius = data->radius * 0.5f;
        half_height = (float)data->count * data->step * 0.5f;
        buffer.q = *(Quad *)(obj + 0x10);
        buffer.f[2] += half_height;
        buffer.f[3] = square_root(half_height * half_height + sphere_radius * sphere_radius);
        if (fast_vec_dist(obj + 0x10, D_L06_001B9840) < 80.0f &&
            (float)math_fast_helper_a(&buffer, 80.0f) >= 0.0f)
            gfx_add_draw_callback_third(gfx_draw_ripple_grid, obj);
        break;
    }
    }
}
