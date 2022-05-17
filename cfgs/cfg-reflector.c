
#include "../includes/plugins.h"

extern uint8_t init_reflector(struct Reflector *reflector, struct Ui *ui, uint8_t *sign);
extern uint8_t output_reflector(struct Reflector *reflector, uint8_t input);

struct IReflector ireflector = { init_reflector, output_reflector };