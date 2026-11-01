/* functional: medium. Plain C written from the assembly. The packet area handed to func_00280B90 is a 144-byte stack block laid out as retail's (header in its last 32 bytes). Read from the assembly only; the meaning of the table fields is inferred. */
extern unsigned char D_00189E20[];
extern unsigned char D_L00_00290C78[];
extern int D_L00_001B19C8;
extern int D_L00_001B2740;
extern float D_L00_001AEFD8;
extern long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

/* Advances the effect record the object points to (at +104): a time at +112 counted up by the frame step times the entry's rate, restarted or cleared by the state of the hero's target (unsigned bytes at +66 and +67 of the object at hero + 0x2290); entries of 96 bytes at D_L00_00290C78 picked by that state (23, 24, 25 or 43). While running it copies the target's matrix into the record and emits the entry's quads through func_00280B90. */
void func_L00_0038B208(void *object)
{
    char *eff = *(char **)((char *)object + 104);
    char *target;
    float t, end;
    unsigned char state;
    int sel, index, size, mode, delta, count, i, k;
    int e[4];
    float shade, scale;
    unsigned int base_colour;
    char *entry;
    union {
        float f[36];
        long q[18];
    } blk;

    if (eff == 0) {
        return;
    }
    t = *(float *)(eff + 112);
    if (t == 0.0f) {
        return;
    }
    if (t == 1.0f) {
        target = *(char **)(D_00189E20 + 0x2290);
        state = (unsigned char)target[66];
        if (state != (unsigned char)target[67]) {
            *(float *)(eff + 112) = 0.0f;
            return;
        }
        if (state == 255) {
            *(float *)(eff + 112) = 0.0f;
            return;
        }
    }
    shade = 1.0f;
    scale = 1.0f;
    size = 20;
    mode = 1;
    base_colour = 0x808080;
    target = *(char **)(D_00189E20 + 0x2290);
    state = (unsigned char)target[66];
    if ((unsigned int)(state - 23) < 3 || state == 43) {
        target = *(char **)(D_00189E20 + 0x2290);
        sel = (unsigned char)target[66];
    } else {
        sel = *(short *)(eff + 120);
    }
    if (sel == 23) {
        *(short *)(eff + 120) = (short)sel;
        index = 0;
    } else if (sel == 24) {
        *(short *)(eff + 120) = (short)sel;
        index = 1;
    } else if (sel == 25) {
        *(short *)(eff + 120) = (short)sel;
        index = 2;
    } else {
        *(short *)(eff + 120) = 43;
        base_colour = 0x408080;
        shade = 0.7f;
        scale = 1.25f;
        size = 12;
        index = 3;
        mode = 2;
    }
    entry = (char *)D_L00_00290C78 + index * 96;
    t = *(float *)(eff + 112);
    for (i = 0; i < 4; i++) {
        e[i] = *(short *)(entry + 2 * i);
    }
    if (t == 1.0f) {
        char *src = *(char **)(D_00189E20 + 0x2290);

        ((unsigned int *)eff)[0] = ((unsigned int *)(src + 192))[0];
        ((unsigned int *)eff)[1] = ((unsigned int *)(src + 192))[1];
        ((unsigned int *)eff)[2] = ((unsigned int *)(src + 192))[2];
        ((unsigned int *)eff)[3] = ((unsigned int *)(src + 192))[3];
        ((unsigned int *)eff)[4] = ((unsigned int *)(src + 208))[0];
        ((unsigned int *)eff)[5] = ((unsigned int *)(src + 208))[1];
        ((unsigned int *)eff)[6] = ((unsigned int *)(src + 208))[2];
        ((unsigned int *)eff)[7] = ((unsigned int *)(src + 208))[3];
        ((unsigned int *)eff)[8] = ((unsigned int *)(src + 224))[0];
        ((unsigned int *)eff)[9] = ((unsigned int *)(src + 224))[1];
        ((unsigned int *)eff)[10] = ((unsigned int *)(src + 224))[2];
        ((unsigned int *)eff)[11] = ((unsigned int *)(src + 224))[3];
        D_L00_001B2740 = D_L00_001B19C8;
    }
    delta = D_L00_001B19C8 - D_L00_001B2740;
    if (!(delta > 0)) {
        delta = 1;
    }
    t = t + (float)delta * *(float *)(entry + 72);
    *(float *)(eff + 112) = t;
    D_L00_001B2740 = D_L00_001B19C8;
    end = (float)(*(short *)(entry + 88) << 1);
    if (end <= t) {
        target = *(char **)(D_00189E20 + 0x2290);
        state = (unsigned char)target[66];
        if ((unsigned int)(state - 23) < 3) {
            return;
        }
        if (state != 43) {
            *(int *)(eff + 112) = 0;
        }
        return;
    }
    blk.q[14] = 5;
    blk.q[15] = func_0027C878(size);
    blk.q[16] = ((long)0xFF90 << 32) | 0x260;
    blk.q[17] = ((long)mode << 2) | ((long)0x8000 << 24) | 0x40;
    {
        char *src = *(char **)(D_00189E20 + 0x2290);

        ((unsigned int *)(eff + 48))[0] = ((unsigned int *)(src + 16))[0];
        ((unsigned int *)(eff + 48))[1] = ((unsigned int *)(src + 16))[1];
        ((unsigned int *)(eff + 48))[2] = ((unsigned int *)(src + 16))[2];
        ((unsigned int *)(eff + 48))[3] = ((unsigned int *)(src + 16))[3];
    }
    count = *(short *)(entry + 88);
    if (count <= 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        for (k = 0; k < 4; k++) {
            unsigned int *colour = (unsigned int *)&blk.f[16 + k];
            char *list = *(char **)(entry + 80);
            int s8 = *(short *)(list + i * 16 + k * 4);
            float u, v;

            if (i == e[0]) {
                *colour = *(unsigned int *)(entry + k * 4 + 8);
            } else if (i == e[1]) {
                *colour = *(unsigned int *)(entry + k * 4 + 24);
            } else if (i == e[2]) {
                *colour = *(unsigned int *)(entry + k * 4 + 40);
            } else if (i == e[3]) {
                *colour = *(unsigned int *)(entry + k * 4 + 56);
            } else {
                *colour = 0x50808080;
            }
            *colour = ((unsigned int)func_00283CF0((float)((signed char *)colour)[3] * shade) << 24) | base_colour;
            func_00282D30(&blk.f[4 * k], *(char **)(entry + 76) + s8 * 16, scale);
            {
                char *list2 = *(char **)(entry + 80);
                float *uv = (float *)(*(char **)(entry + 84) + *(short *)(list2 + i * 16 + k * 4 + 2) * 8);
                float lag = 1.0f - *(float *)(eff + 112) * *(float *)(entry + 92);

                u = (uv[0] - 0.5f) * D_L00_001AEFD8 + 0.5f;
                v = (uv[1] - 0.5f) * D_L00_001AEFD8 + 0.5f;
                v = v + lag;
                blk.f[20 + 2 * k] = u;
                blk.f[21 + 2 * k] = v;
            }
        }
        func_00280B90(blk.f, eff, 0);
    }
}
