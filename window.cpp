#include "window.h"
#include "ui_window.h"

Window::Window(QOpenGLWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    dispatcher = QAbstractEventDispatcher::instance();
    connect(dispatcher, SIGNAL(awake()), SLOT(awake()));
    connect(dispatcher, SIGNAL(aboutToBlock()), SLOT(aboutToBlock()));

    //Sets an idle function to run after 10 milliseconds
    QTimer::singleShot(2000, this, SLOT(doWorkInIdle()));

    ui->setupUi(this);

    this->clicked = false;

    this->buildingPolygon = false;

    //Load player model
    //this->ui->openGLRenderWindow->push(new openGLMesh("../battleships/obj/f-16ver2.obj"));
<<<<<<< HEAD
    this->ui->openGLRenderWindow->push(new openGLMesh("../battleships/obj/shipboat2.obj"));
    ((openGLMesh*)ui->openGLRenderWindow->pop())->scale(0.3f, 0.3f, 0.3f);
    qDebug()<<"Player loaded";
=======
    this->ui->openGLRenderWindow->push(new ship("../battleships/obj/shipboat2.obj"));
    ((openGLMesh*)ui->openGLRenderWindow->pop())->scale(0.2f, 0.2f, 0.2f);
>>>>>>> origin/master
    //((openGLMesh*)ui->openGLRenderWindow->pop())->rotate(90.0f, 0.0f, 0.0f);
    //((openGLMesh*)ui->openGLRenderWindow->pop())->rotate(90.0f, 180.0f, 0.0f);
}

Window::~Window()
{
    delete ui;
}

void Window::awake()
{
    //lastAwake = QTime::currentTime();
    //qDebug() << "Slept for " << lastBlock.msecsTo(lastAwake) << " msec";



    //Paint the scene.
    //ui->openGLRenderWindow->paintGL();
}

void Window::aboutToBlock()
{
    //lastBlock = QTime::currentTime();
    //qDebug() << "Worked for " << lastAwake.msecsTo(lastBlock) << " msec";

    //ui->openGLRenderWindow->paintGL();
}

void Window::doWorkInIdle()
{
    ui->openGLRenderWindow->setFocus();


    //qDebug()<<"old:" <<lastBlock.msecsTo(lastAwake) <<lastAwake.msecsTo(lastBlock);
    lastAwake = QTime::currentTime();
    //qDebug()<<"new:" <<lastBlock.msecsTo(lastAwake) <<lastAwake.msecsTo(lastBlock);
    //Sets this idle function to run again after 10 milliseconds
    QTimer::singleShot(0, this, SLOT(doWorkInIdle()));

    if (lastBlock.msecsTo(lastAwake) >0)
    {
        //Spawn enemies
        this->ui->openGLRenderWindow->spawnEnemies();

        //Process input queue
        this->ui->openGLRenderWindow->processInput();

        //update objects to new positions
        this->ui->openGLRenderWindow->update(lastBlock.msecsTo(lastAwake));

        //Check for collisions
        this->ui->openGLRenderWindow->checkCollisions();

        //Update camera position
        this->ui->openGLRenderWindow->updateCamera();

        ui->openGLRenderWindow->paintGL();
    }
    lastBlock = QTime::currentTime();
}

void Window::keyPressEvent(QKeyEvent *ev)
{
    //Give focus back to the openGL window.
    //if (!ui->openGLRenderWindow->hasFocus())
    //ui->openGLRenderWindow->setFocus();

    if( !ev->isAutoRepeat())
    {
        //qDebug()<<"Pressed:" <<ev->key();
        this->ui->openGLRenderWindow->pushInput(ev->key());
    }

}

void Window::keyReleaseEvent(QKeyEvent *ev)
{

    if( !ev->isAutoRepeat())
    {
        //qDebug()<<"Released:" <<ev->key();
        this->ui->openGLRenderWindow->popInput(ev->key());
    }
}

void Window::mouseMoveEvent(QMouseEvent *ev)
{

    if (clicked && ev->x()>=10 && ev->x()<=OGLWIDTH+10 && ev->y()>=YOFFSET && ev->y() <=OGLHEIGHT+YOFFSET)
    {
        int x = (ev->x()-10)*2-OGLWIDTH;
        int y = (-1)*((ev->y()-YOFFSET)*2-OGLHEIGHT);

        x *= ui->cameraZoomSlider->value()/5;
        y *= ui->cameraZoomSlider->value()/5;

        float z = 0.0f;

        //Rotate upon x
        z = (-1)*(y * sin(ui->cameraXRotSlider->value()*(3.14159265/180)))/OGLHEIGHT;
        y = (y * cos(ui->cameraXRotSlider->value()*(3.14159265/180)));

        //Translate upon x
        x += (-1)*((float)ui->cameraXSlider->value()/100)*OGLWIDTH;
        //Translate upon y
        y += (-1)*((float)ui->cameraYSlider->value()/100)*OGLHEIGHT;
        //Translate upon z


        //qDebug()<<y;

        if (!ui->openGLRenderWindow->isEmpty())
        {
            openGLObject *o = ui->openGLRenderWindow->pop();
            o->setCurrent(false);
            if (o->name() == QString("openGLLine"))
            {
                ui->xEndInput->setText(QString::number(x));
                ui->yEndInput->setText(QString::number(y));

                //l->setP2(QPoint(ev->x()-10,(-1)*(ev->y()-OGLHEIGHT-32)));
                ((openGLLine*)o)->setP2(x,y,z);
            }
            else if (o->name() == QString("openGLCircle"))
            {
                //qDebug()<<"CIRCLE R: " <<sqrt((( (((openGLCircle*)o)->getX()-x) )*((((openGLCircle*)o)->getX()-x))+((((openGLCircle*)o)->getY()-y))*((((openGLCircle*)o)->getY()-y))));
                //((openGLCircle*)o)->setColor(QColor(ui->redBGInput->text().toInt(),ui->greenBGInput->text().toInt(),ui->blueBGInput->text().toInt()));
                //((openGLCircle*)o)->draw();

                ((openGLCircle*)o)->setR(sqrt((( (((openGLCircle*)o)->getX()-x) )*((((openGLCircle*)o)->getX()-x))+((((openGLCircle*)o)->getY()-y))*((((openGLCircle*)o)->getY()-y)))));
                ui->circleRinput->setText(QString::number(((openGLCircle*)o)->getR()));
                ((openGLCircle*)o)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
                ((openGLCircle*)o)->draw();

            }
            else if (o->name() == QString("openGLPolygon"))
            {
                //qDebug()<<"x:" <<x <<"y:" <<y <<" ((openGLPolygon*)o)->size():" <<((openGLPolygon*)o)->size();

                o = ui->openGLRenderWindow->pop();

                ((openGLPolygon*)o)->removeAt(((openGLPolygon*)o)->size()-1);
                ((openGLPolygon*)o)->add(new openGLPoint(x,y));

                //ui->openGLRenderWindow->removeAt(((openGLPolygon*)o)->size());
                //ui->openGLRenderWindow->push(new openGLPoint(x,y));

                //o = ui->openGLRenderWindow->pop();
                //((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->
                //((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setP2(x,y);
                //((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),new openGLPoint(x,y)));
            }

            ui->openGLRenderWindow->paintGL();
        }
    }
}

