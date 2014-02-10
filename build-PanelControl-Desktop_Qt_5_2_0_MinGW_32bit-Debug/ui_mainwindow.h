/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionDebug_Console;
    QAction *actionNetwork_Setup;
    QAction *actionNetwork_Diagnostics;
    QAction *actionVideo_Settings;
    QAction *actionEnable_Maintinance_Mode;
    QAction *actionDisable_Maintinance_Mode;
    QAction *actionReset_Array;
    QAction *actionPoll_Array_Locations;
    QAction *actionColor_Space_Test;
    QAction *actionContrast_Test;
    QAction *actionScaling_AA_Test;
    QAction *actionImage_Adjustments;
    QAction *actionNone;
    QWidget *centralWidget;
    QLabel *rawLabel;
    QGroupBox *groupBox;
    QPushButton *enableButton;
    QPushButton *disableButton;
    QComboBox *cameraSelect;
    QLabel *label;
    QPushButton *useDevice;
    QGroupBox *groupBox_2;
    QPushButton *resButton;
    QPushButton *fpsButton;
    QComboBox *resBox;
    QComboBox *fpsBox;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_3;
    QSlider *sliderX;
    QSlider *sliderY;
    QSlider *sliderW;
    QSlider *sliderH;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *panelOveryalLabel;
    QMenuBar *menuBar;
    QMenu *menuPanelControl;
    QMenu *menuNetwork;
    QMenu *menuVideo;
    QMenu *menuTest_Patterns;
    QMenu *menuMaintinance;
    QMenu *menuEdit;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1288, 856);
        MainWindow->setMinimumSize(QSize(1288, 800));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QLatin1String("QToolTip\n"
"{\n"
"     border: 1px solid black;\n"
"     background-color: #ffa02f;\n"
"     padding: 1px;\n"
"     border-radius: 3px;\n"
"     opacity: 100;\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"    background: transparent;\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"    background: #444;\n"
"    border: 1px solid #000;\n"
"    background-color: QLinearGradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:1 #212121,\n"
"        stop:0.4 #343434/*,\n"
"        stop:0.2 #3"
                        "43434,\n"
"        stop:0.1 #ffaa00*/\n"
"    );\n"
"    margin-bottom:-1px;\n"
"    padding-bottom:1px;\n"
"}\n"
"\n"
"QMenu\n"
"{\n"
"    border: 1px solid #000;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"    padding: 2px 20px 2px 20px;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:disabled\n"
"{\n"
"    color: #404040;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QAbstractItemView\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);\n"
"}\n"
"\n"
"QWidget:focus\n"
"{\n"
"    /*border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);\n"
"    padding: 1px;\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b"
                        "1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #ffaa00;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QComboBox:hover,QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0,"
                        " x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"\n"
"QComboBox:on\n"
"{\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"    selection-background-color: #ffaa00;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView\n"
"{\n"
"    border: 2px solid darkgray;\n"
"    selection-background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QComboBox::drop-down\n"
"{\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"\n"
"     border-left-width: 0px;\n"
"     border-left-color: darkgray;\n"
"     border-left-style: solid; /* just a single line */\n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 3px;\n"
" }\n"
"/*\n"
"QComboBox::down-arrow\n"
"{\n"
"     image: url(:/down_arrow.p"
                        "ng);\n"
"}\n"
"*/\n"
"\n"
"QGroupBox:focus\n"
"{\n"
"border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QTextEdit:focus\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"     height: 7px;\n"
"     margin: 0px 16px 0 16px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"   "
                        "   subcontrol-position: right;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"      width: 7px;\n"
"      margin: 16px 0 16px 0;\n"
"      border: 1px solid #222222;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"      background: QLi"
                        "nearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      height: 14px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\n"
"      height: 14px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar::add-page:"
                        "vertical, QScrollBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QPlainTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QHeaderView::section\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"}\n"
"\n"
"QCheckBox:disabled\n"
"{\n"
"color: #414141;\n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"    text-align: center;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button\n"
"{\n"
"    text-align: center;\n"
"    spacing: 1px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:"
                        "0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button:hover, QDockWidget::float-button:hover\n"
"{\n"
"    background: #242424;\n"
"}\n"
"\n"
"QDockWidget::close-button:pressed, QDockWidget::float-button:pressed\n"
"{\n"
"    padding: 1px -1px -1px 1px;\n"
"}\n"
"\n"
"QMainWindow::separator\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #4c4c4c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QMainWindow::separator:hover\n"
"{\n"
"\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QToolBar::handle\n"
"{\n"
"     spacing: 3px; /* spacing between items"
                        " in the tool bar */\n"
