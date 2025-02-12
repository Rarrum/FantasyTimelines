module;

#include <list>

#include <QWidget>
#include <QtGui/QCloseEvent>

import WorldState;

export module QTrackedWidget;

// Tracks all active windows that need sync'd to a timeline position.
export class QTrackedWidget: public QWidget
{
public:
    QTrackedWidget()
    {
        AllTrackedWidgets.emplace_back(this);
    }

    static void ChangeTimelineView(const World &state) //TODO: iter to timeline too?
    {
        worldView = state;

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

    static World worldView;
};

// Really?  Is needing this a compiler bug?
std::list<QTrackedWidget*> QTrackedWidget::AllTrackedWidgets;
World QTrackedWidget::worldView;
