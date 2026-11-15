#include "include_asm.h"
#include "names.h"

extern void prompt_bar_update(char *p);

extern void func_L00_00430948_1(char *p, float x, float y);

extern int func_002E5E58_1(int a, int b, int c);

extern volatile unsigned char D_001A7BB2 __attribute__((sda));

extern int prompt_bar_destroy(char *p);

void* menu_init_two_sub_objects(void* param_1);

extern int func_0033AB50_1(int);

extern unsigned long long func_00347EA0_1(unsigned long long);

extern int menu_list_get_selected_id(unsigned char *owner);

extern void menu_list_clear_state(unsigned char *owner);

extern char *cam_init_object_table_a(char *p);

extern char *cam_init_object_table_d(char *p);

extern char *cam_init_object_table_c(char *p);

/* Calls two helpers on object-plus-8 using the pointer at plus-684; when flag bit 6 is set and the plus-680 word is zero, calls a third helper and normalizes the measured byte cell to 0 or 1; returns flag bit 6. */
int menu_update_two_part_flags_a(char *object, int flags)
{
    float *vec;

    prompt_bar_update(object + 8);
    vec = *(float **)(object + 684);
    func_L00_00430948_1(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = func_002E5E58_1(4, 0, 0);
        (void)discarded;
        D_001A7BB2 = (D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_sub_object_a(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* Calls two helpers on object-plus-8 using the pointer at plus-684; when flag bit 6 is set and the plus-680 word is zero, calls a third helper and normalizes the measured byte cell to 0 or 1; returns flag bit 6. */
int menu_update_two_part_flags_b(char *object, int flags)
{
    float *vec;

    prompt_bar_update(object + 8);
    vec = *(float **)(object + 684);
    func_L00_00430948_1(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = func_002E5E58_1(4, 0, 0);
        (void)discarded;
        D_001A7BB2 = (D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_sub_object_b(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* Calls two helpers on object-plus-8 using the pointer at plus-684; when flag bit 6 is set and the plus-680 word is zero, calls a third helper and normalizes the measured byte cell to 0 or 1; returns flag bit 6. */
int menu_update_two_part_flags_c(char *object, int flags)
{
    float *vec;

    prompt_bar_update(object + 8);
    vec = *(float **)(object + 684);
    func_L00_00430948_1(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = func_002E5E58_1(4, 0, 0);
        (void)discarded;
        D_001A7BB2 = (D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Initialize the owner subviews at 8 and 0x 2B 0, then return the supplied owner pointer. */
void* menu_init_two_sub_objects(void* param_1)
{
  func_0033AB50_1((int)param_1 + 8);
  func_00347EA0_1((int)param_1 + 0x2b0);
  return param_1;
}


extern void func_430480(void *);
extern void func_42C290(void *);

/* Visits both sub-objects, then hands back the same pointer. */
char *menu_visit_two_sub_objects(char *a0) {
    func_430480(a0 + 0x8);
    func_42C290(a0 + 0x2B0);
    return a0;
}


extern void prompt_bar_draw(char *p);

/* Asks the sub-object 8 bytes in for a value and passes it back. */
void menu_get_sub_object_value(char *p)
{
    prompt_bar_draw(p + 8);
}



/* Does nothing. */
void noop_a(void)
{
}



extern int menu_get_selected_index(char *p);

/* Asks the sub-object 16 bytes in for a value and passes it back. */
int sub_object_get_value_near(char *p)
{
    return menu_get_selected_index(p + 16);
}

/* Does nothing. */
void stub_l00_noop(void)
{
}

/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long stub_l00_return_arg(unsigned long param_1)
{
  return param_1;
}



/* Store the two scalar floating arguments through the supplied pointer cell; original game role is unknown. */
void stub_store_two_floats(float first, float second, float **cell)
{
    (*cell)[0] = first;
    (*cell)[1] = second;
}

extern int menu_list_build_ids(char *p);

/* Asks a sub-object for a value and passes it back. */
int sub_object_get_value_far(char *p)
{
    return menu_list_build_ids(p + 664);
}


/* Return the measured signed-word getter result for the owner subview at 0x 298. */
int sub_object_get_signed_word(unsigned char *owner)
{
    return menu_list_get_selected_id(owner + 0x298);
}

/* Invoke the measured cleanup helper on the owner subview at 0x 298. */
void sub_object_cleanup(unsigned char *owner)
{
    menu_list_clear_state(owner + 0x298);
}


/* Calls a fixed chain of sub-object initialisers at 76-byte steps and returns the base pointer. */
char *sub_object_init_chain(char *p)
{
    cam_init_object_table_a(p);
    cam_init_object_table_a(p + 76);
    cam_init_object_table_a(p + 152);
    cam_init_object_table_a(p + 228);
    cam_init_object_table_a(p + 304);
    cam_init_object_table_a(p + 380);
    cam_init_object_table_d(p + 456);
    cam_init_object_table_d(p + 528);
    cam_init_object_table_c(p + 600);
    cam_init_object_table_d(p + 664);
    cam_init_object_table_d(p + 736);
    cam_init_object_table_d(p + 808);
    cam_init_object_table_d(p + 880);
    cam_init_object_table_d(p + 952);
    return p;
}

/* Calls a fixed chain of sub-object initialisers at 76-byte steps and returns the base pointer. */
char *sub_object_init_chain_copy(char *p)
{
    cam_init_object_table_a(p);
    cam_init_object_table_a(p + 76);
    cam_init_object_table_a(p + 152);
    cam_init_object_table_a(p + 228);
    cam_init_object_table_a(p + 304);
    cam_init_object_table_a(p + 380);
    cam_init_object_table_d(p + 456);
    cam_init_object_table_d(p + 528);
    cam_init_object_table_c(p + 600);
    cam_init_object_table_d(p + 664);
    cam_init_object_table_d(p + 736);
    cam_init_object_table_d(p + 808);
    cam_init_object_table_d(p + 880);
    cam_init_object_table_d(p + 952);
    return p;
}


/* Store the supplied unsigned 32-bit word at owner byte offset 0xB 8. */
void owner_set_word(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0xb8) = param_2;
  return;
}



/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long stub_l00_return_arg_2(unsigned long param_1)
{
  return param_1;
}






/* Stores a value in one of the object's fields. */
void object_set_field_first(char *object, int value) {
    *(int *)(object + 0x157C) = value;
}

/* Stores a value in the next field after the one set by the previous function. */
void object_set_field_next(char *object, int value) {
    *(int *)(object + 0x1580) = value;
}


/* Does nothing. */
void stub_l00_noop_2(void)
{
}

extern void text_panel_update_mode(char *p);

/* Asks a sub-object for a value and passes it back. */
void sub_object_get_value_first(char *p)
{
    text_panel_update_mode(p + 0x1D6C);
}

extern void text_panel_draw_scaled(char *p);

/* Asks the same sub-object for a different value and passes it back. */
void sub_object_get_value_second(char *p)
{
    text_panel_draw_scaled(p + 0x1D6C);
}

/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long stub_l00_return_arg_3(unsigned long param_1)
{
  return param_1;
}

/* The fixed resident address func_L00_004450C0 forwards. */
extern char D_L00_001AEB60[];

extern void func_2A48F0(void *a0, void *a1);

/* Passes a fixed resident address, and the argument, on to the callee. */
void load_forward_resident_address(void *arg)
{
    func_2A48F0(D_L00_001AEB60, arg);
}


/* Does nothing. */
void stub_l00_noop_3(void)
{
}

/* Return the constant signed integer one. */
/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int stub_l00_return_one_2(void) {
    return 1;
}


extern void mpeg_vibuf_get_free_regions(char *p);

/* Asks a sub-object for a value and passes it back. */
void sub_object_get_value_a(char *p)
{
    mpeg_vibuf_get_free_regions(p + 0x48);
}

extern void mpeg_vibuf_add_pending_bytes(char *p);

/* Asks the same sub-object for another value and passes it back. */
void sub_object_get_value_b(char *p)
{
    mpeg_vibuf_add_pending_bytes(p + 0x48);
}

extern int mpeg_vibuf_get_queued_bytes(char *p);

/* Asks the same sub-object for yet another value and passes it back. */
int sub_object_get_value_c(char *p)
{
    return mpeg_vibuf_get_queued_bytes(p + 0x48);
}


/* Does nothing. */
void stub_l00_noop_4(void)
{
}
