#include "include_asm.h"
#include "names.h"

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_00beefd949f6_AbiByte15;

typedef unsigned long long QwenRecovery_00beefd949f6_AbiFlag15;

extern void func_002AFFD8(QwenRecovery_00beefd949f6_AbiByte15 *input, float *output, QwenRecovery_00beefd949f6_AbiFlag15 mode);

extern void func_002AFFD8_1(void *a, void *b, int c);

extern void func_00282F20_14(float f, void *a, void *b);

extern void func_00282CC0_35(char *target, char *first, char *local);

extern int D_L00_001A8FF0_3 __attribute__((sda));

extern int D_L00_001A8FF4 __attribute__((sda));

extern char D_L00_001B1B10[] __attribute__((sda));

extern char D_L00_001A9000[] __attribute__((sda));

extern float func_00282E48_1(char *a, char *b);

extern void func_00282F20(void *, void *, float);

extern void func_00282DD8_2(void *, void *, void *);

extern void func_00282D30_12(void *, void *, float);

extern float func_00282DF0_1(void *);

extern float func_00282C10(float);

extern void func_00283958(void *, void *);

extern void func_00283738(void *, void *, void *);

extern void func_00282AB0_1(void *, void *, int);

extern float func_00283CE0_2(int);

extern float func_002A7940_1(void);

extern float func_002A7878_3(float, float);

extern float func_00283180_2(float);

extern float func_00283198_4(float);

extern void func_00283098_3(float *dst, float *src, char *table);

extern void func_00282CC0_11(float *dst, float *src, float *arg);

extern int D_L00_001A8FF0_1 __attribute__((sda));

extern void func_00273730(char *self, int a1, int a2, int a3, char *p4, char *p5,
                    float *buf, int b3, float fa, float fb);

typedef int s32;

typedef unsigned char u8;

extern u8 D_00139648;

extern unsigned char D_19B278[];

extern int F9a90bcc4_FUN_002A77E0(int count);

/* Finds which way gravity pulls at an object's position and stores that direction. */
void func_002B00B0(QwenRecovery_00beefd949f6_AbiByte15 *object, float *direction, QwenRecovery_00beefd949f6_AbiFlag15 mode)
{
    ComputeViewDirection(object + 0x10, direction, mode);
    return;
}


/* If the linked global word is zero, stores (second_float_field - f) into the first object's float field; otherwise runs a three-call path over a 16-byte local buffer. */
/* Moves a position by a distance along the local gravity direction, or straight down when gravity is flat. */
void func_002B00D8(void *position, float *result, float *base, float distance)
{
    float gravityDir[4];

    if (D_L00_001A8FF0_3 == 0) {
        result[2] = base[2] - distance;
    } else {
        func_002AFFD8_1(position, gravityDir, 0);
        func_00282F20_14(distance, gravityDir, gravityDir);
        func_00282CC0_35((char *)result, (char *)base, (char *)gravityDir);
    }
}

/* Same as the position version, but starts from an object's own position. */
void func_002B0158(char *object, float *result, float *base, float distance) {
    OffsetPositionAlongGravity(object + 0x10, result, base, distance);
}

/* func_002B0178 is defined in 002B0178.c. */


/* Returns a scaled length when a global flag is set, otherwise refreshes a bound data object and forwards the raw helper result. */
/* Gives how far a position is from the gravity centre, flipped around 100 when the other mode is on. */
float func_002B0360(char *position)
{
    float height;

    if (D_L00_001A8FF4 == 0) {
        height = func_00282E48_1(position, D_L00_001B1B10);
    } else {
        height = 100.0f - func_00282E48_1(position, D_L00_001A9000);
    }
    return height;
}

extern void func_00282D30(void *, void *, float);
extern void func_002B0408(void *, void *, void *);

/* Turns a rotation so that it lines up with the opposite of the given direction. */
void func_002B03B8(void *rotation, void *direction, void *outMatrix) {
    float negated[4];
    FastVecScale(negated, direction, -1.0f);
    AlignRotationToDirection(rotation, negated, outMatrix);
}

