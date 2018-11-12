#include "mainwindow.h"
#include <QTextEdit>
#include <QAbstractButton>
#include "SARibbonBar.h"
#include "SARibbonCategory.h"
#include <QPushButton>
#include "SARibbonPannel.h"
#include "SARibbonToolButton.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include "FramelessHelper.h"
#include "SARibbonMenu.h"
#include "SARibbonComboBox.h"
#include "SARibbonLineEdit.h"
#include "SARibbonGallery.h"
#include "SARibbonCheckBox.h"
#include "SARibbonQuickAccessBar.h"
#include "SARibbonButtonGroupWidget.h"
#define PRINT_COST(ElapsedTimer,LastTime,STR) \
    do{\
    int ___TMP_INT = ElapsedTimer.elapsed();\
    qDebug() << STR << ___TMP_INT - LastTime << "(" << ___TMP_INT << ")";\
    LastTime = ___TMP_INT;\
    }while(0)

HReportMainWindow::HReportMainWindow(QWidget *par):QMainWindow(par),m_currentRibbonTheme(RibbonTheme::NormalTheme)
{
    setWindowTitle(QStringLiteral("报表设计"));

    //这里应该是一个表格控件

    //初始化工具栏
    initSARibbonBar();


    m_ribbonMenuBar->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/chartDataManager.png"),"action1",this));
    m_ribbonMenuBar->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/figureIcon.png"),"action2",this));
    m_ribbonMenuBar->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/information.png"),"action3",this));
    m_ribbonMenuBar->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/inRangDataRemove.png"),"action4",this));

    showMaximized();

}

//
void HReportMainWindow::initSARibbonBar()
{
    setRibbonTheme(ribbonTheme());
    m_ribbonMenuBar = new SARibbonBar(this);
    setMenuWidget(m_ribbonMenuBar);
    m_ribbonMenuBar->installEventFilter(this);
    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->setTitleHeight(m_ribbonMenuBar->titleBarHeight());  //设置窗体的标题栏高度
    QFont f = m_ribbonMenuBar->font();
    f.setFamily("微软雅黑");
    m_ribbonMenuBar->setFont(f);
    m_ribbonMenuBar->applitionButton()->setText(QStringLiteral("文件"));//menu
    SARibbonCategory* categoryMain = m_ribbonMenuBar->addCategoryPage(QStringLiteral("开始"));
    createCategoryMain(categoryMain);
    SARibbonCategory* categoryPrint = m_ribbonMenuBar->addCategoryPage(QStringLiteral("打印"));
    createCategoryPrint(categoryPrint);
    SARibbonCategory* categoryOther = m_ribbonMenuBar->addCategoryPage(QStringLiteral("测试"));
    createCategoryOther(categoryOther);
    //m_contextCategory = m_ribbonMenuBar->addContextCategory(QStringLiteral("context"),Qt::red,1);
    //SARibbonCategory* contextCategoryPage1 = m_contextCategory->addCategoryPage(QStringLiteral("Page1"));
    //SARibbonCategory* contextCategoryPage2 = m_contextCategory->addCategoryPage(QStringLiteral("Page1"));
}


void HReportMainWindow::onShowContextCategory(bool on)
{
    m_ribbonMenuBar->setContextCategoryVisible(m_contextCategory,on);
}

void HReportMainWindow::onWpsStyle(bool on)
{
    if(on)
        m_ribbonMenuBar->setRibbonStyle(SARibbonBar::WpsLiteStyle);
    else
        m_ribbonMenuBar->setRibbonStyle(SARibbonBar::OfficeStyle);
    update();
}

