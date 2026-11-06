/* func_PAL_L00_00390F48, the PAL copy of func_L00_0038DE70: the same C, where rename func_00308600 becomes func_PAL_003098C8; expr 0.016666668f becomes 0.020000001f; expr 0.16666667f becomes 0.20000002f; rename func_002A7878_1 becomes func_002A7878. */

typedef int V1306TI __attribute__((mode(TI)));
typedef union { V1306TI q; float f[4]; } V1306Vec;
typedef struct { int entry[6]; } V1306Table;
typedef struct { V1306TI q[5]; } __attribute__((aligned(16))) V1306Packet;
typedef struct { char pad[4]; unsigned char flag; char mid[107]; float f70; char tail[108]; } V1306Material;
extern unsigned char D_00139568[];
extern V1306Material D_L00_00262570[];
extern V1306Packet D_L00_002A26A0;
extern V1306Table D_L00_001AEFE0, D_L00_001AEFF8;
extern char D_L00_001B8DC0[], D_L00_001C3280[];
typedef struct { char pad[0x160]; float amount; int unused, duration, state; } V1439Camera;
extern V1439Camera D_L00_001B8C80;
extern float func_00283CE0(int);
extern void func_00282D30(char *, char *, float);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern float func_00282DB0(char *, char *);
extern void func_00282FB8(char *, char *, float);
extern int func_00277F48(char *, int, char *, int, float);
extern void func_002A9850(char *, char *, char *, int, int, int, int, int, float, float, float);
extern int func_002A7820(int, int);
extern char *func_PAL_003098C8(char *, char *, int, int, int);
extern int func_00283CF0(float);
extern int func_002AAFA0(int, int);
extern char *func_002BBCB0(char *, char *, int, int, float, int, int, float, int, int);
extern char *func_L00_003A0DA0(char *, char *, char *, int, int, int, int, int, float);
extern void func_002AAF40(int *, int *, int *, int);
extern int func_002E5CF8(int, int, char *);
extern char *func_00312B70(void *, char *, int, void *);
static inline V1306Material *V1306Current(void) { return (V1306Material *)(D_00139568[12] * 224 + (int)D_L00_00262570); }
#define V1306_FLAG (V1306Current()->flag != 0)

extern int func_002A77E0(int mode);

extern float func_002A7878(float low, float high);

/* Measured partial layouts; original type and game roles are unknown. */
#ifndef RAC2_T_WORKER_F9E2CD219
#define RAC2_T_WORKER_F9E2CD219
#endif

#ifndef RAC2_T_OWNER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219
#endif

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_4ecc6b5a4034_u8;

typedef unsigned int QwenRecovery_4ecc6b5a4034_u32;

/* Minimum external views; neither declaration allocates original game storage. */
typedef struct {
    QwenRecovery_4ecc6b5a4034_u8 prefix[0x24];
    QwenRecovery_4ecc6b5a4034_u32 word;
    QwenRecovery_4ecc6b5a4034_u8 tail[8];
} QwenRecovery_4ecc6b5a4034_ExtraResetRecord164;

extern QwenRecovery_4ecc6b5a4034_ExtraResetRecord164 D_L00_002372C0[100];

extern QwenRecovery_4ecc6b5a4034_u32 D_L00_00238580[139];

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_03c444112283bc5f_u32;

extern Rac2Native_03c444112283bc5f_u32 D_L00_00238DF0[139];

/* Level object-update walk: one pass over the object list the game exposes at
 * D_L00_001B1EA8, with a per-class dispatch. */
typedef unsigned char L00_0037F7E8_u8;
typedef unsigned int L00_0037F7E8_u32;

/* The empty method this call reaches sits in a different copy in each level
 * (the catalogue splits the identical bodies), so the callee takes a ref_ name:
 * its value is read from the retail bytes at every place. */
extern L00_0037F7E8_u8 *func_002A08A0(void);

extern L00_0037F7E8_u8 *D_L00_001B1EA8 __attribute__((sda));

extern L00_0037F7E8_u32 D_001A7424 __attribute__((sda));

/* Measured partial layout; original type and game roles are unknown. */
/* The level's own data: each place resolves its own value from the retail
 * bytes. The two adjacent flags stay one array so both sites keep the retail's
 * in-place absolute load, which the sda attribute selects. */
extern L00_0037F7E8_u8 ref_L00_001B267C_00[] __attribute__((sda));

/* func_L00_0037FA90 is defined in L00_0037FA90-qcopy.c. */

typedef struct {
    char *entry[64][4];
    int count;
    int best;
} L00_0037FE08_Pool;

