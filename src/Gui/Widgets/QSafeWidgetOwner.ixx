module;

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QIntValidator>
#include <QLayout>

export module QSafeWidgetOwner;

template <typename T>
concept QtTypesWithParentAsLastCtorArg =
    std::derived_from<T, QPushButton> ||
    std::derived_from<T, QGroupBox> ||
    std::derived_from<T, QLabel> ||
    std::derived_from<T, QIntValidator>;

template <typename T>
concept QtTypesThatJustActsDumb =
    std::derived_from<T, QLayout>;

// Attempts to make Qt widget resource management less error-prone by defaulting to creating widgets with a parent that will free them.
export class QSafeWidgetOwner: virtual public QWidget
{
public:
    QSafeWidgetOwner()
    {
        setAttribute(Qt::WA_DeleteOnClose);
    }

protected:
    // some calls take "parent" as a last parameter
    template <typename T, typename ...Args>
    requires
    (
        QtTypesWithParentAsLastCtorArg<T>
    )
    T* CreateOwnedWidget(Args&& ...ctorArgs)
    {
        return new T(std::forward<Args>(ctorArgs)..., this);
    }

    // most calls "parent" this as a first parameter
    template <typename T, typename ...Args>
    requires
    (
        std::derived_from<T, QObject>,
        !QtTypesWithParentAsLastCtorArg<T> && !QtTypesThatJustActsDumb<T>
    )
    T* CreateOwnedWidget(Args&& ...ctorArgs)
    {
        return new T(this, std::forward<Args>(ctorArgs)...);
    }

    // some widgets just malfunction in weird ways if they have a parent prior to using them; just return them and pray.
    template <typename T, typename ...Args>
    requires
    (
        QtTypesThatJustActsDumb<T>
    )
    T* CreateOwnedWidget(Args&& ...ctorArgs)
    {
        return new T(std::forward<Args>(ctorArgs)...);
    }
};
