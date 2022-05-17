
#include <stdint.h>
#include "../includes/utils.h"

#define NUMS                26
#define BUFSIZE             512

#define FORWARD             1
#define BACKWARD            2
#define REFLECT             3

#define KEYBOARD_ON         1
#define KEYBOARD_OFF        0

#define LOCAL_ESCPAE_KEY    27

struct Ui
{
    uint16_t row;
    uint16_t col;
    uint16_t count;
    uint8_t ch;

    struct Listnode lines;
};

struct IUi
{
    uint8_t (*init)(struct Ui *ui, uint8_t *filename);
    uint8_t (*output)(struct Ui *ui);
};

struct Rotor
{
    uint16_t row;
    uint16_t col;

    uint8_t current;
    uint8_t connect[NUMS];
};

struct IRotor
{
    uint8_t (*init)(struct Rotor *rotor, struct Ui *ui, uint8_t *sign);
    uint8_t (*turn)(struct Rotor *rotor);
    uint8_t (*output)(struct Rotor *rotor, uint8_t input, uint8_t direction);
};

struct Reflector
{
    uint8_t connect[NUMS];
};

struct IReflector
{
    uint8_t (*init)(struct Reflector *reflector, struct Ui *ui, uint8_t *sign);
    uint8_t (*output)(struct Reflector *reflector, uint8_t input);
};

struct Plugboard
{
    uint8_t connect[NUMS];
};

struct IPlugboard
{
    uint8_t (*init)(struct Plugboard *plugboard, struct Ui *ui, uint8_t *sign);
    uint8_t (*output)(struct Plugboard *plugboard, uint8_t input);
};

struct Keyboard
{
    uint16_t position[NUMS][2];
};

struct IKeyboard
{
    uint8_t (*init)(struct Keyboard *keyboard, struct Ui *ui, uint8_t *sign);
    uint8_t (*output)(struct Keyboard *keyboard, uint8_t input, uint8_t on);
};

struct Display
{
    uint16_t current;
    uint16_t row;
    uint16_t col;
};

struct IDisplay
{
    uint8_t (*init)(struct Display *display, struct Ui *ui, uint8_t *sign);
    uint8_t (*output)(struct Display *display, uint8_t input);
};

struct Plugins
{
    struct IUi *iui;
    struct IRotor *irotor;
    struct IReflector *ireflector;
    struct IPlugboard *iplugboard;
    struct IKeyboard *ikeyboard;
    struct IDisplay *idisplay;
};

extern struct Plugins plugins;

extern uint8_t rotor_data1[];
extern uint8_t rotor_data2[];
extern uint8_t rotor_data3[];

extern uint8_t reflector_data[];
extern uint8_t plugboard_data[];
