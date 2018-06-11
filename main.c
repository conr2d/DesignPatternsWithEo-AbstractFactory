#define EFL_BETA_API_SUPPORT
#define EFL_EO_API_SUPPORT

#include <Eo.h>

#include "ui_button.eo.h"
#include "mobile_ui_button.eo.h"
#include "wearable_ui_button.eo.h"

#include "ui_factory.eo.h"
#include "mobile_ui_factory.eo.h"
#include "wearable_ui_factory.eo.h"

static Ui_Factory *_ui_factory = NULL;

EOLIAN static Ui_Button *
_mobile_ui_factory_ui_factory_button_add(Eo *obj, void *pd, Efl_Object *parent)
{
    return efl_add(MOBILE_UI_BUTTON_CLASS, parent);
}

EOLIAN static Ui_Button *
_wearable_ui_factory_ui_factory_button_add(Eo *obj, void *pd, Efl_Object *parent)
{
    return efl_add(WEARABLE_UI_BUTTON_CLASS, parent);
}

EOLIAN static void
_mobile_ui_button_ui_button_activate(Eo *obj, void *pd)
{
    printf("Mobile.Ui.Button is activated!\n");
}

EOLIAN static void
_wearable_ui_button_ui_button_activate(Eo *obj, void *pd)
{
    printf("Wearable.Ui.Button is activated!\n");
}

void
ui_init(int argc, char **argv)
{
    if ((argc <= 1) || !strcmp(argv[1], "mobile")) {
        _ui_factory = efl_add(MOBILE_UI_FACTORY_CLASS, NULL);
    } else if (!strcmp(argv[1], "wearable")) {
        _ui_factory = efl_add(WEARABLE_UI_FACTORY_CLASS, NULL);
    }

    if (!_ui_factory) {
        printf("SPANK!! SPANK!! SPANK!! Naughty Programmer, you failed to create Ui.Factory!\n");
        exit(1);
    }
}

Ui_Button *
ui_button_add(Eo *parent)
{
    return ui_factory_button_add(_ui_factory, parent);
}

int
main(int argc, char **argv)
{
   efl_object_init();

   ////////////////////////////////////////

   ui_init(argc, argv);

   Ui_Button *button = ui_button_add(NULL);
   ui_button_activate(button);

   ////////////////////////////////////////

   efl_object_shutdown();

   return 0;
}

#include "ui_button.eo.c"
#include "mobile_ui_button.eo.c"
#include "wearable_ui_button.eo.c"

#include "ui_factory.eo.c"
#include "mobile_ui_factory.eo.c"
#include "wearable_ui_factory.eo.c"
