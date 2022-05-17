
#include "../includes/plugins.h"

extern uint8_t init_plugboard(struct Plugboard *plugboard, struct Ui *ui, uint8_t *sign);
extern uint8_t output_plugboard(struct Plugboard *plugboard, uint8_t input);

struct IPlugboard iplugboard = { init_plugboard, output_plugboard };