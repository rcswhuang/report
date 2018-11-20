﻿#include "hborderset.h"
#include "ui_hborderset.h"
#include <QPainter>
#include <QStandardItem>
#include <QMouseEvent>
#include <QColorDialog>
typedef struct _tagDefaultColor
{
    QString strClrName;
    int     nClrValue;
}DefaultColor;

DefaultColor sysColorList[]=
{
    //name value
    {QStringLiteral("黑色"),Qt::black},
    {QStringLiteral("白色"),Qt::white},
    {QStringLiteral("红色"),Qt::red},
    {QStringLiteral("深红色"),(Qt::darkRed)},
    {QStringLiteral("绿色"),(Qt::green)},
    {QStringLiteral("深绿色"),(Qt::darkGreen)},
    {QStringLiteral("蓝色"),(Qt::blue)},
    {QStringLiteral("深蓝色"),(Qt::darkBlue)},
    {QStringLiteral("青色"),(Qt::cyan)},
    {QStringLiteral("深青色"),(Qt::darkCyan)},
    {QStringLiteral("洋红色"),(Qt::magenta)},
    {QStringLiteral("深洋红色"),(Qt::darkMagenta)},
    {QStringLiteral("黄色"),(Qt::yellow)},
    {QStringLiteral("深黄色"),(Qt::darkYellow)},
    {QStringLiteral("灰色"),(Qt::gray)},
    {QStringLiteral("深灰色"),(Qt::darkGray)},
    {QStringLiteral("浅灰色"),(Qt::lightGray)}
};

HBorderSet::HBorderSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HBorderSet)
{
    ui->setupUi(this);
    m_recentColorList.clear();
    initLineStyleSet();
    initColorSet();
    initBorderSet();
}

HBorderSet::~HBorderSet()
{
    m_recentColorList.clear();
    delete ui;
}

void HBorderSet::initBorderSet()
{
    m_bBorderLeft = false;
    m_bBorderTop = false;
    m_bBorderRight = false;
    m_bBorderBottom = false;
    m_strLineColor = "#000000";
    m_strBorderLeftLineColor = "#000000";//边框左线条颜色
    m_strBorderRightLineColor = "#000000";//边框右线条颜色
    m_strBorderTopLineColor = "#000000";//边框上线条颜色
    m_strBorderBottomLineColor = "#000000";//边框下线条颜色
    ui->borderNoBtn->setDefault(false);
    ui->borderAllBtn->setEnabled(false);
    ui->borderHorBtn->setEnabled(false);
    ui->borderVerBtn->setEnabled(false);
    connect(ui->borderLeftBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderLeftBtn_click()));
    connect(ui->borderRightBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderRightBtn_click()));
    connect(ui->borderTopBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderTopBtn_click()));
    connect(ui->borderBottomBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderBottomBtn_click()));
    connect(ui->borderNoBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderNoBtn_click()));
    connect(ui->borderAllBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderAllBtn_click()));
    connect(ui->borderOutSideBtn,SIGNAL(clicked(bool)),this,SLOT(onBorderOutSideBtn_click()));
}

QPixmap HBorderSet::createPenStyleIcon(Qt::PenStyle penStyle)
{
    QPixmap pixmap(134,16);
    QPainter painter(&pixmap);
    painter.fillRect(QRect(0,0,134,16),Qt::white);
    QPen pen(penStyle);
    pen.setColor(QColor(m_strLineColor));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(5,8,129,8);

    return pixmap;
}

void HBorderSet::initLineStyleSet()
{
    ui->lineSytleWidget->verticalHeader()->hide();
    ui->lineSytleWidget->horizontalHeader()->hide();
    ui->lineSytleWidget->verticalHeader()->setDefaultSectionSize(20);
    ui->lineSytleWidget->horizontalHeader()->setDefaultSectionSize(138);
    ui->lineSytleWidget->setShowGrid(false);
    ui->lineSytleWidget->setColumnCount(1);
    ui->lineSytleWidget->setRowCount(7);
    ui->lineSytleWidget->setStyleSheet("selection-background-color:white;"); //设置选中背景色
    updateLineStyleSet();

}

