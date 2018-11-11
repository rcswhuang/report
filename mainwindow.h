#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
class SARibbonBar;
class SARibbonCategory;
class SARibbonContextCategory;
class QTextEdit;
//报表窗口
class HReportMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum RibbonTheme{
        NormalTheme  ///< 普通主题
          };
public:
    HReportMainWindow(QWidget* par=nullptr);

public:
    void initSARibbonBar();
private slots:
    void onShowContextCategory(bool on);
    void onWpsStyle(bool on);
private:
    void createCategoryMain(SARibbonCategory* page);
    void createCategoryOther(SARibbonCategory* page);
private slots:
    void onMenuButtonPopupCheckableTest(bool b);
    void onInstantPopupCheckableTest(bool b);
    void onDelayedPopupCheckableTest(bool b);

    void onMenuButtonPopupCheckabletriggered(bool b);
    void onInstantPopupCheckabletriggered(bool b);
    void onDelayedPopupCheckabletriggered(bool b);

    void setRibbonTheme(RibbonTheme theme);
    RibbonTheme ribbonTheme() const;

protected:
    void loadTheme(const QString &themeFile);
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *e);
private:
    SARibbonContextCategory* m_contextCategory;
    SARibbonBar* m_ribbonMenuBar;
    RibbonTheme m_currentRibbonTheme;
};

#endif // MAINWINDOW_H