void Window::mousePressEvent(QMouseEvent *ev){

    int x = (ev->x()-10)*2-OGLWIDTH;
    int y = (-1)*((ev->y()-YOFFSET)*2-OGLHEIGHT);

    if (ui->randColorChk->isChecked())
        on_randColorsBtn_clicked();

    openGLObject *o;

    if(!clicked && (ev->button() == Qt::LeftButton) && ev->x()>=10 && ev->x()<=OGLWIDTH+10 && ev->y()>=YOFFSET && ev->y() <=OGLHEIGHT+YOFFSET)
    {
        clicked = true;

        openGLLine *newLine;
        openGLCircle *newCircle;
        openGLPolygon *newPolygon;

        switch(ui->drawingTypesTab->currentIndex())
        {
        case 0:
            //Case Line
            ui->xStartInput->setText(QString::number(x));
            ui->yStartInput->setText(QString::number(y));
            newLine = new openGLLine(x,y,x,y);
            newLine->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
            newLine->setWidth(ui->lineWidthEdit->text().toInt());
            ui->openGLRenderWindow->push(newLine);
            break;
        case 1:
            //Case Circle
            ui->circleXinput->setText(QString::number(x));
            ui->circleYinput->setText(QString::number(y));
            ui->circleRinput->setText(QString::number(0));
            newCircle = new openGLCircle(x,y,0);
            newCircle->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
            newCircle->setFilled(ui->circleFilled->isChecked());
            newCircle->setFillColor(QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt()));
            switch (ui->circleTypeCmb->currentIndex())
            {
            case 0:
                newCircle->setType(QString("FULL"));
                break;
            case 1:
                newCircle->setType(QString("SEMINORTH"));
                break;
            case 2:
                newCircle->setType(QString("SEMIEAST"));
                break;
            case 3:
                newCircle->setType(QString("SEMISOUTH"));
                break;
            case 4:
                newCircle->setType(QString("SEMIWEST"));
                break;
            case 5:
                newCircle->setType(QString("QUADNW"));
                break;
            case 6:
                newCircle->setType(QString("QUADNE"));
                break;
            case 7:
                newCircle->setType(QString("QUADSE"));
                break;
            case 8:
                newCircle->setType(QString("QUADSW"));
                break;
            }
            ui->openGLRenderWindow->push(newCircle);
            break;
        case 2:
            if (buildingPolygon)
            {
                o = ui->openGLRenderWindow->pop();
                ((openGLPolygon*)o)->add(new openGLPoint(x, y, QColor(rand()%256,rand()%256,rand()%256)));
                ((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
            }
            else
            {
                this->buildingPolygon = true;
                newPolygon = new openGLPolygon(new openGLPoint(x,y, QColor(rand()%256,rand()%256,rand()%256)));
                newPolygon->add(new openGLPoint(x,y, QColor(rand()%256,rand()%256,rand()%256)));
                newPolygon->setColor(QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt()));
                //newPolygon->at(0)->setColor(QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt()));
                ui->openGLRenderWindow->push(newPolygon);
                //ui->polygonClosed->setEnabled(ui->polygonClosed->isChecked());
                newPolygon->setClosed(ui->polygonClosed->isChecked());
                newPolygon->setGoraud(ui->polyGoraud->isChecked());
                if(ui->polygonFilled->isChecked())
                    newPolygon->finish();
                else
                    newPolygon->unFinish();
            }
            break;
        default:
            qDebug()<<"Unknown Object Type" <<ui->drawingTypesTab->currentIndex();
            clicked = false;
            break;
        }

        ui->openGLRenderWindow->paintGL();
    }
    //If the middle mouse button is clicked
    else if (!this->clicked && (ev->button() == Qt::MiddleButton || ev->button() == Qt::RightButton) && ev->x()>=10 && ev->x()<=OGLWIDTH+10 && ev->y()>=YOFFSET && ev->y() <=OGLHEIGHT+YOFFSET)
    {
        switch(ui->drawingTypesTab->currentIndex())
        {
        case 2:
            //qDebug()<<"this->buildingPolygon: "<<this->buildingPolygon;
            if (this->buildingPolygon)
            {
                this->buildingPolygon = false;

                o = ui->openGLRenderWindow->pop();
                //((openGLPolygon*)o)->add(new openGLPoint(x,y));
                //((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),new openGLPoint(x,y)));
                //((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));

                if(ui->polygonClosed->isChecked())
                {
                    //o = ui->openGLRenderWindow->pop();
                    //((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),((openGLPolygon*)o)->at(0)->getP1()));
                    //((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
                    if(ui->polygonFilled->isChecked())
                    {
                        ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
                        ((openGLPolygon*)o)->finish();
                    }
                }
                else
                {
                }
                ui->polygonClosed->setEnabled(true);
                buildingPolygon = false;
                this->clicked = false;
            }
            break;

        }
        ui->openGLRenderWindow->paintGL();
    }
    //If the right mouse button is clicked
    else if(ev->button() == Qt::RightButton)
    {
        //qDebug()<<"RightButton";
        if (ui->openGLRenderWindow->size() > 0)
        {
            o = ui->openGLRenderWindow->pop();
            //((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),new openGLPoint(x,y)));
            buildingPolygon = false;
            //qDebug()<<"Poly1: " <<((openGLPolygon*)o)->isFinished();
            ((openGLPolygon*)o)->finish();
            //qDebug()<<"Poly2: " <<((openGLPolygon*)o)->isFinished();
            ui->openGLRenderWindow->paintGL();
        }
    }
}

