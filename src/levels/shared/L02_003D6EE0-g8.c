#include "common.h"
extern void func_002833F0(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00283678(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern int D_L02_001A9018 MACRO_ADDR;
extern unsigned short **D_L02_001A9014 MACRO_ADDR;
extern char *D_L02_001B3C1C[] __attribute__((sda));
void func_L02_003D6EE0(char *object)
{
    struct {
        float inverse[12];
        float rotation[12];
        float transposed[16];
    } frame __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    int index;
    unsigned short *entry;
    unsigned short *list;
    func_002833F0(frame.rotation, object + 0xf0);
    func_00283698(frame.transposed, frame.rotation);
    func_00283678(frame.inverse, frame.transposed);
    index = *(int *)(state + 0xb0);
    if (index != -1 && index < D_L02_001A9018) {
        list = D_L02_001A9014[index];
        if (list) {
            entry = list;
            do {
                int key = *entry & 0x7fff;
                char *record = D_L02_001B3C1C[0] + key * 64;
                if (func_00282E48(object + 0x10, record + 0x30) < 1.0f) {
                    *(short *)(state + 0x78) = key;
                    state[0x7c] = 1;
                    state[0x7a] = 1;
                    *(int *)(state + 0x70) = 0;
                    func_00282CF0(state + 0x60, record + 0x30, object + 0x10);
                    func_00283098(state + 0x60, state + 0x60, frame.inverse);
                    func_00283738(state + 0x30, frame.inverse, record);
                    break;
                }
            } while (*(short *)entry++ >= 0);
        }
    }
}
