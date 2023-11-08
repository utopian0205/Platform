/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ribbonmenubar.h"
#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <QLabel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void slotPaletteChange(int color_style);

private:
    void creatRibbon();
    void createDockingWidget();

private:
  void paintEvent(QPaintEvent *) override;

protected:
    void changeEvent(QEvent *event);

private:

    // 主Dock 窗口
    KDDockWidgets::MainWindow *m_pDockMainWindow;

    //Dock 窗口
    KDDockWidgets::DockWidget *m_pWorkDock;
    KDDockWidgets::DockWidget *m_pQuestionDock;
    KDDockWidgets::DockWidget *m_pSearchDock;
    KDDockWidgets::DockWidget *m_pEditorDock;

    QLabel* m_pWorkLabel;
    QLabel* m_pQuestionLabel;
    QLabel* m_pSearchLabel;
    QLabel* m_pEditorLabel;

    RibbonMenuBar* m_pRibbonMenuBar;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
