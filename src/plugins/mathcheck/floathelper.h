/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

#include <kdb.h> // for ssize_t included within kdbos.h

#define ELEKTRA_DEFAULT_DECIMAL_POINT '.'
#define MAX_CHARS_DOUBLE 24

char * elektraFtoA (char *, ssize_t, double);

double elektraEFtoF (const char *);
