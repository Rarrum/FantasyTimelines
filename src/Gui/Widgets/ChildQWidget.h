#pragma once

#include <functional>

#include <QWidget>
#include <QtGui/QCloseEvent>

class ChildQWidget: public QWidget
{
public:
    inline ChildQWidget(std::function<void(ChildQWidget*)> closeCallback): closeCallback(closeCallback) {}

protected:
    inline void closeEvent(QCloseEvent *event) override
    {
        closeCallback(this);

        QWidget::closeEvent(event);
    }

private:
    std::function<void(ChildQWidget*)> closeCallback;
};
