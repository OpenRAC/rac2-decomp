/* func_US2_L00_00375270, the USA v2.00 copy of func_L00_00373F48: the same C, where rename func_002FB1A0 becomes func_US2_002FC008. */
#include "common.h"

/* Purchase confirmation states of the shop menu. Needs -G64 (gp-relative runtime menu parameters). */
typedef struct { int value; int pad[3]; } PurchaseRow;
typedef union {
    struct { char pad[0x80]; int index, state; } head;
    struct { char prefix[0x140]; PurchaseRow rows[0]; } category;
    struct { char prefix[0x144]; PurchaseRow rows[0]; } group;
    struct { char prefix[0x148]; PurchaseRow rows[0]; } cost;
} PurchaseModel;
extern PurchaseModel D_L00_0022F7C0;
extern char D_00138180[];
/* Retail rereads this byte between its bit test and update at 003742B0/003742C4. */
extern unsigned char D_001A7A80[] MACRO_ADDR;
extern unsigned char D_00139568[];
typedef struct { char pad[0x98]; int flag[3]; char tail[0x3C]; } Metadata;
extern char D_L00_00262570[];
/* Runtime menu parameters; the element count belongs to the selected menu. */
extern int D_L00_001AD4F0[] SDATA(D_L00_001AD4F0);
extern void ref_L00_00373F48_00(void);
extern int func_002B0D70(void);
extern int func_002E5CF8(int, int, char *);
extern int func_00288FB8(int);
extern void func_002F88D8(void *);
extern int func_L00_00326950(int);
extern void func_L00_002F5890(int);
extern void func_002F73A8(void);
extern void func_US2_002FC008(void);

void func_US2_L00_00375270(int *answer) {
    PurchaseModel *model = &D_L00_0022F7C0;
    int cost = model->cost.rows[model->head.index].value;
    int state = model->head.state;
    int category;
    int group;
    int enabled;
    if (state == 1) {
        if (*(int *)((char *)model + 0x740) != 0) {
            ref_L00_00373F48_00();
            D_L00_0022F7C0.head.state = 2;
        } else D_L00_0022F7C0.head.state = 0;
    } else if (state == 2) {
        if (*(unsigned int *)(D_00138180 + 0x1C4) & 0x10) {
            *answer = 0;
            D_L00_0022F7C0.head.state = 4;
        } else if (*(unsigned int *)(D_00138180 + 0x1C4) & 0x40)
            D_L00_0022F7C0.head.state = 3;
    } else if (state == 3) {
        *answer = 0;
        if (func_002B0D70() < cost) {
            func_002E5CF8(2, 17, *(char **)((char *)model + 0x28));
            D_L00_0022F7C0.head.state = 4;
        } else {
            int g = D_L00_0022F7C0.group.rows[model->head.index].value;
            int c = D_L00_0022F7C0.category.rows[model->head.index].value;
            if ((unsigned long)D_001A7A80[g] & ((1U << (c * 2)) & 255UL)) *answer = 0;
            else *answer = 1;
            D_L00_0022F7C0.head.state = 4;
        }
    } else if (state == 4) {
        if (*answer != 0) {
        if (func_002B0D70() >= cost) {
            func_002F88D8((void *)func_00288FB8(0x2c61));
            func_002E5CF8(7, 17, *(char **)((char *)model + 0x28));
            func_L00_00326950(cost);
            func_L00_002F5890(D_L00_001AD4F0[model->head.index]);
            category = D_L00_0022F7C0.category.rows[D_L00_0022F7C0.head.index].value;
            group = D_L00_0022F7C0.group.rows[D_L00_0022F7C0.head.index].value;
            switch (category) {
            case 0: enabled = ((Metadata *)(D_L00_00262570 + D_00139568[group] * 0xE0))->flag[0]; break;
            case 1: enabled = ((Metadata *)(D_L00_00262570 + D_00139568[group] * 0xE0))->flag[1]; break;
            case 2: enabled = ((Metadata *)(D_L00_00262570 + D_00139568[group] * 0xE0))->flag[2]; break;
            default: enabled = 0; break;
            }
            if (enabled) { int t = (1 << (category * 2)) | D_001A7A80[group]; D_001A7A80[group] = t; }
            {
            int category2 = D_L00_0022F7C0.category.rows[D_L00_0022F7C0.head.index].value;
            int group2 = D_L00_0022F7C0.group.rows[D_L00_0022F7C0.head.index].value;
            int enabled2;
            switch (category2) {
            case 0: enabled2 = ((Metadata *)(D_L00_00262570 + D_00139568[group2] * 0xE0))->flag[0]; break;
            case 1: enabled2 = ((Metadata *)(D_L00_00262570 + D_00139568[group2] * 0xE0))->flag[1]; break;
            case 2: enabled2 = ((Metadata *)(D_L00_00262570 + D_00139568[group2] * 0xE0))->flag[2]; break;
            default: enabled2 = 0; break;
            }
            if (enabled2) {
                unsigned long m = (1U << (category2 * 2)) & 255UL;
                if ((unsigned long)D_001A7A80[group2] & m) {
                    int t = (1 << (category2 * 2 + 1)) | D_001A7A80[group2];
                    D_001A7A80[group2] = t;
                }
            }
            }
            func_002F73A8();
        } else {
            func_002F88D8((void *)func_00288FB8(0x2c62));
            func_002E5CF8(0, 17, *(char **)((char *)model + 0x28));
        }
        } else func_002E5CF8(0, 17, *(char **)((char *)model + 0x28));
        D_L00_0022F7C0.head.state = 0;
        func_US2_002FC008();
    }
}
