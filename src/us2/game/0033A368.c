#include "include_asm.h"
#include "names.h"

typedef struct { float x, y; } Float2_00339320;
typedef struct {
    char pad[0x1C8];
    unsigned short count;
    unsigned short unused;
    unsigned int maximum;
    unsigned int levels;
} Statistics_00339320;
extern void object_set_first_float4(void *, float, float, float, float);
extern int text_format_location_name(void *, int);
extern Float2_00339320 ref_L00_0042EC50_00;
extern Float2_00339320 ref_L00_0042EC50_01;
extern Float2_00339320 ref_L00_0042EC50_02;
extern int g_game_time __attribute__((sda));
extern int D_001C51D0;
extern unsigned int D_001A7390 __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern Statistics_00339320 g_progress_statistics;

/* Places the seven sub-objects of the argument at their world positions, hands the
   current level to the one at +0x258, and updates the statistics block: the visit
   count once the game time has reached 11, the highest level number seen and the
   bit of the level that was reached. */
int func_US2_0033A368(char *a0)
{
    Float2_00339320 z0 = {0.0f, 0.0f};
    Float2_00339320 z1 = {0.0f, 0.0f};
    Float2_00339320 z2 = {0.0f, 0.0f};
    Float2_00339320 z3 = {0.0f, 0.0f};
    Float2_00339320 g0 = ref_L00_0042EC50_00;
    Float2_00339320 g1 = ref_L00_0042EC50_01;
    Float2_00339320 g2 = ref_L00_0042EC50_02;

    object_set_first_float4(a0 + 8, z0.x + (*(float **)(a0 + 4))[0], z0.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(a0 + 0x54, z3.x + (*(float **)(a0 + 4))[0], z3.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(a0 + 0xA0, z1.x + (*(float **)(a0 + 4))[0], z1.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(a0 + 0xEC, z2.x + (*(float **)(a0 + 4))[0], z2.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(a0 + 0x138, g0.x + (*(float **)(a0 + 4))[0], g0.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(a0 + 0x190, g1.x + (*(float **)(a0 + 4))[0], g1.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    object_set_first_float4(a0 + 0x1E8, g2.x + (*(float **)(a0 + 4))[0], g2.y + (*(float **)(a0 + 4))[1], 0.0f, 0.0f);
    text_format_location_name(a0 + 0x298, D_001C51D0);
    if (g_game_time >= 11) {
        if (g_progress_statistics.count < 0xffff) g_progress_statistics.count++;
    }
    if (D_001A7390 > g_progress_statistics.maximum) g_progress_statistics.maximum = D_001A7390;
    g_progress_statistics.levels = (g_progress_statistics.levels | (1u << g_current_map_index)) | 0x80000000u;
    return 0;
}

