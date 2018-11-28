#ifndef EXCELMODEL_H
#define EXCELMODEL_H

#include <QHash>
#include <QVariant>
#include <QAbstractTableModel>

namespace xlm
{
    typedef QHash<int, QHash<int, QVariant>> ExcelData;

    class ExcelModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit ExcelModel();
        explicit ExcelModel(const ExcelData &xld);
        explicit ExcelModel(const ExcelModel &xlm);
        ~ExcelModel();

        ExcelModel& operator= (const ExcelModel &rhs);

        ExcelData getExcelData() const;
        int getRowCount() const;
        int getColCount() const;

        void setExcelData(const ExcelData &xld);

    signals:
        void newValue(ExcelModel *xlm);

    private:
        ExcelData xlData;
        int c_row;
        int c_col;

        // Унаследовано от QAbstractTaleModel
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index,
                      int role = Qt::DisplayRole) const;
    };
}

xlm::ExcelData deserializeFromCSV(const QString &path, char separator);

#endif // EXCELMODEL_H
