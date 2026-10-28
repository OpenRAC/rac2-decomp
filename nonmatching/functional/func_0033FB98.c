/* functional: medium. Written from the assembly (no draft existed); same calls with the same arguments in the same order and the same stores. Local names follow the stack slots. */
typedef struct { float x, y; } Vec2;
typedef struct { int *entries; } Table18D4;

extern Vec2 D_001AE048[6];          /* 8-byte pairs at 0x1AE048, 50, 58, 60, 68, 70 */
extern Table18D4 *D_001B18D4;
extern char *D_001A8CFC;
extern unsigned char D_00139568[];
extern int D_00139868[];
extern int D_00138180[];
extern char D_00239BA0[];           /* records, 0xE0 bytes each */

extern void func_00115484(void *, int, int);
extern void func_00335E38(char *, float, float, float, float);
extern void func_00335E68(void *, int);
extern void func_00336920(void *, int, int);
extern char *func_0034E5B8(char *);
extern void func_00336F20(int, int *, int *, int *);
extern int *func_00335E20(void *);
extern void func_00336498(void *, int, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_003409C8(char *, int);
extern void func_00340B70(char *, int);
extern int func_002A9588(int, int, int, int, int);
extern void func_003363C0(void *, float);

#define REC(id) (D_00239BA0 + D_00139568[id] * 0xE0)

static void place(char *obj, int off, Vec2 *v)
{
    float *p = *(float **)(obj + 0x80C);

    func_00335E38(obj + off, v->x + p[0], v->y + p[1], 0.0f, 0.0f);
}

int func_0033FB98(char *obj, int buttons)
{
    Vec2 zero0, zero1, zero2, zero3;    /* sp + 0, 0x10, 0x20, 0x30 */
    Vec2 v40, v50, v60, v70, v80, v90;
    int a0v, a4v, a8v;
    int i;
    char *s3;

    func_00115484(&zero0, 0, 8);
    func_00115484(&zero1, 0, 8);
    func_00115484(&zero2, 0, 8);
    func_00115484(&zero3, 0, 8);
    v40 = D_001AE048[0];
    v50 = D_001AE048[1];
    v60 = D_001AE048[2];
    v70 = D_001AE048[3];
    v80 = D_001AE048[4];
    place(obj, 0x00, &zero0);
    place(obj, 0x4C, &zero3);
    place(obj, 0xE4, &zero1);
    place(obj, 0x130, &zero2);
    place(obj, 0x828, &v40);
    place(obj, 0x8B8, &v60);
    place(obj, 0x900, &v50);
    place(obj, 0x948, &v70);
    place(obj, 0x990, &v80);
    v90 = D_001AE048[5];
    place(obj, 0x2A8, &v90);
    place(obj, 0x2F4, &v90);
    place(obj, 0x5A0, &v90);

    if (D_001B18D4 != 0) {
        s3 = obj + 0x5EC;
        for (i = 0; i < 8; i++, s3 += 0x3C) {
            char *ent = (char *)D_001B18D4->entries + i * 0x1C;
            char *item;
            char *rec;
            int *r;

            if (*(int *)ent == 0)
                func_00335E68(s3, 0);
            else {
                func_00335E68(s3, 1);
                func_00336920(s3, *(int *)((char *)D_001B18D4->entries + i * 0x1C), 0);
            }
            func_00335E68(func_0034E5B8(D_001A8CFC + 0x36F28) + i * 0x48, 0);
            a0v = 0;
            a4v = 0;
            a8v = 0;
            func_00336F20(*(int *)((char *)D_001B18D4->entries + i * 0x1C + 0x18), &a0v, &a4v, &a8v);
            r = func_00335E20(s3);
            *r = (*r & 0xFF000000) | (a8v & 0xFFFFFF);
            item = func_0034E5B8(D_001A8CFC + 0x36F28) + i * 0x48;
            func_00335E68(item, 1);
            func_00336498(item, a0v, a4v);
            func_00336B90(item, 0x64);
            func_00336B98(item, 0x64);

            rec = REC(*(int *)((char *)D_001B18D4->entries + i * 0x1C + 0x18));
            if (*(int *)rec == 0)
                continue;
            if (*(int *)(rec + 0x6C) == 0 && *(unsigned char *)(rec + 4) == 0)
                continue;
            func_00336B90(item, *(int *)(rec + 0x6C));
            r = func_00335E20(s3);
            *r = (*r & 0xFF000000) | (a8v & 0xFFFFFF);
            {
                int id = *(int *)((char *)D_001B18D4->entries + i * 0x1C + 0x18);

                if (*(int *)(REC(id) + 0x6C) > 0)
                    func_00336B98(item, D_00139868[id] >> 5);
            }
        }
    }

    if (buttons & 4) {
        int v;

        func_002E5E58(3, 0, 0);
        v = *(int *)(obj + 0x7CC) - 1;
        *(int *)(obj + 0x7CC) = (-1 < v) ? v : 7;
    } else if (buttons & 8) {
        int v;

        func_002E5E58(3, 0, 0);
        v = *(int *)(obj + 0x7CC) + 1;
        *(int *)(obj + 0x7CC) = (7 < v) ? 0 : v;
    } else {
        int sel = *(int *)(obj + 0x81C);

        if (sel == 0)
            func_003409C8(obj, buttons);
        else if (sel == 1)
            func_00340B70(obj, buttons);
    }
    if (D_00138180[0x1C4 / 4] & 0xC)
        func_002A9588(0, 0, 1, 0, 1);
    {
        char *s1 = obj + 0x5A0;
        int *r = func_00335E20(s1);

        *r = func_002A9588(0x60442D00, 0x70FFFEED, 0x14, 0, 0);
        func_003363C0(s1, (float)*(int *)(obj + 0x7CC));
    }
    return 0;
}
