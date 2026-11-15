#include "include_asm.h"
#include "common.h"

extern int func_00282978_1(char *p);

extern void func_002B9180_1(char *p);

extern void func_00282CC0_1(char *p0, char *p1, char *p2);

extern int func_00282978_11();

extern void func_002B9180_17();

extern float IntToFloat(int a);

extern int func_00283CF0_2(float f);

extern int func_00283D38_1(int a, int b, float f);

extern float func_002A7878_3(float a, float b);

extern void func_00282CC0_13(char *a, char *b, char *c);

extern void func_00282D30_13(char *a, char *b, float f);

extern void func_00300190_1(char *a, char *b);

extern void shop_trigger_current_state_effect(char *a, char *b);

extern int func_00282978_3(char *p);

extern void func_002B9180_6(char *p);

#ifndef RAC2_T_V4_F61E33AD9
#define RAC2_T_V4_F61E33AD9
typedef int V4_F61e33ad9 __attribute__((mode(TI)));
#endif

extern float func_00282C48_4(float f);

extern float vec_distance_xy(void *a, void *b);

extern float fast_vec_dist(void *a, void *b);

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls FUN_0027C540(0)
 *   - Calls FUN_0029C138()
 *   - Calls FUN_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void func_0027C540_2(long);

extern void module_l00_call_handler_4(void);

extern void func_0027C660_2(void);

unsigned long long level_l00_run_setup_return_zero_long(void);

extern void func_0027C540_9(long);

extern void module_l00_call_handler_6(void);

extern void func_0027C660_9(void);

/* Function at 0x002cd8c0: FUN_002CD8C0
 * 
 * Disassembly summary:
 * - 12 instructions, 48 bytes total
 * - Prologue: save ra, allocate 16-byte stack frame
 * - Three calls to external functions:
 *   1. FUN_0027C540(0)
 *   2. FUN_0029C450()
 *   3. FUN_0027C660()
 * - Epilogue: restore ra, return 0, deallocate stack
 * - No local variables used
 * - Return type is void-like; returns zero in v0
 * - Delay slots are_NOP/unused in this case
 */

/* External function declarations (exact addresses from task metadata) */
extern void func_0027C540_7(long);

extern void module_l00_call_handler_11(void);

extern void func_0027C660_7(void);

extern int D_L00_001A904C_3 __attribute__((sda));

extern int tab_menu_get_selected_value(int x);

extern void func_0027C540_6(long);

extern void module_l00_call_handler_16(void);

extern void func_0027C660_6(void);

void func_0027C540_3(long);

void func_0027C660_3(void);

void module_l00_call_handler_17(void);

/* 
 * Function: FUN_002D2EE0
 * 
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls FUN_0027C540(0) (with zero argument)
 * - Calls FUN_0029C7A0()
 * - Calls FUN_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

extern void func_0027C540_4(long arg0);

extern void module_l00_call_handler_18(void);

extern void func_0027C660_4(void);

/* External function declarations as per target specification */
extern void func_0027C540_5(long);

extern void func_0027C660_5(void);

extern void level_l00_call_module_handler_2(void);

/* External functions declared with exact aliases from task.externals */
extern void func_0027C540_8(long param_1);

extern void func_0027C660_8(void);

extern void level_l00_call_module_handler_3(void);

/* Target: FUN_002d5540 on MIPS (SCUS_972.68, -O2 -G0 -ffunction-sections)
 * Calls three externals: FUN_0027C540(int), FUN_0029CED8(void), FUN_0027C660(void)
 * Returns 0. Stack frame size 16 bytes. Delay slots filled.
 */
extern void func_0027C540_1(long);

extern void func_L00_0030DFE0(void);

extern void func_0027C660_1(void);

/* Frozen Batch A A03-counter-mod50-80; acknowledged claim b5e8cf533fd3cee3cb2dcdd0bf7be9549f6cc39cd932c589176487a8b170abee. */
typedef int BatchA_A03_s32;

extern BatchA_A03_s32 D_L00_001A8FE0[] __attribute__((sda));

