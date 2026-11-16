#include "include_asm.h"
#include "names.h"
typedef int s32_Fee27d7bc;
typedef float f32_Fee27d7bc;
extern void *func_00336E40_2 (s32_Fee27d7bc, s32_Fee27d7bc);
extern void *func_00336DA8_2 (s32_Fee27d7bc, s32_Fee27d7bc);
extern void func_0033ABD8_2 (s32_Fee27d7bc, s32_Fee27d7bc, const void *);
extern void func_0033B030_2 (s32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc, f32_Fee27d7bc);
extern void object_init_derived_arrays (s32_Fee27d7bc, const void *, s32_Fee27d7bc);
extern int *func_00335E20_2 (s32_Fee27d7bc);
extern void object_set_helper_result (s32_Fee27d7bc, const void *, s32_Fee27d7bc);
extern void popup_init_texts_hidden (s32_Fee27d7bc);
extern char g_popup_derived_arrays[];
extern s32_Fee27d7bc g_popup_resource_table;
extern s32_Fee27d7bc g_popup_layout_data __attribute__ ((sda));

void popup_init_pal (s32_Fee27d7bc self, s32_Fee27d7bc arg)
{
  s32_Fee27d7bc p;
  *(s32_Fee27d7bc *) self = arg;
  if (arg != 0)
    {
      p = func_00336DA8_2 (16, func_00336E40_2 (arg, arg));
      *(s32_Fee27d7bc *) (self + 804) = p;
      ((s32_Fee27d7bc *) p)[1] = 0;
      ((s32_Fee27d7bc *) p)[2] = 0;
      ((s32_Fee27d7bc *) p)[3] = 0;
      ((s32_Fee27d7bc *) p)[0] = 0;
    }
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (self + 804))[0] = 256.0f;
  ((f32_Fee27d7bc *) *(s32_Fee27d7bc *) (self + 804))[1] = 212.0f;
  *(s32_Fee27d7bc *) (self + 808) = 0;
  func_0033ABD8_2 (self + 8, arg, &g_popup_layout_data);
  func_0033B030_2 (self + 8, 64.0f, -164.0f, 10.0f, 136.0f, 10.0f, 99.0f);
  object_init_derived_arrays (self + 728, g_popup_derived_arrays, arg);
  p = func_00335E20_2 (self + 728);
  *(s32_Fee27d7bc *) p = 0x70FFFEED;
  object_set_helper_result (self + 728, g_popup_resource_table + 0x8710, 214);
  popup_init_texts_hidden (self);
  *(s32_Fee27d7bc *) (self + 816) = 0;
}

extern int g_menu_input_flags[4];
extern int g_popup_label_y_offsets[4] __attribute__((sda));
extern int g_popup_label_x_offset __attribute__((sda));
extern int g_popup_row_spacing __attribute__((sda));
extern void mem_store_two_floats_through_cell(char *, float, float);
extern void prompt_bar_update(char *);
extern int func_002A9588_1(int, int, int, int, int);
extern void *object_get_fourth_field(char *);
extern void func_00335E38_3(char *, float, float, float, float);

int popup_update_position_pal(char *p)
{
    char *a = p + 8;
    char *b;
    void *r;
    float x;
    float y;

    mem_store_two_floats_through_cell(a, ((float *)(*(int *)(p + 804)))[0], ((float *)(*(int *)(p + 804)))[1]);
    prompt_bar_update(a);
    if (g_menu_input_flags[0] & 0x5000)
        func_002A9588_1(0, 0, 1, 0, 1);
    b = p + 728;
    r = object_get_fourth_field(b);
    *(int *)r = func_002A9588_1(0x60442D00, 0x70FFFEED, 20, 0, 0);
    x = ((float *)(*(int *)(p + 804)))[0] + (float)g_popup_label_x_offset;
    y = ((float *)(*(int *)(p + 804)))[1]
        + (float)(*(int *)(p + 808) * g_popup_row_spacing);
    y = y + (float)g_popup_label_y_offsets[0];
    func_00335E38_3(b, x, y, 0.0f, 0.0f);
    return 0;
}
