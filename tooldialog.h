#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QDialog>
#include <QKeyEvent>

class ToolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolDialog(QWidget *parent = nullptr);

public slots:
    void show();

protected:
    void closeEvent(QCloseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    virtual void onClose();

private:
    bool restorePosition;
    QPoint position;
};

#endif // TOOLDIALOG_H
