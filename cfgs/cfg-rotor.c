
#include "../includes/plugins.h"

extern uint8_t init_rotor(struct Rotor *rotor, struct Ui *ui, uint8_t *sign);
extern uint8_t turn_rotor(struct Rotor *rotor);
extern uint8_t output_rotor(struct Rotor *rotor, uint8_t input, uint8_t direction);

struct IRotor irotor = { init_rotor, turn_rotor, output_rotor };