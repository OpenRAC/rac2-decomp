#include "names.h"
/* func_002B8548: the two-word request block at 0x1B1D70 is an sda array (assembler
 * macro stores through $at) whose address is held in a local, as retail keeps it in $s3;
 * the callees are func_001282A8, func_001288C0 and func_00128900(void *, char *), whose
 * result is stored, and the two clears of each state are in retail's store order. */
typedef struct {
    char reserved[0x194];
    int f194;
    int f198;
    int f19C;
} State_2B8548;

extern State_2B8548 g_pad_state;
extern State_2B8548 D_00138500;
extern int D_001B1D70[2] __attribute__((sda));

extern int sceDbcInit(void *);
extern int pad_init_socket_table(int);
extern int scePad2CreateSocket(void *, char *);

/* Sets up both controller ports at start-up. */
void pad_init_ports(void *padInfo)
{
    int *requestBlock = D_001B1D70;
    int portMode = 2;

    sceDbcInit(padInfo);
    pad_init_socket_table(0);
    D_001B1D70[0] = portMode;
    D_001B1D70[1] = 0;
    g_pad_state.f194 = scePad2CreateSocket(requestBlock, (char *)&g_pad_state);
    g_pad_state.f198 = 0;
    g_pad_state.f19C = 0;
    D_001B1D70[0] = portMode;
    D_001B1D70[1] = 1;
    D_00138500.f194 = scePad2CreateSocket(requestBlock, (char *)&D_00138500);
    D_00138500.f198 = 0;
    D_00138500.f19C = 0;
}
