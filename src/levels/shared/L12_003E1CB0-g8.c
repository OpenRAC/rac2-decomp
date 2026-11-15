#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u16 D_L12_001B0B0C __attribute__((sda));

/* Sets the object's byte at +0x95 to 9 and copies a level-wide halfword into its private data. */
void func_L12_003E2448(u8 *moby) {
    *(u8 *)(moby + 0x95) = 9;
    *(u16 *)(*(u32 *)(moby + 0x68) + 0x29E) = D_L12_001B0B0C;
}

extern float func_00283B98(float, float);

extern float func_00283198(float);

extern int func_00283D38(int, int, float);

extern void func_0029FC20(char *, int, void *);

extern void func_L00_002E6CF0(void *, void *);

extern void func_L12_004281D8(u8 *);

/* The entity base and the frame counter are read bare (`lui`/`lw` in one register: `sda` sized
   over 8 bytes in a -G8 unit); the group count is a $gp scalar and the group table an ordinary
   array. The frame counter is read twice, once as the compare and once as the store: the array declaration gives
   the bare form for both, and a scalar declaration under the same assembler name for the compare
   lets cc1 keep retail's order of its load and of the member load before it (with the array
   element cc1 loads the member first). The pair at D_L12_001B21D0 is copied as one 8-byte
   block (`ldl`/`ldr`/`sdl`/`sdr`). */
extern unsigned short *D_L12_001FB960[];
extern int D_L12_001B2EB8 __attribute__((sda));
extern u8 *D_L12_001B2E9C[3] __attribute__((sda));
extern int D_L12_001B29C8[3] __attribute__((sda));
extern int D_L12_001B29C8_s __asm__("D_L12_001B29C8") __attribute__((sda));

struct L12PairWord {
    int a;
    int b;
};

extern struct L12PairWord D_L12_001B21D0 __attribute__((nosda));

/* The kind's private block at +0x68 of the object and of each entity. */
struct L12Kind348 {
    char pad[0x348];
    float f348;
    float f34C;
    int f350;
};

struct L12Kind348Entity {
    char pad0[0x20];
    u8 state;
    char pad1[0x10];
    u8 f31;
    char pad2[0x36];
    struct L12Kind348 *obj;
    char pad3[0x3E];
    short type;
};

struct L12Kind348Object {
    char pad0[0x21];
    u8 group;
    char pad1[0x46];
    struct L12Kind348 *obj;
    char pad2[0x0C];
    int f78;
};

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L12_001B29C8 differs from the object's word at +0x350, walks the object's group
   and refreshes every live entity of kind 0x11EB, then registers func_L12_004281D8. */
