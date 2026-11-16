#include "include_asm.h"
#include "names.h"

extern unsigned char g_ship_settings_byte_a;
extern unsigned char g_ship_settings_byte_b;
extern unsigned char g_ship_settings_byte_c;
extern float g_ship_settings_float_c __attribute__((sda));
extern float g_ship_settings_float_a __attribute__((sda));
extern float g_ship_settings_float_d __attribute__((sda));
extern float g_ship_settings_float_b __attribute__((sda));
extern int g_ship_settings_word __attribute__((sda));
extern unsigned char g_ship_saved_byte_a;
extern unsigned char g_ship_saved_byte_b;
extern unsigned char g_ship_saved_byte_c;
extern float g_ship_saved_float_c __attribute__((sda));
extern float g_ship_saved_float_a __attribute__((sda));
extern float g_ship_saved_float_d __attribute__((sda));
extern float g_ship_saved_float_b __attribute__((sda));
extern int g_ship_saved_word;

/* The reverse copy of func_L05_00442720. */
/* Puts the ship's saved settings back as the current settings. */
void ship_restore_settings(void)
{
    unsigned int byte0 = g_ship_saved_byte_a;
    unsigned int byte1 = g_ship_saved_byte_b;
    unsigned int byte2 = g_ship_saved_byte_c;
    float float0 = g_ship_saved_float_a;
    float float1 = g_ship_saved_float_b;
    float float2 = g_ship_saved_float_c;
    float float3 = g_ship_saved_float_d;
    unsigned int word = g_ship_saved_word;

    g_ship_settings_byte_a = byte0;
    g_ship_settings_byte_b = byte1;
    g_ship_settings_byte_c = byte2;
    g_ship_settings_float_a = float0;
    g_ship_settings_float_b = float1;
    g_ship_settings_float_c = float2;
    g_ship_settings_float_d = float3;
    g_ship_settings_word = word;
}
