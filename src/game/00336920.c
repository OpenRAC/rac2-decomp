#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

typedef float f32;

/* Stores two whole numbers as floats in the element's value pair. */
void hud_set_widget_value_pair(u8 *obj,s32 x,s32 y) {
 **(f32 **)(obj+0x34)=(f32)x;
 (*(f32 **)(obj+0x34))[1]=(f32)y;
}

/* reads a float through double indirection and returns its integer value; byte-identical across all 27 levels. */
s32 hud_get_widget_value_int(u8 *obj) { return (s32)*(f32 *)(*(u8 **)(obj + 0x34)); }

extern void *object_init_base(void *);
extern char D_001ADA18[] __attribute__((sda));

/* Starts building a UI element and sets its type pointer. */
char *hud_construct_widget_base(char *obj) {
    object_init_base(obj);
    *(char **)(obj + 0x30) = D_001ADA18;
    return obj;
}


extern void object_alloc_float4_arrays(void *);
extern unsigned char D_00263B50[];

/* Sets up a UI element: base setup, data pointer, flags and a default scale of 1. */
void hud_init_widget_defaults(char *obj)
{
    object_alloc_float4_arrays(obj);
    *(char **)(obj + 0x34) = (char *)D_00263B50;
    *(long long *)(obj + 0x38) = 1;
    *(int *)(obj + 0x40) = 0;
    **(float **)(obj + 4) = 1.0f;
    (*(float **)(obj + 4))[1] = 1.0f;
    *(int *)(obj + 0x44) = 1;
}

extern char D_001ADA18[] __attribute__((sda));
extern void object_destroy_array(void *);

/* Sets the element type pointer and runs the shared base cleanup. */
void hud_reset_widget_type_and_cleanup(char *obj) {
    *(char **)(obj + 0x30) = D_001ADA18;
    object_destroy_array(obj);
}

/* Stores a value in the element at offset 0x44. */
void hud_set_widget_field_a(int obj, unsigned int value)
{
  *(unsigned int*)(obj + 0x44) = value;
  return;
}

/* Stores a value in the element at offset 0x40. */
void hud_set_widget_field_b(int obj, unsigned int value)
{
  *(unsigned int *)(obj + 0x40) = value;
  return;
}

extern int text_measure_width_scaled(void *a0, s32 a1, void *a2, f32 a3);

/* Draws the element's text using its stored data and scale. */
int hud_draw_widget_text(u8 *obj)
{
    return text_measure_width_scaled(*(void **)(obj + 0x40), -1, *(void **)(obj + 0x34), *(f32 *)*(void **)(obj + 4));
}

