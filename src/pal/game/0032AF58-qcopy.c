#include "include_asm.h"
#include "names.h"

typedef int V4_Fc936841d __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern float math_random_float_range(float, float);
extern void func_002A0F48(void *);

/* Creates a flying chunk moby at data, moving by source, with random spin; starts fully opaque
   and half size (PAL: same as USA v1.01). */
char *part_spawn_flying_chunk_b_pal(int id, void *data, void *source)
{
    char *self = CreateMoby(0xBD8);
    char *state;
    int alpha;

    if (self != 0) {
        state = *(char **)(self + 0x68);
        *(int *)(state + 0x30) = id;
        *(V4_Fc936841d *)(self + 0x10) = *(V4_Fc936841d *)data;
        *(V4_Fc936841d *)state = *(V4_Fc936841d *)source;
        *(int *)(state + 0x10) = 0;
        *(float *)(state + 0x14) = math_random_float_range(180.0f, 360.0f) * 0.0003490659f;
        *(float *)(state + 0x18) = math_random_float_range(180.0f, 360.0f) * 0.0003490659f;
        *(unsigned char *)(self + 0x20) = 0;
        alpha = 0xFF;
        *(unsigned short *)(self + 0x32) = alpha;
        *(unsigned char *)(self + 0x30) = alpha;
        *(float *)(self + 0x2C) *= 0.5f;
        func_002A0F48(self);
    }
    return self;
}
