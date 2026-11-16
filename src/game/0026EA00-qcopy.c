#include "include_asm.h"
#include "common.h"

/* The three resident copy helpers in this unit need the grouped `lq`/`sq`
   profile with its scheduler barrier (-frac2-qcopy -frac2-qcopy-barrier). */

typedef int TI128 __attribute__((mode(TI)));

extern char g_camera_mode_state[];
extern char g_camera_basis_vectors[];
extern int cam_advance_blend(void *, void *);
extern int cam_advance_orbit_transition(void *, void *);

/* Runs the current object through the resident visibility test, then copies
   its four 16-byte blocks into the resident snapshots and clears the test
   state. */
void moby_test_and_snapshot(char *object)
{
    unsigned char *state = (unsigned char *)g_camera_mode_state;
    char *dest;
    int ok;

    if (state[2] == 0)
        ok = cam_advance_blend(object, state + 0x10);
    else
        ok = cam_advance_orbit_transition(object, state + 0x70);
    if (ok == 0)
        return;

    dest = g_camera_basis_vectors;
    *(TI128 *)(dest + 0x00) = *(TI128 *)object;
    *(TI128 *)(dest + 0x10) = *(TI128 *)(object + 0x10);
    *(TI128 *)(dest + 0x20) = *(TI128 *)(object + 0x20);
    *(TI128 *)(dest - 0x230) = *(TI128 *)(object + 0x30);
    *(short *)state = 0;
    state[2] = 0;
}

/* Copies the resident object's saved vectors back into its working ones. */
void moby_restore_vectors(void)
{
    unsigned char *object = (unsigned char *)g_camera_mode_state;

    if (object[2] != 0) {
        *(TI128 *)(object + 0x50) = *(TI128 *)(object + 0xC0);
        *(TI128 *)(object + 0x60) = *(TI128 *)(object + 0xD0);
    }
}

extern char g_hero_velocity[];
extern void FastVecAdd(char *first, char *second, char *third);

/* Copies the resident object's two vectors and asks the engine to rebuild its
   matrix when the object's type says so. */
void moby_save_vectors(void)
{
    unsigned char *object = (unsigned char *)g_camera_mode_state;

    if (object[2] == 0) {
        *(TI128 *)(object + 0xC0) = *(TI128 *)(object + 0x50);
        if (object[3] == 2)
            FastVecAdd((char *)(object + 0xC0), g_hero_velocity, (char *)(object + 0xC0));
        *(TI128 *)(object + 0xD0) = *(TI128 *)(object + 0x60);
    }
}

typedef struct {
    char pad00[0x20];
    unsigned char *obj;
    short flag;
    char pad26[10];
} F273418Mark;

typedef struct {
    F273418Mark e[6];
    int count;
} F273418Marks;

extern int g_game_mode;
extern int g_reticle_screen_params[] __attribute__((sda));
extern F273418Marks g_hud_reticle_marks;
extern void DrawTargetReticle(void);
extern void gfx_project_world_point_to_screen(void *, void *);
extern void gfx_draw_screen_sprite(void *, float, float);
extern float IntToFloat(int);

/* Draws the reticle, then draws each marker on the screen at its projected spot. */
void hud_draw_reticle_and_markers(void) {
    float base[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    F273418Mark *m;
    int i;

    if (g_game_mode == 111) {
        g_hud_reticle_marks.count = 0;
        return;
    }
    DrawTargetReticle();
    if (g_hud_reticle_marks.count != 0) {
        base[0] = IntToFloat(g_reticle_screen_params[0]);
        base[1] = IntToFloat(g_reticle_screen_params[1]);
        for (i = 0; i < g_hud_reticle_marks.count; i++) {
            m = &g_hud_reticle_marks.e[i];
            if (m->obj != 0 && m->obj[0x20] != 0xFE && m->obj[0x20] != 0xFD) {
                if (m->flag != 0) {
                    gfx_project_world_point_to_screen(vec, m);
                    vec[0] = (vec[0] - IntToFloat(g_reticle_screen_params[2])) * 0.0625f;
                    vec[1] = (vec[1] - IntToFloat(g_reticle_screen_params[3])) * 0.0625f;
                } else {
                    qcopy(vec, base);
                }
                gfx_draw_screen_sprite(m, vec[0], vec[1]);
            }
        }
        g_hud_reticle_marks.count = 0;
    }
}

extern char g_active_camera[];
extern char g_camera_state_block[];
extern unsigned char g_cheat_flags[] __attribute__((sda));
extern void cam_update_scalar_transition(void);
extern void cam_update_second_scalar_transition(void);
extern void cam_select_coll_masks(void);
extern void cam_update_follow_hero(void);
extern int cam_update_active(void);
extern void cam_begin_mode_change(void *);
extern int stub_empty_21(void);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern void cam_update_shake(void *, int);
extern void cam_update_grounded(void);
extern void gfx_blend_fog_from_cam_region(void *);
extern void cam_update_fov_transition(void);

/* Updates the camera state each frame: copies the target object's vectors into it and rebuilds its derived vectors. */
void cam_update_state(void) {
    char *camera = g_active_camera;
    char *target;
    char *vectors;
    char *tail;
    char *unused;

    *(int *)(camera + 0x404) = *(int *)(camera + 0x404) + 1;
    cam_update_scalar_transition();
    cam_update_second_scalar_transition();
    cam_select_coll_masks();
    cam_update_follow_hero();
    cam_update_active();
    target = *(char **)(camera + 0x190);
    if ((unsigned)(*(unsigned short *)(camera + 0x290) - 1) < 2)
        cam_begin_mode_change(*(void **)(camera + 0x194));
    if (*(short *)(camera + 0x290) == 3) {
        moby_test_and_snapshot(target);
    } else {
        qcopy(camera + 0x140, target + 0x30);
        qcopy(camera + 0x370, target);
        qcopy(camera + 0x380, target + 0x10);
        qcopy(camera + 0x390, target + 0x20);
    }
    if (stub_empty_21()) {
        vectors = g_active_camera + 0x140;
        qcopy(vectors, g_camera_state_block);
        qcopy(vectors + 0x230, g_camera_state_block + 0x10);
        FastVecCross(vectors + 0x240, vectors + 0x230, g_camera_state_block - 0x14B0);
        vec_scale_to_length(vectors + 0x240, vectors + 0x240, 1.0f);
        FastVecCross(vectors + 0x250, vectors + 0x240, vectors + 0x230);
        vec_scale_to_length(vectors + 0x250, vectors + 0x250, 1.0f);
    }
    tail = g_active_camera + 0x370;
    mat_get_euler_angles(tail, tail - 0x220);
    cam_update_shake(tail - 0x210, 0);
    cam_update_shake(tail - 0x200, 1);
    cam_update_shake(tail - 0x1F0, 2);
    cam_update_grounded();
    gfx_blend_fog_from_cam_region(tail - 0x230);
    if (g_cheat_flags[0])
        FastVecCross(tail + 0x10, tail + 0x20, tail);
    cam_update_fov_transition();
    qzero(tail + 0x50);
}
