#include "names.h"
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
extern int D_L01_001A9460 __attribute__((sda));
extern int D_L01_001A9464 __attribute__((sda));
extern int D_L01_001AF240;
typedef struct SceneManager {
    char prefix[0x30];
    int mode;
    int frame;
    char gap38[0xC];
    short count;
    char gap46[0x146];
    char *entries[0];
} SceneManager;
extern SceneManager D_L01_001BD1C0;
extern TrailCamera D_L01_001C5F90;

extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(char *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern void mem_clear(void *, unsigned int, int);
extern void euler_rotation_basis(void *, void *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void InitializeBoltPointChain(char *);
extern void beam_update_chain_points(char *);
extern void beam_draw_ribbons_level(void *);
extern void ship_build_trail_mesh(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern char *tv_screen_find_nearest(float, float, float);

/* Per-frame level script for the Oozla intro scene. It tweaks a few objects and runs the trailing camera that follows the player. */
void oozla_intro_scene_update(void)
{
    int i;
    char *actor;
    char *trail;
    Quadword angle;

    anim_start_startup_animations();
    for (i = 0; i < D_L01_001BD1C0.count; ++i) {
        actor = D_L01_001BD1C0.entries[i];
        if (actor && *(short *)(actor + 0xAA) == 0xE29 /* moby class 3625 */) {
            *(unsigned short *)(actor + 0x34) |= 0x800;
        }
        if (*(short *)(actor + 0xAA) == 0xD54 /* moby class 3412 */)
            UpdateEquipmentPieces(actor);
        if (actor && *(short *)(actor + 0xAA) == 0xFA0 /* TV Screens */ && *(char **)(actor + 0x68))
            math_store_angle_update_result(actor, (float *)(*(char **)(actor + 0x68) + 0xC),
                             0x80AAAAD2, 0x80396464, 0.061086535453796387f);
    }

    if (g_current_map_index == 1) {
        if (D_L01_001BD1C0.mode == 1) {
            TrailCamera *camera = &D_L01_001C5F90;
            g_hero_state.camera = D_L01_001BD1C0.entries[2];
            trail = D_L01_001BD1C0.entries[3];
            if (D_L01_001BD1C0.frame == D_L01_001A9460) {
                mem_clear(camera, 0, sizeof(TrailCamera));
                D_L01_001AF240 = 1;
                camera->distance = 0.8f;
            }
            if (D_L01_001A9460 < D_L01_001BD1C0.frame &&
                D_L01_001BD1C0.frame < D_L01_001A9464) {
                angle = 0;
                ((float *)&angle)[2] = -0.13f;
                euler_rotation_basis(g_hero_state.transform, &angle);
                camera->distance += (12.0f - camera->distance) * 0.07f;
                moby_transform_joint_to_world(trail, 0, (char *)camera);
                vec_scale_to_length(camera->position, g_hero_state.transform,
                             camera->distance);
                FastVecAdd(camera->position, camera->target,
                             camera->position);
                InitializeBoltPointChain(trail);
                beam_update_chain_points(trail);
                gfx_add_draw_callback_third(beam_draw_ribbons_level, trail);
            } else {
                g_hero_state.camera = 0;
            }
        }
        if (D_L01_001BD1C0.mode == 3) {
            trail = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
            gfx_add_draw_callback_first(ship_build_trail_mesh, trail);
        }
    }
}
