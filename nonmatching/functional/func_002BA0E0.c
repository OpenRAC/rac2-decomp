/* functional: medium. Callback-table reconstruction; all 111 slots present, address-only initialiser. The near-miss draft below differs from retail by one word of code size and scheduling. Verified on one captured call only. */
/* Retained manual reconstruction, 2026-10-24.
 * Profile: -O2 -G0 -ffunction-sections.
 * Final measurements: us: 0/28 placements, exit1, 1476 compiled bytes; us2:
 * 0/28 placements, exit1, 1476 compiled bytes; pal: 0/28 placements, exit1,
 * 1476 compiled bytes.
 * Remaining: All 111 callback slots, including the two repeated
 * func_002B9380 entries, are reconstructed. The address-only initializer
 * leaves callback argument lists unspecified and does not call them.
 * Default, -g and -fno-gcse all produce 1476 versus 1472 bytes with
 * differing save/scheduling details.
 * Reopen with: Concrete callback-table source-lifetime or compiler
 * scheduling evidence resolving the one-word excess and delayed callee
 * saves; three tied profile trials are a stopping point.
 * No byte-match or linked-build credit is claimed.
 */
/* The table holds callback entry addresses; this initializer does not call them.
 * Empty parameter lists deliberately leave each callback's interface unspecified.
 * The consumed return type is likewise irrelevant at this address-only use. */
#define PARTICLE_UPDATES(X) \
 X(0, func_002BA6A0) \
 X(1, func_002BA978) \
 X(2, func_002BABE8) \
 X(3, func_002BAE48) \
 X(4, func_002BAF68) \
 X(5, func_002BB058) \
 X(6, func_002BB100) \
 X(7, func_002BB798) \
 X(8, func_002BB928) \
 X(9, func_002BBA38) \
 X(10, func_002BBB70) \
 X(11, func_002BBF40) \
 X(12, func_002BC510) \
 X(13, func_002BC8E8) \
 X(14, func_002BCA10) \
 X(15, func_002BCC58) \
 X(16, func_002BD0D0) \
 X(17, func_002BD390) \
 X(18, func_002BD398) \
 X(19, func_002BD508) \
 X(20, func_002BD5B0) \
 X(21, func_002BD9B0) \
 X(22, func_002B9288) \
 X(23, func_002BDEB0) \
 X(24, func_002BE150) \
 X(25, func_002BE400) \
 X(26, func_002BE7E8) \
 X(27, func_002BE928) \
 X(28, func_002BE9B8) \
 X(29, func_002BEBC8) \
 X(30, func_002BEE78) \
 X(31, func_002BF390) \
 X(32, func_002BF520) \
 X(33, func_002BF6F0) \
 X(34, func_002BF8F0) \
 X(35, func_002BFC50) \
 X(36, func_002BFE80) \
 X(37, func_002BFFE8) \
 X(38, func_002C00F8) \
 X(39, func_002C0200) \
 X(40, func_002C04C0) \
 X(41, func_002C0C78) \
 X(42, func_002C0E50) \
 X(43, func_002C14E0) \
 X(44, func_002C1840) \
 X(45, func_002C1B38) \
 X(46, func_002C1C88) \
 X(47, func_002C1DB8) \
 X(48, func_002C1E58) \
 X(49, func_002C1EF0) \
 X(50, func_002C1FC0) \
 X(51, func_002C2080) \
 X(52, func_002C2170) \
 X(53, func_002C23B8) \
 X(54, func_002C2658) \
 X(55, func_002C27B0) \
 X(56, func_002C28F8) \
 X(57, func_002C29A8) \
 X(58, func_002C2C80) \
 X(59, func_002C30F8) \
 X(60, func_002C3280) \
 X(61, func_002C3430) \
 X(62, func_002C37E0) \
 X(63, func_002C38A8) \
 X(64, func_002C38E0) \
 X(65, func_002C3B10) \
 X(66, func_002C3EE8) \
 X(67, func_002C4100) \
 X(68, func_002C43D0) \
 X(69, func_002C4500) \
 X(70, func_002C4788) \
 X(71, func_002C47F0) \
 X(72, func_002C4B10) \
 X(73, func_002C4B58) \
 X(74, func_002C4D20) \
 X(75, func_002C4F08) \
 X(76, func_002C5020) \
 X(77, func_002C5070) \
 X(78, func_002C5120) \
 X(79, func_002C5408) \
 X(80, func_002C5550) \
 X(81, func_002C58A8) \
 X(82, func_002C5D00) \
 X(83, func_002C6360) \
 X(84, func_002C64E0) \
 X(85, func_002B9380) \
 X(86, func_002C6868) \
 X(87, func_002C6A08) \
 X(88, func_002C6748) \
 X(89, func_002C6B80) \
 X(90, func_002C6EF0) \
 X(91, func_002C7058) \
 X(92, func_002C72A8) \
 X(93, func_002B9380) \
 X(94, func_002C7538) \
 X(95, func_002C7628) \
 X(96, func_002C7888) \
 X(97, func_002C7AE8) \
 X(98, func_002C7D58) \
 X(99, func_002C7F78) \
 X(100, func_002C8268) \
 X(101, func_002C8350) \
 X(102, func_002C8428) \
 X(103, func_002C85D8) \
 X(104, func_002C8610) \
 X(105, func_002C87B0) \
 X(106, func_002C8888) \
 X(107, func_002C8A38) \
 X(108, func_002C8CA0) \
 X(109, func_002C8F40) \
 X(110, func_002C90A0)
#define DECLARE_UPDATE(index, name) extern void name();
PARTICLE_UPDATES(DECLARE_UPDATE)
#undef DECLARE_UPDATE
extern void (*D_001F2340[])();
void func_002BA0E0(void)
{
#define STORE_UPDATE(index, name) D_001F2340[index] = name;
    PARTICLE_UPDATES(STORE_UPDATE)
#undef STORE_UPDATE
}
#undef PARTICLE_UPDATES
