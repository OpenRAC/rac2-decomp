/* tests/test_no_static_chain_base.py: -frac2-no-static-chain-base, GCC 2.95.3's alias seeds.
   fill_table is the case; fill_short, fill_returned and count_calls are controls; chain_store
   and chain_local check that a nested function keeps its stores through the chain in order.  */

extern void h0();
extern void h1();
extern void h2();
extern void h3();
extern void h4();
extern void h5();
extern void h6();
extern void h7();
extern void h8();
extern void h9();
extern void h10();
extern void h11();
extern void h12();
extern void h13();
extern void h14();
extern void h15();
extern void h16();
extern void h17();
extern void h18();
extern void h19();
extern void h20();
extern void h21();
extern void h22();
extern void h23();
extern void h24();
extern void h25();
extern void h26();
extern void h27();
extern void h28();
extern void h29();
extern void h30();
extern void h31();
extern void (*table[])();
extern void (**get_table(void))();
extern void visit(void (*)(int));

/* After reload the table's address is in $v0, set from the register holding %hi(table).
   Seeded as the static chain, $v0 then has no known base, so sched2 lets every store
   through it depend on the callee saves; with the option the saves move down.  */
void fill_table(void)
{
    table[0] = h0;
    table[1] = h1;
    table[2] = h2;
    table[3] = h3;
    table[4] = h4;
    table[5] = h5;
    table[6] = h6;
    table[7] = h7;
    table[8] = h8;
    table[9] = h9;
    table[10] = h10;
    table[11] = h11;
    table[12] = h12;
    table[13] = h13;
    table[14] = h14;
    table[15] = h15;
    table[16] = h16;
    table[17] = h17;
    table[18] = h18;
    table[19] = h19;
    table[20] = h20;
    table[21] = h21;
    table[22] = h22;
    table[23] = h23;
    table[24] = h24;
    table[25] = h25;
    table[26] = h26;
    table[27] = h27;
    table[28] = h28;
    table[29] = h29;
    table[30] = h30;
    table[31] = h31;
}

/* Control: too few stores to need callee saves.  */
void fill_short(void)
{
    table[0] = h0;
    table[1] = h1;
    table[2] = h2;
    table[3] = h3;
    table[4] = h4;
    table[5] = h5;
    table[6] = h6;
    table[7] = h7;
    table[8] = h8;
    table[9] = h9;
    table[10] = h10;
    table[11] = h11;
}

/* Control: the table pointer is a call's value, which has no base either way.  */
void fill_returned(void)
{
    void (**p)() = get_table();
    p[0] = h0;
    p[1] = h1;
    p[2] = h2;
    p[3] = h3;
    p[4] = h4;
    p[5] = h5;
    p[6] = h6;
    p[7] = h7;
    p[8] = h8;
    p[9] = h9;
    p[10] = h10;
    p[11] = h11;
    p[12] = h12;
    p[13] = h13;
    p[14] = h14;
    p[15] = h15;
    p[16] = h16;
    p[17] = h17;
    p[18] = h18;
    p[19] = h19;
    p[20] = h20;
    p[21] = h21;
    p[22] = h22;
    p[23] = h23;
    p[24] = h24;
    p[25] = h25;
    p[26] = h26;
    p[27] = h27;
    p[28] = h28;
    p[29] = h29;
    p[30] = h30;
    p[31] = h31;
}

/* Control: a GNU C nested function, which does take a static chain in $v0.  bump has no
   stores to reorder: it reads `calls` and `out` through the chain, then stores to both.  */
int count_calls(int *out)
{
    int calls = 0;
    void bump(int k) { calls += k; *out = calls; }
    visit(bump);
    return calls;
}

/* A nested function stores to the parent's x through the chain, then through p, which is &x:
   the x store must stay first.  The default (2.95's seed: the chain is a stack reference, which
   cannot alias an argument) issues the *p store first.  */
int chain_store(int a0, int a1)
{
    int x = 0;
    void store_twice(int *p, int a, int b, int c)
    {
        x = a * b * c * a;
        *p = 5;
    }
    store_twice(&x, a0, a1, 7);
    return x;
}

/* The same stores, then a return of a local's address: the nested function's last set of $v0
   is `$sp + 16`.  Without the seed (2.95.3) the flow-insensitive record_set gives the incoming
   chain that stack base and the *p store goes first again; the option marks the chain seen.  */
int chain_local(int a0, int a1)
{
    int x = 0;
    int *store_and_local(int *p, int a, int b, int c, int *r)
    {
        int local[8];
        x = a * b * c * a;
        *p = 5;
        r = local;
        return r;
    }
    store_and_local(&x, a0, a1, 7, 0);
    return x;
}
