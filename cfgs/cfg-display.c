
#include "../includes/plugins.h"

extern uint8_t init_display(struct Display *display, struct Ui *ui, uint8_t *sign);
extern uint8_t output_display(struct Display *display, uint8_t input);

struct IDisplay idisplay = { init_display, output_display };