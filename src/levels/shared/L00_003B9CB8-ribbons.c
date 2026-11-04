#include "common.h"

extern float func_002A7878(float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern char D_L00_001B8DC0[];
typedef struct {
    float corner[4][4];
    int color[4];
    float uv[8];
    unsigned long long tags[4];
} RibbonPacket;

extern void ref_L00_003BC468_00(void *, int);
extern void ref_L00_003BC468_01(char *);
typedef int Rac2TI128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec16_Fc936841d;
extern long long func_002E67A0_2(int);
extern void func_802EE138_1(float *, float *, char *);
extern void func_802EE3D0_1(float *, float *, float);
extern void func_002EE178_1(char *, char *, float);
extern void func_802EAC30_1(char *, float *, int);
/* Draws two colored, scrolling ribbons along the supplied polyline. */
void func_L00_003BC468(int unused, int width, Vec16_Fc936841d *points, int count)
{
    RibbonPacket a, b;
    float matrix[4][4] __attribute__((aligned(16)));
    float inner[4] __attribute__((aligned(16)));
    float outer[4] __attribute__((aligned(16)));
    int i;
    int outer_color = 0x400072FF;
    unsigned long long texture_state = 0xFF9000000260ULL;
    float t, u, v;
    a.tags[1] = func_002E67A0_2(43);
    a.tags[2] = texture_state;
    a.tags[3] = ((unsigned long long)(unsigned int)width << 32) | 0x68;
    a.tags[0] = 0;
    a.color[0] = a.color[1] = 0x7F0072FF;
    b.tags[1] = func_002E67A0_2(43);
    b.tags[2] = texture_state;
    b.tags[0] = 0;
    b.tags[3] = ((unsigned long long)(unsigned int)(width / 3) << 32) | 0x68;
    b.color[0] = b.color[1] = outer_color;
    *(Rac2TI128 *)inner = 0;
    *(Rac2TI128 *)outer = 0;
    inner[3] = 1.0f;
    outer[3] = 1.0f;
    inner[2] = func_002A7878(0.005f, 0.085f) * 2.0f;
    outer[2] = func_002A7878(0.1f, 0.25f) * 2.0f;
    ref_L00_003BC468_00(points, count);
    ref_L00_003BC468_01((char *)&a);
    ref_L00_003BC468_01((char *)&b);
    a.uv[0] = 0; a.uv[1] = 0; a.uv[2] = 0; a.uv[3] = 1;
    a.uv[4] = 1; a.uv[5] = 0; a.uv[6] = 1; a.uv[7] = 1;
    b.uv[0] = 0; b.uv[1] = 0; b.uv[2] = 0; b.uv[3] = 1;
    b.uv[4] = 0.33f; b.uv[5] = 0; b.uv[6] = 0.33f; b.uv[7] = 1;
    func_802EE138_1(matrix[0], (float *)&points[1], (char *)points);
    func_802EE3D0_1(matrix[0], matrix[0], 1.0f);
    func_802EE138_1(matrix[1], (float *)D_L00_001B8DC0, (char *)points);
    func_00282DD8(matrix[2], matrix[1], matrix[0]);
    func_802EE3D0_1(matrix[2], matrix[2], 1.0f);
    func_00282DD8(matrix[1], matrix[0], matrix[2]);
    qcopy(matrix[3], points);
    qcopy(a.corner[0], inner);
    func_002EE178_1((char *)a.corner[1], (char *)a.corner[0], -1.0f);
    func_002830C0(a.corner[0], a.corner[0], matrix[0]);
    func_002830C0(a.corner[1], a.corner[1], matrix[0]);
    qcopy(b.corner[0], outer);
    func_002EE178_1((char *)b.corner[1], (char *)b.corner[0], -1.0f);
    func_002830C0(b.corner[0], b.corner[0], matrix[0]);
    func_002830C0(b.corner[1], b.corner[1], matrix[0]);
    for (i = 1; i < count - 1; i++) {
        qcopy(a.corner[2], inner);
        func_002EE178_1((char *)a.corner[3], (char *)a.corner[2], -1.0f);
        qcopy(b.corner[2], outer);
        func_002EE178_1((char *)b.corner[3], (char *)b.corner[2], -1.0f);
        func_802EE138_1(matrix[0], (float *)&points[i + 1], (char *)&points[i]);
        func_802EE3D0_1(matrix[0], matrix[0], 1.0f);
        func_802EE138_1(matrix[1], (float *)D_L00_001B8DC0, (char *)&points[i]);
        func_00282DD8(matrix[2], matrix[1], matrix[0]);
        func_802EE3D0_1(matrix[2], matrix[2], 1.0f);
        func_00282DD8(matrix[1], matrix[0], matrix[2]);
        qcopy(matrix[3], &points[i]);
        func_002830C0(a.corner[2], a.corner[2], matrix[0]);
        func_002830C0(a.corner[3], a.corner[3], matrix[0]);
        func_002830C0(b.corner[2], b.corner[2], matrix[0]);
        func_002830C0(b.corner[3], b.corner[3], matrix[0]);
        t = func_00283CE0(i);
        u = func_00283CE0(count);
        t = t / (u - 2.0f);
        a.color[2] = a.color[3] = func_00283D38(0x7F0072FF, 0x7FDDB973, t);
        b.color[2] = b.color[3] = func_00283D38(0x7F0072FF, 0x40FF0000, t);

        func_802EAC30_1((char *)&a, 0, 0);
        func_802EAC30_1((char *)&b, 0, 0);
        u = func_00283CE0(i) * 0.33f;
        v = u + 0.33f;
        if (u >= 1.0f) { u -= 1.0f; v -= 1.0f; }
        a.color[0] = a.color[1] = a.color[2];
        b.color[0] = b.color[1] = b.color[2];
        b.uv[2] = b.uv[0] = u;
        b.uv[6] = b.uv[4] = v;
        qcopy(a.corner[0], a.corner[2]);
        qcopy(a.corner[1], a.corner[3]);
        qcopy(b.corner[0], b.corner[2]);
        qcopy(b.corner[1], b.corner[3]);
    }
}

extern void func_00282D08(void *, void *, void *, float);
extern void ref_L00_003BCF88_00(Vec16_Fc936841d *, int);
extern void ref_L00_003BCF88_01(char *);
/* The same two ribbons as func_L00_003BC468, an eighth as wide, with the
   last segment's edges drawn together at their midpoint. */
void func_L00_003BCF88(int unused, int width, Vec16_Fc936841d *points, int count)
{
    RibbonPacket a, b;
    float matrix[4][4] __attribute__((aligned(16)));
    float inner[4] __attribute__((aligned(16)));
    float outer[4] __attribute__((aligned(16)));
    int i;
    int outer_color = 0x400072FF;
    unsigned long long texture_state = 0xFF9000000260ULL;
    float t, u, v;
    a.tags[1] = func_002E67A0_2(43);
    a.tags[2] = texture_state;
    a.tags[3] = ((unsigned long long)(unsigned int)width << 32) | 0x68;
    a.tags[0] = 0;
    a.color[0] = a.color[1] = 0x7F0072FF;
    b.tags[1] = func_002E67A0_2(43);
    b.tags[2] = texture_state;
    b.tags[0] = 0;
    b.tags[3] = ((unsigned long long)(unsigned int)(width / 3) << 32) | 0x68;
    b.color[0] = b.color[1] = outer_color;
    *(Rac2TI128 *)inner = 0;
    *(Rac2TI128 *)outer = 0;
    inner[3] = 1.0f;
    outer[3] = 1.0f;
    inner[2] = func_002A7878(0.005f, 0.085f) * 0.25f;
    outer[2] = func_002A7878(0.1f, 0.25f) * 0.25f;
    ref_L00_003BCF88_00(points, count);
    ref_L00_003BCF88_01((char *)&a);
    ref_L00_003BCF88_01((char *)&b);
    a.uv[0] = 0; a.uv[1] = 0; a.uv[2] = 0; a.uv[3] = 1;
    a.uv[4] = 1; a.uv[5] = 0; a.uv[6] = 1; a.uv[7] = 1;
    b.uv[0] = 0; b.uv[1] = 0; b.uv[2] = 0; b.uv[3] = 1;
    b.uv[4] = 0.33f; b.uv[5] = 0; b.uv[6] = 0.33f; b.uv[7] = 1;
    func_802EE138_1(matrix[0], (float *)&points[1], (char *)points);
    func_802EE3D0_1(matrix[0], matrix[0], 1.0f);
    func_802EE138_1(matrix[1], (float *)D_L00_001B8DC0, (char *)points);
    func_00282DD8(matrix[2], matrix[1], matrix[0]);
    func_802EE3D0_1(matrix[2], matrix[2], 1.0f);
    func_00282DD8(matrix[1], matrix[0], matrix[2]);
    qcopy(matrix[3], points);
    qcopy(a.corner[0], inner);
    func_002EE178_1((char *)a.corner[1], (char *)a.corner[0], -1.0f);
    func_002830C0(a.corner[0], a.corner[0], matrix[0]);
    func_002830C0(a.corner[1], a.corner[1], matrix[0]);
    qcopy(b.corner[0], outer);
    func_002EE178_1((char *)b.corner[1], (char *)b.corner[0], -1.0f);
    func_002830C0(b.corner[0], b.corner[0], matrix[0]);
    func_002830C0(b.corner[1], b.corner[1], matrix[0]);
    for (i = 1; i < count - 1; i++) {
        qcopy(a.corner[2], inner);
        func_002EE178_1((char *)a.corner[3], (char *)a.corner[2], -1.0f);
        qcopy(b.corner[2], outer);
        func_002EE178_1((char *)b.corner[3], (char *)b.corner[2], -1.0f);
        func_802EE138_1(matrix[0], (float *)&points[i + 1], (char *)&points[i]);
        func_802EE3D0_1(matrix[0], matrix[0], 1.0f);
        func_802EE138_1(matrix[1], (float *)D_L00_001B8DC0, (char *)&points[i]);
        func_00282DD8(matrix[2], matrix[1], matrix[0]);
        func_802EE3D0_1(matrix[2], matrix[2], 1.0f);
        func_00282DD8(matrix[1], matrix[0], matrix[2]);
        qcopy(matrix[3], &points[i]);
        func_002830C0(a.corner[2], a.corner[2], matrix[0]);
        func_002830C0(a.corner[3], a.corner[3], matrix[0]);
        func_002830C0(b.corner[2], b.corner[2], matrix[0]);
        func_002830C0(b.corner[3], b.corner[3], matrix[0]);
        t = func_00283CE0(i);
        u = func_00283CE0(count);
        t = t / (u - 2.0f);
        a.color[2] = a.color[3] = func_00283D38(0x7F0072FF, 0x7FDDB973, t);
        b.color[2] = b.color[3] = func_00283D38(0x7F0072FF, 0x40FF0000, t);
        if (i == count - 2) {
            func_00282D08(a.corner[2], a.corner[2], a.corner[3], 0.5f);
            func_00282D08(b.corner[2], b.corner[2], b.corner[3], 0.5f);
            qcopy(a.corner[3], a.corner[2]);
            qcopy(b.corner[3], b.corner[2]);
        }
        func_802EAC30_1((char *)&a, 0, 0);
        func_802EAC30_1((char *)&b, 0, 0);
        {
            float step = 0.33f;
            u = func_00283CE0(i) * step;
            v = u + step;
        }
        if (u >= 1.0f) { u -= 1.0f; v -= 1.0f; }
        a.color[0] = a.color[1] = a.color[2];
        b.color[0] = b.color[1] = b.color[2];
        b.uv[2] = b.uv[0] = u;
        b.uv[6] = b.uv[4] = v;
        qcopy(a.corner[0], a.corner[2]);
        qcopy(a.corner[1], a.corner[3]);
        qcopy(b.corner[0], b.corner[2]);
        qcopy(b.corner[1], b.corner[3]);
    }
}
