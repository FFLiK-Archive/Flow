#pragma once
/* KSC5601 -> Unicode 2.0 mapping table, compressed for the 94*94 codeset. */
/* Generated based on  KSC5601.txt at
   ftp://ftp.unicode.org/Public/MAPPINGS/EASTASIA/KSC  */
/*
 * Unlike kuten-table, needed offset is 33 (0x21) instead of
 * 32 for 7-bit portion of each byte.  i.e., a Unicode
 * codepoint for KSC's codepoint (n, m) would be found at
 * index (n-33)*94+m-33.
 */
#include <SDL.h>

        /* # of entries in the table. */

static unsigned short convert_char_ksc5601_to_ucs2(unsigned char byte1, unsigned char byte2);


void han2unicode(const char *src, Uint16 *dest);
