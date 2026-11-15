#include "common.h"
extern float func_00283198(float), func_00283180(float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern int func_00283CF0(float);
typedef union { int address; unsigned long *words; } SpriteCursor;
/* The incomplete array keeps absolute cursor accesses in the macro address model. */
extern SpriteCursor D_L05_001B2C88[] __attribute__((sda));
extern int D_001A7350, D_001A7354;
/* Counterpart: RAC1 append_rotated_textured_screen_quad. Emits one rotated sprite packet. */
/* Draws one flat sprite on the screen, turned by the given angle, by writing a packet for the graphics hardware. */
void func_L05_00444FD0(float center_x, float center_y, float width, float height,
                      float angle, int texture_width, int texture_height,
                      long texture, int depth, int red, int green, int blue, int alpha)
{
    float vertical[4];
    float horizontal[4];
    float center[4];
    float upper_left[4];
    float upper_right[4];
    float lower_left[4];
    float lower_right[4];
    unsigned long color;
    unsigned long green_bits;
    unsigned long blue_bits;
    unsigned long alpha_bits;
    unsigned long texture_word;
    int z_value;
    unsigned long depth_bits;
    unsigned long gif_tag;
    unsigned long register_list;
    unsigned long texture_register;
    unsigned long initial_uv;
    int vif_tag;
    int texture_u;
    int texture_v;
    char *tag;
    unsigned long *packet;
    float subpixel_scale;

    color = red & 0xFF;
    green_bits = green & 0xFF;
    blue_bits = blue & 0xFF;
    alpha_bits = alpha & 0xFF;
    texture_word = texture;
    z_value = depth;

    center[0] = center_x;
    center[1] = center_y;
    vertical[0] = height * FastSinOrCosB(angle);
    vertical[1] = height * FastSinOrCosA(angle);
    horizontal[0] = width * FastSinOrCosA(angle);
    horizontal[1] = -width * FastSinOrCosB(angle);
    FastVecAdd(upper_left, center, vertical);
    FastVecSub(upper_left, upper_left, horizontal);
    FastVecAdd(upper_right, center, vertical);
    FastVecSub(lower_left, center, horizontal);
    qcopy(lower_right, center);

    *(int *)(D_L05_001B2C88[0].address + 0) = 0x10000007;
    color = color | (green_bits << 8);
    vif_tag = 0x50000007;
    register_list = 0x53535353106;
    *(int *)(D_L05_001B2C88[0].address + 4) = 0;
    blue_bits = blue_bits << 16;
    color = color | blue_bits;
    alpha_bits = alpha_bits << 24;
    texture_register = 0x154;
    initial_uv = 0x100010;
    gif_tag = 0xB400000000008001;
    color = color | alpha_bits;
    *(int *)(D_L05_001B2C88[0].address + 8) = 0;
    subpixel_scale = 16.0f;
    texture_u = texture_width << 4;
    texture_v = texture_height << 20;
    depth_bits = (unsigned long)z_value << 32;
    *(int *)(D_L05_001B2C88[0].address + 12) = vif_tag;
    tag = (char *)D_L05_001B2C88[0].address;
    packet = (unsigned long *)(tag + 0x10);
    D_L05_001B2C88[0].address = (int)packet;
    *(unsigned long *)(tag + 0x10) = gif_tag;
    packet[1] = register_list;
    packet[2] = texture_word;
    packet[3] = texture_register;
    packet[4] = color;
    packet[5] = initial_uv;

    {
        int pixel_x = FloatToInt(upper_left[0] * subpixel_scale);
        int pixel_y = FloatToInt(upper_left[1] * subpixel_scale);

        packet[6] = (unsigned long)(pixel_x + gScreenOffsetX - 8) | ((unsigned long)(pixel_y + gScreenOffsetY - 8) << 16) | depth_bits;
        packet[7] = texture_u;
    }
    {
        int pixel_x = FloatToInt(upper_right[0] * subpixel_scale);
        int pixel_y = FloatToInt(upper_right[1] * subpixel_scale);
        packet[8] = (unsigned long)(pixel_x + gScreenOffsetX - 8) | ((unsigned long)(pixel_y + gScreenOffsetY - 8) << 16) | depth_bits;
        packet[9] = texture_v;
    }
    {
        int pixel_x = FloatToInt(lower_left[0] * subpixel_scale);
        int pixel_y = FloatToInt(lower_left[1] * subpixel_scale);
        texture_v = texture_v + texture_u;
        packet[10] = (unsigned long)(pixel_x + gScreenOffsetX - 8) | ((unsigned long)(pixel_y + gScreenOffsetY - 8) << 16) | depth_bits;
        packet[11] = texture_v;
    }
    {
        int pixel_x = FloatToInt(lower_right[0] * subpixel_scale);
        int pixel_y = FloatToInt(lower_right[1] * subpixel_scale);
        packet[13] = 0;
        packet[12] = (unsigned long)(pixel_x + gScreenOffsetX - 8) | ((unsigned long)(pixel_y + gScreenOffsetY - 8) << 16) | depth_bits;
    }

    D_L05_001B2C88[0].address += 0x70;
}
