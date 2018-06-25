/* inet_aton implementation for Windows */


#include <ctype.h> /* Windows needs this header file for the implementation of inet_aton() */
#include <assert.h>

/*
 * Check whether "cp" is a valid ascii representation of an Internet address
 * and convert to a binary address.  Returns 1 if the address is valid, 0 if
 * not.  This replaces inet_addr, the return value from which cannot
 * distinguish between failure and a local broadcast address.
 *
 * This implementation of the standard inet_aton() function was copied
 * (with trivial modifications) from the OpenBSD project.
 */
int inet_aton(const char *cp, struct in_addr *addr) {
  register unsigned int val;
  register int base, n;
  register char c;
  unsigned int parts[4];
  register unsigned int *pp = parts;

  assert (sizeof(val) == 4);

  c = *cp;
  for (;;) {
    /*
     * Collect number up to ``.''.
     * Values are specified as for C:
     * 0x=hex, 0=octal, isdigit=decimal.
     */
    if (!isdigit(c)) return(0);
    val = 0;
    base = 10;
    if (c == '0') {
      c = *++cp;
      if ((c == 'x') || (c == 'X')) {
        base = 16, c = *++cp;
      } else {
        base = 8;
      }
    }
    for (;;) {
      if (isascii(c) && isdigit(c)) {
          val = (val * base) + (c - '0');
          c = *++cp;
      } else if (base == 16 && isascii(c) && isxdigit(c)) {
          val = (val << 4) | (c + 10 - (islower(c) ? 'a' : 'A'));
          c = *++cp;
      } else {
          break;
      }
    }
    if (c == '.') {
      /* Internet format:
       *    a.b.c.d
       *    a.b.c    (with c treated as 16 bits)
       *    a.b    (with b treated as 24 bits) */
      if (pp >= parts + 3) return(0);
      *pp++ = val;
      c = *++cp;
    } else {
      break;
    }
  }
  /*
   * Check for trailing characters.
   */
  if (c != '\0' && (!isascii(c) || !isspace(c))) return (0);
  /*
   * Concoct the address according to
   * the number of parts specified.
   */
  n = pp - parts + 1;
  switch (n) {
    case 0:
      return (0);        /* initial nondigit */
    case 1:                /* a -- 32 bits */
      break;
    case 2:                /* a.b -- 8.24 bits */
      if ((val > 0xffffff) || (parts[0] > 0xff)) return (0);
      val |= parts[0] << 24;
      break;
    case 3:                /* a.b.c -- 8.8.16 bits */
      if((val > 0xffff) || (parts[0] > 0xff) || (parts[1] > 0xff)) return (0);
      val |= (parts[0] << 24) | (parts[1] << 16);
      break;
    case 4:                /* a.b.c.d -- 8.8.8.8 bits */
      if((val > 0xff) || (parts[0] > 0xff) || (parts[1] > 0xff) || (parts[2] > 0xff)) return (0);
      val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
      break;
  }
  if (addr) addr->s_addr = htonl(val);
  return (1);
}
