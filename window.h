#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QStringRef>
#include <QDateTime>
#include <QAbstractEventDispatcher>
#include <QTimer>

#include "math.h"
#include "openglrender/openglrender.h"

#define YOFFSET 50

namespace Ui {
class Window;
}



class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QOpenGLWidget *parent = 0);
    ~Window();

    //Keypress events:
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    //void clearButton_clicked();
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);

    void updateCamera();

private slots:

    void awake();

    void aboutToBlock();

    void doWorkInIdle();

    void on_clearBtn_clicked();

    void on_redInput_textEdited(const QString &arg1);

    void on_greenInput_textEdited(const QString &arg1);

    void on_blueInput_textEdited(const QString &arg1);

    void on_lineWidthEdit_textEdited(const QString &arg1);

    void on_drawLineBtn_clicked();

    void on_editLineBtn_clicked();

    void on_drawCircleBtn_clicked();

    void on_drawingTypesTab_currentChanged(int index);

    void on_polyAddPointBtn_clicked();

    void on_polyAddFinalPointBtn_clicked();

    void on_randColorsBtn_clicked();

    void on_ellipseThetaInput_textEdited(const QString &arg1);

    void on_drawEllipseBtn_clicked();

    void on_drawCycloidBtn_clicked();

    void on_polygonClosed_clicked();

    void on_polygonFill_clicked();

    void on_polygonPrebuiltFill_clicked();

    void on_polyPrebuiltCmb_currentIndexChanged(int index);

    void on_polygonPrebuildSet_clicked();

    void on_polygonSet_clicked();

    void on_polygonFilled_clicked();

    void on_polyGoraud_clicked();

    void on_cameraXSlider_valueChanged(int value);

    void on_cameraYSlider_valueChanged(int value);

    void on_cameraZSlider_valueChanged(int value);

    void on_cameraXRotSlider_valueChanged(int value);

    void on_cameraYRotSlider_valueChanged(int value);

    void on_cameraZRotSlider_valueChanged(int value);

    void on_rotResetBtn_clicked();

    void on_transResetBtn_clicked();

    void on_loadObjButton_clicked();

    void on_cameraZoomSlider_valueChanged(int value);

    void on_cameraAspectSlider_1_valueChanged(int value);

    void on_cameraAspectSlider_2_valueChanged(int value);

    void on_cameraXSliderEdit_textEdited(const QString &arg1);

    void on_cameraYSliderEdit_textEdited(const QString &arg1);

    void on_cameraZSliderEdit_textEdited(const QString &arg1);

    void on_cameraXRotSliderEdit_textEdited(const QString &arg1);

    void on_cameraYRotSliderEdit_textEdited(const QString &arg1);

    void on_cameraZRotSliderEdit_textEdited(const QString &arg1);

    void on_LightingBox_clicked(bool checked);

    void on_objectTypeRadioBtn_3_clicked();

    void on_objectTypeRadioBtn_2_clicked();

    void on_objectTypeRadioBtn_clicked();

    void on_zClippingNearSlider_valueChanged(int value);

    void on_zClippingFarSlider_valueChanged(int value);

    void on_cameraZoomSliderEdit_textEdited(const QString &arg1);

    void on_objTransButton_clicked();

    void on_objRotButton_clicked();

    void on_modelListView_currentRowChanged(int currentRow);

    void on_objScaleButton_clicked();

    void on_animationPathButton_clicked();

    void on_LightingBox_clicked();

private:
    Ui::Window *ui;
    //GLMmodel* Window::loadplayer(QString filename);

    QAbstractEventDispatcher *dispatcher;
    QTime lastAwake;
    QTime lastBlock;

    bool clicked;

    bool buildingPolygon;

    int xRot;
    int zRot;

    bool playgame;
};

#endif // WINDOW_H
