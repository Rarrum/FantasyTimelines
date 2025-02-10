// Temporarily not using modules for the Gui, due to compiler bugs when Qt and Modules are used together.

#pragma once

#include <string>
#include <vector>

#include <QWidget>

import WorldState;

class WorldGui : public QWidget
{
public:
    WorldGui(Universe &universe);

private:
    Universe &universe;
    World currentView;
};
