#include "include_asm.h"
#include "names.h"
extern double g_fade_in_spark_param_c __attribute__((sda));
extern double g_fade_in_spark_param_b __attribute__((sda));
extern double g_fade_in_spark_param_a __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_31A718(unsigned char *);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_3F8C68(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

/* Updates a simple object like fade_in_update, and also throws sparks while it is active (PAL). */
void fade_in_spark_update_pal(unsigned char *obj) {
    unsigned char *vars = *(unsigned char **)(obj + 0x68);

    switch (obj[0x20]) {
    case 0:
        func_3248E0(obj, 1, -1);
        break;
    case 1:
        if (func_326C70(obj, 0x04010000, 0) != 0 && *(int *)vars == 0)
            func_3248E0(obj, 2, -1);
        obj[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(obj, &g_fade_in_spark_param_a, &g_fade_in_spark_param_b, &g_fade_in_spark_param_c, 0xFFFF, 0, -1, 0,
                    0xFFFF, 0xFF, 0);
        func_3F8C68(obj + 0x10, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.3f, 20.0f, 1, 1, 0, 0);
        func_31A718(obj);
        break;
    }
}
