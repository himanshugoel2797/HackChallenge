#ifndef _MD5_H_
#define _MD5_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef union uwb {
    unsigned w;
    unsigned char b[4];
} WBunion;

typedef unsigned Digest[4];


typedef unsigned (*DgstFctn)(unsigned a[]);


#endif /* end of include guard: _MD5_H_ */
