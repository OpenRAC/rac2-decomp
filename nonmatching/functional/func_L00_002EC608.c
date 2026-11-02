/* functional: medium. Plain C written from the assembly; the block handed to func_00280B90 is the first 28 words of a 36-word stack area, and the matrix's fourth row is the point 0.25 along the direction from the position to the target, written in the same places as retail (the colour words are packed from the argument with a random alpha ORed in as retail's shifts do). */
extern void func_00281DE8(void *, int, int, int);
extern int func_002A7820(int, int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern void func_00283410(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);
extern float D_L00_001B8DC0[3];

/* A burst of three quads at `position` that point at the point D_L00_001B8DC0: a block of 4 rows of 4 floats (a quad), the colour words, and per-quad scale and random alpha, handed to func_00280B90 three times with the quad shrinking by half each time. `colour` is halved bytewise for the first. */
void func_L00_002EC608(void *position, int colour)
{
    float *pos = position;
    float blk[36];
    float ang[4], dir[4], mat[16];
    float *moved = mat + 12;
    unsigned int packed, alpha;
    float dist, scale;
    int i;

    blk[0] = 0.0f;
    blk[1] = -2.0f;
    blk[2] = -2.0f;
    blk[3] = 1.0f;
    blk[4] = 0.0f;
    blk[5] = -2.0f;
    blk[6] = 2.0f;
    blk[7] = 1.0f;
    blk[8] = 0.0f;
    blk[9] = 2.0f;
    blk[10] = -2.0f;
    blk[11] = 1.0f;
    blk[12] = 0.0f;
    blk[13] = 2.0f;
    blk[14] = 2.0f;
    blk[15] = 1.0f;
    func_00281DE8(blk, 44, 1, 128);
    alpha = (unsigned int)func_002A7820(48, 64);
    packed = (alpha << 24) | (((unsigned int)(colour >> 17)) << 16) | (((unsigned int)(colour >> 9)) & 0xFF00) | (((unsigned int)(colour >> 1)) & 0xFF);
    blk[23] = 1.0f;
    blk[24] = 1.0f;
    blk[26] = 1.0f;
    blk[27] = 1.0f;
    *(unsigned int *)&blk[16] = packed;
    *(unsigned int *)&blk[19] = packed;
    *(unsigned int *)&blk[18] = packed;
    *(unsigned int *)&blk[17] = packed;
    blk[20] = 0.0f;
    blk[21] = 0.0f;
    blk[22] = 0.0f;
    blk[25] = 0.0f;
    ang[3] = 0.0f;
    ang[2] = func_00283248(D_L00_001B8DC0[0] - pos[0], D_L00_001B8DC0[1] - pos[1]);
    dist = func_00282E80(pos, D_L00_001B8DC0);
    ang[1] = -func_00283248(dist, D_L00_001B8DC0[2] - pos[2]);
    ang[0] = func_002A7940();
    func_00283410(mat, ang);
    func_00282CF0(dir, D_L00_001B8DC0, pos);
    func_00282F20(dir, dir, 0.25f);
    moved[3] = 1.0f;
    moved[2] = pos[2] + dir[2];
    moved[0] = pos[0] + dir[0];
    moved[1] = pos[1] + dir[1];
    scale = func_002A7878(0.3f, 0.4f);
    for (i = 0; i < 4; i++) {
        func_00282D30(blk + 4 * i, blk + 4 * i, scale);
    }
    func_00280B90(blk, mat, 0);
    for (i = 0; i < 4; i++) {
        func_00282D30(blk + 4 * i, blk + 4 * i, 0.5f);
    }
    alpha = (unsigned int)func_002A7820(64, 127);
    packed = (unsigned int)colour + (alpha << 24);
    *(unsigned int *)&blk[16] = packed;
    *(unsigned int *)&blk[19] = packed;
    *(unsigned int *)&blk[18] = packed;
    *(unsigned int *)&blk[17] = packed;
    func_00280B90(blk, mat, 0);
    for (i = 0; i < 4; i++) {
        func_00282D30(blk + 4 * i, blk + 4 * i, 0.5f);
    }
    alpha = (unsigned int)func_002A7820(64, 127);
    packed = (alpha << 24) + 0x7F7F7F;
    *(unsigned int *)&blk[16] = packed;
    *(unsigned int *)&blk[19] = packed;
    *(unsigned int *)&blk[18] = packed;
    *(unsigned int *)&blk[17] = packed;
    func_00280B90(blk, mat, 0);
}
