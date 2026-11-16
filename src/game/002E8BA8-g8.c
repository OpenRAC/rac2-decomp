#include "common.h"

extern char g_str_transition_debug[];
typedef struct { char pad[0xB0]; float value; } Camera;
extern Camera g_view_params;
typedef struct { char pad[0x64]; int variant; } SceneMenu;
extern SceneMenu g_hero_moby_default;
typedef struct { char pad[0x34]; int frame; char pad38[0x154]; char *first; } Scene;
extern Scene g_scene_playback_state;
typedef struct { char pad[0x15C]; int mode; int pad160; int next; } Control;
extern Control g_memcard_state;
extern char *g_transition_effect_list MACRO_ADDR;
extern int g_frame_counter_3 MACRO_ADDR, g_transition_force_flag MACRO_ADDR;
extern int g_gfx_pass_mode __attribute__((sda));
extern float g_screen_fade MACRO_ADDR;
extern int g_screen_height;
extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_build_view_matrices(void);
extern void moby_update_watched_objects(void);
extern void gfx_write_clear_color_packets(void);
extern void UpdateViewContext(void);
extern void cam_build_view_transforms(void);
extern void SetupGifPaging(int);
extern void gfx_draw_overlay_quads(void);
extern void DoGifPaging(void);
extern void tex_upload_main_textures(void);
extern void append_dma_tag(int);
extern void gfx_draw_fade_strip(int);
extern void ship_draw_engine_flames(void *);
extern void render_environment_mapped_object(void *);
extern void part_draw_effect_records(void);
extern void STUB_printf(void *,int,int);
extern void ship_spawn_thruster_particles(void *);
extern void VU1_addGSregister(unsigned int,unsigned long long);
extern void gfx_wait_for_dma_status_bits(unsigned long long);
extern void PatchMobyGifs(void);
extern void gfx_set_clear_color_packet(int,int,int,int);
extern unsigned long long GetEffectTextureDescriptor(int);
extern int FloatToInt(float);
extern void DrawTexturedQuad(int,int,int,int,int,int,int,int,unsigned long long,unsigned long long);
extern void DrawRotatedSprite(float,float,float,float,float,int,int,unsigned long long);
#define H(p,o) (*(short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))

/* Renders the transition scene, its loading indicator and the final fade. */
void transition_render_scene(void) {
    float saved;
    char *object;
    int alpha;
    gfx_append_draw_list_buffer_tag(0);
    gfx_build_view_matrices();
    moby_update_watched_objects();
    gfx_write_clear_color_packets();
    saved = g_view_params.value;
    g_gfx_pass_mode = -1;
    if (saved<0.62f) g_view_params.value = 0.62f;
    UpdateViewContext();
    gfx_build_view_matrices();
    cam_build_view_transforms();
    g_view_params.value = saved;
    UpdateViewContext();
    gfx_build_view_matrices();
    if (g_hero_moby_default.variant==4) {
        SetupGifPaging(1);
        gfx_draw_overlay_quads();
        DoGifPaging();
    }
    tex_upload_main_textures();
    append_dma_tag(0x2080000);
    SetupGifPaging(1);
    if (g_hero_moby_default.variant==4 && g_scene_playback_state.frame>60) {
        alpha = (g_scene_playback_state.frame-60)*2;
        if (alpha>128) alpha = 128;
        gfx_draw_fade_strip(alpha);
    }
    if (!g_transition_effect_list || H(g_transition_effect_list, 0xAA)==0xD54 /* moby class 3412 */) {
        object = g_scene_playback_state.first;
        if (B(object, 0x95)>16) {
            ship_draw_engine_flames(object);
            render_environment_mapped_object(object);
            part_draw_effect_records();
        }
        else STUB_printf(g_str_transition_debug, B(object, 0x95), g_frame_counter_3);

    } else if (B(g_scene_playback_state.first, 0x95)>16) part_draw_effect_records();
    if (g_transition_effect_list && ((unsigned short)(H(g_transition_effect_list, 0xAA)-0x128C /* moby class 4748 */)<2 || H(g_transition_effect_list, 0xAA)==0x1342 /* moby class 4930 */)) ship_spawn_thruster_particles(g_transition_effect_list);
    if ((unsigned int)(g_memcard_state.mode-15)<2 || g_memcard_state.next==15 || g_transition_force_flag) {
        float y, angle;
        VU1_addGSregister(0x47, 0x3004B);
        DrawTexturedQuad(0x2C, g_screen_height-0x60, 64, 64, 0, 0, 64, 64, 0x80808080ULL, GetEffectTextureDescriptor(3));
        y = (float)((g_screen_height-0x40)<<4);
        angle = (g_frame_counter_3%55)*-0.11423972994f;
        DrawRotatedSprite(1216.0f, y, 272.0f, 272.0f, angle, 64, 64, GetEffectTextureDescriptor(4));
        if ((unsigned int)(g_memcard_state.mode-15)<2 || g_memcard_state.next==15) g_transition_force_flag = 30;
        else g_transition_force_flag = g_transition_force_flag-1;
    }
    DoGifPaging();
    if (g_screen_fade>0.0f) {
        if (g_screen_fade>1.0f) g_screen_fade = 1.0f;
        gfx_set_clear_color_packet(0, 0, 0, FloatToInt(g_screen_fade*128.0f));
    }
    gfx_wait_for_dma_status_bits(16);
    PatchMobyGifs();
}
