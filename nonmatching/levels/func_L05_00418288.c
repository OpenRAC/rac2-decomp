/* func_L05_00418288 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G16 -Wa,-G16 -ffunction-sections.
 * Measured in src/levels/shared/L05_00418288-g8.c: 444/436 bytes.
 * US: 0/4 local places; PAL: 0/4 local places; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * The 16-byte rotation view preserves the helper read extent, but mixed GP/absolute field access and copy scheduling differ. Reopen with field-origin evidence; do not shrink the rotation object.
 */

#include "common.h"

typedef struct { float x, y, z; int flags; } Rotation;
typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector rows[3]; } Matrix;
extern int D_L05_001B0FA4 __attribute__((sda));
extern char D_L05_001C7840[];
extern Rotation D_L05_001B34E0;
extern Vector D_L05_001B34F0;
extern float D_L05_001B3500;
extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D90(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

void func_L05_00418288(char *object)
{
    Vector value;
    Matrix rotation;
    char *entry = D_L05_001C7840 + D_L05_001B0FA4 * 32;
    char *position = object + 0x10;
    char *output = entry + 0x10;
    D_L05_001B34E0.flags = 0;
    D_L05_001B34E0.x = func_00283B98(D_L05_001B34E0.x, 0.1f);
    D_L05_001B34E0.y = func_00283B98(D_L05_001B34E0.y, 0.09f);
    D_L05_001B34E0.z = func_00283B98(D_L05_001B34E0.z, 0.11f);
    func_00282C88(&value);
    value.x = 0.4f;
    func_002833F0(&rotation, &D_L05_001B34E0);
    func_00283098(&value, &value, &rotation);
    func_00282CC0(&value, &value, position);
    qcopy(output, &value);
    *(float *)(entry + 0x1C) = 3.0f;
    if (D_L05_001B3500 > 0.0f) {
        func_00282D90(&D_L05_001B34F0, &D_L05_001B34F0, D_L05_001B3500);
        func_00282CF0(&D_L05_001B34F0, &D_L05_001B34F0, position);
        func_00282F20(&D_L05_001B34F0, &D_L05_001B34F0, 5.0f);
        func_00282CC0(&D_L05_001B34F0, &D_L05_001B34F0, position);
        qcopy(output, &D_L05_001B34F0);
        *(float *)(entry + 0x1C) = 10.0f;
    } else {
        *(float *)(entry + 0x1C) = 0.0f;
    }
    func_00282C88(&D_L05_001B34F0);
    D_L05_001B3500 = 0.0f;
}