extern L00_0037FE08_Pool D_L00_00231540;

/* Keep the pool entry nearest to the fixed origin: the count is re-read every
 * pass, so the loop bound stays live in memory. */
/* 16-slot object table searched for the first entry the name resolver accepts.
 * The `sda` attribute (SYMBOL_REF_FLAG) suppresses gcc's HIGH/LO_SUM split: its
 * `lui`/`addiu` pair is one RTL insn, so the address stays in the single
 * callee-saved register that retail uses instead of taking an extra one. */
/* func_L00_003825C8 is defined in L00_003825C8.c. */

/* func_L00_00382910 is defined in L00_00382910.c. */

/* func_L00_00382F28 is defined in L00_0037E898-g8.c. */

/* func_L00_00384248 is defined in L00_0037E898-trail-g8.c. */

/* func_L00_00384678 is defined in L00_00384678-g8.c. */

/* func_L00_00384C20 is matched in L00_00384C20.c (built with -fno-strength-reduce). */

/* func_L00_00384CA8 is defined in L00_00384CA8-qcopy.c. */

/* func_L00_00387370 is defined in L00_00387370-g8-qcopy.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
/* Update the owner vector using the two bound vector helpers, refresh the three saved source coordinates, and conditionally set the measured owner byte to 7; original game role is unknown. */
/* Shared native body; original game role is unknown. */
/* Clear the selected word in 100 records, reset 136 state words, and set the three trailing state words. */
/* shared native body of family a04928c6 */
/* func_L00_00388490 is defined in L00_00388490.c. */

/* func_L00_00388790 is defined in L00_00388790-qcopy.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
/* Update the owner vector using the two bound vector helpers, refresh the three saved source coordinates, and conditionally set the measured owner byte to 7; original game role is unknown. */
/* Shared native body; original game role is unknown. */
/* Reset two 64-word banks, eight trailing words, and three state words. The original game role is unknown. */
/* shared native body of family a04928c6 */
/* func_L00_0038AAD0 is defined in L00_0038AAD0.c. */

extern void *D_L00_001BF218;

extern void *ref_L00_0038B848_00(void *arg);

extern void *D_L00_001BF218;

extern void *ref_L00_0038B848_00(void *arg);

/* Measured partial layouts; the original types and game roles are unknown. */
typedef struct {
    unsigned char pad[0x2290];
    int value;
} D_00189E20_Struct;

extern D_00189E20_Struct D_00189E20;

/* Walk the level's node list from D_L00_001B1EA8: each node's own measure is
 * compared with the limit (2.7, or 10.0 when D_001A7B2A is set); a node of kind
 * 0x13 is then handed to func_003022A0, any other node to its own handler. A mode
 * of 0xFE or 0xFD, or a null next pointer, ends the walk. */
extern float func_00282DF0(char *object);

extern void func_00282F20(char *object, char *other, float value);

/* Fold an angle into the measured 1.8325959 ceiling, ease the remaining gap and
 * hand the result to the setter. */
