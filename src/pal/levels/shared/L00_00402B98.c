#include "include_asm.h"
#include "names.h"

extern int math_random_int_below(int x);
extern float math_random_float_range(float, float);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_random_direction(char *, float, float);
extern char *part_spawn_spinning_spark_pal(float, float, float, float, char *, int, char *,
                     unsigned int, int);
extern void vec_scale_to_length(void *, void *, float);
extern char *moby_spawn_template_effect(void *, void *, void *, void *);
extern char ref_L00_003FE310_00[];

/* Twenty rounds that spawn a particle at the second argument: each round draws a radius
   (70000..150000) and a byte (10..127), builds a three-float direction on the stack and
   fills the new record's short and byte fields; the level's own data address is then
   handed to the vector routine with the third argument and a scale of 1.5, and to the
   level-object starter with the second argument. */
void part_spawn_muzzle_spark_burst_pal(void *unused, void *position, void *direction)
{
    char velocity[16];
    float speed;
    int i;
    unsigned int shade;
    unsigned int packed;
    unsigned int color;
    char *spark;

    for (i = 19; i >= 0; i--) {
        math_random_int_below(2);
        math_random_int_below(2);
        speed = math_random_float_range(70000.0f, 1.5e+05f);
        shade = math_random_int_range(10, 127);
        packed = (shade << 8) | 0x7f000000U;
        color = (shade << 16) | packed;
        shade = color | shade;
        vec_random_direction(velocity, 2.0000003e-05f,
                0.008f);
        spark = part_spawn_spinning_spark_pal(0.3f, 1.0f, 1.01f, speed, position, 0, velocity, shade, 1);
        if (spark != 0) {
            char *ext = spark + 32;

            *(short *)(spark + 10) = 100;
            *(int *)(ext + 4) = 2;
            *(char *)(ext + 10) = 127;
            *(char *)(ext + 11) = *(unsigned char *)(spark + 10);
        }
    }
    vec_scale_to_length(ref_L00_003FE310_00, direction, 1.5f);
    moby_spawn_template_effect(ref_L00_003FE310_00, position, 0, 0);
}


typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;
extern void func_002FDBD8_6(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void moby_draw_attached_effect_pal(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_6(1.0f, context, context->vector_10, 0);
    }
}