extern BatchA_A03_s32 D_001A7BC0[] __attribute__((sda));

extern BatchA_A03_s32 D_001A7B90_1[] __attribute__((sda));

/* Guarded child-descriptor update: when the guard call returns non-zero the child is released, otherwise a packed colour byte is folded into a parent word and a four-float vector is assembled and handed to a spawn helper before three counters are advanced. */
/* Updates one small visual effect each frame: it fades and moves the effect, or removes it when its time is up. */
void part_l00_update_fading_effect_2(char *effect)
{
    char delta[16];
    char *effect_base = effect;
    char *params;
    int packed_word;
    int new_alpha;
    char *effect_pos;

    if (func_00282978_1(effect + 10) != 0) {
        func_002B9180_1(effect);
        return;
    }
    params = effect + 32;
    packed_word = *(int *)(effect_base + 4);
    new_alpha = (packed_word >> 24) + *(unsigned char *)(params + 20);
    *(int *)(effect_base + 4) = (packed_word & 0x00ffffff) | (new_alpha << 24);
    effect_pos = effect_base + 16;
    *(float *)(delta + 0) = *(float *)(effect_base + 32);
    *(float *)(delta + 4) = *(float *)(params + 4);
    *(float *)(delta + 8) = *(float *)(params + 8);
    *(int *)(delta + 12) = 0;
    func_00282CC0_1(effect_pos, effect_pos, delta);
    *(float *)(params + 8) = *(float *)(params + 8) - *(float *)(params + 12);
    *(unsigned char *)(effect_base + 8) = *(unsigned char *)(effect_base + 8) + *(unsigned char *)(params + 21);
    *(float *)(effect_base + 12) = *(float *)(effect_base + 12) + *(float *)(params + 16);
}



/* Calls a routine on pointer-plus-10 and, when it returns non-zero, calls a second routine with the pointer itself. */
/* Removes the effect once its timer check says it is finished. */
void part_remove_finished_effect(char *effect)
{
    if (func_00282978_11(effect + 10)) {
        func_002B9180_17(effect);
    }
}

/* Guarded child-descriptor update: when the guard call returns non-zero the child is released, otherwise a packed colour byte is folded into a parent word and a four-float vector is assembled and handed to a spawn helper before three counters are advanced. */
/* Updates one small visual effect each frame: it fades and moves the effect, or removes it when its time is up. */
void part_l00_update_fading_effect_3(char *effect)
{
    char delta[16];
    char *effect_base = effect;
    char *params;
    int packed_word;
    int new_alpha;
    char *effect_pos;

    if (func_00282978_1(effect + 10) != 0) {
        func_002B9180_1(effect);
        return;
    }
    params = effect + 32;
    packed_word = *(int *)(effect_base + 4);
    new_alpha = (packed_word >> 24) + *(unsigned char *)(params + 20);
    *(int *)(effect_base + 4) = (packed_word & 0x00ffffff) | (new_alpha << 24);
    effect_pos = effect_base + 16;
    *(float *)(delta + 0) = *(float *)(effect_base + 32);
    *(float *)(delta + 4) = *(float *)(params + 4);
    *(float *)(delta + 8) = *(float *)(params + 8);
    *(int *)(delta + 12) = 0;
    func_00282CC0_1(effect_pos, effect_pos, delta);
    *(float *)(params + 8) = *(float *)(params + 8) - *(float *)(params + 12);
    *(unsigned char *)(effect_base + 8) = *(unsigned char *)(effect_base + 8) + *(unsigned char *)(params + 21);
    *(float *)(effect_base + 12) = *(float *)(effect_base + 12) + *(float *)(params + 16);
}



/* func_L00_003406E8 is defined in L00_003406E8.c. */







