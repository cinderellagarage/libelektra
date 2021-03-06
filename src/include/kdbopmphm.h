#ifndef OPMPHM_H
#define OPMPHM_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * The Order Preserving Minimal Perfect Hash Map (OPMPHM) first maps each key name to a k-tuple, k is stored in OPMPHMTUPLE.
 * Each element of the k-tuples is in the range 0 to width. The width (abbreviated with w) determines how many keys can fit in the OPMPHM.
 * w^OPMPHMTUPLE is the maximum number of keys that fit in. w is set dynamically to the minimum value that:
 *
 * w^OPMPHMTUPLE > opmphmRatio * n
 *
 * opmphmRatio should never be less than 1.
 *
 */
#define OPMPHMTUPLE 7
extern double opmphmRatio;


/**
 * Saves a k-tuple in h[] and tells the OPMPHM the return value of each element, only needed during build.
 */
typedef struct
{
	size_t h[OPMPHMTUPLE]; /*!< the k-tuple filled by the OPMPHM with the hash function values */
	size_t order;	  /*!< the desired return value */
} OpmphmOrder;

/**
 * Only needed for Initialisation.
 */
typedef const char * (*opmphmGetString) (void *);
typedef struct
{
	opmphmGetString getString; /*!< Function pointer used to extract the key name from the data. */
	void ** data;		   /*!< The data */
	uint32_t initSeed;	 /*!< seed for random actions */
} OpmphmInit;


/**
 * Opmphm represents the final OPMPHM.
 * This struct is needed for the lookup, during the lookup the key name gets hashed OPMPHMTUPLE times
 * with different seeds from opmphmHashFunctionSeeds.
 */
typedef struct
{
	uint32_t opmphmHashFunctionSeeds[OPMPHMTUPLE]; /*!< the seeds for the tree hash function calls */
} Opmphm;

// build functions
OpmphmOrder ** opmphmInit (Opmphm * opmphm, OpmphmInit * init, OpmphmOrder * order, size_t n);

/**
 * Hash function
 * By Bob Jenkins, May 2006
 * http://burtleburtle.net/bob/c/lookup3.c
 */

#define OPMPHM_HASHFUNCTION_ROT(x, k) (((x) << (k)) | ((x) >> (32 - (k))))

#define OPMPHM_HASHFUNCTION_FINAL(a, b, c)                                                                                                 \
	{                                                                                                                                  \
		c ^= b;                                                                                                                    \
		c -= OPMPHM_HASHFUNCTION_ROT (b, 14);                                                                                      \
		a ^= c;                                                                                                                    \
		a -= OPMPHM_HASHFUNCTION_ROT (c, 11);                                                                                      \
		b ^= a;                                                                                                                    \
		b -= OPMPHM_HASHFUNCTION_ROT (a, 25);                                                                                      \
		c ^= b;                                                                                                                    \
		c -= OPMPHM_HASHFUNCTION_ROT (b, 16);                                                                                      \
		a ^= c;                                                                                                                    \
		a -= OPMPHM_HASHFUNCTION_ROT (c, 4);                                                                                       \
		b ^= a;                                                                                                                    \
		b -= OPMPHM_HASHFUNCTION_ROT (a, 14);                                                                                      \
		c ^= b;                                                                                                                    \
		c -= OPMPHM_HASHFUNCTION_ROT (b, 24);                                                                                      \
	}

#define OPMPHM_HASHFUNCTION_MIX(a, b, c)                                                                                                   \
	{                                                                                                                                  \
		a -= c;                                                                                                                    \
		a ^= OPMPHM_HASHFUNCTION_ROT (c, 4);                                                                                       \
		c += b;                                                                                                                    \
		b -= a;                                                                                                                    \
		b ^= OPMPHM_HASHFUNCTION_ROT (a, 6);                                                                                       \
		a += c;                                                                                                                    \
		c -= b;                                                                                                                    \
		c ^= OPMPHM_HASHFUNCTION_ROT (b, 8);                                                                                       \
		b += a;                                                                                                                    \
		a -= c;                                                                                                                    \
		a ^= OPMPHM_HASHFUNCTION_ROT (c, 16);                                                                                      \
		c += b;                                                                                                                    \
		b -= a;                                                                                                                    \
		b ^= OPMPHM_HASHFUNCTION_ROT (a, 19);                                                                                      \
		a += c;                                                                                                                    \
		c -= b;                                                                                                                    \
		c ^= OPMPHM_HASHFUNCTION_ROT (b, 4);                                                                                       \
		b += a;                                                                                                                    \
	}
uint32_t opmphmHashfunction (const void * key, size_t length, uint32_t initval);

/* Random */

uint32_t opmphmRandom (unsigned int * seedp);

/**
* @defgroup datastructs Private Datastructures
* @brief Private Datastructures
*
* These datastructures can be used within Elektra’s ecosystem.
*
* The requirements are described in doc/help/elektra-data-structures.md.
*/


/**
 *
 * @defgroup vstack Vstack
 * @ingroup datastructs
 *
 * The Vstack structure.
 *
 * A stack implementation with dynamical memory allocation.
 * The space gets doubled if full and reduced by half if used only a quarter of it,
 * but not less than minSize.
 */

typedef struct
{
	size_t minSize; /*!< the minimal size of the stack > */
	size_t size;    /*!< The maximal size of the stack */
	void ** data;   /*!< The data array */
	void ** head;   /*!< The stack pointer, which gets incremented or decremented after each push or pop. */
} Vstack;

Vstack * elektraVstackInit (size_t minSize);
int elektraVstackPush (Vstack * stack, void * data);
void * elektraVstackPop (Vstack * stack);
int elektraVstackIsEmpty (const Vstack * stack);
void elektraVstackDel (Vstack * stack);
int elektraVstackClear (Vstack * stack);


typedef int (*VheapComp) (void *, void *);
/**
 *
 * @defgroup vheap Vheap
 * @ingroup datastructs
 *
 * The Vheap structure.
 *
 * A heap is a Data structure which keeps the data ordered.
 * Elements can only be retrieved in this order! Insertions and retrieves need log (n).
 *
 * This implementation allocates memory dynamically.
 * The space gets doubled if full and reduced by half if used only a quarter of it,
 * but not less than minSize.
 *
 * To construct a max heap the comparison function VheapComp (a, b), must return
 * 1 on a > b and 0 otherwise. For a min heap 1 on a < b and 0 otherwise.
 */
typedef struct
{
	size_t minSize; /*!< the minimal size of the heap > */
	size_t size;    /*!< The size of the heap */
	size_t count;   /*!< The current number of elements in the heap */
	VheapComp comp; /*!< The comparison function */
	void ** data;   /*!< The data array */
} Vheap;

Vheap * elektraVheapInit (VheapComp comp, size_t minSize);
void elektraVheapDel (Vheap * vheap);
int elektraVheapClear (Vheap * vheap);
int elektraVheapIsEmpty (const Vheap * vheap);
int elektraVheapInsert (Vheap * vheap, void * data);
void * elektraVheapRemove (Vheap * vheap);

#endif
