/* func_L23_0041CA58: the level-22 routine func_L22_003A36A0 without its second probe loop. Its `% 3` result is unused, as in L22: retail keeps only the zero-divisor guard. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x230];
    int ids[47];
} State;

typedef struct {
    int count;
    int pad[3];
    TI128 pts[1];
} Rec;

extern Rec *D_L23_001FF300[];

extern void func_L23_0041CCC0(char *);
extern void func_L23_0041C7D8(void *, int);
extern int func_002A77E0(int);
extern void *func_00115484(void *, int, unsigned int);

void func_L23_0041CA58(char *obj) {
    int cumulative[47];
    int selected[7];
    struct {
        TI128 point, low, normal;
    } v;
    State *st = *(State **)(obj + 0x68);
    int total = 0, i, j, next, unused, chosen, duplicate;

    func_L23_0041CCC0(obj);
    func_002A77E0(3);
    func_00115484(selected, -1, 28);
    for (i = 0; i < 47; i++) {
        cumulative[i] = total;
        total += D_L23_001FF300[st->ids[i]]->count - 1;
    }
    for (i = 0; i < 7; i++) {
        duplicate = 1;
        do {
            chosen = func_002A77E0(total);
            for (j = 0; j < 7; j++) {
                if (chosen == selected[j]) {
                    duplicate = 1;
                    break;
                }
                if (j == 6) duplicate = 0;
            }
        } while (duplicate == 1);
        selected[i] = chosen;
        for (j = 0; j < 47; j = next) {
            if (j == 46) {
                qcopy_nc(&v.point, (char *)((chosen - cumulative[46]) * 16 + (int)D_L23_001FF300[st->ids[46]]) + 16);
                break;
            }
            next = j + 1;
            if (chosen >= cumulative[j] && chosen < cumulative[next]) {
                qcopy_nc(&v.point, (char *)((chosen - cumulative[j]) * 16 + (int)D_L23_001FF300[st->ids[j]]) + 16);
                break;
            }
        }
        if (j != 10 && j != 27 && j != 28 && j != 31 && j != 15) {
            unused = i % 3;
            func_L23_0041C7D8(&v.point, 0);
        }
    }
}
