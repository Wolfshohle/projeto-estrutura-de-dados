#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <arpa/inet.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct tree TREE;
typedef struct descompressed_tree TREE_D;


//struct da arvore de compactacao
struct tree
{
    void *byte;
    long frequency;
    TREE *next, *left, *right;
};

//struct para arvore de descompactacao
struct descompressed_tree
{
    void *byte;
    TREE_D *left, *right;
};
