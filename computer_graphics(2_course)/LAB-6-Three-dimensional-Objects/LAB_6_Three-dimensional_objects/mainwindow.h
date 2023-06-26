#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "letter.h"
//#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *mainWgt;
    QWidget *leftSide;
    QWidget *rightSide;

    Letter *letterWgt;
    QGroupBox *wgtButtonsGroup;
    QPushButton *originLetter;
    QPushButton *getColor;
    QPushButton *toOrigin;

    QGroupBox *projectionGroup;
    QPushButton *xyProj;
    QPushButton *xzProj;
    QPushButton *zyProj;

    QGroupBox *scalingGroup;
    QLabel *xScaleLbl;
    QLabel *yScaleLbl;
    QLabel *zScaleLbl;
    QDoubleSpinBox *xScaleSpBx;
    QDoubleSpinBox *yScaleSpBx;
    QDoubleSpinBox *zScaleSpBx;
    QPushButton *scaleButton;

    QGroupBox *rotationGroup;
    QLabel *xRotationLbl;
    QLabel *yRotationLbl;
    QLabel *zRotationLbl;
    QDoubleSpinBox *xRotationSpBx;
    QDoubleSpinBox *yRotationSpBx;
    QDoubleSpinBox *zRotationSpBx;
    QPushButton *rotationButton;

    QGroupBox *transferingGroup;
    QLabel *xTransferLbl;
    QLabel *yTransferLbl;
    QLabel *zTransferLbl;
    QDoubleSpinBox *xTransferSpBx;
    QDoubleSpinBox *yTransferSpBx;
    QDoubleSpinBox *zTransferSpBx;
    QPushButton *transferButton;

    QFont font;

    void keyPressEvent(QKeyEvent* pe);

private slots:

    void drawOriginLetter();
    void setColor();
    void goToOrigin();

    void xyProjection();
    void xzProjection();
    void zyProjection();

    void scaleLetter();
    void rotateLetter();
    void transferLetter();

    void showInfo();
};

#endif // MAINWINDOW_H
