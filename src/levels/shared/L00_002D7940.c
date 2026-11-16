#include "include_asm.h"
#include "names.h"

typedef int s32;

extern float func_00283180_13(float x);

extern float func_00283198_14(float x);

extern void func_00282CC0_42(float *out, float *in, void *q);

typedef unsigned char u8;

typedef float f32;

extern void gravity_offset_position(char *a, char *b, char *c, f32 d);

extern void func_00282CC0_5(char *a, char *b, char *c);

extern void func_00283098_1(char *a, char *b, char *c);

extern void quaternion_to_rotation_basis(char *a, char *b);

extern void multiply_matrix3x3(char *a, char *b, char *c);

extern void func_00282CF0_4(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif

#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif

#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif

/* clear five object fields; independently qualified in this overlay */
/* Sets five whole-number fields of an object to zero. */
void moby_zero_five_words(s32 *object) {
    object[0]=0; object[1]=0; object[2]=0; object[3]=0; object[4]=0;
}

extern float FastAddRotations(float, float);

/* blends the first component of the source through the helper, then copies the four
   remaining components straight across */
/* Copies five numbers, passing the first one through a helper first. */
void vec_copy5_blend_first(f32 *dst, f32 *src, f32 x) {
 dst[0]=FastAddRotations(src[0],x);
 dst[1]=src[1];
 dst[2]=src[2];
 dst[3]=src[3];
 dst[4]=src[4];
}


typedef void (*L00_Dispatch)(void *);

typedef struct {
    L00_Dispatch entries[5];
} L00_DispatchRecord;

/* The shared class table: a 0x14-byte record per type index, its entries at +0x8. */
extern L00_DispatchRecord g_moby_class_dispatch_table[];

/* Calls the object's class entry 2 for the type index in its +0x8C halfword. */
/* Runs the object's type-specific update step, if its type has one. */
void moby_call_class_update(char *object) {
    L00_Dispatch callback = g_moby_class_dispatch_table[*(short *)(object + 0x8C)].entries[2];
    if (callback != 0)
        callback(object);
}

/* Calls the object's class entry 4 for the type index in its +0x8C halfword. */
/* Runs the object's type-specific cleanup step, if its type has one. */
void moby_call_class_cleanup(char *object) {
    L00_Dispatch callback = g_moby_class_dispatch_table[*(short *)(object + 0x8C)].entries[4];
    if (callback != 0)
        callback(object);
}

typedef struct {
    int key;
    int pad[4];
} E_r002D9D48;

extern E_r002D9D48 r1_D_L00_001EAC00[];

/* rac1-decomp src/overlays/shared/camera_001EB508.c: func_L00_001ED5B0 */
/* Returns the index of the entry with the given key, or of the -1 terminator. */
/* Looks up a camera entry by its id number and returns its position in the list. */
int cam_find_entry_index(int key) {
    int i = 0;
    while (r1_D_L00_001EAC00[i].key != -1 && r1_D_L00_001EAC00[i].key != key) {
        i++;
    }
    return i;
}



/* func_L00_002D9E80 is in L00_002D7940-setup-g8.c. */

/* Builds a 3-component vector from a spherical radius/elevation/azimuth triple using two unary float helpers, clears the 4th component, then forwards the destination twice plus a third argument to a final helper. */
/* Turns an angle-and-distance description into a direction vector, then rotates it with a matrix. */
void vec_spherical_to_vector(float *out, float *p, void *q)
{
    float t;

    t = func_00283180_13(p[1]);
    out[0] = p[2] * t * func_00283180_13(p[0]);
    t = func_00283180_13(p[1]);
    out[1] = p[2] * t * func_00283198_14(p[0]);
    out[2] = p[2] * func_00283198_14(p[1]);
    out[3] = 0.0f;
    func_00282CC0_42(out, out, q);
}

/* func_L00_002DA1E0 is in L00_002D7940-motion.c. */


/* func_L00_002DB350 is in L00_002D7940-grid.c. */

/* func_L00_002DB4B8 is in L00_002D7940-shape.c. */

/* Return the constant signed integer one. */
/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
/* Always answers yes (1). */
int math_return_one(void) {
    return 1;
}

/* Return the constant signed integer one. */
/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
/* Always answers yes (1). */
int math_return_one_alt(void) {
    return 1;
}

/* Drives eight calls over a parameter object: loads the pointer at +104, builds four 16-byte stack scratch records at sp+0/+16/+32/+48, and passes the object's +16 and +192 regions to the callees. */
/* Moves an object's position and orientation toward those of its parent object. */
void moby_follow_parent_transform(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    gravity_offset_position((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    func_00282CC0_5((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    func_00283098_1((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    quaternion_to_rotation_basis((char *)p + 0x10, (char *)&tmp[3]);
    multiply_matrix3x3((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    func_00283098_1((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    func_00282CF0_4((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    func_00282CF0_4((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

/* Drives eight calls over a parameter object: loads the pointer at +104, builds four 16-byte stack scratch records at sp+0/+16/+32/+48, and passes the object's +16 and +192 regions to the callees. */
/* Moves an object's position and orientation toward those of its parent object. */
void moby_follow_parent_transform_alt(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    gravity_offset_position((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    func_00282CC0_5((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    func_00283098_1((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    quaternion_to_rotation_basis((char *)p + 0x10, (char *)&tmp[3]);
    multiply_matrix3x3((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    func_00283098_1((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    func_00282CF0_4((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    func_00282CF0_4((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

ASM_FUNC("asm/levels", func_L00_002E0200);

/* func_L00_002E2048 (packed status field) is a near miss:
   nonmatching/levels/func_L00_002E2048.c */
/* Original assembly: trapping addi; the compiler cannot emit it. */
ASM_FUNC("asm/levels", func_L00_002E2048);


/* func_L00_002E2958 is in L00_002D7940-wipe.c. */

/* func_L00_002E2C30 is in L00_002D7940-fade.c. */

/* func_L00_002E30B8 is in L00_002D7940-g8.c. */

#ifndef MACRO_ADDR
#define MACRO_ADDR __attribute__((section(".sdata")))
#endif

typedef struct {
    int key, firstKey;
    int reserved08, reserved0C, width;
    int origin;
    int reserved18, reserved1C, step, reserved24;
} TextGroup;
typedef struct {
    char reserved00[0x20];
    short group;
    char reserved22[0x384 - 0x22];
    int anchor;
} TextContextPrefix;

extern TextGroup g_fading_text_layouts[];
extern char g_fading_text_style[];
extern int g_screen_width MACRO_ADDR;
extern int AdvanceGroupedTableOffset(int, int *, int *);
extern int text_find_level_by_key(int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long long);
extern void FontSetWindow(unsigned short *, int, int, int, int, int, int, int, int);
extern void text_draw_window_small(unsigned short *, unsigned long, unsigned char *, int);

/* The layout constructor initializes all twelve halfwords consumed by FontPrint. */
/* Draws one line of caption text with a dark bar and a shadow behind it. */
void text_draw_caption_line(int row, float alpha)
{
    unsigned short layout[12];
    int group, index;
    unsigned char *text;
    TextContextPrefix *context;
    int origin;
    if (!AdvanceGroupedTableOffset(row, &group, &index)) return;
    text = (unsigned char *)text_find_level_by_key(g_fading_text_layouts[group].firstKey + index);
    if (!text) return;
    context = (TextContextPrefix *)g_fading_text_style;
    origin = g_fading_text_layouts[context->group].origin + row * g_fading_text_layouts[context->group].step;
    gfx_draw_colored_rectangle(origin + 2, origin + g_fading_text_layouts[context->group].step - 2,
        0, g_screen_width, (unsigned long long)((int)(alpha * 96.0f) << 24));
    FontSetWindow(layout, origin, origin + g_fading_text_layouts[context->group].step, 0,
        g_screen_width, g_screen_width / 2 + 2,
        origin + g_fading_text_layouts[context->group].step / 2 + 1, context->anchor, 3);
    text_draw_window_small(layout, 0x80000000UL, text, -1);
    FontSetWindow(layout, origin, origin + g_fading_text_layouts[context->group].step, 0,
        g_screen_width, g_screen_width / 2,
        origin + g_fading_text_layouts[context->group].step / 2, context->anchor, 3);
    text_draw_window_small(layout, 0xFFFFFFFFUL, text, -1);
}

/* Draw the current caption over six successively shaded bars. */
/* Draws the current caption text with a shaded bar fading out above it. */
void text_draw_caption_bars(void)
{
    int text = text_find_level_by_key(g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].key);
    unsigned short layout[12];
    int i, y, bottom;

    if (text) {
        FontSetWindow(layout, 0, g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].origin, 0,
            g_screen_width, g_screen_width / 2,
            g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].width, 18, 1);
        text_draw_window_small(layout, 0xFFFFFFFFUL, (unsigned char *)text, -1);
        bottom = g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].origin - 2;
        y = g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].origin - 4;
        for (i = 0; i < 6; i++) {
            gfx_draw_colored_rectangle(bottom - y, bottom, -g_screen_width, g_screen_width * 2, 0x18000000);
            y = y * 5 / 6;
        }
        FontSetWindow(layout, 0, g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].origin, 0,
            g_screen_width, g_screen_width / 2,
            g_fading_text_layouts[((TextContextPrefix *)g_fading_text_style)->group].width, 18, 1);
        text_draw_window_small(layout, 0xFFFFFFFFUL, (unsigned char *)text, -1);
    }
}

#ifndef RAC2_T_REC_2E36F8
#define RAC2_T_REC_2E36F8
typedef struct {
    s32 value;         /* +0x00 */
    s32 key;           /* +0x04 */
    char pad08[8];
} Rec_2e36f8;
#endif

extern s32 ref_L00_001BC200_00[];

/* Linear search of the level's record list (sixteen-byte stride): the block's fourth word
 * holds the list pointer and its fifth the count; the record's second word is the key, and a
 * match returns its first word. Zero when the count is not positive or nothing matches. */
/* Finds the text for a key in the level's text list and returns it, or 0 if missing. */
s32 text_find_level_by_key(s32 key)
{
    Rec_2e36f8 *entry;
    s32 count = ref_L00_001BC200_00[4];
    s32 i;

    if (count > 0) {
        i = 0;
        entry = (Rec_2e36f8 *)ref_L00_001BC200_00[3];
        do {
            if (entry->key == key)
                return entry->value;
            entry++;
            i++;
        } while (i < count);
    }
    return 0;
}

extern int func_2EDD48(void *);
extern char ref_L00_001BC228_00[];

/* Thin forwarder: hands one global to the shared handler. */
/* Passes a global object to a shared handler. */
void level_forward_to_shared_handler(void) {
    func_2EDD48(ref_L00_001BC228_00);
}

/* evaluates (b-a)*(t*t)+a*t and converts the measured float result to a signed word */
/* Blends smoothly from a toward b over t (0 to 1), then rounds to a whole number. */
s32 math_blend_quadratic_to_int(f32 a,f32 b,f32 t) {
 f32 difference=b-a;
 f32 squared=t*t;
 a=a*t;
 difference=difference*squared;
 a=a+difference;
 return (s32)a;
}

/* A .sdata flag the compiler addresses through the assembler macro (lui + lbu in one register). */
extern unsigned char g_weighted_taps_skip_flag __attribute__((section(".sdata")));
typedef struct {
    u8 row;
    u8 col;
    short weight;
} WeightTap;

extern WeightTap g_weight_tap_table[][16][10];
extern int g_tap_weight_grid[][16];

/* Adds up ten weighted values from a table for a pair of indices, or returns 0 if out of range. */
int math_sum_weighted_table_taps(int a, int b)
{
    WeightTap *tap;
    int sum;
    int n;

    if (g_weighted_taps_skip_flag != 0 || a >= 21)
        return 0;
    if (b >= 16)
        return 0;
    tap = g_weight_tap_table[a][b];
    sum = 0;
    for (n = 9; n >= 0; n--) {
        sum += tap->weight * g_tap_weight_grid[tap->row][tap->col];
        tap++;
    }
    return sum;
}