/* divides one helper result by a second, multiplies a third by the quotient, quantises that product to a byte lane and the half quotient through two more helpers, bumps a byte counter, adds a scaled helper result to a float field, forwards two 16-byte sub-objects to three helpers, stores the merged byte lanes over a low halfword and calls a trailing helper when a probe on the parameter returns non-zero */
/* Updates a fading, shrinking effect that drifts and is removed when its time runs out. */
void part_update_shrinking_effect(char *effect)
{
    char *params = effect + 32;
    char *effect_pos = effect + 16;
    float ratio, total, start_value, jitter;
    int alpha_byte, color_byte;

    ratio = IntToFloat(*(short *)(effect + 10));
    total = IntToFloat(*(int *)(params + 24));
    ratio = ratio / total;
    start_value = IntToFloat(*(int *)(params + 16));
    alpha_byte = func_00283CF0_2(start_value * ratio);
    color_byte = func_00283D38_1(0, *(int *)(params + 20), ratio * 0.5f);
    *(char *)(effect + 8) = *(unsigned char *)(effect + 8) + 1;
    jitter = func_002A7878_3(0.004f, 0.012f);
    *(float *)(effect + 12) = *(float *)(effect + 12) + jitter * 210000.0f;
    func_00282CC0_13(effect_pos, effect_pos, params);
    func_00282D30_13(params, params, 0.99f);
    func_00300190_1(effect_pos, effect_pos);
    shop_trigger_current_state_effect(params, params);
    *(int *)(effect + 4) = color_byte | (alpha_byte << 24);
    if (func_00282978_3(effect + 10) != 0) {
        func_002B9180_6(effect);
    }
}


/* advances an index with signed delta and either wraps by count or clamps the applicable endpoint */
/* Advances a signed index, wrapping or clamping to the measured count. */
/* Moves a list index forward or back and either wraps around or stops at the ends. */
s32 path_advance_index(const s32 *count, s32 index, s32 delta, s32 wrap) {
    if (wrap != 0) {
        index = (index + delta + *count) % *count;
    } else {
        index += delta;
        if (delta < 0) {
            if (index < 0) index = 0;
        } else if (index > *count - 1) {
            index = *count - 1;
        }
    }
    return index;
}

/* func_L00_00341820 is defined in L00_0033F678-spline.c. */

/* copies two 16-byte records into locals; when the float threshold is positive it passes the difference of their third components through a float leaf returning the absolute value and, if that is below the threshold, calls one leaf with both records, otherwise the shared alternative leaf */
/* Measures how far apart two points are, using a quicker check when they are close in height. */
float vec_measure_distance_with_height(void *vec_a, void *vec_b, float scale)
{
    V4_F61e33ad9 copy_a;
    V4_F61e33ad9 copy_b;
    float *floats_a;
    float *floats_b;
    float z_a;
    float z_b;

    copy_a = *(V4_F61e33ad9 *)vec_a;
    copy_b = *(V4_F61e33ad9 *)vec_b;
    floats_a = (float *)&copy_a;
    floats_b = (float *)&copy_b;
    if (0.0f < scale) {
        z_a = floats_a[2];
        z_b = floats_b[2];
        if (func_00282C48_4(z_a - z_b) < scale) {
            return vec_distance_xy(floats_a, floats_b);
        }
    }
    return fast_vec_dist(floats_a, floats_b);
}



/* func_L00_00341D08 is defined in L00_0033F678-projection.c. */

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { int count; int reserved[3]; Vector points[0]; } Path;
extern int Spline_AdvanceByDistance(const Path *, Vector *, int *, float *, float, int);
extern float ProjectPointOntoSegment(Vector *, const Vector *, const Vector *, const Vector *, float);
extern void vec_clear_128(Quadword *);

/* Find the nearby path segment and the projected position on that segment.
 * Counterpart of rac1-decomp's find_nearest_path_point (moby_ground_collision.c). */
