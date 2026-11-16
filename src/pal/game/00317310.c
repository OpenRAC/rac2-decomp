#include "include_asm.h"

#include "common.h"
typedef struct {
    float offset[4];             
    float rotation[4];           
    float origin[4];             
    float position[4];           
    float angle[3];              
    float speed[3];              
    float amplitude[3];          
    float angle2[3];             
    float speed2[3];             
    float amplitude2[3];         
    int fade;                    
    void *owner;                 
    char *object;                
    int timer;                   
    int duration;                
    int expired;                 
} PoolEffect;
extern PoolEffect g_pool_effect_slots[3];
extern char g_emitter_origin[] MACRO_ADDR;
extern float math_random_float_range(float min, float max);
extern float math_random_signed_float_range(float min, float max);
extern void vec_clear_128(void *vector);
extern char *moby_get_private_value_0(void *object);
extern void gravity_get_dir_at_object(void *object, void *out, int);
extern void FastVecScale(void *out, void *vector, float scale);
extern void FastVecAdd(void *,void *,void *);
extern int g_slot_play_counters[] MACRO_ADDR;
extern void FastVecAdd(void *, void *, void *);

/* func_00316248 is in 0030F7B0-g8.c. */

/* Fills the first free effect slot for owner: random angles, speeds and amplitudes, a timer
 * of duration frames, and the object's position as the start (offset when it has a record). */
void func_PAL_00317928(void *owner, char *object, int duration)
{
    PoolEffect *pool = g_pool_effect_slots;
    int i = 0;
    const char *origin = g_emitter_origin;
    PoolEffect *effect;
    float displacement[4] __attribute__((aligned(16)));
    char *info;

    for (; i < 3; i++) {
        effect = &pool[i];
        if (effect->owner != 0)
            continue;

        effect->owner = owner;
        qcopy(effect->origin, origin);
        effect->angle[0] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle[1] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle[2] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle2[0] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle2[1] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->angle2[2] = math_random_float_range(-3.1415927f, 3.1415927f);
        effect->speed[0] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed[1] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed[2] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed2[0] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed2[1] = math_random_signed_float_range(0.001f, 0.005f);
        effect->speed2[2] = math_random_signed_float_range(0.001f, 0.005f);
        effect->amplitude[0] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude[1] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude[2] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[0] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[1] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[2] = math_random_float_range(3.25f, 4.75f) * 0.5f;
        vec_clear_128(effect->offset);
        vec_clear_128(effect->rotation);
        effect->timer = duration;
        effect->duration = duration;
        effect->fade = 12;
        effect->object = object;
        effect->expired = 0;

        info = moby_get_private_value_0(object);
        if (info != 0) {
            gravity_get_dir_at_object(object, displacement, 1);
            FastVecScale(displacement, displacement, *(float *)(info + 16));
            FastVecAdd(effect->position, displacement, object + 16);
        } else {
            char *source = object + 16;

            qcopy(effect->position, source);
        }
        break;
    }
}