void HBorderSet::updateLineStyleSet()
{
    ui->lineSytleWidget->clear();
    QLabel *label = new QLabel();
    label->setText(QStringLiteral("无"));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(0,0,label);
    label = new QLabel();
    label->setPixmap(createPenStyleIcon(Qt::SolidLine));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(1,0,label);
    label = new QLabel();
    label->setPixmap(createPenStyleIcon(Qt::DashLine));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(2,0,label);
    label = new QLabel();
    label->setPixmap(createPenStyleIcon(Qt::DotLine));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(3,0,label);
    label = new QLabel();
    label->setPixmap(createPenStyleIcon(Qt::DashDotLine));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(4,0,label);
    label = new QLabel();
    label->setPixmap(createPenStyleIcon(Qt::DashDotDotLine));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(5,0,label);
    label = new QLabel();
    label->setPixmap(createPenStyleIcon(Qt::CustomDashLine));
    label->setAlignment(Qt::AlignCenter);
    ui->lineSytleWidget->setCellWidget(6,0,label);
}

void HBorderSet::initColorSet()
{   
    ui->lineColorComboBox->setStyle(new HNoFocusProxyStyle);
    ui->lineColorComboBox->setStyleSheet("selection-background-color:white;"); //设置选中背景色
    ui->lineColorComboBox->setIconSize( QSize( 100, 20 ) );
    ui->lineColorComboBox->setSizeAdjustPolicy( QComboBox::AdjustToContents );
    updateColorListSet();
    QObject::connect(ui->lineColorComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChanged_click(int)));
    connect(ui->moreColorBtn,SIGNAL(clicked(bool)),this,SLOT(onMoreColorBtn_click()));
}

void HBorderSet::updateColorListSet()
{
    QStandardItemModel *model = (QStandardItemModel *)ui->lineColorComboBox->model();
    if(model == NULL)
    {
        model = new QStandardItemModel();//添加提示tootip

    }
    model->clear();
    for( int i = 0; i < m_recentColorList.count();i++)
    {
        QString strClr = m_recentColorList[i];//strClr就是color的名称 #000000
        QColor clr = QColor(strClr);
        QPixmap pix( QSize( 100, 20 ) );
        pix.fill( clr);
        QStandardItem *item = new QStandardItem(QIcon( pix ), NULL);
        item->setData(QVariant(clr.value()));
        item->setToolTip(clr.name());
        model->appendRow(item);
    }

    for( int i = 0; i < sizeof(sysColorList)/sizeof(DefaultColor);i++ )
    {
        DefaultColor color = sysColorList[i];
        QPixmap pix( QSize( 100, 20 ) );
        pix.fill( QColor( Qt::GlobalColor(color.nClrValue) ) );
        QStandardItem *item = new QStandardItem(QIcon( pix ), NULL);
        item->setData(QVariant(color.nClrValue));
        item->setToolTip(color.strClrName);
        model->appendRow(item);
    }
    ui->lineColorComboBox->setModel(model);

}

void HBorderSet::mousePressEvent(QMouseEvent *event)
{

}