void Window::mouseReleaseEvent(QMouseEvent *ev){



    if(clicked && (ev->button() == Qt::LeftButton) && ev->x()>=10 && ev->x()<=OGLWIDTH+10 && ev->y()>=YOFFSET && ev->y() <=OGLHEIGHT+YOFFSET){

        openGLObject *o;
        QString s;

        //clicked = false;
        int x = (ev->x()-10)*2-OGLWIDTH;
        int y = (-1)*((ev->y()-YOFFSET)*2-OGLHEIGHT);

        if (!ui->openGLRenderWindow->isEmpty())
        {
            switch(ui->drawingTypesTab->currentIndex())
            {
            case 0:
                //Case Line
                clicked = false;
                ui->xEndInput->setText(QString::number(x));
                ui->yEndInput->setText(QString::number(y));
                o = ui->openGLRenderWindow->pop();
                ((openGLLine*)o)->setP2(x,y);

                //Add the line to the list
                s = QString(("LINE: P1(") + QString::number(((openGLLine*)o)->x1()) + QString(",") + QString::number(((openGLLine*)o)->y1()) + QString(") P2(")  + QString::number(((openGLLine*)o)->x2()) + QString(",") + QString::number(((openGLLine*)o)->y2()));
                s += QString(") r:") + ui->redInput->text();
                s += QString(" g:") + ui->greenInput->text();
                s += QString(" b:") + ui->blueInput->text();
                s += QString(" width:") + ui->lineWidthEdit->text();
                //ui->lineLst->addItem(s);

                break;
            case 1:
                //Case Circle
                clicked = false;
                o = ui->openGLRenderWindow->pop();
                ((openGLCircle*)o)->setR(sqrt((( (((openGLCircle*)o)->getX()-x) )*((((openGLCircle*)o)->getX()-x))+((((openGLCircle*)o)->getY()-y))*((((openGLCircle*)o)->getY()-y)))));
                ui->circleRinput->setText(QString::number(((openGLCircle*)o)->getR()));

                //Add the circle to the list
                s = QString(("CIRCLE: (") + QString::number(((openGLCircle*)o)->getX()) + QString(",") + QString::number(((openGLCircle*)o)->getY()) + QString(") radius:")  + QString::number(((openGLCircle*)o)->getR()));
                s += QString(") r:") + ui->redInput->text();
                s += QString(" g:") + ui->greenInput->text();
                s += QString(" b:") + ui->blueInput->text();
                s += QString(" fill: ") + QString::number(ui->circleFilled->isChecked());
                s += QString(" fr: ") + ui->fillRed->text();
                s += QString(" fg: ") + ui->fillGreen->text();
                s += QString(" fb: ") + ui->fillBlue->text();
                //ui->lineLst->addItem(s);

                break;
            case 2:
                //Case Polygon
                clicked = false;
                o = ui->openGLRenderWindow->pop();
                ((openGLPolygon*)o)->removeAt(((openGLPolygon*)o)->size()-1);
                ((openGLPolygon*)o)->add(new openGLPoint(x,y, QColor(rand()%256,rand()%256,rand()%256)));
                //o = ui->openGLRenderWindow->pop();
                //((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setP2(x,y);

                //Add the polygon's line to the list
                //Add the line to the list
                //s = QString(("POLYGON: P1(") + QString::number(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP1()->getX()) + QString(",") + QString::number(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP1()->getY()) + QString(") P2(")  + QString::number(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2()->getX()) + QString(",") + QString::number(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2()->getY()));
                //s += QString(") r:") + ui->redInput->text();
                //s += QString(" g:") + ui->greenInput->text();
                //s += QString(" b:") + ui->blueInput->text();
                //s += QString(" width:") + ui->lineWidthEdit->text();
                //ui->lineLst->addItem(s);

                break;
            default:
                clicked = false;
                break;
            }


            //o->setCurrent(false);
            ui->openGLRenderWindow->paintGL();
        }
    }
}

void Window::on_clearBtn_clicked()
{
    ui->openGLRenderWindow->setBackgroundColor(ui->redBGInput->text().toInt(),ui->greenBGInput->text().toInt(),ui->blueBGInput->text().toInt(),255);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //makeCurrent();
    //this->swapBuffers();
    //clearGL();

    //ui->lineLst->clearSelection();

    //ui->lineLst->clear();

    ui->openGLRenderWindow->clearObjects();
    ui->openGLRenderWindow->clearGL();

    this->clicked = false;

    this->buildingPolygon = false;

    ui->openGLRenderWindow->paintGL();
}

void Window::on_redInput_textEdited(const QString &arg1)
{
    //Reset to 0 if bad input
    if (arg1.toInt() == 0)
        ui->redInput->setText("0");
}

void Window::on_greenInput_textEdited(const QString &arg1)
{
    //Reset to 0 if bad input
    if (arg1.toInt() == 0)
        ui->greenInput->setText("0");
}

void Window::on_blueInput_textEdited(const QString &arg1)
{
    //Reset to 0 if bad input
    if (arg1.toInt() == 0)
        ui->blueInput->setText("0");
}

void Window::on_lineWidthEdit_textEdited(const QString &arg1)
{
    if (arg1.toInt() == 0)
        ui->lineWidthEdit->setText("1");
    if (arg1.toInt() > 20)
        ui->lineWidthEdit->setText("20");
    ui->openGLRenderWindow->setLineSizeGL(arg1.toInt());
}

