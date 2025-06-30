#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LumaX.h"

class QMdiArea;

class LumaX : public QMainWindow
{
    Q_OBJECT

public:
    LumaX(QWidget *parent = nullptr);
    ~LumaX();

private:
    Ui::LumaXClass ui;
    QMdiArea* mdiArea;

private slots:
    void onFileOpen();
};