
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../includes/utils.h"

uint8_t init_list(struct Listnode *list)
{
    list->data = NULL;
    list->next = NULL;

    return 0;
}

uint8_t append_list(struct Listnode *list, uint8_t *data)
{
    struct Listnode *p = list;
    struct Listnode *node = NULL;

    if (!(node = (struct Listnode *)malloc(sizeof(struct Listnode))))
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;

    while (p->next) p = p->next; 
    p->next = node;

    return 0;
}