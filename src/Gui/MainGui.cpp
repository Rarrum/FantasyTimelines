#include "MainGui.h"

#include "CharacterListGui.h"

#include <QPushButton>
#include <QVBoxLayout>

#include <list>

struct MainGuiState
{
    World InitialWorld;
    Timeline WorldTimeline;
    World CurrentView;

    std::list<ChildQWidget*> AllChildWindows;

    std::function<void(ChildQWidget*)> ChildClosedCallback()
    {
        return [&](ChildQWidget *child)
        {
            AllChildWindows.remove(child);
        };
    }
};

MainGui::MainGui()
{
    state = std::make_unique<MainGuiState>();

    // Temp for testing
    Character c;
    c.DisplayName = "Rarrum";
    state->InitialWorld.Elements.emplace_back(c);

    //TODO: default to the final view?
    state->CurrentView = state->InitialWorld;

    QVBoxLayout *manualLayout = new QVBoxLayout();
    manualLayout->setAlignment(Qt::AlignTop);

    QPushButton *tempButton = new QPushButton();
    tempButton->setText("(Placeholder for Timeline Stuff)");
    manualLayout->addWidget(tempButton);

    QPushButton *charactersButton = new QPushButton();
    charactersButton->setText("View Characters");
    QObject::connect(charactersButton, &QPushButton::clicked, [&]()
    {
        state->AllChildWindows.emplace_back(new CharacterListGui(state->CurrentView, state->ChildClosedCallback()));
    });
    manualLayout->addWidget(charactersButton);

    setLayout(manualLayout);
    resize(800, 600);
    show();
}

MainGui::~MainGui()
{
}

void MainGui::closeEvent(QCloseEvent *event)
{
    for (ChildQWidget *child : state->AllChildWindows)
        delete child;
    state->AllChildWindows.clear();
}
