#include "WorldGui.h"

#include "CharacterListGui.h"

#include <QPushButton>
#include <QVBoxLayout>

WorldGui::WorldGui(Universe &universe)
    : universe(universe)
{
    //TODO: default to the final view?
    currentView = universe.InitialWorld;

    QPushButton *button = new QPushButton(this);
    button->setText("View Characters");
    QObject::connect(button, &QPushButton::clicked, [&]()
    {
        CharacterListGui *characterListGui = new CharacterListGui(currentView, this);
        characterListGui->resize(800, 600);
        characterListGui->show();
    });

    QVBoxLayout *manualLayout = new QVBoxLayout();
    manualLayout->setAlignment(Qt::AlignTop);
    manualLayout->addWidget(button);

    setLayout(manualLayout);
}
