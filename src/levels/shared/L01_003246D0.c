#include "names.h"
/* Keep the key lookup as a canonical call rather than inlining its level copy. */
extern int func_L01_003246F8(int key);
extern void func_L01_003246A0(int index);

/* Looks up the table index for a key and then acts on that index. */
void func_L01_003246D0(int key)
{
    MarkTableEntryUsed(FindKeyInPairTable(key));
}
