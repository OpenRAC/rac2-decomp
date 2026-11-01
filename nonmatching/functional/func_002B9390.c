/* functional: high. Same record walk and handler calls as retail, and the return address is stored in the same global slot; the cache-prefetch hint is omitted and the stack is used for what retail keeps in registers. */

typedef struct EventRecord {
    signed char handler;
    signed char flags;
    char padding[62];
} EventRecord;

extern EventRecord *D_001B1D90_g SDATA(D_001B1D90);
extern int D_001B1D98_g SDATA(D_001B1D98);
extern EventRecord *D_001B1DB0_g[2] SDATA(D_001B1DB0);
extern unsigned long long D_001B1DA8_g SDATA(D_001B1DA8);
extern void (*D_001F2340[])(EventRecord *);

void func_002B9390(void)
{
    EventRecord *record;
    EventRecord *end;

    D_001B1DA8_g = (unsigned int)__builtin_return_address(0);
    record = D_001B1D90_g;
    end = record + D_001B1D98_g + 1;
    D_001B1DB0_g[1] = end;
    while (record != end) {
        if (record->flags < 0) {
            record++;
            continue;
        }
        D_001B1DB0_g[0] = record + 1;
        D_001F2340[record->handler](record);
        record = D_001B1DB0_g[0];
        end = D_001B1DB0_g[1];
    }
}
