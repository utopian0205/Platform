/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#include "ribbontabcontent.h"
#include "ui_ribbontabcontent.h"
#include <QPaintEvent>
#include <QPainter>

RibbonButtonGroup::RibbonButtonGroup(QWidget *parent)
  : QWidget(parent)
  , m_title("")
{
    m_pBtnGroupLabel = new QLabel;
    m_pBtnGroupLabel->setAlignment(Qt::AlignCenter);
    m_pHorizontalLine = new QFrame;
    m_pHorizontalLine->setFrameShadow(QFrame::Plain);
    m_pHorizontalLine->setFrameShape(QFrame::HLine);
    m_pHorizontalLine->setObjectName("horizontalLine");

    m_pHorizontalLayout = new QHBoxLayout;
    QVBoxLayout* pVerticalLayout = new QVBoxLayout(this);
    pVerticalLayout->addLayout(m_pHorizontalLayout);
    pVerticalLayout->addWidget(m_pHorizontalLine);
    pVerticalLayout->addWidget(m_pBtnGroupLabel);

    setMinimumHeight(118);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

}

RibbonButtonGroup::~RibbonButtonGroup()
{
}

void RibbonButtonGroup::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    QColor color = QColor("gray");
    int penWidth = 3;
    p.setPen(QPen(color,penWidth)); //设置画笔记颜色

    p.drawRect(0, 0, width() -1, height() -1); //绘制边框
    //p.drawRoundedRect(0, 0, width(), height(),20.0,15.0);

}

void RibbonButtonGroup::setTitle(const QString &title)
{
  m_title = title;
  m_pBtnGroupLabel->setText(m_title);
}

QString RibbonButtonGroup::title() const
{
  return m_title;
}

int RibbonButtonGroup::buttonCount() const
{
  return m_pHorizontalLayout->count();
}

void RibbonButtonGroup::addButton(QToolButton *button)
{
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  button->setMinimumSize(48, 48);
  button->setAutoRaise(true);
  button->setIconSize(QSize(32,32));
  button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  m_pHorizontalLayout->addWidget(button);
}

void RibbonButtonGroup::removeButton(QToolButton *button)
{
  /// \todo What happens if button is not part of the layout?
  m_pHorizontalLayout->removeWidget(button);
}

RibbonTabContent::RibbonTabContent(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::RibbonTabContent)
{
    ui->setupUi(this);
    setMinimumHeight(150);


}

RibbonTabContent::~RibbonTabContent()
{
  delete ui;
}

void RibbonTabContent::addGroup(const QString &groupName)
{

    ui->ribbonHorizontalLayout->setSpacing(10);

    RibbonButtonGroup *ribbonButtonGroup = new RibbonButtonGroup;
    ribbonButtonGroup->setTitle(groupName);
    ui->ribbonHorizontalLayout->addWidget(ribbonButtonGroup);
}

void RibbonTabContent::removeGroup(const QString &groupName)
{
  // Find ribbon group
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonButtonGroup *group = static_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ui->ribbonHorizontalLayout->removeWidget(group); /// \todo :( No effect
      delete group;
      break;
    }
  }

  /// \todo  What if the group still contains buttons? Delete manually?
  // Or automaticly deleted by Qt parent() system.
}

int RibbonTabContent::groupCount() const
{
  return ui->ribbonHorizontalLayout->count();
}

void RibbonTabContent::addButton(const QString &groupName, QToolButton *button)
{
  // Find ribbon group
  RibbonButtonGroup *ribbonButtonGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonButtonGroup *group = static_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonButtonGroup = group;
      break;
    }
  }

  if (ribbonButtonGroup != nullptr)
  {
    // Group found
    // Add ribbon button
    ribbonButtonGroup->addButton(button);
  }
  else
  {
    // Group not found
    // Add ribbon group
    addGroup(groupName);

    // Add ribbon button
    addButton(groupName, button);
  }
}

void RibbonTabContent::removeButton(const QString &groupName, QToolButton *button)
{
  // Find ribbon group
  RibbonButtonGroup *ribbonButtonGroup = nullptr;
  for (int i = 0; i < ui->ribbonHorizontalLayout->count(); i++)
  {
    RibbonButtonGroup *group = static_cast<RibbonButtonGroup*>(ui->ribbonHorizontalLayout->itemAt(i)->widget());
    if (group->title().toLower() == groupName.toLower())
    {
      ribbonButtonGroup = group;
      break;
    }
  }

  if (ribbonButtonGroup != nullptr)
  {
    // Group found
    // Remove ribbon button
    ribbonButtonGroup->removeButton(button);

    if (ribbonButtonGroup->buttonCount() == 0)
    {
      // Empty button group
      // Remove button group
      removeGroup(groupName);
    }
  }
}

void RibbonTabContent::hideTab()
{
    setMinimumHeight(0);
    ui->ribbonTabScrollArea->hide();
    this->hide();
}

void RibbonTabContent::extandTab()
{
    setMinimumHeight(150);
    ui->ribbonTabScrollArea->show();
    this->show();
}
