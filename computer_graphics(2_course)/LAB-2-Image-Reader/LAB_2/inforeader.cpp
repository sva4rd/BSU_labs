#include "inforeader.h"
#include <QDebug>

InfoReader::InfoReader(QWidget *parent): QWidget(parent)
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    setMinimumSize(600, 300);
    setWindowTitle("Image Reader");

    tableWidget = new QTableWidget(this);

    pickFiles = new QPushButton(this);
    pickFiles->setMinimumHeight(35);
    pickFiles->setMaximumWidth(200);
    pickFiles->setText("Pick Files");
    QFont font;
    font.setBold(true);
    pickFiles->setFont(font);

    grid = new QGridLayout(this);
    grid->addWidget(tableWidget, 0, 0, 3, 3);
    grid->addWidget(pickFiles, 3, 0);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    QHeaderView* header = tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    connect(pickFiles, &QPushButton::clicked, this, &InfoReader::getFiles);


    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
    tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Extension"));
    tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Size (bits)"));
    tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Size (pixels)"));
    tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Deepth"));
    tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Resolution (dpi)"));


    currentPath = "D:/";
    filters << "*.jpg" << "*.gif" << "*.tif" << "*.bmp" << "*.png" << "*.pcx" << "*.jpeg";
    dir.setNameFilters(filters);
}


void InfoReader::readAndSetInfo(QFileInfo fileInfo)
{
    image.load(currentPath + "/" + fileInfo.fileName());

    QString resolution = QVariant(image.width()).toString()+ "x" +QVariant(image.height()).toString();
    tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setItem(tableWidget->rowCount() - 1, 0, new QTableWidgetItem(fileInfo.fileName()));
    tableWidget->setItem(tableWidget->rowCount() - 1, 1, new QTableWidgetItem(fileInfo.suffix().toUpper()));

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, fileInfo.size());
    tableWidget->setItem(tableWidget->rowCount() - 1, 2, item);
    tableWidget->setItem(tableWidget->rowCount() - 1, 3, new QTableWidgetItem(resolution));
    tableWidget->setItem(tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QVariant(image.bitPlaneCount()).toString()));

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, round(image.dotsPerMeterX()/39.37));
    tableWidget->setItem(tableWidget->rowCount() - 1, 5, item);


    //#include <gdiplusheaders.h>
//    item = new QTableWidgetItem();
//    std::wstring fileName = std::wstring(fileInfo.fileName().begin(), fileInfo.fileName().end());
//    const WCHAR *newFileName = fileName.c_str();
//    Image *img = Image::FromFile(newFileName);
//    item->setData(Qt::DisplayRole, img->GetHorizontalResolution()/*int(image.dotsPerMeterX() / 39.37)*/);
//    tableWidget->setItem(tableWidget->rowCount() - 1, 4, item);
//    tableWidget->setItem(tableWidget->rowCount() - 1, 5, new QTableWidgetItem(QVariant(image.bitPlaneCount()).toString()));
}

void InfoReader::getFiles()
{
    QStringList fileName = QFileDialog ::getOpenFileNames(this, "Open Files", currentPath,
                                                          "Image(*jpg *gif *tif *bmp *png *pcx *jpeg);;Archieve(*zip)");
    if(fileName.isEmpty())
        return;

    tableWidget->setSortingEnabled(false);

    if (fileName[0].contains("zip"))
    {
        tempPath = QDir::currentPath() + "/temp";
        dir.setPath(tempPath);
        dir.mkdir(tempPath);

        fileInfo.setFile(fileName[0]);
        currentPath = fileInfo.path();

        QZipReader zipReader(fileName[0]);
        zipReader.extractAll(tempPath);

        QFileInfoList files = dir.entryInfoList();
        if (files.empty())
        {
            QMessageBox::information(this, "Information", "There are no files in the archive in the correct format");
            return;
        }

        fileInfo = files[0];
        QString saveCurrPath = currentPath;
        currentPath = fileInfo.path();

        for (int i = 0; i < files.size(); i++)
        {
            fileInfo = files[i];
            readAndSetInfo(fileInfo);
        }

        dir.removeRecursively();
        currentPath = saveCurrPath;
    }

    else
    {
        fileInfo.setFile(fileName[0]);
        currentPath = fileInfo.path();

        for (int i = 0; i < fileName.size(); i++)
        {
            fileInfo.setFile(fileName[i]);
            readAndSetInfo(fileInfo);
        }
    }

    tableWidget->sortByColumn(0,Qt::AscendingOrder);
    tableWidget->setSortingEnabled(true);
}

InfoReader::~InfoReader()
{
}

