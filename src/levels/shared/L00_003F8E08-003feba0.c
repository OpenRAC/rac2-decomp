#include "include_asm.h"
#include "names.h"
extern int func_002A77E0_3(int);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern void func_002A7A00(char *,float,float);
extern char *func_002BDCE8(float,float,float,float,char *,int,char *,unsigned int,int);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Spawn six sparks along a segment centred on pos and running along direction. */
void func_L00_003FEBA0(void *unused, void *pos, void *direction)
{
    float out[4], scaled[4], local[4];
    float length = FastVecLength(direction);
    float speed;
    int i;
    unsigned int shade, packed, color;
    unsigned int alpha;
    char *spark;

    if (length == 0.0f)
        return;

    {
        float inverse;

        inverse = 1.0f / length;
        FastVecScale(scaled, direction, inverse * 0.5f);
    }
    FastVecAdd(out, pos, scaled);

    alpha = 0x7f000000U;
    for (i = 5; i >= 0; i--) {
        func_002A77E0_3(2);
        func_002A77E0_3(2);
        speed = RandomFloatRange(70000.0f, 150000.0f);
        shade = RandomIntRange(10, 127);
        packed = (shade << 8) | alpha;
        color = (shade << 16) | packed;
        shade = color | shade;
        RandomDirectionVector((char *)local, 1.6666668670950457453728e-05f, 6.6666672937572002410889e-03f);
        spark = SpawnSpinningSparkParticle(0.3f, 1.0f, 1.01f, speed, (char *)out, 0, (char *)local, shade, 1);
        if (spark != 0) {
            char *ext = spark + 32;

            *(short *)(spark + 10) = 120;
            *(int *)(ext + 4) = 2;
            ext[10] = 127;
            ext[11] = *(unsigned char *)(spark + 10);
        }
    }
}
