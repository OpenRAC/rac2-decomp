#include "include_asm.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    unsigned char reserved_00[0x18];
    unsigned char enabled;
    unsigned char count;
    unsigned char kind;
    unsigned char reserved_1b[0x65];
    unsigned char payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;

typedef unsigned long Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags;

extern int ref_L00_00327858_02;

extern void ref_L00_00327858_03(void *owner, void *payload, int count);

extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags ref_L00_00327858_01(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context);

extern Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags ref_L00_00327858_00(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context);

/* Runs the stored action for an object depending on its kind, and switches the action off when it reports it is done. */
Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags func_002B1C20(void *owner, Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *context)
{
    Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchFlags result = 0;
    if (context->enabled == 1 && context->count != 0)
        ref_L00_00327858_03(owner, context->payload, context->count);
    switch (context->kind) {
    case 0:
    case 1:
    case 2:
        if (ref_L00_00327858_02 == 0)
            result = ref_L00_00327858_01(owner, context);
        else
            result = ref_L00_00327858_00(owner, context);
        break;
    default:
        break;
    }
    if ((result & 2) != 0) context->enabled = 0;
    return result;
}

/* func_002B1CC8 is in 002B1C20-steering.c. */

/* func_002B2A10 is in 002B1C20-gravity.c. */

/* func_002B3380 is in 002B1C20-effects-g8.c. */



