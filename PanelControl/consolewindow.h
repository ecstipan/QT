#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QDialog>

namespace Ui {
class ConsoleWindow;
}

class ConsoleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConsoleWindow(QWidget *parent = 0);
    ~ConsoleWindow();
    bool eventFilter(QObject *obj, QEvent *event);
    bool destroy;
    void addLog(QString test);
private:
    Ui::ConsoleWindow *ui;
};

#endif // CONSOLEWINDOW_H
