#include "names.h"
/* func_PAL_L01_002F3E90, the PAL copy of func_L01_002F2570: the same C, where the frame limits take the
   50 Hz scale, the step and angle constants change, and the third actor test also requires D_001A79F0 != 0x33. */
typedef int Quadword __attribute__((mode(TI)));
/* The clear proves an 80-byte state span; this view covers that span. */
typedef struct TrailCamera {
    float target[4];
    float position[4];
    float unused20;
    float distance;
    unsigned char tail[0x28];
} TrailCamera;

/* Resident view through the transform used here; later fields are not described. */
typedef struct HeroView {
    char prefix[0x5C0];
    char *camera;
    char gap5C4[0x16C];
    float transform[16];
} HeroView;
extern HeroView g_hero_state;
extern int g_current_map_index;
extern int g_oozla_intro_frame_start __attribute__((sda));
extern int g_oozla_intro_frame_end __attribute__((sda));
extern int g_oozla_intro_started;
typedef struct SceneManager {
    char prefix[0x30];
    int mode;
    int frame;
    char gap38[0xC];
    short count;
    char gap46[0x146];
    char *entries[0];
} SceneManager;
extern SceneManager g_ship_trail_state;
extern TrailCamera g_trail_camera;

extern void anim_start_startup_animations(void);
extern void update_equipment_pieces_pal(char *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern void mem_clear(void *, unsigned int, int);
extern void euler_rotation_basis(void *, void *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void initialize_bolt_point_chain_pal(char *);
extern void beam_update_chain_points_pal(char *);
extern void beam_draw_ribbons_level_pal(void *);
extern void ship_build_trail_mesh(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern char *tv_screen_find_nearest(float, float, float);

/* Per-frame update of the Oozla intro scene: sets up the scene objects and moves the ship trail camera (PAL: 50 Hz frame limits). */
void oozla_intro_scene_update_pal(void)
{
    int i;
    char *actor;
    char *trail;
    Quadword angle;

    anim_start_startup_animations();
    for (i = 0; i < g_ship_trail_state.count; ++i) {
        actor = g_ship_trail_state.entries[i];
        if (actor && *(short *)(actor + 0xAA) == 0xE29) {
            *(unsigned short *)(actor + 0x34) |= 0x800;
        }
        if (*(short *)(actor + 0xAA) == 0xD54)
            update_equipment_pieces_pal(actor);
        if (actor) {
            int kind = 0xFA0; /* MOBY_CLASS_TV_SCREENS */
            if (*(short *)(actor + 0xAA) == kind && g_current_map_index != 0x33 && *(char **)(actor + 0x68))
                math_store_angle_update_result(actor, (float *)(*(char **)(actor + 0x68) + 0xC),
                                 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }

    if (g_current_map_index == 1) {
        if (g_ship_trail_state.mode == 1) {
            TrailCamera *camera = &g_trail_camera;
            g_hero_state.camera = g_ship_trail_state.entries[2];
            trail = g_ship_trail_state.entries[3];
            if (g_ship_trail_state.frame == (((int)(g_oozla_intro_frame_start) * 5 + 2) / 6)) {
                mem_clear(camera, 0, sizeof(TrailCamera));
                g_oozla_intro_started = 1;
                camera->distance = 0.8f;
            }
            if ((((int)(g_oozla_intro_frame_start) * 5 + 2) / 6) < g_ship_trail_state.frame &&
                g_ship_trail_state.frame < (((int)(g_oozla_intro_frame_end) * 5 + 2) / 6)) {
                angle = 0;
                ((float *)&angle)[2] = -0.13f;
                euler_rotation_basis(g_hero_state.transform, &angle);
                camera->distance += (12.0f - camera->distance) * 0.08400001f;
                moby_transform_joint_to_world(trail, 0, (char *)camera);
                vec_scale_to_length(camera->position, g_hero_state.transform,
                             camera->distance);
                FastVecAdd(camera->position, camera->target,
                             camera->position);
                initialize_bolt_point_chain_pal(trail);
                beam_update_chain_points_pal(trail);
                gfx_add_draw_callback_third(beam_draw_ribbons_level_pal, trail);
            } else {
                g_hero_state.camera = 0;
            }
        }
        if (g_ship_trail_state.mode == 3) {
            trail = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
            gfx_add_draw_callback_first(ship_build_trail_mesh, trail);
        }
    }
}
