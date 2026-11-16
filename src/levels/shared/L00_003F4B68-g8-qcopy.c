#include "names.h"
/* Reconstructed from retail; standalone all-placement checks pass in all three releases.
 * The lead must still verify strict linked builds. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void vec_add_transformed_or_copy(char *,char *,char *);
extern float mat_fast_helper_a(float,float);
extern void func_002A0F48(char *);
extern unsigned short g_bouncing_explosive_timer __attribute__((sda));
extern float g_bouncing_explosive_speed_scale __attribute__((sda));

/* Creates a bouncing explosive moby (class 3315) at the given position, with its throw
   velocity, owner and timer. */
char *bouncing_explosive_spawn(int owner, char *position, char *velocity, int value, float scale)
{
    char *object = CreateMoby(0xcf3 /* moby class 3315 */);
    char *state;
    float angle;
    unsigned short timer;
    if (object != 0) {
        state = *(char **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x31] = 1;
        object[0x20] = 0;
        *(int *)(state + 0x24) = owner;
        *(TI128 *)(object + 0x10) = *(TI128 *)position;
        *(TI128 *)(state + 0x10) = *(TI128 *)velocity;
        vec_add_transformed_or_copy(state + 0x10, state + 0x10, position);
        timer = g_bouncing_explosive_timer;
        *(float *)(state + 0x1c) = scale;
        *(int *)(state + 0x20) = value;
        *(short *)(state + 0x28) = timer;
        *(short *)(state + 0x2a) = 0;
        *(int *)(object + 0xf0) = 0;
        *(int *)(object + 0xf4) = 0;
        angle = mat_fast_helper_a(*(float *)velocity, *(float *)(velocity+4));
        *(float *)(object + 0x2c) *= g_bouncing_explosive_speed_scale;
        *(float *)(object + 0xf8) = angle;
        func_002A0F48(object);
    }
    return object;
}
