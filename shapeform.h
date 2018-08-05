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
     * @brief Called by ShapeDialog to initialzie the form.
     */
    virtual void initialize() = 0;

    static void setText(QLineEdit* field, qreal value);
};

#endif // SHAPEFORM_H
