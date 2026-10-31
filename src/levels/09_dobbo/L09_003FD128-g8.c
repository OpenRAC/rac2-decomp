/* Adapted from OpenRAC rac1-decomp, GPL-3.0, heavy_interceptor_and_turrets.c,
 * Revision a23a07114bae7547adffb442b0f23fc295a48238,
 * draw_blarg_heavy_interceptor_light_ring. The four-row frame, 82 XYZ
 * vertices, 84 colors and temporary vector agree with the measured RAC2
 * frame; source tables retain incomplete outer extents.
 */
#include "common.h"
extern void func_L09_003FCF68(char *);
extern char D_L09_001B9A00[];
extern int D_L09_001B11D8 __attribute__((sda));
extern float D_L09_002A1FF0[][3];
extern u32 D_L09_002A2658[];
extern char D_L09_002A23C8[];
extern u64 func_0027C878(int);
extern void func_002FC560(int,u64);
extern void func_00280328(void);
extern void func_00281810(int,void *,void *,void *,int);
extern void func_00282CF0(void *,void *,void *), func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float), func_00282D30(void *,void *,float);
extern void func_002830C0(void *,void *,void *);

void func_L09_003FD128(char *moby) {
    char *d = *(char **)(moby + 0x68);
    struct {
        float mat[4][4]; /* camera-facing frame */
        float verts[82][3]; /* ring vertices transformed by mat */
    } f;
    u32 cols[84];
    float v[4];
    int i;
    int j;

    func_L09_003FCF68(moby);
    qcopy(f.mat[0], d + 0x340);
    func_00282CF0(f.mat[2], d + 0x370, D_L09_001B9A00);
    func_00282DD8(f.mat[1], f.mat[0], f.mat[2]);
    func_00282F20(f.mat[1], f.mat[1], 1.0f);
    func_00282DD8(f.mat[2], f.mat[1], f.mat[0]);
    qcopy(f.mat[3], d + 0x370);
    f.mat[3][3] = 1.0f;
    func_002FC560(6, func_0027C878(0x16));
    func_002FC560(0x42, 0x8000000048);
    func_002FC560(8, 5);
    func_002FC560(0x14, 0xFF9000000260);
    func_002FC560(0x47, 0x51001);
    func_002FC560(0x4A, 0);
    func_00280328();
    for (i = 0; i < D_L09_001B11D8; i++) {
        float *s = D_L09_002A1FF0[i];
        float *o = f.verts[i];
        v[0] = s[0];
        v[1] = s[1];
        v[2] = s[2];
        v[3] = 1.0f;
        func_002830C0(v, v, f.mat);
        o[0] = v[0];
        o[1] = v[1];
        o[2] = v[2];
        if (*(short *)(d + 0x422) != 0) {
            cols[i] = D_L09_002A2658[i] & 0xFF0000FF;
        }
    }
    if (*(short *)(d + 0x422) != 0) {
        func_00281810(D_L09_001B11D8, f.verts, cols, D_L09_002A23C8, 1);
    } else {
        func_00281810(D_L09_001B11D8, f.verts, D_L09_002A2658, D_L09_002A23C8, 1);
    }
    func_00282D30(f.mat[1], f.mat[1], -1.0f);
    func_00282D30(f.mat[2], f.mat[2], -1.0f);
    for (j = 0; j < D_L09_001B11D8; j++) {
        float *o = f.verts[j];
        float *s = D_L09_002A1FF0[j];
        v[0] = s[0];
        v[1] = s[1];
        v[2] = s[2];
        v[3] = 1.0f;
        func_002830C0(v, v, f.mat);
        o[0] = v[0];
        o[1] = v[1];
        o[2] = v[2];
    }
    if (*(short *)(d + 0x422) != 0) {
        func_00281810(D_L09_001B11D8, f.verts, cols, D_L09_002A23C8, 1);
    } else {
        func_00281810(D_L09_001B11D8, f.verts, D_L09_002A2658, D_L09_002A23C8, 1);
    }
}
