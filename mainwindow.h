#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "excelmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_open_csv_action();

    void set_tableViewModel(QAbstractTableModel *model);

private:
    Ui::MainWindow *ui;
    xlm::ExcelModel *ptrExcelModel;

    void init();
};

#endif // MAINWINDOW_H
