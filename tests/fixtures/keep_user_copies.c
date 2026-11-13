/* -frac2-keep-user-copies (tests/test_keep_user_copies.py): a frame counter copied into a
   named local after its incremented value is stored, as in func_PAL_L09_0040FD68 and
   func_PAL_L00_003B9E80, and controls without such a copy. */

extern void act(char *obj, int state, int arg);

/* The L09 shape: the copy feeds a float conversion compared with a 50 Hz limit.  */
void counter_float(char *obj, float *data)
{
    int ticks, t;

    ticks = *(unsigned short *)(obj + 0x96);
    *(unsigned short *)(obj + 0x96) = ticks + 1;
    t = ticks;
    if ((float)t > ((data[0] + data[1]) * 300.0f + 2.0f) * 0.16666667f)
        act(obj, 4, -1);
}

/* The L00 shape: the copy is compared with a converted frame limit.  */
extern int limit_frames;
void counter_limit(char *obj)
{
    int limit = limit_frames;
    unsigned timer = *(unsigned short *)(obj + 0x96), old;

    *(unsigned short *)(obj + 0x96) = timer + 1;
    old = timer;
    if ((int)old <= (limit * 5 + 2) / 6)
        return;
    act(obj, 0, 0);
}

/* Controls: no copy into a user variable.  */
void control_float(char *obj, float *data)
{
    int ticks = *(unsigned short *)(obj + 0x96);

    *(unsigned short *)(obj + 0x96) = ticks + 1;
    if ((float)ticks > ((data[0] + data[1]) * 300.0f + 2.0f) * 0.16666667f)
        act(obj, 4, -1);
}

void control_limit(char *obj)
{
    int limit = limit_frames;
    unsigned old = *(unsigned short *)(obj + 0x96);

    *(unsigned short *)(obj + 0x96) = old + 1;
    if ((int)old <= (limit * 5 + 2) / 6)
        return;
    act(obj, 0, 0);
}

int control_sum(int *p, int n)
{
    int i, s = 0;

    for (i = 0; i < n; i++)
        s += p[i];
    return s;
}
