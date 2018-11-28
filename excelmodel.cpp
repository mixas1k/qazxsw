#include "excelmodel.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace xlm
{
    ExcelModel::ExcelModel()
        : QAbstractTableModel(), xlData(), c_row(0), c_col(0)
    {
        emit newValue(this);
    }

    ExcelModel::ExcelModel(const ExcelData &xld)
        : QAbstractTableModel(),
          xlData(xld),
          c_row(xld.size()),
          c_col(xld.size() ? xld[0].size() : 0)
    {
        emit newValue(this);
    }

    ExcelModel::ExcelModel(const ExcelModel &xlm)
        : QAbstractTableModel(),
          xlData(xlm.getExcelData()),
          c_row(xlm.getRowCount()),
          c_col(xlm.getColCount())
    {
        emit newValue(this);
    }

    ExcelModel::~ExcelModel() { }

    ExcelModel& ExcelModel::operator= (const ExcelModel &rhs)
    {
        xlData = rhs.getExcelData();
        c_row = rhs.getRowCount();
        c_col = rhs.getColCount();

        emit newValue(this);

        return *this;
    }

    ExcelData ExcelModel::getExcelData() const { return xlData; }

    int ExcelModel::getRowCount() const { return c_row; }

    int ExcelModel::getColCount() const { return c_col; }

    void ExcelModel::setExcelData(const ExcelData &xld)
    {
        xlData = xld;
        c_row = xld.size();
        c_col = xld.size() ? xld[0].size() : 0;

        emit newValue(this);
    }

    int ExcelModel::rowCount(const QModelIndex& /*parent*/) const
    {
        return c_row;
    }
    int ExcelModel::columnCount(const QModelIndex& /*parent*/) const
    {
        return c_col;
    }

    QVariant ExcelModel::data(const QModelIndex &index, int role) const
    {
        if(role == Qt::DisplayRole) {
            return QVariant(xlData[index.row()][index.column()]);
        }
        return QVariant();
    }
}

xlm::ExcelData deserializeFromCSV(const QString &path, char separator)
{
    QFile file(path);

    if(!file.exists() || !file.open(QFile::ReadOnly)) {
        qDebug() << "Не удалось открыть файл: " + path;
        return xlm::ExcelData();
    }

    QTextStream stream(&file);

    QString text = stream.readAll();
    QStringList rows = text.split('\n');

    xlm::ExcelData result;

    int row_indx = 0;
    for(const QString &row : rows) {
        int col_indx = 0;
        QStringList cols = row.split(separator);
        QHash<int, QVariant> temp;

        for(const QString &value : cols) {
            temp.insert(col_indx, value);
            ++col_indx;
        }

        result.insert(row_indx, temp);
        ++row_indx;
    }

    return result;
}
