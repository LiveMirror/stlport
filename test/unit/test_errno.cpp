#include <errno.h>

#include <errno.h> // not typo, check errno def/undef/redef

int check()
{
  if ( errno != 0 ) {
    return 1;
  }

/* Note: in common, you can't write ::errno or std::errno,
 * due to errno in most cases is just a macro, that frequently
 * (in MT environment errno is a per-thread value) expand to something like
 * (*__errno_location()). I don't know way how masquerade such
 * things: name of macro can't include ::.
 *
 *                - ptr, 2005-03-30
 */
#if 0
  if ( ::errno != 0 ) {
    return 1;
  }
  if ( std::errno != 0 ) {
    return 1;
  }
#endif

  return 0;
}
