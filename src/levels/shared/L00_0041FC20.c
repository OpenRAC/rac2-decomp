#include "common.h"

typedef struct { float x,y,z,w; } ImpactVector;
extern float D_L00_001B8DC0[];
extern float D_L00_001A8F20[] MACRO_ADDR;
extern float func_002A7878(float, float), func_002A7940(void), func_002A78D8(float, float);
extern int func_002A7820(int, int);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_L00_0033E888(float, float, void *, void *, int, int, int, int, int, int, int);
extern void *func_L00_0033EC48(float, void *, float, int, int, int, int, float *, int, int, short, int);

/* Both effect constructors replace the copied position W before consumption;
 * 0033E888 likewise replaces velocity W with its rotation value. */
/* Spawns a burst of blue sparks and flashes where a shot hits something. */
void func_L00_0041FC20(float *position, void *unused, int shortLife)
{
    ImpactVector velocity, offset, point;
    int i = 1;
    float pitch, yaw, life;
    do {
        pitch = RandomFloatRange(-0.9599312f, -1.3962636f);
        yaw = RandomAngle();
        BuildSphericalOffset(&velocity, RandomFloatRange(0.0f, 0.5f) * 0.016666668f, yaw, pitch);
        FastVecSub(&offset, gCameraPosition_L00, position);
        vec_scale_to_length(&offset, &offset, 0.15f);
        FastVecAdd(position, position, &offset);
        life = RandomFloatRange(30000.0f, 60000.0f);
        point.x = position[0] + RandomSignedFloatRange(0.0f, 0.15f);
        point.y = position[1] + RandomSignedFloatRange(0.0f, 0.15f);
        point.z = position[2] + RandomSignedFloatRange(0.0f, 0.15f);
        if (shortLife)
            SpawnSpinningParticle_L00(life, 0.5f, &point, &velocity, 0x4F93E5FF, 0x102434EE,
                              RandomIntRange(10, 20), 1, -1, -1, 1);
        else
            SpawnSpinningParticle_L00(life, 0.5f, &point, &velocity, 0x4F93E5FF, 0x102434EE,
                              RandomIntRange(25, 60), 1, -1, -1, 1);
    } while (--i >= 0);
    SpawnPulledParticle(0.1f, position, 1.05f, 40, 0x64FFFFFF, 2, 4, D_L00_001A8F20, 0, 1, 6, 1);
    SpawnPulledParticle(0.4f, position, 2.05f, 30, 0x3C388EF7, 2, 0, D_L00_001A8F20, 0, 0, 6, 1);
    SpawnPulledParticle(0.15f, position, 1.65f, 40, 0x32388EF7, 0, 2, D_L00_001A8F20, 0, 4, 6, 1);
    SpawnPulledParticle(0.5f, position, 2.35f, 27, 0x3C0063F7, 2, 0, D_L00_001A8F20, 3, 0, 6, 1);
    SpawnPulledParticle(0.3f, position, 1.75f, 27, 0x1E0063F7, 1, -2, D_L00_001A8F20, 3, 4, 6, 1);
    SpawnPulledParticle(1.25f, position, 1.7f, 70, 0x2D002DFF, 0, 0, D_L00_001A8F20, 4, 3, 6, 1);
    SpawnPulledParticle(0.9f, position, 0.7f, 10, 0x3C787878, 2, 2, D_L00_001A8F20, 0, 2, 6, 1);
    SpawnPulledParticle(1.7f, position, 0.7f, 10, 0x3C787878, 2, -1, D_L00_001A8F20, 1, 2, 6, 1);
    SpawnPulledParticle(2.0f, position, 1.5f, 10, 0x23787878, 2, 1, D_L00_001A8F20, 1, 2, 6, 1);
}