/* Builds a 4-float value from a unit seed and a 0.5f-scaled blend against a region 32 bytes into the first argument, squares a scalar returned by a fourth callee, stores the negated complement of that square into a fifth word, converts the value into a 48-byte record and copies that record into the third argument when it is non-null. */
/* Turns a rotation so that its up axis lines up with the given direction. */
void func_002B0408(void *rotation, void *direction, void *outMatrix)
{
    float basis[12];
    float axis[4];
    float seed[4];
    float dot;

    vec_scale_to_length(seed, direction, 1.0f);
    func_00282DD8_2(axis, seed, (char *)rotation + 32);
    func_00282D30_12(axis, axis, 0.5f);
    dot = func_00282DF0_1(axis);
    axis[3] = -square_root(1.0f - dot * dot);
    quaternion_to_rotation_basis(axis, basis);
    multiply_matrix3x3(rotation, basis, rotation);
    if (outMatrix != 0)
        func_00282AB0_1(outMatrix, basis, 48);
}


extern void func_002AFDD8(char *a0, char *a1, char *a2, char *a3);
extern float func_00283248(float a, float b);

typedef int V4_002B04E0 __attribute__((mode(TI)));

/* Works out the heading angle of a vector as seen from an object. */
float func_002B04E0(char *object, float *vector, char *extra)
{
    float localVec[4];

    *(V4_002B04E0 *)localVec = *(V4_002B04E0 *)vector;
    TransformVectorByObjectOrGiven(object, (char *)localVec, (char *)localVec, extra);
    return FastMatrixHelperA(localVec[0], localVec[1]);
}



/* func_002B0668 is defined in 002B00B0-effect-g8.c. */


/* Calls one float-conversion helper on (a0 %% a1) and again on a1, then returns 2*pi times the quotient minus pi. */
/* Turns a step number out of a total into an evenly spaced angle between minus pi and pi. */
float func_002B08A8(int index, int count)
{
    float part = func_00283CE0_2(index % count);
    float whole = func_00283CE0_2(count);

    return 2.0f * part * 3.1415927f / whole - 3.1415927f;
}

extern float func_002B08A8(int, int);
extern float func_00283198(float);
extern void func_00283D38(int, int, float);
/* Fades between two colours using a smooth wave that follows the step number. */
void func_002B0910(int index, int count, int colorA, int colorB)
{
    float phase = GetEvenlySpacedAngle(index, count);
    phase = FastSinOrCosB(phase);
    FastTweenColor(colorA, colorB, phase * 0.5f + 0.5f);
}


extern u8 D_001A7A47 __attribute__((sda));
extern void func_002AEC48(void *a0, void *a1, int a2, float f12, float f13);

/* Stores the third argument (or 1.0f) in the object's float at 0x70, and, when the fifth argument
   is set and that float differs from the one at 0x20, calls func_002AEC48 with the object's two
   first arguments, the fourth argument and the pair 0.03f, 0.3f. */
/* Sets a value on an object and, if asked, starts a short smooth change when it differs from the old value. */
void func_002B0990(void *owner, float *state, float value, int param, int startChange)
{
    if (D_001A7A47 != 0) {
        state[28] = value;
    } else {
        state[28] = 1.0f;
    }
    if (startChange != 0) {
        if (state[28] != state[8]) {
            UpdateEasedNode(owner, state, param, 0.03f, 0.3f);
        }
    }
}

/* Looks up an entry by index and passes it on with one more value. */
void func_002B0A18(int first, int second)
{
    extern int func_00288FB8(int);
    extern void func_0029CC98(int, int);
    func_0029CC98(GetLocalizedString(first), second);
}

extern void func_0029CC50(int, int, int);

/* Passes three values on to another routine. */
void func_002B0A48(int first, int second, int third) {
    func_0029CC50(first, second, third);
}

/* Walks selected mask bits, evaluates three stored curve components, optionally transforms the vector, and dispatches one object operation per selected bit. */
/* Throws out small pieces in random directions for each selected part of an object. */
void func_002B0A68(char *moby, int partMask, float *baseVelocity,
                                        unsigned char flags,
                                        float speedMinXY, float speedMaxXY, float speedMinZ, float speedMaxZ)
{
    /* Vector primitives read/write all 16 bytes; retail initializes only xyz. */
    float velocity[4] __attribute__((aligned(16)));
    float angle;
    float speed;
    float randomA;
    float randomB;
    int i;

    for (i = 0; i < 15; i++) {
        if (((partMask >> i) ^ 1) & 1)
            continue;
        angle = func_002A7940_1();
        speed = func_002A7878_3(speedMinXY, speedMaxXY) * (1.0f / 60.0f);
        velocity[0] = func_00283180_2(angle) * speed;
        velocity[1] = func_00283198_4(angle) * speed;
        velocity[2] = 0.0f;
        velocity[2] = func_002A7878_3(speedMinZ, speedMaxZ) * (1.0f / 60.0f);
        if (D_L00_001A8FF0_1 != 0)
            func_00283098_3(velocity, velocity, moby + 192);
        func_00282CC0_11(velocity, velocity, baseVelocity);
        randomA = func_002A7878_3(90.0f, 270.0f);
        randomB = func_002A7878_3(10.0f, 20.0f);
        CreateCameraMoby(moby, 2, *(short *)(moby + 170), i, moby + 16, moby + 240,
                velocity, flags, randomA, randomB);
    }
}


