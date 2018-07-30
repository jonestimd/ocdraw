#ifndef SHAPEFORM_H
#define SHAPEFORM_H

#include <QtWidgets>

/**
 * @brief The ShapeForm class defines the interface for a form displayed within the ShapeDialog.
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
};

#endif // SHAPEFORM_H
