#include "common.h"

extern void func_002829A8(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern char *func_002BDCE8(float, void *, float, float, int, void *, float, unsigned int, int);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
typedef struct { char prefix[0xD4]; unsigned char *material; } SceneMaterialPrefix;
extern SceneMaterialPrefix D_L00_001FE940;

extern float func_00283B98_2(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

extern int func_002A7820_2(int, int);

extern float func_002A7878_5(float, float);

extern float func_002A7940_2(void);

extern void func_00281EB8(char *, int, int, int, float, float, float);

extern void func_002A3F10(char *p, int one, int *w, char *out);

extern void func_00282D30_3(char *a, char *out, float f);

extern void func_00282CC0_4(char *a, char *b, char *c);

extern void func_00283098_2(char *a, char *b, char *c);

extern char D_L00_001A8F20[] __attribute__((sda));

extern void func_0029FCC0_1(int a, int b, void *c);

extern int func_L00_003AB9C0(int a, void *b, int c, char *d, float e, float f, float g, float h);

extern void func_00282F20_1(char *, char *, float);

extern void func_00282DD8(char *, char *, char *);

extern char *func_L00_0032A088_1();

extern int *func_L00_0032A0B8_1();

typedef int VectorBits __attribute__((mode(TI)));
typedef union { VectorBits bits; float f[4]; } __attribute__((aligned(16))) BeamVector;
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { float vertices[4][4]; unsigned int colors[4]; float uv[4][2]; u64 registers[4]; } __attribute__((aligned(16))) BeamQuad;
extern void func_L00_003A2B28(char *);


/* func_L00_003A1580 is defined in L00_003A1580-g8.c. */



/* func_L00_003A2018 is defined in L00_003A2018-curve.c. */

/* Shared native body; original game role is unknown. */
/* Spins the wobble angles of each beam point and works out where it sits this frame. */
void func_L00_003A2138(int unused, float *points, int pointCount)
{
    float *point;
    int remaining;
    if (pointCount <= 0)
        return;
    point = points;
    remaining = pointCount;
    do {
        point[0] = func_00283B98_2(point[0], point[3]);
        point[1] = func_00283B98_2(point[1], point[4]);
        point[2] = func_00283B98_2(point[2], point[5]);
        point[9] = func_00283B98_2(point[9], point[12]);
        point[10] = func_00283B98_2(point[10], point[13]);
        point[11] = func_00283B98_2(point[11], point[14]);
        point[20] = FastSinOrCosA(point[0]) * point[6];
        point[21] = FastSinOrCosB(point[1]) * point[7];
        point[22] = -FastSinOrCosB(point[2]) * point[8];
        point[24] = FastSinOrCosA(point[9]) * point[15];
        point[25] = FastSinOrCosB(point[10]) * point[16];
        point[26] = -FastSinOrCosB(point[11]) * point[17];
        point += 32;
    } while (--remaining != 0);
}




/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
/* Fills in a missing trail point by continuing the line from the two points before it. */
void func_L00_003A2570(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* Derives a value from half of one argument, merges a helper's low byte into a packed word, then scales an input float, doubles a second helper's result and dispatches a seven-argument spawn. */
/* Spawns one glowing flare at a point, with a random size and brightness. */
void func_L00_003A25D8(int owner, int position, int color, int alphaBase, float size)
{
    int alpha;
    float radius;
    float rotation;

    alpha = func_002A7820_2(alphaBase >> 1, alphaBase);
    color = color | (alpha << 24);
    radius = func_002A7878_5(size * 0.75f, size);
    radius = radius + radius;
    rotation = func_002A7940_2();
    DrawBillboardQuad_00281EB8((char *)position, 44, color, 1, radius, 0.08f, rotation);
}

/* func_L00_003A2668 is defined in L00_003A2668-ribbon.c. */


/* straight-line constant-store body (no calls, no branches, no loads) */
/* Sets a drawing quad back to a plain square with default corners and texture settings. */
void func_L00_003A2B28(char *quad)
{
    *(long long *)(quad + 112) = 0LL;
    *(int *)(quad + 80) = 0;
    *(int *)(quad + 88) = 0;
    *(float *)(quad + 96) = 1.0f;
    *(float *)(quad + 104) = 1.0f;
    *(int *)(quad + 84) = 0;
    *(float *)(quad + 92) = 1.0f;
    *(int *)(quad + 100) = 0;
    *(float *)(quad + 108) = 1.0f;
    *(float *)(quad + 8) = -2.0f;
    *(float *)(quad + 24) = 2.0f;
    *(float *)(quad + 40) = -2.0f;
    *(float *)(quad + 56) = 2.0f;
    *(float *)(quad + 4) = -2.0f;
    *(float *)(quad + 36) = 2.0f;
    *(int *)(quad + 0) = 0;
    *(int *)(quad + 16) = 0;
    *(int *)(quad + 32) = 0;
    *(int *)(quad + 48) = 0;
    *(float *)(quad + 12) = 1.0f;
    *(float *)(quad + 28) = 1.0f;
    *(float *)(quad + 44) = 1.0f;
    *(long long *)(quad + 128) = 280993940374112LL;
    *(float *)(quad + 20) = -2.0f;
    *(float *)(quad + 52) = 2.0f;
    *(float *)(quad + 60) = 1.0f;
}

/* scales a float field by 1/1024, passes a caller word and two 16/48-byte scratch buffers to a four-argument helper, then forwards the second buffer with the scaled float to one helper and two sub-objects of the same parameter to three more helpers */
/* Works out where one of the weapon's attachment points is in the world. */
void func_L00_003A2BB8(char *moby, int jointIndex, char *out, char *offset)
{
    char jointMatrices[48];
    char scratch[16];
    int joint;
    float scale;

    scale = *(float *)(moby + 44) * 0.0009765625f;
    joint = jointIndex;
    get_moby_joint_matrices(moby, 1, &joint, jointMatrices);
    func_00282D30_3(out, scratch, scale);
    func_00282CC0_4(out, out, offset);
    func_00283098_2(out, out, moby + 192);
    func_00282CC0_4(out, out, moby + 16);
}

/* func_L00_003A2C60 is defined in L00_003A2C60-g8.c. */

/* func_L00_003A2EE0 is defined in L00_003A2EE0-g8.c. */



/* Emit layered sparks while the object's effect timer remains active. */
void func_L00_003A41F0(char *moby)
{
    float position[4], offset[4], velocity[4];
    int count, rotation;
    int style;
    int firstStyle;
    int firstKind, firstAlpha, secondKind, secondAlpha;
    float size;
    if (!*(unsigned char *)(moby + 0xBC))
        return;
    FastVectorHelperA(moby + 0xBC);
    firstStyle = 8;
    firstKind = 2;
    firstAlpha = 127;
    FastVecScale(position, moby + 0xD0, 0.1f);
    FastVecAdd(position, position, moby + 0x10);
    FastVecScale(offset, moby + 0xC0, 0.275f);
    FastVecAdd(position, position, offset);
    FastVecScale(velocity, moby + 0xD0, 0.1000000089f);
    for (count = 3; count >= 0; count--) {
        char *particle;
        rotation = RandomIntBelow(16);
        if (RandomIntBelow(2))
            rotation = -rotation;
        particle = SpawnSpinningSparkParticle(0.04f, position, 1.0f, 0.9f, rotation, velocity, 52500.0f, 0x7F204080, 0);
        if (particle) {
            char *sub;
            sub = particle + 0x20;
            *(short *)(particle + 10) = firstStyle;
            *(unsigned char *)(particle + 9) = ((*(short *)(moby + 0x32) >> 5) << 4) + FloatToInt(4.0f);
            *(int *)(sub + 4) = firstKind;
            *(unsigned char *)(sub + 10) = firstAlpha;
            *(unsigned char *)(sub + 11) = *(unsigned char *)(particle + 10);
        }
    }
    rotation = 16;
    style = 2;
    size = 15750.0009765625f;
    secondKind = 2;
    secondAlpha = 127;
    for (count = 2; count >= 0; count--) {
        char *particle = SpawnSpinningSparkParticle(0.02f, position, 1.0f, 1.0f, rotation, velocity, size, 0x7FFFFFFF, 0);
        if (particle) {
            char *sub;
            int brightness;
            sub = particle + 0x20;
            brightness = ((*(short *)(moby + 0x32) >> 5) << 4) + FloatToInt(4.0f);
            *(short *)(particle + 10) = style;
            *(unsigned char *)(particle + 9) = brightness;
            *(unsigned char *)(particle + 8) = RandomIntBelow(255);
            *(int *)(sub + 4) = secondKind;
            *(unsigned char *)(sub + 10) = secondAlpha;
            *(unsigned char *)(sub + 11) = *(unsigned char *)(particle + 10);
        }
        rotation = -rotation;
        style <<= 1;
        size -= 3150.0f;
    }
}


/* Runs one helper over the object and a stack buffer, then builds a second call from the object's field 104 sub-object - its field 24 as a float, the constants 2.0f/5.0f/0.6f and a bound data address - and stores the object into field 184 of the returned pointer when it is non-null. */
/* Spawns the weapon effect at the muzzle and links it back to the weapon. */
void func_L00_003A5370(int moby)
{
    int origin[4];
    int vars;
    int effect;

    vars = *(int *)(moby + 104);
    func_0029FCC0_1(moby, 0, origin);
    effect = SpawnTargetedProjectile(moby, origin, *(int *)(vars + 16), D_L00_001A8F20, *(float *)(vars + 24), 2.0f, 5.0f, 0.6f);
    if (effect != 0) {
        *(int *)(effect + 184) = moby;
    }
}

/* func_L00_003A53E8 is defined in L00_003A53E8-g16.c. */

/* func_L00_003A5FC0 is defined in L00_003A5FC0-contact.c. */



/* Emit the two layers of a short particle trail. */
void func_L00_003A78B0(char *moby)
{
    float point[4], offset[4], step[4], jitter[4];
    float *state = (float *)(*(char **)(moby + 0x68) + 0x14);
    float size = 0.175f;
    int i;
    point[0] = state[0];
    point[1] = state[1];
    point[2] = state[2];
    point[3] = 0.0f;
    FastVecScale(offset, moby + 0xD0, -0.1f);
    FastVecAdd(point, point, offset);
    FastVecScale(step, moby + 0xE0, 0.15f);
    FastVecAdd(point, point, step);
    FastVecScale(step, moby + 0xE0, -0.03333333507f);
    for (i = 8; i >= 0; i--) {
        char *particle;
        int rotation;
        jitter[0] = point[0] + RandomSignedFloatRange(0.0f, 0.1f);
        jitter[1] = point[1] + RandomSignedFloatRange(0.0f, 0.1f);
        jitter[2] = point[2] + RandomSignedFloatRange(0.0f, 0.1f);
        rotation = RandomIntBelow(255);
        SpawnGravityFadeParticle(jitter, D_L00_001A8F20, 4, 0x808080, rotation, 127, 127,
                      size * 210000.0f, size * 210000.0f, 0.0f, 1);
        particle = SpawnGravityFadeParticle(point, D_L00_001A8F20, 4, 0x203080, rotation, 16, 16,
                                 262500.0f, 262500.0f, 0.0f, 1);
        if (particle)
            *(unsigned char *)(particle + 2) = *D_L00_001FE940.material;
        FastVecAdd(point, point, step);
    }
}



/* func_L00_003A7E78 is defined in L00_003A7E78.c. */

/* Computes two sub-record addresses of a 192-byte block and hands three of its sub-records to four helpers, threading a second argument through two of them. */
/* Builds three direction vectors for the object from a starting direction. */
void func_L00_003A8060(char *moby, char *direction)
{
    char *base = moby + 192;
    char *other = moby + 208;
    float one = 1.0f;

    func_00282F20_1(base, (char *)(*(int *)(moby + 104)), one);
    FastVecCross(other, base, direction);
    func_00282F20_1(other, other, one);
    FastVecCross(moby + 224, other, base);
}



/* func_L00_003A8238 is defined in L00_003A8238-impact.c. */

/* Two size-driven clear loops over one buffer: calls two helpers with a fixed id to obtain a base and an offset, clears 80 records of 112 bytes walking backwards, then clears three fields at offsets 80/84/88 of every 96-byte record up to the buffer end. */
/* Clears all beam particles and the trail slots so none are active. */
void func_L00_003A8508(char *index)
{
	int cursor;
	int offset;
	int slotTable;
	int i;
	int slotEnd;
	short *particle;

	cursor = (int)func_L00_0032A088_1(1483 /* Pulse Rifle */, index);
	offset = *func_L00_0032A0B8_1(1483 /* Pulse Rifle */, index);
	slotTable = cursor + offset;
	particle = (short *)(cursor + 8866);
	for (i = 79; i >= 0; i--) {
		*particle = 0;
		particle = particle - 56;
	}
	cursor = slotTable;
	slotEnd = cursor + 288;
	do {
		*(short *)(cursor + 80) = 0;
		*(int *)(cursor + 84) = 0;
		*(int *)(cursor + 88) = 0;
		cursor = cursor + 96;
	} while (cursor < slotEnd);
}

/* Runs the two setup helpers on the object. When either reports a failure the dispatch
 * callback func_L00_003A8618 is registered against it instead; otherwise the object takes
 * the discard path unless its tag byte is 2. */
extern int func_L00_003A87D8(char *);

extern int func_L00_003A9000(char *);

extern void func_310440(char *);

extern void func_L00_003A8618(char *);

/* Registering the callback targets the level's own variant of the dispatcher: in four programs
 * (08, 09, ...) the call goes to a level-local function beside the shared one. */
extern void ref_L00_002E6EF8_00(void (*)(char *), char *);

/* Updates the beam effect each frame, and removes it once nothing is left to show. */
void func_L00_003A85A0(char *moby)
{
    char *thisMoby = moby;
    int first = UpdateBeamParticles(moby);
    int second = UpdateTrailSlot(moby);

    if (first == 0 && second == 0) {
        if (*(unsigned char *)(thisMoby + 0x20) == 2)
            func_310440(thisMoby);
    } else {
        ref_L00_002E6EF8_00(DrawBeamEffectMoby, thisMoby);
    }
}
/* Dispatches on a table lookup: the object's +0x68 pointer names a short that is looked up
   with key 0x5CB; on a miss the object takes the discard path, otherwise the two update
   helpers run. */
extern int func_32A060(int, int);
extern void func_310440(char *);
extern void func_3A8940(char *);
extern void func_3A91A0(char *);

/* Draws the beam effect, or removes it if its particle pool is gone. */
void func_L00_003A8618(char *moby)
{
    char *thisMoby = moby;

    if (func_32A060(0x5CB /* Pulse Rifle */, *(short *)(*(char **)(thisMoby + 0x68) + 0x1A)) == 0)
        func_310440(thisMoby);
    else {
        func_3A8940(thisMoby);
        func_3A91A0(thisMoby);
    }
}