void HReportMainWindow::createCategoryMain(SARibbonCategory *page)
{
    SARibbonToolButton * btn = NULL;
    /*
    SARibbonMenu* menu = new SARibbonMenu(this);
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("11"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("11111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("11111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111111111111111111111111"));*/

    ///////////////////////////////////////////剪贴板//////////////////////////////////////////
    SARibbonPannel* pannel = page->addPannel(QStringLiteral("剪贴板"));

    //剪切板
    QAction* pasteAct;
    QAction* cutAct;
    QAction* copyAct;
    QAction* formatPainterAct;

    //字体设置
    QAction* boldAct;
    QAction* italicAct;
    QAction* underlineAct;

    //字体颜色
    QAction* fontColorAct;
    QAction* fontBkColorAct;

    //边框设置
    QAction* borderBottomAct;
    QAction* borderTopAct;
    QAction* borderLeftAct;
    QAction* borderRightAct;
    QAction* borderNoneAct;
    QAction* borderAllAct;
    QAction* borderOutSideAct;
    QAction* borderInsideAct;
    QAction* borderInsideHorAct;
    QAction* borderInsideVerAct;

    //字体大小设置
    QAction* fontSizeIncreaseAct;
    QAction* fontSizeDecreaseAct;

    //字体格式
    QAction* clearCellAll;//清除所有
    QAction* clearFormatsAct; //清楚格式
    QAction* clearFormatingAct;//清除内容

    //字体对齐
    QAction* alignTopAct;
    QAction* alignMiddleAct;
    QAction* alignBottomAct;
    QAction* alignLeftAct;
    QAction* alignCenterAct;
    QAction* alignRightAct;

    //自动换行
    QAction* autoWrapTextAct;//自动换行

    //合并单元格
    QAction* mergeCenterAct;
    QAction* mergeCellsAct;
    QAction* mergeSplitAct;

    //单元格插入
    QAction* cellInsertAct;
    QAction* cellInsertRowAct;
    QAction* cellRemoveActAct;

    //单元格删除
    QAction* cellDeleteActAct;
    QAction* cellInsertColAct;
    QAction* cellRomoveColAct;

    //单元格格式
    QAction* cellRowHeightAct;
    QAction* cellAutoRowHeightAct;
    QAction* cellColWidthAct;
    QAction* cellAutoColWidthAct;
    QAction* cellDefaultColWidthAct;

    QAction* act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/Paste.png"));
    act->setText(QStringLiteral("粘贴"));
    pannel->addLargeAction(act);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/Cut.png"));
    act->setText(QStringLiteral("剪切"));
    pannel->addSmallAction(act);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/Copy.png"));
    act->setText(QStringLiteral("拷贝"));
    pannel->addSmallAction(act);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/FormatPainter.png"));
    act->setText(QStringLiteral("格式刷"));
    act->setCheckable(true);
    act->setChecked(false);
    btn = pannel->addSmallAction(act);


    ////////////////////////////////////////////字体设置///////////////////////////////////////////
    //字体格式设置
    SARibbonPannel* fontPannel = page->addPannel(QStringLiteral("字体"));
    SARibbonComboBox* com = new SARibbonComboBox(this);//设置字体
    com->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    com->setEditable(true);
    fontPannel->addWidget(com,0,3);

    SARibbonButtonGroupWidget* btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/Bold.png"),"",this));
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/Italic.png"),"",this));
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/Underline.png"),"",this));

    //字体背景颜色
    SARibbonMenu* clrmenu = new SARibbonMenu(this);
    QAction* item1 = clrmenu->addAction(QIcon(":/icon/icon/fontbkcolor.png"),QStringLiteral("color"));
    clrmenu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1"));
    clrmenu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("11"));
    btn = btnGroup->addButton(item1);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setMenu(clrmenu);
    btn->setFixedWidth(32);
    btnGroup->addWidget(btn);

    //字体颜色
    SARibbonMenu* clrmenu2 = new SARibbonMenu(this);
    item1 = clrmenu2->addAction(QIcon(":/icon/icon/fontcolor.png"),QStringLiteral("color"));
    btn = btnGroup->addButton(item1);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setMenu(clrmenu);
    btn->setFixedWidth(32);
    btnGroup->addWidget(btn);
    fontPannel->addWidget(btnGroup,3,3);
    fontPannel->addSeparator();

    //字体大小格式
    com = new SARibbonComboBox(this);
    com->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    com->setEditable(true);
    fontPannel->addWidget(com,0,3);
    btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    //btn->setFixedWidth(35);
    SARibbonMenu* bordermenu = new SARibbonMenu(this);
    QAction * item = bordermenu->addAction(QIcon(":/icon/icon/BorderBottom.png"),QStringLiteral("下框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderTop.png"),QStringLiteral("上框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderLeft.png"),QStringLiteral("左框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderRight.png"),QStringLiteral("右框线"));
    bordermenu->addSeparator();

    bordermenu->addAction(QIcon(":/icon/icon/BorderNone.png"),QStringLiteral("无框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderAll.png"),QStringLiteral("所有框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderOutside.png"),QStringLiteral("外侧框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderInside.png"),QStringLiteral("内部框线"));
    bordermenu->addSeparator();
    bordermenu->addAction(QIcon(":/icon/icon/BorderInsideHorizontal.png"),QStringLiteral("内部竖框线"));
    bordermenu->addAction(QIcon(":/icon/icon/BorderInsideVertical.png"),QStringLiteral("内部横框线"));
    //如果单纯QAction就不需要下面操作，如果QAction变成菜单样式就需要借助SARibbonToolButton控件
    btn = btnGroup->addButton(item);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setMenu(bordermenu);
    btn->setFixedWidth(32);
    btn = btnGroup->addButton(new QAction(QIcon(":/icon/icon/Clear.png"),"",this));
    fontPannel->addWidget(btnGroup,3,3);

    //调整字体设置
    btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btnGroup->setFrameShape(QFrame::NoFrame);
    btn = btnGroup->addButton(new QAction(QIcon(":/icon/icon/FontSizeIncrease.png"),"",this));
    btn = btnGroup->addButton(new QAction(QIcon(":/icon/icon/FontSizeDecrease.png"),"",this));
    fontPannel->addWidget(btnGroup,0,3);
    btnGroup = new SARibbonButtonGroupWidget(fontPannel);
    btn = btnGroup->addButton(new QAction(QIcon(":/icon/icon/ClearFormats.png"),"",this));
    btn = btnGroup->addButton(new QAction(QIcon(":/icon/icon/ClearFormatting.png"),"",this));
    fontPannel->addWidget(btnGroup,3,3);


    ////////////////////////////////////////////对齐设置/////////////////////////////////////////////////
    SARibbonPannel* alignAndborderPannel = page->addPannel(QStringLiteral("对齐"));
    btnGroup = new SARibbonButtonGroupWidget(alignAndborderPannel);
    SARibbonButtonGroupWidget* btnGroup1 = new SARibbonButtonGroupWidget(alignAndborderPannel);
    btnGroup1->setFrameShape(QFrame::NoFrame);
    btnGroup1->addButton(new QAction(QIcon(":/icon/icon/AlignTop.png"),"",this));
    btnGroup1->addButton(new QAction(QIcon(":/icon/icon/AlignMiddle.png"),"",this));
    btnGroup1->addButton(new QAction(QIcon(":/icon/icon/AlignBottom.png"),"",this));
    alignAndborderPannel->addWidget(btnGroup1,0,3);
    btnGroup->setFrameShape(QFrame::NoFrame);
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/AlignLeft.png"),"",this));
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/AlignCenter.png"),"",this));
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/AlignRight.png"),"",this));
    alignAndborderPannel->addWidget(btnGroup,2,3);
    alignAndborderPannel->addSeparator();

    //设置自动换行
    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/WrapText.png"));
    act->setText(QStringLiteral("自动换行"));
    btn = alignAndborderPannel->addSmallAction(act);
    alignAndborderPannel->addWidget(btn,0,3);
    //合并单元格
    SARibbonMenu* mergemenu = new SARibbonMenu(this);
    QAction * mergeItem = mergemenu->addAction(QIcon(":/icon/icon/MergeCenter.png"),QStringLiteral("合并后居中"));
    mergemenu->addAction(QIcon(":/icon/icon/MergeCells.png"),QStringLiteral("合并单元格"));
    mergemenu->addAction(QIcon(":/icon/icon/MergeOrSplitCells.png"),QStringLiteral("取消合并单元格"));
    btn = alignAndborderPannel->addSmallAction(mergeItem);
    btn->setIcon(QIcon(":/icon/icon/MergeCenter.png"));
    btn->setText(QStringLiteral("合并后居中"));
    btn->setPopupMode(QToolButton::InstantPopup);
    //btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn->setMenu(mergemenu);
    alignAndborderPannel->addWidget(btn,2,3);

    //////////////////////////////////////////////////////单元格///////////////////////////////////////////
    SARibbonPannel* cellPannel = page->addPannel(QStringLiteral("单元格"));
    //插入单元格
    SARibbonMenu* cellmenu = new SARibbonMenu(this);
    QAction * cellItem = cellmenu->addAction(QIcon(":/icon/icon/sCellsInsertDialog.png"),QStringLiteral("插入单元格"));
    cellmenu->addSeparator();
    cellmenu->addAction(QIcon(":/icon/icon/InsertRow.png"),QStringLiteral("插入工作表行"));
    cellmenu->addAction(QIcon(":/icon/icon/RemoveRow.png"),QStringLiteral("删除工作表行"));
    btn = cellPannel->addLargeAction(cellItem);
    btn->setIcon(QIcon(":/icon/icon/CellsInsertDialog.png"));
    btn->setText(QStringLiteral("插入"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(cellmenu);
    cellPannel->addWidget(btn);
    //删除单元格
    cellmenu = new SARibbonMenu(this);
    cellItem = cellmenu->addAction(QIcon(":/icon/icon/sCellsDelete.png"),QStringLiteral("删除单元格"));
    cellmenu->addSeparator();
    cellmenu->addAction(QIcon(":/icon/icon/InsertColumn.png"),QStringLiteral("插入工作表行"));
    cellmenu->addAction(QIcon(":/icon/icon/RemoveColumn.png"),QStringLiteral("删除工作表行"));
    btn = cellPannel->addLargeAction(cellItem);
    btn->setIcon(QIcon(":/icon/icon/CellsDelete.png"));
    btn->setText(QStringLiteral("删除"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(cellmenu);
    cellPannel->addWidget(btn);

    //格式化单元格
    cellmenu = new SARibbonMenu(this);
    cellItem = cellmenu->addAction(QIcon(":/icon/icon/RowHeight.png"),QStringLiteral("行高"));
    cellmenu->addAction(QStringLiteral("自动调整行高"));
    cellmenu->addSeparator();
    cellmenu->addAction(QIcon(":/icon/icon/ColumnWidth.png"),QStringLiteral("列宽"));
    cellmenu->addAction(QStringLiteral("自动调整列宽"));
    cellmenu->addAction(QStringLiteral("默认列宽"));
    cellmenu->addSeparator();
    cellmenu->addAction(QIcon(":/icon/icon/CellsFormat.png"),QStringLiteral("设置单元格格式"));
    btn = cellPannel->addLargeAction(cellItem);
    btn->setIcon(QIcon(":/icon/icon/CellStylesGallery.png"));
    btn->setText(QStringLiteral("格式"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(cellmenu);
    cellPannel->addWidget(btn);
    return;
    //btn->setPopupMode(QToolButton::MenuButtonPopup);

    //act = new QAction(this);
    //act->setIcon(QIcon(":/icon/icon/Bold.png"));
    //act->setText(QStringLiteral("test 3"));
    //act->setMenu(menu);
    //btn = fontPannel->addSmallAction(act);
    //btn->setPopupMode(QToolButton::MenuButtonPopup);

    //act = new QAction(this);
    //act->setIcon(QIcon(":/icon/icon/Italic.png"));
    //act->setText(QStringLiteral("test 4"));
    //act->setMenu(menu);
    //btn = fontPannel->addSmallAction(act);
    //btn->setPopupMode(QToolButton::InstantPopup);

    //act = new QAction(this);
    //act->setIcon(QIcon(":/icon/icon/Underline.png"));
    //act->setText(QStringLiteral("test 4"));
    //act->setMenu(menu);
    //btn = fontPannel->addSmallAction(act);
    //btn->setPopupMode(QToolButton::InstantPopup);



    return;
    /*
    pannel->addSeparator();

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("DelayedPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::DelayedPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onDelayedPopupCheckabletriggered);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("MenuButtonPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onMenuButtonPopupCheckabletriggered);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("InstantPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::InstantPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onInstantPopupCheckabletriggered);

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("DelayedPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::DelayedPopup);
    btn->setCheckable(true);
    connect(act,&QAction::triggered,this,&MainWindow::onDelayedPopupCheckableTest);

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/folder.png"));
    act->setText(QStringLiteral("MenuButtonPopup\n checkable"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    btn->setCheckable(true);
    connect(act,&QAction::triggered,this,&MainWindow::onMenuButtonPopupCheckableTest);

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("InstantPopup"));
    act->setMenu(menu);
    btn = pannel->addLargeAction(act);
    btn->setCheckable(true);
    btn->setPopupMode(QToolButton::InstantPopup);
    connect(act,&QAction::triggered,this,&MainWindow::onInstantPopupCheckableTest);

    SARibbonPannel* panne2 = page->addPannel(QStringLiteral("pannel 2"));
    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("show\nContext"));
    btn = panne2->addLargeAction(act);
    btn->setCheckable(true);
    //btn->setPopupMode(QToolButton::InstantPopup);
    connect(act,&QAction::triggered,this,[this](bool on){
        if(on)
            m_ribbonMenuBar->showContextCategory(this->m_contextCategory);
        else
            m_ribbonMenuBar->hideContextCategory(this->m_contextCategory);
    });

    act = new QAction(this);
    act->setCheckable(true);
    act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
    act->setText(QStringLiteral("unactive"));
    act->setMenu(menu);
    btn = panne2->addLargeAction(act);
    btn->setCheckable(true);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setEnabled(false);




    com = new SARibbonComboBox(this);
    com->setSizePolicy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    com->setWindowIcon(QIcon(":/icon/icon/folder.png"));
    com->setWindowTitle("ComboBox Editable");
    for (int i=0;i<40;++i)
        com->addItem("111111111111");
    pannel->addWidget(com);

    SARibbonLineEdit* lineEdit = new SARibbonLineEdit(this);
    lineEdit->setSizePolicy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    lineEdit->setWindowIcon(QIcon(":/icon/icon/folder.png"));
    lineEdit->setWindowTitle("Line Edit");
    lineEdit->setText("SARibbonLineEdit");
    pannel->addWidget(lineEdit);
QWidget* w = lineEdit->parentWidget();
while(w)
{
    qDebug() << w->metaObject()->className();
    w = w->parentWidget();
}
    SARibbonCheckBox* checkBox = new SARibbonCheckBox(this);
    checkBox->setSizePolicy(QSizePolicy::Expanding,
                       QSizePolicy::Fixed);
    checkBox->setWindowIcon(QIcon(":/icon/icon/folder.png"));
    checkBox->setText("checkBox");
    pannel->addWidget(checkBox);*/

    //pannel->setExpanding();
    QAction* optAct = new QAction(this);
    pannel->addOptionAction(optAct);
}

void HReportMainWindow::createCategoryOther(SARibbonCategory *page)
{
    SARibbonMenu* menu = new SARibbonMenu(this);
    QAction * item = menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("22221111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));
    menu->addAction(QIcon(":/icon/icon/folder.png"),QStringLiteral("1111111"));

    SARibbonPannel* pannel = page->addPannel(QStringLiteral("pannel 1"));
    SARibbonButtonGroupWidget* btnGroup = new SARibbonButtonGroupWidget(pannel);
    btnGroup->setFrameShape(QFrame::Box);
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/figureIcon.png"),"",this));
    btnGroup->addButton(new QAction(QIcon(":/icon/icon/information.png"),"",this));
    pannel->addWidget(btnGroup,0,3);

    SARibbonToolButton* btn;
    btn = pannel->addLargeAction(item);
    btn->setIcon(QIcon(":/icon/icon/folder.png"));
    btn->setText(QStringLiteral("un format\nicon"));
    btn->setPopupMode(QToolButton::DelayedPopup);
    btn->setFixedHeight(78);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(menu);
    pannel->addWidget(btn);

    btn = pannel->addLargeAction(item);
    btn->setIcon(QIcon(":/icon/icon/folder.png"));
    btn->setText(QStringLiteral("change page\ntest"));
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    btn->setFixedHeight(78);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(menu);
    pannel->addWidget(btn);

    btn = pannel->addLargeAction(item);
    btn->setIcon(QIcon(":/icon/icon/folder.png"));
    btn->setText(QStringLiteral("LargeBtn"));
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setFixedHeight(78);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setMenu(menu);
    pannel->addWidget(btn);

    SARibbonGallery* gallery = pannel->addGallery();
    SARibbonGalleryGroup*group = gallery->addGalleryGroup();
    for(int i=0;i<100;++i)
    {
        group->addItem(QIcon(":/icon/icon/folder.png"));
    }
    QAction* optAct = new QAction(this);
    pannel->addOptionAction(optAct);
    pannel->setObjectName("debug");

}

void HReportMainWindow::createCategoryPrint(SARibbonCategory* page)
{
    SARibbonPannel* printpannel = page->addPannel(QStringLiteral("打印设置"));

    QAction* act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/PrintDialogAccess.png"));
    act->setText(QStringLiteral("快速打印"));
    printpannel->addLargeAction(act);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/PrintOptionsMenuWord.png"));
    act->setText(QStringLiteral("打印选项"));
    printpannel->addLargeAction(act);

    act = new QAction(this);
    act->setIcon(QIcon(":/icon/icon/PrintPreviewZoomMenu.png"));
    act->setText(QStringLiteral("打印预览"));
    printpannel->addLargeAction(act);

}

void HReportMainWindow::onMenuButtonPopupCheckableTest(bool b)
{
    //m_edit->append(QStringLiteral("MenuButtonPopupCheckableTest : %1").arg(b));
}

void HReportMainWindow::onInstantPopupCheckableTest(bool b)
{
   // m_edit->append(QStringLiteral("InstantPopupCheckableTest : %1").arg(b));
}

void HReportMainWindow::onDelayedPopupCheckableTest(bool b)
{
    //m_edit->append(QStringLiteral("DelayedPopupCheckableTest : %1").arg(b));
}

void HReportMainWindow::onMenuButtonPopupCheckabletriggered(bool b)
{
    //m_edit->append(QStringLiteral("MenuButtonPopupCheckabletriggered : %1").arg(b));
}

void HReportMainWindow::onInstantPopupCheckabletriggered(bool b)
{
    //m_edit->append(QStringLiteral("InstantPopupCheckabletriggered : %1").arg(b));
}

void HReportMainWindow::onDelayedPopupCheckabletriggered(bool b)
{
    //m_edit->append(QStringLiteral("DelayedPopupCheckabletriggered : %1").arg(b));
}


/*
SARibbonBar *MainWindow::ribbonBar()
{
    return m_ribbonMenuBar;
}*/

void HReportMainWindow::setRibbonTheme(RibbonTheme theme)
{
    switch(theme)
    {
    case NormalTheme:
        loadTheme("resource/default.qss");
        break;
    default:
        loadTheme(":/theme/resource/default.qss");
        break;
    }
}

HReportMainWindow::RibbonTheme HReportMainWindow::ribbonTheme() const
{
    return m_currentRibbonTheme;
}

void HReportMainWindow::resizeEvent(QResizeEvent *event)
{
    if(m_ribbonMenuBar)
    {
        if(m_ribbonMenuBar->size().width() != this->size().width())
        {
            m_ribbonMenuBar->setFixedWidth(this->size().width());
        }
    }
    QMainWindow::resizeEvent(event);
}

bool HReportMainWindow::eventFilter(QObject *obj, QEvent *e)
{//
    /*if(obj == m_d->ribbonBar)
    {
        switch (e->type())
        {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        case QEvent::Leave:
        case QEvent::HoverMove:
        case QEvent::MouseButtonDblClick:
            QApplication::sendEvent(this,e);
        default:
            break;
        }
    }*/
    return QMainWindow::eventFilter(obj,e);
}


void HReportMainWindow::loadTheme(const QString& themeFile)
{
    QFile file(themeFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
     return;
    }
    QString str = file.readAll();
    setStyleSheet(str);
    file.close();
}

