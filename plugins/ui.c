
#include <fcntl.h>
#include <unistd.h>
#include <curses.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/utils.h"
#include "../includes/plugins.h"

static int readline(int fd, uint8_t *buffer, int size)
{
    int count = 0;

    if (count >= size) return -1;

    while (read(fd, buffer + count, 1) > 0)
    {
        if (*(buffer + count) == '\n') break;
        count++;
        if (count >= size) break;
    }
    *(buffer + count) = '\0';
    
    return count;
}

uint8_t init_ui(struct Ui *ui, uint8_t *filename)
{
    int fd = 0;

    uint8_t buffer[BUFSIZE] = { 0 };
    uint8_t *data = NULL;

    utils.ilist->init(&(ui->lines));

    if ((fd = open(filename, O_RDONLY)) == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (readline(fd, buffer, sizeof(buffer)) > 0)
    {
        data = malloc(strlen(buffer) + 1);
        memcpy(data, buffer, strlen(buffer) + 1);
        utils.ilist->append(&(ui->lines), data);
    }

    return 0;
}

uint8_t output_ui(struct Ui *ui)
{
    uint8_t buffer[BUFSIZE] = { 0 };
    uint8_t *temp = NULL;

    struct Listnode *p = &(ui->lines);

    while (p->next)
    {
        p = p->next;
        memcpy(buffer, p->data, strlen(p->data) + 1);
        temp = strtok(buffer, " ");

        for (uint8_t i = 0; temp; i++)
        {
            switch (i)
            {
            case 0: ui->row = atoi(temp); break;
            case 1: ui->col = atoi(temp); break;
            case 2: ui->count = atoi(temp); break;
            case 3: ui->ch = temp[0]; break;
            }       
            temp = strtok(NULL, " ");
        }

        for (uint8_t i = 0; i < ui->count; i++)
        {
            move(ui->row, ui->col + i);
            addch(ui->ch);
        }
    }
    refresh();

    return 0;
}