void HBorderSet::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();
    QRect rect = ui->viewFrame->geometry();
    QPoint borderPt = ui->groupBox_5->geometry().topLeft();
    QPoint viewFrameTopLeft = ui->viewFrame->geometry().topLeft()+borderPt ;
    QPoint viewFrameTopRight = viewFrameTopLeft+QPoint(rect.width(),0);
    QPoint viewFrameBottomLeft = viewFrameTopLeft+QPoint(0,rect.height());
    QPoint viewFrameBottomRight = viewFrameTopLeft+QPoint(rect.width(),rect.height());
    QRect borderLeftRect = QRect((viewFrameTopLeft + QPoint(0,10)),(viewFrameBottomLeft + QPoint(10,-10)));//ok
    QRect borderRightRect = QRect((viewFrameTopRight + QPoint(-10,10)),(viewFrameBottomRight + QPoint(0,-10)));//ok
    QRect borderTopRect = QRect((viewFrameTopLeft + QPoint(10,0)),(viewFrameTopRight + QPoint(-10,10)));//ok
    QRect borderBottomRect = QRect((viewFrameBottomLeft + QPoint(10,-10)),(viewFrameBottomRight + QPoint(-10,0)));//ok
    if(borderLeftRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderLeftLineColor && m_bBorderLeft)
        {
            m_strBorderLeftLineColor = m_strLineColor;
        }
        else
        {
            m_bBorderLeft = !m_bBorderLeft;
            m_strBorderLeftLineColor = m_strLineColor;
        }
        ui->borderLeftBtn->setChecked(m_bBorderLeft);
    }
    else if(borderTopRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderTopLineColor && m_bBorderTop)
        {
            m_strBorderTopLineColor = m_strLineColor;
        }
        else
        {
            m_bBorderTop = !m_bBorderTop;
            m_strBorderTopLineColor = m_strLineColor;
        }
        ui->borderTopBtn->setChecked(m_bBorderTop);
    }
    else if(borderRightRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderRightLineColor && m_bBorderRight)
        {
            m_strBorderRightLineColor = m_strLineColor;
        }
        else
        {
            m_bBorderRight = !m_bBorderRight;
            m_strBorderRightLineColor = m_strLineColor;
        }
        ui->borderRightBtn->setChecked(m_bBorderRight);
    }
    else if(borderBottomRect.contains(pt))
    {
        if(m_strLineColor != m_strBorderBottomLineColor && m_bBorderBottom)
        {
            m_strBorderBottomLineColor = m_strLineColor;
        }
        else
        {
            m_bBorderBottom = !m_bBorderBottom;
            m_strBorderBottomLineColor = m_strLineColor;
        }
        ui->borderBottomBtn->setChecked(m_bBorderBottom);
    }
    update();
}

void HBorderSet::moveEvent(QMoveEvent *event)
{

}

void HBorderSet::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = ui->viewFrame->geometry();
    QPoint borderPt = ui->groupBox_5->geometry().topLeft();
    QPoint viewFrameLeft = ui->viewFrame->geometry().topLeft()+borderPt ;
    QPoint viewFrameRight = viewFrameLeft+QPoint(rect.width(),0) ;

    QPoint frameInsideTopLeft = viewFrameLeft + QPoint(10,10);
    QPoint frameInsideTopRight = viewFrameRight + QPoint(-10,10);
    QPoint frameInsideBottomLeft = viewFrameLeft + QPoint(0,rect.height())+QPoint(10,-10);
    QPoint frameInsideBottomRight = viewFrameRight + QPoint(0,rect.height())+QPoint(-10,-10);

    //外框
    painter.setPen(QColor(Qt::black));
    painter.drawRect(QRect(viewFrameLeft,QSize(rect.width(),rect.height())));
    //分隔符
    painter.setPen(QColor(Qt::gray));
    painter.drawLine(frameInsideTopLeft-QPoint(0,5),frameInsideTopLeft);
    painter.drawLine(frameInsideTopLeft-QPoint(5,0),frameInsideTopLeft);
    painter.drawLine(frameInsideTopRight,frameInsideTopRight - QPoint(0,5));
    painter.drawLine(frameInsideTopRight,frameInsideTopRight + QPoint(5,0));
    painter.drawLine(frameInsideBottomLeft+QPoint(0,5),frameInsideBottomLeft);
    painter.drawLine(frameInsideBottomLeft-QPoint(5,0),frameInsideBottomLeft);
    painter.drawLine(frameInsideBottomRight,frameInsideBottomRight + QPoint(0,5));
    painter.drawLine(frameInsideBottomRight,frameInsideBottomRight + QPoint(5,0));

    if(m_bBorderLeft)
    {
        painter.setPen(QColor(m_strBorderLeftLineColor));
        painter.drawLine(frameInsideTopLeft,frameInsideBottomLeft);
    }
    if(m_bBorderRight)
    {
        painter.setPen(QColor(m_strBorderRightLineColor));
        painter.drawLine(frameInsideTopRight,frameInsideBottomRight);
    }
    if(m_bBorderTop)
    {
        painter.setPen(QColor(m_strBorderTopLineColor));
        painter.drawLine(frameInsideTopLeft,frameInsideTopRight);
    }
    if(m_bBorderBottom)
    {
        painter.setPen(QColor(m_strBorderBottomLineColor));
        painter.drawLine(frameInsideBottomLeft,frameInsideBottomRight);
    }
    //painter.drawText();
}

