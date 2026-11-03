/* functional: high. Plain floats in place of VU0 code, in its order (a*(1-t) accumulated, then b*t added); the index word is read as its low 32 bits where retail loads the 64-bit word at +0x38 and uses only bits 0-23. vitof12 of frac*16 is frac*16/4096. */
extern char D_001C2740[];

/* Colour of a blended light pair: obj+0x38 holds two 64-byte D_001C2740 entry indices (bytes 0, 1) and a blend byte (byte 2).
   Blend 0 copies entry a's quadword at +0x10 whole; otherwise out.xyz = a*(1-t) + b*t with t = blend/256, out.w = a.w. */
void func_002A04E8(void *obj, void *out)
{
    unsigned int k = *(unsigned int *)((char *)obj + 0x38);
    unsigned int ia = k & 0xFF;
    unsigned int ib = (k >> 8) & 0xFF;
    unsigned int f = (k >> 16) & 0xFF;
    float *a = (float *)(D_001C2740 + ia * 64 + 16);
    float *d = out;

    if (f == 0) {
        unsigned int *s = (unsigned int *)a, *o = out;
        o[0] = s[0];
        o[1] = s[1];
        o[2] = s[2];
        o[3] = s[3];
    } else {
        float *b = (float *)(D_001C2740 + ib * 64 + 16);
        float t = (float)(int)(f << 4) * (1.0f / 4096.0f);
        float u = 1.0f - t;
        unsigned int w = ((unsigned int *)a)[3];
        float r[3];
        int i;

        for (i = 0; i < 3; i++) {
            float acc = a[i] * u;
            r[i] = acc + b[i] * t;
        }
        d[0] = r[0];
        d[1] = r[1];
        d[2] = r[2];
        ((unsigned int *)out)[3] = w;
    }
}
