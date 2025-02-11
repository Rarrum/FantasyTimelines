// Temporarily not using modules for the Gui, due to compiler bugs when Qt and Modules are used together.

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <QWidget>

import WorldState;

struct MainGuiState;

class MainGui : public QWidget
{
public:
    MainGui();
    ~MainGui();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    std::unique_ptr<MainGuiState> state;
};
