#include "include_asm.h"
#include "names.h"
extern unsigned char D_001A7B96 __attribute__((sda));

extern void prompt_bar_set_texts_enabled(unsigned char *owner, int value);

extern void prompt_bar_destroy(char *p);

extern void func_0033AE28_2(char *p);

extern void func_L00_00430948_3(char *p, float a, float b);

extern void func_002E5E58_3(int a, int b, int c);

extern volatile unsigned char D_001A7B95 __attribute__((sda));

extern volatile unsigned char D_001A7B94 __attribute__((sda));

extern void prompt_bar_update (char *object);

extern void func_L00_00430948_1 (char *object, float x, float y);

extern int func_002E5E58_1 (int a, int b, int c);

extern void func_0033AE28_1(char *p);

extern void func_L00_00430948_2(char *p, float a, float b);

extern void func_002E5E58_2(int a, int b, int c);

extern volatile unsigned char D_001A7BB2_1 __attribute__((sda));

extern volatile unsigned char D_001A7BB3 __attribute__((sda));

/* Does nothing. */
void menu_hook_noop_a(void)
{
}

/* Does nothing. */
void menu_hook_noop_b(void)
{
}

/* Does nothing. */
void menu_hook_noop_c(void)
{
}


/* Forward owner+8 and the supplied signed word to the measured two-argument setter. */
void menu_forward_value_setter(unsigned char *owner, int value)
{
    prompt_bar_set_texts_enabled(owner + 8, value);
}






/* Store the two scalar floating arguments through the supplied pointer cell; original game role is unknown. */
void mem_store_two_floats_through_cell(float first, float second, float **cell)
{
    (*cell)[0] = first;
    (*cell)[1] = second;
}



/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_a(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_b(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_c(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_d(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* makes two float-binding calls, then toggles one of two global flag bytes selected by an object field and returns bit 6 of the flag word */
int menu_handle_page_input_a(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    func_0033AE28_2(p);
    q = *(float **)(a0 + 684);
    func_L00_00430948_3(p, q[0], q[1]);
    if (a1 & 0x1000) {
        func_002E5E58_3(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        func_002E5E58_3(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        func_002E5E58_3(4, 0, 0);
        switch (*(int *)(a0 + 680)) {
        case 0:
            D_001A7B95 = D_001A7B95 == 0;
            break;
        case 1:
            D_001A7B94 = D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}


/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_e(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* resets a sub-object, applies a two-float transform, and when bit 6 of flags is set and an int field is zero calls a mode setter and toggles a global byte */
int menu_handle_page_input_b (char *object, int flags)
{
  unsigned char *g = &D_001A7B96;
  float *vec;
  int discarded;

  prompt_bar_update (object + 8);
  vec = *(float **) (object + 684);
  func_L00_00430948_1 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 680) == 0)
    {
      discarded = func_002E5E58_1 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_f(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


/* makes two float-binding calls, then toggles one of two global flag bytes selected by an object field and returns bit 6 of the flag word */
int menu_handle_page_input_c(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    func_0033AE28_1(p);
    q = *(float **)(a0 + 684);
    func_L00_00430948_2(p, q[0], q[1]);
    if (a1 & 0x1000) {
        func_002E5E58_2(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        func_002E5E58_2(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        func_002E5E58_2(4, 0, 0);
        switch (*(int *)(a0 + 680)) {
        case 0:
            D_001A7BB2_1 = D_001A7BB2_1 == 0;
            break;
        case 1:
            D_001A7BB3 = D_001A7BB3 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_g(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

