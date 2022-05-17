
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/utils.h"
#include "../includes/plugins.h"

uint8_t init_reflector(struct Reflector *reflector, struct Ui *ui, uint8_t *sign)
{
    uint8_t buffer[BUFSIZE] = { 0 };
    uint8_t *temp = NULL;
    uint8_t index = 0;

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
                    reflector->connect[index++] = ui->ch - 'A';
                }
                break;
            }       
            temp = strtok(NULL, " ");
        }
    }

    return 0;
}

uint8_t output_reflector(struct Reflector *reflector, uint8_t input)
{
    if (input >= NUMS) return 0xff;
    return reflector->connect[input];
}