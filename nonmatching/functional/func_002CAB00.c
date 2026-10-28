/* functional: high. Transcribed branch by branch from retail; calls, arguments and stores in retail's order. */
typedef struct Slot Slot;
typedef int (*SlotFn)(Slot *);
typedef void (*SlotCb)(Slot *, int);
struct Slot { int fn0; int pad4; int cb8; int cbC; };

typedef struct Screen {
    char pad0[0xE8];
    Slot *cur;               /* 0xE8 */
    Slot *slots[14];         /* 0xEC */
    char pad124[4];
    Slot *next;              /* 0x128 */
} Screen;

typedef struct Menu {
    int state;               /* 0x00 */
    int phase;               /* 0x04 */
    int mode;                /* 0x08 */
    char pad0C[8];
    Screen *screen;          /* 0x14 */
    Screen *target;          /* 0x18 */
    int result;              /* 0x1C */
    char pad20[0xC0];
    Screen *old;             /* 0xE0 */
} Menu;

extern Menu D_001F2840;
extern int D_001AB7A4;
extern char D_0025A190[];
extern char D_00259198[];
extern void func_002D7AC8(int, int);
extern int func_002CBAE0(void);
extern void func_002CCED0(void);
extern void func_002E5E58(int, int, int);

#define CALL_CB(o, off, arg) ((SlotCb)(*(int *)((char *)(o) + (off))))((o), (arg))

void func_002CAB00(void)
{
    Menu *m = &D_001F2840;
    Screen *p = m->screen;
    Slot **arr = p->slots;
    int i;
    Slot *o;

    if (D_001AB7A4 != 0) {
        if (m->phase == 0 && (char *)p == D_0025A190)
            func_002D7AC8(0, 0);
        if (func_002CBAE0() != 0) {
            if (m->phase == 0)
                m->phase = 1;
            return;
        }
    }
    if (m->phase == 0) {
        for (i = 0; i < 14; i++) {
            o = m->screen->slots[i];
            if (o != 0 && o->cb8 != 0)
                CALL_CB(o, 8, 0);
        }
        m->phase = m->phase + 1;
    }
    for (i = 0; i < 14; i++) {
        o = arr[i];
        if (o == 0 || o->fn0 == 0)
            continue;
        if ((char *)o == D_00259198)
            func_002CCED0();
        if (((SlotFn)arr[i]->fn0)(arr[i]))
            m->result = (m->mode == 4) ? 2 : 1;
    }
    p = m->screen;
    if (p != 0 && p->next != 0) {
        o = p->cur;
        if (o->cbC != 0)
            CALL_CB(o, 0xC, 1);
        p = m->screen;
        p->cur = p->next;
        m->screen->next = 0;
        o = m->screen->cur;
        if (o->cb8 != 0)
            CALL_CB(o, 8, 1);
    }
    if (m->target == 0)
        return;
    if (m->screen != m->target)
        func_002E5E58(0x12, 0, 0);
    else
        func_002E5E58(0x11, 0, 0);
    for (i = 0; i < 14; i++) {
        o = m->screen->slots[i];
        if (o != 0 && o->cbC != 0)
            CALL_CB(o, 0xC, 0);
    }
    m->old = m->screen;
    m->state = 3;
    m->phase = 0;
    m->screen = 0;
}