/* Returns a saved count byte used as a starting value. */
s32 func_002B0D60(void) { return D_00139648; }

extern int func_002B0DB8(void);

/* Counts the filled slots in a 28 by 4 table, keeping the result between 0 and 40. */
int func_002B0DB8(void)
{
    int filled = 0;
    int i;

    for (i = 0; i < 0x1C; i++) {
        int j;

        for (j = 0; j < 4; j++) {
            if (D_19B278[i * 4 + j] != 0)
                filled++;
        }
    }
    if (filled < 0)
        filled = 0;
    if (filled > 0x28)
        filled = 0x28;
    return filled;
}

extern u8 D_00139568[];
extern u8 D_00239BA0[];

/* Counts the entries of a 56-byte table whose scaled entry in a second table is at least 2, and
   clamps the count to 0..20. */
int func_002B0E28(void)
{
    int count = 0;
    int i;

    for (i = 0; i < 56; i++) {
        u8 v = gItemSlotToRecord[i];
        u8 *p = gWeaponTable_00239BA0 + v * 224;
        int x = p[4];

        if (x >= 2) {
            count++;
        }
    }
    if (count < 0) {
        count = 0;
    }
    if (count > 20) {
        count = 20;
    }
    return count;
}

extern u8 D_001A7A60[] __attribute__((sda));

/* Counts the non-zero bytes of a 32-byte table, and clamps the count to 0..30. */
int func_002B0E90(void)
{
    int count = 0;
    int i;

    for (i = 0; i < 32; i++) {
        if (D_001A7A60[i] != 0) {
            count++;
        }
    }
    if (count < 0) {
        count = 0;
    }
    if (count > 30) {
        count = 30;
    }
    return count;
}

/* func_002B1350 is defined in 002B00B0-reaction-g8.c. */

/* Picks a random entry of the given kind from an owner's list and gives back its scaled values. */
int func_002B1A80(u8 *owner, int kind, int *outIndex,
                                       float *outA, float *outB, float *outC, float *outD,
                                       float *outE, float *outF, float *outG)
{
    int matches;
    int count;
    int i;
    int pick;
    int remaining;
    u8 *entry;

    matches = 0;
    count = *(u8 *)(*(int *)(owner + 36) + 12);
    if (count != 0) {
        int *slot = (int *)(*(int *)(owner + 36) + 72);
        u8 *info;
        remaining = count;
        do {
            info = *(u8 **)(*slot + 20);
            if (info != 0 && *info == kind)
                matches++;
            slot++;
            remaining--;
        } while (remaining != 0);
    }

    if (matches != 0)
        goto second;

    return 0;

found:
    *outA = *(float *)(entry + 8) * 0.016666668f;
    *outB = *(float *)(entry + 12) * 0.016666668f;
    *outC = *(float *)(entry + 16) * 0.00027777778f;
    *outD = *(float *)(entry + 20) * 0.00027777778f;
    *outG = *(float *)(entry + 4) * 0.00027777778f;
    *outE = *(float *)(entry + 24);
    *outF = *(float *)(entry + 28);
    *outIndex = i;
    return 1;

second:
    pick = F9a90bcc4_FUN_002A77E0(matches);
    for (i = 0; i < *(u8 *)(*(int *)(owner + 36) + 12); i++) {
        char *table = (char *)(*(int *)(owner + 36) + 72);
        char *slotEntry = *(char **)(table + i * 4);
        entry = *(u8 **)(slotEntry + 20);
        if (entry == 0 || *entry != kind)
            continue;
        if (pick == 0)
            goto found;
        pick--;
    }
    return 0;
}
