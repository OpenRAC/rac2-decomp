/*
 * func_L20_0039BEC8 -- non-matching draft
 * Tier: Claude Opus 5.5, xhigh effort, task v2204 (opus-1).
 * Target file: src/levels/20_yeedil/L20_002DEBE0-g8.c (-G8), replacing
 *   INCLUDE_ASM("asm/levels", func_L20_0039BEC8);
 * Best check.py: "20_yeedil: instruction at +0x8c differs" /
 *   "func_L20_0039BEC8: 0 of 1 places match"; 1252/1252 bytes.
 * What differs (all else, incl. prologue, loop-1 allocation and the four
 *   D_L20_001AECD8 colour loads, matches apart from relocations):
 *   - PRE spill-slot order of the hoisted sp+X addresses (0x148..0x168).
 *     Retail order normal,color,rotated,uv.x,uv.y,rotated+12,obj+0x10,dir,
 *     tangent is reproduced by the gcse hash model only with a 129-bucket
 *     expression table (ours: 135, i.e. ~12 fewer insns at gcse time) and
 *     an obj+0x10 base pseudo numbered 113..127 (ours: reg 85), so the
 *     original probably spells the post-loop-1 part differently (inline
 *     helper taking the object pointer?).
 *   - third loop: retail loads width into $f0 then neg.s $f12,$f0; ours
 *     loads into $f12 (preference through the neg). Shared outer `width`
 *     changes nothing.
 * Needs from the g8 file: u32/u64, qcopy, SDATA/NOT_SDA, and the existing
 *   externs func_002A7878(float,float) and func_002A7940(void).
 * FastTweenColor (func_00283D38) prototype (int from, int to, float t) is
 *   what fixes loop-1 s6/s7/fp; D_L20_001AECD8 as incomplete sda array
 *   (indices 1..3 become unsplit CONST lui/lw loads) plus a SDATA view
 *   for index 0 reproduces the colour-argument loads.
 */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { float x, y; } Pair;
