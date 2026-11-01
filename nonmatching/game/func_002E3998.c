/* Closer C2, 1 November 2026: 576/572, one instruction off, -O2 -G8. Same as func_002E3BD8 with another second
 * callee and no tail; see that draft's note for the a3 copy that is left. Functional C stays in nonmatching/functional.
 */
typedef short s16;
typedef unsigned char u8;

extern unsigned char *D_001B22A8;
extern char D_00139370[];
extern int D_001ABDD8[2] __attribute__((sda));
extern int D_001ABDE0 __attribute__((sda));

extern void func_002E4388(void *, int, void *);
extern int func_002E3E54(int, int, int, int);
extern void func_002E40C8(int, int, int, int);
extern void func_0029CF58(int, int, int);
extern void func_0029CF78(void);

typedef struct {
    u8 pad[0x20];
    int w10;
    s16 h14, h16, h18, h1A, h1C, h1E;
} Rec;
typedef struct {
    int count;
} Obj;
#define R(o, k) ((Rec *)((char *)(o) + ((k) << 5)))

void func_002E3998(Obj *object)
{
    int count = object->count;
    u8 frame[count];
    int i;

    if (count == 0)
        return;
    func_002E4388((char *)object + 0x10, count, frame);
    *(int *)(D_001B22A8 + 0) = 0x30000007;
    *(int *)(D_001B22A8 + 4) = (int)D_00139370;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 0xC) = 0x50000007;
    D_001B22A8 = D_001B22A8 + 16;
    D_001ABDE0 = 1 - D_001ABDE0;
    if (frame[0] == 1)
        func_0029CF58(R(object, 0)->w10, R(object, 0)->h1E >> 4, D_001ABDD8[D_001ABDE0]);
    for (i = 0; i < object->count; i++) {
        if (frame[i] == 1)
            func_0029CF78();
        D_001ABDE0 = 1 - D_001ABDE0;
        if (i + 1 < object->count && frame[i + 1] == 1)
            func_0029CF58(R(object, i + 1)->w10, R(object, i + 1)->h1E >> 4, D_001ABDD8[D_001ABDE0]);
        if (frame[i] == 1) {
            int base = D_001ABDD8[1 - D_001ABDE0];
            int h, k, m, a, b;
            h = R(object, i)->h1C;
            m = R(object, i)->h18;
            k = R(object, i)->h1A;
            a = base + h; b = base + k;
            if (func_002E3E54(base + m, 0x70002000, R(object, i)->h14, h) == 0)
                func_002E40C8(R(object, i)->h16, a, b, 0x70002000);
        }
    }
}