/* Finds the closest spot along a path to a given point. */
int find_nearest_path_point(const Path *path, const Vector *point, Vector *out,
                     int *index, float *offset, int wrap,
                     float range, float step, float height) {
    Vector current, a, b, candidate;
    int scanIndex = 0;
    float scanOffset = 0.0f;
    int left, right;
    int nearestIndex;
    float nearestOffset;
    float nearestDistance, distance, searchRange;
    int finished, previous, next;
    qcopy(&current, &((const Vector *)path)[1]);
    a.q = point->q;
    nearestIndex = 0;
    nearestOffset = 0.0f;
    nearestDistance = vec_measure_distance_with_height(&current, &a, height);
    if (path->count == 0) {
        vec_clear_128(&out->q);
        return 0;
    }
    searchRange = step + range;
    do {
        finished = Spline_AdvanceByDistance(path, &current, &scanIndex, &scanOffset, step, wrap);
        a.q = point->q;
        distance = vec_measure_distance_with_height(&current, &a, height);
        if (distance < nearestDistance) {
            nearestIndex = scanIndex;
            nearestDistance = distance;
            nearestOffset = scanOffset;
        }
    } while (!finished);
    if (searchRange < nearestDistance) return 0;
    left = nearestIndex;
    scanOffset = nearestOffset;
    Spline_AdvanceByDistance(path, &current, &left, &scanOffset, -step, wrap);
    right = nearestIndex;
    scanOffset = nearestOffset;
    Spline_AdvanceByDistance(path, &current, &right, &scanOffset, step, wrap);
    right = path_advance_index(&path->count, right, 1, wrap);
    scanIndex = left;
    nearestDistance = 1000000000.0f;
    for (;;) {
        a.q = ((const Vector *)path)[scanIndex + 1].q;
        b.q = point->q;
        distance = vec_measure_distance_with_height(&a, &b, height);
        if (distance < nearestDistance) {
            nearestIndex = scanIndex;
            nearestDistance = distance;
        }
        if (scanIndex == right) break;
        scanIndex = (scanIndex + 1) % path->count;
    }
    nearestDistance = 1000000000.0f;
    /* As in RAC1's find_nearest_path_point, the projection distance is kept in an
     * arm-local and becomes the best distance only after the offset call. */
    if (nearestIndex > 0 || wrap) {
        float projected;
        previous = path->count - 1;
        previous = (nearestIndex + previous) % path->count;
        projected = ProjectPointOntoSegment(out, point, &((const Vector *)path)[previous + 1], &((const Vector *)path)[nearestIndex + 1], height);
        *index = previous;
        a.q = ((const Vector *)path)[previous + 1].q;
        b.q = out->q;
        *offset = vec_measure_distance_with_height(&a, &b, 0.0f);
        nearestDistance = projected;
    }
    if (nearestIndex < path->count - 1 || wrap) {
        next = (nearestIndex + 1) % path->count;
        distance = ProjectPointOntoSegment(&a, point, &((const Vector *)path)[nearestIndex + 1], &((const Vector *)path)[next + 1], height);
        if (distance < nearestDistance) {
            qcopy(out, &a);
            *index = nearestIndex;
            b.q = ((const Vector *)path)[nearestIndex + 1].q;
            candidate.q = out->q;
            *offset = vec_measure_distance_with_height(&b, &candidate, 0.0f);
        }
    }
    return 1;
}

/* func_L00_003425F8 is defined in L00_0033F678-pushout.c. */


#define NOT_SDA __attribute__((section(".data")))

extern void *r1_D_0012F86C NOT_SDA;

/* rac1-decomp src/core/001138A8.c: func_001138A8 */
/* Returns a stored global pointer. */
int level_get_stored_global_pointer(void) {
    return (int)r1_D_0012F86C;
}

