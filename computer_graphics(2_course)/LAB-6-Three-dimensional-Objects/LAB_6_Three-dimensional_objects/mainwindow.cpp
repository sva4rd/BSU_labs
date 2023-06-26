#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    font.setBold(true);

    qApp->setStyle(QStyleFactory::create("Fusion"));
    setWindowTitle("Three-dimensional Letter");
    setMinimumSize(1000, 700);
    setFont(font);

    mainWgt = new QWidget;
    setCentralWidget(mainWgt);

    leftSide = new QWidget;
    rightSide = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWgt);
    mainLayout->addWidget(leftSide);
    mainLayout->addWidget(rightSide);

    letterWgt = new Letter;
    letterWgt->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    originLetter = new QPushButton("Original Letter");
    getColor = new QPushButton("Color");
    toOrigin = new QPushButton("To Origin");
    QHBoxLayout *wgtButtonsLayout = new QHBoxLayout;
    wgtButtonsLayout->addWidget(originLetter);
    wgtButtonsLayout->addWidget(getColor);
    wgtButtonsLayout->addWidget(toOrigin);
    wgtButtonsGroup = new QGroupBox;
    wgtButtonsGroup->setLayout(wgtButtonsLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout(rightSide);
    rightLayout->addWidget(letterWgt);
    rightLayout->addWidget(wgtButtonsGroup);


    projectionGroup = new QGroupBox;
    xyProj = new QPushButton("XY Projection");
    xzProj = new QPushButton("XZ Projection");
    zyProj = new QPushButton("ZY Projection");
    QVBoxLayout *projectionLayout = new QVBoxLayout;
    projectionLayout->addWidget(xyProj);
    projectionLayout->addWidget(xzProj);
    projectionLayout->addWidget(zyProj);
    projectionGroup->setLayout(projectionLayout);

    scalingGroup = new QGroupBox;
    xScaleLbl = new QLabel("X scale:");
    yScaleLbl = new QLabel("Y scale:");
    zScaleLbl = new QLabel("Z scale:");
    xScaleSpBx = new QDoubleSpinBox;
    xScaleSpBx->setRange(0.1, 7.0);
    xScaleSpBx->setValue(1.0);
    yScaleSpBx = new QDoubleSpinBox;
    yScaleSpBx->setRange(0.1, 7.0);
    yScaleSpBx->setValue(1.0);
    zScaleSpBx = new QDoubleSpinBox;
    zScaleSpBx->setRange(0.1, 7.0);
    zScaleSpBx->setValue(1.0);
    scaleButton = new QPushButton("Scale");
    QGridLayout *scaleLayout = new QGridLayout;
    scaleLayout->addWidget(xScaleLbl, 0, 0);
    scaleLayout->addWidget(yScaleLbl, 1, 0);
    scaleLayout->addWidget(zScaleLbl, 2, 0);
    scaleLayout->addWidget(xScaleSpBx, 0, 1, 1, 2);
    scaleLayout->addWidget(yScaleSpBx, 1, 1, 1, 2);
    scaleLayout->addWidget(zScaleSpBx, 2, 1, 1, 2);
    scaleLayout->addWidget(scaleButton, 3, 1, 1, 2);
    scalingGroup->setLayout(scaleLayout);

    rotationGroup = new QGroupBox;
    xRotationLbl = new QLabel("X rotation:");
    yRotationLbl = new QLabel("Y rotation:");
    zRotationLbl = new QLabel("Z rotation:");
    xRotationSpBx = new QDoubleSpinBox;
    xRotationSpBx->setRange(-1080.0, 1080.0);
    yRotationSpBx = new QDoubleSpinBox;
    yRotationSpBx->setRange(-1080.0, 1080.0);
    zRotationSpBx = new QDoubleSpinBox;
    zRotationSpBx->setRange(-1080.0, 1080.0);
    rotationButton = new QPushButton("Rotate");
    QGridLayout *rotationLayout = new QGridLayout;
    rotationLayout->addWidget(xRotationLbl, 0, 0);
    rotationLayout->addWidget(yRotationLbl, 1, 0);
    rotationLayout->addWidget(zRotationLbl, 2, 0);
    rotationLayout->addWidget(xRotationSpBx, 0, 1, 1, 2);
    rotationLayout->addWidget(yRotationSpBx, 1, 1, 1, 2);
    rotationLayout->addWidget(zRotationSpBx, 2, 1, 1, 2);
    rotationLayout->addWidget(rotationButton, 3, 1, 1, 2);
    rotationGroup->setLayout(rotationLayout);

    transferingGroup = new QGroupBox;
    xTransferLbl = new QLabel("X transfer:");
    yTransferLbl = new QLabel("Y transfer:");
    zTransferLbl = new QLabel("Z transfer:");
    xTransferSpBx = new QDoubleSpinBox;
    xTransferSpBx->setRange(-10.0, 10.0);
    yTransferSpBx = new QDoubleSpinBox;
    yTransferSpBx->setRange(-10.0, 10.0);
    zTransferSpBx = new QDoubleSpinBox;
    zTransferSpBx->setRange(-10.0, 10.0);
    transferButton = new QPushButton("Transfer");
    QGridLayout *transferLayout = new QGridLayout;
    transferLayout->addWidget(xTransferLbl, 0, 0);
    transferLayout->addWidget(yTransferLbl, 1, 0);
    transferLayout->addWidget(zTransferLbl, 2, 0);
    transferLayout->addWidget(xTransferSpBx, 0, 1, 1, 2);
    transferLayout->addWidget(yTransferSpBx, 1, 1, 1, 2);
    transferLayout->addWidget(zTransferSpBx, 2, 1, 1, 2);
    transferLayout->addWidget(transferButton, 3, 1, 1, 2);
    transferingGroup->setLayout(transferLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftSide);
    leftLayout->addWidget(projectionGroup);
    leftLayout->addWidget(scalingGroup);
    leftLayout->addWidget(rotationGroup);
    leftLayout->addWidget(transferingGroup);
    leftLayout->addStretch(1);


    connect(originLetter, &QPushButton::clicked, this, &MainWindow::drawOriginLetter);
    connect(getColor, &QPushButton::clicked, this, &MainWindow::setColor);
    connect(toOrigin, &QPushButton::clicked, this, &MainWindow::goToOrigin);

    connect(xyProj, &QPushButton::clicked, this, &MainWindow::xyProjection);
    connect(xzProj, &QPushButton::clicked, this, &MainWindow::xzProjection);
    connect(zyProj, &QPushButton::clicked, this, &MainWindow::zyProjection);

    connect(scaleButton, &QPushButton::clicked, this, &MainWindow::scaleLetter);
    connect(rotationButton, &QPushButton::clicked, this, &MainWindow::rotateLetter);
    connect(transferButton, &QPushButton::clicked, this, &MainWindow::transferLetter);

    QAction *infoAction = new QAction ("Info", this);
    infoAction->setShortcut(QKeySequence("Ctrl+I"));
    connect(infoAction, SIGNAL(triggered()), this, SLOT(showInfo()));
    menuBar()->addAction(infoAction);
}

