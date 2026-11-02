/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Retained plain-C attempt: 256/260 bytes; first difference +0x88.
 * us: 0/27, pal: 0/27, us2: 0/27.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * The scan matches structurally, but callback-pointer allocation and delay-slot scheduling differ. -g and disabling the second scheduler did not resolve it. Next: callback ABI/lifetime evidence.
 */
extern int D_L00_001FACE0 __attribute__((nosda));
extern char *D_L00_001B1EA8;
extern char *D_L00_001B1EA8_1 __attribute__((sda));
extern char *D_L00_001B1E9C;
extern void func_002A05A8(void *object);
extern void func_002A0F48(void *object);
void func_L00_0032CF60(void)
{
    char *scan, *object, *last = 0;
    void (*update)(void *);
    D_L00_001FACE0 = 0;
    D_L00_001B1EA8 = 0;
    for (scan = D_L00_001B1E9C; *(unsigned char *)(scan + 0x20) != 255; scan += 0x100) {
        if ((*(unsigned char *)(scan + 0x20) & 0x80) == 0 &&
            (*(unsigned short *)(scan + 0x34) & 2) == 0) {
            if (last != 0)
                *(char **)(last + 0x28) = scan;
            else
                D_L00_001B1EA8_1 = scan;
            last = scan;
        }
    }
    if (last != 0)
        *(char **)(last + 0x28) = 0;
    object = D_L00_001B1EA8;
    while (object != 0) {
        if (*(signed char *)(object + 0x20) >= 0) {
            if ((*(unsigned short *)(object + 0x34) & 0x40) == 0)
                func_002A05A8(object);
            update = *(void (**)(void *))(object + 0x64);
            if (update != 0)
                update(object);
            if ((*(unsigned short *)(object + 0x34) & 4) == 0)
                func_002A0F48(object);
        }
        object = *(char **)(object + 0x28);
    }
}
