/* functional: medium (the only captured call may not reach the later half). Complete reconstruction from the near-miss draft; calls, arguments and stores follow retail, only table addressing and scheduling differ. */

typedef unsigned char u8;
extern int D_001C4FA0[];
extern char D_0014B540_1[];
extern int D_001A79F0_3 __attribute__((sda));
extern unsigned int func_00294EC8(int);
typedef struct { float x0, y0, x1, y1, u0, v0, u1, v1; } UiMapEndpoints;
typedef struct { float x_bias, x_scale, y_bias, y_scale; } UiMapCoefficients;
extern int D_00256028[][2];
extern UiMapEndpoints D_00255C30[];
extern UiMapCoefficients D_00255ED0[];
extern UiMapEndpoints D_001A93D0[];
extern UiMapCoefficients D_001A9428[];
extern unsigned char D_001A7AFD;
extern char *D_001BAED0;
extern char D_001A95A0[], D_001A95B8[];
extern unsigned char D_0018D278[];
extern void func_00295C50(int);
extern int func_002B7C80(char *, int, int);
extern int func_002EED58(int, int, int, int);
extern int func_0029D4D0(char *, char *);
/* Retail retains the allocator's source-file and line slots, although its
   release implementation consumes only the byte count. */
extern char *func_0028B2B8(int, int, const char *, int);
extern void func_00282B50(void *, void *, int);
extern void func_00297730(char *, unsigned char *, int);
extern void func_00297400(u8 *, u8 *, short *);

void func_00294F10(void)
{
    int i, j;
    int *state = D_001C4FA0;
    char *scratch, *packed;
    int bytes, size;
    state[4] = 1;
    for (i = 20; i >= 0; i--) {
        int index = 20 - i;
        state[0x108 / 4 + index] = D_00256028[index][0];
        state[0x15C / 4 + index] = D_00256028[index][1];
        ((float *)state)[0xB4 / 4 + index] = 0.65f;
    }
    state[0x238 / 4] = -1;
    func_00295C50(D_001A79F0_3);
    for (i = 20; i >= 0; i--) {
        int index = 20 - i;
        UiMapEndpoints *in = &D_00255C30[index];
        UiMapCoefficients *out = &D_00255ED0[index];
        float sx = (in->u0 - in->u1) / (in->x0 - in->x1);
        float sy = (in->v0 - in->v1) / (in->y0 - in->y1);
        out->x_scale = sx;
        out->y_scale = sy;
        out->x_bias = in->u0 - sx * in->x0;
        out->y_bias = in->v0 - sy * in->y0;
    }
    for (i = 1; i >= 0; i--) {
        int index = 1 - i;
        UiMapEndpoints *in = &D_001A93D0[index];
        UiMapCoefficients *out = &D_001A9428[index];
        float sx = (in->u0 - in->u1) / (in->x0 - in->x1);
        float sy = (in->v0 - in->v1) / (in->y0 - in->y1);
        out->x_scale = sx;
        out->x_bias = in->u0 - sx * in->x0;
        out->y_scale = sy;
        out->y_bias = in->v0 - sy * in->y0;
    }
    if (((int *)D_0014B540_1)[(0x14F4 / 4) + state[0x230 / 4] * 2] == 0 || D_001A7AFD) {
        if (((int *)D_0014B540_1)[(0x15D4 / 4) + state[0x230 / 4] * 2] == 0 || !D_001A7AFD) {
            state[0] = 0;
            state[0x28 / 4] = 0;
            state[2] = 0;
            state[3] = 0;
            state[1] = 0;
            return;
        }
    }
    state[0x28 / 4] = 1;
    if (D_001A7AFD)
        bytes = ((int *)D_0014B540_1)[0x15D4 / 4 + state[0x230 / 4] * 2];
    else
        bytes = ((int *)D_0014B540_1)[0x14F4 / 4 + state[0x230 / 4] * 2];
    bytes <<= 7;
    scratch = D_001BAED0;
    packed = scratch + 0x9A800;
    if (D_001A7AFD) {
        func_002B7C80(packed,
            ((int *)D_0014B540_1)[0x15D0 / 4 + state[0x230 / 4] * 2] + ((int *)D_0014B540_1)[0x36C / 4],
            ((int *)D_0014B540_1)[0x15D4 / 4 + state[0x230 / 4] * 2]);
        state[0x23C / 4] = 1;
    } else {
        func_002B7C80(packed,
            ((int *)D_0014B540_1)[0x14F0 / 4 + state[0x230 / 4] * 2] + ((int *)D_0014B540_1)[0x36C / 4],
            ((int *)D_0014B540_1)[0x14F4 / 4 + state[0x230 / 4] * 2]);
        state[0x23C / 4] = 0;
    }
    state[0x238 / 4] = func_002EED58((int)packed, bytes, 0x3C00, (int)D_001A95A0);
    state[0x240 / 4] = bytes;
    func_0029D4D0(packed, scratch);
    size = ((int *)scratch)[1] - ((int *)scratch)[0];
    state[0] = (int)func_0028B2B8(size, 0, D_001A95B8, 0x2EB);
    func_00282B50((void *)state[0], scratch + ((int *)scratch)[0], size);
    state[0] += 8;
    state[1] = state[0];
    size = ((int *)scratch)[2] - ((int *)scratch)[1];
    state[5] = (int)func_0028B2B8(size, 0, D_001A95B8, 0x2FC);
    func_00282B50((void *)state[5], scratch + ((int *)scratch)[1], size);
    state[2] = (int)func_0028B2B8(0x1000, 0, D_001A95B8, 0x303);
    for (i = 0; i < 8; i++) {
        state[0x30 / 4 + i * 4] = -1;
        state[0x34 / 4 + i * 4] = -1;
        state[0x38 / 4 + i * 4] = state[2] + (i << 9);
    }
    state[3] = (int)func_0028B2B8(0x8000, 0, D_001A95B8, 0x30C);
    if (func_00294EC8(state[0x230 / 4]))
        func_00297730((char *)state[3], D_0018D278 + (state[0x230 / 4] << 11), state[5]);
    else
        func_00297400((u8 *)state[3], (u8 *)state[0], (short *)state[1]);
    for (i = 0; i < 32; i++) {
        float dy = 15.5f - (float)i;
        float dy2 = dy * dy;
        for (j = 0; j < 32; j++) {
            float dx = 15.5f - (float)j;
            if (dy2 + dx * dx > 256.0f)
                ((u8 *)state)[0x1B0 + i * 4 + j / 8] |= 1 << (j % 8);
        }
    }
}
