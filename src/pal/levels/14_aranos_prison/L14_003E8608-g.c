#include "names.h"
/* func_PAL_L14_003E8608, the PAL copy of func_L14_003E4208: the same C, where 0.008333334f becomes 0.01f, 0.016666668f becomes 0.02f, 100 becomes 83, 60 becomes 50 and total / 3 is scaled to 50 Hz. */
#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

extern float math_random_float_range(float, float);
extern int math_fast_float_d(int *counter);
extern void matrix_mul_vec3(void *dst, void *a, void *mtx);
extern void FastVecAdd(void *dst, void *a, void *b);
extern void moby_set_state(char *object, int state, int arg);
extern int flag_set_first_pending(char *self);
extern void snd_stop_voice(int index);
extern int PlayMobySound(int index, int a1, char *a2);
extern int FastTweenColor(int a, int b, float t);
extern float math_lerp_float(float a, float b, float t);
/* The particle spawner (src/levels/shared/L00_0033E888-qcopy.c), declared with the life and
   rotation floats among the integer arguments: the EE ABI keeps each register bank's order. */
extern void *part_spawn_spinning_particle(void *position, void *velocity, int color, int value, float life, int size,
                               int extra, float rotation, int texture, int flags, int weight);
extern char g_sound_state[];
extern char g_identity_l14_matrix[] __attribute__((sda));

/* The state block of a particle emitter. */
typedef struct {
    float rate_start;   /* 0x00 */
    float rate_end;     /* 0x04 */
    float accum;        /* 0x08 */
    float trigger;      /* 0x0C */
    int size;           /* 0x10 */
    int total;          /* 0x14 */
    int reset;          /* 0x18 */
    int remaining;      /* 0x1C */
    float spread[3];    /* 0x20 */
    float rotation;     /* 0x2C */
    int color[4];       /* 0x30 */
    float life_min[2];  /* 0x40 */
    float life_max[2];  /* 0x48 */
    int entry;          /* 0x50 */
} Emitter;

/* Particle emitter state machine. State 0 fills in the emitter block at self+0x68. State 2 stops
   the sound slot self still owns, then, while func_00282948 has not finished the remaining count,
   spawns particles at self+0x10 whenever the accumulated emission rate exceeds 1, with the rate
   and color ramped over that count; once the count is done it moves to state 3. State 3 claims a
   sound slot if self does not own one and keeps spawning at the end rate until triggered. */
