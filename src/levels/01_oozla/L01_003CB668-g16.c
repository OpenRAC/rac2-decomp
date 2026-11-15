#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
extern void gfx_draw_animated_water_background(void), gfx_finish_wave_grid_packet(void);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), FastAddRotations(float, float);
extern void FastVecCross(float *, float *, float *), vec_scale_to_length(float *, float *, float);
extern float FastVecDot(float *, float *);
extern u32 FastTweenColor(unsigned int, unsigned int, float);
extern int D_L01_001B2088;
extern float D_L01_001B0370 __attribute__((sda)), D_L01_001B0378 __attribute__((sda));
extern int D_L01_001B0374 __attribute__((sda)), D_L01_001B037C __attribute__((sda));
extern float D_L01_001B0380 __attribute__((sda)), D_L01_001B0384 __attribute__((sda));
extern float D_L01_001B0388 __attribute__((sda)), D_L01_001B038C __attribute__((sda));
extern short D_L01_00297580[];
extern unsigned int D_L01_00297960[];
extern unsigned char *D_L01_001B036C __attribute__((sda));
/* This routine uses absolute accesses to the real packet cursor. */
extern unsigned char *D_L01_001B2CC8[] __attribute__((sda));
extern unsigned char *D_L01_001B2CC8_gp __asm__("D_L01_001B2CC8") MACRO_ADDR;
/* All are complete 16-byte constants; their observed address forms differ. The MACRO_ADDR ones
   load through an unsplit la: split HIGH/LO_SUM insns would lengthen the packet base's life and
   lower its local-alloc priority below the cursor values, moving it from $a0 to $a1. */
extern Quad D_L01_001B01E0 __attribute__((sda));
extern Quad D_L01_001B01F0 MACRO_ADDR, D_L01_001B0200 MACRO_ADDR, D_L01_001B0210 MACRO_ADDR;
extern Quad D_L01_001B0220 __attribute__((sda)), D_L01_001B0230 __attribute__((sda));
extern Quad D_L01_001B0260 __attribute__((sda)), D_L01_001B0290 __attribute__((sda));
#define APPEND_QUAD(value) { cursor[offset] = (value); offset += 1; D_L01_001B2CC8[0] = (unsigned char *)(cursor + offset); }
/* Builds the animated water wave grid. It works out the height and shading of each grid point, then writes the draw packet. */
void BuildWaveGridPacket(void)
{
    gfx_draw_animated_water_background();
    {
        int i;
        int firstPhase[8], secondPhase[8];
        float firstAngle = (float)(D_L01_001B2088 % (D_L01_001B0374 * 2) - D_L01_001B0374)
            * (3.14159274f / (float)D_L01_001B0374);
        float secondAngle = (float)(D_L01_001B2088 % (D_L01_001B037C * 2) - D_L01_001B037C)
            * (3.14159274f / (float)D_L01_001B037C);
        for (i = 0; i < 8; i++) {
            firstPhase[i] = (int)((math_fast_sin_or_cos_a(firstAngle) + 1.0f) * D_L01_001B0370);
            secondPhase[i] = (int)((math_fast_sin_or_cos_a(secondAngle) + 1.0f) * D_L01_001B0378);
            firstAngle = FastAddRotations(firstAngle, 0.785398006f);
            secondAngle = FastAddRotations(secondAngle, 0.785398006f);
        }
        { int row, col;
        for (row = 0; row < 8; row++)
            for (col = 0; col < 8; col++)
                D_L01_00297580[(row*9+col)*4+2] = (unsigned short)firstPhase[(col + row) & 7]
                    + (unsigned short)secondPhase[(-row) & 7];
        }
        { int j; for (j = 0; j < 36; j += 4) { int index = j + 2; short *p = D_L01_00297580 + index; p[288] = *p; } }
        { int j; for (j = 0; j < 324; j += 36) { int index = j + 2; short *p = D_L01_00297580 + index; p[32] = *p; } }
    }
    {
        int i, j;
        float direction[4] __attribute__((aligned(16)));
        float horizontal[4] __attribute__((aligned(16)));
        float vertical[4] __attribute__((aligned(16)));
        float normal[4] __attribute__((aligned(16)));
        unsigned int shade, target;
        direction[0] = math_fast_sin_or_cos_a(D_L01_001B0384) * math_fast_sin_or_cos_a(D_L01_001B0388);
        direction[1] = math_fast_sin_or_cos_b(D_L01_001B0384) * math_fast_sin_or_cos_a(D_L01_001B0388);
        direction[2] = math_fast_sin_or_cos_b(D_L01_001B0388);
        for (i = 0; i < 8; i++) {
            int palette = ((i + 2) * 128) | 8;
            for (j = 0; j < 8; j++) {
                int k = (i * 9 + j) * 4;
                horizontal[0] = D_L01_001B0380;
                horizontal[1] = 0.0f;
                horizontal[2] = (float)(D_L01_00297580[k + 6] - D_L01_00297580[k + 2]) * 0.0009765625f;
                vertical[0] = 0.0f;
                vertical[1] = D_L01_001B0380;
                vertical[2] = (float)(D_L01_00297580[k + 38] - D_L01_00297580[k + 2]) * 0.0009765625f;
                FastVecCross(normal, vertical, horizontal);
                vec_scale_to_length(normal, normal, 1.0f);
                shade = (int)(FastVecDot(normal, direction) * 128.0f);
                {
                    unsigned int green = (shade << 8) | 0x80000000;
                    unsigned int red = shade << 16;
                    target = red | green;
                    target |= shade;
                }
                D_L01_00297960[(i) * 9 + (j)] = FastTweenColor(
                    *(unsigned int *)(palette + (unsigned int)D_L01_001B036C), target, D_L01_001B038C);
                palette += 4;
            }
        }
        { int k; for (k = 0; k < 9; k++) D_L01_00297960[k + 72] = D_L01_00297960[k]; }
        { int k; for (k = 0; k < 81; k += 9) { unsigned int *p = D_L01_00297960 + k; p[8] = *p; } }
    }
    { Quad *cursor = (Quad *)D_L01_001B2CC8[0]; int offset = 0;
    APPEND_QUAD(D_L01_001B0220);
    APPEND_QUAD(D_L01_001B01E0);
    APPEND_QUAD(D_L01_001B0230);
    APPEND_QUAD(D_L01_001B0260);
    APPEND_QUAD(D_L01_001B0290);
    APPEND_QUAD(D_L01_001B0220);
    APPEND_QUAD(D_L01_001B01F0);
    APPEND_QUAD(D_L01_001B0230);
    APPEND_QUAD(D_L01_001B0260);
    APPEND_QUAD(D_L01_001B0290);
    APPEND_QUAD(D_L01_001B0220);
    APPEND_QUAD(D_L01_001B0200);
    APPEND_QUAD(D_L01_001B0230);
    APPEND_QUAD(D_L01_001B0260);
    APPEND_QUAD(D_L01_001B0290);
    APPEND_QUAD(D_L01_001B0220);
    APPEND_QUAD(D_L01_001B0210);
    APPEND_QUAD(D_L01_001B0230);
    APPEND_QUAD(D_L01_001B0260);
    cursor[offset] = D_L01_001B0290; offset += 1;
    D_L01_001B2CC8_gp = (unsigned char *)(cursor + offset);
    }
    gfx_finish_wave_grid_packet();
}
