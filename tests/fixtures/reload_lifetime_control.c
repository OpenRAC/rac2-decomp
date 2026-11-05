/* Authored lifetime controls for the actual patched GCC predicate, not game code. */
#include <string.h>
#define MAX_RECOG_OPERANDS 8
#define REG 1
#define NULL_RTX ((rtx)0)
typedef unsigned long long HARD_REG_SET;
#define TEST_HARD_REG_BIT(set, n) (((set) >> (n)) & 1)
#define IOR_COMPL_HARD_REG_SET(dst, src) ((dst) |= ~(src))
#define COPY_HARD_REG_SET(dst, src) ((dst) = (src))
typedef struct Node { int code, regno, width, value; } Node;
typedef Node *rtx;
#define GET_CODE(x) ((x)->code)
#define REGNO(x) ((x)->regno)
#define GET_MODE(x) ((x)->width)
#define HARD_REGNO_NREGS(reg, mode) (mode)
static int true_regnum(rtx x) { return x->regno; }
static int rtx_equal_p(rtx a, rtx b) { return a == b; }
enum reload_type {
    RELOAD_FOR_OTHER_ADDRESS, RELOAD_OTHER, RELOAD_FOR_INPADDR_ADDRESS,
    RELOAD_FOR_INPUT_ADDRESS, RELOAD_FOR_INPUT, RELOAD_FOR_OPADDR_ADDR,
    RELOAD_FOR_OPERAND_ADDRESS, RELOAD_FOR_OUTADDR_ADDRESS,
    RELOAD_FOR_OUTPUT_ADDRESS, RELOAD_FOR_INSN, RELOAD_FOR_OUTPUT
};
static Node zero, value_a, value_b, output;
static rtx const0_rtx = &zero;
static HARD_REG_SET reload_reg_used, rac2_reload_unavailable;
static int n_reloads, reload_opnum[4];
static rtx reload_reg_rtx[4], reload_in[4], reload_out[4], reload_out_reg[4];
static enum reload_type reload_when_needed[4];

static void begin_insn(HARD_REG_SET available)
{
    reload_reg_used = 0;
    IOR_COMPL_HARD_REG_SET(reload_reg_used, available);
    COPY_HARD_REG_SET(rac2_reload_unavailable, reload_reg_used);
    n_reloads = 0;
    memset(reload_reg_rtx, 0, sizeof(reload_reg_rtx));
    memset(reload_in, 0, sizeof(reload_in));
    memset(reload_out, 0, sizeof(reload_out));
    memset(reload_out_reg, 0, sizeof(reload_out_reg));
}

/* INSERT_ACTUAL_PREDICATE */

#define CHECK(condition, error) do { if (!(condition)) return error; } while (0)
int main(void)
{
    Node own = {REG, 2, 1, 0}, overlapping = {REG, 2, 2, 0};
    begin_insn((1ULL << 2) | (1ULL << 3) | (1ULL << 4));
    n_reloads = 1;
    reload_reg_rtx[0] = &own;
    reload_in[0] = &value_a;
    reload_out[0] = &output;
    reload_when_needed[0] = RELOAD_OTHER;
    /* Allocation marks its own register; this is not an interference edge. */
    reload_reg_used |= 1ULL << 2;
    CHECK(reload_reg_free_for_value_p(2, 0, RELOAD_OTHER, &value_a, &output, 0, 0), 40);

    /* A live/early-clobbered register is unavailable even without another reload. */
    begin_insn(1ULL << 3);
    CHECK(!reload_reg_free_for_value_p(2, 0, RELOAD_OTHER, &value_a, &output, 0, 0), 41);

    begin_insn((1ULL << 2) | (1ULL << 3) | (1ULL << 4));
    n_reloads = 2;
    reload_reg_rtx[1] = &own;
    reload_in[1] = &value_b;
    reload_out[1] = &output;
    reload_when_needed[1] = RELOAD_OTHER;
    CHECK(!reload_reg_free_for_value_p(2, 0, RELOAD_OTHER, &value_a, &output, 0, 0), 42);

    /* Equal, read-only input values may share; output lifetimes may not. */
    reload_in[1] = &value_a;
    reload_out[1] = 0;
    reload_when_needed[1] = RELOAD_FOR_INPUT;
    CHECK(reload_reg_free_for_value_p(2, 0, RELOAD_FOR_INPUT, &value_a, 0, 0, 0), 43);
    reload_reg_rtx[1] = &overlapping;
    reload_in[1] = &value_b;
    reload_out[1] = &output;
    reload_when_needed[1] = RELOAD_FOR_OUTPUT;
    CHECK(!reload_reg_free_for_value_p(3, 0, RELOAD_OTHER, &value_a, &output, 0, 0), 44);
    CHECK(reload_reg_free_for_value_p(4, 0, RELOAD_OTHER, &value_a, &output, 0, 0), 45);
    return 0;
}