typedef struct { Vec position[4]; u32 color[4]; Pair uv[4]; u64 descriptor[4]; } TrailPacket;
extern int D_L20_001AEC6C __attribute__((sda)), D_L20_001AECA0 __attribute__((sda));
extern u32 D_L20_001AEC70[2] __attribute__((sda)), D_L20_001AECA8[2] __attribute__((sda));
extern float D_L20_001AEC84[] __attribute__((sda)) NOT_SDA, D_L20_001AECBC[] __attribute__((sda)) NOT_SDA;
extern Pair D_L20_001AEC80_gp[4] SDATA(D_L20_001AEC80) __attribute__((sda));
extern Pair D_L20_001AECB8_gp[4] SDATA(D_L20_001AECB8) __attribute__((sda));
extern float D_L20_001AEC78 __attribute__((sda)), D_L20_001AEC7C __attribute__((sda)), D_L20_001AECB4 __attribute__((sda));
extern u32 D_L20_001AECD8_gp SDATA(D_L20_001AECD8) __attribute__((sda));
extern u32 D_L20_001AECD8[] __attribute__((sda));
extern float D_L20_001AECE8 __attribute__((sda)), D_L20_001AECEC;
extern float D_L20_001B9FC0[4];
extern void func_00283658(void *,void *);
extern u64 func_0027C878(int);
extern int func_00283D38(int, int, float);
extern void func_00282C90(void *);
extern void func_002833F0(void *,void *);
extern void func_L01_002E1510(void *,int,void *,int,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AFDD8(char *,char *,char *,char *);
extern void func_00282F20(void *,void *,float);
extern void func_00280B90(void *,void *,int);
extern void func_00281EB8(void *,int,u32,int,float,float,float);



void func_L20_0039BEC8(void *arg)
{
    char *object = arg;
    TrailPacket packet;
    float matrix[16], rotated[16];
    Vec direction, tangent, normal;
    float *vars = *(float **)(object + 0x68);

    u32 color;
    func_00283658(matrix, object + 0xc0);
    qcopy(matrix + 12, object + 0x10);
    packet.descriptor[1] = func_0027C878(D_L20_001AEC6C);
    packet.descriptor[0] = 0;
    packet.descriptor[2] = 0xff9000000260ULL;
    packet.descriptor[3] = 0x8000000048ULL;
    {
        int i;
        for (i = 0; i < 4; i++) {
            u32 color;
            packet.uv[i].x = D_L20_001AEC80_gp[i].x;
            packet.uv[i].y = D_L20_001AEC84[i * 2];
            color = D_L20_001AEC70[(i & 1) ? 0 : 1];
            packet.color[i] = color;
            packet.color[i] = func_00283D38(color & 0xffffff, color, vars[0]);
            func_00282C90(&packet.position[i]);
            packet.position[i].f[0] = D_L20_001AEC7C;
            if ((i & 1) == 0) packet.position[i].f[2] = D_L20_001AEC78;
            else packet.position[i].f[2] = 0.0f;
        }
    }
    *(Quad *)(rotated + 12) = 0;
    rotated[14] = 0.19634954631328583f;
    func_002833F0(rotated, rotated + 12);
    func_L01_002E1510(&packet, 1, rotated, 32, matrix);
    func_00282CF0(&direction, D_L20_001B9FC0, object + 0x10);
    func_002AFDD8(object, (char *)&direction, (char *)&direction, 0);
    normal.q = 0;
    normal.f[0] = direction.f[1];
    normal.f[1] = -direction.f[0];
    normal.f[3] = 1.0f;
    tangent.q = normal.q;
    direction.f[2] = 0.0f;
    packet.descriptor[1] = func_0027C878(D_L20_001AECA0);
    {
        int i;
        for (i = 0; i < 4; i++) {
            u32 color;
            float width;
            packet.uv[i].x = D_L20_001AECB8_gp[i].x + vars[3];
            packet.uv[i].y = D_L20_001AECBC[i * 2];
            color = D_L20_001AECA8[(i & 1) ? 0 : 1];
            packet.color[i] = color;
            packet.color[i] = func_00283D38(color & 0xffffff, color, vars[0]);
            width = i > 1 ? D_L20_001AECB4 : D_L20_001AEC7C;
            func_00282F20(&packet.position[i], &tangent, width);
            if ((i & 1) == 0) packet.position[i].f[2] = D_L20_001AEC78;
            else packet.position[i].f[2] = 0.0f;
        }
    }
    func_00280B90(&packet, matrix, 0);
    {
        int i;
        for (i = 0; i < 4; i++) {
            float width = i > 1 ? D_L20_001AECB4 : D_L20_001AEC7C;
            func_00282F20(&packet.position[i], &tangent, -width);
            if ((i & 1) == 0) packet.position[i].f[2] = D_L20_001AEC78;
            else packet.position[i].f[2] = 0.0f;
        }
    }
    func_00280B90(&packet, matrix, 0);
    qcopy(&normal, object + 0x10);
    normal.f[2] += 0.333f;
    color = func_00283D38(D_L20_001AECD8_gp, D_L20_001AECD8[1], func_002A7878(0.0f,1.0f));
    color = func_00283D38(color & 0xffffff, color, vars[0]);
    func_00281EB8(&normal, 11, color, 1, D_L20_001AECE8, 0.0f, func_002A7940());
    color = func_00283D38(D_L20_001AECD8[2], D_L20_001AECD8[3], func_002A7878(0.0f,1.0f));
    color = func_00283D38(color & 0xffffff, color, vars[0]);
    func_00281EB8(&normal, 11, color, 1, D_L20_001AECEC, 0.0f, func_002A7940());
    func_00281EB8(object + 0x10, 49, color, 1, D_L20_001AECEC, 0.0f, func_002A7940());
}
