#include "common.h"

/* func_L13_00438D88 (-g: its line labels give the nop pair before both div.s).
   Samples the camera's projected paths for the settings entry's mode, smooths
   the position and builds the camera frame.  The types differ from those of
   L13_0041B670.c, hence a unit of its own. */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;

typedef struct { int count; int reserved[3]; Vector point[0]; } CameraPath;
typedef struct { int index; float distance; } PathCursor;
typedef struct { char pad[0x20]; float rate; char pad24[0x10]; float velocity; } TurnSpring;
typedef struct { Vector saved; char pad[0x3C]; float elevation; } CameraMotion;
typedef struct { PathCursor cursor; int pad8[2]; int marker; } CameraRun;
typedef struct {
    char prefix[0x80];
    Vector position;
    char before_path[0x5A0];
    CameraPath *path;
    PathCursor cursor;
} PathHero;
extern PathHero g_hero_state;
extern int g_current_map_index __attribute__((sda));

extern float g_camera_axis_vector[4];
extern char *g_cam_settings_table[] __attribute__((sda));
typedef struct {
    char unknown00[0x10];
    CameraPath *path;
    char unknown14[0xC];
} CameraRouteRecord;
extern CameraRouteRecord *g_cam_route_table __attribute__((sda));
extern CameraPath *g_guard_path_table[];
extern int Spline_AdvanceByDistance(void *, void *, int *, float *, int, float);
extern int find_nearest_path_point(void *, void *, void *, int *, float *, int, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern int FloatToInt(float);
extern float math_fabs(float);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);