void Window::on_drawLineBtn_clicked()
{
    QString s;

    //qDebug()<< ui->xStartInput->text().toFloat();
    openGLLine *newLine = new openGLLine(ui->xStartInput->text().toFloat(),(ui->yStartInput->text().toFloat()),ui->xEndInput->text().toFloat(),(ui->yEndInput->text().toFloat()));
    newLine->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
    newLine->setWidth(ui->lineWidthEdit->text().toInt());
    ui->openGLRenderWindow->push(newLine);
    ui->openGLRenderWindow->setColorGL( ui->redInput->text().toInt(), ui->greenInput->text().toInt(),ui->blueInput->text().toInt());

    //Add the line to the list
    s = QString(("LINE: P1(") + QString::number(newLine->x1()) + QString(",") + QString::number(newLine->y1()) + QString(") P2(")  + QString::number(newLine->x2()) + QString(",") + QString::number(newLine->y2()));
    s += QString(") r:") + ui->redInput->text();
    s += QString(" g:") + ui->greenInput->text();
    s += QString(" b:") + ui->blueInput->text();
    s += QString(" width:") + ui->lineWidthEdit->text();
    //ui->lineLst->addItem(s);

    ui->openGLRenderWindow->paintGL();
}

void Window::on_editLineBtn_clicked()
{

    /*if (!ui->openGLRenderWindow->isEmpty() && ui->lineLst->currentRow() >=0)
    {

        if (ui->openGLRenderWindow->size() > ui->lineLst->currentRow())
        {
            if (ui->lineLst->item(ui->lineLst->currentRow())->text().contains("LINE"))
            {

            }
        }
    }*/
    /*//Get selected line
    openGLLine *l = ui->openGLRenderWindow->at(ui->lineLst->currentRow());

    //Set line's new P1 and P2
    l->setP1(ui->xStartInput->text().toInt(),(ui->yStartInput->text().toInt()));
    l->setP2(ui->xEndInput->text().toInt(),(ui->yEndInput->text().toInt()));

    //Update the line's colors
    l->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));

    //Update the line's width
    l->setWidth(ui->lineWidthEdit->text().toInt());

    ui->openGLRenderWindow->clearGL();
    ui->openGLRenderWindow->paintGL();

    //Update the list with new line data
    QString s = QString(("P1(") + QString::number(l->x1()) + QString(",") + QString::number(l->y1()) + QString(") P2(")  + QString::number(l->x2()) + QString(",") + QString::number(l->y2()));
    s += QString(") r:") + QString(QString::number(ui->redSlider->value()));
    s += QString(" g:") + QString(QString::number(ui->greenSlider->value()));
    s += QString(" b:") + QString(QString::number(ui->blueSlider->value()));
    ui->lineLst->currentItem()->setText(s);*/
}

void Window::on_drawCircleBtn_clicked()
{
    openGLCircle* newCircle = new openGLCircle(ui->circleXinput->text().toFloat(),ui->circleYinput->text().toFloat(),ui->circleRinput->text().toFloat());

    newCircle->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
    newCircle->setFilled(ui->circleFilled->isChecked());
    newCircle->setFillColor(QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt()));

    switch (ui->circleTypeCmb->currentIndex())
    {
    case 0:
        newCircle->setType(QString("FULL"));
        break;
    case 1:
        newCircle->setType(QString("SEMINORTH"));
        break;
    case 2:
        newCircle->setType(QString("SEMIEAST"));
        break;
    case 3:
        newCircle->setType(QString("SEMISOUTH"));
        break;
    case 4:
        newCircle->setType(QString("SEMIWEST"));
        break;
    case 5:
        newCircle->setType(QString("QUADNW"));
        break;
    case 6:
        newCircle->setType(QString("QUADNE"));
        break;
    case 7:
        newCircle->setType(QString("QUADSE"));
        break;
    case 8:
        newCircle->setType(QString("QUADSW"));
        break;
    }

    ui->openGLRenderWindow->push(newCircle);

    ui->openGLRenderWindow->paintGL();
}

void Window::on_drawingTypesTab_currentChanged(int index)
{
    if( this->buildingPolygon)
    {
        openGLObject* o;
        this->buildingPolygon = false;

        o = ui->openGLRenderWindow->pop();

        if(ui->polygonClosed->isChecked())
        {
            if(ui->polygonFilled->isChecked())
            {
                ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
                ((openGLPolygon*)o)->finish();
            }
        }
        ui->openGLRenderWindow->paintGL();
    }
}

