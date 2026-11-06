/* func_US2_0033E8B0, the USA v2.00 copy of func_0033D868: the same C, where template sibling func_US2_L00_004348C8; rename-macro func_0033AE28 becomes func_US2_0033BE70; rename Fc558ca70_D_001A7B95 becomes D_US2_001A7BBA; rename Fc558ca70_D_001A7B94 becomes D_US2_001A7BBB. */
/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
/* makes two float-binding calls, then toggles one of two global flag bytes selected by an object field and returns bit 6 of the flag word */
/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
/* resets a sub-object, applies a two-float transform, and when bit 6 of flags is set and an int field is zero calls a mode setter and toggles a global byte */
/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern void Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char D_US2_001A7BBA __attribute__((sda));
extern volatile unsigned char D_US2_001A7BBB __attribute__((sda));

int func_US2_0033E8B0(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    Fc558ca70_FUN_0033AE28(p);
    q = *(float **)(a0 + 732);
    Fc558ca70_FUN_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 728)) {
        case 0:
            D_US2_001A7BBA = D_US2_001A7BBA == 0;
            break;
        case 1:
            D_US2_001A7BBB = D_US2_001A7BBB == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */

