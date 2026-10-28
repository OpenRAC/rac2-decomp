/* functional: medium. Decoded from the assembly: a 43-point fan is transformed (or eased from its previous frame's points by the G2/60 ratio), then 38 four-vertex quads are copied from the point tables into one packet and sent to func_00280B90. Same calls, arguments and order as retail; locals and loops are clearer. Helper names are the catalogue's; their float/vector roles are guessed from use. */
typedef struct { float x, y, z, w; } V4;
typedef struct {
    V4 pos[4];
    unsigned int col[4];
    float uv[4][2];
    long long q70, q78, q80, q88;
} Pkt;

extern long func_0027C878(int);
extern void func_0029FC20(void *, int, float *, unsigned int);
extern float func_00282C48(float);
extern float func_00282C10(float);
extern float func_00283CE0(int);
extern void func_00282948(int *);
extern void func_002830C0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern void func_00282F20(float, float *, float *);
extern float func_00282DB0(float *, float *);
extern void func_00282D30(float, float *, float *);
extern void func_00280B90(Pkt *, int, int);

extern int D_001A8BB0;
extern float D_001B5200[];
extern short D_00152C20;
extern float D_001B5340[];
extern float D_002620A0[];
extern float D_002625B0[];
extern float D_00214CE0[];
extern float D_00214E38[];
extern float D_00214A30[];
extern short D_00262350[];
extern int D_001ABF00 __attribute__((sda));
extern int D_001ABF04 __attribute__((sda));
extern int D_001ABF08 __attribute__((sda));

void func_002ECB70(float *obj)
{
    Pkt pkt;
    float mtx[16];
    float v1[4], v0[4], v2[4];
    float *mtxp;
    long ret;
    unsigned int col;
    int s2 = 0;
    int i, j;

    ret = func_0027C878(0x15);
    col = (D_001A8BB0 == 2) ? 0x28A5A281u : 0x3CA5A281u;
    pkt.q88 = 0x8000000044LL;
    pkt.q80 = 0xFF9000000260LL;
    pkt.q78 = ret;
    pkt.q70 = 0;
    pkt.col[0] = col;
    pkt.col[1] = col;
    pkt.col[2] = col;
    pkt.col[3] = col;
    func_0029FC20(obj, 0, mtx, col);

    if (D_001A8BB0 == 0 || D_001A8BB0 == 2) {
        if (func_00282C48(D_001B5200[0x140 / 4] - obj[4]) < 16.0f) {
            if (func_00282C48(D_001B5200[0x144 / 4] - obj[5]) < 16.0f)
                s2 = 1;
        }
    } else {
        s2 = 1;
    }
    if (D_001A8BB0 == 6 && D_00152C20 == 2)
        s2 = 0;

    if (s2 == 0 && D_001ABF00 != 1) {
        if (D_001ABF04 == 1) {
            D_001ABF04 = 0;
            for (i = 0; i < 43; i++) {
                D_00214E38[i * 2] = D_00214CE0[i * 2];
                D_00214E38[i * 2 + 1] = D_00214CE0[i * 2 + 1];
                func_002830C0(D_00214A30 + i * 4, D_002620A0 + i * 4, mtx);
            }
        } else {
            for (i = 0; i < 43; i++)
                func_002830C0(D_00214A30 + i * 4, D_002620A0 + i * 4, mtx);
        }
        D_001ABF08 = 0x3C;
    } else {
        float t;

        mtxp = mtx;
        D_001ABF04 = 1;
        func_00282948(&D_001ABF08);
        t = func_00283CE0(D_001ABF08);
        t = t / func_00283CE0(0x3C);
        for (i = 0; i < 43; i++) {
            float d, r, f4, x, y;

            func_002830C0(D_00214A30 + i * 4, D_002620A0 + i * 4, mtxp);
            func_00282CF0(v2, D_00214A30 + i * 4, D_001B5340);
            func_00282F20(1.0f, v2, v2);
            func_002830C0(v1, D_002625B0 + i * 4, mtxp);
            func_00282F20(0.1f, v1, v1);
            d = func_00282DB0(v1, v2);
            func_00282D30(d + d, v0, v1);
            func_00282CF0(v0, v2, v0);
            func_00282F20(1.0f, v0, v0);
            v0[2] = v0[2] + 1.0f;
            r = func_00282C10(v0[2] + v0[2]);
            f4 = r + r;
            x = v0[0] / f4 + 0.5f;
            y = v0[1] / f4 + 0.5f;
            if (D_001ABF00 == 1 || D_001ABF08 == 0) {
                D_00214CE0[i * 2] = x;
                D_00214CE0[i * 2 + 1] = y;
            } else {
                D_00214CE0[i * 2] = x + (D_00214E38[i * 2] - x) * t;
                D_00214CE0[i * 2 + 1] = y + (D_00214E38[i * 2 + 1] - y) * t;
            }
        }
        if (D_001ABF00 == 1)
            D_001ABF00 = 2;
    }

    for (i = 0; i < 38; i++) {
        for (j = 0; j < 4; j++) {
            int idx = D_00262350[i * 8 + j * 2];

            pkt.pos[j] = *(V4 *)(D_00214A30 + idx * 4);
            pkt.uv[j][0] = D_00214CE0[idx * 2];
            pkt.uv[j][1] = D_00214CE0[idx * 2 + 1];
        }
        func_00280B90(&pkt, 0, 0);
    }
}
