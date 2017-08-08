#include <iostream>
#include "model.h"
#include "constantmodelinterface.h"
#include "controller.h"
#include "view.h"

int main()
{
    Model model;
    Controller controller(&model);
    View view(&model, &controller);
    model.addListener(&view);
    view.run();
    return 0;
}