void MainWindow::keyPressEvent(QKeyEvent* pe)
{
    letterWgt->keyPressEvent(pe);
    letterWgt->updateGL();
}

void MainWindow::drawOriginLetter()
{
    letterWgt->check=9;
    letterWgt->updateGL();
}

void MainWindow::setColor()
{
    letterWgt->colour = QColorDialog::getColor(letterWgt->colour);
}

void MainWindow::goToOrigin()
{
    letterWgt->defaultScene();
    letterWgt->updateGL();
}

void MainWindow::xyProjection()
{
    letterWgt->check=1;
    letterWgt->updateGL();
}

void MainWindow::xzProjection()
{
    letterWgt->check=2;
    letterWgt->updateGL();
}

void MainWindow::zyProjection()
{
    letterWgt->check=3;
    letterWgt->updateGL();
}

void MainWindow::scaleLetter()
{
    letterWgt->x_scale = xScaleSpBx->value();
    letterWgt->y_scale = yScaleSpBx->value();
    letterWgt->z_scale = zScaleSpBx->value();
    letterWgt->check=4;
    letterWgt->updateGL();
}

void MainWindow::rotateLetter()
{
    letterWgt->check=6;
    letterWgt->angle=xRotationSpBx->value();
    letterWgt->updateGL();
    letterWgt->check=7;
    letterWgt->angle=yRotationSpBx->value();
    letterWgt->updateGL();
    letterWgt->check=8;
    letterWgt->angle=zRotationSpBx->value();
    letterWgt->updateGL();
}

void MainWindow::transferLetter()
{
    letterWgt->x_transfer = xTransferSpBx->value();
    letterWgt->y_transfer = yTransferSpBx->value();
    letterWgt->z_transfer = zTransferSpBx->value();
    letterWgt->check=5;
    letterWgt->updateGL();
}

void MainWindow::showInfo()
{
    QMessageBox::information(this,"Interaction instructions",
                                  "To zoom in press \"+\" \n"
                                                 "To zoom out press \"-\" \n"
                                                 "To rotate up press \"w\" \n"
                                                 "To rotate down press \"s\" \n"
                                                 "To rotate left press \"a\" \n"
                                                 "To rotate right press \"d\" \n"
                                                 "To translate down press \"z\" \n"
                                                 "To translate up press \"x\" \n");
}

MainWindow:: ~MainWindow()
{
    delete letterWgt;
}
