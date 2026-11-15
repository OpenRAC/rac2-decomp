#include "include_asm.h"
#include "names.h"

/* func_PAL_002AC290 and func_PAL_002AC3C0, the PAL copies of func_002AB800 and func_002AB8C0:
 * the same C, where the frame counts at +0xC and +0xE are rescaled to 50 Hz. */

typedef int s32;
typedef unsigned char u8;

extern float IntToFloat(int index);
extern int FloatToInt(float value);
extern void get_moby_color(int first, char *a, char *b, char *c);
extern int FastDecTimer(char *a0);
extern void set_moby_color(void *a, int b, int c, int d);

void func_PAL_002AC290(int first, char *object)
{
    char *s0 = object;
    short s1 = *(short *)(s0 + 0);
    int total;
    float limit;
    int result;

    if (s1 != 0 && *(short *)(s0 + 2) == 0)
        return;
    total = ((s32)(*(short *)(s0 + 12)) * 5 + 2) / 6;
    *(short *)(s0 + 2) = 0;
    *(short *)(s0 + 0) = total;
    if (s1 != 0) {
        limit = IntToFloat(((s32)(*(short *)(s0 + 14)) * 5 + 2) / 6);
        result = FloatToInt((float)(((s32)(*(short *)(s0 + 12)) * 5 + 2) / 6) * ((float)s1 / limit));
        *(short *)(s0 + 0) = (short)result;
        if ((short)result <= 0)
            *(short *)(s0 + 0) = 1;
    } else {
        int a, b, c;
        get_moby_color(first, (char *)&a, (char *)&b, (char *)&c);
        *(char *)(s0 + 4) = (unsigned char)a;
        *(char *)(s0 + 5) = (unsigned char)b;
        *(char *)(s0 + 6) = (unsigned char)c;
    }
}

void func_PAL_002AC3C0(void *owner, u8 *obj)
{
    int r, g, b;
    float limit, f;

    if (*(short *)obj == 0)
        return;

    if (FastDecTimer((char *)obj) != 0) {
        if (*(short *)(obj + 2) != 0) {
            set_moby_color(owner, obj[4], obj[5], obj[6]);
            return;
        }
        *(short *)(obj + 2) = 1;
        *(short *)obj = ((s32)(*(short *)(obj + 0xE)) * 5 + 2) / 6;
    }

    if (*(short *)(obj + 2) == 0) {
        limit = IntToFloat(((s32)(*(short *)(obj + 0xC)) * 5 + 2) / 6);
        f = (limit - (float)*(short *)obj) / limit;
        r = obj[7] ? FloatToInt((float)obj[4] + (float)(obj[7] - obj[4]) * f) : obj[4];
        g = obj[8] ? FloatToInt((float)obj[5] + (float)(obj[8] - obj[5]) * f) : obj[5];
        b = obj[9] ? FloatToInt((float)obj[6] + (float)(obj[9] - obj[6]) * f) : obj[6];
    } else {
        limit = IntToFloat(((s32)(*(short *)(obj + 0xE)) * 5 + 2) / 6);
        f = (limit - (float)*(short *)obj) / limit;
        r = obj[7] ? FloatToInt((float)obj[7] + (float)(obj[4] - obj[7]) * f) : obj[4];
        g = obj[8] ? FloatToInt((float)obj[8] + (float)(obj[5] - obj[8]) * f) : obj[5];
        b = obj[9] ? FloatToInt((float)obj[9] + (float)(obj[6] - obj[9]) * f) : obj[6];
    }

    set_moby_color(owner, r, g, b);
}
