module;

#include <list>

#include <QWidget>
#include <QtGui/QCloseEvent>

import WorldState;
import QSafeWidgetOwner;

export module QTrackedWidget;

// Tracks all active windows that need sync'd to a timeline position.
export class QTrackedWidget: virtual public QWidget, public QSafeWidgetOwner
{
public:
    QTrackedWidget()
    {
        AllTrackedWidgets.emplace_back(this);
    }

    static void ChangeTimelineView()
    {
        for (QTrackedWidget *w : AllTrackedWidgets)
            w->OnChangeTimelineView();
    }

    static std::list<QTrackedWidget*> AllTrackedWidgets;

protected:
    void closeEvent(QCloseEvent *event) override
    {
        AllTrackedWidgets.remove(this);

        QWidget::closeEvent(event);
    }

    virtual void OnChangeTimelineView()
    {
    }
};

std::list<QTrackedWidget*> QTrackedWidget::AllTrackedWidgets;