/* Dispatches on a byte mode at object+32: mode 0 updates two float angles from a linked node and runs a follow-up call; mode 1 refreshes a 16-byte block and a node copy then calls a final update. */
void func_PAL_L00_00390F48(char *object, char *direction, char *axis)
{
    V1306Packet packet;
    V1306Vec delta, temp, vector, random;
    V1306Table first, second;
    int red, green, blue, red2, green2, blue2;
    int *child;
    int i, n, counter, asset1, asset2, life1, life2;
    float scale, length, twice, speed, force;
    packet = D_L00_002A26A0;
    child = *(int **)(object + 0x68);
    scale = func_00283CE0(V1306_FLAG) + 1.0f;
    func_00282D30(direction, direction, scale);
    func_00282CF0((char *)&delta, D_L00_001B8DC0, object + 0x10);
    length = func_00282DF0((char *)&delta);
    i = func_00277F48(object + 0x10, 16, object, 0, scale * 0.5f);
    vector.q = *(V1306TI *)(object + 0x10);
    func_002A9850(object, (char *)&vector, D_L00_001C3280, i, 0, 0x830000, 2, 1,
        V1306Current()->f70, 1.0f, 1.0f);
    object[0x20] = 1;
    for (counter = 0; counter < 10; counter++) {
        random.q = 0;
        random.f[0] = func_002A7878(-1.0f, 1.0f);
        random.f[1] = func_002A7878(-1.0f, 1.0f);
        vector.q = random.q;
        func_00282F20((char *)&temp, axis, func_00282DB0((char *)&vector, axis));
        func_00282CF0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&temp, axis, func_002A7878(0.0f, 1.0f));
        func_00282CC0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&vector, (char *)&vector, scale * func_002A7878(3.5f, 6.5f) * (0.020000001f));
        func_00282CC0((char *)&vector, (char *)&vector, direction);
        life1 = func_002A7820(50,100);
        func_PAL_003098C8(object+0x10, (char *)&vector, life1, 0, V1306_FLAG);
    }
    twice = length + length;
    for (n = 0; n < 4; n++) {
        random.q = 0;
        random.f[0] = func_002A7878(-1.0f, 1.0f);
        random.f[1] = func_002A7878(-1.0f, 1.0f);
        vector.q = random.q;
        func_00282F20((char *)&temp, axis, func_00282DB0((char *)&vector, axis));
        func_00282CF0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&temp, axis, func_002A7878(0.0f, 1.0f));
        func_00282CC0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&vector, (char *)&vector, scale * func_002A7878(6.5f, 10.0f) * (0.020000001f));
        func_00282CC0((char *)&vector, (char *)&vector, direction);
        life1 = func_002A7820(50,75);
        func_PAL_003098C8(object+0x10, (char *)&vector, life1, 1, V1306_FLAG);
    }
    random.q = 0;
    random.f[0] = func_002A7878(-1.0f, 1.0f);
    random.f[1] = func_002A7878(-1.0f, 1.0f);
    random.f[2] = func_002A7878(-1.0f, 1.0f);
    vector.q = random.q;
    delta.f[2] += length * 0.5f;
    func_00282F20((char *)&vector, (char *)&vector, length * 0.004f);
    func_00282F20((char *)&delta, (char *)&delta, twice * (0.020000001f));
    func_00282CC0((char *)&vector, (char *)&vector, (char *)&delta);
    func_00282FB8((char *)&vector, (char *)&vector, 0.20000002f);
    life1 = func_002A7820(50,75);
    func_PAL_003098C8(object+0x10, (char *)&vector, life1, 1, V1306_FLAG);
    if (length < 6.0f) i = func_00283CF0(length) + 1;
    else i = 4;
    twice = 0.0f;
    if (length < 7.0f) twice = 7.0f - length;
    for (n = 0; n < i; n++) {
        float step = 0.020000001f;
        float limit = 400000.0f;
        force = scale;
        speed = scale * func_002A7878(8.0f, 10.0f);
        force *= limit;
        first = D_L00_001AEFE0;
        second = D_L00_001AEFF8;
        speed *= step;
        speed -= twice * step;
        asset1 = func_002AAFA0(first.entry[func_002A77E0(6)], V1306_FLAG);
        asset2 = func_002AAFA0(second.entry[func_002A77E0(6)], V1306_FLAG);
        life1 = func_002A7820(12,17);
        life2 = func_002A7820(21,25);
        func_002BBCB0(object+0x10, direction, asset1, asset2, force, life1, life2, speed, 0, 0);
    }
    if (length > 9.0f) {
        float size = scale * 4.0f;
        func_L00_003A0DA0(object,object+0x10,direction,12,127,127,127,32,size);
        red=127; green=32; blue=0;
        func_002AAF40(&red,&green,&blue,V1306_FLAG);
        func_L00_003A0DA0(object,object+0x10,direction,20,(unsigned char)red,(unsigned char)green,(unsigned char)blue,32,size);
    }
    red2=127; green2=63; blue2=0;
    func_002AAF40(&red2,&green2,&blue2,V1306_FLAG);
    func_L00_003A0DA0(object,object+0x10,direction,17,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,48,scale*4.0f);
    red2=96; green2=16; blue2=0;
    func_002AAF40(&red2,&green2,&blue2,V1306_FLAG);
    func_L00_003A0DA0(object,object+0x10,direction,22,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,64,scale*3.5f);
    red2=32; green2=0; blue2=0;
    func_002AAF40(&red2,&green2,&blue2,V1306_FLAG);
    func_L00_003A0DA0(object,object+0x10,direction,24,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,32,scale*3.0f);
    *child = 0;
    object[0xBC] = 0;
    if (V1306_FLAG) func_002E5CF8(0,0,object);
    else func_002E5CF8(0,0,object);
    { V1439Camera *camera = &D_L00_001B8C80;
    if (length < 20.0f) camera->amount = 0.4f - length * 0.0175f;
    else camera->amount = 0.050000011920928955f;
    }
    D_L00_001B8C80.duration=21;
    D_L00_001B8C80.state=0;
    func_00312B70(&packet,object+0x10,0,0);
}

