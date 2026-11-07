/* Authored controls for the optional 16-byte slots of TImode GPR saves; no game code.
   tests/test_wide_saves_below.py compiles one case at a time (-DCASE_...): a widened save
   mode stays in force for the rest of a unit, which CASE_STICKY measures on purpose. */
typedef int TI __attribute__((mode(TI)));
extern void call(void);
extern void callf(float);

#ifdef CASE_PLAIN
/* Negative control: saved registers, none written in TImode. */
int plain(int *p, int n)
{
    int a = p[0], b = p[1], i;
    for (i = 0; i < n; i++)
        call();
    return a + b;
}
#endif

#if defined(CASE_ONE) || defined(CASE_STICKY)
/* One quadword held across calls in a saved register, beside 8-byte saves and an FPR. */
void wide_one(TI *p, TI *q, int n, float f)
{
    TI v = *p;
    int i;
    for (i = 0; i < n; i++)
        callf(f);
    *q = v;
}
#endif

#ifdef CASE_STICKY
/* Saves $17, which wide_one widened for the rest of the unit, without writing it in TImode. */
int plain_after(int *p, int n)
{
    int a = p[0], b = p[1], i;
    for (i = 0; i < n; i++)
        call();
    return a + b;
}
#endif

#ifdef CASE_ARGS
/* Stack arguments s1 and s2: their offsets come from the frame size reload works with,
   which the wide slot takes from 32 to 48 bytes. */
long wide_args(TI *p, TI *q, long a1, long a2, long a3, long a4, long a5, long a6,
               long s1, long s2)
{
    TI v = *p;
    long sum = s1 + s2;
    call();
    *q = v;
    return sum;
}
#endif

#ifdef CASE_TWO
/* Two quadwords held across calls: the order of two wide slots is not measured in retail. */
void wide_two(TI *p, TI *q, int n)
{
    TI v = p[0], w = p[1];
    int i;
    for (i = 0; i < n; i++)
        call();
    q[0] = v;
    q[1] = w;
}
#endif
