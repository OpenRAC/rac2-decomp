#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
extern float D_L00_0024F7C0[4][32];
extern float D_L00_0029AE20[5][4];
extern float D_L00_001B2B80[4] MACRO_ADDR;
extern float D_L00_001B06DC __attribute__((sda));
extern float D_L00_001B06E0 __attribute__((sda));
extern float D_L00_001B06C4 __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_L00_003E9660(int, float *, int);
extern void func_002A3F10(void *, int, int *, void *);
extern float func_00283198(float), func_00283180(float), func_00283B98(float, float);
extern void func_002830C0(void *, void *, void *);
extern void func_L00_003EA0E0(char *, int, char *, char *);
extern void func_L00_003E9B00(int, int, int, int, float);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern void func_L00_003E9780(void *, void *, void *, void *);
extern void func_L00_003E9930(char *, void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_001163B0(void);
extern void func_L00_003EA188(void *, int, float);
extern void func_0029FCC0(char *, int, char *);

/* Transform the weapon's animated attachment points and draw its beam network. */
void func_L00_003E8A98(void *object)
{
    float points[5][4], attachments[5][4], matrix[4][4];
    float normal[4], side[4], endpoint[4], muzzle[4];
    char *moby = object;
    char *state;
    int lookup, i;
    float *first;
    func_002FC560(0x47, 0x53001ULL);
    state = *(char **)(moby + 0x68);
    func_L00_003E9660((int)moby, D_L00_0024F7C0[0], 4);
    lookup = 0;
    func_002A3F10(moby, 1, &lookup, matrix);
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    D_L00_0029AE20[1][0] = -func_00283180(D_L00_001B06E0) * 0.0151f;
    D_L00_0029AE20[1][2] = func_00283180(D_L00_001B06DC) * 0.0149f;
    D_L00_0029AE20[1][1] = -(func_00283198(D_L00_001B06DC) * 0.015f + 0.4f);
    D_L00_001B06DC = func_00283B98(D_L00_001B06DC, 0.4188790917f);
    D_L00_001B06E0 = func_00283B98(D_L00_001B06E0, 0.4130613208f);
    {
        float *src = D_L00_0029AE20[0], *dst;
        first = attachments[0];
        dst = first;
        for (i = 0; i < 5; i++) {
            func_002830C0(dst, src, matrix);
            src += 4;
            dst += 4;
        }
    }
    func_L00_003EA0E0(moby, 0, (char *)points[0], (char *)first);
    func_L00_003E9B00((int)moby, (int)points[0], 0x7F7F2020, 0x40, 0.11f);
    func_L00_003E9B00((int)moby, (int)points[0], 0x7FFF4040, 0x78, 0.05f);
    func_L00_003EA0E0(moby, 0, (char *)points[1], (char *)attachments[1]);
    if (D_L00_001B2B80[3] == -1.0f) {
        qcopy(D_L00_001B2B80, points[1]);
        D_L00_001B2B80[3] = 0.0f;
    } else {
        int changed = 0;
        func_002AA458(D_L00_001B2B80, points[1], &changed, 0.25f, 0.2000000179f, 0.5f);
    }
    func_L00_003E9B00((int)moby, (int)D_L00_001B2B80, 0x7F00397F, 0x40, 2.0f * *(float *)(state + 0x10) * 0.082499996f);
    func_L00_003E9B00((int)moby, (int)D_L00_001B2B80, 0x7F0072FF, 0x78, 2.0f * *(float *)(state + 0x10) * 0.0375f);
    func_L00_003EA0E0(moby, 1, (char *)points[2], (char *)attachments[2]);
    func_L00_003E9B00((int)moby, (int)points[2], 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)points[2], 0x7FFF4040, 0x78, 0.025f);
    func_L00_003EA0E0(moby, 2, (char *)points[3], (char *)attachments[3]);
    func_L00_003E9B00((int)moby, (int)points[3], 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)points[3], 0x7FFF4040, 0x78, 0.025f);
    func_L00_003EA0E0(moby, 3, (char *)points[4], (char *)attachments[4]);
    func_L00_003E9B00((int)moby, (int)points[4], 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)points[4], 0x7FFF4040, 0x78, 0.025f);
    func_L00_003E9780(moby, points[0], D_L00_001B2B80, D_L00_0024F7C0[0]);
    func_L00_003E9930(moby, D_L00_001B2B80, normal, *(float *)(state + 0x10) * 0.35f);
    func_00282CF0(side, D_L00_001B2B80, points[2]);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, *(float *)(state + 0x10) * 0.45f);
    func_00282CC0(endpoint, side, D_L00_001B2B80);
    func_L00_003E9780(moby, points[2], endpoint, D_L00_0024F7C0[1]);
    func_L00_003E9B00((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0x10) > D_L00_001B06C4)
        func_L00_003EA188(endpoint, 1, 0.0f);
    func_00282CF0(side, D_L00_001B2B80, points[3]);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, *(float *)(state + 0x10) * 0.45f);
    func_00282CC0(endpoint, side, D_L00_001B2B80);
    func_L00_003E9780(moby, points[3], endpoint, D_L00_0024F7C0[2]);
    func_L00_003E9B00((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0x10) > D_L00_001B06C4)
        func_L00_003EA188(endpoint, 1, 0.0f);
    func_00282CF0(side, D_L00_001B2B80, points[4]);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, *(float *)(state + 0x10) * 0.45f);
    func_00282CC0(endpoint, side, D_L00_001B2B80);
    func_L00_003E9780(moby, points[4], endpoint, D_L00_0024F7C0[3]);
    func_L00_003E9B00((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0x10) > D_L00_001B06C4)
        func_L00_003EA188(endpoint, 1, 0.0f);
    func_0029FCC0(moby, 1, (char *)muzzle);
    func_L00_003E9780(moby, muzzle, points[2], D_L00_0024F7C0[3]);
    func_L00_003E9B00((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    func_0029FCC0(moby, 2, (char *)muzzle);
    func_L00_003E9780(moby, muzzle, points[3], D_L00_0024F7C0[2]);
    func_L00_003E9B00((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    func_0029FCC0(moby, 3, (char *)muzzle);
    func_L00_003E9780(moby, muzzle, points[4], D_L00_0024F7C0[1]);
    func_L00_003E9B00((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003E9B00((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0) {
        int selected = func_001163B0();
        selected %= 4;
        func_L00_003EA188(points[selected + 1], 1, 0.001f);
    }
    func_002FC560(0x47, 0x5360BULL);
}
