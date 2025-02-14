module;

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>

#include <list>

import WorldState;
import CharacterListGui;
import QTrackedWidget;

export module MainGui;

// The base top-level window for the app.
export class MainGui : public QWidget
{
public:
    MainGui(QApplication &app)
        : app(app)
    {
        setWindowTitle("Fantasy Timelines - Main Controls");

        // Temp for testing
        Character c;
        c.DisplayName = "Rarrum";
        GlobalWorld.InitialWorld.Elements.emplace_back(c);

        QVBoxLayout *manualLayout = new QVBoxLayout();
        manualLayout->setAlignment(Qt::AlignTop);

        QPushButton *tempButton = new QPushButton();
        tempButton->setText("(Placeholder for Timeline Stuff)");
        manualLayout->addWidget(tempButton);

        QPushButton *charactersButton = new QPushButton();
        charactersButton->setText("View Characters");
        QObject::connect(charactersButton, &QPushButton::clicked, [&]()
        {
            new CharacterListGui();
        });
        manualLayout->addWidget(charactersButton);

        setLayout(manualLayout);
        resize(800, 600);
        show();
    }

protected:
    void closeEvent(QCloseEvent *event) override
    {
        app.closeAllWindows();
    }

private:
    QApplication &app;
};
