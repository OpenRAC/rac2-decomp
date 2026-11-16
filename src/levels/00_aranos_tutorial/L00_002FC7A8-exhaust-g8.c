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
/* The integer and FP argument banks retain their independent EE ABI order. */
extern char *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, int, int);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float g_exhaust_angle_a __attribute__((sda));
extern float g_exhaust_angle_b __attribute__((sda));
extern float g_exhaust_rate_a __attribute__((sda));
extern float g_exhaust_rate_b __attribute__((sda));
extern float g_exhaust_angle_degrees __attribute__((sda));

/* Spawns glowing exhaust particles behind the object while it is active. */
void UpdatePairedSparkEmitter(unsigned char *obj) {
    struct {
        Vec velocity, forward, position, up, side;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *first, *second, *child;
    if ((unsigned char)obj[0x20] == 0) {
        *(int *)(ctx + 0x10) = math_random_int_below(40);
        obj[0x20] = 1;
        obj[0x30] = 100;
        *(int *)(ctx + 0x18) = 0;
        *(float *)(ctx + 0x28) = *(float *)(obj + 0x18);
    }
    if ((unsigned char)obj[0x20] == 1) {
        if (math_fast_float_d(ctx + 0x10)) obj[0x20] = 2;
        {
            int angle;
            vec_scale_to_length(&frame.velocity, obj + 0xC0, -0.15f);
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            qcopy(&frame.position, obj + 0x10);
            vec_scale_to_length(&frame.forward, obj + 0xC0, -2.3f);
            FastVecAdd(&frame.position, &frame.position, &frame.forward);
            vec_scale_to_length(&frame.up, obj + 0xE0, 0.75f);
            FastVecAdd(&frame.position, &frame.position, &frame.up);
            vec_scale_to_length(&frame.side, obj + 0xD0, 0.25f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            first = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = SpawnSpinningSparkParticle(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = FloatToInt(4.0f);
                *(short *)(child + 10) = 20;
                child[9] = brightness + 112;
                child[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            vec_scale_to_length(&frame.side, obj + 0xD0, -0.5f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            first = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = SpawnSpinningSparkParticle(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = FloatToInt(4.0f);
                *(short *)(child + 10) = 20;
                child[9] = brightness + 112;
                child[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
        }
    }
    if ((unsigned char)obj[0x20] == 2) {
        math_update_wrapped_angle_offset(obj, ctx + 0xC, ctx, g_exhaust_angle_a,
            g_exhaust_angle_b * 0.00029088825f, *(float *)(ctx + 0x28));
        moby_scale_owner_words_by_angles(obj, ctx + 4, ctx + 8,
            g_exhaust_angle_degrees * 0.017453294f, g_exhaust_rate_a * 0.00029088825f,
            g_exhaust_rate_b * 0.00029088825f);
        {
            int angle;
            vec_scale_to_length(&frame.velocity, obj + 0xC0, -0.15f);
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            qcopy(&frame.position, obj + 0x10);
            vec_scale_to_length(&frame.forward, obj + 0xC0, -2.3f);
            FastVecAdd(&frame.position, &frame.position, &frame.forward);
            vec_scale_to_length(&frame.up, obj + 0xE0, 0.75f);
            FastVecAdd(&frame.position, &frame.position, &frame.up);
            vec_scale_to_length(&frame.side, obj + 0xD0, 0.25f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            first = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = SpawnSpinningSparkParticle(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = FloatToInt(4.0f);
                child[9] = brightness + 112;
                *(short *)(child + 10) = 20;
                child[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            angle = math_random_int_below(16);
            if (math_random_int_below(2)) angle = -angle;
            vec_scale_to_length(&frame.side, obj + 0xD0, -0.5f);
            FastVecAdd(&frame.position, &frame.side, &frame.position);
            first = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (first) {
                ExhaustTail *tail = (ExhaustTail *)(first + 0x20);
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            second = SpawnSpinningSparkParticle(&frame.position, 0.1f, 1.0f, 0.9f,
                angle, &frame.velocity, 100000.0f, 0xDF204080, 0);
            if (second) {
                ExhaustTail *tail = (ExhaustTail *)(second + 0x20);
                /* Retail updates the first particle's header again here. */
                *(short *)(first + 10) = 20;
                first[9] = FloatToInt(4.0f) + 112;
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
            child = SpawnSpinningSparkParticle(&frame.position, 0.05f, 1.0f, 0.97f,
                16, &frame.velocity, 60000.0f, 0xDFFFFFFF, 0);
            if (child) {
                int brightness;
                ExhaustTail *tail = (ExhaustTail *)(child + 0x20);
                brightness = FloatToInt(4.0f);
                *(short *)(child + 10) = 20;
                child[9] = brightness + 112;
                child[8] = math_random_int_below(255);
                tail->mode = 2;
                tail->alpha = 0xDF;
                tail->brightness = (unsigned char)first[10];
            }
        }
    }
}
