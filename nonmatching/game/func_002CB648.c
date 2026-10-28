/* func_002CB648 - 388 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002CB648: draft 404 B vs 388 (needs -G8 file, 002CB648-g8.c with "-O2
   -G8 -ffunction-sections"). Retail walks a flags pointer s4=&D_00210A40+0xC
   (stride 4) plus i (s6) and j=2i (s3), keeps &D_00210A40 in s5 and hoists
   the 0x80FFDE8D colour in s7. Mine uses index/base regs differently (struct
   index, pointer walk and separate D_00210A4C[] symbol all tried). ~80 diff
   lines. */

typedef struct { int count; int selected; int *items; int flags[1]; } MenuList;

extern MenuList D_00210A40;
extern int D_00210A4C[];
extern int D_001AB8F4 __attribute__((sda));
extern int D_001AB8F8 __attribute__((sda));
extern char D_001AB900[];
extern void func_0027DDC0(int, int, int, int);
extern int func_00288FB8(int);
extern void func_00115DA8(char *, char *, int, int);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0027FAA8(int, int, unsigned long, char *, int);

void func_002CB648(void)
{
    char buf[0x100];
    int i = 0;
    int j = 0;
    int row;
    int a;
    int b;

    buf[0xFF] = 0;
    func_0027DDC0(0, 0, 0, 0x60);
    if (D_00210A40.count * 2 >= 0) {
        do {
            if (D_00210A4C[i] != 0) {
                row = (i == 0x18) ? 0x24 : j;
                a = func_00288FB8(D_00210A40.items[j + 1]);
                b = func_00288FB8(D_00210A40.items[j]);
                func_00115DA8(buf, D_001AB900, a, b);
                func_0027EB88(D_001AB8F8 + row * D_001AB8F4, D_001AB8F8 + row * D_001AB8F4 + 0xF, 0x40, 0x1C0, 0x60, 0x442D00);
                func_0027FAA8(0x100, D_001AB8F8 + row * D_001AB8F4,
                              D_00210A4C[i] == 0 ? 0x80000000u : (D_00210A40.selected == i ? 0x80FFDE8Du : 0x80808080u),
                              buf, -1);
            }
            j += 2;
            i++;
        } while (D_00210A40.count * 2 >= j);
    }
}
