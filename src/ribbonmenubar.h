#ifndef RIBBONMENUBAR_H
#define RIBBONMENUBAR_H

#include <QWidget>
#include"ribbon.h"
#include<QMouseEvent>

#define BUTTON_HEIGHT 35 //按钮高度
#define BUTTON_WIDTH 35
#define TITLE_HEIGHT 35

enum STYLE_SHEETS{
    STYLE_SHEET_BLUE = 0,  //#a7cefa
    STYLE_SHEET_AQUA = 1,  //#00c0c0
    STYLE_SHEET_SILVER = 2,//#c0c0c0
    STYLE_SHEET_BLACK = 3  //#000000
};


namespace Ui {
class RibbonMenuBar;
}

class RibbonMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit RibbonMenuBar(QWidget *parent = nullptr);
    ~RibbonMenuBar();

private:
    void initTitleBar();
    void setBackStyle(int style);
    void initMenu();
    void initTitle();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
public:
    void setTitleState(Qt::WindowStates state);

signals:
    void sigBtnCloseClicked();
    void sigBtnMaxClicked();
    void sigBtnMinClicked();
    void sigBtnStyleClicked();
    void sigPaletteChange(int color_style);

private slots:
    void on_ribbonTabWidget_tabBarDoubleClicked(int );

private:
    bool m_bIsPressed;    //移动窗口的变量
    QPoint m_mouseStartPos;//移动前 鼠标 位置记录

    Ui::RibbonMenuBar *ui;
};

#endif // RIBBONMENUBAR_H