void func_L12_00428040(struct L12Kind348Object *moby) {
    struct L12Kind348 *vars = moby->obj;
    struct L12PairWord colorPair = D_L12_001B21D0;
    float wave;
    unsigned short *groupEntry;
    struct L12Kind348Entity *entity;
    struct L12Kind348 *entityVars;

    wave = FastAddRotations(vars->f348, 0.2094395458f);
    vars->f348 = wave;
    wave = FastSinOrCosB(wave);
    vars->f34C = wave * 0.5f + 0.5f;
    moby->f78 = FastTweenColor(colorPair.a, colorPair.b, vars->f34C);
    if (vars->f350 != D_L12_001B29C8_s) {
        for (groupEntry = D_L12_001FB960[moby->group];
             moby->group != 0xFF && moby->group <= D_L12_001B2EB8 && groupEntry != 0 &&
             ((groupEntry != 0 && (short)groupEntry[-1] >= 0) || groupEntry == D_L12_001FB960[moby->group]);
             groupEntry++) {
            entity = (struct L12Kind348Entity *)(D_L12_001B2E9C[0] + ((*groupEntry & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (entity->f31 != 0 && entity->type == 0x11EB && entity->state != 0xFE && entity->state != 0xFD) {
                entityVars = entity->obj;
                TransformMobyJointPoint((char *)entity, 0, (char *)entityVars + 0x240);
                entityVars->f350 = D_L12_001B29C8[0];
            }
        }
        AddDrawCallbackToList1((void *)DrawGroupEntityGlows, moby);
    }
}

extern void func_00282D30(void *dst, void *src, float value);

extern void func_002830C0(void *, void *, void *);

extern void func_L00_00325AE8(void *, int, float, float);

/* Here the group count is read bare, so it takes a second name sized over 8 bytes (its .extern
   re-sizes the symbol after func_L12_00428040's $gp reads). The vector's address is $gp-relative.
   The colour pair is one plain 8-byte object, read as two members: cc1 counts `lw $4,D` (a small
   symbol) as one instruction, but `lw $5,D+4` as two (mips.c's simple_memory_operand has no case
   for a symbol plus an offset), so the delay-slot filler passes over the second argument's load
   and takes the first's. In the slot the assembler gives that load the $gp form; outside it,
   with a plain declaration's .extern only at the end of the file, `lw $5,D+4` becomes retail's
   `lui $a1` / `lw $a1`. With `sda` both words come through $gp (380 bytes); as two separate
   words each load is one instruction and the second argument's takes the slot. */
extern int D_L12_001B2EB8_a[3] __asm__("D_L12_001B2EB8") __attribute__((sda));
extern char D_L12_001B21E0[8] __attribute__((sda));
extern struct L12PairWord D_L12_001B21F0;

/* Turns the entities of the object's group that are kind 0x11EB and in use (flag byte at +0x31
   set, state byte at +0x20 not 0xFE or 0xFD): the vector at D_L12_001B21E0 is turned by the
   angle at +0x344 of the entity's private block and then by its matrix at +0x240, the colour
   pair at D_L12_001B21F0 is mixed by the fraction at +0x34C, and both go to func_L00_00325AE8. */
void func_L12_004281D8(u8 *moby) {
    u16 *q;
    u16 *p;
    u8 *e;
    u8 *priv;
    float buf[4];
    int r;

    if (moby[0x21] == 0xFF)
        return;
    q = D_L12_001FB960[moby[0x21]];
    if (q == 0)
        return;
    for (p = q; moby[0x21] != 0xFF && moby[0x21] <= D_L12_001B2EB8_a[0] && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L12_001FB960[moby[0x21]]);
         p++) {
        e = D_L12_001B2E9C[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x31] != 0 && *(s16 *)(e + 0xAA) == 0x11EB /* moby class 4587 */ && e[0x20] != 0xFE && e[0x20] != 0xFD) {
            priv = *(u8 **)(e + 0x68);
            FastVecScale(buf, D_L12_001B21E0, *(float *)(priv + 0x344));
            transform_vector(buf, buf, priv + 0x240);
            r = FastTweenColor(D_L12_001B21F0.a, D_L12_001B21F0.b, *(float *)(priv + 0x34C));
            DrawBillboardQuad_L00(buf, r, *(float *)(priv + 0x344) * 0.2f, 0.08f);
        }
    }
}

extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void ref_L12_00429D60_00(void *, int, float, int, float, float, int, int, void *);
extern float D_L12_001B2328 __attribute__((sda));
extern float D_L12_001B232C __attribute__((sda));
extern int D_L12_001B2320 __attribute__((sda));
extern int D_L12_001B2324 __attribute__((sda));
extern int D_L12_001B22E4 __attribute__((sda));
extern int D_L12_001B22E8 __attribute__((sda));

/* Draws two glow effects at the object's position, each with a random brightness and its own scale and colour. */
void func_L12_00429D60(char *object) {
    int flareAlpha;
    int flareAlpha2;
    float scale;
    float scale2;
    float random;
    scale = D_L12_001B2328;
    scale *= *(float *)(object + 0x2C);
    flareAlpha = RandomIntRange(95, 111);
    random = RandomAngle();
    ref_L12_00429D60_00(object + 0x10, D_L12_001B22E4, scale, flareAlpha, random, 1.0f, D_L12_001B2320, 2, object);
    scale2 = D_L12_001B2328;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= D_L12_001B232C;
    flareAlpha2 = RandomIntRange(111, 127);
    random = RandomAngle();
    ref_L12_00429D60_00(object + 0x10, D_L12_001B22E8, scale2, flareAlpha2, random, 1.0f, D_L12_001B2324, 2, object);
}
