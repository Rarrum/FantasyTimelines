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

        for (const auto &e : GlobalWorld.CurrentView().Elements)
        {
            const Character *c = dynamic_cast<const Character*>(&*e);
            if (!c)
                continue;

            QPushButton *button = new QPushButton(this);
            button->setText(c->Name.c_str());
            QObject::connect(button, &QPushButton::clicked, [&, c]()
            {
                new CharacterGui(c->Name);
            });

            manualLayout->addWidget(button);
        }
    }

private:
    QVBoxLayout *manualLayout = nullptr;
};
