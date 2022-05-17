
#include "../includes/plugins.h"

extern uint8_t init_ui(struct Ui *ui, uint8_t *filename);
extern uint8_t output_ui(struct Ui *ui);

struct IUi iui = { init_ui, output_ui };