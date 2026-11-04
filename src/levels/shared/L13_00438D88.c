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
extern PathHero D_00189E20;
extern int D_001A79F0 __attribute__((sda));

extern float D_L13_001B9940[4];
extern char *D_L13_001B22C4[] __attribute__((sda));
typedef struct {
    char unknown00[0x10];
    CameraPath *path;
    char unknown14[0xC];
} CameraRouteRecord;
extern CameraRouteRecord *D_L13_001B2140 __attribute__((sda));
extern CameraPath *D_L13_001FE580[];
extern int func_L00_00341820(void *, void *, int *, float *, int, float);
extern int func_L00_00341FA8(void *, void *, void *, int *, float *, int, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002702C8(float *, float, float, float, float, float);
extern int func_00283CF0(float);
extern float func_00282C48(float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);

extern float func_002703B0(char *, float, float, float, float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);

typedef struct { char pad0[0x38]; float sample_distance; } CameraSettings;

void func_L13_00438D88(char *settings) {
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
    settings = *(char **)(D_L13_001B22C4[0] + *(short *)(camera + 0x84) * 32 + 0x1C);
    look_ahead = *(float *)settings;
    angular_rate = 0.01f;
    position_rate = 0.01f;
    path_index = *(int *)(settings + 0x20);
    mode = *(int *)(settings + 0x30);
    if (mode == 0) {
        cursor_index = D_00189E20.cursor.index;
        cursor_distance = D_00189E20.cursor.distance;
        path_slot = &D_L13_001FE580[path_index];
        run->cursor.distance = cursor_distance;
        run->cursor.index = cursor_index;
        func_L00_00341820(*path_slot, &desired, &run->cursor.index, &run->cursor.distance, 0, 1.0f);
        qcopy(&motion->saved, &desired);
        path0 = *path_slot;
        fraction = cursor_distance / D_00189E20.path->point[cursor_index].f[3];
        interpolation_distance = path0->point[cursor_index].f[3];
        interpolation_distance *= fraction;
        func_00282CF0(&tangent, &path0->point[cursor_index + 1], &path0->point[cursor_index]);
        func_00282F20(&point, &tangent, interpolation_distance);
        func_00282CC0(&interpolated, &path0->point[cursor_index], &point);
        *(float *)(camera + 0x30) = func_002702C8((float *)private, *(float *)(camera + 0x30), interpolated.f[0], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x34) = func_002702C8((float *)(private + 4), *(float *)(camera + 0x34), interpolated.f[1], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x38) = func_002702C8((float *)(private + 8), *(float *)(camera + 0x38), interpolated.f[2], position_rate, 0.175f, 0.0f);
    } else if (mode == 2) {
        CameraPath *path2;
        CameraPath *route;
        CameraPath *positions;
        path2 = D_L13_001FE580[path_index];
        route = D_L13_001B2140[*(int *)(settings + 0x24)].path;
        positions = D_L13_001FE580[*(int *)(settings + 0x28)];
        markers = D_L13_001FE580[*(int *)(settings + 0x2C)];
        previous = markers->count - 1;
        for (i = 0; i < markers->count; i++) {
            begin = func_00283CF0(markers->point[previous].f[3]);
            end = func_00283CF0(markers->point[i].f[3]);
            if (end < begin) {
                if (D_00189E20.cursor.index >= begin || D_00189E20.cursor.index < end) break;
            } else if (D_00189E20.cursor.index >= begin && D_00189E20.cursor.index < end) break;
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
        start = func_00283CF0(markers->point[previous].f[3]);
        steps = D_00189E20.cursor.index - start;
        if (steps < 0) steps += route->count;
        for (i = 0; i < steps; i++)
            path_distance += route->point[(start + i) % route->count].f[3];
        path_distance += D_00189E20.cursor.distance;
        travelled = path_distance / duration;
        target_distance = segment_length * travelled;
        selection_index = func_00283CF0(positions->point[previous].f[3]);
        selection_distance = 0.0f;
        func_L00_00341820(path2, &point, &selection_index, &selection_distance, 1,
                         target_distance);
        path_distance = positions->point[previous].f[0];
        if (path_distance <= 0.0f) path_distance = 0.01f;
        else {
            angular_rate *= path_distance;
            path_distance *= 0.01f;
        }
        if (func_00282C48(*(float *)(private + 0x10) - path_distance) < 0.00015f)
            *(float *)(private + 0x10) = path_distance;
        else if (*(float *)(private + 0x10) < path_distance)
            *(float *)(private + 0x10) += 0.00015f;
        else
            *(float *)(private + 0x10) -= 0.00015f;
        *(float *)(camera + 0x30) = func_002702C8((float *)private, *(float *)(camera + 0x30), point.f[0], *(float *)(private + 0x10), 0.175f, 0.0f);
        *(float *)(camera + 0x34) = func_002702C8((float *)(private + 4), *(float *)(camera + 0x34), point.f[1], *(float *)(private + 0x10), 0.175f, 0.0f);
        *(float *)(camera + 0x38) = func_002702C8((float *)(private + 8), *(float *)(camera + 0x38), point.f[2], *(float *)(private + 0x10), 0.175f, 0.0f);
    } else {
        other_path = D_L13_001FE580[path_index];
        if (*(int *)(settings + 0x24) < 0) {
            func_L00_00341FA8(other_path, &D_00189E20.position, &sampled, &cursor_index, &cursor_distance, 0, 20.0f, 1.0f, 0.0f);
            sample_distance = *(short *)(settings + 0x36) == 1 ? -(((CameraSettings *)settings)->sample_distance * 4.0f) : ((CameraSettings *)settings)->sample_distance;
            func_L00_00341820(other_path, &sampled, &cursor_index, &cursor_distance, 1, sample_distance);
            qcopy(&desired, &sampled);
        } else {
            advance_index = D_00189E20.cursor.index;
            advance_distance = D_00189E20.cursor.distance;
            func_L00_00341820(D_00189E20.path, &sampled, &advance_index, &advance_distance, 1, ((CameraSettings *)settings)->sample_distance);
            func_L00_00341FA8(other_path, &sampled, &desired, &cursor_index, &cursor_distance, 0, 20.0f, 1.0f, 0.0f);
        }
        *(float *)(camera + 0x30) = func_002702C8((float *)private, *(float *)(camera + 0x30), desired.f[0], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x34) = func_002702C8((float *)(private + 4), *(float *)(camera + 0x34), desired.f[1], position_rate, 0.175f, 0.0f);
        *(float *)(camera + 0x38) = func_002702C8((float *)(private + 8), *(float *)(camera + 0x38), desired.f[2], position_rate, 0.175f, 0.0f);
    }
    if (*(int *)(settings + 0x24) < 0) {
        look_path = D_L13_001FE580[*(int *)(settings + 0x20)];
        func_L00_00341FA8(look_path, &D_00189E20.position, &point, &cursor_index, &cursor_distance, 0, 20.0f, 1.0f, 0.0f);
        if (D_001A79F0 == 14 && *(int *)(settings + 0x30) == 0)
            func_L00_00341820(look_path, &tangent, &cursor_index, &cursor_distance, 0, look_ahead);
        else
            func_L00_00341820(look_path, &tangent, &cursor_index, &cursor_distance, 1, look_ahead);
        func_00282CF0(&tangent, &tangent, &point);
        func_00282CC0(&point, &D_00189E20.position, &tangent);
    } else {
        final_advance_index = D_00189E20.cursor.index;
        final_advance_distance = D_00189E20.cursor.distance;
        func_L00_00341820(D_00189E20.path, &point, &final_advance_index, &final_advance_distance, 1, look_ahead);
    }
    func_00282F20(&eye_offset, D_L13_001B9940, motion->elevation);
    func_00282CC0(&sampled, &eye_offset, &point);
    func_00282CF0(&direction, &sampled, camera + 0x30);
    {
        direction_length = func_00282DF0(&direction);
        if (direction_length != 0.0f) {
            func_00282D30(&direction, &direction, 1.0f / direction_length);
            angle = 1.5707964f - func_002831B0(func_00282DB0(&direction, camera));
        } else {
            angle = 0.0f;
        }
        if (func_00282C48(turn->rate - angular_rate) < 0.00015f)
            turn->rate = angular_rate;
        else if (turn->rate < angular_rate)
            turn->rate += 0.00015f;
        else
            turn->rate -= 0.00015f;
        smoothed_angle = func_002703B0((char *)&turn->velocity, 0.0f, angle, turn->rate, 0.175f, 0.0f);
    }
    func_00282DD8(&tangent, &direction, camera + 0x40);
    func_002ACEC0(camera, camera + 0x40, &tangent, smoothed_angle);
    func_00282F20(camera + 0x40, camera, 1.0f);
    func_00282F20(camera, camera, 1.0f);
    func_00282DD8(camera + 0x10, camera, D_L13_001B9940);
    func_00282F20(camera + 0x10, camera + 0x10, 1.0f);
    func_00282DD8(camera + 0x20, camera + 0x10, camera);
}
