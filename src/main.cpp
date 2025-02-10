#include <vector>

#include <QApplication>
#include <QWidget>

import WorldState;
import Utilities;

class A
{
public:
    virtual int Meow() = 0;
    virtual ~A() = default;
};

class B : public A
{
public:
    int Meow() override { return 42; }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget window = QWidget();
    window.resize(800, 600);
    window.show();

    //temp to verify the world module stuff is working
    Timeline timeline;
    WorldState world;

    //temp stuff to verify ClonePtr covers the cases needed
    ClonePtr<int> v1;
    ClonePtr<int> v2;
    ClonePtr<int> v3(v1);
    v2 = v1;
    int *ip = v1;
    int &ir = *v1;

    ClonePtr<A>(ClonePtr<B>());

    std::vector<ClonePtr<A>> v;
    v.emplace_back(B());
    v.emplace_back(ClonePtr<B>());

    for (auto &r : v)
    {
        r->Meow();
    }

    ClonePtr<Character>::Make();

    return app.exec();
}
