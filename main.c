
#include <curses.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./includes/utils.h"
#include "./includes/plugins.h"

int main(int argc, char *argv[])
{
    initscr();
    curs_set(0);

    struct Ui ui = { 0 };

    struct Rotor rotor1 = { 0 };
    struct Rotor rotor2 = { 0 };
    struct Rotor rotor3 = { 0 };

    struct Reflector reflector = { 0 };
    struct Plugboard plugboard = { 0 };

    struct Keyboard keyboard = { 0 };
    struct Keyboard lampboard = { 0 };

    struct Display display = { 0 };

    uint8_t pre = 0, key = 0, temp = 0;
    uint16_t position[2] = { 0 };

    plugins.iui->init(&ui, "./tpls/tpl-ui");
    plugins.iui->output(&ui);

    plugins.irotor->init(&rotor1, &ui, "ROTOR1");
    plugins.irotor->init(&rotor2, &ui, "ROTOR2");
    plugins.irotor->init(&rotor3, &ui, "ROTOR3");

    // refresh the current rotor point
    plugins.irotor->output(&rotor1, temp, FORWARD);
    plugins.irotor->output(&rotor2, temp, FORWARD);
    plugins.irotor->output(&rotor3, temp, FORWARD);

    plugins.ireflector->init(&reflector, &ui, "REFLECTOR");
    plugins.iplugboard->init(&plugboard, &ui, "PLUGBOARD");

    plugins.ikeyboard->init(&keyboard, &ui, "KEYBOARD");
    plugins.ikeyboard->init(&lampboard, &ui, "LAMPBOARD");

    plugins.idisplay->init(&display, &ui, "DISPLAY");

    pre = key = toupper(getch());
    while(key != ERR && key != LOCAL_ESCPAE_KEY)
    {
        plugins.ikeyboard->output(&keyboard, key - 'A', KEYBOARD_ON);
        temp = plugins.iplugboard->output(&plugboard, key - 'A');
        temp = plugins.irotor->output(&rotor1, temp, FORWARD);
        temp = plugins.irotor->output(&rotor2, temp, FORWARD);
        temp = plugins.irotor->output(&rotor3, temp, FORWARD);
        temp = plugins.ireflector->output(&reflector, temp);
        temp = plugins.irotor->output(&rotor3, temp, BACKWARD);
        temp = plugins.irotor->output(&rotor2, temp, BACKWARD);
        temp = plugins.irotor->output(&rotor1, temp, BACKWARD);
        temp = plugins.iplugboard->output(&plugboard, temp);
        plugins.ikeyboard->output(&lampboard, temp, KEYBOARD_ON);
        plugins.idisplay->output(&display, temp);

        if (temp == 0xff) // recover the ui if the input is not a alphabet
        {
            plugins.iui->output(&ui); 
        }
        else if (plugins.irotor->turn(&rotor1)) // turn the rotor if the input is valid
        {
            if (plugins.irotor->turn(&rotor2)) plugins.irotor->turn(&rotor3);
        }

        // refresh the current rotor point
        plugins.irotor->output(&rotor1, temp, FORWARD);
        plugins.irotor->output(&rotor2, temp, FORWARD);
        plugins.irotor->output(&rotor3, temp, FORWARD);

        key = toupper(getch());
        if (pre != key)
        {
            plugins.ikeyboard->output(&keyboard, pre - 'A', KEYBOARD_OFF);
            pre = key;
        }
        plugins.ikeyboard->output(&lampboard, temp, KEYBOARD_OFF);
    }

    endwin();

    return 0;
}