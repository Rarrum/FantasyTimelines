module;

#include <QLabel>
#include <QVBoxLayout>

import WorldState;
import QTrackedWidget;

export module CharacterGui;

export class CharacterGui : public QTrackedWidget
{
public:
    CharacterGui(std::string characterId)
    {
        setWindowTitle("Fantasy Timelines - Character");
        id = characterId;

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

        const Character *c = FindCharacter(worldView, id);
        if (!c)
            return;

        setWindowTitle(QString::fromStdString("Fantasy Timelines - Character - " + c->DisplayName));

        manualLayout->addWidget(new QLabel("hp: 30"));
        manualLayout->addWidget(new QLabel("mp: 20"));
        manualLayout->addWidget(new QLabel("ac: 10"));
    }

private:
    QVBoxLayout *manualLayout = nullptr;

    std::string id;
};
