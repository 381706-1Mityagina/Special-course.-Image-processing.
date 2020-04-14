#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
     void _open();
     void _inv();
     void _sepia();
     void _contrast();
     void _bw();
     void _tisnenie();
     void _gray_world();
     void _linear_contrast();
     void _save();
     void _correction();
     void _gray();
     void _about();
     void _sobel();
     void _otsu();
     void _razm();
     void _wide();
     void _tight();
     void _gauss();
     void _rezk();
     void _boarders();
     void _median();

private:
    Ui::MainWindow *ui;
    QString currentFile;
    QMenu *fileMenu;
    QMenu *fileMenu_1;
    QAction *open;
    QAction *sobel;
    QAction *otsu;
    QAction *gray;
    QAction *razm;
    QAction *wide;
    QAction *tight;
    QAction *gauss;
    QAction *rezk;
    QAction *boarders;
    QAction *median;
    QAction *about;

    QAction *bw;
    QAction *gray_world;
    QAction *tisnenie;
    QAction *linear_contrast;
    QAction *sepia;
    QAction *contrast;
    QAction *inv;
    QAction *correction;

    void createMenus();
    void createActions();
};

#endif // MAINWINDOW_H
