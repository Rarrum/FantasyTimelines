module;

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>

#include <list>

import WorldState;
import CharacterListGui;
import QSafeWidgetOwner;

export module MainGui;

// The base top-level window for the app.
export class MainGui : virtual public QWidget, QSafeWidgetOwner
{
public:
    MainGui(QApplication &app)
        : app(app)
    {
        setWindowTitle("Fantasy Timelines - Main Controls");

        auto manualLayout = CreateOwnedWidget<QVBoxLayout>();
        manualLayout->setAlignment(Qt::AlignTop);

        auto tempButton = CreateOwnedWidget<QPushButton>();
        tempButton->setText("(Placeholder for Timeline Stuff)");
        manualLayout->addWidget(tempButton);

        auto charactersButton = CreateOwnedWidget<QPushButton>();
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
