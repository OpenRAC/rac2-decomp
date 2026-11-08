/* tests/test_sticky_volatile_sets.py: GCC 2.95's set-side `|=`, the default, and
   -fno-rac2-sticky-volatile-sets. Authored controls, no game code. store_then_volatile is
   the case; plain_stores, volatile_first and volatile_load are controls.  */
extern volatile int status;
extern int extra;
extern void one(void);
extern void two(int);

/* A plain store, then a volatile store, before one(). reorg's backward search from the call
   passes the volatile store, then the plain one: by default the flag stays set and the
   search stops there; with -fno-rac2-sticky-volatile-sets the plain store clears it and
   the multiply moves into one()'s slot.  */
void store_then_volatile(int *p, int a, int b, int c)
{
    int product = a * b;

    *p = c;
    status = 0;
    one();
    two(product);
}

/* No volatile store: the multiply may fill one()'s slot either way.  */
void plain_stores(int *p, int a, int b, int c)
{
    int product = a * b;

    *p = c;
    extra = 0;
    one();
    two(product);
}

/* The volatile store comes first: the plain store after it fills the slot either way.  */
void volatile_first(int *p, int a, int b, int c)
{
    int product = a * b;

    status = 0;
    *p = c;
    one();
    two(product);
}

/* A volatile load, not a store: the set side never sees it.  */
void volatile_load(int *p, int a, int b)
{
    int product = a * b;

    *p = status;
    one();
    two(product);
}
