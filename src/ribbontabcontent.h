/*
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef RIBBONTABCONTENT_H
#define RIBBONTABCONTENT_H

#include <QWidget>
#include <QToolButton>
#include<QLabel>
#include<QFrame>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>


class RibbonButtonGroup : public QWidget
{
  Q_OBJECT

public:
  explicit RibbonButtonGroup(QWidget *parent = 0);
  virtual ~RibbonButtonGroup();

  /// Set the title of the button group.
  /// The title is shown underneath the buttons.
  ///
  /// \param[in] title The title
  void setTitle(const QString &title);

  /// Get the title of the button group.
  ///
  /// \return The title
  QString title() const;

  /// Get the number of buttons in the button group.
  ///
  /// \return The number of buttons
  int buttonCount() const;

  /// Add a button to the group.
  ///
  /// \param[in] button The button
  void addButton(QToolButton *button);

  /// Remove a button from the group.
  ///
  /// \param[in] button The button
  void removeButton(QToolButton *button);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QString m_title; ///< Title of the button group
  QLabel* m_pBtnGroupLabel;
  QFrame* m_pHorizontalLine;
  QHBoxLayout* m_pHorizontalLayout;

};

namespace Ui {
class RibbonTabContent;
}

class RibbonTabContent : public QWidget
{
  Q_OBJECT

public:
  explicit RibbonTabContent(QWidget *parent = 0);
  virtual ~RibbonTabContent();

  /// Add a group to the tab content.
  ///
  /// \param[in] groupName Name of the group
  void addGroup(const QString &groupName);

  /// Remove a group from the tab content.
  ///
  /// \param[in] groupName Name of the group
  void removeGroup(const QString &groupName);

  /// Get the number of button groups in this tab content.
  ///
  /// \return The number of button groups
  int groupCount() const;

  /// Add a button to the specified group.
  /// The group is created if it does not exist.
  ///
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void addButton(const QString &groupName, QToolButton *button);

  /// Remove a button from the specified group.
  /// The group is also removed if it's empty.
  ///
  /// \param[in] groupName Name of the group
  /// \param[in] button The button
  void removeButton(const QString &groupName, QToolButton *button);

  void hideTab();
  void extandTab();

private:
  Ui::RibbonTabContent *ui;
};

#endif // RIBBONTABCONTENT_H
