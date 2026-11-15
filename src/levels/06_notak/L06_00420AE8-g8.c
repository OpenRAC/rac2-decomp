#include "common.h"
extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(char *, int);
extern void func_002A7470(char *, int, int, int);
extern void func_0026FEB8(char *);
extern float func_00283248(float, float);

extern int func_L06_00420230(char *);
extern int func_002B1C20(char *, char *);
/* Callers set a mode in $a1 after the four floats; each EE register bank keeps its order. */
extern int func_L06_00420548(char *, float, float, float, float, int);
extern char D_L06_001B0830[];
extern char *D_L06_001FE500[];

extern void func_L06_00382608(void *, int, unsigned int, int, int, float);
extern int func_L06_00382850(void *, void *, float);
extern void func_L00_00341820(void *, void *, int *, float *, int, float);
extern void func_L03_00339128(void *, void *, int, unsigned int, int, int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283B98(float, float);
extern int func_L06_00420740(char *, int, void *, void *, float, float, float, float,
                            float, float, float, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern float func_0029F530(void *);
extern void *func_003280C8(void *, void *, void *, int, int, float);
extern char *func_0032DA58(void *, void *, void *, float);
extern void func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_002A7A00(void *, float, float);
extern float func_00282C48(float);
extern char *func_00273730(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_00310C88(void);
extern void func_002A6C58(void *, int, int);
extern void func_0029F338(void *);
extern void func_L06_0041FD90(void *);
extern char D_L06_001AC520[] MACRO_ADDR;
extern char D_00189EA0[];
extern char D_L06_001B9840[];
extern char D_L06_001A8F20[] MACRO_ADDR;
extern char D_00188660[];
extern char *D_L06_001B290C MACRO_ADDR;
extern int D_L06_001B2348 MACRO_ADDR;

typedef int L06Quad __attribute__((mode(TI)));

/* A level path: a count in the first quadword, then the points. */
typedef struct {
    int count;
    int pad[3];
    float points[1][4];
} L06Path;

/* A path or object basis: three axes and the inverse computed from them. */
typedef struct {
    float direction[4];
    float side[4];
    float up[4];
    float inverse[16];
} L06Basis;

void func_L06_00420AE8(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    unsigned int state;
    int flags;
    if (func_L06_00420230(obj)) {
        func_0029F338(obj);
    } else {
        switch ((unsigned char)obj[0x95]) {
        case 0:
            state = (unsigned char)obj[0x20];
            if (*(int *)(st + 0x258) > 0) {
                if (state < 3) {
                    func_002A7750(obj, 2, 1);
                } else if (state < 8) {
                    if (IsPointInCuboid(obj + 0x10, *(int *)(st + 0x268))) {
                        if (*(int *)(st + 0x2A0) != -1) func_002A7750(obj, 6, 1);
                        else func_002A7750(obj, 5, 1);
                    } else {
                        if (*(int *)(st + 0x2A0) != -1) func_002A7750(obj, 4, 1);
                        else func_002A7750(obj, 3, 1);
                    }
                }
            } else if (state >= 4) {
                if (state < 8) {
                    if (IsPointInCuboid(obj + 0x10, *(int *)(st + 0x268))) {
                        if (*(int *)(st + 0x2A0) != -1) func_002A7750(obj, 6, 1);
                        else func_002A7750(obj, 5, 1);
                    } else {
                        if (*(int *)(st + 0x2A0) != -1) func_002A7750(obj, 4, 1);
                        else func_002A7750(obj, 3, 1);
                    }
                }
            }
            *(int *)(st + 0x278) = 0;
            break;
        case 1:
            *(int *)(st + 0x278) = 0;
            if (*(int *)(st + 0x258) != 1) {
                if (*(int *)(st + 0x258) == 2) {
                    if ((unsigned int)((unsigned char)obj[0x20] - 3) < 5) obj[0x95] = 2;
                } else if ((unsigned int)((unsigned char)obj[0x20] - 3) < 5) {
                    if (*(int *)(st + 0x2A0) != -1) func_002A7750(obj, 4, 1);
                    else func_002A7750(obj, 3, 1);
                }
            }
            break;
        case 2:
            *(int *)(st + 0x278) = 0;
            if (*(int *)(st + 0x258) == 1) obj[0x95] = 1;
            else if (*(int *)(st + 0x258) == 0) obj[0x95] = 0;
            break;
        case 3:
            ++*(int *)(st + 0x278);
            flags = func_002B1C20(obj, st + 0x60);
            if (flags & 1) {
                func_002A7750(obj, 8, -1);
            } else if (flags & 2) {
                if (*(unsigned char *)(obj + 0x43) != 1) func_002A7470(obj, 1, 0, 10);
                *(int *)(st + 0x278) = 0;
                qzero(st + 0x230);
                obj[0x95] = 0;
            }
            break;
        }
        switch ((unsigned char)obj[0x20]) {
        case 0:
            STUB_printf(D_L06_001B0830);
            break;
        case 2: {
            char *path;
            if (func_L06_00420548(obj, 12.0f, 12.0f,
                                 func_00283248(*(float *)(st + 0x220) - *(float *)(obj + 0x10),
                                             *(float *)(st + 0x224) - *(float *)(obj + 0x14)),
                                 0.0f, 0)) {
                path = D_L06_001FE500[*(int *)(st + 0x274)];
                ++*(int *)(st + 0x26C);
                if (*(int *)(st + 0x26C) >= *(int *)path) {
                    if (*(int *)(st + 0x2A0) == -1) {
                        *(int *)(st + 0x26C) = 0;
                        qcopy(st + 0x220, D_L06_001FE500[*(int *)(st + 0x270)] + 0x10);
                        qcopy(st + 0x210, st + 0x220);
                        func_002A7750(obj, 3, -1);
                    } else func_002A7750(obj, 4, -1);
                } else qcopy(st + 0x220, ((L06Path *)path)->points[*(int *)(st + 0x26C)]);
            }
            break;
        }
        case 3: {
            /* Its own block: these stack slots are free again for the next case. */
            {
                L06Basis basis;
                float offset[4], target[4], test[4];
                L06Basis basis2;
                int index;
                float fraction, distance, yaw;
                char *path, *up;
                int node;
                DrawPath(obj, *(int *)(st + 0x270), 0x80808080, 4, 1, 0.75f);
                path = D_L06_001FE500[*(int *)(st + 0x270)];
                node = func_L06_00382850(st + 0x1C0, path, 0.0f);
                if (node > 0)
                    FastVecSub(basis.direction, path + ((node << 4) + 0x10), path + (node << 4));
                else
                    FastVecSub(basis.direction, path + ((node << 4) + 0x20), path + ((node << 4) + 0x10));
                up = D_L06_001AC520;
                vec_scale_to_length(basis.direction, basis.direction, 1.0f);
                qcopy(basis.up, up);
                FastVecCross(basis.side, basis.direction, basis.up);
                matrix_from_basis_rows(basis.inverse, basis.direction);
                FastVecSub(offset, st + 0x1C0, path + ((node << 4) + 0x10));
                transform_vector(offset, offset, basis.inverse);
                qcopy(target, D_00189EA0);
                target[2] += 2.0f;
                /* Retail restarts from the target before each component update. */
                qcopy(test, target);
                test[0] += offset[0];
                qcopy(test, target);
                test[1] += offset[1];
                qcopy(test, target);
                test[2] += offset[2];
                index = node;
                while (index > 0 && vec_distance_xy(st + 0x1C0, path + ((index << 4) + 0x10)) < 6.0f)
                    --index;
                distance = vec_distance_xy(st + 0x1C0, path + ((index << 4) + 0x10)) - 6.0f;
                fraction = 0.0f;
                func_L03_00339128(path + ((index << 4) + 0x10), obj, 2, 0x80000080, 0x7F, 20, 255, 0.33f);
                Spline_AdvanceByDistance(path, target, &index, &fraction, 0, distance);
                func_L03_00339128(target, obj, 3, 0x80008000, 0x7F, 20, 255, 1.0f);
                yaw = func_00283248(*(float *)(st + 0x1C0) - *(float *)(obj + 0x10),
                                   *(float *)(st + 0x1C4) - *(float *)(obj + 0x14));
                if (vec_distance_xy(obj + 0x10, st + 0x1C0) > 8.0f)
                    yaw = FastAddRotations(yaw, func_00283198(func_002ABB18(IntToFloat(D_L06_001B2348) * 0.02f)) * 0.7853982448577881f);
                index = func_L06_00382850(target, path, 0.0f);
                if (func_L06_00420548(obj, 12.0f, 6.0f, yaw, 0.0f, 1)) {
                    int desired = index;
                    if (desired < *(int *)(st + 0x26C)) ++desired;
                    else --desired;
                    if (desired < 0) desired = 0;
                    if (desired < *(int *)(st + 0x26C)) {
                        --*(int *)(st + 0x26C);
                        qcopy(st + 0x210, ((L06Path *)path)->points[*(int *)(st + 0x26C)]);
                    } else if (desired > *(int *)(st + 0x26C)) {
                        ++*(int *)(st + 0x26C);
                        qcopy(st + 0x210, ((L06Path *)path)->points[*(int *)(st + 0x26C)]);
                    } else {
                        qcopy(st + 0x210, target);
                        *(int *)(st + 0x26C) = desired;
                    }
                    if (*(int *)(st + 0x26C) > *(int *)path - 1)
                        *(int *)(st + 0x26C) = *(int *)path - 1;
                    else if (*(int *)(st + 0x26C) < 0)
                        *(int *)(st + 0x26C) = 0;
                }
                node = *(int *)(st + 0x26C);
                if (node > 0)
                    FastVecSub(basis2.direction, path + ((node << 4) + 0x10), path + (node << 4));
                else
                    FastVecSub(basis2.direction, path + ((node << 4) + 0x20), path + ((node << 4) + 0x10));
                vec_scale_to_length(basis2.direction, basis2.direction, 1.0f);
                qcopy(basis2.up, D_L06_001AC520);
                FastVecCross(basis2.side, basis2.direction, basis2.up);
                offset[0] = 0.0f;
                offset[2] = 0.0f;
                if (offset[1] > *(float *)(st + 0x29C)) offset[1] = *(float *)(st + 0x29C);
                else if (offset[1] < -*(float *)(st + 0x29C)) offset[1] = -*(float *)(st + 0x29C);
                matrix_mul_vec3(offset, offset, basis2.direction);
                FastVecAdd(st + 0x220, st + 0x210, offset);
                func_L03_00339128(st + 0x220, obj, 5, 0x80800080, 0x7F, 30, 255, 1.2f);
            }
            break;
        }
        case 4:
        case 6: {
            /* Its own block: these stack slots are free again for the next case. */
            {
                float local[4];
                L06Basis basis;
                float target[4], offset[4], velocity[4], acceleration[4], shot[4], joint[4];
                float width, height, distance, phase;
                char *record = D_L06_001B290C + (*(int *)(st + 0x2A0) << 7);
                FastVecSub(local, st + 0x190, record + 0x30);
                euler_rotation_basis(basis.direction, record + 0x70);
                matrix_from_basis_rows(basis.inverse, basis.direction);
                transform_vector(local, local, basis.inverse);
                local[0] -= 6.0f;
                width = FastVecLength(record);
                height = FastVecLength(record + 0x10);
                if (local[0] > width) local[0] = width;
                else if (local[0] < -width) local[0] = -width;
                if (local[1] > height) local[1] = height;
                else if (local[1] < -height) local[1] = -height;
                local[2] = 0.0f;
                matrix_mul_vec3(local, local, basis.direction);
                FastVecAdd(st + 0x220, record + 0x30, local);
                if (*(int *)(st + 0x258) == 0) {
                    char *path = D_L06_001FE500[*(int *)(st + 0x274)];
                    qcopy(st + 0x220, ((L06Path *)path)->points[*(int *)path - 1]);
                }
                if (vec_distance_xy(obj + 0x10, *(char **)(st + 0x1A0) + 0x10) < 13.0f) {
                    target[0] = func_00283180(*(float *)(record + 0x78)) * 8.0f;
                    target[1] = func_00283198(*(float *)(record + 0x78)) * 8.0f;
                    target[2] = 0.0f;
                    FastVecAdd(target, obj + 0x10, target);
                    *(L06Quad *)(st + 0x220) = *(L06Quad *)target;
                }
                if (*(int *)(st + 0x334)) qcopy(st + 0x220, obj + 0x10);
                *(float *)(st + 0x228) = *(float *)(record + 0x38) + 1.0f;
                if ((unsigned char)obj[0x20] == 6)
                    func_00283248(*(float *)(st + 0x190) - *(float *)(obj + 0x10),
                                *(float *)(st + 0x194) - *(float *)(obj + 0x14));
                func_L06_00420740(obj, 1, basis.direction, basis.inverse,
                    func_00283248(*(float *)(st + 0x190) - *(float *)(obj + 0x10),
                                *(float *)(st + 0x194) - *(float *)(obj + 0x14)),
                    0.0f, 5.0f, 12.0f, 10.0f, 10.0f, 10.0f, 10.0f, 0.02f, 6.0f);
                distance = vec_distance_xy(obj + 0x10, st + 0x190);
                func_0029FCC0(obj, 4, target);
                FastVecSub(offset, st + 0x190, st + 0x190);
                FastVecScale(offset, offset, 0.0f);
                FastVecAdd(offset, offset, st + 0x190);
                *(float *)(st + 0x314) = func_00283248(vec_distance_xy(st + 0x190, target), target[2] - *(float *)(st + 0x198));
                func_002AEC48(obj, st + 0x2B0, 1, 0.03f, 0.3f);
                if (distance < *(float *)(st + 0x338) * 20.0f) {
                    if (*(unsigned char *)(obj + 0x43) != 4) {
                        *(float *)(obj + 0x48) = 0.5f;
                        if (*(unsigned char *)(obj + 0x43) != 3) func_002A7470(obj, 3, 0, 10);
                    } else if ((unsigned char)obj[0x42] == *(unsigned char *)(obj + 0x43) && (obj[0x60] & 2)) {
                        *(float *)(obj + 0x48) = 0.5f;
                        func_002A7470(obj, 3, 0, 10);
                    }
                    func_0029FC20(obj, 1, joint);
                    vec_scale_to_length(velocity, joint, 0.3333333432674408f);
                    FastVecAdd(velocity, velocity, st + 0x230);
                    FastVecScale(acceleration, velocity, 1.0f / IntToFloat(6));
                    if ((unsigned char)obj[0x42] == 3) {
                        phase = func_0029F530(obj);
                        if (phase >= 4.0f) {
                            if (phase < 4.4f) {
                                FastVecSub(shot, st + 0x190, target);
                                vec_scale_to_length(shot, shot, 0.3333333432674408f);
                                func_003280C8(obj, shot, target, 0, 0, *(float *)(st + 0x2A8));
                                *(float *)(st + 0x2AC) += 1.0f;
                            }
                        }
                        if (*(float *)(st + 0x2AC) == 4.0f) {
                            *(float *)(st + 0x2AC) = 0.0f;
                            if (*(unsigned char *)(obj + 0x43) != 4) func_002A7470(obj, 4, 0, 10);
                            *(float *)(obj + 0x48) = 0.5f;
                        }
                    }
                } else {
                    *(float *)(obj + 0x48) = 1.0f;
                    if (*(unsigned char *)(obj + 0x43) != 0) func_002A7470(obj, 0, 0, 10);
                }
            }
            break;
        }
        case 8: {
            float local[4], direction[4], velocity[4];
            char *rec, *effect;
            int i;
            /* Retail reads sp+0x10 here without initializing it on this path. */
            FastVecSub(direction, D_L06_001B9840, local);
            vec_scale_to_length(direction, direction, 1.0f);
            func_0032DA58(obj, obj + 0x10, direction, 5.0f);
            PlayMobySound(3, 0, obj);
            if (*(int *)(st + 0x254) != -1) {
                rec = D_00188660 + *(int *)(st + 0x254) * 0x70;
                if (*(char **)(rec + 0x88) == obj && *(unsigned char *)(rec + 0x74))
                    func_002E59F8(*(int *)(st + 0x254));
            }
            *(int *)(st + 0x254) = -1;
            for (i = 0; i < 6; ++i) {
                func_002A7A00(velocity, 0.13333334028720856f, 0.20000001788139343f);
                velocity[2] = func_00282C48(velocity[2]) * 2.5f;
                FastVecAdd(velocity, velocity, D_L06_001A8F20);
                effect = func_00273730(obj, 1, *(short *)(obj + 0xAA), i, obj + 0x10, obj + 0xF0, velocity, 255, 30.0f, 15.0f);
                *(void (**)(void))(effect + 0x64) = func_00310C88;
            }
            SetDeathBits(obj, 0, 3);
            func_0029F338(obj);
            goto done;
        }
        default:
            break;
        }
        func_L06_0041FD90(obj);
    }
done:
    return;
}
