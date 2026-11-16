#include "include_asm.h"
#include "names.h"

typedef struct { int colors[6]; } Colors1043;
extern Colors1043 ref_L00_002AC728_00, ref_L00_002AC728_01;
extern float ref_L00_002AC728_02[];
extern int math_random_int_below(int);
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, float, int, int);
extern char *func_PAL_003096D0(void *, void *, void *, int, int, int, int, int, float);
extern int PlayMobySound(int, int, void *);
extern char *moby_spawn_template_effect(void *, void *, int, int);
extern void vec_clear_128(char *p);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);

void part_spawn_explosion_with_sparks_pal(unsigned char *object, void *position, int sound, float scale, float radius)
{
    float zero[3];
    Colors1043 first, second;
    float speed, energy;
    int i, life;
    int *a, *b;
    vec_clear_128((char *)zero);
    for (i=2;i>=0;i--) {
        speed = math_random_float_range(8.0f,10.0f) * 0.020000001f;
        energy = scale * 400000.0f;
        first = ref_L00_002AC728_00;
        second = ref_L00_002AC728_01;
        a = &first.colors[math_random_int_below(6)];
        b = &second.colors[math_random_int_below(6)];
        life = math_random_int_range(12,17);
        part_spawn_firework_spark(position,zero,*a,*b,energy,life,math_random_int_range(21,25),speed*scale,0,0);
    }
    if (object) {
        func_PAL_003096D0(object,position,zero,17,127,64,0,48,scale*4.0f);
        func_PAL_003096D0(object,position,zero,24,96,32,0,32,scale*3.0f);
        if (object[0x20] != 0xfe)
            if (object[0x20] != 0xfd)
                if (sound != -1) PlayMobySound(sound,0,object);
    }
    if (radius != 0.0f) {
        if (radius > 0.0f) {
            ref_L00_002AC728_02[9]=radius;
            ref_L00_002AC728_02[10]=radius;
            ref_L00_002AC728_02[8]=radius;
        } else {
            ref_L00_002AC728_02[9]=13.0f;
            ref_L00_002AC728_02[10]=13.0f;
            ref_L00_002AC728_02[8]=13.0f;
        }
        moby_spawn_template_effect(ref_L00_002AC728_02,position,0,0);
    }
}
