#include "common.h"

extern char g_effect_path_origins_a[] __attribute__((sda));
extern char g_effect_path_origins_b[] __attribute__((sda));
extern char g_effect_path_origins_c[] __attribute__((sda));
extern char g_effect_path_origins_d[] __attribute__((sda));
extern char g_effect_path_origins_e[] __attribute__((sda));
extern char g_effect_path_origins_f[] __attribute__((sda));
extern char g_effect_path_origins_g[] __attribute__((sda));
extern char g_effect_path_origins_h[] __attribute__((sda));
extern char g_effect_path_origins_i[] __attribute__((sda));
extern char g_effect_path_origins_j[] __attribute__((sda));
extern char g_effect_path_velocities_a[] __attribute__((sda));
extern char g_effect_path_velocities_b[] __attribute__((sda));
extern char g_effect_path_velocities_c[] __attribute__((sda));
extern char g_effect_path_velocities_d[] __attribute__((sda));
extern char g_effect_path_velocities_e[] __attribute__((sda));
extern char g_effect_path_velocities_f[] __attribute__((sda));
extern char g_effect_path_velocities_g[] __attribute__((sda));
extern char g_effect_path_velocities_h[] __attribute__((sda));
extern char g_effect_path_durations_a[] __attribute__((sda));
extern char g_effect_path_durations_b[] __attribute__((sda));
extern char g_effect_path_durations_c[] __attribute__((sda));
extern char g_effect_path_durations_d[] __attribute__((sda));
extern char g_effect_path_durations_e[] __attribute__((sda));
extern char g_effect_path_durations_f[] __attribute__((sda));
extern char g_effect_path_durations_g[] __attribute__((sda));
extern char g_effect_path_durations_h[] __attribute__((sda));
extern char g_effect_path_durations_i[] __attribute__((sda));
extern char g_effect_path_durations_j[] __attribute__((sda));
extern char g_effect_path_starts_a[] __attribute__((sda));
extern char g_effect_path_starts_b[] __attribute__((sda));
extern char g_effect_path_starts_c[] __attribute__((sda));
extern char g_effect_path_starts_d[] __attribute__((sda));
extern char g_effect_path_starts_e[] __attribute__((sda));
extern char g_effect_path_starts_f[] __attribute__((sda));
extern char g_effect_path_starts_g[] __attribute__((sda));
extern char g_effect_path_starts_h[] __attribute__((sda));
extern char g_effect_path_starts_i[] __attribute__((sda));
extern char g_effect_path_starts_j[] __attribute__((sda));
extern char g_effect_path_total_a[] __attribute__((sda));
extern char g_effect_path_total_b[] __attribute__((sda));
extern char g_effect_path_total_c[] __attribute__((sda));
extern char g_effect_path_total_d[] __attribute__((sda));
extern char g_effect_path_total_e[] __attribute__((sda));
extern char g_effect_path_total_f[] __attribute__((sda));
extern char g_effect_path_total_g[] __attribute__((sda));
extern char g_effect_path_total_h[] __attribute__((sda));
extern char g_effect_path_total_i[] __attribute__((sda));
extern char g_effect_path_total_j[] __attribute__((sda));
extern char g_path_l11_segment_velocities[];
extern char g_path_l11_segment_velocities_2[];
extern void func_00282D30_2(char *, char *, float);
extern void FastVecAdd(void *, void *, void *);

extern char *g_path_l11_table[];
extern char g_str_curve_stub_a[], g_str_curve_stub_b[], g_str_curve_stub_c[];
extern void STUB_printf(char *, ...);

