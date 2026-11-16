#include "names.h"


#ifndef RAC2_T_U8_FE9770B1E
#define RAC2_T_U8_FE9770B1E
typedef unsigned char u8_Fe9770b1e;
#endif

#ifndef RAC2_T_S32_FE9770B1E
#define RAC2_T_S32_FE9770B1E
typedef int s32_Fe9770b1e;
#endif

#ifndef RAC2_T_F32_FE9770B1E
#define RAC2_T_F32_FE9770B1E
typedef float f32_Fe9770b1e;
#endif

/* Resident shared table reached through $gp (small-data symbol). */
extern f32_Fe9770b1e g_prompt_menu_data[2] __attribute__((sda));

extern void *func_00336E40_1(void *);

extern void *func_00336DA8_1(s32_Fe9770b1e, void *);

extern void func_0033ABD8_1(u8_Fe9770b1e *, void *, f32_Fe9770b1e *);

extern char *func_00288FB8_1(s32_Fe9770b1e);

extern void func_0033B050_1(u8_Fe9770b1e *, void *, void *, void *);

extern void func_0033B030_1(u8_Fe9770b1e *, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e, f32_Fe9770b1e);

extern void func_0033B0A8_1(u8_Fe9770b1e *, f32_Fe9770b1e);

extern int menu_handle_page_input_a(u8_Fe9770b1e *, s32_Fe9770b1e);

/* Sets up a menu with a button prompt bar, its labels and position, then runs its first update. */
void prompt_menu_init(u8_Fe9770b1e *self, void *arg) {
    u8_Fe9770b1e *prompt;
    void *textA, *textB, *textC;
    *(void **)self = arg;
    if (arg != 0) {
        void *owner = func_00336E40_1(arg);
        void *allocation = func_00336DA8_1(16, owner);
        *(void **)(self + 684) = allocation;
        ((s32_Fe9770b1e *)allocation)[1] = 0;
        ((s32_Fe9770b1e *)allocation)[2] = 0;
        ((s32_Fe9770b1e *)allocation)[3] = 0;
        ((s32_Fe9770b1e *)allocation)[0] = 0;
    }
    prompt = self + 8;
    ((f32_Fe9770b1e *)*(void **)(self + 684))[0] = 255.0f;
    ((f32_Fe9770b1e *)*(void **)(self + 684))[1] = 195.0f;
    func_0033ABD8_1(prompt, arg, g_prompt_menu_data);
    textA = func_00288FB8_1(11667);
    textB = func_00288FB8_1(11598);
    textC = func_00288FB8_1(11599);
    func_0033B050_1(prompt, textA, textB, textC);
    func_0033B030_1(prompt, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    func_0033B0A8_1(prompt, 0.2f);
    *(s32_Fe9770b1e *)(self + 680) = 0;
    menu_handle_page_input_a(self, 0);
}
