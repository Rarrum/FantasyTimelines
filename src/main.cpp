#include <vector>

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

#include "Gui/WorldGui.h"

import WorldState;
import Utilities;

int main(int argc, char **argv)
{
    Universe universe;

    // Temp for testing
    Character c;
    c.DisplayName = "Rarrum";
    universe.InitialWorld.Elements.emplace_back(c);

    // Gui
    QApplication app(argc, argv);
    QWidget window = QWidget();
    window.resize(800, 600);
    window.show();

    WorldGui *worldGui = new WorldGui(universe);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(worldGui);
    window.setLayout(mainLayout);

    return app.exec();
}
