#include "include_asm.h"



extern float func_002A7878_1(float low, float high);
typedef unsigned char L00_0037F7E8_u8;
extern L00_0037F7E8_u8 *func_002A08A0(void);
extern L00_0037F7E8_u8 *D_L00_001B1EA8 __attribute__((sda));
extern L00_0037F7E8_u8 ref_L00_001B267C_00[] __attribute__((sda));
extern unsigned char D_001A7B2A __attribute__((sda));
typedef struct L00_0038BD00_Kind {
    unsigned char pad00[0x46];
    short type;
} L00_0038BD00_Kind;
typedef struct L00_0038BD00_Node {
    unsigned char pad00[0x20];
    unsigned char mode;
    unsigned char pad21[3];
    L00_0038BD00_Kind *kind;
    struct L00_0038BD00_Node *next;
} L00_0038BD00_Node;
typedef struct {
    unsigned char pad[0x2290];
    int value;
} D_00189E20_Struct;
extern D_00189E20_Struct D_00189E20;
extern float func_00282E48(char *object, char *other);
extern int func_003022A0(char *object, int value, float first, float second);
extern int func_L00_0031F2B0(char *object);
extern int func_L00_003D1B50(char *value);

/* Walk the level's node list from D_L00_001B1EA8: each node's own measure is
 * compared with the limit (2.7, or 10.0 when D_001A7B2A is set); a node of kind
 * 0x13 is then handed to func_003022A0, any other node to its own handler. A mode
 * of 0xFE or 0xFD, or a null next pointer, ends the walk. */
void func_PAL_L00_0038EDD8(char *object)
{
    L00_0038BD00_Node *s0;
    float limit;
    float step;
    float value;
    int mode;
    int result;
    L00_0038BD00_Kind *kind;

    limit = 2.7f;
    if (D_001A7B2A != 0)
        limit = 10.0f;
    s0 = (L00_0038BD00_Node *)D_L00_001B1EA8;
    if (s0 == 0)
        return;
    step = 0.01745329424738884f;
    while (1) {
        mode = s0->mode;
        if (mode == 0xFE)
            return;
        if (mode == 0xFD)
            return;
        if (s0 != 0 && (kind = s0->kind) != 0 && kind->type == 0x13) {
            value = func_00282E48((char *)s0 + 0x10, object + 0x10);
            if (value < limit) {
                value = func_002A7878_1(-30.0f, 30.0f);
                result = func_003022A0((char *)s0, D_00189E20.value, value * step, 0.0f);
            } else {
                s0 = s0->next;
                goto next;
            }
        } else {
            if (func_L00_0031F2B0((char *)s0) == 0) {
                s0 = s0->next;
                goto next;
            }
            value = func_00282E48((char *)s0 + 0x10, object + 0x10);
            if (value < limit) {
                result = func_L00_003D1B50((char *)s0);
            } else {
                s0 = s0->next;
                goto next;
            }
        }
        if (result != 0)
            return;
        s0 = s0->next;
next:
        /* The walk's end test: the goto above reaches it with the next pointer
         * already loaded, which is the shape retail's code has. */
        if (s0 == 0)
            return;
    }
}

