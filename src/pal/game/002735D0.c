#include "include_asm.h"


#include "common.h"
extern int moby_get_joint_matrix(void *, void *, int, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern void moby_get_joint_midpoint(void *, int, void *);

void cam_moby_init_tracking_pal(char *obj, int mode, int index, void *a, void *b, unsigned char tag, float angle) {
    char *p;
    float local[4];
    *(int *)(obj+0x98) = 0;
    *(unsigned short *)(obj+0x34)|=0x100;
    p = *(char **)(obj+0x68);
    qcopy(p, a);
    qcopy(p+0x10, b);
    *(float *)(p+0x38) = 0.45f;
    *(float *)(p+0x3c) = 0.040000003f;
    *(float *)(p+0x40) = 0.5f;
    *(float *)(p+0x44) = 0.015707966f;
    *(float *)(p+0x48) = angle*0.00040000002f;
    *(float *)(p+0x4c) = 0.0025132746f;
    *(short *)(p+0x34) = 150;
    p[0x5e] = tag;
    p[0x5d] = mode;
    p[0x58] = 0;
    p[0x5c] = 0;
    *(int *)(p+0x30) = 0;
    switch (mode) {
        case 2:
        *(short *)(p+0x36) = index;
        *(short *)(obj+0x7c) = (1<<index)|0x8000;
        p[0x58] = moby_get_joint_matrix(obj, p+0x20, *(int *)(p+0x30), index);
        FastVecSub(p+0x20, p+0x20, obj+0x10);
        vec_transform_by_object_or_given(obj, p+0x20, p+0x20, 0);
        break;
        case 0: case 3:
        FastVecScale(p+0x20, obj, 0.0009765625f);
        *(float *)(p+0x2c) = *(float *)(obj+0xc)*0.0009765625f;
        FastVecSub(p+0x20, p+0x20, obj+0x10);
        vec_transform_by_object_or_given(obj, p+0x20, p+0x20, 0);
        break;
        case 1:
        *(short *)(p+0x36) = index;
        *(short *)(obj+0x7c) = (mode<<index)|0x8000;
        moby_get_joint_midpoint(obj, index, local);
        FastVecSub(p+0x20, local, obj+0x10);
        vec_transform_by_object_or_given(obj, p+0x20, p+0x20, 0);
        break;
    }
}



extern void Fdb046c5d_FUN_002742E8(void *);
extern void Fdb046c5d_FUN_00274128(void *);
extern int Fdb046c5d_FUN_00274500(void *);
extern void Fdb046c5d_FUN_00282F20(float, void *, void *);
extern void Fdb046c5d_FUN_00282DD8(void *, void *, void *);
extern void Fdb046c5d_FUN_00274A88(void *, void *, void *);
extern void Fdb046c5d_FUN_002AFFD8(void *, void *, int);
extern int Fdb046c5d_FUN_00274BA8(void *, void *, void *, float, float);
extern int Fdb046c5d_FUN_002E5CF8(int, int, void *);
extern unsigned int Fdb046c5d_FUN_00274768(void *, int, void *);
extern int Fdb046c5d_FUN_002E5F00(int, void *);
extern char Fdb046c5d_D_001BAFC0[];

int target_seeker_update_pal(char *obj)
{
    float buf[4];
    float out[4];
    char *p;
    char *seeker_pos;
    unsigned char k;
    int r;
    int sound_id;
    int target_slot;

    p = *(char **)(obj + 104);
    k = *(unsigned char *)(p + 92);
    if (k >= 3)
        return 1;
    if (k != 0)
        Fdb046c5d_FUN_002742E8(obj);
    else
        Fdb046c5d_FUN_00274128(obj);

    target_slot = Fdb046c5d_FUN_00274500(obj);
    if (target_slot == -1)
        return 0;

    seeker_pos = Fdb046c5d_D_001BAFC0;
    sound_id = -1;
    Fdb046c5d_FUN_00282F20(1.0f, seeker_pos, seeker_pos);
    Fdb046c5d_FUN_00282DD8(buf, seeker_pos, p);
    Fdb046c5d_FUN_00274A88(obj, p + 16, buf);
    Fdb046c5d_FUN_002AFFD8(obj + 16, out, 1);
    r = Fdb046c5d_FUN_00274BA8(p, seeker_pos, out, *(float *)(p + 56), *(float *)(p + 60));
    if (r == 0) {
        if (*(unsigned char *)(p + 94) != 255 && *(unsigned char *)(p + 92) == 0)
            sound_id = Fdb046c5d_FUN_002E5CF8(*(unsigned char *)(p + 94), 0, obj);
        Fdb046c5d_FUN_00274768(obj, target_slot, out);
    } else {
        if (*(unsigned char *)(p + 94) != 255)
            sound_id = Fdb046c5d_FUN_002E5CF8(*(unsigned char *)(p + 94), 0, obj);
    }
    if (sound_id != -1)
        Fdb046c5d_FUN_002E5F00(sound_id, p + 32);
    return 0;
}

