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
extern void moby_destroy_with_explosion(char *);
extern void vec_scale_to_length(void *, void *, float);
extern int flag_is_third_pending_set(char *);
extern int flag_set_first_pending(char *);
extern int PlayMobySound(int, int, char *);
extern void yeedil_wake_group_troopers(char *);
extern void *jtbl_002B5940[];

/* Runs the swinging arm (moby class 4584). It goes through its raise, drop and settle steps and keeps its linked object attached to it. */
void swinging_l20_arm_update(char *obj) {
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
            *(float *)(obj + 0xF0)=fast_subtract_rotations(*(float *)(obj + 0xF0), 1.57079649f);
            moby_set_state(obj, 6, -1);
        }
        goto c7;
    c2:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.57079649f, 0.000533295097f, 174.532944f, 290.888275f);
        if (*(float *)(obj + 0xF0)<=-0.785398245f) {
            char *other=*(char **)(state + 0x10);
            if (other && *(short *)(other + 0xAA)==MOBY_CLASS_MEGACORP_HOVER_TANK && (unsigned char)other[0x20]!=0xFE && (unsigned char)other[0x20]!=0xFD)
                moby_destroy_with_explosion(other);
        }
        if (*(float *)(obj + 0xF0)<=-1.57079649f) { *(int *)(state + 4)=0; moby_set_state(obj, 3, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c3:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.30899704f, 0.0174532942f, 0.000436332368f, 0.87266475f);
        if (*(float *)(obj + 0xF0)>=-1.30899704f) { *(int *)(state + 4)=0; moby_set_state(obj, 4, -1); }
        goto c7;
    c4:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.57079649f, 0.000436332368f, 0.17453295f, 2.90888262f);
        if (*(float *)(obj + 0xF0)<=-1.57079649f) { *(int *)(state + 4)=0; moby_set_state(obj, 5, -1); PlayMobySound(1, 0, obj); }
        goto c7;
    c5:
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.48353004f, 0.0174532942f, 0.000436332368f, 0.87266475f);
        if (*(float *)(obj + 0xF0)>=-1.48353004f) { *(int *)(state + 4)=0; moby_set_state(obj, 6, -1); }
        goto c7;
    c6:
        if (flag_set_first_pending(obj)) yeedil_wake_group_troopers(obj);
        math_step_value_toward_target(obj + 0xF0, state + 4, -1.57079649f, 0.000436332368f, 0.17453295f, 2.90888262f);
        if (*(float *)(obj + 0xF0)<=-1.57079649f) { *(int *)(state + 4)=0; moby_set_state(obj, 7, -1); PlayMobySound(1, 0, obj); }
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