void smoke_emitter_update_pal(char *self)
{
    Emitter *emitter = *(Emitter **)(self + 0x68);
    Vec pos;
    Vec vel;
    Vec offset;
    float rate;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        emitter->trigger = 0.0f;
        emitter->rate_start = 2.0f;
        emitter->rate_end = 30.0f;
        emitter->size = 50;
        emitter->total = 83;
        emitter->reset = 83;
        emitter->spread[0] = 0.005f;
        emitter->spread[1] = 0.01f;
        emitter->spread[2] = 0.002f;
        emitter->rotation = 4.0f;
        emitter->life_min[0] = 105000.0f;
        emitter->life_min[1] = 210000.0f;
        emitter->life_max[0] = 210000.0f;
        emitter->life_max[1] = 420000.0f;
        emitter->color[0] = 0x30505000;
        emitter->color[2] = 0x80508000;
        emitter->color[1] = 0x70700050;
        emitter->color[3] = 0x80800070;
        emitter->entry = -1;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (emitter->trigger == 1.0f) {
            emitter->trigger = 0.0f;
            moby_set_state(self, 2, -1);
        }
        break;
    case 2: {
        int start_color;
        int color;
        int value;
        float life;
        float rotation;

        if (emitter->trigger == 1.0f) {
            emitter->trigger = 0.0f;
            moby_set_state(self, 2, -1);
        }
        if (flag_set_first_pending(self)) {
            emitter->accum = 0.0f;
            emitter->remaining = emitter->total;
        }
        if (emitter->entry != -1) {
            char *sound_entry = g_sound_state + emitter->entry * 0x70;
            if (*(int *)(sound_entry + 0x88) == (int)self && *(unsigned char *)(sound_entry + 0x74) != 0) {
                snd_stop_voice(emitter->entry);
            }
        }
        emitter->entry = -1;
        if (math_fast_float_d(&emitter->remaining) == 0) {
            rate = (emitter->rate_end - emitter->rate_start) / (float)emitter->total;
            rate = emitter->rate_start + rate * (((float)emitter->total - (float)emitter->remaining) - 0.01f);
            rate *= 0.02f;
            emitter->accum += rate;
            while (emitter->accum > 1.0f) {
                char *moby_pos = self + 0x10;

                qcopy(&pos, moby_pos);
                qcopy(&vel, g_identity_l14_matrix);
                qcopy(&offset, g_identity_l14_matrix);
                offset.f[0] += 1.1f;
                matrix_mul_vec3(&offset, &offset, self + 0xC0);
                FastVecAdd(&pos, &pos, &offset);
                start_color = FastTweenColor(emitter->color[0], emitter->color[2], math_random_float_range(0.0f, 1.0f));
                color = FastTweenColor(FastTweenColor(emitter->color[1], emitter->color[3], math_random_float_range(0.0f, 1.0f)), start_color,
                                      (float)emitter->remaining / (float)emitter->total);
                value = color & 0xFFFFFF;
                life = math_random_float_range(math_lerp_float(emitter->life_max[0], emitter->life_min[0], (float)emitter->remaining / (float)emitter->total),
                                     math_lerp_float(emitter->life_max[1], emitter->life_min[1], (float)emitter->remaining / (float)emitter->total));
                if (emitter->remaining < ((s32)(emitter->total / 3) * 5 + 2) / 6) {
                    vel.f[0] += math_random_float_range(0.0f, emitter->spread[0] * 2.0f);
                    vel.f[1] += math_random_float_range(0.0f, emitter->spread[1] * 2.0f);
                    vel.f[2] += math_random_float_range(-emitter->spread[2], 0.0f);
                    life *= 1.5f;
                    rotation = 0.0f;
                } else {
                    vel.f[0] += math_random_float_range(0.0f, emitter->spread[0]);
                    vel.f[1] += math_random_float_range(0.0f, emitter->spread[1]);
                    vel.f[2] += math_random_float_range(-emitter->spread[2], 0.0f);
                    rotation = emitter->rotation;
                }
                matrix_mul_vec3(&vel, &vel, self + 0xC0);
                part_spawn_spinning_particle(&pos, &vel, color, value, life, emitter->size, 0, rotation, 2, -1, 0);
                emitter->accum -= 1.0f;
            }
        } else {
            moby_set_state(self, 3, -1);
        }
        break;
    }
    case 3: {
        char *sound_entry;

        flag_set_first_pending(self);
        sound_entry = g_sound_state + emitter->entry * 0x70;
        if (*(int *)(sound_entry + 0x88) != (int)self || *(unsigned char *)(sound_entry + 0x74) == 0) {
            emitter->entry = PlayMobySound(0, 4, self);
        }
        if (emitter->trigger == 0.0f) {
            rate = (emitter->rate_end - emitter->rate_start) / (float)emitter->total;
            rate = emitter->rate_start + rate * ((float)emitter->total - 0.01f);
            rate *= 0.02f;
            emitter->accum += rate;
            while (emitter->accum > 1.0f) {
                int color;
                int value;
                float life;

                qcopy(&pos, self + 0x10);
                qcopy(&vel, g_identity_l14_matrix);
                qcopy(&offset, g_identity_l14_matrix);
                offset.f[0] += 1.1f;
                matrix_mul_vec3(&offset, &offset, self + 0xC0);
                FastVecAdd(&pos, &pos, &offset);
                color = FastTweenColor(emitter->color[1], emitter->color[3], math_random_float_range(0.0f, 1.0f));
                value = color & 0xFFFFFF;
                life = math_random_float_range(math_lerp_float(emitter->life_max[0], emitter->life_min[0], (float)emitter->remaining / (float)emitter->total),
                                     math_lerp_float(emitter->life_max[1], emitter->life_min[1], (float)emitter->remaining / (float)emitter->total));
                vel.f[0] += math_random_float_range(0.0f, emitter->spread[0] * 2.0f);
                vel.f[1] += math_random_float_range(0.0f, emitter->spread[1] * 2.0f);
                vel.f[2] += math_random_float_range(-emitter->spread[2], 0.0f);
                life *= 1.5f;
                matrix_mul_vec3(&vel, &vel, self + 0xC0);
                part_spawn_spinning_particle(&pos, &vel, color, value, life, emitter->size, 0, 0.0f, 2, -1, 0);
                emitter->accum -= 1.0f;
            }
        } else {
            emitter->trigger = 0.0f;
            moby_set_state(self, 2, -1);
        }
        break;
    }
    }
}
