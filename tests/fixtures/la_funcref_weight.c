/* -frac2-la-funcref-weight positive control: five block-local values stored into two
   state blocks, two of them function addresses, one then called through its register. */
typedef struct { int a, b; int *next; int *page; } Menu;
typedef struct { int a; int (*init)(int); void (*upd)(void); int *c; } Cine;
extern Menu menu;
extern Cine cine;
extern int page[], next[], table[];
extern int init_fn(int);
extern void upd_fn(void);
extern int mode;

void control(void)
{
    if (mode == 8) {
        menu.next = next;
        cine.a = 0x18;
        menu.page = page;
        cine.c = table;
        menu.b = 0x18;
        cine.upd = upd_fn;
        cine.init = init_fn;
        cine.init(0);
    }
}
