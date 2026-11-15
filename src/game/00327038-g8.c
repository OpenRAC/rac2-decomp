#include "include_asm.h"
#include "names.h"

/* The threshold lives in small data, so this file is built with -G8. It differs
   from program to program, so it carries no level. */
extern float ref_L00_00327D08_00 __attribute__((sda));
extern void func_002FC808(void);
extern void func_00327D50(char *);

/* Runs the shared update, then advances the object's sub-record while its
   stored float is still below the small-data threshold. */
void func_00327D08(char *a0)
{
    float value;

    AppendVu1DmaChainTable3();
    value = *(float *)(*(char **)(a0 + 0x68) + 0x24);
    if (value < ref_L00_00327D08_00)
        DrawDistortionRing(a0);
}

extern int D_001B1688;
extern char *D_001B1B68;
extern float ref_L00_00327A60_00 __attribute__((sda));
extern float func_00282E48(void *, void *);
extern void func_00302440(void *, void *);

/* The camera block the level keeps, with the fields this body writes. */
typedef struct {
    unsigned char pad_000[0x218];
    int field_218;
    float field_21C;
    unsigned char pad_220[8];
    float field_228;
    float field_22C;
    int field_230;
    int field_234;
    int field_238;
} Ref_L00_0032E4F0_Block;

extern Ref_L00_0032E4F0_Block ref_L00_0032E4F0_00;
extern float D_001B0870 __attribute__((sda));
extern int D_001B0820 __attribute__((sda));
extern int D_001B0824 __attribute__((sda));
extern float ref_L00_0032E4F0_04;
extern void func_0027AB40(void);

/* Scales the resident zoom value by the argument's size, keeps it in the
   camera block and hands the block to the shared update. */
void func_0032E4F0(float size)
{
    Ref_L00_0032E4F0_Block *block = &ref_L00_0032E4F0_00;
    float zoom = size * (D_001B0870 * 1024.0f);

    D_001B0824 = D_001B0820;
    block->field_228 = 255.0f;
    block->field_22C = 100.0f;
    block->field_21C = zoom;
    ref_L00_0032E4F0_04 = size;
    block->field_218 = 0;
    block->field_230 = 0xFF;
    block->field_234 = 0xFF;
    block->field_238 = 0xFF;
    UpdateViewContext();
}

/* Looks through the live objects and reacts to each one of a certain kind that is close to this object. */
void func_00327A60(char *object)
{
    char *cursor;
    if (gGameTime & 1) {
        cursor = D_001B1B68;
        while (cursor) {
            int kind = *(unsigned char *)(cursor + 0x20);
            if (kind == 0xfe) return;
            if (kind == 0xfd) return;
            if (cursor && *(char **)(cursor + 0x24) &&
                *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                if (fast_vec_dist(cursor + 0x10, object + 0x10) < ref_L00_00327A60_00)
                    StartPickupFlyIfIdle(cursor, object);
            }
            cursor = *(char **)(cursor + 0x28);
        }
    }
}
