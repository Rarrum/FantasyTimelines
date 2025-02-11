module;

#include <functional>

#include <QWidget>
#include <QtGui/QCloseEvent>

export module ChildQWidget;

export class ChildQWidget: public QWidget
{
public:
    ChildQWidget(std::function<void(ChildQWidget*)> closeCallback): closeCallback(closeCallback) {}

protected:
    void closeEvent(QCloseEvent *event) override
    {
        closeCallback(this);

        QWidget::closeEvent(event);
    }

private:
    std::function<void(ChildQWidget*)> closeCallback;
};
