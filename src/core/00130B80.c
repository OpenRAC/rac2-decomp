#include "common.h"
#include "structs.h"

/* sceIpuStopDMA: request the IPU-in (D4/toIPU) DMA channel to stop
 * (func_00130B18(1)), save its MADR/TADR/QWC/CHCR into env[0..3], wait for
 * the IPU's queued-command count (IPU_CTRL bits 4-7) to drain, stop the
 * IPU-out (D3/fromIPU) channel (func_00130AB0(0)) and save its
 * MADR/QWC/CHCR plus IPU_BP and IPU_CTRL into env[4..8]. */
extern void ipu_write_in_dma_control(unsigned int);

extern void ipu_write_out_dma_control(unsigned int);

/* rac1-decomp src/core/0012CC90.c: func_0012CD60 */
/* Stops both picture DMA channels and saves their registers into a block. */
void sceIpuStopDMA(unsigned int *env) {
    ipu_write_in_dma_control(1);
    env[0] = D4_MADR;
    env[1] = D4_TADR;
    env[2] = D4_QWC;
    env[3] = D4_CHCR;
    while ((IPU_CTRL & 0xF0) != 0) {
    }
    ipu_write_out_dma_control(0);
    env[4] = D3_MADR;
    env[5] = D3_QWC;
    env[6] = D3_CHCR;
    env[7] = IPU_BP;
    env[8] = IPU_CTRL;
}