"     background: url(:/images/handle.png);\n"
"}\n"
"\n"
"QMenu::separator\n"
"{\n"
"    height: 2px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    margin-left: 10px;\n"
"    margin-right: 5px;\n"
"}\n"
"\n"
"QProgressBar\n"
"{\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"    background-color: #d7801a;\n"
"    width: 2.15px;\n"
"    margin: 0.5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    color: #b1b1b1;\n"
"    border: 1px solid #444;\n"
"    border-bottom-style: none;\n"
"    background-color: #323232;\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"    padding-top: 3px;\n"
"    padding-bottom: 2px;\n"
"    margin-right: -1px;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #444;\n"
"    top: 1px;\n"
"}\n"
"\n"
"QTabBar::tab:last\n"
""
                        "{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:first:!selected\n"
"{\n"
" margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */\n"
"\n"
"\n"
"    border-top-left-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected\n"
"{\n"
"    color: #b1b1b1;\n"
"    border-bottom-style: solid;\n"
"    margin-top: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    margin-bottom: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover\n"
"{\n"
"    /*border-top: 2px solid #ffaa00;\n"
"    padding-bottom: 3px;*/\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ff"
                        "aa00);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked, QRadioButton::indicator:unchecked{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked\n"
"{\n"
"    background-color: qradialgradient(\n"
"        cx: 0.5, cy: 0.5,\n"
"        fx: 0.5, fy: 0.5,\n"
"        radius: 1.0,\n"
"        stop: 0.25 #ffaa00,\n"
"        stop: 0.3 #323232\n"
"    );\n"
"}\n"
"\n"
"QCheckBox::indicator{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"QRadioButton::indicator\n"
"{\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:hover, QCheckBox::indicator:hover\n"
"{\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(:/images/checkbox.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:disabled, QRadioButton::indicator:disabled\n"
"{\n"
"    border: 1px sol"
                        "id #444;\n"
