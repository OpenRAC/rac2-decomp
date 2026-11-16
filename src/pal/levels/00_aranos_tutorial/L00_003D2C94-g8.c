#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    int color;
    int mode;
    char gap[2];
    unsigned char alpha, brightness;
} ExhaustTail;
extern int math_random_int_below(int);
extern int math_fast_float_d(char *);
extern int FloatToInt(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_spinning_spark_pal(void *, float, float, float, int, void *, float, int, int);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float g_exhaust_angle_a __attribute__((sda));
extern float g_exhaust_angle_b __attribute__((sda));
extern float g_exhaust_rate_a __attribute__((sda));
extern float g_exhaust_rate_b __attribute__((sda));
extern float g_exhaust_angle_degrees __attribute__((sda));

/* Spawns glowing exhaust particles behind the object while it is active (PAL: 5/6 start delay). */
void paired_spark_emitter_update_pal(unsigned char *moby) {
    struct {
        Vec velocity, forward, position, up, side;
    } frame;
    char *vars = *(char **)(moby + 0x68), *glow_a, *glow_b, *glow_c;
    if ((unsigned char)moby[0x20] == 0) {
        *(int *)(vars + 0x10) = ((s32)(math_random_int_below(40)) * 5 + 2) / 6;
        moby[0x20] = 1;
        moby[0x30] = 100;
        *(int *)(vars + 0x18) = 0;
        *(float *)(vars + 0x28) = *(float *)(moby + 0x18);
    }
    if ((unsigned char)moby[0x20] == 1) {
        if (math_fast_float_d(vars + 0x10)) moby[0x20] = 2;
        {
            int angle;
            vec_scale_to_length(&frame.velocity, moby + 0xC0, -0.15f);
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            qcopy(&frame.position, moby + 0x10);
            vec_scale_to_length(&frame.forward, moby + 0xC0, -2.3f);
            FastVecAdd(&frame.position, &frame.position, &frame.forward);
            vec_scale_to_length(&frame.up, moby + 0xE0, 0.75f);
            FastVecAdd(&frame.position, &frame.position, &frame.up);
            vec_scale_to_length(&frame.side, moby + 0xD0, 0.25f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            glow_a = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_a) {
                ExhaustTail *tail = (ExhaustTail *)(glow_a + 0x20);
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_b = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_b) {
                ExhaustTail *tail = (ExhaustTail *)(glow_b + 0x20);
                /* Retail updates the glow_a particle's header again here. */
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_c = part_spawn_spinning_spark_pal(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (glow_c) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(glow_c + 0x20);
                brightness = FloatToInt(4.0f);
                *(short *)(glow_c + 10) = 17;
                glow_c[9] = brightness + 112;
                glow_c[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            vec_scale_to_length(&frame.side, moby + 0xD0, -0.5f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            glow_a = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_a) {
                ExhaustTail *tail = (ExhaustTail *)(glow_a + 0x20);
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_b = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_b) {
                ExhaustTail *tail = (ExhaustTail *)(glow_b + 0x20);
                /* Retail updates the glow_a particle's header again here. */
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_c = part_spawn_spinning_spark_pal(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (glow_c) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(glow_c + 0x20);
                brightness = FloatToInt(4.0f);
                *(short *)(glow_c + 10) = 17;
                glow_c[9] = brightness + 112;
                glow_c[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
        }
    }
    if ((unsigned char)moby[0x20] == 2) {
        math_update_wrapped_angle_offset(moby, vars + 0xC, vars, g_exhaust_angle_a,
            g_exhaust_angle_b * 0.0003490659f, *(float *)(vars + 0x28));
        moby_scale_owner_words_by_angles(moby, vars + 4, vars + 8,
            g_exhaust_angle_degrees * 0.017453294f, g_exhaust_rate_a * 0.0003490659f,
            g_exhaust_rate_b * 0.0003490659f);
        {
            int angle;
            vec_scale_to_length(&frame.velocity, moby + 0xC0, -0.15f);
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            qcopy(&frame.position, moby + 0x10);
            vec_scale_to_length(&frame.forward, moby + 0xC0, -2.3f);
            FastVecAdd(&frame.position, &frame.position, &frame.forward);
            vec_scale_to_length(&frame.up, moby + 0xE0, 0.75f);
            FastVecAdd(&frame.position, &frame.position, &frame.up);
            vec_scale_to_length(&frame.side, moby + 0xD0, 0.25f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            glow_a = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_a) {
                ExhaustTail *tail = (ExhaustTail *)(glow_a + 0x20);
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_b = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_b) {
                ExhaustTail *tail = (ExhaustTail *)(glow_b + 0x20);
                /* Retail updates the glow_a particle's header again here. */
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_c = part_spawn_spinning_spark_pal(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (glow_c) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(glow_c + 0x20);
                brightness = FloatToInt(4.0f);
                glow_c[9] = brightness + 112;
                *(short *)(glow_c + 10) = 17;
                glow_c[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            vec_scale_to_length(&frame.side, moby + 0xD0, -0.5f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            glow_a = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_a) {
                ExhaustTail *tail = (ExhaustTail *)(glow_a + 0x20);
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_b = part_spawn_spinning_spark_pal(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (glow_b) {
                ExhaustTail *tail = (ExhaustTail *)(glow_b + 0x20);
                /* Retail updates the glow_a particle's header again here. */
                *(short *)(glow_a + 10) = 17;
                glow_a[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
            glow_c = part_spawn_spinning_spark_pal(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (glow_c) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(glow_c + 0x20);
                brightness = FloatToInt(4.0f);
                *(short *)(glow_c + 10) = 17;
                glow_c[9] = brightness + 112;
                glow_c[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)glow_a[10];
            }
        }
    }
}
