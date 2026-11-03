/* functional: high. Same calls, arguments, reads and writes as retail, written as plain loops (the near miss's goto shaping removed). */

/* Rebuilds the 8x8 grid of a deformable surface moby: when its group's spawn state (func_002A8508(group, -1))
 * is 5, it walks the group list D_001EE5A0[group] (16-bit moby indices into D_001B1B5C, 0x100 bytes each, the
 * last with bit 15 set) and takes each control-point moby's (class 0x1130) x and y into state +0x50/+0x60
 * [selector] (selector clamped to 0..3), and the first one's z into +0x70; else it clears them. Then each grid
 * point (row, column) of surface +0x40 is the bilinear blend of the four control points at steps of 1/7,
 * stored as x, y and the common z into D_00222AE0[surface * 64 + row * 8 + column]. */

typedef struct { float x, y, z, w; } SurfaceGridPoint;

extern unsigned short *D_001EE5A0[];
extern int D_001B1B78;
extern char *D_001B1B5C;
extern SurfaceGridPoint D_00222AE0[];
extern int func_002A8508(int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

void func_00303210(char *object)
{
    char *state = *(char **)(object + 0x68);
    float first[4] __attribute__((aligned(16)));
    float second[4] __attribute__((aligned(16)));
    float right[4] __attribute__((aligned(16)));
    float left[4] __attribute__((aligned(16)));
    int column, row, surface;

    if (func_002A8508(*(unsigned char *)(object + 0x21), -1) == 5) {
        unsigned short *entry = D_001EE5A0[*(unsigned char *)(object + 0x21)];
        for (;;) {
            unsigned int list = *(unsigned char *)(object + 0x21);
            char *control;
            if (list == 0xff || D_001B1B78 < (int)list || entry == 0)
                break;
            if (!((short)entry[-1] >= 0 || entry == D_001EE5A0[list]))
                break;
            control = D_001B1B5C + ((*entry & 0x7fff) << 8);
            if (control == 0)
                break;
            if (*(short *)(control + 0xaa) == 0x1130) {
                char *settings = *(char **)(control + 0x68);
                if (*(unsigned int *)(settings + 0x14) >= 4)
                    *(unsigned int *)(settings + 0x14) = 0;
                ((float *)(state + 0x50))[*(unsigned int *)(settings + 0x14)] = *(float *)(control + 0x10);
                ((float *)(state + 0x60))[*(unsigned int *)(settings + 0x14)] = *(float *)(control + 0x14);
                entry++;
                if (*(unsigned int *)(settings + 0x14) == 0)
                    *(float *)(state + 0x70) = *(float *)(control + 0x18);
            } else {
                entry++;
            }
        }
    } else {
        *(int *)(state + 0x50) = 0;
        *(int *)(state + 0x60) = 0;
        *(int *)(state + 0x54) = 0;
        *(int *)(state + 0x64) = 0;
        *(int *)(state + 0x58) = 0;
        *(int *)(state + 0x68) = 0;
        *(int *)(state + 0x5c) = 0;
        *(int *)(state + 0x6c) = 0;
        *(int *)(state + 0x70) = 0;
    }

    surface = *(int *)(state + 0x40);
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            float columnWeight = (float)column * 0.14285715f;
            SurfaceGridPoint *point;
            first[0] = *(float *)(state + 0x54) - *(float *)(state + 0x50);
            first[1] = *(float *)(state + 0x64) - *(float *)(state + 0x60);
            first[2] = 0.0f;
            first[3] = 1.0f;
            second[0] = *(float *)(state + 0x58) - *(float *)(state + 0x5c);
            second[1] = *(float *)(state + 0x68) - *(float *)(state + 0x6c);
            second[2] = 0.0f;
            second[3] = 1.0f;
            func_00282D30(first, first, columnWeight);
            func_00282D30(second, second, columnWeight);
            left[0] = *(float *)(state + 0x50);
            left[1] = *(float *)(state + 0x60);
            left[2] = 0.0f;
            left[3] = 1.0f;
            func_00282CC0(left, left, first);
            right[0] = *(float *)(state + 0x5c);
            right[1] = *(float *)(state + 0x6c);
            right[2] = 0.0f;
            right[3] = 1.0f;
            func_00282CC0(right, right, second);
            func_00282CF0(right, right, left);
            func_00282D30(right, right, (float)row * 0.14285715f);
            func_00282CC0(left, left, right);
            point = &D_00222AE0[surface * 64 + row * 8 + column];
            point->x = left[0];
            point->y = left[1];
            point->z = *(float *)(state + 0x70);
        }
    }
}
