/* func_L05_0042AFE0: current720B catalogue body starts one instruction late.
 * US05 entry42AFEC begins SP-40 then LWC1 F0,26E8(gp), but +10 addsF1
 * before definingF1. Immediately preceding42AFE8 is LWC1 F1,26E4(gp).
 * Preceding42AFE0/4 are previous epilogue SP+10/NOP. A real pre-prologue
 * global load at42AFE8 would make the complete function724B.
 * Fresh audit2026-10-28 finds the same precedingF1 GP load at all12 carrying
 * placements in US/US2/PAL. No direct J/JAL, absolute-pointer or nearby
 * LUI+ADDI/ORI reference to42AFE0/8/C was found in US05; no direct-call proof
 * is claimed. Missing incomingF1 cannot be invented as an ordinary C argument.
 * Audit: workspace/workers/w03/work/large-w03-L05_0042AFE0-entry-audit.txt.
 * The body wraps five scalar animation phases into[-7,7], forms a sine/cosine
 * direction and calls BB10 plus four B2C0 draws. It remains its original ASM
 * marker, without catalogue changes, compiles or matching credit.
 */
