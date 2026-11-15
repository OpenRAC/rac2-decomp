#include "common.h"
extern s32 FloatToInt(float);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void moby_set_state(u8 *, s32, s32);
extern void protopet_reset_to_idle(u8 *);
extern s32 moby_set_table_entry_byte(u8 *, s32, s32);
extern u8 *g_moby_l18_table MACRO_ADDR;
typedef struct {
    u8 reserved00[0x20];
    float animation;
    s16 mode;
    u8 reserved26[2];
    u8 kind, ready;
    u8 reserved2A[6];
    float blend;
    u8 reserved34[0x14];
    u8 duration;
    u8 reserved49;
    u8 speed;
    u8 reserved4B[0x15];
    u8 type;
    u8 reserved61[0x1F];
    float strength, secondary;
    u8 reserved88[4];
    float decay;
    u8 reserved90[8];
    s32 count;
    u8 reserved9C[0x30];
    s32 configuration;
} InitializationFields;

/* Sets up a new Protopet: its timings, speeds, sizes and starting animation. */
void protopet_init(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    s16 mode;
    s32 configuration;
    InitializationFields *settings = (InitializationFields *)state;
    settings->duration = FloatToInt(15.0f);
    settings->speed = FloatToInt(6.0f);
    configuration = *(s32 *)(state + 0x260);
    settings->type = 17;
    settings->ready = 1;
    settings->count = 3;
    settings->strength = 0.49000000953674316f;
    settings->secondary = 0.49000000953674316f;
    settings->configuration = configuration;
    settings->decay = 0.4f;
    if (settings->mode == 0) {
        settings->mode = 16;
        settings->animation = 16.0f;
    }
    settings->kind = 3;
    settings->blend = 0.5f;
    state[0x2E] = 1;
    *(float *)(state + 0x134) = 1.4f;
    *(float *)(state + 0x104) = 0.2f;
    *(float *)(state + 0x100) = 0.4f;
    *(float *)(state + 0x12C) = 0.0055555556900799274f;
    *(float *)(state + 0x108) = 2.0f;
    *(float *)(state + 0x10C) = 5.0f;
    *(float *)(state + 0x110) = 1.5707964897155762f;
    moby_set_controller_speed_limits(object, 0.004444444552063942f, 0.13333334028720856f, 0.0034906589426100254f, 0.20943954586982727f);
    if (*(s32 *)(state + 0x260) != -1) *(s32 *)(state + 0x13C) = *(s32 *)(state + 0x260);
    *(float *)(state + 0x268) = *(float *)(object + 0x2C);
    if (*(s32 *)(state + 0x280) != -1) *(u8 **)(state + 0x258) = g_moby_l18_table + (*(s32 *)(state + 0x280) << 8);
    *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
    moby_set_state(object, 6, 2);
    mode = *(s16 *)(state + 0x296);
    if (mode == 14) {
        if (*(s32 *)(state + 0x26C) != -1) moby_set_state(object, 14, 2);
    } else if (mode == 1) protopet_reset_to_idle(object);
    else if (mode == 2) moby_set_state(object, 2, 0);
    qcopy((state + 0x210), (object + 0x10));
    qcopy((state + 0x220), (object + 0xF0));
    moby_set_table_entry_byte(object, 0, 3);
}
