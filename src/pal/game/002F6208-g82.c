#include "include_asm.h"

#include "common.h"
extern void UpdateViewContext(void);
#include "common.h"
typedef struct { u8 pad00[0xC]; u8 kind; u8 pad0D[3]; f32 w0[4]; } CamRec_2F5AF8;
typedef struct { u8 pad00[0x38]; s32 index; u8 pad3C[0x68 - 0x3C]; CamRec_2F5AF8 *recs; } CamList_2F5AF8;
typedef struct { u8 pad[0xB0]; f32 scale; } CamView_2F5AF8;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x370 - 0x150];
    f32 row0[3];
    f32 pad37C;
    f32 row1[3];
    f32 pad38C;
    f32 row2[3];
} Cam_2F5AF8;
extern CamList_2F5AF8 g_scene_playback_state;
extern CamView_2F5AF8 g_view_params;
extern Cam_2F5AF8 g_active_camera;
extern u8 g_unlocked_item_flags;
extern f32 g_cutscene_camera_scale;
extern f32 g_cutscene_camera_blend;
extern f32 g_camera_shake_states[12];
extern void UpdateViewContext(void);
extern void func_00129178(f32 *);
extern void pad_vib_routine_f(f32 *, f32 *, f32);
extern void pad_vib_routine_g(f32 *, f32 *, f32);
extern void pad_vib_routine_e(f32 *, f32 *, f32);
extern void vec_scale_to_length(f32 *, f32 *, f32);
extern void FastVecSub(f32 *, f32 *, f32 *);
extern void cam_update_shake_pal(f32 *, int);

u8 cutscene_apply_camera_key_pal(void)
{
    f32 m[16] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    CamRec_2F5AF8 *rec;
    f32 *w;
    f32 scale;
    f32 k;
    u8 kind;

    rec = &g_scene_playback_state.recs[g_scene_playback_state.index];
    w = rec->w0;
    kind = rec->kind;
    scale = w[3];
    g_view_params.scale = scale;
    if (g_unlocked_item_flags != 0)
        g_view_params.scale = scale * g_cutscene_camera_scale;
    UpdateViewContext();
    qcopy(g_active_camera.pos, rec);
    func_00129178(m);
    pad_vib_routine_f(m, m, w[0]);
    pad_vib_routine_g(m, m, w[1]);
    pad_vib_routine_e(m, m, w[2]);
    g_active_camera.row0[0] = -m[8];
    g_active_camera.row1[0] = -m[0];
    g_active_camera.row2[0] = m[4];
    g_active_camera.row0[1] = -m[9];
    g_active_camera.row1[1] = -m[1];
    g_active_camera.row2[1] = m[5];
    g_active_camera.row0[2] = -m[10];
    g_active_camera.row1[2] = -m[2];
    g_active_camera.row2[2] = m[6];
    if (g_unlocked_item_flags != 0 && (k = g_cutscene_camera_blend) != 0.0f) {
        qcopy(t, g_active_camera.row0);
        vec_scale_to_length(t, t, k);
        FastVecSub(g_active_camera.pos, g_active_camera.pos, t);
    }
    cam_update_shake_pal(&g_camera_shake_states[0], 0);
    cam_update_shake_pal(&g_camera_shake_states[4], 1);
    cam_update_shake_pal(&g_camera_shake_states[8], 2);
    return kind;
}
