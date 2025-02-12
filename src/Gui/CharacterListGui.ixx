module;

#include <QPushButton>
#include <QVBoxLayout>

import WorldState;
import QTrackedWidget;
import CharacterGui;

export module CharacterListGui;

export class CharacterListGui : public QTrackedWidget
{
public:
    CharacterListGui()
    {
        setWindowTitle("Fantasy Timelines - Character List");
        OnChangeTimelineView();
        resize(800, 600);
        show();
    }

    void OnChangeTimelineView() override
    {
        if (manualLayout)
            delete manualLayout;
        manualLayout = new QVBoxLayout();

        manualLayout->setAlignment(Qt::AlignTop);
        setLayout(manualLayout);

        for (auto &e : worldView.Elements)
        {
            Character *c = dynamic_cast<Character*>(&*e);
            if (!c)
                continue;

            QPushButton *button = new QPushButton(this);
            button->setText(c->DisplayName.c_str());
            QObject::connect(button, &QPushButton::clicked, [&, c]()
            {
                new CharacterGui(c->DisplayName);
            });

            manualLayout->addWidget(button);
        }
    }

private:
    QVBoxLayout *manualLayout = nullptr;
};
