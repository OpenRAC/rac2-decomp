#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern char g_hero_state[];
extern char *g_carried_marker_cam_slot __attribute__((sda));
extern float g_carried_marker_radius __attribute__((sda));
extern float g_carried_marker_override_x __attribute__((sda));
extern float g_carried_marker_override_x_alt __attribute__((sda));
extern float g_carried_marker_override_w __attribute__((sda));
extern float g_carried_marker_override_z __attribute__((sda));
extern int g_carried_marker_state;
extern char g_hero_origin_vec[];

extern int IsPointInCuboid(char *, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(float *, float *, char *);
extern char *cam_alloc_override_slot(int);
extern void cam_end_override(char *);
extern void FastVecSub(char *, float *, char *);

/* Per-frame update of the carried-object marker: arms it, tracks markerOffset linked flag, and while the hero is in state 0x31 places and sizes the marker from the grabbed object's bounds. */
void carried_marker_update(char *obj) {
    float marker_offset[4];
    float marker_pos[4];
    char *held_object;

    int *vars = FLD(obj, int *, 0x68);

    switch (FLD(obj, u8, 0x20)) {
    case 0:
        g_carried_marker_cam_slot = 0;
        FLD(obj, u8, 0x20) = 1;
        FLD(obj, u8, 0x30) = 0xFF;
        return;
    case 1:
        if (vars[0] != -1) {
            if (IsPointInCuboid(g_hero_origin_vec, vars[0]) != 0) {
                g_carried_marker_state = 2;
            } else if (g_carried_marker_state == 2) {
                g_carried_marker_state = 0;
            }
        }
        break;
    default:
        return;
    }
    if (FLD(g_hero_state, int, 0x2294) == 0x31 && (held_object = FLD(g_hero_state, char *, 0x1830)) != 0) {
        vec_build_spherical_offset(marker_offset, g_carried_marker_radius, FLD(held_object, float, 0xF8), -FLD(held_object, float, 0xF4) * 0.5f);
        FastVecAdd(marker_pos, marker_offset, FLD(g_hero_state, char *, 0x1830) + 0x10);
        if (g_carried_marker_cam_slot == 0) {
            g_carried_marker_cam_slot = cam_alloc_override_slot(5);
            if (g_carried_marker_cam_slot == 0) {
                return;
            }
        }
        if (FLD(FLD(g_hero_state, char *, 0x1830), s16, 0xAA) == MOBY_CLASS_GLIDER) {
            FLD(g_carried_marker_cam_slot, float, 0) = g_carried_marker_override_x;
            FLD(g_carried_marker_cam_slot, float, 0xC) = -1.0f;
            FLD(g_carried_marker_cam_slot, float, 8) = -1.0f;
        } else {
            FLD(g_carried_marker_cam_slot, float, 0) = g_carried_marker_override_x_alt;
            FLD(g_carried_marker_cam_slot, float, 0xC) = g_carried_marker_override_w;
            FLD(g_carried_marker_cam_slot, float, 8) = g_carried_marker_override_z;
        }
        FLD(g_carried_marker_cam_slot, u8, 0x1F) = 1;
        FastVecSub(g_carried_marker_cam_slot + 0x20, marker_pos, g_hero_origin_vec);
        return;
    }
    if (g_carried_marker_cam_slot != 0) {
        cam_end_override(g_carried_marker_cam_slot);
        g_carried_marker_cam_slot = 0;
    }
}
