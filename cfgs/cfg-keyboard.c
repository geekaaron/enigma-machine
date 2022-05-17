
#include "../includes/plugins.h"

extern uint8_t init_keyboard(struct Keyboard *keyboard, struct Ui *ui, uint8_t *sign);
extern uint8_t output_keyboard(struct Keyboard *keyboard, uint8_t input, uint8_t on);

struct IKeyboard ikeyboard = { init_keyboard, output_keyboard };