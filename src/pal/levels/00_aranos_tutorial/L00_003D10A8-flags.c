#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
extern char g_hero_state[];
#define D_00189EA0 (*(Vec *)(D_00189E20 + 0x80))
#define D_0018C0B0 (*(char **)(D_00189E20 + 0x2290))
typedef struct {
    unsigned char pad[4];
    unsigned char active;
    unsigned char gap[0x13];
    char *object;
    unsigned char tail[0x54];
} SoundSlot;
extern SoundSlot g_sound_state[];
extern Vec g_hero_l00_position;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float IntToFloat(int);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int math_fast_float_d(int *);
extern int IsPointInCuboid(void *, int);
extern void gfx_draw_scrolling_rings(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern int coll_test_point(void *, int, void *, float);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int snd_start_in_slot(int, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void *part_spawn_ground_effect(void *, int, int, int, int, void *, float, float, float, int);
extern void snd_stop_voice(int);

/* Moves a ring of light along its heading and resets it after a while, and sprays sparks when the player is close (PAL). */
void ring_of_light_update_pal(unsigned char *moby) {
    struct {
        Vec offset, direction, rotated, position;
    } frame;
    char *vars = *(char **)(moby + 0x68);
    char *ring_point;
    int i, handle, sign;
    int particle_count;
    char *camera;
    SoundSlot *sound;
    float angle, step, size, yaw, pitch, speed;

    if ((unsigned char)moby[0x20] == 0) {
        *(float *)(moby + 0x18) += 1.5f;
        *(int *)(vars + 0x200) = 0;
        qcopy(vars + 0x210, moby + 0x10);
        *(int *)(vars + 0x204) = 0;
        frame.offset.q = 0;
        frame.offset.f[3] = 1.0f;
        frame.offset.f[2] = 3.0f;
        frame.direction.f[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8));
        frame.direction.f[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8));
        angle = 0.0f;
        frame.direction.f[3] = 1.0f;
        frame.direction.f[2] = angle;
        step = 6.283186f / (IntToFloat(9) - 1.0f);
        ring_point = vars;
        i = 8;
        do {
            math_build_axis_angle_quat(&frame.rotated, &frame.direction, angle);
            angle += step;
            --i;
            vec_rotate_by_quaternion(ring_point, &frame.offset, &frame.rotated);
            FastVecAdd(ring_point, ring_point, moby + 0x10);
            *(float *)(ring_point + 0xC) = 0.6f;
            ring_point += 0x10;
        } while (i >= 0);
        moby[0x20] = 1;
    }
    if ((unsigned char)moby[0x20] == 1 && math_fast_float_d((int *)(vars + 0x208))) {
        moby[0x20] = 2;
    }
    if ((unsigned char)moby[0x20] == 2) {
        frame.offset.f[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 0.10000001f;
        frame.offset.f[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * 0.10000001f;
        frame.offset.f[2] = 0.0f;
        FastVecAdd(moby + 0x10, &frame.offset, moby + 0x10);
        if (++*(int *)(vars + 0x204) > 0x1B0) {
            *(int *)(vars + 0x204) = 0;
            qcopy(moby + 0x10, vars + 0x210);
        }
        if (IsPointInCuboid(&g_hero_position, *(int *)(vars + 0x220))) {
            gfx_add_draw_callback_first(gfx_draw_scrolling_rings, moby);
        }
    }
    camera = (char *)&g_hero_position;
    if (IsPointInCuboid(camera, *(int *)(vars + 0x20C))) {
        qcopy(&frame.offset, &g_hero_position);
        frame.offset.f[2] += 0.75f;
        camera -= 0x80;
        if (coll_test_point(&frame.offset, 2, *(char **)(camera + 0x2290), 0.5f)) {
            if (!snd_is_voice_playing_for_owner(g_hero_moby, *(int *)(vars + 0x224))) {
                *(int *)(vars + 0x224) = snd_start_in_slot(0x18, 4, g_hero_moby);
            }
            qcopy(&frame.position, &g_hero_l00_position);
            particle_count = 0;
            do {
                size = math_random_float_range(1.0f, 2.0f);
                sign = math_random_int_below(2);
                if (!sign) {
                    sign = sign - 1;
                }
                yaw = math_random_angle();
                pitch = math_random_float_range(0.3490659f, 1.5358898639678955f);
                speed = math_random_float_range(0.05f, 0.1f);
                vec_build_spherical_offset(&frame.direction, speed, yaw, pitch);
                qcopy(&frame.rotated, &frame.position);
                frame.position.f[0] += math_random_signed_float_range(0.0f, 0.15f);
                --particle_count;
                frame.position.f[1] += math_random_signed_float_range(0.0f, 0.15f);
                frame.position.f[2] += math_random_signed_float_range(0.0f, 0.15f);
                part_spawn_ground_effect(&frame.position, 12, 0xFF400000, 0, sign, &frame.direction, size * 0.1f, size, 0.006f, 0);
                part_spawn_ground_effect(&frame.position, 12, 0x3F7F7F7F, 1, -sign, &frame.direction, size * 0.04f, size * 0.4f, 0.006f, 0);
            } while (particle_count >= 0);
            return;
        }
        /* Stop the sound if it is still the player's. Written out on each path: jump2 merges their tails. */
        handle = *(int *)(vars + 0x224);
        if (handle != -1) {
            sound = &g_sound_state[handle];
            if (sound[1].object == *(char **)(camera + 0x2290) && sound[1].active) {
                snd_stop_voice(handle);
            }
        }
        *(int *)(vars + 0x224) = -1;
    } else {
        handle = *(int *)(vars + 0x224);
        if (handle != -1) {
            sound = &g_sound_state[handle];
            if (sound[1].object == *(char **)(camera + 0x2210) && sound[1].active) {
                snd_stop_voice(handle);
            }
        }
        *(int *)(vars + 0x224) = -1;
    }
}
