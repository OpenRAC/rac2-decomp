#include "common.h"

typedef int Vector __attribute__((mode(TI)));
extern float D_L02_001B03E0[4] __attribute__((sda));
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *CreateMoby(int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_002A0F48(char *);
extern void mat_normalize_columns(void *);
extern void func_002A10E8(char *);
extern int flag_set_first_pending(char *);
extern int FastDecTimer(void *);
extern float IntToFloat(int);
extern void chainblade_release_held_actors(char *);

/* Per-frame update for moby class 2581. Updates a lift-like moby that slides along its direction while its animation plays, and keeps a child moby stuck to its joint. */
void sliding_l02_platform_update(char *moby) {
    float startPos[4] __attribute__((aligned(16)));
    /* Separate initial and final query events use four measured local vectors. */
    float moveDelta[4] __attribute__((aligned(16)));
    float jointPos[4] __attribute__((aligned(16)));
    float rotatedOffset[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    Vector *sourceRow;
    Vector *destRow;
    int i;
    qcopy(startPos, moby + 0x10);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(vars + 0x10) = 0;
        *(int *)(vars + 0x14) = 0;
        *(int *)(vars + 0x18) = 0;
        moby_set_state(moby, 2, -1);
        if (*(unsigned char *)(moby + 0x43) != 0) anim_start_blended(moby, 0, 0, 0);
        *(float *)(moby + 0x48) = 0.0f;
        vec_scale_to_length(moveDelta, moby + 0xD0, 2.0f);
        FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
        qcopy(vars, moby + 0x10);
        *(char **)(vars + 0x1C) = CreateMoby(0x1172 /* moby class 4466 */);
        if (*(char **)(vars + 0x1C) == 0) return;
        *(unsigned short *)(*(char **)(vars + 0x1C) + 0x34) |= 0x41;
        *(unsigned char *)(*(char **)(vars + 0x1C) + 0x30) = *(unsigned char *)(moby + 0x30);
        *(short *)(*(char **)(vars + 0x1C) + 0x32) = 0;
        moby_transform_joint_to_world(moby, 0, (char *)jointPos);
        matrix_mul_vec3(rotatedOffset, D_L02_001B03E0, moby + 0xC0);
        FastVecAdd(jointPos, rotatedOffset, jointPos);
        {
            char *child = *(char **)(vars + 0x1C);
            qcopy(child + 0x10, jointPos);
            func_002A0F48(child);
        }
        {
            Vector *row = (Vector *)(moby + 0xC0);
            Vector *out = (Vector *)(*(char **)(vars + 0x1C) + 0xC0);
            int count = 0;
            do {
                qcopy(out, row);
                count++;
                row++;
                out++;
            } while (count < 3);
        }
        mat_normalize_columns(*(char **)(vars + 0x1C) + 0xC0);
        func_002A10E8(*(char **)(vars + 0x1C));
        *(unsigned short *)(*(char **)(vars + 0x1C) + 0x34) |= 6;
        break;
    case 1:
        if (flag_set_first_pending(moby)) *(short *)(vars + 0x22) = 19;
        if (!FastDecTimer(vars + 0x22)) {
            vec_scale_to_length(moveDelta, moby + 0xD0, 2.0f / IntToFloat(19));
            FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
        }
        if (*(unsigned char *)(moby + 0x60) & 2) {
            qcopy(moby + 0x10, vars);
            *(float *)(moby + 0x48) = 0.0f;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) *(short *)(vars + 0x22) = 19;
        if (!FastDecTimer(vars + 0x22)) {
            vec_scale_to_length(moveDelta, moby + 0xD0, -2.0f / IntToFloat(19));
            FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
        }
        if (*(unsigned char *)(moby + 0x60) & 2) {
            *(float *)(moby + 0x48) = 0.0f;
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        moby_set_state(moby, 5, -1);
        *(float *)(moby + 0x48) = 1.0f;
        if (*(unsigned char *)(moby + 0x43) != 1) anim_start_blended(moby, 1, 0, 0);
        chainblade_release_held_actors(moby);
        break;
    case 5:
        if (*(unsigned char *)(moby + 0x60) & 2) {
            *(short *)(vars + 0x20) = 90;
            *(float *)(moby + 0x48) = 0.0f;
            moby_set_state(moby, 6, -1);
        }
        break;
    case 6:
        if (!*(short *)(vars + 0x20)) {
        *(float *)(moby + 0x48) = 1.0f;
        if (*(unsigned char *)(moby + 0x43) != 2) anim_start_blended(moby, 2, 0, 0);
        moby_set_state(moby, 7, -1);
        } else {
            FastDecTimer(vars + 0x20);
        }
        break;
    case 7:
        if (*(unsigned char *)(moby + 0x60) & 2) {
            if (*(unsigned char *)(moby + 0x43) != 3) anim_start_blended(moby, 3, 0, 0);
            moby_set_state(moby, 1, -1);
        }
        break;
    }
    if (*(char **)(vars + 0x1C) && *(float *)(moby + 0x48) != 0.0f) {
        moby_transform_joint_to_world(moby, 0, (char *)moveDelta);
        matrix_mul_vec3(jointPos, D_L02_001B03E0, moby + 0xC0);
        FastVecAdd(moveDelta, jointPos, moveDelta);
        {
            char *child = *(char **)(vars + 0x1C);
            qcopy(child + 0x10, moveDelta);
            func_002A0F48(child);
        }
        {
        char *childMatrix = *(char **)(vars + 0x1C);
        sourceRow = (Vector *)(moby + 0xC0);
        destRow = (Vector *)(childMatrix + 0xC0);
        for (i = 0; i < 3; i++) {
            *destRow = *sourceRow;
            sourceRow++;
            destRow++;
        }
        mat_normalize_columns(childMatrix + 0xC0);
        }
        func_002A10E8(*(char **)(vars + 0x1C));
        *(unsigned short *)(*(char **)(vars + 0x1C) + 0x34) |= 6;
    }
}
