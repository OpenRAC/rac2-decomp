#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;
extern char *D_L20_001B2F9C __attribute__((sda));
extern void moby_set_state(char *, int, int);
extern float fast_subtract_rotations(float, float);
extern void FastVecAdd(char *, char *, char *);
extern unsigned char D_0019B2E8[];
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int g_current_map_index __attribute__((sda));
extern void func_PAL_L09_003EF588(char *);
extern void vec_scale_to_length(void *, void *, float);
extern int flag_is_third_pending_set(char *);
extern int flag_set_first_pending(char *);
extern int PlayMobySound(int, int, char *);
extern void yeedil_wake_group_troopers(char *);
extern void *jtbl_002B5940[];

void func_PAL_L20_0044A780(char *obj) {
    /* Keep all eight destinations represented by the level's dispatch table. */
    static void *volatile states[] = {
        &&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7
    };
    Vec4 v, w;
    unsigned int sel;
    char *state = *(char **)(obj + 0x68);
    char *target = D_L20_001B2F9C + (*(int *)state << 8);

    sel = *(unsigned char *)(obj + 0x20);
    if (sel >= 8) goto c7;
    goto *jtbl_002B5940[sel];
    c0:
        if (*(int *)(state + 8)>=0) *(char **)(state + 0x10)=(char *)(D_L20_001B2F9C+(*(int *)(state + 8)<<8));
        else *(char **)(state + 0x10)=0;
        moby_set_state(obj, 1, -1); goto c7;
    c1:
        if (flag_is_third_pending_set(target)) {
            PlayMobySound(0, 0, obj);
            moby_set_state(obj, 2, -1);
        }
        if (D_0019B2E8[(unsigned char)obj[0xB0]+g_current_map_index*16]&0x80) {
            *(float *)(obj + 0xF0)=fast_subtract_rotations(*(float *)(obj + 0xF0), 1.5707965f);
            moby_set_state(obj, 6, -1);
        }
        goto c7;
    c2:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.5707965f, 0.000767945f, 251.32744f, 349.06592f);
        if (*(float *)(obj + 0xF0)<=-0.785398245f) {
            char *other=*(char **)(state + 0x10);
            if (other && *(short *)(other + 0xAA)==0xCBC && (unsigned char)other[0x20]!=0xFE && (unsigned char)other[0x20]!=0xFD)
                func_PAL_L09_003EF588(other);
        }
        if (*(float *)(obj + 0xF0)<=-1.5707965f) { *(int *)(state + 4)=0; moby_set_state(obj, 3, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c3:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.308997f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (*(float *)(obj + 0xF0)>=-1.308997f) { *(int *)(state + 4)=0; moby_set_state(obj, 4, -1); }
        goto c7;
    c4:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.5707965f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(obj + 0xF0)<=-1.5707965f) { *(int *)(state + 4)=0; moby_set_state(obj, 5, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c5:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.48353f, 0.025132746f, 0.00062831864f, 1.0471977f);
        if (*(float *)(obj + 0xF0)>=-1.48353f) { *(int *)(state + 4)=0; moby_set_state(obj, 6, -1); }
        goto c7;
    c6:
        if (flag_set_first_pending(obj)) yeedil_wake_group_troopers(obj);
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.5707965f, 0.00062831864f, 0.25132746f, 3.4906592f);
        if (*(float *)(obj + 0xF0)<=-1.5707965f) { *(int *)(state + 4)=0; moby_set_state(obj, 7, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c7:
    {
        char *pos = target + 0x10;

        qcopy(pos, obj + 0x10);
        vec_scale_to_length(&v, obj + 0xE0, 5.7f);
        FastVecAdd(pos, pos, (char *)&v);
        vec_scale_to_length(&w, obj + 0xD0, 0.35f);
        FastVecAdd(pos, pos, (char *)&w);
    }
}

