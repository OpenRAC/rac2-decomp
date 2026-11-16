#include "common.h"

typedef struct { float x, y, z, w; } QuadPoint;
extern void gfx_setup_offscreen_target(int, int, float);
extern void gfx_call_sync_helper(void);
extern void VU1_addGSregister(unsigned int, unsigned long);
/* Snapshot the view, render the selected object into a texture, then draw
   its four-corner world-space quad after restoring the view. */
typedef struct {
    QuadPoint vertices[4];
    unsigned int colors[4];
    float uv[4][2];
    unsigned long state[4];
} CaptureQuad;
typedef struct { char pad[0x34]; unsigned short flags; } CaptureMoby;
typedef struct { QuadPoint position; float angles[4]; QuadPoint vertices[4]; float width, height; CaptureMoby *moby; } CaptureObject;
typedef struct { char pad[0x50]; CaptureObject *capture; } CaptureState;
extern CaptureState g_scene_playback_state;
typedef struct {
    char reserved0[0x140];
    QuadPoint position;
    char reserved150[0x370 - 0x150];
    QuadPoint matrix[4];
} CaptureCamera;
extern CaptureCamera g_active_camera;
typedef struct { char pad[0xB0]; float scale; } CaptureView;
extern CaptureView g_view_params;
extern char g_preview_camera_matrix[];
extern QuadPoint g_preview_quad_a __attribute__((sda));
extern QuadPoint g_preview_quad_b __attribute__((sda));
extern QuadPoint g_preview_quad_c __attribute__((sda));
extern QuadPoint g_preview_quad_d __attribute__((sda));
extern float g_preview_quad_u[4] __attribute__((sda));
extern float g_preview_quad_v[4] __attribute__((sda));
extern unsigned long g_quad_texture[] __attribute__((sda));
extern int g_object_preview_scene[] __attribute__((sda));
extern void DrawMobysSetup(void), mem_fill_scratch_area(void), mem_save_scratch_area(void);
extern void tex_upload_object_textures(void *, int);
extern void mem_fast_helper_c(void *, void *, int);
extern void func_00129178(void *);
extern void pad_vib_routine_f(void *, void *, float);
extern void pad_vib_routine_g(void *, void *, float);
extern void pad_vib_routine_e(void *, void *, float);
extern void gfx_build_view_matrices(void);
extern void gfx_pack_render_command_fields(void *, int, int, int, int);
extern void UpdateViewContext(void), mem_restore_scratch_area(void), tex_upload_main_textures(void);
extern void gfx_append_vu1_preset_a(void);
extern int tex_run_upload_and_setup(void);
extern void draw_world_quad(void *, int, int);

/* Draws the selected object into a small texture, then shows that texture as a flat picture on screen. */
void gfx_render_object_preview_to_texture(void)
{
    CaptureObject *object = g_scene_playback_state.capture;
    QuadPoint saved_matrix[4], saved_position, matrix[4];
    CaptureQuad quad;
    if (object) {
        CaptureMoby *moby = object->moby;
        QuadPoint *position = &object->position;
        char *view_matrix;
        char *view_position;
        float saved_scale;
        void *scene;
        int i;
        DrawMobysSetup();
        mem_fill_scratch_area();
        mem_save_scratch_area();
        scene = (void *)g_object_preview_scene[1];
        moby->flags |= 1;
        tex_upload_object_textures(scene, -1);
        moby->flags &= ~1;
        view_matrix = (char *)&g_active_camera + 0x370;
        mem_fast_helper_c(saved_matrix, view_matrix, 0x40);
        do { view_position = view_matrix - 0x230; } while (0);
        qcopy(&saved_position, view_position);
        saved_scale = g_view_params.scale;
        gfx_setup_offscreen_target(8, 8, 1.0f);
        func_00129178(matrix);
        pad_vib_routine_f(matrix, matrix, object->angles[0]);
        pad_vib_routine_g(matrix, matrix, object->angles[1]);
        pad_vib_routine_e(matrix, matrix, object->angles[2]);
        mem_fast_helper_c(view_matrix, matrix, 0x40);
        qcopy(view_position, position);
        gfx_build_view_matrices();
        gfx_pack_render_command_fields(moby, 0x404040, 0xE, 0, 0);
        qcopy(g_preview_camera_matrix, &g_preview_quad_a);
        qcopy(g_preview_camera_matrix + 0x20, &g_preview_quad_b);
        qcopy(g_preview_camera_matrix + 0x10, &g_preview_quad_c);
        qcopy(g_preview_camera_matrix + 0x30, &g_preview_quad_d);
        tex_upload_object_textures(moby, 1); gfx_call_sync_helper();
        g_view_params.scale = saved_scale;
        UpdateViewContext();
        mem_fast_helper_c(view_matrix, saved_matrix, 0x40);
        qcopy(view_position, &saved_position);
        gfx_build_view_matrices();
        VU1_addGSregister(0x42, 0x8000000044UL); VU1_addGSregister(8, 5);
        gfx_append_vu1_preset_a(); mem_restore_scratch_area(); tex_run_upload_and_setup();
        quad.state[1] = g_quad_texture[0];
        quad.state[2] = 0xFF9000000260UL;
        quad.state[0] = 5;
        quad.state[3] = 0x8000000044UL;
        for (i = 0; i < 4; i++) {
            quad.colors[i] = 0x80808080;
            quad.uv[i][0] = object->width * g_preview_quad_u[i] + 0.5f;
            quad.uv[i][1] = object->height * g_preview_quad_v[i] + 0.5f;
            qcopy(&quad.vertices[i], &object->vertices[i]);
        }
        draw_world_quad(&quad, 0, 0);
    } else tex_upload_main_textures();
}
