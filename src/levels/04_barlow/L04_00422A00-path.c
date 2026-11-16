#include "names.h"
typedef unsigned char u8;
typedef float f32;
struct BarlowAnimation { int frames; u8 unused[24]; f32 dustartn; };
extern struct BarlowAnimation *g_route_path_table[];
extern u8 g_str_path_debug[];
extern void STUB_printf(const char *, ...);
extern void FastVecScale(f32, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int g_barlow_l04_path_points_a[][2] __attribute__((sda));
extern f32 g_barlow_path_vectors_a[][4];
extern f32 g_barlow_path_lengths_a[] __attribute__((sda));
extern f32 g_barlow_path_starts_a[] __attribute__((sda));
extern f32 g_barlow_path_total_a __attribute__((sda));
extern int g_barlow_l04_path_points_b[][2] __attribute__((sda));
extern f32 g_barlow_l04_path_vectors_b[][4] __attribute__((sda));
extern f32 g_barlow_path_lengths_b[] __attribute__((sda));
extern f32 g_barlow_path_starts_b[] __attribute__((sda));
extern f32 g_barlow_path_total_b __attribute__((sda));
extern int g_barlow_l04_path_points_a_2[][2];
extern f32 g_barlow_l04_path_vectors_b_2[][4];
extern f32 g_barlow_path_lengths_c[] __attribute__((sda));
extern f32 g_barlow_path_starts_c[] __attribute__((sda));
extern f32 g_barlow_path_total_c __attribute__((sda));
extern int g_barlow_path_points_c[][2] __attribute__((sda));
extern f32 g_barlow_path_vectors_c[][4];
extern f32 g_barlow_path_lengths_d[] __attribute__((sda));
extern f32 g_barlow_path_starts_d[] __attribute__((sda));
extern f32 g_barlow_path_total_d __attribute__((sda));
extern int g_barlow_l04_path_points_b_2[][2];
extern f32 g_barlow_l04_path_vectors_d_2[][4];
extern f32 g_barlow_path_lengths_e[] __attribute__((sda));
extern f32 g_barlow_path_starts_e[] __attribute__((sda));
extern f32 g_barlow_path_total_e __attribute__((sda));
extern int g_barlow_path_points_d[][2] __attribute__((sda));
extern f32 g_barlow_l04_path_vectors_d[][4] __attribute__((sda));
extern f32 g_barlow_path_lengths_f[] __attribute__((sda));
extern f32 g_barlow_path_starts_f[] __attribute__((sda));
extern f32 g_barlow_path_total_f __attribute__((sda));
extern int g_barlow_path_points_e[][2] __attribute__((sda));
extern f32 g_barlow_path_vectors_e[][4] __attribute__((sda));
extern f32 g_barlow_path_lengths_g[] __attribute__((sda));
extern f32 g_barlow_path_starts_g[] __attribute__((sda));
extern f32 g_barlow_path_total_g __attribute__((sda));

/* Finds where on the screen the Barlow walk path is for the current animation and frame, and remembers which path piece it is on. */
void GetAnimationPathPoint(int *outX, int *outY, int animation, int frame, int *currentPath, int *currentSegment, u8 *data) {
    f32 point[4], movement[4];
    int (*points)[2];
    f32 (*vectors)[4], *lengths, *starts;
    int count, path = -1, segment;
    f32 progress, start;
    struct BarlowAnimation *timing;
    if (animation == -1 && frame >= 0 && frame <= 151) {
        timing = g_route_path_table[*(int *)(data + 0x1A8)];
        start = (timing->dustartn * (f32)(frame - 0)) / (timing->dustartn * 151.0f);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_a;
        points = g_barlow_l04_path_points_a;
        vectors = g_barlow_path_vectors_a;
        lengths = g_barlow_path_lengths_a;
        starts = g_barlow_path_starts_a;
        count = 7;
        path = 1;
    } else if (animation == -1 && frame >= 151 && frame <= 174) {
        timing = g_route_path_table[*(int *)(data + 0x1A8)];
        start = (timing->dustartn * (f32)(frame - 151)) / (timing->dustartn * 23.0f);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_b;
        points = g_barlow_l04_path_points_b;
        vectors = g_barlow_l04_path_vectors_b;
        lengths = g_barlow_path_lengths_b;
        starts = g_barlow_path_starts_b;
        count = 3;
        path = 2;
    } else if (animation == -1 && frame >= 174 && frame <= 312) {
        timing = g_route_path_table[*(int *)(data + 0x1A8)];
        start = (timing->dustartn * (f32)(frame - 174)) / (timing->dustartn * 138.0f);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_c;
        points = g_barlow_l04_path_points_a_2;
        vectors = g_barlow_l04_path_vectors_b_2;
        lengths = g_barlow_path_lengths_c;
        starts = g_barlow_path_starts_c;
        count = 11;
        path = 3;
    } else if (animation == -1 && frame >= 312 && frame <= 500) {
        timing = g_route_path_table[*(int *)(data + 0x1A8)];
        start = (timing->dustartn * (f32)(frame - 312)) / (timing->dustartn * 186.0f);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_d;
        points = g_barlow_path_points_c;
        vectors = g_barlow_path_vectors_c;
        lengths = g_barlow_path_lengths_d;
        starts = g_barlow_path_starts_d;
        count = 6;
        path = 4;
    } else if (animation == 0) {
        timing = g_route_path_table[*(int *)(data + 0x1AC)];
        start = (timing->dustartn * (f32)frame) / (timing->dustartn * (f32)timing->frames);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_e;
        points = g_barlow_l04_path_points_b_2;
        vectors = g_barlow_l04_path_vectors_d_2;
        lengths = g_barlow_path_lengths_e;
        starts = g_barlow_path_starts_e;
        count = 9;
        path = 5;
    } else if (animation == 2) {
        timing = g_route_path_table[*(int *)(data + 0x1B4)];
        start = (timing->dustartn * (f32)frame) / (timing->dustartn * (f32)timing->frames);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_f;
        points = g_barlow_path_points_d;
        vectors = g_barlow_l04_path_vectors_d;
        lengths = g_barlow_path_lengths_f;
        starts = g_barlow_path_starts_f;
        count = 3;
        path = 6;
    } else if (animation == 1) {
        timing = g_route_path_table[*(int *)(data + 0x1B0)];
        start = (timing->dustartn * (f32)frame) / (timing->dustartn * (f32)timing->frames);
        if (start > 1.0f)
            start = 1.0f;
        progress = start * g_barlow_path_total_g;
        points = g_barlow_path_points_e;
        vectors = g_barlow_path_vectors_e;
        lengths = g_barlow_path_lengths_g;
        starts = g_barlow_path_starts_g;
        count = 2;
        path = 7;
    } else {
        STUB_printf(g_str_path_debug);
        *currentPath = -1;
        *currentSegment = 0;
        *outX = 0;
        *outY = 0;
        return;
    }
    if (path != *currentPath) {
        start = 0.0f;
        for (segment = 0; start <= progress; segment++) {
            start += lengths[segment];
            if (progress < start) {
                start -= lengths[segment];
                break;
            }
        }
        *currentSegment = segment;
        *currentPath = path;
    } else {
        segment = *currentSegment;
        start = starts[segment];
        if (start > progress) {
            while (progress < start) {
                segment--;
                if (segment < 0)
                    segment = count;
                start -= lengths[segment];
            }
        } else {
            while (start < progress) {
                start += lengths[segment];
                if (start < progress) {
                    segment++;
                    if (segment >= count)
                        segment = 0;
                }
            }
        }
        start = starts[segment];
        *currentSegment = segment;
    }
    point[0] = (f32)points[segment][0];
    point[1] = (f32)points[segment][1];
    point[2] = 0.0f;
    FastVecScale(progress - start, movement, vectors[segment]);
    FastVecAdd(point, point, movement);
    *outX = (int)point[0];
    *outY = (int)point[1];
}
