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

private:
  void paintEvent(QPaintEvent *) override;

protected:
    void changeEvent(QEvent *event);

private:

    RibbonMenuBar* m_pRibbonMenuBar;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
