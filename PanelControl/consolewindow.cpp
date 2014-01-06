#include "consolewindow.h"
#include "ui_consolewindow.h"
#include <QDebug>
#include <ctime>
#include <QDate>

ConsoleWindow::ConsoleWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsoleWindow)
{
    ui->setupUi(this);
    destroy = false;
}

ConsoleWindow::~ConsoleWindow()
{
    delete ui;
}

void ConsoleWindow::addLog(QString test)
{
    QDateTime date = QDateTime();
    test.prepend(" | ").prepend(date.currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
    this->ui->consoleText->appendPlainText(test.append('\n'));
}

bool ConsoleWindow::eventFilter(QObject *obj, QEvent *event) {

    if (event->type() == QEvent::Close) {
        if (!this->destroy){
            event->ignore();
            this->close();
            return ConsoleWindow::eventFilter(obj, event);
        }
        return true;
    }
    return ConsoleWindow::eventFilter(obj, event);
}
