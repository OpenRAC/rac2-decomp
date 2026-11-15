/* func_L00_002C2DE8 (708 bytes, 27 places), in its own -G8 unit: the frame counter
 * D_L00_001B19C8 is one .sdata word, read as a lui/lw macro in ordinary flow and through $gp
 * in a delay slot (the reload after the % 3 guard, docs/build/compiler-notes.md, "a division guard
 * ends the redundant-insn search"). */
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

/* Every few frames, checks the ground and ledges around the hero and records what it finds,
 * such as a nearby target and whether there is room to step forward. */
void func_L00_002C2DE8(void)
{
    float first[4], second[4], probe[4];
    if (gHeroState.gate != 0) return;
    ref_L00_002C2DE8_00();
    if (gFrameCounter_L00 % 3 == 0) {
        gHeroState.height = 4.0f;
        gHeroState.first_flag = 0;
        gHeroState.second_flag = 0;
        if (TestHeroReachBlend(&gHeroState.height, 0.7f, 4.0f)) {
            gHeroState.angle = FastMatrixHelperA(gCollisionResult.direction[2], vec_length_xy(gCollisionResult.direction));
            if (gCollisionResult.object) {
                gHeroState.second_flag = 1;
                if (IsMobyInSpecialClassRange(gCollisionResult.object)) gHeroState.first_flag = 1;
            }
        }
    }
    if (gFrameCounter_L00 % 5 == 0) {
        int hit;
        float distance, offset;
        gHeroState.valid = 0;
        gHeroState.distance = 0.0f;
        if (gHeroState.enabled == 0) return;
        BuildHeroRelativePoint(first, 1.1f, 0.0f, 1, 1.0f);
        BuildHeroRelativePoint(second, 1.1f, 0.0f, 1, -20.0f);
        if (second[2] < 0.5f) second[2] = 0.5f;
        distance = 20.0f;
        hit = CollLine(first, second, 2, gHeroState.object, 0);
        if (hit) distance = fast_vec_dist(first, gCollisionResult.hit_position);
        if (!hit || 3.0f < distance) {
            offset = -0.4f;
            do {
                BuildHeroRelativePoint(probe, offset + 1.1f, 0.0f, 1, 0.0f);
                if (!TestPointAgainstCollision(probe, 2, 0, gHeroState.scale)) {
                    gHeroState.valid = 1;
                    if (!hit) gHeroState.distance = 20.0f;
                    else gHeroState.distance = distance;
                    gHeroState.clearance = gHeroState.scale + offset;
                    if (gHeroState.clearance < 0.0f) gHeroState.clearance = 0.0f;
                    return;
                }
                offset += 0.1f;
            } while (offset < 0.5f);
        }
    }
}
