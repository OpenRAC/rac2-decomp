/* Authored controls for the optional frame-pointer liveness; no game code. */
extern int f(int);
extern int more(int);
extern int *next(int *, int);
extern void g(int, int, int, int);
extern int one, two, three;

/* Nine values live across calls, so $fp holds x, the one set at the top of the loop body.
   x dies at the last test in the body. Three tests after the loop use up reorg's search
   budget, so the loop branch's slot (x = p + 4, taken from the body) depends on flow's view of
   $fp at the exit: live there by default (bnel), dead with the option (bne). */
void dead_after_loop(int *p, int n)
{
    int a = p[0], b = p[1], c = p[2], d = p[3], e = p[4], h = p[5];
    int *x;

    while (more(n--)) {
        x = p + 4;
        if ((int) x & n) {
            f(a); f(b); f(c); f(d); f(e); f(h);
        }
        f(a); f(b); f(c); f(d); f(e); f(h);
        f(a); f(b); f(c); f(d); f(e); f(h);
        if ((int) x == n)
            f(0);
        p = next(p, n);
    }
    if (one)
        f(1);
    if (two)
        f(2);
    if (three)
        f(3);
    g(a, b, c, d);
    g(e, h, 0, 0);
}

/* Control: x is read after the loop, so $fp is live at the exit either way. */
int live_after_loop(int *p, int n)
{
    int a = p[0], b = p[1], c = p[2], d = p[3], e = p[4], h = p[5];
    int *x = p;

    while (more(n--)) {
        x = p + 4;
        if ((int) x & n) {
            f(a); f(b); f(c); f(d); f(e); f(h);
        }
        f(a); f(b); f(c); f(d); f(e); f(h);
        f(a); f(b); f(c); f(d); f(e); f(h);
        if ((int) x == n)
            f(0);
        p = next(p, n);
    }
    if (one)
        f(1);
    if (two)
        f(2);
    if (three)
        f(3);
    g(a, b, c, d);
    g(e, h, 0, 0);
    return *x;
}

/* Control: one value fewer, so x gets an ordinary saved register ($fp only holds an address
   after the loop). */
void no_fp(int *p, int n)
{
    int a = p[0], b = p[1], c = p[2], d = p[3], e = p[4];
    int *x;

    while (more(n--)) {
        x = p + 4;
        if ((int) x & n) {
            f(a); f(b); f(c); f(d); f(e);
        }
        f(a); f(b); f(c); f(d); f(e);
        f(a); f(b); f(c); f(d); f(e);
        if ((int) x == n)
            f(0);
        p = next(p, n);
    }
    if (one)
        f(1);
    if (two)
        f(2);
    if (three)
        f(3);
    g(a, b, c, d);
    g(e, 0, 0, 0);
}

/* Control: alloca needs a frame pointer, so $fp keeps its special liveness either way. */
void with_frame_pointer(int *p, int n)
{
    int a = p[0], b = p[1], c = p[2], d = p[3], e = p[4], h = p[5];
    int *x;
    int *buffer = __builtin_alloca(n * 4);

    while (more(n--)) {
        x = p + 4;
        if ((int) x & n) {
            f(a); f(b); f(c); f(d); f(e); f(h);
        }
        f(a); f(b); f(c); f(d); f(e); f(h);
        if ((int) x == n)
            f(0);
        p = next(p, n);
    }
    if (one)
        f(1);
    if (two)
        f(2);
    g(a, b, c, d);
    g(e, h, buffer[0], 0);
}
