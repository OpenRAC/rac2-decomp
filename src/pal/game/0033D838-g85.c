#include "include_asm.h"
#include "names.h"

typedef int s32_F09f721e0;
typedef float f32_F09f721e0;
extern void *pool_alloc_cell (s32_F09f721e0, s32_F09f721e0);
extern void *ui_return_second_arg (s32_F09f721e0, s32_F09f721e0);
extern void prompt_bar_init_pal (s32_F09f721e0, s32_F09f721e0, const void *);
extern char *GetLocalizedString (s32_F09f721e0);
extern void prompt_bar_set_texts_pal (s32_F09f721e0, s32_F09f721e0, s32_F09f721e0, s32_F09f721e0);
extern void prompt_bar_set_text_offsets_pal (s32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0, f32_F09f721e0);
extern void prompt_bar_set_spacing_pal (s32_F09f721e0, f32_F09f721e0);
extern int func_PAL_0033DDC0 (s32_F09f721e0, s32_F09f721e0);
extern s32_F09f721e0 g_screen_adjust_prompt_data __attribute__ ((sda));

void func_PAL_0033DC98 (s32_F09f721e0 self, s32_F09f721e0 arg)
{
  s32_F09f721e0 q;
  s32_F09f721e0 p;
  s32_F09f721e0 a, b;
  *(s32_F09f721e0 *) self = arg;
  if (arg != 0)
    {
      p = ui_return_second_arg (16, pool_alloc_cell (arg, arg));
      *(s32_F09f721e0 *) (self + 732) = p;
      ((s32_F09f721e0 *) p)[1] = 0;
      ((s32_F09f721e0 *) p)[2] = 0;
      ((s32_F09f721e0 *) p)[3] = 0;
      ((s32_F09f721e0 *) p)[0] = 0;
    }
  q = self + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 732))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (self + 732))[1] = 195.0f;
  prompt_bar_init_pal (q, arg, &g_screen_adjust_prompt_data);
  a = GetLocalizedString (7027);
  b = GetLocalizedString (2911);
  prompt_bar_set_texts_pal (q, a, b, GetLocalizedString (2912));
  prompt_bar_set_text_offsets_pal (q, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 125.0f);
  prompt_bar_set_spacing_pal (q, 0.65f);
  *(s32_F09f721e0 *) (self + 728) = 0;
  *(s32_F09f721e0 *) (q + 716) = 0;
  func_PAL_0033DDC0 (self, 0);
}

extern void prompt_bar_update_pal(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern int snd_play_from_global_bank(int, int, void *);
extern void snd_send_cmd11_one_value(int);
extern void meter_set_value(void *, int);
extern void snd_set_default_group_volumes(void);
extern unsigned char g_subtitles_option[] __attribute__((sda));
extern struct { int w0, w1, w2; } g_pad_menu_flags;
extern float g_audio_menu_offset_a __attribute__((sda));
extern float g_audio_menu_offset_c __attribute__((sda));
extern float g_audio_menu_offset_b, g_audio_menu_offset_d;

int func_PAL_0033EEF8(char *object, int flags)
{
    char *p = object + 8;
    float *vec;

    prompt_bar_update_pal(p);
    vec = *(float **)(object + 0x36C);
    menu_set_anchor_pos(p, vec[0], vec[1]);
    vec = *(float **)(object + 0x36C);
    object_set_first_float4(object + 0x2DC, vec[0] + g_audio_menu_offset_a,
                 vec[1] + g_audio_menu_offset_b, 0.0f, 0.0f);
    vec = *(float **)(object + 0x36C);
    object_set_first_float4(object + 0x324, vec[0] + g_audio_menu_offset_c,
                 vec[1] + g_audio_menu_offset_d, 0.0f, 0.0f);
    if (flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 2) % 3;
    } else if (flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 1) % 3;
    } else if (g_pad_menu_flags.w0 & 0x8000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(g_subtitles_option + 12) - 3;
            *(int *)(g_subtitles_option + 12) = value < 0 ? 0 : value;
            break;
        }
        case 1: {
            int value = *(int *)(g_subtitles_option + 8) - 3;
            *(int *)(g_subtitles_option + 8) = value < 0 ? 0 : value;
            break;
        }
        }
    } else if (g_pad_menu_flags.w0 & 0x2000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(g_subtitles_option + 12) + 3;
            *(int *)(g_subtitles_option + 12) = value > 1024 ? 1024 : value;
            break;
        }
        case 1: {
            int value = *(int *)(g_subtitles_option + 8) + 3;
            *(int *)(g_subtitles_option + 8) = value > 1024 ? 1024 : value;
            break;
        }
        }
    } else if (flags & 0x40) {
        if (*(int *)(object + 0x2D8) == 2) {
            int value;
            snd_play_from_global_bank(4, 0, 0);
            value = *(int *)(g_subtitles_option + 4) == 0;
            *(int *)(g_subtitles_option + 4) = value;
            snd_send_cmd11_one_value(!value);
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    meter_set_value(object + 0x324, *(int *)(g_subtitles_option + 8));
    meter_set_value(object + 0x2DC, *(int *)(g_subtitles_option + 12));
    snd_set_default_group_volumes();
    return (flags >> 6) & 1;
}
