#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

/* func_L16_002B5EE0 is in L16_002B5EE0-motion.c. */



/* func_L16_00395858 is in L16_00395858-state.c. */

/* func_L16_003959B8 is in L16_003959B8.c. */

extern char g_hero_state[];
extern void vec_transform_by_object_or_given(char *object, void *out, void *table, int a3);
extern float mat_fast_helper_a(float a, float b);
extern float math_fabs(float a);
extern void vec_scale_to_length(char *dst, char *src, float x);
extern float math_fast_sin_or_cos_b(float a);
extern float math_fast_sin_or_cos_a(float a);
extern void quaternion_to_rotation_basis(char *a, char *b);
extern void multiply_matrix3x3(char *a, char *b, char *c);

/* steers the object along the ground normal the terrain query returns */
/* func_L16_00395C00 uses its dedicated compiler profile. */

/* func_L16_00395D30 is defined in L16_00395D30-g16.c. */

/* func_L16_00395ED0 is in L16_00395ED0-blend-g8.c. */

/* Read and return the float at linked offset 0x 34 through the pointer stored at owner+0x 68. */
float moby_get_linked_float(const unsigned char *owner)
{
    const unsigned char *linked = *(const unsigned char * const *)(owner + 0x68);
    return *(const float *)(linked + 0x34);
}

extern int func_002DA3C8(void *v, int a1, char *object, int a3, float f);
extern char *g_blocker_moby_table[];

/* reports whether the first live marker in the run still carries the kind byte it looks for */
/* func_L16_003960F8 uses its dedicated compiler profile. */

/* func_L16_003A8D58 is in L16_002B5EE0-shot.c. */


/* func_L16_003C2C08 is in L16_002B5EE0-state-g8.c. */

/* func_L16_003C32F8 is in L16_003C32F8-render-g64.c. */

/* func_L16_003C3870 uses its dedicated compiler profile. */

/* func_L16_003C3A10 uses its dedicated compiler profile. */

/* func_L16_004051A8 is in L16_004051A8-g8.c. */




/* func_L16_0040BED0 is in L16_0040BED0.c. */

/* func_L16_0040C5F0 is defined in L16_0040C5F0-g8.c. */

extern char *g_beam_definition_table __attribute__((sda));
extern char *g_moby_instance_table __attribute__((sda));

/* copies the 16-byte record the object's two indices pick out of the chosen table into dst */
/* Defined in L16_0040C7E8-g8.c. */

/* func_L16_00413850 is in L16_00413850.c. */



extern char *g_linked_node_state_ptr;

/* pushes the two axis values onto the linked node, unless the node is inert or a value is zero */
void moby_push_axis_to_linked_node(float x, float y)
{
    char *st = g_linked_node_state_ptr;
    char *p;

    if (*(s16 *)(st + 0x86) != 0)
        return;
    p = *(char **)(st + 0x70) + 0x20;
    if (x != 0.0f)
        *(float *)(p + 0x1C) = x;
    if (y != 0.0f)
        *(float *)(p + 0x20) = y;
}

extern void cam_update_zone_control(void);

/* runs the level's one-shot start-up; the caller uses this only for its side effects */
int level_run_startup(void)
{
    cam_update_zone_control();
    return 0;
}
