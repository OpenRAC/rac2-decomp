#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
extern Vector g_camera_l02_position;
extern struct { Vector point, normal; } D_L02_001C0970;
extern char *g_route_polygons[];
extern float D_L02_001B0080 __attribute__((sda)), D_L02_001B0084 __attribute__((sda)), D_L02_001B0088 __attribute__((sda));
extern float D_L02_001B008C __attribute__((sda)), D_L02_001B0090 __attribute__((sda));
extern int D_L02_001B0098[2];
extern int g_frame_l02_counter[] MACRO_ADDR;
extern float fast_vec_dist(void *, void *), vec_distance_xy(void *, void *), FastVecDot(void *, void *), vec_length_xy(void *), mat_fast_helper_a(float, float), FastAddRotations(float, float);
extern void moby_update_ground_check(char *), moby_set_state(u8 *, int, int), func_PAL_002A7E68(char *, int, int, int);
extern int flag_set_first_pending(u8 *), flag_is_third_pending_set(u8 *), math_random_int_below(int), moby_start_effect_from_entry(int, float);
extern int path_build_route_nodes(void *, int, void *, int), path_find_route_node_containing_point(void *, void *, int, int *), func_PAL_L02_003CECB0(char *, int), IsPointInCuboid(void *, int), coll_test_point(void *, int, float, void *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void path_enemy_pick_patrol_point(char *, void *), func_PAL_L02_003CEF50(char *);
extern void func_PAL_L01_0031C9C0(char *, void *, float, float, float, int);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(Quad *), vec_fast_normalize_helper(void *, void *, float), vec_scale_to_length(void *, void *, float), vec_fast_normalize(void *, void *, void *), FastVecScale(void *, void *, float);
extern int PulseColor(int, int, float);
typedef struct { u8 prefix[0x80]; Vector position_80; u8 gap_90[0x530]; char *pointer_5c0; } L02_ResidentGrabPrefix;
extern L02_ResidentGrabPrefix g_hero_state NOT_SDA;
typedef struct { int id; u8 gap[0xC]; Vector position; } L02_PathRef;
typedef struct {
    u8 pad0[0x20]; float f20; u16 f24; u8 pad26[0xA]; float f30;
    u8 pad34[0x1C]; float f50, f54, f58, f5c, f60;
    u8 pad64[0x1C]; float f80, f84; int f88, f8c; u8 pad90[0xC]; char *f9c;
    u8 padA0[0xD4]; float f174, f178; u8 pad17C[0x114]; L02_PathRef refs[8]; int f390, f394; u8 pad398[0x1E]; short f3b6;
} L02_PathState;

void func_PAL_L02_003CE368(char *self) {
    char *state = *(char **)(self + 0x68), *path;
    Vector point;
    int step, pathCount;
    float slope, length;
    if (((u8 *)self)[0x31] && fast_vec_dist(self + 0x10, &g_camera_l02_position) < 24.0f) {
        moby_update_ground_check(self); ((u8 *)self)[0x6F] = 22;
    }
    if (!((u8 *)self)[0x95]) {
        if (self == g_hero_state.pointer_5c0) {
            moby_set_state((u8 *)self, 5, 1); qcopy(state + 0x150,self + 0x10);
        } else if (vec_distance_xy(self + 0x10, &g_hero_state.position_80) < *(float *)(state + 0x178)) *(u16 *)(self + 0x34) |= 0x1000;
        else *(u16 *)(self + 0x34) &= 0xEFFF;
    }
    switch (((u8 *)self)[0x20]) {
    case 0:
        *(float *)(self + 0x2C) = *(float *)(*(char **)(self + 0x24) + 0x24) * D_L02_001B0080;
        ((L02_PathState *)state)->f24 = 1;
        ((L02_PathState *)state)->f20 = 1; ((L02_PathState *)state)->f30 = 1.5f; ((L02_PathState *)state)->f84 = 0.05f;
        ((L02_PathState *)state)->f54 = 0.2f; ((L02_PathState *)state)->f50 = 0.825f; ((L02_PathState *)state)->f5c = ((L02_PathState *)state)->f58 = 0.4f;
        ((L02_PathState *)state)->f60 = 1.5707964897155762f; ((L02_PathState *)state)->f80 = 0.523598849773407f;
        ((L02_PathState *)state)->f88 |= 1; ((L02_PathState *)state)->f8c = ((L02_PathState *)state)->f394; ((L02_PathState *)state)->f9c = state + 0x190;
        ((L02_PathState *)state)->f174 = 4; ((L02_PathState *)state)->f178 = 12;
        *(short *)(state + 0x3B6) = path_build_route_nodes(self, *(int *)(state + 0x390), state + 0x290, 8);
        ((u8 *)self)[0x20] = 1; ((u8 *)self)[0x30] = 0x80; *(u16 *)(self + 0x34) |= 0x1000;
        break;
    case 1:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != math_random_int_below(2)) func_PAL_002A7E68(self, math_random_int_below(2), 0, 8);
        if (*(int *)(state + 0x3C0) < (int)*(u16 *)(self + 0x96)) moby_set_state((u8 *)self, 2, -1);
        break;
    case 4:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 5) func_PAL_002A7E68(self, 5, 0, 17);
            moby_set_controller_speed_limits((u8 *)self, 0.0032000002f, D_L02_001B008C * 0.020000001f, 0.005026549f, 0.25132746f);
        }
        func_PAL_L02_003CECB0(self, (int)(&g_hero_state.position_80));
        if (*(float *)(state + 0x11C) < 6) moby_set_state((u8 *)self, 1, -1);
        break;
    case 2:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 4) func_PAL_002A7E68(self, 4, 0, 17);
            moby_set_controller_speed_limits((u8 *)self, 0.0016000001f, D_L02_001B0088 * 0.020000001f, 0.0012566373f, 0.12566373f);
            path_enemy_pick_patrol_point(self, state + 0x3A0);
        }
        func_PAL_L02_003CECB0(self, (int)(state + 0x3A0));
        if ((*(u32 *)(state + 0xE4) & 0x80) || *(u16 *)(self + 0x96) >= 250) moby_set_state((u8 *)self, 1, -1);
        break;
    case 3:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 5) func_PAL_002A7E68(self, 5, 0, 17);
            moby_set_controller_speed_limits((u8 *)self, 0.0056000003f, D_L02_001B008C * 0.020000001f, 0.005026549f, 0.5026549f);
            path_enemy_pick_patrol_point(self, state + 0x3A0);
        }
        func_PAL_L02_003CECB0(self, (int)(state + 0x3A0));
        if (*(u16 *)(self + 0x96) >= 350) moby_set_state((u8 *)self, 1, -1);
        break;
    case 5:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 7) func_PAL_002A7E68(self, 7, 0, 8);
            *(short *)(state + 0x3B4) = 0;
        }
        slope = FastVecDot(self + 0xC0, state + 0x140);
        if (slope < -0.040000003f) { if (((u8 *)self)[0x43] != 10) func_PAL_002A7E68(self, 10, 0, 8); }
        else if (slope > 0.040000003f) { if (((u8 *)self)[0x43] != 9) func_PAL_002A7E68(self, 9, 0, 8); }
        else if (((u8 *)self)[0x43] != 7) func_PAL_002A7E68(self, 7, 0, 8);
        moby_start_effect_from_entry((int)self, mat_fast_helper_a(g_hero_state.position_80.f[0] - *(float *)(self + 0x10), g_hero_state.position_80.f[1] - *(float *)(self + 0x14)));
        func_PAL_L01_0031C9C0(self, state + 0x140, 0.7f, 0.5f, 0.1f, *(int *)(state + 0x394));
        func_PAL_L02_003CEF50(self);
        if (flag_is_third_pending_set((u8 *)self)) {
            moby_set_state((u8 *)self, 6, -1);
            break;
        }
        if (self != g_hero_state.pointer_5c0) moby_set_state((u8 *)self, 3, 0);
        break;
    case 6:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 13) func_PAL_002A7E68(self, 13, 0, 8);
        moby_start_effect_from_entry((int)self, mat_fast_helper_a(g_hero_state.position_80.f[0] - *(float *)(self + 0x10), g_hero_state.position_80.f[1] - *(float *)(self + 0x14)));
        func_PAL_L02_003CEF50(self);
        break;
    case 7:
        FastVecAdd(self + 0x10, self + 0x10, state + 0xF0);
        *(float *)(state + 0xF8) -= D_L02_001B0084 * 0.00040000002f;
        func_PAL_L02_003CEF50(self);
        if (IsPointInCuboid(self + 0x10, *(int *)(state + 0x398))) {
            length = vec_length_xy(state + 0xF0); if (length > 0.020000001f) length = 0.020000001f;
            vec_fast_normalize_helper(state + 0xF0, state + 0xF0, length);
        }
        qcopy(&point,self + 0x10); point.f[2] += 0.5f;
        if (coll_test_point(&point, 0, 0.5f, self)) {
            qcopy(self + 0x10,&D_L02_001C0970.point); *(float *)(self + 0x18) -= 0.5f;
            vec_scale_to_length(&D_L02_001C0970.normal, &D_L02_001C0970.normal, 1);
            if (FastVecDot(&D_L02_001C0970.normal, state + 0xF0) < 0) {
                vec_fast_normalize(state + 0xF0, state + 0xF0, &D_L02_001C0970.normal);
                FastVecScale(state + 0xF0, state + 0xF0, 0.5f);
            }
            if (D_L02_001C0970.normal.f[2] >= 0.95f) {
                *(u16 *)(self + 0x34) |= 0x1000; moby_set_state((u8 *)self, 1, 0);
                qzero(state + 0xF0); qcopy(state + 0x150,self + 0x10);
                vec_clear_128((Quad *)(state + 0x140));
            }
        }
        break;
    }
    if (((u8 *)self)[0x31]) {
        *(float *)(state + 0x3B0) = FastAddRotations(*(float *)(state + 0x3B0), D_L02_001B0090 * 0.0003490659f);
        *(int *)(self + 0x78) = PulseColor(D_L02_001B0098[0], D_L02_001B0098[1], *(float *)(state + 0x3B0));
    }
    if ((g_frame_l02_counter[0] & 31) == (((int)self >> 8) & 31)) {
        step = *(int *)(state + 0x3C4);
        pathCount = ((L02_PathState *)state)->f3b6;
        path_find_route_node_containing_point(&g_hero_state.position_80, state + 0x290, pathCount, &step);
        if (*(int *)(state + 0x3C4) < step) {
            path = g_route_polygons[((L02_PathState *)state)->refs[step].id];
            if (fast_vec_dist(path + 0x10, path + ((*(int *)path >> 1) * 16 + 0x10)) > 8) *(int *)(state + 0x3C4) = step;
        }
    }
    ++*(u16 *)(self + 0x96);
}