/* Works out where something moving along a path made of curve pieces is at a given frame, and gives back its x and y. */
void InterpolateSegmentedPath(int *outX, int *outY, int selector, int frame,
                       int *previousCurve, int *segment, char *object)
{
    float point[4], delta[4];
    int *origins;
    float *velocities, *durations, *starts;
    int count, curve = -1, i; /* the -1 load is shared with the first selector test */
    char *path;
    float time, start;

    if (selector == -1 && frame >= 0 && frame <= 54) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * 54.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_a;
        origins = (int *)g_effect_path_origins_a;
        velocities = (float *)g_effect_path_velocities_a;
        durations = (float *)g_effect_path_durations_a;
        starts = (float *)g_effect_path_starts_a;
        count = 4;
        curve = 1;
    } else if (selector == -1 && frame >= 54 && frame <= 110) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 54)) /
                   (*(float *)(path + 0x1C) * 56.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_b;
        origins = (int *)g_effect_path_origins_b;
        velocities = (float *)g_effect_path_velocities_b;
        durations = (float *)g_effect_path_durations_b;
        starts = (float *)g_effect_path_starts_b;
        count = 2;
        curve = 2;
    } else if (selector == 0) {
        path = g_path_l11_table[*(int *)(object + 0x1AC)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * (float)*(int *)path);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_c;
        origins = (int *)g_effect_path_origins_c;
        velocities = (float *)g_effect_path_velocities_c;
        durations = (float *)g_effect_path_durations_c;
        starts = (float *)g_effect_path_starts_c;
        count = 4;
        curve = 3;
    } else if (selector == -1 && frame >= 110 && frame <= 118) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 110)) /
                   (*(float *)(path + 0x1C) * 8.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_d;
        origins = (int *)g_effect_path_origins_d;
        velocities = (float *)g_effect_path_velocities_d;
        durations = (float *)g_effect_path_durations_d;
        starts = (float *)g_effect_path_starts_d;
        count = 2;
        curve = 4;
    } else if (selector == -1 && frame >= 118 && frame <= 313) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 118)) /
                   (*(float *)(path + 0x1C) * 195.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_e;
        origins = (int *)g_effect_path_origins_e;
        velocities = (float *)g_path_l11_segment_velocities;
        durations = (float *)g_effect_path_durations_e;
        starts = (float *)g_effect_path_starts_e;
        count = 6;
        curve = 5;
    } else if (selector == 1) {
        path = g_path_l11_table[*(int *)(object + 0x1B0)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * (float)*(int *)path);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_f;
        origins = (int *)g_effect_path_origins_f;
        velocities = (float *)g_path_l11_segment_velocities_2;
        durations = (float *)g_effect_path_durations_f;
        starts = (float *)g_effect_path_starts_f;
        count = 8;
        curve = 6;
    } else if (selector == -1 && frame >= 313 && frame <= 321) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 313)) /
                   (*(float *)(path + 0x1C) * 8.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_g;
        origins = (int *)g_effect_path_origins_g;
        velocities = (float *)g_effect_path_velocities_e;
        durations = (float *)g_effect_path_durations_g;
        starts = (float *)g_effect_path_starts_g;
        count = 2;
        curve = 7;
    } else if (selector == -1 && frame >= 321 && frame <= 468) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 321)) /
                   (*(float *)(path + 0x1C) * 147.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_h;
        origins = (int *)g_effect_path_origins_h;
        velocities = (float *)g_effect_path_velocities_f;
        durations = (float *)g_effect_path_durations_h;
        starts = (float *)g_effect_path_starts_h;
        count = 4;
        curve = 8;
    } else if (selector == 2) {
        path = g_path_l11_table[*(int *)(object + 0x1B4)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * (float)*(int *)path);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_i;
        origins = (int *)g_effect_path_origins_i;
        velocities = (float *)g_effect_path_velocities_g;
        durations = (float *)g_effect_path_durations_i;
        starts = (float *)g_effect_path_starts_i;
        count = 4;
        curve = 9;
    } else if (selector == -1 && frame >= 468 && frame <= 500) {
        path = g_path_l11_table[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 468)) /
                   (*(float *)(path + 0x1C) * 32.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)g_effect_path_total_j;
        origins = (int *)g_effect_path_origins_j;
        velocities = (float *)g_effect_path_velocities_h;
        durations = (float *)g_effect_path_durations_j;
        starts = (float *)g_effect_path_starts_j;
        count = 2;
        curve = 10;
    } else {
        STUB_printf(g_str_curve_stub_a);
        *previousCurve = -1;
        *segment = 0;
        *outX = 0;
        *outY = 0;
        return;
    }

    if (curve != *previousCurve) {
        start = 0.0f;
        for (i = 0; start <= time; i++) {
            start = durations[i] + start;
            if (time < start) {
                start -= durations[i];
                break;
            }
        }
        *segment = i;
        *previousCurve = curve;
    } else {
        i = *segment;
        start = starts[i];
        if (time < start) {
            while (start > time) {
                i--;
                if (i < 0) {
                    i = count;
                    STUB_printf(g_str_curve_stub_b);
                }
                start -= durations[i];
            }
        } else if (time > start) {
            do {
                start += durations[i];
                if (start < time) {
                    i++;
                    if (i >= count) {
                        STUB_printf(g_str_curve_stub_c);
                        i = 0;
                    }
                }
            } while (start < time);
        }
        start = starts[i];
        *segment = i;
    }
    point[0] = (float)origins[i * 2];
    point[1] = (float)origins[i * 2 + 1];
    point[2] = 0.0f;
    func_00282D30_2((char *)delta, (char *)(velocities + i * 4), time - start);
    FastVecAdd(point, point, delta);
    *outX = (int)point[0];
    *outY = (int)point[1];
}
