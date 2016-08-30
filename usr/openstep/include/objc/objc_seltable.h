#ident "@(#) objc_seltable.h, Rev 1.4, 97/03/17"
//
//	Copyright (c) 1995-1996, Sun Microsystems, Inc.
//	All rights reserved.

typedef struct objc_hash_elem {
        struct objc_hash_elem *next;
        char  *key;
        int index; // this index replaces the string selector;
        };
 
typedef struct objc_selector_info {
        unsigned long blobsize;
	unsigned long stringsize;
	unsigned long hashsize;
	unsigned long fullsize;
};

#define SELECTOR_FILE "objc_selector_table.bin"
#define SELECTOR_LIB  "libObjcSelector.so"
#define SELECTOR_TABLE_SIZE 1637

/* utilities */
static inline unsigned int _objc_strhash (const unsigned char *s)
{
  unsigned int hash = 0;

  /* Unroll the loop. */
  while (1)
    { 
      if (*s == '\0') 
        break;
      hash ^= *s++;
      if (*s == '\0') 
        break;
      hash ^= *s++ << 8;
      if (*s == '\0') 
        break;
      hash ^= *s++ << 16;
      if (*s == '\0') 
        break;
      hash ^= *s++ << 24;
    }
  
  return hash;
}

