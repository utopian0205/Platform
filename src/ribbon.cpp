/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#include "ribbon.h"
#include "ribbontabcontent.h"

#include <QApplication>
#include <QStyleOption>
#include <QPainter>
#include<QHBoxLayout>
#include<QAction>

Ribbon::Ribbon(QWidget *parent)
  : QTabWidget(parent)
{
    //QTabWidget右上角创建按钮
    QFrame *cornerFrame = new QFrame(this);
    cornerFrame->setProperty("TTFrame", QVariant(true));
    cornerFrame->setFrameShape(QFrame::NoFrame);
    cornerFrame->setLineWidth(0);
    cornerFrame->setContentsMargins(0, 0, 0, 0);
    cornerFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    QHBoxLayout *cornerLayout = new QHBoxLayout(cornerFrame);
    cornerLayout->setMargin(0);
    cornerLayout->setContentsMargins(0, 0, 0, 0);
    cornerLayout->setSpacing(0);
    cornerLayout->setDirection(QBoxLayout::LeftToRight);
    cornerFrame->setLayout(cornerLayout);

    QAction *hideAction = new QAction(this);
    hideAction->setCheckable(true);
    hideAction->setIcon(QIcon(":/res/add_top.png"));
    QToolButton *hideButton = new QToolButton(this);
    hideButton->setObjectName("btnMenu");
    hideButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    hideButton->setDefaultAction(hideAction);
    hideButton->setAutoRaise(true);
    hideButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cornerLayout->addWidget(hideButton);
    this->setCornerWidget(cornerFrame);

    QObject::connect(hideAction, &QAction::triggered, this, [=]() {
        int cnt =  count();
        if(cnt<=0) return;
        QWidget *tab = widget(0);
        RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
        bool bExtand = ribbonTabContent->isVisible();
        if(bExtand)
        {
            //hide
            for (int i=0;i<cnt;++i) {
                QWidget *tab = widget(i);
                RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
                ribbonTabContent->hideTab();
            }
        }
        else{
            //show
            for (int i=0;i<cnt;++i) {
                QWidget *tab = widget(i);
                RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
                ribbonTabContent->extandTab();
            }
        }

        hideAction->setIcon(bExtand ? QIcon(":/res/add_bottom.png") : QIcon(":/res/add_top.png"));
    });




  // Determine default colors
  QColor bg = qApp->palette().color(QPalette::Background);
  QColor mid = qApp->palette().color(QPalette::Mid);

  // Note: the order in which the background/palette/stylesheet functions are
  // called does matter. Should be same as in Qt designer.
  //setAutoFillBackground(true);

  // Set stylesheet
  QString styleSheetText = QString(
    "QTabWidget::pane {"
    "  border-top: 1px solid rgb(%4, %5, %6);"
    "  position: absolute;"
    "  top: -1px;"
    "}"
    ""
    "QTabBar::tab {"
    "  padding-top: 5px;"
    "  padding-bottom: 5px;"
    "  padding-left: 10px;"
    "  padding-right: 10px;"
    "  margin-top: 1px;"
    "}"
    ""
    "QTabBar::tab::!selected {"
    "  border-bottom: 1px solid rgb(%4, %5, %6);"
    "  background-color:#ffffff;"
    "}"
    ""
    "QTabBar::tab:selected {"
    "  background-color: rgb(%1, %2, %3);"
    "  border-top: 1px solid rgb(%4, %5, %6);"
    "  border-right: 1px solid rgb(%4, %5, %6);"
    "  border-left: 1px solid rgb(%4, %5, %6);"
    "  border-bottom: 1px solid rgb(%1, %2, %3);"
    "}"
    ""
    "QTabBar::tab:hover"
    "{"
    "  background-color: rgb(205, 232, 255);"
    "}"
    ""
    "QTabBar::tab:selected:hover {"
    "  background-color: rgb(%1, %2, %3);"
    "}"
    ).arg(bg.red()).arg(bg.green()).arg(bg.blue())
     .arg(mid.red()).arg(mid.green()).arg(mid.blue());

//  setStyleSheet(styleSheetText);



//  setStyleSheet(QString::fromUtf8("QTabBar::tab{background-color: #a7cefa}"));
}

Ribbon::~Ribbon()
{
}

void Ribbon::paintEvent(QPaintEvent *)
{
    QPainter p(this);
//    p.fillRect(rect(),QColor(0xa7,0xce,0xfa));

}

void Ribbon::addTab(const QString &tabName)
{
  // Note: superclass QTabWidget also has a function addTab()
  RibbonTabContent *ribbonTabContent = new RibbonTabContent;
  QTabWidget::addTab(ribbonTabContent, tabName);
}

void Ribbon::addTab(const QIcon &tabIcon, const QString &tabName)
{
  // Note: superclass QTabWidget also has a function addTab()
  RibbonTabContent *ribbonTabContent = new RibbonTabContent;
  QTabWidget::addTab(ribbonTabContent, tabIcon, tabName);
}

void Ribbon::removeTab(const QString &tabName)
{
  // Find ribbon tab
  for (int i = 0; i < count(); i++)
  {
    if (tabText(i).toLower() == tabName.toLower())
    {
      // Remove tab
      QWidget *tab = QTabWidget::widget(i);
      QTabWidget::removeTab(i);
      delete tab;
      break;
    }
  }
}

void Ribbon::addGroup(const QString &tabName, const QString &groupName)
{
  // Find ribbon tab
  QWidget *tab = nullptr;
  for (int i = 0; i < count(); i++)
  {
    if (tabText(i).toLower() == tabName.toLower())
    {
      tab = QTabWidget::widget(i);
      break;
    }
  }

  if (tab != nullptr)
  {
    // Tab found
    // Add ribbon group
    RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
    ribbonTabContent->addGroup(groupName);
  }
  else
  {
    // Tab not found
    // Create tab
    addTab(tabName);

    // Add ribbon group
    addGroup(tabName, groupName);
  }
}

void Ribbon::addButton(const QString &tabName, const QString &groupName, QToolButton *button)
{
  // Find ribbon tab
  QWidget *tab = nullptr;
  for (int i = 0; i < count(); i++)
  {
    if (tabText(i).toLower() == tabName.toLower())
    {
      tab = QTabWidget::widget(i);
      break;
    }
  }

  if (tab != nullptr)
  {
    // Tab found
    // Add ribbon button
    RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
    ribbonTabContent->addButton(groupName, button);
  }
  else
  {
    // Tab not found.
    // Create tab
    addTab(tabName);

    // Add ribbon button
    addButton(tabName, groupName, button);
  }
}

void Ribbon::removeButton(const QString &tabName, const QString &groupName, QToolButton *button)
{
  // Find ribbon tab
  QWidget *tab = nullptr;
  for (int i = 0; i < count(); i++)
  {
    if (tabText(i).toLower() == tabName.toLower())
    {
      tab = QTabWidget::widget(i);
      break;
    }
  }

  if (tab != nullptr)
  {
    // Tab found
    // Remove ribbon button
    RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
    ribbonTabContent->removeButton(groupName, button);

    if (ribbonTabContent->groupCount() == 0)
    {
      removeTab(tabName);
    }
  }
}
