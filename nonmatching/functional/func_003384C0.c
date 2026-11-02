/* functional: high. Near miss (604 vs 600 bytes: scheduling and one address form only); same reads, writes and calls in order; float constants taken from the retail words. */
extern void func_0027AB40(void);
extern void func_00300A00(void *, int, float, float, float, float, float);
extern int func_00335E08(void);
extern int D_001A8CFC;
extern float D_001B9040[];

void func_003384C0(char *obj, int hi, int lo, float a, float b, float c, float d)
{
    float saved, k, t, c2, d2;
    int flags;

    if (D_001A8CFC == 0)
        return;
    saved = D_001B9040[44];
    D_001B9040[44] = 0.62f;
    k = 1.0f;
    func_0027AB40();
    t = (b - a - 26.0f) * 0.008928571827709675f;
    t = t * 0.3110000193119049f + 0.03750000149011612f;
    if (func_00335E08() == 1)
        k = 0.9f;
    flags = (hi << 24) | lo;
    func_00300A00(*(void **)(obj + 0x220C), flags, c, a, -1.0f, k, t);
    func_00300A00(*(void **)(obj + 0x220C), flags, d, a, 1.0f, k, t);
    t = (d - c - 150.0f) * 0.003267973894253373f;
    c2 = c + 16.0f;
    d2 = d - 16.0f;
    t = t * 0.43300002813339233f + 0.10199999809265137f;
    func_00300A00(*(void **)(obj + 0x2210), flags, c2, a, -1.0f, 1.0f, t);
    func_00300A00(*(void **)(obj + 0x2210), flags, d2, a, 1.0f, 1.0f, t);
    func_00300A00(*(void **)(obj + 0x2210), flags, c2, b, -1.0f, -1.0f, t);
    func_00300A00(*(void **)(obj + 0x2210), flags, d2, b, 1.0f, -1.0f, t);
    D_001B9040[44] = saved;
    func_0027AB40();
}
