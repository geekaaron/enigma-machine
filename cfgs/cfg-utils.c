
#include "../includes/utils.h"

extern uint8_t init_list(struct Listnode *list);
extern uint8_t append_list(struct Listnode *list, uint8_t *data);

struct IList ilist = { init_list, append_list };