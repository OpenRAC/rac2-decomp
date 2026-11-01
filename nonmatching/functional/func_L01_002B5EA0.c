/* functional: medium. Written from the assembly: plain floats, 16-byte copies as four ints, the three scratch vectors are one local array; func_L00_002D49F0 is passed the player record's +32 vector that retail leaves in a0. The meaning of the data words at 0x1BF900-0x1BF940 and 0x1A9030 is taken from their use here. The argument is only compared with 15. */

extern char D_00189E20[];                   /* the player record */
extern char D_L01_001BF900[];
extern char D_L01_001BF920[];
extern char D_L01_001BF930[];
extern char D_L01_001BF940[];
extern int D_L01_001A9030;

extern void func_00282C88(void *);
extern void func_L00_002D49F0(void *);
extern float func_00282DB0(void *, void *);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_L00_002E0200(float, void *, int, void *, float);
extern int func_00278870(void *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);

static void copy16_002B5EA0(void *dst, void *src)
{
    ((int *)dst)[0] = ((int *)src)[0];
    ((int *)dst)[1] = ((int *)src)[1];
    ((int *)dst)[2] = ((int *)src)[2];
    ((int *)dst)[3] = ((int *)src)[3];
}

/* Moves the player by the step vector it builds (a fall, a slide or a walk, by the record's mode
   bytes), pushing the position out of the level's collision up to eight times. Returns 1 when
   the player cannot move (+496 set) or the step is short, and -1 when the push was longer than
   1.5 times the radius at +612; with `arg` 15 that push is clamped to 512 per axis, scaled by
   the radius and added back to the position before returning -1. */
int func_L01_002B5EA0(int arg)
{
    char *p = D_00189E20;
    float buf[12];                  /* 0: position copy, 4: step, 8: push */
    float *step = buf + 4;
    float *push = buf + 8;
    float length;
    int onfloor, count, hit, i;

    if (*(short *)(p + 496) != 0) {
        return 1;
    }
    copy16_002B5EA0(buf, p + 128);
    func_00282C88(step);
    if (*(short *)(p + 9470) != 0) {
        func_L00_002D49F0(p + 32);
        *(short *)(p + 9470) = 0;
    }
    onfloor = -0.92f < func_00282DB0(p + 32, p + 704);

    if (*(int *)(p + 8860) != 17) {
        if (p[8899] == 0 && *(short *)(p + 536) == 0 && onfloor == 0) {
            step[2] = *(float *)(p + 596);
        } else if ((unsigned char)p[8884] == 2) {
            func_L00_002D38A0(step, step, 5.0f);
        } else if ((unsigned char)p[8899] == 1 || *(short *)(p + 536) != 0) {
            func_L00_002D36E0(step, 0, 0.0f, 0.0f, 0.6f);
        } else if (D_L01_001A9030 == 0) {
            func_L00_002D36E0(step, 0, 0.0f, 0.0f, *(float *)(p + 596));
        } else {
            func_L00_002D38A0(step, step, 0.77f);
        }
    }

    func_00282CC0(p + 128, p + 128, step);
    for (count = 0; count < 8;) {
        if (p[8899] != 0 || onfloor != 0) {
            hit = func_00277258(p + 128, 804, *(char **)(p + 8848), *(float *)(p + 612));
        } else {
            float rise = *(float *)(p + 592) - *(float *)(p + 596);

            if (rise < 0.05f) {
                rise = 0.05f;
            }
            hit = func_L00_002E0200(*(float *)(p + 612), p + 128, 804, *(char **)(p + 8848), rise);
        }
        if (*(short *)(p + 486) == 0) {
            hit |= func_00278870(p + 128, *(float *)(p + 612));
        }
        if (hit == 0) {
            break;
        }
        copy16_002B5EA0(p + 128, D_L01_001BF930);
        copy16_002B5EA0(p + 304, D_L01_001BF940);
        copy16_002B5EA0(p + 320, D_L01_001BF920);
        count++;
        p[647] = 1;
        *(int *)(p + 620) = *(int *)(D_L01_001BF900 + 24);
    }

    func_00282CF0(p + 128, p + 128, step);
    func_00282CF0(push, p + 128, buf);
    length = func_00282DF0(push);
    if (*(float *)(p + 612) * 1.5f < length) {
        if (arg != 15) {
            return -1;
        }
        for (i = 0; i < 3; i++) {
            if (512.0f < push[i]) {
                push[i] = 512.0f;
            } else if (push[i] < -512.0f) {
                push[i] = -512.0f;
            }
        }
        func_00282F20(push, push, *(float *)(p + 612));
        func_00282CC0(p + 128, buf, push);
        return -1;
    }
    return 1;
}