void HBorderSet::currentIndexChanged_click(int index)
{
    if((int)-1 == index)
        return;
    QStandardItemModel *model  = (QStandardItemModel *)ui->lineColorComboBox->model();
    if(model)
    {
        int clrValue = model->item(index,0)->data().toInt();
        m_strLineColor = QColor(Qt::GlobalColor(clrValue)).name();
    }
    updateLineStyleSet();
}

void HBorderSet::onBorderLeftBtn_click()
{
    if(m_strLineColor != m_strBorderLeftLineColor && m_bBorderLeft)
    {
        m_strBorderLeftLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderLeft = !m_bBorderLeft;
        m_strBorderLeftLineColor = m_strLineColor;
    }
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    update();
}

void HBorderSet::onBorderVerBtn_click()
{

}

void HBorderSet::onBorderRightBtn_click()
{

    if(m_strLineColor != m_strBorderRightLineColor && m_bBorderRight)
    {
        m_strBorderRightLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderRight = !m_bBorderRight;
        m_strBorderRightLineColor = m_strLineColor;
    }
    ui->borderRightBtn->setChecked(m_bBorderRight);
    update();
}

void HBorderSet::onBorderTopBtn_click()
{
    if(m_strLineColor != m_strBorderTopLineColor && m_bBorderTop)
    {
        m_strBorderTopLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderTop = !m_bBorderTop;
        m_strBorderTopLineColor = m_strLineColor;
    }
    ui->borderTopBtn->setChecked(m_bBorderTop);
    update();

}

void HBorderSet::onBorderHorBtn_click()
{

}

void HBorderSet::onBorderBottomBtn_click()
{
    if(m_strLineColor != m_strBorderBottomLineColor && m_bBorderBottom)
    {
        m_strBorderBottomLineColor = m_strLineColor;
    }
    else
    {
        m_bBorderBottom = !m_bBorderBottom;
        m_strBorderBottomLineColor = m_strLineColor;
    }
    ui->borderBottomBtn->setChecked(m_bBorderBottom);
    update();

}

void HBorderSet::onBorderNoBtn_click()
{
    m_bBorderLeft = m_bBorderBottom = m_bBorderTop = m_bBorderRight = false;
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    ui->borderBottomBtn->setChecked(m_bBorderBottom);
    ui->borderTopBtn->setChecked(m_bBorderTop);
    ui->borderRightBtn->setChecked(m_bBorderRight);
    update();
}

void HBorderSet::onBorderAllBtn_click()
{

}

void HBorderSet::onBorderOutSideBtn_click()
{
    m_bBorderLeft = m_bBorderBottom = m_bBorderTop = m_bBorderRight = true;
    ui->borderLeftBtn->setChecked(m_bBorderLeft);
    ui->borderBottomBtn->setChecked(m_bBorderBottom);
    ui->borderTopBtn->setChecked(m_bBorderTop);
    ui->borderRightBtn->setChecked(m_bBorderRight);
    m_strBorderLeftLineColor = m_strLineColor;
    m_strBorderRightLineColor = m_strLineColor;
    m_strBorderTopLineColor = m_strLineColor;
    m_strBorderBottomLineColor = m_strLineColor;
    update();
}

void HBorderSet::onMoreColorBtn_click()
{
    QColor clr = QColorDialog::getColor(QColor(m_strLineColor),this,QStringLiteral("选择颜色"));
    while(m_recentColorList.count() > 5)
        m_recentColorList.removeLast();
    if((int)-1 == m_recentColorList.indexOf(clr.name()))
        m_recentColorList.push_front(clr.name());
    updateColorListSet();
    m_strLineColor = clr.name();
    updateLineStyleSet();
    update();
}


