#pragma once

#include <QPlainTextEdit>
#include <QGridLayout>
#include <QDebug>
#include <QApplication>
#include <QToolBar>
#include <QWindow>
#include <QFontMetrics>

#include "cpphighligher.h"

class Filter : public QObject {
 Q_OBJECT
 public:
    bool eventFilter(QObject *object, QEvent *event);
};

class TextEditor : public QTextEdit {
 Q_OBJECT
 protected:
    void focusInEvent(QFocusEvent *e) override;
 public:
    explicit TextEditor(QFile *file, QWidget *parent = Q_NULLPTR);
    void SearchInText(QString from, bool isRegex);
    void ReplaceInText(QString from, QString to, bool isRegex);
    void Save();
 protected:
    void keyPressEvent(QKeyEvent *e) override;
 public:
    void SaveAtExit();
    QFile *file();
 public slots:
    void addText();
    void copy();
    void paste();
    void cut();
    void find();
    void replace();
    void undo();
    void redo();
 signals:
    void InFocus(QWidget *widget);
    void TriggerSearch(QString selectedText);
    void TriggerReplace(QString selectedText);
 private:
    QFile *m_file = Q_NULLPTR;
    bool m_changed{false};
};
