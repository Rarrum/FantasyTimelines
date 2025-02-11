module;

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <list>

import WorldState;
import CharacterListGui;
import ChildQWidget;

export module MainGui;

export class MainGui : public QWidget
{
public:
    MainGui()
    {
        // Temp for testing
        Character c;
        c.DisplayName = "Rarrum";
        initialWorld.Elements.emplace_back(c);

        //TODO: default to the final view?
        currentView = initialWorld;

        QVBoxLayout *manualLayout = new QVBoxLayout();
        manualLayout->setAlignment(Qt::AlignTop);

        QPushButton *tempButton = new QPushButton();
        tempButton->setText("(Placeholder for Timeline Stuff)");
        manualLayout->addWidget(tempButton);

        QPushButton *charactersButton = new QPushButton();
        charactersButton->setText("View Characters");
        QObject::connect(charactersButton, &QPushButton::clicked, [&]()
        {
            allChildWindows.emplace_back(new CharacterListGui(currentView, ChildClosedCallback()));
        });
        manualLayout->addWidget(charactersButton);

        setLayout(manualLayout);
        resize(800, 600);
        show();
    }

protected:
    void closeEvent(QCloseEvent *event) override
    {
        for (ChildQWidget *child : allChildWindows)
            delete child;
        allChildWindows.clear();
    }

private:
    World initialWorld;
    Timeline worldTimeline;
    World currentView;

    std::list<ChildQWidget*> allChildWindows;

    std::function<void(ChildQWidget*)> ChildClosedCallback()
    {
        return [&](ChildQWidget *child)
        {
            allChildWindows.remove(child);
        };
    }
};
