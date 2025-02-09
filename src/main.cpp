#include <vector>

#include <QApplication>
#include <QWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget window = QWidget();
    window.resize(800, 600);
    window.show();

    return app.exec();
}
