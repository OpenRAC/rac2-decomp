#include "names.h"
/* func_PAL_L00_002B6488, the PAL copy of func_L00_002B6560: the same C, where scale p- becomes entries[p->index].duration. */
#include "common.h"

extern int hero_slot_item_id(int);
extern void hero_apply_mode_transform(void *, void *, float);
extern float cam_get_view_space_height(void *);
extern void cam_set_view_space_height(void *, void *, float);
extern void cam_offset_point_in_view_space(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void ApproachValue(float *, float, float);
extern float square_root(float);
extern void snd_update_slot_object(int, int, int);
extern void snd_stop_voice(int);
/* The EE passes the three floats independently of the two integer arguments. */
extern void hero_build_relative_point(void *, float, float, float, int);
extern int CollLine(void *, void *, int, int, int);

extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern char g_sound_state[];
extern char g_hero_state[];
extern int D_00138320[];
extern char g_hero_position[];

typedef struct {
    float initial, acceleration;
    int duration;
} HeroMotionEntry;

typedef struct {
    char pad[20];
    HeroMotionEntry *entries;
    int index, ticks;
    float value;
} HeroMotionSequence;

/* Apply gravity and the current jump or hovering motion to the hero's velocity. */
void func_PAL_L00_002B6488(void)
{
    float v[4], w[4], u[4], len;
    float speed, distance;
    int near, clear;

    {
        char *g = (char *)&g_hero_state;
        int state = *(int *)(g + 0x2294), age;

        if (!((state == 27 && *(int *)(g + 0x1B8) < 8) ||
              (state == 137 && (age = *(int *)(g + 0x1B8)) < 12) ||
              (state == 72 && *(int *)(g + 0x1B8) < 11))) {
            if (*(int *)(g + 0x1B8) < *(short *)(g + 0x4AC)) {
                cam_set_view_space_height(g + 0xF0, g + 0xF0, 0.0f);
                hero_apply_mode_transform(g + 0xF0, g + 0xF0, 0.0192f);
            } else if (*(unsigned char *)(g + 0x49C)) {
                cam_set_view_space_height(g + 0xF0, g + 0xF0, 0.0f);
                hero_apply_mode_transform(g + 0xF0, g + 0xF0, 0.0216f);
            } else {
                float z;

                hero_apply_mode_transform(g + 0xF0, g + 0xF0, *(float *)(g + 0x520));
                z = cam_get_view_space_height(g + 0xF0);
                if (z < -*(float *)(g + 0x4A0))
                    z = -*(float *)(g + 0x4A0);
                cam_set_view_space_height(g + 0xF0, g + 0xF0, z);
            }
        }
    }
    {
        char *g = (char *)&g_hero_state;

        if (*(int *)(g + 0x2294) == 14) {
            speed = 0.14000002f;
            near = 0;
            if (g_item_owned_flags[2] && *(short *)(g + 0x24FC) == 0)
                near = hero_slot_item_id(3) == 3;
            {
                char *position = g_hero_position;

                FastVecSub(v, position, position + 0x3E0);
                distance = cam_get_view_space_height(v);
                clear = 1;
                if (near) {
                    char *g = position - 0x80;

                    if (!*(unsigned char *)(g + 0x49E)) {
                        snd_update_slot_object(4, *(int *)(g + 0x2290), 13);
                    } else {
                        int index = *(int *)(g + 0x243C);

                        if (index != -1) {
                            char *entry = g_sound_state + index * 112;

                            if (*(int *)(entry + 0x88) == *(int *)(g + 0x2290) &&
                                *(unsigned char *)(entry + 0x74)) {
                                snd_stop_voice(index);
                            }
                        }
                        {
                            char *h = (char *)g_hero_state;

                            *(int *)(h + 0x243C) = -1;
                        }
                    }
                    hero_build_relative_point(u, 0.0f, 0.0f, 1.0f, 1);
                    hero_build_relative_point(w, 0.0f, 0.0f, 2.7f, 1);
                    if (CollLine(u, w, 2, 0, 0))
                        clear = 0;
                }
            }
            if (near && clear) {
                if (distance > 2.8f)
                    speed *= 0.47f;
                else if (distance > 2.2f)
                    speed *= 0.7f;
            } else {
                if (distance > 2.1f)
                    speed *= 0.45f;
                else if (distance > 1.7f)
                    speed *= 0.7f;
            }
            if (hero_slot_item_id(3) == 3) {
                char *g = (char *)g_hero_state;

                if (*(short *)(g + 0x24FC) == 0) {
                    if (clear)
                        speed *= 1.25f;
                }
            }
            {
                char *g = (char *)&g_hero_state;

                if (*(int *)(g + 0x1B8) < 7) {
                    len = cam_get_view_space_height(g + 0xF0);
                    if (len < speed)
                        ApproachValue(&len, speed, 0.060000002f);
                    cam_set_view_space_height(g + 0xF0, g + 0xF0, len);
                }
            }
        } else {
            int zero = 0;
            char *k;

            if (*(float *)(g + 0x4B0) == 0.0f && *(float *)(g + 0x4B4) == 0.0f)
                zero = 1;
            if ((D_00138320[0] & 0x40) || zero ||
                (k = (char *)g_hero_state, *(int *)(k + 0x2294) == 18)) {
                char *g = (char *)&g_hero_state;

                if (*(float *)(g + 0x4A8) < *(float *)(g + 0x50C) &&
                    *(int *)(g + 0x1B8) <= *(short *)(g + 0x518)) {
                    *(float *)(g + 0x4A8) +=
                        (*(float *)(g + 0x50C) - *(float *)(g + 0x508)) /
                        (float)*(short *)(g + 0x518);
                    if (*(float *)(g + 0x50C) < *(float *)(g + 0x4A8))
                        *(float *)(g + 0x4A8) = *(float *)(g + 0x50C);
                    *(float *)(g + 0x4B0) +=
                        square_root(*(float *)(g + 0x4A8) * 2.0f * *(float *)(g + 0x520)) -
                        *(float *)(g + 0x4B4) - *(float *)(g + 0x4B0);
                }
            }
            {
                char *g = (char *)&g_hero_state;

                if (*(int *)(g + 0x1B8) >= *(short *)(g + 0x4AC) &&
                    *(float *)(g + 0x4B0) > 0.0f) {
                    cam_offset_point_in_view_space(g + 0xF0, g + 0xF0, *(float *)(g + 0x4B0));
                    *(float *)(g + 0x4B4) += *(float *)(g + 0x4B0);
                    *(float *)(g + 0x4B0) = 0.0f;
                }
            }
            {
                char *g = (char *)&g_hero_state;

                if (*(unsigned char *)(g + 0x49D) &&
                    *(int *)(g + 0x1B8) >= *(int *)(g + 0x430) &&
                    *(int *)(g + 0x1B8) < *(int *)(g + 0x434)) {
                    HeroMotionSequence *p = (HeroMotionSequence *)(g + 0x430);

                    p->ticks++;
                    while (p->index == -1 || p->ticks >= (((int)(p->entries[p->index].duration) * 5 + 2) / 6)) {
                        p->ticks = 0;
                        p->index++;
                        if (p->entries[p->index].initial != -999999.0f)
                            p->value = p->entries[p->index].initial * 0.00040000002f;
                    }
                    if (p->ticks > 0)
                        p->value += p->entries[p->index].acceleration * 0.00040000002f;
                    cam_offset_point_in_view_space((char *)&g_hero_state + 0xF0,
                                     (char *)&g_hero_state + 0xF0, p->value);
                }
            }
        }
    }
}