extern float math_step_spring_damper_stored(char *, float, float, float, float, float);
extern void FastVecCross(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

typedef struct { char pad0[0x38]; float sample_distance; } CameraSettings;

/* Moves the camera along its route while following the player, and turns it smoothly to look at the point ahead. */
void UpdatePathCamera(char *settings) {
    Vector desired;
    Vector eye_offset;
    Vector direction;
    Vector sampled;
    Vector point;
    Vector tangent;
    Vector interpolated;
    int selection_index;
    float selection_distance;
    int cursor_index;
    float cursor_distance;
    int advance_index;
    float advance_distance;
    int final_advance_index;
    float final_advance_distance;
    CameraPath **path_slot;
    CameraPath *markers;
    float look_ahead;
    float angular_rate;
    float position_rate;
    float segment_length;
    float duration;
    float smoothed_angle;
    int path_index;
    int mode;
    int i;
    int previous;
    int begin;
    int end;
    int steps;
    float interpolation_distance;
    float fraction;
    CameraPath *path0;
    float path_distance;
    float travelled;
    float target_distance;
    int last;
    int start;
    float marker_look_ahead;
    float sample_distance;
    CameraPath *other_path;
    CameraPath *look_path;
    float direction_length;
    float angle;
    char *camera = settings;
    char *private = *(char **)(camera + 0x70);
    TurnSpring *turn = (TurnSpring *)(private + 0x30);
    CameraMotion *motion = (CameraMotion *)(private + 0x80);
    CameraRun *run = (CameraRun *)(private + 0x150);
    settings = *(char **)(g_cam_settings_table[0] + *(short *)(camera + 0x84) * 32 + 0x1C);
    look_ahead = *(float *)settings;
    angular_rate = 0.01f;
    position_rate = 0.01f;
    path_index = *(int *)(settings + 0x20);
    mode = *(int *)(settings + 0x30);
    if (mode == 0) {
        cursor_index = g_hero_state.cursor.index;
        cursor_distance = g_hero_state.cursor.distance;
        path_slot = &g_guard_path_table[path_index];
        run->cursor.distance = cursor_distance;
        run->cursor.index = cursor_index;
        Spline_AdvanceByDistance(*path_slot, &desired, &run->cursor.index, &run->cursor.distance, 0, 1.0f);
        qcopy(&motion->saved, &desired);
        path0 = *path_slot;
        fraction = cursor_distance / g_hero_state.path->point[cursor_index].f[3];
        interpolation_distance = path0->point[cursor_index].f[3];
        interpolation_distance *= fraction;
        FastVecSub(&tangent, &path0->point[cursor_index + 1], &path0->point[cursor_index]);
        vec_scale_to_length(&point, &tangent, interpolation_distance);
        FastVecAdd(&interpolated, &path0->point[cursor_index], &point);
        *(float *)(camera + 0x30) = math_step_spring_damper_clamped((float *)private, *(float *)(camera + 0x30), interpolated.f[0], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x34) = math_step_spring_damper_clamped((float *)(private + 4), *(float *)(camera + 0x34), interpolated.f[1], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x38) = math_step_spring_damper_clamped((float *)(private + 8), *(float *)(camera + 0x38), interpolated.f[2], position_rate, 0.175f, 0.0f);
    } else if (mode == 2) {
        CameraPath *path2;
        CameraPath *route;
        CameraPath *positions;
        path2 = g_guard_path_table[path_index];
        route = g_cam_route_table[*(int *)(settings + 0x24)].path;
        positions = g_guard_path_table[*(int *)(settings + 0x28)];
        markers = g_guard_path_table[*(int *)(settings + 0x2C)];
        previous = markers->count - 1;
        for (i = 0; i < markers->count; i++) {
            begin = FloatToInt(markers->point[previous].f[3]);
            end = FloatToInt(markers->point[i].f[3]);
            if (end < begin) {
                if (g_hero_state.cursor.index >= begin || g_hero_state.cursor.index < end) break;
            } else if (g_hero_state.cursor.index >= begin && g_hero_state.cursor.index < end) break;
            previous = i;
        }
        run->marker = i;
        path_distance = 0.0f;
        last = markers->count - 1;
        previous = (i + last) % markers->count;
        duration = markers->point[i].f[1];
        segment_length = positions->point[i].f[1];
        marker_look_ahead = markers->point[previous].f[0];
        if (marker_look_ahead != 0.0f) look_ahead = marker_look_ahead;
        start = FloatToInt(markers->point[previous].f[3]);
        steps = g_hero_state.cursor.index - start;
        if (steps < 0) steps += route->count;
        for (i = 0; i < steps; i++)
            path_distance += route->point[(start + i) % route->count].f[3];
        path_distance += g_hero_state.cursor.distance;
        travelled = path_distance / duration;
        target_distance = segment_length * travelled;
        selection_index = FloatToInt(positions->point[previous].f[3]);
        selection_distance = 0.0f;
        Spline_AdvanceByDistance(path2, &point, &selection_index, &selection_distance, 1,
                         target_distance);
        path_distance = positions->point[previous].f[0];
        if (path_distance <= 0.0f) path_distance = 0.01f;
        else {
            angular_rate *= path_distance;
            path_distance *= 0.01f;
        }
        if (math_fabs(*(float *)(private + 0x10) - path_distance) < 0.00015f)
            *(float *)(private + 0x10) = path_distance;
        else if (*(float *)(private + 0x10) < path_distance)
            *(float *)(private + 0x10) += 0.00015f;
        else
            *(float *)(private + 0x10) -= 0.00015f;
        *(float *)(camera + 0x30) = math_step_spring_damper_clamped((float *)private, *(float *)(camera + 0x30), point.f[0], *(float *)(private + 0x10), 0.175f, 0.0f);
        *(float *)(camera + 0x34) = math_step_spring_damper_clamped((float *)(private + 4), *(float *)(camera + 0x34), point.f[1], *(float *)(private + 0x10), 0.175f, 0.0f);
        *(float *)(camera + 0x38) = math_step_spring_damper_clamped((float *)(private + 8), *(float *)(camera + 0x38), point.f[2], *(float *)(private + 0x10), 0.175f, 0.0f);
    } else {
        other_path = g_guard_path_table[path_index];
        if (*(int *)(settings + 0x24) < 0) {
            find_nearest_path_point(other_path, &g_hero_state.position, &sampled, &cursor_index, &cursor_distance, 0, 20.0f, 1.0f, 0.0f);
            sample_distance = *(short *)(settings + 0x36) == 1 ? -(((CameraSettings *)settings)->sample_distance * 4.0f) : ((CameraSettings *)settings)->sample_distance;
            Spline_AdvanceByDistance(other_path, &sampled, &cursor_index, &cursor_distance, 1, sample_distance);
            qcopy(&desired, &sampled);
        } else {
            advance_index = g_hero_state.cursor.index;
            advance_distance = g_hero_state.cursor.distance;
            Spline_AdvanceByDistance(g_hero_state.path, &sampled, &advance_index, &advance_distance, 1, ((CameraSettings *)settings)->sample_distance);
            find_nearest_path_point(other_path, &sampled, &desired, &cursor_index, &cursor_distance, 0, 20.0f, 1.0f, 0.0f);
        }
        *(float *)(camera + 0x30) = math_step_spring_damper_clamped((float *)private, *(float *)(camera + 0x30), desired.f[0], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x34) = math_step_spring_damper_clamped((float *)(private + 4), *(float *)(camera + 0x34), desired.f[1], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x38) = math_step_spring_damper_clamped((float *)(private + 8), *(float *)(camera + 0x38), desired.f[2], position_rate, 0.175f, 0.0f);
    }
    if (*(int *)(settings + 0x24) < 0) {
        look_path = g_guard_path_table[*(int *)(settings + 0x20)];
        find_nearest_path_point(look_path, &g_hero_state.position, &point, &cursor_index, &cursor_distance, 0, 20.0f, 1.0f, 0.0f);
        if (g_current_map_index == 14 && *(int *)(settings + 0x30) == 0)
            Spline_AdvanceByDistance(look_path, &tangent, &cursor_index, &cursor_distance, 0, look_ahead);
        else
            Spline_AdvanceByDistance(look_path, &tangent, &cursor_index, &cursor_distance, 1, look_ahead);
        FastVecSub(&tangent, &tangent, &point);
        FastVecAdd(&point, &g_hero_state.position, &tangent);
    } else {
        final_advance_index = g_hero_state.cursor.index;
        final_advance_distance = g_hero_state.cursor.distance;
        Spline_AdvanceByDistance(g_hero_state.path, &point, &final_advance_index, &final_advance_distance, 1, look_ahead);
    }
    vec_scale_to_length(&eye_offset, g_camera_axis_vector, motion->elevation);
    FastVecAdd(&sampled, &eye_offset, &point);
    FastVecSub(&direction, &sampled, camera + 0x30);
    {
        direction_length = FastVecLength(&direction);
        if (direction_length != 0.0f) {
            FastVecScale(&direction, &direction, 1.0f / direction_length);
            angle = 1.5707964f - math_fast_angle_helper(FastVecDot(&direction, camera));
        } else {
            angle = 0.0f;
        }
        if (math_fabs(turn->rate - angular_rate) < 0.00015f)
            turn->rate = angular_rate;
        else if (turn->rate < angular_rate)
            turn->rate += 0.00015f;
        else
            turn->rate -= 0.00015f;
        smoothed_angle = math_step_spring_damper_stored((char *)&turn->velocity, 0.0f, angle, turn->rate, 0.175f, 0.0f);
    }
    FastVecCross(&tangent, &direction, camera + 0x40);
    math_apply_axis_rotation_to_quat(camera, camera + 0x40, &tangent, smoothed_angle);
    vec_scale_to_length(camera + 0x40, camera, 1.0f);
    vec_scale_to_length(camera, camera, 1.0f);
    FastVecCross(camera + 0x10, camera, g_camera_axis_vector);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
}
