#include "include_asm.h"
#include "names.h"

/* func_L23_00422798 is a unit of its own: retail clears its local direction as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps
   (config/cflags.txt). */

typedef unsigned char u8;

typedef unsigned int u32;

typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B1908 __attribute__((sda));

extern float D_L23_001B190C __attribute__((sda));

extern float D_L23_001B18E0 __attribute__((sda));

extern u32 D_L23_001B18E4 __attribute__((sda));

extern u32 D_L23_001B18E8 __attribute__((sda));

extern u32 D_L23_001B18EC __attribute__((sda));

extern u32 D_L23_001B18F0 __attribute__((sda));

extern s32 D_L23_001B18F4 __attribute__((sda));

extern u32 D_L23_001B18F8 __attribute__((sda));

extern s32 D_L23_001B18FC __attribute__((sda));

extern u32 D_L23_001B1900 __attribute__((sda));

extern s32 D_L23_001B1904 __attribute__((sda));

extern float func_00282DF0(void *);

extern float func_002A7940(void);

extern void func_00281EB8(void *, s32, u32, s32, float, float, float);

extern void func_L00_002ECFE8(void *, void *, s32, u32, s32, s32, float, float, float);

/* scrolls the effect's phase, spawns three particles around it, and once the phase passes the
   limit emits three more through the shared emitter with the local direction {0, 0, 0, 1} */
/* Per-frame update of a scrolling energy effect. It spawns a few glowing particles and,
   once the effect has built up, shoots out three more. */
void func_L23_00422798(u8 *obj) {
    float direction[4];
    u8 *vars = *(u8 **)(obj + 0x68);
    float phase;
    float scrollStep;
    float size;

    *(TI128 *)direction = 0;
    direction[3] = 1.0f;
    phase = *(float *)(vars + 0x14) - 0.1f;
    *(float *)(vars + 0x14) = phase;
    if (phase <= -8.0f) {
        *(float *)(vars + 0x14) = phase + 8.0f;
    }
    scrollStep = FastVecLength(vars);
    size = D_L23_001B1908 * 0.2f;
    *(float *)(vars + 0x18) = *(float *)(vars + 0x18) + scrollStep;
    DrawBillboardQuad_00281EB8(obj + 0x10, 0x31, D_L23_001B18E4, 1, size, 0.0f, RandomAngle());
    DrawBillboardQuad_00281EB8(obj + 0x10, 0x31, D_L23_001B18E8, 1, D_L23_001B1908 * 0.1f, 0.0f, RandomAngle());
    DrawBillboardQuad_00281EB8(obj + 0x10, 0x2F, D_L23_001B18EC, 1, D_L23_001B1908 * 0.05f, 0.0f, RandomAngle());
    if (*(float *)(vars + 0x18) > D_L23_001B18E0) {
        DrawOrientedQuadsAtPoints(obj, direction, 1, D_L23_001B18F0, D_L23_001B18F4, 0x17, D_L23_001B1908 * 0.02f,
                          D_L23_001B190C * D_L23_001B1908, *(float *)(vars + 0x14));
        DrawOrientedQuadsAtPoints(obj, direction, 1, D_L23_001B18F8, D_L23_001B18FC, 0x17, D_L23_001B1908 * 0.07f,
                          D_L23_001B190C * D_L23_001B1908, *(float *)(vars + 0x14));
        DrawOrientedQuadsAtPoints(obj, direction, 1, D_L23_001B1900, D_L23_001B1904, 0x17, D_L23_001B1908 * 0.07f,
                          D_L23_001B190C * D_L23_001B1908, *(float *)(vars + 0x14));
    }
}
