// Temporarily not using modules for the Gui, due to compiler bugs when Qt and Modules are used together.

#pragma once

#include <string>
#include <vector>

#include <QWidget>

import WorldState;

class CharacterListGui : public QWidget
{
public:
    CharacterListGui(World view, QWidget *parent);
};
