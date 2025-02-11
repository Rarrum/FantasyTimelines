// Temporarily not using modules for the Gui, due to compiler bugs when Qt and Modules are used together.

#pragma once

#include <string>
#include <vector>

#include "Widgets/ChildQWidget.h"

import WorldState;

class CharacterListGui : public ChildQWidget
{
public:
    CharacterListGui(World view, std::function<void(ChildQWidget*)> closeCallback);
};
