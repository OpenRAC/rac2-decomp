/* func_002E7338 - 568 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft is 560 B vs 568 (2 instructions). Whole body matches except one
   thing:
   - retail hoists the constant 0x2058B0 (lui 0x20 / ori 0x58B0) after the
   `blez count` guard and spills it to 0xA8($sp), reloading it (lw
   v1,0xA8($sp)) in the loop for `or s4,s0<<24,v1`; the matrix pointer is then
   at 0xAC($sp). Mine builds the constant inside the loop, matrix ptr at 0xA8.
   - retail uv copy loop uses two separate walking pointers (v0=&uv[0],
   v1=&uv[1]) plus gp ptr a1 and lui ptr a2 loaded early; mine uses one with
   offset 4.
   Tried: constant as local at function top (hoists before the call, wrong),
   color local per outer iteration, ascending vs descending inner loop
   (ascending is right: compiler reverses it), separate loop counter for uv
   loop (right: a0).
   Struct Draw2E7338 {verts[4][16]; colors[4]; uv[8]; u64 head[4]} passed
   whole to func_00280B90. */

/* append to src/game/002E7018-g8.c */
extern float ref_L00_002E7338_00 __attribute__((sda));
extern int ref_L00_002E7338_01 __attribute__((sda));
extern int *ref_L00_002E7338_02 __attribute__((sda));
extern unsigned char ref_L00_002E7338_03 __attribute__((sda));
extern float ref_L00_002E7338_04[];
extern unsigned int D_001A7AF0;

extern unsigned long long func_0027C878(int);
extern void func_00282D30(unsigned char *, unsigned char *, float);
extern void func_00282CC0(unsigned char *, unsigned char *, unsigned char *);
extern void func_00283098(unsigned char *, unsigned char *, unsigned char *);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern void func_00280B90(unsigned char *, int, int);

typedef struct {
    unsigned char verts[4][16];
    int colors[4];
    float uv[8];
    unsigned long long head[4];
} Draw2E7338;

void func_002E7338(unsigned char *object)
{
    Draw2E7338 d;
    unsigned char matrix[16];
    int *table = (&ref_L00_002E7338_02)[(D_001A7AF0 >> 4) & 1];
    int count = (&ref_L00_002E7338_01)[(D_001A7AF0 >> 4) & 1];
    int i;
    int j;
    int k;

    d.head[1] = func_0027C878(5);
    d.head[2] = 0xFF9000000260ULL;
    d.head[3] = 0x8000000048ULL;
    d.head[0] = 0;
    for (k = 0; k < 4; k++) {
        d.uv[k * 2] = (&ref_L00_002E7338_00)[k * 2];
        d.uv[k * 2 + 1] = ref_L00_002E7338_04[k * 2];
    }
    func_00282D30(matrix, object, 0.0009765625f);
    for (i = 0; i < count; i++) {
        int shade = *(short *)(object + 0xB2);
        int s = object[0xBC];
        float f;
        int color;

        if (shade != 0)
            s += func_002A77E0(shade);
        f = func_00283CE0(s) * 0.025f * *(float *)((unsigned char *)table + i * 16 + 0xC);
        color = (s << 24) | 0x2058B0;
        for (j = 0; j < 4; j++) {
            d.colors[j] = color;
            func_00282D30(d.verts[j], &ref_L00_002E7338_03 + j * 16, f);
            func_00282CC0(d.verts[j], d.verts[j], (unsigned char *)table + i * 16);
            func_00283098(d.verts[j], d.verts[j], object + 0xC0);
            func_00282CC0(d.verts[j], d.verts[j], matrix);
        }
        func_00280B90((unsigned char *)&d, 0, 0);
    }
}
