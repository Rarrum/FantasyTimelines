module;

#include <QPushButton>
#include <QVBoxLayout>

import WorldState;
import ChildQWidget;

export module CharacterListGui;

export class CharacterListGui : public ChildQWidget
{
public:
    CharacterListGui(World view, std::function<void(ChildQWidget*)> closeCallback)
        : ChildQWidget(closeCallback)
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

        resize(800, 600);
        show();
    }
};
