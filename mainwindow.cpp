#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ptrExcelModel(nullptr)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QMenu *fileMenu = new QMenu("Файл");
    QMenu *openFileMenu = new QMenu("Открыть");
    QAction *saveFileAction = new QAction("Сохранить");
    QMenu *saveAsFileMenu = new QMenu("Сохранить как");

    QAction *csvAction = new QAction("CSV");
    QAction *xlsAction = new QAction("XLS");
    QAction *xlsxAction = new QAction("XLSX");

    openFileMenu->addActions({csvAction, xlsAction, xlsxAction});
    saveAsFileMenu->addActions({csvAction, xlsAction, xlsxAction});

    fileMenu->addMenu(openFileMenu);
    fileMenu->addAction(saveFileAction);
    fileMenu->addMenu(saveAsFileMenu);

    ui->menuBar->addMenu(fileMenu);

    connect(fileMenu, &QMenu::destroyed, this,
            [&](){ openFileMenu->deleteLater(); saveFileAction->deleteLater();
                    saveAsFileMenu->deleteLater(); csvAction->deleteLater();
                    xlsAction->deleteLater(); xlsxAction->deleteLater(); }
    );

    connect(this, &MainWindow::destroyed, fileMenu, &QMenu::deleteLater);

    connect(csvAction, &QAction::triggered,
            this, &MainWindow::on_open_csv_action);

    connect(ptrExcelModel, &xlm::ExcelModel::newValue,
            this, &MainWindow::set_tableViewModel);
}

void MainWindow::set_tableViewModel(QAbstractTableModel *model)
{
    ui->tableView->setModel(model);
}

void MainWindow::on_open_csv_action()
{
    QString path = QFileDialog::getOpenFileName(this, "Открыть CSV", "",
                                                "*.csv");

    xlm::ExcelData temp = deserializeFromCSV(path, ';');


}
