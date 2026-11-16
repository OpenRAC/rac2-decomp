#include "common.h"

extern void FastVecAdd(char *, char *, char *);
extern float IntToFloat(int);
extern int FastTweenColor(int, int, float);
extern int g_streak_fade_start __attribute__((sda));
extern int g_streak_fade_end __attribute__((sda));
extern int g_streak_color_a __attribute__((sda));
extern int g_streak_color_b __attribute__((sda));
extern int g_streak_color_c __attribute__((sda));
/* Steps the streak effect each frame: moves its trail points and fades its brightness as the timer runs down. */
void streak_effect_update(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    int j;
    char *q;
    if (*(short *)(s + 0x12)) {
        (*(short *)(s + 0x12))--;
        {
            int i;
            for (i = 0; i < 23; i++)
                FastVecAdd(s + 0x60 + i * 16, s + 0x60 + i * 16, s + 0x260 + i * 16);
        }
        {
            int i = 0;
            do {
                int next = i + 1;
                char *p;
                q = (char *)(i * 16 + (int)s);
                j = 2;
                p = q;
                do {
                    q += 0x460;
                } while (0);
                for (; j >= 0; j--) {
                    char *b = p + 0x560 + (2 - j) * 64;
                    char *a = q + (2 - j) * 64;
                    FastVecAdd(a, a, b);
                }
                i = next;
            } while (i < 4.0f);
        }
        {
            int i;
            for (i = 0; i < 4; i++) {
                unsigned char *idx = (unsigned char *)s + 0x18;
                q = (char *)(idx[i] * 16 + (int)s) + 0x20;
                qcopy(s + 0x420 + i * 16, q);
            }
        }
    }
    if (*(short *)(s + 0x12) > g_streak_fade_start) {
        float a = IntToFloat(*(short *)(s + 0x12) - g_streak_fade_start);
        float b = IntToFloat(*(int *)(s + 0x620) - g_streak_fade_start);
        *(int *)(s + 0x14) = FastTweenColor(g_streak_color_b, g_streak_color_a, a / b);
    } else if (*(short *)(s + 0x12) > g_streak_fade_end) {
        float a = IntToFloat(*(short *)(s + 0x12) - g_streak_fade_end);
        float b = IntToFloat(g_streak_fade_start - g_streak_fade_end);
        *(int *)(s + 0x14) = FastTweenColor(g_streak_color_c, g_streak_color_b, a / b);
    } else *(int *)(s + 0x14) = 0;
}
