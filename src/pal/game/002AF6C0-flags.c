/* func_PAL_002AF6C0, the PAL copy of func_002AEB60: the same C, where the field at 0x4C becomes 0.6f. */

extern float func_0029F530(void *);
extern float func_002AEAE0(int, float);

int func_PAL_002AF6C0(char *object, float threshold)
{
    float current = func_002AEAE0(4, func_0029F530(object));
    float difference = current - threshold;
    float step = func_002AEAE0(4, *(float *)(object + 0x48) * 0.6f);
    if (threshold <= current)
        return difference < step;
    return 0;
}
