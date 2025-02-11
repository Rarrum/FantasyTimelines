#include <vector>

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

#include "Gui/MainGui.h"

import WorldState;
import Utilities;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainGui mainGui;

    return app.exec();
}
