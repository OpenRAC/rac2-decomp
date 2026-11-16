#include "common.h"

/* the level's table of two floats */
typedef struct {
    u8  pad00[0x10];
    f32 field10;
    f32 field14;
} L04Table;

/* the level's lighting values; the fields are reached as symbol+offset, which this
   compiler keeps out of delay slots */
typedef struct {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u8  pad18[4];
    f32 f1C;
    u8  pad20[4];
    u32 f24;
    u32 f28;
    f32 dir[3];
    u8  f38;
    u8  f39;
} L04Lighting;

extern L04Table ref_L04_003A1868_00;
extern L04Lighting ref_L04_003A1868_01 MACRO_ADDR;
extern f32 ref_L04_003A1868_02 __attribute__((sda));
extern f32 ref_L04_003A1868_03 __attribute__((sda));
extern f32 ref_L04_003A1868_04 __attribute__((sda));
extern f32 ref_L04_003A1868_05 __attribute__((sda));
extern u32 ref_L04_003A1868_06 __attribute__((sda));
extern void *ref_L04_003A1868_07[3] MACRO_ADDR;

extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 math_fast_sin_or_cos_a(f32 a);
extern f32 math_fast_sin_or_cos_b(f32 a);

/* Sets the level's lighting values: the light direction comes from the angle
   func_00283248 gives for the table's two floats, scaled by 1/sqrt(3). Stores
   its three arguments in the level's pointer table. */
/* Sets up the level lighting: one sun direction and its colours. */
void level_setup_lighting(void *first, void *second, void *third) {
    L04Table *table = &ref_L04_003A1868_00;
    f32 angle;
    f32 scale;

    ref_L04_003A1868_02 = 16.0f;
    ref_L04_003A1868_01.f00 = 16.0f;
    ref_L04_003A1868_01.f04 = -8.0f;
    ref_L04_003A1868_01.f08 = -8.0f;
    ref_L04_003A1868_01.f0C = 1.0f;
    ref_L04_003A1868_01.f10 = 1.0f;
    ref_L04_003A1868_01.f14 = 0.9f;
    ref_L04_003A1868_01.f1C = 0.1f;
    angle = mat_fast_helper_a(table->field10, table->field14);
    scale = 0.57735f;
    ref_L04_003A1868_01.dir[0] = math_fast_sin_or_cos_a(angle) * scale;
    ref_L04_003A1868_01.dir[1] = math_fast_sin_or_cos_b(angle) * scale;
    ref_L04_003A1868_01.dir[2] = -0.57735f;
    ref_L04_003A1868_01.f24 = 63;
    ref_L04_003A1868_01.f28 = 64;
    ref_L04_003A1868_01.f38 = 127;
    ref_L04_003A1868_01.f39 = 127;
    ref_L04_003A1868_03 = 32768.0f;
    ref_L04_003A1868_04 = 255.0f;
    ref_L04_003A1868_05 = 48.0f;
    ref_L04_003A1868_06 = 0;
    ref_L04_003A1868_07[0] = first;
    ref_L04_003A1868_07[1] = second;
    ref_L04_003A1868_07[2] = third;
}

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l04_source_entries[];
extern char g_menu_l04_entry_callback[];
extern InitEntry12 g_menu_l04_entry_list[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_volatile_ptr __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l04_state;
