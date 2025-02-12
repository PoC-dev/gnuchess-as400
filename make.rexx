/*
 * Compile GNU Chess. Run:
 * SBMJOB CMD(STRREXPRC SRCMBR(MAKE) SRCFILE(GNUCHESS/QREXSRC)) JOB(CMPLCHESS)
 */
"CHGCURLIB CURLIB(GNUCHESS)"
"CRTCMOD MODULE(ATAK) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(BOOK) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(CMD) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(EPD) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(EVAL) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(GENMOVE) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(HASH) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(HUNG) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(INIT) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(ITERATE) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(MAIN) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(MOVE) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(NULL) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(OUTPUT) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(PGN) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(PLAYERS) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(PLAYERS) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(QUIESCE) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(RANDOM) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(REPEAT) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(SEARCH) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(SOLVE) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(SORT) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(SWAP) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(TEST) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(TTABLE) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(UTIL) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTCMOD MODULE(VERSION) INLINE(*ON) OPTIMIZE(*FULL) SYSIFCOPT(*ALL)"
"CRTPGM PGM(GNUCHESS) MODULE(*CURLIB/*ALL) ENTMOD(*CURLIB/MAIN) ACTGRP(*NEW)"
