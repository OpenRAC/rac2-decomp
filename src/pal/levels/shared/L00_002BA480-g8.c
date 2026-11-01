#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x264]; float scale;
    unsigned char pad1[0x278 - 0x268]; float height;
    unsigned char pad2[4]; float angle;
    unsigned char first_flag, second_flag, pad3[2];
    float distance, clearance; int valid;
    unsigned char pad4[0x340 - 0x294]; int enabled;
    unsigned char pad5[0x2290 - 0x344]; void *object;
    unsigned char pad6[0x22BD - 0x2294]; unsigned char gate;
} HeroProbeState;
extern HeroProbeState D_00189E20;
typedef struct {
    unsigned char pad0[0x18]; void *object;
    unsigned char pad1[4]; float hit_position[4];
    unsigned char pad2[0x10]; float direction[4];
} SceneProbeState;
extern SceneProbeState D_L00_001BF200;
extern int D_L00_001B19C8 MACRO_ADDR;
extern void ref_L00_002C2DE8_00(void);
extern int func_L00_002AB108(float *, float, float);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern int func_002ABB78(void *);
extern void func_L00_002D36E0(float *, float, float, int, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_00282E48(void *, void *);
extern int func_00277258(void *, int, void *, float);

void func_PAL_L00_002C2F88(void)
{
    float first[4], second[4], probe[4];
    if (D_00189E20.gate != 0) return;
    ref_L00_002C2DE8_00();
    if (D_L00_001B19C8 % 3 == 0) {
        D_00189E20.height = 4.0f;
        D_00189E20.first_flag = 0;
        D_00189E20.second_flag = 0;
        if (func_L00_002AB108(&D_00189E20.height, 0.7f, 4.0f)) {
            D_00189E20.angle = func_00283248(D_L00_001BF200.direction[2], func_00282E20(D_L00_001BF200.direction));
            if (D_L00_001BF200.object) {
                D_00189E20.second_flag = 1;
                if (func_002ABB78(D_L00_001BF200.object)) D_00189E20.first_flag = 1;
            }
        }
    }
    if (D_L00_001B19C8 % 5 == 0) {
        int hit;
        float distance, offset;
        D_00189E20.valid = 0;
        D_00189E20.distance = 0.0f;
        if (D_00189E20.enabled == 0) return;
        func_L00_002D36E0(first, 1.1f, 0.0f, 1, 1.0f);
        func_L00_002D36E0(second, 1.1f, 0.0f, 1, -20.0f);
        if (second[2] < 0.5f) second[2] = 0.5f;
        distance = 20.0f;
        hit = func_002761F8(first, second, 2, D_00189E20.object, 0);
        if (hit) distance = func_00282E48(first, D_L00_001BF200.hit_position);
        if (!hit || 3.0f < distance) {
            offset = -0.4f;
            do {
                func_L00_002D36E0(probe, offset + 1.1f, 0.0f, 1, 0.0f);
                if (!func_00277258(probe, 2, 0, D_00189E20.scale)) {
                    D_00189E20.valid = 1;
                    if (!hit) D_00189E20.distance = 20.0f;
                    else D_00189E20.distance = distance;
                    D_00189E20.clearance = D_00189E20.scale + offset;
                    if (D_00189E20.clearance < 0.0f) D_00189E20.clearance = 0.0f;
                    return;
                }
                offset += 0.1f;
            } while (offset < 0.5f);
        }
    }
}
