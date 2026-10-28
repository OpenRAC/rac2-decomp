/* functional: medium. Menu list update: sets the visibility of the seven sub-widgets from the mode flag at +0x44C, positions five widgets from a constant table plus the origin at +0x434, lays out the item rows, then moves the selection on the pad's up/down bits (skipping empty entries), highlights it and returns the selected index. Field names are unknown; stores, calls and branches follow retail. */
typedef unsigned char u8;

extern float D_001AE5EC;
extern float D_001AE760[10];

extern void func_00335E68(u8 *w, int on);
extern void func_003363C0(u8 *w, float f);
extern float *func_00335E10(u8 *w);
extern unsigned int *func_00335E20(u8 *w);
extern void func_00335F88(u8 *w, float f);
extern void func_002E5E58(int a, int b, int c);
extern void func_002A9588(int a, int b, int c, int d, int e);

int func_003489E8(u8 *m, int pad)
{
    u8 *w98 = m + 0x98;
    u8 *w4C = m + 0x4C;
    u8 *w130 = m + 0x130;
    u8 *w17C = m + 0x17C;
    u8 *w1C8 = m + 0x1C8;
    u8 *wE4 = m + 0xE4;
    u8 *a, *b, *c, *d;
    float f;
    int pressed, step, i, n, idx, v, start, lim;
    float *p;
    float **org = (float **)(m + 0x434);

    func_00335E68(m, *(int *)(m + 0x44C) == 0);
    func_00335E68(w98, *(int *)(m + 0x44C) == 0);
    func_00335E68(w4C, *(int *)(m + 0x44C) == 0);
    func_00335E68(wE4, *(int *)(m + 0x44C) == 0);
    func_00335E68(w130, *(int *)(m + 0x44C) == 0);
    func_00335E68(w17C, (*(int *)(m + 0x44C) ^ 1) == 0);
    func_00335E68(w1C8, (*(int *)(m + 0x44C) ^ 1) == 0);
    func_003363C0(w17C, D_001AE5EC);
    func_003363C0(w1C8, D_001AE5EC);

    if (*(int *)(m + 0x44C) == 0 && *(int *)(m + 0x448) != 0) {
        f = 1.0f;
        func_003363C0(m, f);
        func_003363C0(w98, f);
        func_003363C0(w4C, f);
        func_003363C0(w130, f);
        (*org)[1] = 170.0f;
    } else {
        f = 0.0f;
        func_003363C0(m, f);
        func_003363C0(w98, f);
        func_003363C0(w4C, f);
        func_003363C0(w130, f);
        (*org)[1] = 190.0f;
    }

    a = w130; b = w4C; c = w98; d = wE4;
    pressed = pad & 0x1000;

    p = func_00335E10(m);
    p[0] = D_001AE760[0] + (*org)[0];
    p[1] = D_001AE760[1] + (*org)[1];
    p = func_00335E10(a);
    p[0] = D_001AE760[2] + (*org)[0];
    p[1] = D_001AE760[3] + (*org)[1];
    p = func_00335E10(b);
    p[0] = D_001AE760[4] + (*org)[0];
    p[1] = D_001AE760[5] + (*org)[1];
    p = func_00335E10(c);
    p[0] = D_001AE760[6] + (*org)[0];
    p[1] = D_001AE760[7] + (*org)[1];
    p = func_00335E10(d);
    p[0] = D_001AE760[8] + (*org)[0];
    p[1] = D_001AE760[9] + (*org)[1];

    n = *(int *)(m + 0x444);
    for (i = 0; i < *(int *)(m + 0x444); i++) {
        u8 *row = m + 0x218 + i * 0x48;
        float *src;
        p = func_00335E10(row);
        src = (float *)(*(int *)(m + 0x414) + i * 12);
        p[0] = src[0] + (*org)[0];
        src = (float *)(*(int *)(m + 0x414) + i * 12);
        p[1] = src[1] + (*org)[1];
        func_00335F88(row, ((float *)(*(int *)(m + 0x414) + i * 12))[2]);
        if (*(int *)(m + 0x418 + i * 4) != 0)
            *func_00335E20(row) = 0x80F0F0F0;
        else
            *func_00335E20(row) = 0x80808080;
    }

    step = 0;
    if (pressed) {
        func_002E5E58(3, 0, 0);
        step = -1;
    } else if (pad & 0x4000) {
        func_002E5E58(3, 0, 0);
        step = 1;
    }
    if (step != 0) {
        start = *(int *)(m + 0x43C);
        func_002A9588(0, 0, 1, 0, 1);
        lim = n - 1;
        do {
            v = *(int *)(m + 0x43C) + step;
            if (lim < v)
                v = 0;
            idx = (v > -1) ? v : lim;
            *(int *)(m + 0x43C) = idx;
            if (*(int *)(m + 0x418 + idx * 4) != 0)
                break;
        } while (start != idx);
    }
    func_003363C0(wE4, (float)*(int *)(m + 0x43C));
    *func_00335E20(m + *(int *)(m + 0x43C) * 0x48 + 0x218) = 0x70FFFEED;
    return *(int *)(m + 0x43C);
}
