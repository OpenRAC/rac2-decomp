#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

typedef float f32;

/* Stores two whole numbers as floats in the element's value pair. */
void func_00336920(u8 *obj,s32 x,s32 y) {
 **(f32 **)(obj+0x34)=(f32)x;
 (*(f32 **)(obj+0x34))[1]=(f32)y;
}

/* reads a float through double indirection and returns its integer value; byte-identical across all 27 levels. */
s32 func_00336950(u8 *obj) { return (s32)*(f32 *)(*(u8 **)(obj + 0x34)); }

extern void func_00335FB0(void *);
extern char D_001ADA18[] __attribute__((sda));

/* Starts building a UI element and sets its type pointer. */
char *func_00336968(char *obj) {
    InitBaseObject(obj);
    *(char **)(obj + 0x30) = D_001ADA18;
    return obj;
}


extern void func_00335FC8(void *);
extern unsigned char D_00263B50[];

/* Sets up a UI element: base setup, data pointer, flags and a default scale of 1. */
void func_003369A8(char *obj)
{
    AllocateFloat4Arrays(obj);
    *(char **)(obj + 0x34) = (char *)D_00263B50;
    *(long long *)(obj + 0x38) = 1;
    *(int *)(obj + 0x40) = 0;
    **(float **)(obj + 4) = 1.0f;
    (*(float **)(obj + 4))[1] = 1.0f;
    *(int *)(obj + 0x44) = 1;
}

extern char D_001ADA18[] __attribute__((sda));
extern void func_003360F8(void *);

/* Sets the element type pointer and runs the shared base cleanup. */
void func_00336A08(char *obj) {
    *(char **)(obj + 0x30) = D_001ADA18;
    DestroyArrayObject(obj);
}

/* Stores a value in the element at offset 0x44. */
void func_00336A30(int obj, unsigned int value)
{
  *(unsigned int*)(obj + 0x44) = value;
  return;
}

/* Stores a value in the element at offset 0x40. */
void func_00336A38(int obj, unsigned int value)
{
  *(unsigned int *)(obj + 0x40) = value;
  return;
}

extern void func_0027F1D8(void *a0, s32 a1, void *a2, f32 a3);

/* Draws the element's text using its stored data and scale. */
void func_00336A40(u8 *obj)
{
    MeasureTextWidthScaled(*(void **)(obj + 0x40), -1, *(void **)(obj + 0x34), *(f32 *)*(void **)(obj + 4));
}

