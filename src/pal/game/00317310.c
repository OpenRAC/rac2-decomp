#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_00317310);

INCLUDE_ASM("asm/pal/game", func_PAL_00317768);

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
extern PoolEffect D_0022AA10[3];
extern char D_001B2520[] MACRO_ADDR;
extern float func_002A7878(float min, float max);
extern float func_002A78D8(float min, float max);
extern void func_00282C88(void *vector);
extern char *func_002AB1F0(void *object);
extern void func_002B00B0(void *object, void *out, int);
extern void func_00282D30(void *out, void *vector, float scale);
extern void func_00282CC0(void *,void *,void *);
extern int D_001A73E0[] MACRO_ADDR;
extern void func_00282CC0(void *, void *, void *);

/* func_00316248 is in 0030F7B0-g8.c. */

/* Fills the first free effect slot for owner: random angles, speeds and amplitudes, a timer
 * of duration frames, and the object's position as the start (offset when it has a record). */
void func_PAL_00317928(void *owner, char *object, int duration)
{
    PoolEffect *pool = D_0022AA10;
    int i = 0;
    const char *origin = D_001B2520;
    PoolEffect *effect;
    float displacement[4] __attribute__((aligned(16)));
    char *info;

    for (; i < 3; i++) {
        effect = &pool[i];
        if (effect->owner != 0)
            continue;

        effect->owner = owner;
        qcopy(effect->origin, origin);
        effect->angle[0] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle[1] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle[2] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle2[0] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle2[1] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->angle2[2] = func_002A7878(-3.1415927f, 3.1415927f);
        effect->speed[0] = func_002A78D8(0.001f, 0.005f);
        effect->speed[1] = func_002A78D8(0.001f, 0.005f);
        effect->speed[2] = func_002A78D8(0.001f, 0.005f);
        effect->speed2[0] = func_002A78D8(0.001f, 0.005f);
        effect->speed2[1] = func_002A78D8(0.001f, 0.005f);
        effect->speed2[2] = func_002A78D8(0.001f, 0.005f);
        effect->amplitude[0] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude[1] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude[2] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[0] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[1] = func_002A7878(3.25f, 4.75f) * 0.5f;
        effect->amplitude2[2] = func_002A7878(3.25f, 4.75f) * 0.5f;
        func_00282C88(effect->offset);
        func_00282C88(effect->rotation);
        effect->timer = duration;
        effect->duration = duration;
        effect->fade = 12;
        effect->object = object;
        effect->expired = 0;

        info = func_002AB1F0(object);
        if (info != 0) {
            func_002B00B0(object, displacement, 1);
            func_00282D30(displacement, displacement, *(float *)(info + 16));
            func_00282CC0(effect->position, displacement, object + 16);
        } else {
            char *source = object + 16;

            qcopy(effect->position, source);
        }
        break;
    }
}

