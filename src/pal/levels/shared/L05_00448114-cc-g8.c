#include "names.h"
/* func_PAL_L05_00448114, the PAL copy of func_L05_00441F30: the same C, where rename func_L05_00442A58 becomes func_PAL_L05_00448CA8; rename func_L05_004432E0 becomes func_PAL_L05_004495C8; rename func_L05_00443740 becomes func_PAL_L05_00449A28; rename func_L00_002B30E8 becomes func_PAL_L00_002B3000; rename func_L05_00442560 becomes func_PAL_L05_00448790; scale D_L05_001B1ADC - 20. */
#include "common.h"

extern unsigned char g_hero_state[];
extern char *g_hero_moby_default NOT_SDA;
extern int D_L05_001B20CC;
extern float D_L05_001B1A4C __attribute__((sda));
extern float D_L05_001B1A50 __attribute__((sda));
extern float D_L05_001B1A54 __attribute__((sda));
extern float D_L05_001B1A58 __attribute__((sda));
extern float D_L05_001B1A5C __attribute__((sda));
extern float D_L05_001B1A64 __attribute__((sda));
extern float D_L05_001B1AC0 __attribute__((sda));
extern float D_L05_001B1F60, D_L05_001B1F64;
/* These views address the same fade words through $gp. */
extern float D_L05_001B1F60_sda SDATA(D_L05_001B1F60);
extern float D_L05_001B1F64_sda SDATA(D_L05_001B1F64);
extern int D_L05_001B1AF8 __attribute__((sda));
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern int D_L05_001B1ADC __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
/* Incomplete sda arrays keep absolute addresses together without claiming
 * the complete extent of the saved transforms. */
extern char D_L05_001B3620[] __attribute__((sda));
extern char D_L05_001B3610[] __attribute__((sda));
extern char D_L05_001B3600[] __attribute__((sda));
extern char D_L05_001B35D0[] __attribute__((sda));
extern char D_L05_001B35E0[] __attribute__((sda));
extern char D_L05_001B35F0[] __attribute__((sda));
extern char D_L05_002B8770[];

extern void hero_set_objects_flag_bit(void);
extern void func_PAL_L05_00448CA8(void *, void *, void *);
extern void ship_apply_steering_rotation(void *, void *, void *);
extern void func_PAL_L05_004495C8(void *);
extern void func_PAL_L05_00449A28(void *);
extern void euler_rotation_basis(void *, void *);
extern void func_PAL_L00_002B3000(void);
extern void ship_update_record_transform(void *, float);
extern void slot_copy_records_to_free(void *);
extern void func_PAL_L05_00448790(void *);
extern float hero_get_clamped_stat(void);
extern int hero_get_state_value_c(void);
extern int math_fast_float_d(void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))

/* Dispatches the flight controller and its timed transform transitions. */
void func_PAL_L05_00448114(char *obj)
{
    int first, second;
    char *input = P(obj, 0x70) + 0x50;
    float a = D_L05_001B1A4C, b = D_L05_001B1A50, c = D_L05_001B1A54;
    float d = D_L05_001B1A58, e = D_L05_001B1A5C, f = D_L05_001B1A64;

    F(input, 0) = a;
    F(input, 4) = b;
    F(input, 8) = c;
    F(input, 12) = d;
    F(input, 16) = e;
    F(input, 20) = f;
    D_L05_001B20CC = 2;
    if (!g_hero_state[0x22B5]) {
        I(P(g_hero_state, 0x2290), 0x98) = 0;
        hero_set_objects_flag_bit();
        g_hero_state[0x22B5] = 1;
    }
    if (!D_L05_001B1AF8) {
        U(g_hero_moby_default, 0x34) |= 0x41;
        U(g_hero_moby_default, 0x34) &= 0xEFFF;
        I(g_hero_moby_default, 0x98) = 0;
    }
    D_L05_001B1AC0 = hero_get_clamped_stat();
    if (hero_get_state_value_c()) return;

    switch (g_ship_state) {
    case 0:
        func_PAL_L05_00448CA8(obj, &first, &second);
        ship_apply_steering_rotation(obj, &first, &second);
        func_PAL_L05_004495C8(obj);
        func_PAL_L05_00449A28(obj);
        break;
    case 1:
        func_PAL_L05_00448CA8(obj, &first, &second);
        ship_apply_steering_rotation(obj, &first, &second);
        func_PAL_L05_004495C8(obj);
        func_PAL_L05_00449A28(obj);
        D_L05_001B1F60_sda = D_L05_001B1F60 + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            D_L05_001B1F60 = 1.0f;
            g_ship_state = 4;
            qcopy(obj + 0x30, D_L05_001B3620);
            euler_rotation_basis(obj, D_L05_001B3610);
        }
        break;
    case 4:
        D_L05_001B1F60_sda = D_L05_001B1F60 - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60 = 0.0f;
            g_ship_state = 5;
        }
        break;
    case 5:
        if (math_fast_float_d(&g_ship_transition_timer)) g_ship_state = 3;
        break;
    case 3:
        D_L05_001B1F60_sda = D_L05_001B1F60 + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            D_L05_001B1F60 = 1.0f;
            g_ship_state = 2;
            qcopy(obj + 0x30, D_L05_001B3600);
            qcopy(obj, D_L05_001B35D0);
            qcopy(obj + 0x10, D_L05_001B35E0);
            qcopy(obj + 0x20, D_L05_001B35F0);
        }
        break;
    case 2:
        func_PAL_L05_00448CA8(obj, &first, &second);
        ship_apply_steering_rotation(obj, &first, &second);
        func_PAL_L05_004495C8(obj);
        func_PAL_L05_00449A28(obj);
        D_L05_001B1F60_sda = D_L05_001B1F60 - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60_sda = 0.0f;
            g_ship_state = 0;
        }
        break;
    case 6:
        qcopy(obj + 0x30, D_L05_001B3620);
        euler_rotation_basis(obj, D_L05_001B3610);
        if (math_fast_float_d(&g_ship_transition_timer)) {
            func_PAL_L00_002B3000();
        } else {
            float t = 0.16000001f;
            if (g_current_map_index == 20) t = 0.32000002f;
            ship_update_record_transform(obj, t);
            if ((((int)(D_L05_001B1ADC - 20) * 5 + 2) / 6) < g_ship_transition_timer) {
                slot_copy_records_to_free(D_L05_002B8770);
            }
        }
        break;
    case 7:
        D_L05_001B1F64_sda = D_L05_001B1F64 + 0.05f;
        if (D_L05_001B1F64_sda >= 1.0f) {
            D_L05_001B1F64 = 1.0f;
            g_ship_state = 8;
            func_PAL_L05_00448790(obj);
        }
        break;
    case 8:
        D_L05_001B1F64_sda = D_L05_001B1F64 - 0.05f;
        if (D_L05_001B1F64_sda <= 0.0f) {
            D_L05_001B1F64 = 0.0f;
            g_ship_state = 0;
        }
        break;
    }
}
