#include "include_asm.h"

/* Level reset: frees the two sound handles, restores the camera pose from the 16-byte
   default (a quadword copy of the small-data vector, so this unit is built with -G16). */
#include "common.h"
typedef struct { char pad[0x28]; char *obj; char pad2[0x60 - 0x2C]; int f60; char pad3[0x78 - 0x64]; int sound_handle1; int sound_handle2; char pad4[0x8C - 0x80]; int f8C; } Reset2F8768;
typedef struct { float v[4]; } Vec4_2F8768 __attribute__((aligned(16)));
typedef struct { char pad[0x72]; unsigned short mode; } Mode2F8768;
extern Reset2F8768 g_vendor_menu_state;
extern Mode2F8768 g_music_state;
extern char g_hero_state[];
extern int g_current_game_mode __attribute__((sda));
extern Vec4_2F8768 g_shop_camera_vec __attribute__((sda));
extern void set_animation_parameter(int, int);
extern void hud_tick_countdown(void);
extern unsigned int stub_empty_8(int, int);
extern void stub_empty_4(void);
extern void stub_empty_14(char *, void *, int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void cam_set_mode_state(int);
extern void shop_clear_preview(void);
extern void moby_mark_spawned(void *);
extern void snd_send_cmd23(int);
extern void music_Unpause(void);
extern int snd_Pump(void);

void shop_reset_menu_camera(void)
{
    Vec4_2F8768 out;
    float dir[4];
    Vec4_2F8768 in;

    if (g_vendor_menu_state.sound_handle2 != -1)
        set_animation_parameter(g_vendor_menu_state.sound_handle2, 0);
    if (g_vendor_menu_state.sound_handle1 != -1)
        set_animation_parameter(g_vendor_menu_state.sound_handle1, 0);
    g_vendor_menu_state.sound_handle2 = -1;
    g_vendor_menu_state.sound_handle1 = -1;
    hud_tick_countdown();
    g_current_game_mode = 0;
    stub_empty_8(0, 1);
    g_hero_state[0x22B5] = 0;
    stub_empty_4();
    if (g_vendor_menu_state.f60 == 0) {
        qcopy(&in, &g_shop_camera_vec);
        matrix_mul_vec3(&out, &in, g_vendor_menu_state.obj + 0xC0);
        FastVecAdd(&out, &out, g_vendor_menu_state.obj + 0x10);
        dir[0] = 0;
        dir[1] = 0;
        dir[2] = FastAddRotations(*(float *)(g_vendor_menu_state.obj + 0xF8), 3.1415927f);
        stub_empty_14((char *)&out, dir, 0, 0);
        cam_set_mode_state(2);
    }
    g_vendor_menu_state.obj[0x20] = 1;
    if ((unsigned short)(g_music_state.mode - 6) >= 2)
        g_music_state.mode = 5;
    if (g_vendor_menu_state.f8C != 0)
        shop_clear_preview();
    if (g_vendor_menu_state.f60 != 0)
        moby_mark_spawned(g_vendor_menu_state.obj);
    snd_send_cmd23(0x5D);
    music_Unpause();
    snd_Pump();
}
