
#include <curses.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/utils.h"
#include "../includes/plugins.h"

uint8_t init_rotor(struct Rotor *rotor, struct Ui *ui, uint8_t *sign)
{
    uint8_t buffer[BUFSIZE] = { 0 };
    uint8_t nsign[BUFSIZE] = { 0 };
    uint8_t csign[BUFSIZE] = { 0 };
    
    uint8_t *temp = NULL;
    uint8_t *current = NULL;
    uint8_t index = 0;

    struct Listnode *p = &(ui->lines);

    strcat(nsign, sign);
    strcat(nsign + strlen(sign), "-NUM");
    strcat(csign, sign);
    strcat(csign + strlen(sign), "-CHAR");

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
            case 3: ui->ch = temp[0]; current = temp; break;
            case 4:
                if (!strcmp(temp, nsign))
                {
                    rotor->row = ui->row;
                    rotor->col = ui->col;
                    rotor->current = atoi(current);
                }
                else if (!strcmp(temp, csign))
                {
                    rotor->connect[index++] = ui->ch - 'A';
                }
                break;
            }       
            temp = strtok(NULL, " ");
        }
    }
    refresh();

    return 0;
}

uint8_t turn_rotor(struct Rotor *rotor)
{
    if (++(rotor->current) >= NUMS)
    {
        rotor->current %= NUMS;
        return 1;
    }
    return 0;
}

static int get_index(uint8_t array[], uint8_t target)
{
    for (int i = 0; i < NUMS; i++)
    {
        if (array[i] == target) return i;
    }
    return -1;
}

uint8_t output_rotor(struct Rotor *rotor, uint8_t input, uint8_t direction)
{
    uint8_t real_input, real_output, reflect; 

    attroff(A_BLINK);
    move(rotor->row, rotor->col);
    printw("%02d", rotor->current);
    move(rotor->row, rotor->col);
    refresh();

    if (input >= NUMS) return 0xff;

    real_input = (input + rotor->current) % NUMS;
    if (direction == FORWARD)
    {
        real_output = rotor->connect[real_input] - rotor->current;
        if (real_output & 0x80) real_output += NUMS;
    }
    else if (direction == BACKWARD)
    {
        real_output = get_index(rotor->connect, real_input);
        real_output = real_output - rotor->current;
        if (real_output & 0x80) real_output += NUMS;
    }

    return real_output;
}