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
extern int screen_adjust_menu_update_pal (s32_F09f721e0, s32_F09f721e0);
extern s32_F09f721e0 g_screen_adjust_prompt_data __attribute__ ((sda));

/* Sets up the screen adjust menu: prompt bar and its texts, then the first update (PAL). */
void screen_adjust_menu_init_pal (s32_F09f721e0 menu, s32_F09f721e0 owner)
{
  s32_F09f721e0 prompt_bar;
  s32_F09f721e0 alloc;
  s32_F09f721e0 text, second;
  *(s32_F09f721e0 *) menu = owner;
  if (owner != 0)
    {
      alloc = ui_return_second_arg (16, pool_alloc_cell (owner, owner));
      *(s32_F09f721e0 *) (menu + 732) = alloc;
      ((s32_F09f721e0 *) alloc)[1] = 0;
      ((s32_F09f721e0 *) alloc)[2] = 0;
      ((s32_F09f721e0 *) alloc)[3] = 0;
      ((s32_F09f721e0 *) alloc)[0] = 0;
    }
  prompt_bar = menu + 8;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (menu + 732))[0] = 255.0f;
  ((f32_F09f721e0 *) *(s32_F09f721e0 *) (menu + 732))[1] = 195.0f;
  prompt_bar_init_pal (prompt_bar, owner, &g_screen_adjust_prompt_data);
  text = GetLocalizedString (7027);
  second = GetLocalizedString (2911);
  prompt_bar_set_texts_pal (prompt_bar, text, second, GetLocalizedString (2912));
  prompt_bar_set_text_offsets_pal (prompt_bar, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 125.0f);
  prompt_bar_set_spacing_pal (prompt_bar, 0.65f);
  *(s32_F09f721e0 *) (menu + 728) = 0;
  *(s32_F09f721e0 *) (prompt_bar + 716) = 0;
  screen_adjust_menu_update_pal (menu, 0);
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

/* Updates the audio menu: moves the selection, changes the music and sound volumes, toggles subtitles on X (PAL). */
int audio_menu_update_pal(char *menu, int pad_flags)
{
    char *prompt_bar = menu + 8;
    float *vec;

    prompt_bar_update_pal(prompt_bar);
    vec = *(float **)(menu + 0x36C);
    menu_set_anchor_pos(prompt_bar, vec[0], vec[1]);
    vec = *(float **)(menu + 0x36C);
    object_set_first_float4(menu + 0x2DC, vec[0] + g_audio_menu_offset_a,
                 vec[1] + g_audio_menu_offset_b, 0.0f, 0.0f);
    vec = *(float **)(menu + 0x36C);
    object_set_first_float4(menu + 0x324, vec[0] + g_audio_menu_offset_c,
                 vec[1] + g_audio_menu_offset_d, 0.0f, 0.0f);
    if (pad_flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x2D8) = (*(int *)(menu + 0x2D8) + 2) % 3;
    } else if (pad_flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(menu + 0x2D8) = (*(int *)(menu + 0x2D8) + 1) % 3;
    } else if (g_pad_menu_flags.w0 & 0x8000) {
        switch (*(int *)(menu + 0x2D8)) {
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
        switch (*(int *)(menu + 0x2D8)) {
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
    } else if (pad_flags & 0x40) {
        if (*(int *)(menu + 0x2D8) == 2) {
            int value;
            snd_play_from_global_bank(4, 0, 0);
            value = *(int *)(g_subtitles_option + 4) == 0;
            *(int *)(g_subtitles_option + 4) = value;
            snd_send_cmd11_one_value(!value);
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    meter_set_value(menu + 0x324, *(int *)(g_subtitles_option + 8));
    meter_set_value(menu + 0x2DC, *(int *)(g_subtitles_option + 12));
    snd_set_default_group_volumes();
    return (pad_flags >> 6) & 1;
}
