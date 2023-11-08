/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ribbontabcontent.h"

#include<QTabBar>
#include<QDebug>
#include<QWindowStateChangeEvent>
#include <QMenu>
#include<QPainter>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(800,600);
    creatRibbon();
    showMaximized();

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::creatRibbon()
{
    slotPaletteChange(STYLE_SHEET_BLUE);

    m_pRibbonMenuBar = new RibbonMenuBar(this);
    setMenuWidget(m_pRibbonMenuBar);

    connect(m_pRibbonMenuBar,&RibbonMenuBar::sigBtnCloseClicked,this,&MainWindow::close);
    connect(m_pRibbonMenuBar,&RibbonMenuBar::sigBtnMaxClicked,this,[=](){
        setWindowState(windowState() ^ Qt::WindowMaximized);
    });
    connect(m_pRibbonMenuBar,&RibbonMenuBar::sigBtnMinClicked,this,&MainWindow::showMinimized);

    setWindowFlag(Qt::FramelessWindowHint, true);
    connect(m_pRibbonMenuBar,&RibbonMenuBar::sigPaletteChange,this,&MainWindow::slotPaletteChange);



}

void MainWindow::paintEvent(QPaintEvent *)
{
    //绘制圆角MainWindow
    QPainter custompainter(this);
    custompainter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addRoundedRect(rect(),20,20);
    QRegion maskRegion(path.toFillPolygon().toPolygon());
    setMask(maskRegion);

}



void MainWindow::slotPaletteChange(int color_style)
{

    QPalette pal = palette();

    QColor color;
    switch (color_style) {
    case STYLE_SHEET_BLUE:
        color = QColor(0xd7,0xee,0xff);
        break;
    case STYLE_SHEET_AQUA:
        color = QColor(0x00,0xc0,0xc0);
        break;
    case STYLE_SHEET_SILVER:
        color = QColor(0xc0,0xc0,0xc0);
        break;
    case STYLE_SHEET_BLACK:
        color = QColor(0x0,0x0,0x0);
        break;
    default:
        color = QColor(0xa7,0xce,0xfa);
        break;
    }
    pal.setColor(QPalette::Background,color);
    setPalette(pal);


}

void MainWindow::changeEvent(QEvent *event)
{
    if(QEvent::WindowStateChange == event->type()){
        QWindowStateChangeEvent * stateEvent = dynamic_cast<QWindowStateChangeEvent*>(event);
        if(Q_NULLPTR != stateEvent){
            m_pRibbonMenuBar->setTitleState(stateEvent->oldState());
        }
    }
}
