
/* Bounded near miss, 2026-10-28: 668/668 bytes under the default profile.
 * Five forms. Naming the actual secondary source triple adds the real+0x30
 * base and restores the entire retail GPR allocation. Only initial scalar
 * snapshot/color setup differs from+0x58 before the first conversion; the
 * later scalar movement/fade flow matches. -fno-regmove ties; disabling the
 * first scheduler worsens the prologue. No broad flags retained.
 * Reopen with a truthful two-triple snapshot scheduling witness. The complete
 * particle view is0x40 bytes and all four local vectors are16 bytes; copied
 * source triples receive explicitw=0 stores present in retail. Packed shifts
 * use unsigned operands, including the sign-bit alpha cases.
 */
#include "common.h"

struct PackedMotion {
    float velocity[3];
    unsigned char color_alpha, frame_flags, lifetime, distance;
    float acceleration[3];
    unsigned char speed_start, speed_end, size_start, size_end;
};
struct PackedParticle {
    unsigned char unknown0[4];
    unsigned int color;
    unsigned char frame, unknown9;
    short remaining;
    float size;
    float position[4];
    struct PackedMotion motion;
};
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void func_00300190(char *, char *);
extern float func_002A7790(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282978(char *);
extern void func_002B9180(char *);

/* Complete0x40-byte particle prefix and four16-byte locals. Both packed
 * source triples become initialized vectors with explicit zero fourth lanes. */
void func_002C8CA0(struct PackedParticle *particle)
{
    float change[4], velocity[4], acceleration[4], step[4];
    struct PackedMotion *motion = &particle->motion;
    float *primary = motion->velocity;
    float *secondary = motion->acceleration;
    unsigned int color, alpha;
    int flags, frame_step;
    float size_start, size_end, speed_start, speed_end, distance;
    float life, progress;
    velocity[0] = primary[0];
    velocity[1] = primary[1];
    velocity[2] = primary[2];
    velocity[3] = 0.0f;
    acceleration[0] = secondary[0];
    acceleration[1] = secondary[1];
    acceleration[2] = secondary[2];
    acceleration[3] = 0.0f;
    color = motion->color_alpha & 15;
    color |= (color << 16) | (color << 8);
    alpha = (motion->color_alpha >> 4) | 0x70;
    flags = motion->frame_flags & 15;
    frame_step = motion->frame_flags >> 4;
    size_start = func_00283CE0(motion->size_start) * 1640.625f;
    size_end = func_00283CE0(motion->size_end) * 1640.625f;
    speed_start = func_00283CE0(motion->speed_start) * 0.0078125f;
    speed_end = func_00283CE0(motion->speed_end) * 0.0078125f;
    distance = func_00283CE0(motion->distance) * 0.0078125f;
    func_00300190((char *)particle->position, (char *)particle->position);
    life = func_00283CE0(particle->remaining);
    life /= func_00283CE0(motion->lifetime);
    progress = 1.0f - life;
    if (!flags) {
        particle->color = func_00283D38(0x103080, (int)color, progress) | (alpha << 24);
        particle->size = size_start + (size_end - size_start) * progress;
        speed_start += (speed_end - speed_start) * progress;
        func_00282D30(change, acceleration, distance * func_002A7790(progress));
    } else {
        float first_alpha, fade;
        int next_alpha;
        speed_start = speed_end;
        first_alpha = func_00283CE0(alpha);
        fade = func_00283CE0(alpha);
        fade *= func_002A7790(progress);
        next_alpha = func_00283CF0(first_alpha - fade);
        particle->color = color | ((unsigned int)next_alpha << 24);
        func_00282D30(change, acceleration, distance);
    }
    func_00282F20(step, velocity, speed_start);
    func_00282CC0(particle->position, particle->position, step);
    func_00282CC0(particle->position, change, particle->position);
    particle->frame += frame_step;
    if (func_00282978((char *)&particle->remaining)) {
        if (!flags) {
            motion->frame_flags |= 1;
            motion->lifetime = 20;
            particle->remaining = 20;
        } else func_002B9180((char *)particle);
    }
}
