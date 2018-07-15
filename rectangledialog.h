#ifndef RECTANGLEDIALOG_H
#define RECTANGLEDIALOG_H

#include <QDialog>
#include <QColor>

namespace Ui {
class RectangleDialog;
}

class RectangleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RectangleDialog(QWidget *parent = 0);
    ~RectangleDialog();

private slots:
    void on_anchorX_textChanged(const QString &arg1);

    void on_fillColor_clicked();
    void on_strokeColor_clicked();

private:
    Ui::RectangleDialog *ui;
    QColor fillColor;
    QColor strokeColor;

    void setFillColor(const QColor fillColor);
    void setStrokeColor(const QColor StrokeColor);
};

#endif // RECTANGLEDIALOG_H
