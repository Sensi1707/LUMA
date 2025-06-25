#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LumaX.h"

class LumaX : public QMainWindow
{
    Q_OBJECT

public:
    LumaX(QWidget *parent = nullptr);
    ~LumaX();

private:
    Ui::LumaXClass ui;
};
