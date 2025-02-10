#include "CharacterListGui.h"

#include <QPushButton>
#include <QVBoxLayout>

CharacterListGui::CharacterListGui(World view, QWidget *parent)
    //: QWidget(parent) hrm
{
    QVBoxLayout *manualLayout = new QVBoxLayout();
    manualLayout->setAlignment(Qt::AlignTop);

    for (auto &e : view.Elements)
    {
        Character *c = dynamic_cast<Character*>(&*e);
        if (!c)
            continue;

        QPushButton *button = new QPushButton(this);
        button->setText(c->DisplayName.c_str());
        QObject::connect(button, &QPushButton::clicked, [&]()
        {
        });

        manualLayout->addWidget(button);
    }

    setLayout(manualLayout);
}
