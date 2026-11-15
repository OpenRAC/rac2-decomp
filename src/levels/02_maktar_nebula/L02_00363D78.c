#include "common.h"

/* The background sky effects (rac1's update_sky_effects twin): seeds 256 effects
   on the first frame - 10 orbiting stars and 246 twinkling points on the shell -
   then moves the stars and re-randomises the points' colours, and submits them. */

typedef struct {
    short azimuth;
    u16 elevation;
} SkyAngles;

typedef union {
    SkyAngles angles;
    u32 base_color;
} SkyEffectState;

typedef struct {
    u8 randomize_color;
    u8 pad1;
    u8 texture_index;
    u8 flags;
    u32 color;
    float angle;
    SkyEffectState state;
    float position_x;
    float position_y;
    float position_z;
    float size;
} SkyEffect;

typedef struct {
    u8 pad0[4];
    u16 relocation_state;
    u8 pad6[2];
    short effect_count;
    u8 padA[0x12];
    SkyEffect *effects;
} SkyEffectData;

extern SkyEffectData *D_L02_001B3B20[] __attribute__((sda));
extern float D_L02_001B3B50[] MACRO_ADDR;

extern void func_00283388(float *);
extern void func_002E3478(int);
extern void func_002E3940(int);
extern int func_001163B0(void);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_00283CE0(int);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern void func_L02_00364A18(void);
extern void func_002FC560(unsigned int, unsigned long long);

void func_L02_00363D78(void)
{
    float trig_product;
    float elevation;
    float azimuth;
    int color_delta;
    u32 base_color;
    int i;
    int effect_index;
    int alpha_delta;
    int random_bits;
    int effect_flags;
    float radius;
    SkyEffect *effect;
    SkyAngles *orbit;
    short *angles;

    D_L02_001B3B20[0]->relocation_state = 0;
    set_identity_matrix(D_L02_001B3B50);
    func_002E3478(0);
    func_002E3940(0);
    func_002E3478(1);
    func_002E3940(1);
    if (D_L02_001B3B20[0]->effect_count == 0) {
        D_L02_001B3B20[0]->effect_count = 0x100;
        i = 0;
        do {
            radius = 50.0f;
            effect_flags = 0x48;
            base_color = 0x30505050;
            effect = &D_L02_001B3B20[0]->effects[i];
            if (i >= 0xF6) {
                effect->randomize_color = 0;
                angles = &effect->state.angles.azimuth;
                effect->state.angles.azimuth = (short)(func_001163B0() >> 16);
                angles[1] = (short)(func_001163B0() >> 16);
                effect->size = 0.16f;
                effect->texture_index = 1;
                effect->flags = effect_flags;
            } else {
                effect->randomize_color = 3;
                effect->state.angles.azimuth = func_002A77E0(0x100);
                effect->texture_index = (func_001163B0() >> 16) & 1;
                effect->flags = effect_flags;
                effect->angle = func_002A7940();
                effect->size = IntToFloat(func_002A77E0(0x30) + 0x20) * 0.00390625f;
                azimuth = func_002A7940();
                elevation = func_002A7940();
                trig_product = func_00283180(azimuth);
                trig_product = trig_product * func_00283198(elevation);
                trig_product = trig_product * radius;
                effect->position_x = trig_product;
                trig_product = func_00283198(azimuth);
                trig_product = trig_product * func_00283198(elevation);
                trig_product = trig_product * radius;
                effect->position_y = trig_product;
                trig_product = func_00283180(elevation);
                trig_product = trig_product * func_00283180(elevation);
                trig_product = trig_product * 36.0f;
                trig_product = trig_product + 16.0f;
                effect->position_z = trig_product;
                color_delta = func_002A77E0(0x18);
                alpha_delta = func_002A77E0(0x20) << 24;
                if ((func_001163B0() >> 16) & 1)
                    effect->state.base_color = alpha_delta + ((color_delta << 16) + base_color);
                else
                    effect->state.base_color = (alpha_delta + ((color_delta << 8) + base_color)) | color_delta;
            }
        } while (++i < D_L02_001B3B20[0]->effect_count);
    }
    for (effect_index = 0; effect_index < D_L02_001B3B20[0]->effect_count; effect_index++) {
        effect = &D_L02_001B3B20[0]->effects[effect_index];
        if (effect->randomize_color == 0) {
            orbit = &effect->state.angles;
            angles = &effect->state.angles.azimuth;
            effect->state.angles.azimuth = (short)(effect->state.angles.azimuth + 1);
            angles[1] = (u16)(angles[1] + 1);
            azimuth = IntToFloat((orbit->azimuth & 0xFFF) - 0x800) * 0.0015339808f;
            elevation = IntToFloat((angles[1] & 0xFFF) - 0x800) * 0.0015339808f;
            trig_product = func_00283180(azimuth);
            trig_product = trig_product * func_00283198(elevation);
            trig_product = trig_product * 50.0f;
            effect->position_x = trig_product;
            trig_product = func_00283198(azimuth);
            trig_product = trig_product * func_00283198(elevation);
            trig_product = trig_product * 50.0f;
            effect->position_y = trig_product;
            effect->position_z = func_00282C48(func_00283180(elevation)) * 50.0f;
            if ((u32)(orbit->azimuth & 0x3F) < 8U)
                effect->color = 0x702020F0;
            else
                effect->color = 0x202020F0;
        } else if (effect->randomize_color == 3) {
            u32 color_value;
            u32 color_offset;

            random_bits = func_001163B0() >> 16;
            color_offset = ((random_bits & 0x1F00) << 10) + 0xFFDFDFE0;
            color_value = effect->state.base_color + color_offset;
            color_value += (random_bits & 0x1F0) << 6;
            color_value += (random_bits & 0x1F) << 2;
            effect->color = color_value;
        }
    }
    func_L02_00364A18();
    VU1_addGSregister(0x42, (0x8000ULL << 24) | 0x44);
    func_002E3478(2);
    func_002E3940(2);
    func_002E3478(3);
    func_002E3940(3);
}
