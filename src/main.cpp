#include <vector>

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

import MainGui;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    new MainGui(app);

    return app.exec();
}
