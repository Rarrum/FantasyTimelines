#include <vector>

#include <QApplication>
#include <QWidget>

import WorldState;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget window = QWidget();
    window.resize(800, 600);
    window.show();

    //temp to verify module stuff is working
    Timeline timeline;
    WorldState world;
    Character character;

    return app.exec();
}
