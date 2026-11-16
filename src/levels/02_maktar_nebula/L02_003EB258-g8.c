#include "names.h"
/* func_L02_003EB258 is a unit of its own: it needs the quadword-copy profile with its barrier,
   -mno-split-addresses for the unsplit lui+lw and la pairs, and -g, which places the nops around
   the div.s (config/cflags.txt).

   D_L02_001B0DA8 is one table of four colors and D_L02_001B0D68 one table of U,V pairs. Retail's
   assembler used $gp only at offset 0, so sym+N came out as lui+lw or lui+addiu; ours would use
   $gp for sym+N too, hence the second names D_L02_001B0DAC and D_L02_001B0D6C.

   `tint` is a real pseudo: it is not allocated, and reload substitutes the symbol at each use, so
   it leaves no code of its own. The compiler still hoists its set into the loop preheader, where
   it separates the U-destination copy from the V-source set. That live length is what gives the
   V source $s7 and the U destination $fp. Direct loads do not: they also move the lui+lw. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    float vertex[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long long state[4];
} SurfacePacket __attribute__((aligned(16)));
extern int g_energy_sheet_textures[2] __attribute__((sda));
extern float g_energy_sheet_uv_table[][2] SDATA(D_L02_001B0D68);
extern float g_energy_sheet_uv_second[][2] __attribute__((sda));
extern unsigned int g_energy_sheet_colors __attribute__((sda));
extern unsigned int g_energy_sheet_tints[] __attribute__((sda));
extern char *g_matrix_l02_record_table;
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern void copy_matrix_rotation(void *, void *);
extern void draw_world_quad(void *, void *, int);

/* Draws a glowing energy sheet made of thin slices, with its colors blending
   between two tints. */
void gfx_draw_energy_sheet(char *actor) {
    SurfacePacket packet[2];
    typedef struct { float weights[2]; } BlendWeights;
    BlendWeights blend;
    BlendWeights calculated __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    char *state = *(char **)(actor + 0x68);
    int i, slice, count;
    float step;
    unsigned int *tint;
    unsigned int mask;
    char *vertex;
    float (*uv)[2] = packet[0].uv;
    {
        int layer;
        for (layer = 0; layer < 2; layer++) gfx_init_quad_packet_state(packet + layer, g_energy_sheet_textures[layer], 0, 0x80);
    }
    calculated.weights[0] = math_fast_sin_or_cos_b(*(float *)(state + 0x14)) * 0.5f + 0.5f;
    calculated.weights[1] = math_fast_sin_or_cos_b(FastAddRotations(*(float *)(state + 0x14), 3.1415927f)) * 0.5f + 0.5f;
    blend = calculated;
    count = FloatToInt(FastVecLength(g_matrix_l02_record_table + *(int *)(state + 8) * 0x80 + 0x10));
    *(Quad *)normal = 0;
    normal[3] = 1.0f;
    step = 2.0f / (float)count;
    mask = 0x00FFFFFF;
    for (i = 0, vertex = (char *)&packet; i < 4; vertex += 16, i++) {
        uv[i][0] = g_energy_sheet_uv_table[i][0];
        packet[0].uv[i][1] = g_energy_sheet_uv_second[i][0];
        packet[1].uv[i][0] = g_energy_sheet_uv_table[i+4][0] + *(float *)(state + 0x18);
        packet[1].uv[i][1] = g_energy_sheet_uv_second[i+4][0];
        tint = g_energy_sheet_tints;
        packet[0].color[i] = FastTweenColor(g_energy_sheet_colors, tint[0], blend.weights[0]);
        packet[1].color[i] = FastTweenColor(tint[1], tint[2], blend.weights[1]);
        if (*(float *)(state + 0x1C) < 1.0f) {
            packet[0].color[i] = FastTweenColor(packet[0].color[i] & mask, packet[0].color[i], *(float *)(state + 0x1C));
            packet[1].color[i] = FastTweenColor(packet[1].color[i] & mask, packet[1].color[i], *(float *)(state + 0x1C));
        }
        qcopy(vertex, normal);
        if (i >= 2) *(float *)vertex = -1.0f; else *(float *)vertex = 1.0f;
        *(float *)(vertex + 4) = (i & 1) ? -1.0f : step + -1.0f;
        qcopy(packet[1].vertex[i], normal);
        if (i >= 2) *(float *)(vertex + 0x90) = -1.0f; else *(float *)(vertex + 0x90) = 1.0f;
        *(float *)(vertex + 0x94) = (i & 1) ? -1.0f : step + -1.0f;
    }
    copy_matrix_rotation(matrix, g_matrix_l02_record_table + *(int *)(state + 8) * 0x80);
    qcopy(matrix + 12, g_matrix_l02_record_table + *(int *)(state + 8) * 0x80 + 0x30);
    for (slice = 0; slice < count; slice++) {
        draw_world_quad(packet, matrix, 0);
        draw_world_quad(packet + 1, matrix, 0);
        {
        int j;
        char *sliceVertex = (char *)&packet;
        for (j = 0; j < 4; j++, sliceVertex += 16) {
            *(float *)(sliceVertex + 4) += step;
            *(float *)(sliceVertex + 0x94) += step;
        }
        }
    }
}
