module;

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
        if (mainLayout)
            delete mainLayout;
        mainLayout = new QVBoxLayout();

        mainLayout->setAlignment(Qt::AlignTop);
        setLayout(mainLayout);

        //TODO: scroll bar for characters?  Or use a list control instead?

        for (const auto &e : GlobalWorld.CurrentView().Elements)
        {
            const Character *c = dynamic_cast<const Character*>(&*e);
            if (!c)
                continue;

            auto button = new QPushButton(c->Name.c_str());
            QObject::connect(button, &QPushButton::clicked, [&, c]()
            {
                new CharacterGui(c->Name);
            });

            mainLayout->addWidget(button);
        }

        auto bottomControlsLayout = new QHBoxLayout();
        mainLayout->addLayout(bottomControlsLayout);

        auto buttonCreate = new QPushButton("Create New");
        QObject::connect(buttonCreate, &QPushButton::clicked, [&]()
        {
            //new CharacterCreateGui();

            //some temp hardcoded ones for initial testing
            {
                Character tempChar = CreateTempTestCharacter("Rarone");
                TimelineAddCharacter timelineAddChar;
                timelineAddChar.NewCharacter = tempChar;
                GlobalWorld.AddToTimelineAndUpdateView(timelineAddChar);
            }
            {
                Character tempChar = CreateTempTestCharacter("Rartwo");
                TimelineAddCharacter timelineAddChar;
                timelineAddChar.NewCharacter = tempChar;
                GlobalWorld.AddToTimelineAndUpdateView(timelineAddChar);
            }

            QTrackedWidget::ChangeTimelineView();
        });
        bottomControlsLayout->addWidget(buttonCreate);

        auto buttonImport = new QPushButton("Import");
        QObject::connect(buttonImport, &QPushButton::clicked, [&]()
        {
            //new CharacterImportGui();
        });
        bottomControlsLayout->addWidget(buttonImport);

        auto buttonExport = new QPushButton("Export");
        QObject::connect(buttonExport, &QPushButton::clicked, [&]()
        {
            //new CharacterImportGui();
        });
        bottomControlsLayout->addWidget(buttonExport);
    }

private:
    QVBoxLayout *mainLayout = nullptr;
};
