/* -frac2-la-funcref-weight negative control: the same block with data addresses only,
   so the switch must leave it byte-identical. */
typedef struct { int a, b; int *next; int *page; } Menu;
typedef struct { int a; int (*init)(int); void (*upd)(void); int *c; } Cine;
extern Menu menu;
extern Cine cine;
extern int page[], next[], table[];
extern int init_tab[];
extern int upd_tab[];
extern int mode;

void control(void)
{
    if (mode == 8) {
        menu.next = next;
        cine.a = 0x18;
        menu.page = page;
        cine.c = table;
        menu.b = 0x18;
        cine.c = upd_tab;
        menu.page = init_tab;
        mode = 0;
    }
}
