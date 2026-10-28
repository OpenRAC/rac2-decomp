/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por.
 * Emitted/retail size: 600/592 bytes.
 * us: 0 of 13 places match.
 * pal: ABSENT.
 * us2: 0 of 13 places match.
 * No strict linked build was run for this draft.
 * The optional rotation pointer and count compete for a saved register; alpha spills instead of remaining in a register. The real eight-GPR/two-FPR spawn interface and full 16-byte rotations are retained. A positive countdown loop ties. Reopen with allocator evidence.
 */
#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef union { TI q; float f[4]; } Vector;
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern char *func_00273730(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_L00_0039B288(char *);
extern void func_002A0488(char *, unsigned long, unsigned long, unsigned long);

void func_L00_003263D0(char *owner, void *origin, int count, int mode,
                      void *velocity_origin, int color, Vector *fixed_rotation,
                      float radius, float speed, float low_scale, float high_scale)
{
    Vector velocity, position, rotation, random_rotation;
    char *effect, *payload;
    int kind, variant;
    int r, g, b, alpha, colored;
    float life;
    if (count <= 0)
        return;
    do {
        func_002A7A00(&velocity, 0.0f, speed * 0.016666668f);
        func_00282CC0(&velocity, &velocity, velocity_origin);
        func_002A7A00(&position, 0.0f, radius);
        func_00282CC0(&position, &position, origin);
        random_rotation.q = 0;
        random_rotation.f[0] = func_002A7940();
        random_rotation.f[2] = func_002A7940();
        rotation.q = random_rotation.q;
        if (fixed_rotation != 0)
            qcopy(&rotation, fixed_rotation);
        kind = mode ? 2 : 1;
        variant = func_002A77E0(4);
        life = func_002A7878(10.0f, 20.0f);
        effect = func_00273730(owner, kind, 0x43e, variant, &position, &rotation, &velocity, 0xff, 180.0f, life);
        if (effect != 0) {
            *(void (**)(char *))(effect + 0x64) = func_L00_0039B288;
            r = color & 0xff;
            alpha = (unsigned int)color >> 24;
            *(float *)(effect + 0x2c) = *(float *)(*(char **)(effect + 0x24) + 0x24) * func_002A7878(low_scale, high_scale);
            b = (color >> 16) & 0xff;
            g = (color >> 8) & 0xff;
            payload = *(char **)(effect + 0x68);
            func_002A0488(effect, r, g, b);
            ((unsigned char *)effect)[0x23] = alpha;
            colored = (r != g || r != b);
            *(u32 *)(payload + 0x50) = (colored << 24) | (b << 16) | (g << 8) | r;
        }
    } while (--count != 0);
}
