#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <memory>

#include <QCoreApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QtQuickWidgets/QQuickWidget>

#include <octoon/octoon.h>

#include <octoon/game_application.h>
#include <octoon/input/input_event.h>

#include "widgets/OViewWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QDockWidget *viewDock;
    QDockWidget *commandDock;
    QQuickWidget *commandPanel;
    OViewWidget *viewPanel;
};

#endif // MAINWINDOW_H