/* Does nothing and returns zero. */
unsigned int return_l00_zero(void)
{
    return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_2(void) {
    return 0;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero(void)
{
  func_0027C540_2(0);
  module_l00_call_handler_4();
  func_0027C660_2();
  return 0;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
unsigned long long level_l00_run_setup_return_zero_long(void)
{
  func_0027C540_9(0);
  module_l00_call_handler_6();
  func_0027C660_9();
  return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_3(void) {
    return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_4(void) {
    return 0;
}

/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_2(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_8();
    DoGifPaging();
    return 0;
}

extern int grid_menu_get_selected_text_id(int x);

/* When the global is set, derives a pointer from it plus a fixed offset, runs it through a callee and stores the result into a field of the argument. */
/* Looks up a data entry from a global table and stores it in the object. */
int level_l00_store_table_entry_in_object(int *effect)
{
    if (D_L00_001A904C_3 != 0)
        effect[13] = grid_menu_get_selected_text_id(D_L00_001A904C_3 + 0x39F38);
    return 0;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
long long level_l00_run_setup_return_zero_long_2(void)
{
    func_0027C540_7(0LL);
    module_l00_call_handler_11();
    func_0027C660_7();
    return 0LL;
}

/* Does nothing and returns zero. */
int return_l00_zero_5(void) {
    return 0;
}

/* When a global flag is set, derives a pointer from that global plus a fixed offset, runs it through one callee and stores the callee result into a field of the argument. */
/* Looks up a data entry from a global table and stores it in the object. */
int level_l00_store_table_entry_in_object_2(int *obj)
{
    if (D_L00_001A904C_3 != 0)
        obj[13] = tab_menu_get_selected_value(D_L00_001A904C_3 + 0x3BE08);
    return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_6(void) {
    return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_7(void) {
    return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_8(void) {
    return 0;
}

/* Does nothing and returns zero. */
int return_l00_zero_9(void) {
    return 0;
}

extern int D_00138344;

extern void module_l00_call_handler_with_arg_15(int a);

extern void level_l00_call_module_handler_with_arg_11(int a);

extern void SetupGifPaging(int a);

extern void DoGifPaging(void);

extern void level_l00_call_module_handler_8(void);

extern void module_l00_call_handler_15(void);

extern void module_l00_call_handler_19(void);


extern void module_l00_call_handler_with_arg_9(int a);

/* Runs an update step using the saved input state and returns zero. */
int pad_run_input_update_return_zero(void)
{
    module_l00_call_handler_with_arg_15(D_00138344);
    return 0;
}

/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_3(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_15();
    DoGifPaging();
    return 0;
}

/* Callback state read by the guarded update below: a source pointer the value is taken from, the
   value itself and the fallback word that decides the -1 result. */
typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackStateL001FEC40;

extern CallbackStateL001FEC40 D_L00_001FEC40;

extern void module_l00_call_handler_with_arg_16(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
/* Checks the saved input state and runs an update step for it. */
int pad_l00_update_input_callback(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        module_l00_call_handler_with_arg_16(flags);
    return result;
}

/* Guarded callback updates: with the pending-input bit set, refresh the value from its source
   and report it (or the fallback's -1); with a busy bit set report 1; otherwise run the setup
   call and service the pending request. Three copies differ only in their callees. */

extern int g_pad_state[];
extern int module_l00_call_handler_with_arg_12(int);
extern int level_l00_call_module_handler_with_arg_2(int);
extern int level_l00_call_module_handler_with_arg_5(int);
extern int tab_menu_get_selected_entry(int);
extern int list_page_get_selected_record(int);
extern int list_menu_get_selected_record(int);
extern void menu_start_action(int);

/* Checks the saved input state, runs an update step and may send out a pending request. */
int pad_update_input_callback_with_request(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags = state[0x1C4 / 4];

    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);

        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else {
        module_l00_call_handler_with_arg_12(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_L00_001A904C_3) {
            char *entry = (char *)tab_menu_get_selected_entry(D_L00_001A904C_3 + 0x3BE08);
            struct { short unused; unsigned short id; int value; } request;

            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_4(void)
{
    func_0027C540_6(0);
    module_l00_call_handler_16();
    func_0027C660_6();
    return 0;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
unsigned long long level_l00_run_setup_return_zero_long_3(void)
{
    func_0027C540_3(0);
    module_l00_call_handler_17();
    func_0027C660_3();
    return 0;
}

extern void module_l00_call_handler_with_arg_18(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
/* Checks the saved input state and runs an update step for it. */
int pad_l00_update_input_callback_2(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        module_l00_call_handler_with_arg_18(flags);
    return result;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
unsigned long long level_l00_run_setup_return_zero_long_4(void)
{
    func_0027C540_4(0);
    module_l00_call_handler_18();
    func_0027C660_4();
    return 0;
}

extern void module_l00_call_handler_with_arg_19(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
/* Checks the saved input state and runs an update step for it. */
int pad_l00_update_input_callback_3(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        module_l00_call_handler_with_arg_19(flags);
    return result;
}
/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_5(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_19();
    DoGifPaging();
    return 0;
}

extern void level_l00_call_module_handler_with_arg_4(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
/* Checks the saved input state and runs an update step for it. */
int pad_l00_update_input_callback_4(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        level_l00_call_module_handler_with_arg_4(flags);
    return result;
}
extern void level_l00_call_module_handler_5(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_6(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_5();
    DoGifPaging();
    return 0;
}

extern void level_l00_call_module_handler_with_arg_3(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
/* Checks the saved input state and runs an update step for it. */
int pad_l00_update_input_callback_5(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        level_l00_call_module_handler_with_arg_3(flags);
    return result;
}
extern void level_l00_call_module_handler_4(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_7(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_4();
    DoGifPaging();
    return 0;
}

extern void level_l00_call_module_handler(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int level_l00_run_setup_return_zero_8(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler();
    DoGifPaging();
    return 0;
}

extern void level_l00_call_module_handler_with_arg(int);

/* Guarded callback update: with the pending-input bit set, refreshes the value from its source and reports it (or the fallback's -1), otherwise reports a configured input or runs the setup call. */
/* Checks the saved input state and runs an update step for it. */
int pad_l00_update_input_callback_6(void)
{
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);
        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        level_l00_call_module_handler_with_arg(flags);
    return result;
}
/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Implementation matching decompiled output */
/* Runs a short setup routine and returns zero. */
long setup_l00_run_three_return_zero(void)
{
  func_0027C540_5(0);
  level_l00_call_module_handler_2();
  func_0027C660_5();
  return 0;
}

/* The same guarded callback update with its own setup call and pending-request reader. */
/* Checks the saved input state, runs an update step and may send out a pending request. */
int input_l00_callback_send_request(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags = state[0x1C4 / 4];

    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);

        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else {
        level_l00_call_module_handler_with_arg_2(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_L00_001A904C_3) {
            char *entry = (char *)list_page_get_selected_record(D_L00_001A904C_3 + 0x3EDB8);
            struct { short unused; unsigned short id; int value; } request;

            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Candidate function: FUN_002d3390 */
/* Runs a short setup routine and returns zero. */
unsigned long long setup_l00_run_three_return_zero_2(void)
{
    func_0027C540_8(0);
    level_l00_call_module_handler_3();
    func_0027C660_8();
    return 0;
}

extern void module_l00_call_handler_14(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int setup_l00_run_three_return_zero_3(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_14();
    DoGifPaging();
    return 0;
}

/* When a global flag is set, derives a pointer from that global plus a fixed offset, runs it through one callee and stores the callee result into a field of the argument. */
/* Looks up a data entry from a global table and stores it in the object. */
int table_store_entry_in_object(int *obj)
{
    if (D_L00_001A904C_3 != 0)
        obj[13] = tab_menu_get_selected_value(D_L00_001A904C_3 + 0x3BE08);
    return 0;
}

/* Runs an update step using the saved input state and returns zero. */
int input_l00_update_return_zero(void)
{
    level_l00_call_module_handler_with_arg_11(D_00138344);
    return 0;
}

/* Runs an update step using the saved input state and returns zero. */
int input_l00_update_return_zero_2(void)
{
    level_l00_call_module_handler_with_arg_11(D_00138344);
    return 0;
}

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
long long setup_l00_run_three_return_zero_4(void)
{
    func_0027C540_1(0);
    func_L00_0030DFE0();
    func_0027C660_1();
    return 0;
}

/* Does nothing and returns zero. */
int stub_l00_return_zero(void) {
    return 0;
}

extern void level_l00_call_module_handler_7(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int setup_l00_run_three_return_zero_5(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_7();
    DoGifPaging();
    return 0;
}

/* The same guarded callback update with its own setup call and pending-request reader. */
/* Checks the saved input state, runs an update step and may send out a pending request. */
int input_l00_callback_send_request_2(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags = state[0x1C4 / 4];

    if (flags & 0x10) {
        int value = *(int *)(D_L00_001FEC40.source + 0xE0);

        if (value != 0)
            D_L00_001FEC40.value = value;
        else if (D_L00_001FEC40.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else {
        level_l00_call_module_handler_with_arg_5(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_L00_001A904C_3) {
            char *entry = (char *)list_menu_get_selected_record(D_L00_001A904C_3 + 0x3E1D8);
            struct { short unused; unsigned short id; int value; } request;

            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}

extern void level_l00_call_module_handler_6(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int setup_l00_run_three_return_zero_6(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_6();
    DoGifPaging();
    return 0;
}

/* Runs an update step using the saved input state and returns zero. */
int input_l00_update_return_zero_3(void)
{
    module_l00_call_handler_with_arg_9(D_00138344);
    return 0;
}

extern void module_l00_call_handler_9(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int setup_l00_run_three_return_zero_7(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_9();
    DoGifPaging();
    return 0;
}

extern int D_L00_001C95D4;

/* Resets a global value to minus one. */
int state_l00_reset_to_minus_one(void) {
    D_L00_001C95D4 = -1;
    return 0;
}

/* Does nothing and returns zero. */
int stub_l00_return_zero_2(void) {
    return 0;
}

extern void module_l00_call_handler_10(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
/* Runs a short setup routine and returns zero. */
int setup_l00_run_three_return_zero_8(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_10();
    DoGifPaging();
    return 0;
}


extern int D_L00_001C95D4;

/* Resets a global value to minus one. */
int state_l00_reset_to_minus_one_2(void) {
    D_L00_001C95D4 = -1;
    return 0;
}

/* Does nothing and returns zero. */
unsigned int stub_l00_return_zero_3(void)
{
    return 0;
}


/* A03-counter-mod50-80 freshly exact-verified under family reservation */
/* Counts calls and gives the counter a small bump every 50th call. */
void counter_count_calls_bump(void)
{
    if (D_L00_001A8FE0[0] == 0) {
        BatchA_A03_s32 counter = D_001A7BC0[0] + 1;
        D_001A7BC0[0] = counter;
        if (counter % 50 == 0) {
            if (D_001A7B90_1[0]) {
                D_001A7BC0[0] = counter + 10;
            }
        }
    }
}

/* Return the constant signed integer one. */
/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
/* Always returns 1. */
int stub_l00_return_one(void) {
    return 1;
}



extern void mem_clear(unsigned int *dst, unsigned int val, int size);

extern char D_L00_0021D140[];
extern char D_L00_0021DDB0[];
extern char D_L00_001B2370[] __attribute__((sda));

/* Zeroes the three measured work areas, the two 0xC70-byte ones and a 0x40-byte one. */
/* Clears three work memory areas to zero. */
void mem_clear_work_areas(void)
{
    mem_clear((unsigned int *)D_L00_0021D140, 0, 0xC70);
    mem_clear((unsigned int *)D_L00_0021DDB0, 0, 0xC70);
    mem_clear((unsigned int *)D_L00_001B2370, 0, 0x40);
}


extern char *D_L00_001B1E9C __attribute__((sda));
extern char *D_L00_001B1EA0 __attribute__((sda));

/* Walks the 0x100-byte records between the two list bounds and returns the first whose 16-bit key at 0xB2 matches, or null. */
/* Searches the record list for the entry with a matching id and returns it, or null. */
char *record_find_by_id(int a0, int key)
{
    char *cur;
    for (cur = D_L00_001B1E9C; cur != D_L00_001B1EA0; cur += 0x100) {
        if (*(short *)(cur + 0xB2) == key)
            return cur;
    }
    return 0;
}
