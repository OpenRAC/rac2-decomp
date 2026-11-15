#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

extern f32 func_00282C48(f32 t);
extern f32 func_00282C10(f32 t);

/* Clamps the measured value at P into the band the two arguments describe: the value is
   pulled down to the square root of twice the radius times the rate when it lies above it,
   and up to the opposite bound when it lies below.  The division is on its own line: the
   unit carries -g, so the assembler's division padding is reproduced. */
/* Limits a speed value so the object can still stop in time, using the given limit and braking rate. */
void func_L16_00317C90(f32 *speedPtr, f32 direction, f32 brake)
{
    f32 speed = *speedPtr;
    f32 brakeDistance;
    f32 maxSpeed;
    f32 latest;

    if (speed * direction <= 0.0f) {
        return;
    }
    if (direction == 0.0f) {
        return;
    }
    brakeDistance = (speed * speed / brake) * 0.5f;
    if (!(FloatAbs(direction) < brakeDistance)) {
        return;
    }
    maxSpeed = square_root((brake + brake) * direction);
    latest = *speedPtr;
    if (maxSpeed < latest) {
        *speedPtr = maxSpeed;
    } else {
        maxSpeed = -maxSpeed;
        if (latest < maxSpeed) {
            *speedPtr = maxSpeed;
        }
    }
}
