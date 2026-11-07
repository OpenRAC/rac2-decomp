/* Fixture for tests/test_no_extra_increment_givs.py: authored, not game code. */
extern unsigned long table[];
extern volatile int status;

/* Four unconditional increments of one cursor per iteration: by default strength_reduce turns
   the first three into givs, so the stores take offsets 0/8/16/24 and the cursor one add.
   With the option every increment stays a biv increment: store, add, four times. */
void fill(unsigned long *p, int n, unsigned long a, unsigned long b)
{
    int i;

    for (i = 0; i < n; i++) {
        *p++ = a;
        *p++ = b;
        *p++ = a + i;
        *p++ = b + i;
    }
}

/* The same cursor through an index: the biv is n, incremented four times. */
void fill_index(int count, unsigned long a)
{
    int i, n;

    for (i = 0, n = 12; i < count; i++) {
        table[n] = a;
        n++;
        table[n] = a + 1;
        n++;
        table[n] = a + i;
        n++;
        table[n] = i;
        n++;
    }
}

/* Control: one increment per iteration, nothing to convert. */
void fill_once(unsigned long *p, int n, unsigned long a)
{
    int i;

    for (i = 0; i < n; i++)
        *p++ = a + i;
}

/* Control: a volatile read in the loop sets loop_has_volatile, which already skips the
   conversion in both profiles. */
void fill_volatile(unsigned long *p, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        *p++ = status;
        *p++ = i;
    }
}

/* Control: increments under a test are not unconditional, so they are never converted. */
void fill_some(unsigned long *p, int n, unsigned long a)
{
    int i;

    for (i = 0; i < n; i++) {
        if (a & (1 << i)) {
            *p++ = a;
            *p++ = i;
        }
    }
}

/* Control: a counted loop whose counter check_dbra_loop reverses into a count-down, which the
   option does not touch. */
void clear16(unsigned long *p)
{
    int i;

    for (i = 0; i < 16; i++)
        p[i] = 0;
}

/* The loop counter itself is incremented twice. By default the first increment becomes a giv,
   which leaves the counter one increment, and check_dbra_loop reverses the loop (a count-down
   to bgez). With the option the counter keeps both increments, check_dbra_loop sees two, and
   the loop counts up as written: the option changes check_dbra_loop's input, not its code. */
void pairs(unsigned long *p)
{
    int i;

    for (i = 0; i < 32; ) {
        p[i] = 0;
        i++;
        p[i] = 1;
        i++;
    }
}