void Window::on_polyAddPointBtn_clicked()
{

    openGLObject* o;
    openGLPolygon* newPolygon;

    if (buildingPolygon)
    {
        o = ui->openGLRenderWindow->pop();
        ((openGLPolygon*)o)->add(new openGLPoint(ui->xPolyInput->text().toFloat(), ui->yPolyInput->text().toFloat(), QColor(rand()%256,rand()%256,rand()%256)));
        ((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
    }
    else
    {
        this->buildingPolygon = true;
        newPolygon = new openGLPolygon(new openGLPoint(ui->xPolyInput->text().toFloat(),ui->yPolyInput->text().toFloat(), QColor(rand()%256,rand()%256,rand()%256)));
        newPolygon->add(new openGLPoint(ui->xPolyInput->text().toFloat(),ui->yPolyInput->text().toFloat(), QColor(rand()%256,rand()%256,rand()%256)));
        newPolygon->at(0)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
        ui->openGLRenderWindow->push(newPolygon);
        ui->polygonClosed->setEnabled(ui->polygonClosed->isChecked());
        newPolygon->setGoraud(ui->polyGoraud->isChecked());
    }

    /*openGLObject *o;
    openGLPolygon *newPolygon;

    int x = ui->xPolyInput->text().toFloat();
    int y = ui->yPolyInput->text().toFloat();


    if (buildingPolygon)
    {
        o = ui->openGLRenderWindow->pop();
        ((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),new openGLPoint(x,y)));
        ((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
    }
    else
    {
        ui->polygonClosed->setEnabled(false);
        this->buildingPolygon = true;
        newPolygon = new openGLPolygon(new openGLLine(x,y,x,y));
        newPolygon->at(0)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
        ui->openGLRenderWindow->push(newPolygon);
        ui->polygonClosed->setEnabled(ui->polygonClosed->isChecked());
    }
*/
    ui->openGLRenderWindow->paintGL();
}

void Window::on_polyAddFinalPointBtn_clicked()
{
    openGLObject *o;

    if (this->buildingPolygon)
    {
        this->buildingPolygon = false;

        o = ui->openGLRenderWindow->pop();

        if(ui->polygonClosed->isChecked())
        {
            if(ui->polygonFilled->isChecked())
            {
                ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
                ((openGLPolygon*)o)->finish();
            }
        }
        else
        {
        }
        ui->polygonClosed->setEnabled(true);
        buildingPolygon = false;
        this->clicked = false;
    }

    /*

    int x = ui->xPolyInput->text().toFloat();
    int y = ui->yPolyInput->text().toFloat();

    if (this->buildingPolygon)
    {
        this->buildingPolygon = false;

        o = ui->openGLRenderWindow->pop();
        ((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),new openGLPoint(x,y)));
        ((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));

        if(ui->polygonClosed->isChecked())
        {
            o = ui->openGLRenderWindow->pop();
            ((openGLPolygon*)o)->add(new openGLLine(((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->getP2(),((openGLPolygon*)o)->at(0)->getP1()));
            ((openGLPolygon*)o)->at(((openGLPolygon*)o)->size()-1)->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));
            if(ui->polygonFilled->isChecked())
            {
                ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
                ((openGLPolygon*)o)->finish();
            }
        }
        else
        {
        }
        ui->polygonClosed->setEnabled(true);
        buildingPolygon = false;
        this->clicked = false;
        ui->polygonClosed->setEnabled(true);
    }
*/
    ui->openGLRenderWindow->paintGL();
}

void Window::on_randColorsBtn_clicked()
{
    ui->redInput->setText(QString::number(rand()%256));
    ui->greenInput->setText(QString::number(rand()%256));
    ui->blueInput->setText(QString::number(rand()%256));
}

void Window::on_ellipseThetaInput_textEdited(const QString &arg1)
{
    if (arg1.toInt() == 0)
        ui->ellipseThetaInput->setText("0");
    else if (arg1.toInt() > 360)
        ui->ellipseThetaInput->setText("360");
}

void Window::on_drawEllipseBtn_clicked()
{
    if (ui->randColorChk->isChecked())
        on_randColorsBtn_clicked();

    openGLEllipse *e = new openGLEllipse(ui->ellipseCXinput->text().toInt(),ui->ellipseCYinput->text().toInt(),ui->ellipseRXinput->text().toInt(),ui->ellipseRYinput->text().toInt(),ui->ellipseThetaInput->text().toInt());
    e->setColor(QColor(ui->redInput->text().toInt(),ui->greenInput->text().toInt(),ui->blueInput->text().toInt()));

    ui->openGLRenderWindow->push(e);
    ui->openGLRenderWindow->paintGL();
}

void Window::on_drawCycloidBtn_clicked()
{
    openGLCycloids *c = new openGLCycloids();
    //glColor3f(0.5f,0.0f,0.0f);
    ui->openGLRenderWindow->push(c);


    ui->openGLRenderWindow->paintGL();
}

void Window::on_polygonClosed_clicked()
{

    ui->polygonFilled->setEnabled(ui->polygonClosed->isChecked());
    ui->polygonFilled->setChecked(false);
    ui->polyGoraud->setEnabled(ui->polygonClosed->isChecked());
    ui->polyGoraud->setChecked(false);

    if(this->buildingPolygon)
    {
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setClosed(ui->polygonClosed->isChecked());
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->unFinish();
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setGoraud(false);

        ui->openGLRenderWindow->paintGL();
    }
}

void Window::on_polygonFill_clicked()
{
    openGLObject* o = ui->openGLRenderWindow->pop();

    if (o->name() == "openGLPolygon")
    {
        ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        ((openGLPolygon*)o)->finish();
        //qDebug()<<"DrawFilled";
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setDebug(true);
        ((openGLPolygon*)o)->drawFilled();
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setDebug(false);
    }
}

void Window::on_polygonPrebuiltFill_clicked()
{

    //If currently building a polygon, finish it.
    if( this->buildingPolygon)
    {
        openGLObject* o;
        this->buildingPolygon = false;

        o = ui->openGLRenderWindow->pop();

        if(ui->polygonClosed->isChecked())
        {
            if(ui->polygonFilled->isChecked())
            {
                ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
                ((openGLPolygon*)o)->finish();
            }
        }
        ui->openGLRenderWindow->paintGL();
    }

    openGLPolygon *p;
    int i;

    GLfloat polygon1[][2] = { {0, 30}, {10, 10}, {50, 10}, {80, 40}, {100, 40}, {110, 50}, {110, 115}, {130, 120}, {130, 130}, {100, 135}, {130, 140}, {130, 150}, {110, 160}, {80, 160}, {70, 150}, {70, 130}, {80, 120}, {70, 110}, {60, 60}, {40, 30}, {30, 20}, {10, 20} };

    GLfloat polygon2[][2] = { {80, 100}, {90, 90}, {100, 90}, {130, 80}, {140, 90}, {160, 90}, {150, 95}, {160, 100}, {150, 100}, {155, 110}, {145, 100}, {140, 110}, {140, 100}, {130, 90}, {110, 110}, {90, 110} };

    GLfloat polygon3[][2] = { {80, 60}, {80, 40}, {90, 30}, {90, 20}, {80, 10}, {80, 5}, {90, 0}, {120, 0}, {100, 10}, {100, 20}, {120, 40}, {110, 60}, {100, 70}, {90, 70} };

    GLfloat polygon4[][2] = { {87.5, 150}, {90, 147}, {96, 147}, {101, 150}, {96, 152.5}, {90, 152.5} };

    GLfloat polygon5[][2] = { {125.0,275.0}, {375.0,275.0}, { 150.0, 150.0}, {250.0, 350.0}, {350.0, 150.0} };

    GLfloat polygon6[][2] = { {9*4,5*4}, {14*4,5*4}, {14*4,11*4}, {22*4,11*4}, {27*4,16*4}, {20*4,25*4}, {13*4,25*4}, {13*4,20*4}, {8*4,20*4}, {8*4,16*4}, {4*4,16*4}, {4*4,9*4} };

    GLfloat polygon7[][2] = { {2,3}, {7,1}, {13,5}, {13,11}, {7,7}, {2,9} };

    GLfloat polygon8[][2] = { {0, 0}, {35, 0}, {35, 40}, {0, 40}, {0, 10},{25, 10}, {25, 30}, {10, 30}, {10, 20}, {15, 20},{15, 25}, {20, 25}, {20, 15}, {5, 15}, {5, 35}, {30, 35}, {30, 5}, {0, 5} };

    GLfloat polygon9[][2] = { {0, 0}, {15, 20}, {30, 0}, {45, 20}, {60, 0}, {75, 20}, {90, 0}, {90, 30}, {70, 30}, {60, 15},{50, 30}, {40, 30}, {30, 15}, {20, 30}, {0, 30}};

    switch(ui->polyPrebuiltCmb->currentIndex())
    {
    case 0:
        p = new openGLPolygon();
        for(i=0; i<22; i++)
            p->add(new openGLPoint(polygon1[i][0],polygon1[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 1:
        p = new openGLPolygon();
        for(i=0; i<16; i++)
            p->add(new openGLPoint(polygon2[i][0],polygon2[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 2:
        p = new openGLPolygon();
        for(i=0; i<14; i++)
            p->add(new openGLPoint(polygon3[i][0],polygon3[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 3:
        p = new openGLPolygon();
        for(i=0; i<6; i++)
            p->add(new openGLPoint(polygon4[i][0],polygon4[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 4:
        p = new openGLPolygon();
        for(i=0; i<5; i++)
            p->add(new openGLPoint(polygon5[i][0],polygon5[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 5:
        p = new openGLPolygon();
        for(i=0; i<12; i++)
            p->add(new openGLPoint(polygon6[i][0],polygon6[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 6:
        p = new openGLPolygon();
        for(i=0; i<6; i++)
            p->add(new openGLPoint(polygon7[i][0],polygon7[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 7:
        p = new openGLPolygon();
        for(i=0; i<18; i++)
            p->add(new openGLPoint(polygon8[i][0],polygon8[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    case 8:
        p = new openGLPolygon();
        for(i=0; i<15; i++)
            p->add(new openGLPoint(polygon9[i][0],polygon9[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        p->finish();
        ui->openGLRenderWindow->push(p);
        break;
    }
    p->setDebug(true);
    ui->openGLRenderWindow->paintGL();
    p->setDebug(false);
}

void Window::on_polyPrebuiltCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->fillRed->setText(QString::number(0.0*255));
        ui->fillGreen->setText(QString::number(0.5*255));
        ui->fillBlue->setText(QString::number(0.0*255));
        break;
    case 1:
        ui->fillRed->setText(QString::number(1.0*255));
        ui->fillGreen->setText(QString::number(1.0*255));
        ui->fillBlue->setText(QString::number(0.0*255));
        break;
    case 2:
        ui->fillRed->setText(QString::number(0.67*255));
        ui->fillGreen->setText(QString::number(0.31*255));
        ui->fillBlue->setText(QString::number(0.0*255));
        break;

    case 3:
        ui->fillRed->setText(QString::number(1.0*255));
        ui->fillGreen->setText(QString::number(0.0*255));
        ui->fillBlue->setText(QString::number(0.0*255));
        break;
    case 4:
        ui->fillRed->setText(QString::number(1.0*255));
        ui->fillGreen->setText(QString::number(1.0*255));
        ui->fillBlue->setText(QString::number(1.0*255));
        break;
    }
}

void Window::on_polygonPrebuildSet_clicked()
{
    //If currently building a polygon, finish it.
    if( this->buildingPolygon)
    {
        openGLObject* o;
        this->buildingPolygon = false;

        o = ui->openGLRenderWindow->pop();

        if(ui->polygonClosed->isChecked())
        {
            if(ui->polygonFilled->isChecked())
            {
                ((openGLPolygon*)o)->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
                ((openGLPolygon*)o)->finish();
            }
        }
        ui->openGLRenderWindow->paintGL();
    }

    GLfloat polygon1[][2] = { {0, 30}, {10, 10}, {50, 10}, {80, 40}, {100, 40}, {110, 50}, {110, 115}, {130, 120}, {130, 130}, {100, 135}, {130, 140}, {130, 150}, {110, 160}, {80, 160}, {70, 150}, {70, 130}, {80, 120}, {70, 110}, {60, 60}, {40, 30}, {30, 20}, {10, 20} };

    GLfloat polygon2[][2] = { {80, 100}, {90, 90}, {100, 90}, {130, 80}, {140, 90}, {160, 90}, {150, 95}, {160, 100}, {150, 100}, {155, 110}, {145, 100}, {140, 110}, {140, 100}, {130, 90}, {110, 110}, {90, 110} };

    GLfloat polygon3[][2] = { {80, 60}, {80, 40}, {90, 30}, {90, 20}, {80, 10}, {80, 5}, {90, 0}, {120, 0}, {100, 10}, {100, 20}, {120, 40}, {110, 60}, {100, 70}, {90, 70} };

    GLfloat polygon4[][2] = { {87.5, 150}, {90, 147}, {96, 147}, {101, 150}, {96, 152.5}, {90, 152.5} };

    GLfloat polygon5[][2] = { {125.0,275.0}, {375.0,275.0}, { 150.0, 150.0}, {250.0, 350.0}, {350.0, 150.0} };

    GLfloat polygon6[][2] = { {9*4,5*4}, {14*4,5*4}, {14*4,11*4}, {22*4,11*4}, {27*4,16*4}, {20*4,25*4}, {13*4,25*4}, {13*4,20*4}, {8*4,20*4}, {8*4,16*4}, {4*4,16*4}, {4*4,9*4} };

    GLfloat polygon7[][2] = { {2,3}, {7,1}, {13,5}, {13,11}, {7,7}, {2,9} };

    GLfloat polygon8[][2] = { {0, 0}, {35, 0}, {35, 40}, {0, 40}, {0, 10},{25, 10}, {25, 30}, {10, 30}, {10, 20}, {15, 20},{15, 25}, {20, 25}, {20, 15}, {5, 15}, {5, 35}, {30, 35}, {30, 5}, {0, 5} };

    GLfloat polygon9[][2] = { {0, 0}, {15, 20}, {30, 0}, {45, 20}, {60, 0}, {75, 20}, {90, 0}, {90, 30}, {70, 30}, {60, 15},{50, 30}, {40, 30}, {30, 15}, {20, 30}, {0, 30}};

    openGLPolygon *p;
    int i;
    switch(ui->polyPrebuiltCmb->currentIndex())
    {
    case 0:
        p = new openGLPolygon();
        for(i=0; i<22; i++)
            p->add(new openGLPoint(polygon1[i][0],polygon1[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 1:
        p = new openGLPolygon();
        for(i=0; i<16; i++)
            p->add(new openGLPoint(polygon2[i][0],polygon2[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 2:
        p = new openGLPolygon();
        for(i=0; i<14; i++)
            p->add(new openGLPoint(polygon3[i][0],polygon3[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 3:
        p = new openGLPolygon();
        for(i=0; i<6; i++)
            p->add(new openGLPoint(polygon4[i][0],polygon4[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 4:
        p = new openGLPolygon();
        for(i=0; i<5; i++)
            p->add(new openGLPoint(polygon5[i][0],polygon5[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 5:
        p = new openGLPolygon();
        for(i=0; i<12; i++)
            p->add(new openGLPoint(polygon6[i][0],polygon6[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 6:
        p = new openGLPolygon();
        for(i=0; i<6; i++)
            p->add(new openGLPoint(polygon7[i][0],polygon7[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 7:
        p = new openGLPolygon();
        for(i=0; i<18; i++)
            p->add(new openGLPoint(polygon8[i][0],polygon8[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    case 8:
        p = new openGLPolygon();
        for(i=0; i<15; i++)
            p->add(new openGLPoint(polygon9[i][0],polygon9[i][1]));
        p->setColor((QColor(ui->fillRed->text().toInt(),ui->fillGreen->text().toInt(),ui->fillBlue->text().toInt())));
        //p->finish();
        //ui->openGLRenderWindow->push(p);
        break;
    }
    p->setDebug(true);
    p->createSet();
    delete p;
}

void Window::on_polygonSet_clicked()
{
    if(ui->openGLRenderWindow->pop()->name() == "openGLPolygon")
    {
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setDebug(true);
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->createSet();
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setDebug(false);
    }
}

void Window::on_polygonFilled_clicked()
{
    ui->polyGoraud->setEnabled(ui->polygonFilled->isChecked());
    ui->polyGoraud->setChecked(false);

    if(this->buildingPolygon)
    {
        if(ui->polygonFilled->isChecked())
            ((openGLPolygon*)ui->openGLRenderWindow->pop())->finish();
        else
            ((openGLPolygon*)ui->openGLRenderWindow->pop())->unFinish();
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setGoraud(false);
        ui->openGLRenderWindow->paintGL();
    }
}

void Window::on_polyGoraud_clicked()
{
    if(this->buildingPolygon)
    {
        ((openGLPolygon*)ui->openGLRenderWindow->pop())->setGoraud(ui->polyGoraud->isChecked());
        ui->openGLRenderWindow->paintGL();
    }
}

void Window::translate(float x, float y, float z)
{
    glTranslatef(x/100, y/100, z/100);
    //glTranslatef((float)ui->cameraXSlider->value()/100, (float)ui->cameraYSlider->value()/100, (float)ui->cameraZSlider->value()/100);
}

void Window::rotate(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glRotatef(x, 1.0f, 0.0f, 0.0f);
    glRotatef(y, 0.0f, 1.0f, 0.0f);
    glRotatef(z, 0.0f, 0.0f, 1.0f);
}

void Window::on_cameraXSlider_valueChanged(int value)
{
    glLoadIdentity();

    updateCamera();

    ui->openGLRenderWindow->paintGL();

    ui->cameraXSliderEdit->setText(QString::number(value));
}

void Window::on_cameraYSlider_valueChanged(int value)
{
    glLoadIdentity();

    updateCamera();

    ui->openGLRenderWindow->paintGL();

    ui->cameraYSliderEdit->setText(QString::number(value));
}

void Window::on_cameraZSlider_valueChanged(int value)
{
    glLoadIdentity();

    updateCamera();

    ui->openGLRenderWindow->paintGL();

    ui->cameraZSliderEdit->setText(QString::number(value));
}

void Window::on_cameraXRotSlider_valueChanged(int value)
{
    glLoadIdentity();

    updateCamera();

    ui->openGLRenderWindow->paintGL();

    ui->cameraXRotSliderEdit->setText(QString::number(value));
}

void Window::on_cameraYRotSlider_valueChanged(int value)
{
    glLoadIdentity();

    updateCamera();

    ui->openGLRenderWindow->paintGL();

    ui->cameraYRotSliderEdit->setText(QString::number(value));
}

void Window::on_cameraZRotSlider_valueChanged(int value)
{
    glLoadIdentity();

    updateCamera();

    ui->openGLRenderWindow->paintGL();

    ui->cameraZRotSliderEdit->setText(QString::number(value));
}

void Window::updateCamera()
{
    this->rotate((float)ui->cameraXRotSlider->value(), (float)ui->cameraYRotSlider->value(), (float)ui->cameraZRotSlider->value());
    this->translate((float)ui->cameraXSlider->value(), (float)ui->cameraYSlider->value(), (float)ui->cameraZSlider->value());
}

void Window::on_rotResetBtn_clicked()
{
    ui->cameraXRotSlider->setValue(45);
    ui->cameraYRotSlider->setValue(30);
    ui->cameraZRotSlider->setValue(0);

    glLoadIdentity();

    this->updateCamera();

    ui->openGLRenderWindow->paintGL();
}

void Window::on_transResetBtn_clicked()
{
    ui->cameraXSlider->setValue(0);
    ui->cameraYSlider->setValue(0);
    ui->cameraZSlider->setValue(0);

    glLoadIdentity();

    this->updateCamera();

    ui->openGLRenderWindow->paintGL();
}

void Window::on_loadObjButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "../battleships/obj", tr("Files (*.obj)"));

    //Only try to load a file if a file was actually selected.
    if (filename != "")
    {
        this->ui->openGLRenderWindow->push(new openGLMesh(filename));

        ui->openGLRenderWindow->paintGL();
    }
}

void Window::on_cameraZoomSlider_valueChanged(int value)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((float)(-value), (float)value, (float)(-value), (float)(value) , (float)(-value), (float)(value));
    //glOrtho((float)(-value), (float)value, (float)(-value), (float)(value), (float)(-value), (float)(value));

    //glOrtho(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f);

    //qDebug()<<value;
    ui->openGLRenderWindow->paintGL();
    //glViewport(0,0,OGLWIDTH*value,OGLHEIGHT*value);

    ui->cameraAspectSlider_1->setValue(value);
    ui->cameraAspectSlider_2->setValue(value);

    ui->cameraZoomSliderEdit->setText(QString::number(value));
}

void Window::on_cameraAspectSlider_1_valueChanged(int value)
{

}

void Window::on_cameraAspectSlider_2_valueChanged(int value)
{

}

void Window::on_cameraXSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraXSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_cameraYSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraYSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_cameraZSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraZSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_cameraXRotSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraXRotSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_cameraYRotSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraYRotSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_cameraZRotSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraZRotSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_LightingBox_clicked(bool checked)
{
    if (checked)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    ui->openGLRenderWindow->paintGL();
}

void Window::on_objectTypeRadioBtn_3_clicked()
{
    //Set the selected model to GL_TRIANGLES
    ui->openGLRenderWindow->paintGL();
}

void Window::on_objectTypeRadioBtn_2_clicked()
{
    //Set the selected model to GL_LINES;
    ui->openGLRenderWindow->paintGL();
}

void Window::on_objectTypeRadioBtn_clicked()
{
    //Set the selected model to GL_POINTS;
    ui->openGLRenderWindow->paintGL();
}

void Window::on_zClippingNearSlider_valueChanged(int value)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho((float)(-ui->cameraAspectSlider_2->value())/10, (float)(ui->cameraAspectSlider_2->value())/10, (float)(-ui->cameraAspectSlider_1->value())/10, (float)(ui->cameraAspectSlider_2->value())/10, (float)ui->zClippingNearSlider->value(), (float)ui->zClippingFarSlider->value());
    glOrtho((float)(-ui->cameraAspectSlider_2->value())/10, (float)(ui->cameraAspectSlider_2->value())/10, (float)(-ui->cameraAspectSlider_1->value())/10, (float)(ui->cameraAspectSlider_2->value())/10, (float)(value)/10, 15.0f);

    ui->openGLRenderWindow->paintGL();
}

void Window::on_zClippingFarSlider_valueChanged(int value)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho((float)(-ui->cameraAspectSlider_2->value())/10, (float)(ui->cameraAspectSlider_2->value())/10, (float)(-ui->cameraAspectSlider_1->value())/10, (float)(ui->cameraAspectSlider_2->value())/10, (float)ui->zClippingNearSlider->value()/10, (float)(value)/10);

    ui->openGLRenderWindow->paintGL();
}

void Window::on_cameraZoomSliderEdit_textEdited(const QString &arg1)
{
    ui->cameraZoomSlider->setValue(arg1.toInt());

    ui->openGLRenderWindow->paintGL();
}

void Window::on_objTransButton_clicked()
{
    /*QTime* t = new QTime();

    t->start();

    if (ui->modelListView->currentIndex().row() >= 0)
    {
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xTrans = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yTrans = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->zTrans = 0.0f;

        while(t->elapsed() < 1000)
        {
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xTrans += (ui->objTransXEdit->text().toFloat())/1000;
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yTrans += (ui->objTransYEdit->text().toFloat())/1000;
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->zTrans += (ui->objTransZEdit->text().toFloat())/1000;

            ui->openGLRenderWindow->paintGL();
        }
    }
    delete t;*/
}

void Window::on_objRotButton_clicked()
{
    /*
    QTime* t = new QTime();

    t->start();

    if (ui->modelListView->currentIndex().row() >= 0)
    {
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xRot = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yRot = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->zRot = 0.0f;

        while (t->elapsed() < 1);
        while(t->elapsed() < 1000)
        {
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xRot += (ui->objRotXEdit->text().toFloat())/1000;
            //ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xRot = (ui->objRotXEdit->text().toFloat())/(3000/t->elapsed());
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yRot += (ui->objRotYEdit->text().toFloat())/1000;
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->zRot += (ui->objRotZEdit->text().toFloat())/1000;

            ui->openGLRenderWindow->paintGL();
        }
    }
    delete t;
    */
}

void Window::on_modelListView_currentRowChanged(int currentRow)
{
    //ui->objRotXEdit->setText(QString::number(ui->openGLRenderWindow->m->at(currentRow)->xRot));
}

void Window::on_objScaleButton_clicked()
{
    /*
    QTime* t = new QTime();

    t->start();

    if (ui->modelListView->currentIndex().row() >= 0)
    {
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale = 1.0f;

        while(t->elapsed() < 1000)
        {
            ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale += (ui->objScaleEdit->text().toFloat())/100000;

            ui->openGLRenderWindow->paintGL();
        }
    }
    delete t;
    */
}

void Window::on_animationPathButton_clicked()
{
    /*
    QTime* t = new QTime();

    t->start();

    if (ui->modelListView->currentIndex().row() >= 0)
    {
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xTrans = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yTrans = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->zTrans = 0.0f;
        ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale  = 1.0f;

        while(t->elapsed() < 4000)
        {
            if(t->elapsed()<1000)
            {
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xTrans += (ui->objTransXEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xRot += (ui->objRotXEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale += (ui->objScaleEdit->text().toFloat())/100000;
            }
            else if(t->elapsed()<2000)
            {
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yTrans += (ui->objTransYEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yRot += (ui->objRotYEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale -= (ui->objScaleEdit->text().toFloat())/100000;
            }
            else if(t->elapsed()<3000)
            {
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xTrans -= (ui->objTransXEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->xRot -= (ui->objRotXEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale += (ui->objScaleEdit->text().toFloat())/100000;
            }
            else
            {
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yTrans -= (ui->objTransYEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->yRot -= (ui->objRotYEdit->text().toFloat())/1000;
                ui->openGLRenderWindow->m->at(ui->modelListView->currentIndex().row())->scale -= (ui->objScaleEdit->text().toFloat())/100000;
            }


            ui->openGLRenderWindow->paintGL();
        }
    }
    delete t;
    */
}

void Window::on_LightingBox_clicked()
{

}
