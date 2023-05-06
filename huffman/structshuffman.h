#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define Max_table 256

typedef struct tree TREE;
typedef struct descompressed_tree TREE_D;
