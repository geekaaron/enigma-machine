
#include <curses.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/utils.h"
#include "../includes/plugins.h"

uint8_t init_keyboard(struct Keyboard *keyboard, struct Ui *ui, uint8_t *sign)
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
            case 4:
                if (!strcmp(temp, sign))
                {
                    keyboard->position[ui->ch - 'A'][0] = ui->row;
                    keyboard->position[ui->ch - 'A'][1] = ui->col;
                }
                break;
            }       
            temp = strtok(NULL, " ");
        }
    }

    return 0;
}

uint8_t output_keyboard(struct Keyboard *keyboard, uint8_t input, uint8_t on)
{
    if (input >= NUMS) return 0xff;

    if (on) attron(A_BLINK);
    else attroff(A_BLINK);

    move(keyboard->position[input][0], keyboard->position[input][1]);
    addch(input + 'A');
    move(keyboard->position[input][0], keyboard->position[input][1]);
    refresh();

    return 0;
}