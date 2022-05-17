
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

struct Listnode
{
    uint8_t *data;
    struct Listnode *next;
};

struct IList
{
    uint8_t (*init)(struct Listnode *list);
    uint8_t (*append)(struct Listnode *list, uint8_t *data);
};

struct Utils
{
    struct IList *ilist;
};

extern struct IList ilist;
extern struct Utils utils;

#endif