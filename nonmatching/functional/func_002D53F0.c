/* functional: high. Same calls, arguments, reads and writes as retail (the near miss without its matching-only address macro). */

/* Draws a centred text line (string 0x2D4F) at x 422, y = (int)(D_001B23A4 * 329 + 0.5), colour 0x80F0F0F0,
 * between the text begin/end calls, and returns 0. */

extern float D_001B23A4;
extern void func_0027C540(int);
extern void func_0029C530(void);
extern unsigned char *func_00288FB8(int);
extern void func_0027C660(void);
extern int func_0027FAA8(int, int, unsigned long, unsigned char *, int);

int func_002D53F0(void)
{
    int y;

    func_0027C540(0);
    func_0029C530();
    y = (int)(D_001B23A4 * 329.0f + 0.5f);
    func_0027FAA8(0x1A6, y, 0x80F0F0F0UL, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
