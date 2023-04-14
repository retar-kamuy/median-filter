#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>

#define MAX_IMAGE_WIDTH     514
#define MAX_IMAGE_HEIGHT    514

#define FILTER_V_SIZE   3
#define FILTER_H_SIZE   3

#define SORT_SIZE       16
#define SORT_LOG_SIZE   4   // log2(SORT_SIZE)

typedef unsigned char      		U8;
typedef unsigned short     		U16;
typedef unsigned int       		U32;

typedef signed char        		I8;
typedef signed short       		I16;
typedef signed int         		I32;

#endif  // COMMON_HPP_
