#ifndef INFOREADER_H
#define INFOREADER_H

#include <QtWidgets>
#include <qzipreader_p.h>
#include <qzipwriter_p.h>

class InfoReader : public QWidget
{
    Q_OBJECT

public:
    InfoReader(QWidget *parent = nullptr);
    ~InfoReader();

private:
    QTableWidget *tableWidget;
    QPushButton *pickFiles;
    QGridLayout *grid;

    bool firstFile;
    QStringList suffixes;
    QString currentPath;

    QFileInfo fileInfo;
    QImage image;

    QDir dir;
    QString tempPath;
    QStringList filters;

    void setHeaders();
    void readAndSetInfo(QFileInfo fileInfo);

private slots:
    void getFiles();
};
#endif // INFOREADER_H
