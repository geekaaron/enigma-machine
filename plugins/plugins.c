
#include "../includes/plugins.h"

extern struct IUi iui;
extern struct IRotor irotor;
extern struct IReflector ireflector;
extern struct IPlugboard iplugboard;
extern struct IKeyboard ikeyboard;
extern struct IDisplay idisplay;

struct Plugins plugins = { &iui, &irotor, &ireflector, &iplugboard, &ikeyboard, &idisplay };