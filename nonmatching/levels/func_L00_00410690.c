/* func_L00_00410690 - 432 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_L00_00410690 452B vs 432B (in the -g8 sibling; -G8 is needed for the
   gp floats D_L00_001B1260/64/68 and the table at gp+0x2290, named by
   address). Logic matches. Left: allocation: retail saves s0-s3 only (alpha
   in s0 -> reused as the count, node in s1 -> reused as the src pointer),
   mine uses a fifth saved reg; the clamp min(level*4,0x60) is 'slti; movz
   s0,a0' in retail but 'li s0,0x60; slti; movn' in mine (tried
   if/ternary/>=0x61); the (alpha+f)<<24 shift is in the delay slot of
   func_002EF0F8 in retail. Constant 0x3E0EFA36 = 0.13962636f. */

/* goes in src/levels/shared/L00_004096B0-g8.c (-G8 needed for the gp floats), remove the marker from L00_004096B0.c */
typedef struct { char pad[0x1A]; short level; char pad1C[4]; float phase; } Node00410690;
extern float func_002EF240(int);
extern float func_002EE6F8(float);
extern float func_002EF0F8(float, float);
extern void func_002EE5B0(void *, void *, void *);
extern void func_002EE108(char *a, int *b, char *c);
extern void func_002ED210(void *, int, int, int, float, float, float);
extern float D_L00_001B1260 __attribute__((sda));
extern float D_L00_001B1264 __attribute__((sda));
extern int D_L00_001B1268 __attribute__((sda));
extern char D_L00_001B1280[] __attribute__((sda));
extern int D_L00_0018B068;
extern int D_L00_00139688[];

extern int func_L00_00410840(char *);

void func_L00_00410690(char *object)
{
    char vec[16] __attribute__((aligned(16)));
    int alpha;
    int color;
    int count;
    char *src;
    float ratio;
    float shade;
    Node00410690 *node;

    node = *(Node00410690 **)(object + 0x68);

    ratio = func_002EF240(node->level) / func_002EF240(0x5A);
    if (ratio > 1.0f)
        ratio = 1.0f;
    shade = D_L00_001B1260 + (D_L00_001B1264 - D_L00_001B1260) * ratio;
    alpha = node->level * 4;
    if (alpha > 0x60)
        alpha = 0x60;
    alpha = (alpha + func_002EF250(func_002EE6F8(node->phase) * 32.0f)) << 24;
    node->phase = func_002EF0F8(node->phase, 0.13962636f);
    color = alpha | D_L00_001B1268;
    count = D_L00_00139688[D_L00_0018B068];
    {
        int avail = func_L00_00410840(object);
        if (avail < count)
            count = avail;
    }
    if (count > 0) {
        src = D_L00_001B1280;
        do {
            func_002EE5B0(vec, src, object + 0xC0);
            src += 0x10;
            count--;
            func_002EE108(vec, (int *)(object + 0x10), vec);
            func_002ED210(vec, 0xB, color, 1, shade, 0.0f, 0.0f);
            func_002ED210(vec, 0xB, 0x80808080, 1, shade * 0.3f, 0.0f, 0.0f);
        } while (count != 0);
    }
}
