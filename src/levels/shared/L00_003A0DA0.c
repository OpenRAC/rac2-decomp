#include "names.h"
/* func_L00_003A0DA0 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern void *CreateMoby(int);
extern float math_random_float_range(float,float);
extern void set_moby_color(void *,unsigned char,unsigned char,unsigned char);
extern void func_002A0F48(void *);
/* Creates an explosion effect object at the given position and sets its color, size and lifetime. */
char *part_create_explosion(int value,Quad *position,Quad *velocity,int timer,
 unsigned char red,unsigned char green,unsigned char blue,unsigned char flags,float scale)
{
    char *object=CreateMoby(1192 /* Explosion Effect */);
    char *state;
    /* Two adjacent complete vectors occupy retail stack offsets 0 and 0x10. */
    struct {
        Quad angles;
        union { Quad quad; float f[4]; } random;
    } scratch;
    if(object) {
        state=*(char **)(object+0x68);
        scratch.random.quad=0;
        scratch.random.f[0]=math_random_float_range(-3.1415927410125732f,3.1415927410125732f);
        scratch.random.f[1]=math_random_float_range(-3.1415927410125732f,3.1415927410125732f);
        scratch.random.f[2]=math_random_float_range(-3.1415927410125732f,3.1415927410125732f);
        scratch.angles=scratch.random.quad;
        object[0x20]=0;
        object[0x23]=flags;
        *(unsigned char *)(object+0x30)=255;
        *(unsigned short *)(object+0x32)=255;
        object[0x31]=1;
        set_moby_color(object,red,green,blue);
        *(float *)(state+0x18)=*(float *)(object+0x2C)*scale;
        *(float *)(object+0x2C)=0.0f;
        *(int *)(state+0x10)=value;
        qcopy(object+0x10, position);
        qcopy(state, velocity);
        qcopy(object+0xF0, &scratch.angles);
        *(short *)(state+0x1E)=flags;
        *(int *)(state+0x14)=timer;
        *(short *)(state+0x1C)=*(unsigned short *)(state+0x14);
        func_002A0F48(object);
    }
    return object;
}
