#ifndef SHAPEFORM_H
#define SHAPEFORM_H

#include <QtWidgets>

/**
 * @brief The ShapeForm class defines the interface for a form that displays shape parameters within the ShapeDialog.
 */
class ShapeForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeForm(QWidget* parent = nullptr);
    virtual ~ShapeForm();

    /**
     * @brief Called by \c ShapeDialog to initialzie the form before it is displayed.
     */
    virtual void initialize() = 0;

    /**
     * @brief Called by \c ShapeDialog when the form is hidden.
     * @param closing true if the dialog is closing
     */
    virtual void uninitialize(bool closing) = 0;

    static void setColorIcon(const QColor color, QToolButton *button);
    static void setText(QLineEdit* field, qreal value);
};

#endif // SHAPEFORM_H