"}"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionDebug_Console = new QAction(MainWindow);
        actionDebug_Console->setObjectName(QStringLiteral("actionDebug_Console"));
        actionNetwork_Setup = new QAction(MainWindow);
        actionNetwork_Setup->setObjectName(QStringLiteral("actionNetwork_Setup"));
        actionNetwork_Diagnostics = new QAction(MainWindow);
        actionNetwork_Diagnostics->setObjectName(QStringLiteral("actionNetwork_Diagnostics"));
        actionVideo_Settings = new QAction(MainWindow);
        actionVideo_Settings->setObjectName(QStringLiteral("actionVideo_Settings"));
        actionEnable_Maintinance_Mode = new QAction(MainWindow);
        actionEnable_Maintinance_Mode->setObjectName(QStringLiteral("actionEnable_Maintinance_Mode"));
        actionDisable_Maintinance_Mode = new QAction(MainWindow);
        actionDisable_Maintinance_Mode->setObjectName(QStringLiteral("actionDisable_Maintinance_Mode"));
        actionReset_Array = new QAction(MainWindow);
        actionReset_Array->setObjectName(QStringLiteral("actionReset_Array"));
        actionPoll_Array_Locations = new QAction(MainWindow);
        actionPoll_Array_Locations->setObjectName(QStringLiteral("actionPoll_Array_Locations"));
        actionColor_Space_Test = new QAction(MainWindow);
        actionColor_Space_Test->setObjectName(QStringLiteral("actionColor_Space_Test"));
        actionContrast_Test = new QAction(MainWindow);
        actionContrast_Test->setObjectName(QStringLiteral("actionContrast_Test"));
        actionScaling_AA_Test = new QAction(MainWindow);
        actionScaling_AA_Test->setObjectName(QStringLiteral("actionScaling_AA_Test"));
        actionImage_Adjustments = new QAction(MainWindow);
        actionImage_Adjustments->setObjectName(QStringLiteral("actionImage_Adjustments"));
        actionNone = new QAction(MainWindow);
        actionNone->setObjectName(QStringLiteral("actionNone"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        rawLabel = new QLabel(centralWidget);
        rawLabel->setObjectName(QStringLiteral("rawLabel"));
        rawLabel->setGeometry(QRect(4, 4, 1280, 720));
        rawLabel->setMinimumSize(QSize(1280, 720));
        rawLabel->setMaximumSize(QSize(1280, 720));
        rawLabel->setCursor(QCursor(Qt::CrossCursor));
        rawLabel->setContextMenuPolicy(Qt::NoContextMenu);
        rawLabel->setAutoFillBackground(false);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(4, 728, 281, 89));
        enableButton = new QPushButton(groupBox);
        enableButton->setObjectName(QStringLiteral("enableButton"));
        enableButton->setGeometry(QRect(4, 20, 81, 23));
        disableButton = new QPushButton(groupBox);
        disableButton->setObjectName(QStringLiteral("disableButton"));
        disableButton->setGeometry(QRect(88, 20, 81, 23));
        cameraSelect = new QComboBox(groupBox);
        cameraSelect->setObjectName(QStringLiteral("cameraSelect"));
        cameraSelect->setGeometry(QRect(4, 64, 273, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(8, 48, 73, 16));
        useDevice = new QPushButton(groupBox);
        useDevice->setObjectName(QStringLiteral("useDevice"));
        useDevice->setGeometry(QRect(172, 20, 105, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(288, 728, 309, 89));
        resButton = new QPushButton(groupBox_2);
        resButton->setObjectName(QStringLiteral("resButton"));
        resButton->setGeometry(QRect(4, 20, 149, 23));
        fpsButton = new QPushButton(groupBox_2);
        fpsButton->setObjectName(QStringLiteral("fpsButton"));
        fpsButton->setGeometry(QRect(156, 20, 149, 23));
        resBox = new QComboBox(groupBox_2);
        resBox->setObjectName(QStringLiteral("resBox"));
        resBox->setGeometry(QRect(4, 64, 149, 22));
        fpsBox = new QComboBox(groupBox_2);
        fpsBox->setObjectName(QStringLiteral("fpsBox"));
        fpsBox->setGeometry(QRect(156, 64, 149, 22));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(8, 48, 105, 16));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 48, 109, 16));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(599, 728, 685, 89));
        sliderX = new QSlider(groupBox_3);
        sliderX->setObjectName(QStringLiteral("sliderX"));
        sliderX->setGeometry(QRect(60, 24, 256, 19));
        sliderX->setMaximum(1179);
        sliderX->setOrientation(Qt::Horizontal);
        sliderY = new QSlider(groupBox_3);
        sliderY->setObjectName(QStringLiteral("sliderY"));
        sliderY->setGeometry(QRect(60, 60, 256, 19));
        sliderY->setMaximum(619);
        sliderY->setOrientation(Qt::Horizontal);
        sliderW = new QSlider(groupBox_3);
        sliderW->setObjectName(QStringLiteral("sliderW"));
        sliderW->setGeometry(QRect(380, 24, 288, 19));
        sliderW->setMinimum(99);
        sliderW->setMaximum(1279);
        sliderW->setValue(1279);
        sliderW->setOrientation(Qt::Horizontal);
        sliderH = new QSlider(groupBox_3);
        sliderH->setObjectName(QStringLiteral("sliderH"));
        sliderH->setGeometry(QRect(380, 60, 288, 19));
        sliderH->setMinimum(99);
        sliderH->setMaximum(719);
        sliderH->setValue(719);
        sliderH->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(16, 24, 40, 16));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(16, 60, 40, 16));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(340, 24, 37, 16));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(340, 60, 37, 16));
        panelOveryalLabel = new QLabel(centralWidget);
        panelOveryalLabel->setObjectName(QStringLiteral("panelOveryalLabel"));
        panelOveryalLabel->setGeometry(QRect(4, 4, 1280, 720));
        panelOveryalLabel->setCursor(QCursor(Qt::CrossCursor));
        panelOveryalLabel->setMouseTracking(true);
        panelOveryalLabel->setStyleSheet(QStringLiteral(""));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1288, 21));
        menuPanelControl = new QMenu(menuBar);
        menuPanelControl->setObjectName(QStringLiteral("menuPanelControl"));
        menuNetwork = new QMenu(menuBar);
        menuNetwork->setObjectName(QStringLiteral("menuNetwork"));
        menuVideo = new QMenu(menuBar);
        menuVideo->setObjectName(QStringLiteral("menuVideo"));
        menuTest_Patterns = new QMenu(menuVideo);
        menuTest_Patterns->setObjectName(QStringLiteral("menuTest_Patterns"));
        menuMaintinance = new QMenu(menuBar);
        menuMaintinance->setObjectName(QStringLiteral("menuMaintinance"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuPanelControl->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuNetwork->menuAction());
        menuBar->addAction(menuVideo->menuAction());
        menuBar->addAction(menuMaintinance->menuAction());
        menuPanelControl->addAction(actionExit);
        menuNetwork->addAction(actionNetwork_Setup);
        menuNetwork->addAction(actionNetwork_Diagnostics);
        menuVideo->addAction(actionVideo_Settings);
        menuVideo->addSeparator();
        menuVideo->addAction(menuTest_Patterns->menuAction());
        menuVideo->addSeparator();
        menuVideo->addAction(actionImage_Adjustments);
        menuTest_Patterns->addAction(actionColor_Space_Test);
        menuTest_Patterns->addAction(actionContrast_Test);
        menuTest_Patterns->addAction(actionScaling_AA_Test);
        menuTest_Patterns->addSeparator();
        menuTest_Patterns->addAction(actionNone);
        menuMaintinance->addAction(actionEnable_Maintinance_Mode);
        menuMaintinance->addAction(actionDisable_Maintinance_Mode);
        menuMaintinance->addSeparator();
        menuMaintinance->addAction(actionReset_Array);
        menuMaintinance->addAction(actionPoll_Array_Locations);
        menuMaintinance->addSeparator();
        menuEdit->addAction(actionDebug_Console);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PanelControl v 0.1", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionDebug_Console->setText(QApplication::translate("MainWindow", "Debug Console", 0));
        actionNetwork_Setup->setText(QApplication::translate("MainWindow", "Network Setup", 0));
        actionNetwork_Diagnostics->setText(QApplication::translate("MainWindow", "Network Diagnostics", 0));
        actionVideo_Settings->setText(QApplication::translate("MainWindow", "Video Settings", 0));
        actionEnable_Maintinance_Mode->setText(QApplication::translate("MainWindow", "Enable Maintinance Mode", 0));
        actionDisable_Maintinance_Mode->setText(QApplication::translate("MainWindow", "Disable Maintinance Mode", 0));
        actionReset_Array->setText(QApplication::translate("MainWindow", "Trigger Array Remapping", 0));
        actionPoll_Array_Locations->setText(QApplication::translate("MainWindow", "Poll Array Locations", 0));
        actionColor_Space_Test->setText(QApplication::translate("MainWindow", "Color Space Test", 0));
        actionContrast_Test->setText(QApplication::translate("MainWindow", "Contrast Test", 0));
        actionScaling_AA_Test->setText(QApplication::translate("MainWindow", "Scaling/AA Test", 0));
        actionImage_Adjustments->setText(QApplication::translate("MainWindow", "Image Adjustments", 0));
        actionNone->setText(QApplication::translate("MainWindow", "None", 0));
        rawLabel->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Live Video Input", 0));
        enableButton->setText(QApplication::translate("MainWindow", "Enable", 0));
        disableButton->setText(QApplication::translate("MainWindow", "Disable", 0));
        label->setText(QApplication::translate("MainWindow", "Input Device", 0));
        useDevice->setText(QApplication::translate("MainWindow", "Update Device", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Basic Image Settings", 0));
        resButton->setText(QApplication::translate("MainWindow", "Set Resolution", 0));
        fpsButton->setText(QApplication::translate("MainWindow", "Set Frame Rate", 0));
        label_2->setText(QApplication::translate("MainWindow", "Capture Resolution", 0));
        label_3->setText(QApplication::translate("MainWindow", "Capture Frame Rate", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Video Mapping Settings", 0));
        label_4->setText(QApplication::translate("MainWindow", "X Start", 0));
        label_5->setText(QApplication::translate("MainWindow", "Y Start", 0));
        label_6->setText(QApplication::translate("MainWindow", "X End", 0));
        label_7->setText(QApplication::translate("MainWindow", "Y End", 0));
        panelOveryalLabel->setText(QString());
        menuPanelControl->setTitle(QApplication::translate("MainWindow", "PanelControl", 0));
        menuNetwork->setTitle(QApplication::translate("MainWindow", "Network", 0));
        menuVideo->setTitle(QApplication::translate("MainWindow", "Video", 0));
        menuTest_Patterns->setTitle(QApplication::translate("MainWindow", "Test Patterns", 0));
        menuMaintinance->setTitle(QApplication::translate("MainWindow", "Maintinance", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
