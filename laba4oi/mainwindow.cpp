#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "methods.cpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QFileDialog>
#include <QDesktopServices>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_open()
{
    QFileDialog dialog;
    dialog.showNormal();
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    QList<QUrl> urls;
    urls << QUrl::fromLocalFile("/home/");
    dialog.setSidebarUrls(urls);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    QString fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles()[0];
    std::string name = fileNames.toStdString();
    cv::Mat image = cv::imread(name, CV_LOAD_IMAGE_COLOR);
    cv::imwrite("main.jpg", image);

    auto imageObject = new QImage();
    imageObject->load("main.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView->setScene(scene);
}

void MainWindow::_about()
{

}

void MainWindow::_sobel()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Sobel(image);

    cv::imwrite("out_sobel.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_sobel.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_razm()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    cv::imwrite("out_razm.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_razm.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_wide()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    cv::imwrite("out_wide.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_wide.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_tight()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    cv::imwrite("out_tight.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_tight.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_gauss()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gauss(out);

    cv::imwrite("out_gauss.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_gauss.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_rezk()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    cv::imwrite("out_rezk.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_rezk.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_boarders()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    cv::imwrite("out_borders.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_borders.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_otsu()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    out = Otsus_method(image, out);
    cv::imwrite("out_otsu.jpg", out);
    auto imageObject = new QImage();
    imageObject->load("out_otsu.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_median()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);
    cv::imwrite("out_median.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_median.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);
    scene->setSceneRect(im.rect());
    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_gray()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

//    cv::cvtColor(image, out, CV_BGR2GRAY);
    out = Gray_sc(image);
    cv::imwrite("out_gray.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_gray.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_inv()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);

    cv::imwrite("out_inv.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("out_inv.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_sepia()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);
    cv::imwrite("sepia.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("sepia.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_contrast()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);
    cv::imwrite("_contrast.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("_contrast.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_bw()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);
    cv::imwrite("_bw.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("_bw.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_tisnenie()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);
    cv::imwrite("_tisnenie.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("_tisnenie.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_gray_world()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);
    cv::imwrite("_gray_world.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("_gray_world.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_linear_contrast()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::Mat out(image);

    out = Linear_contrast(image);

    cv::imwrite("_linear_contrast.jpg", out);
    auto imageObject = new QImage();
    imageObject->load("_linear_contrast.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::_correction()
{
    cv::Mat image = cv::imread("main.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat out(image);

    out = Gray_sc(image);
    cv::imwrite("_correction.jpg", out);

    auto imageObject = new QImage();
    imageObject->load("_correction.jpg");
    auto im = QPixmap::fromImage(*imageObject);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(im);

    ui->graphicsView_2->setScene(scene);
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&Файл"), this);
    fileMenu_1 = new QMenu(tr("&Фильтры"), this);
    fileMenu->addAction(open);
    fileMenu_1->addAction(sobel);
    fileMenu_1->addAction(razm);
    fileMenu_1->addAction(wide);
    fileMenu_1->addAction(gauss);
    fileMenu_1->addAction(gray);
    fileMenu_1->addAction(tight);
    fileMenu_1->addAction(otsu);
//    fileMenu_1->addAction(boarders);
    fileMenu_1->addAction(median);

    fileMenu_1->addAction(bw);
    fileMenu_1->addAction(gray_world);
    fileMenu_1->addAction(tisnenie);
    fileMenu_1->addAction(linear_contrast);
    fileMenu_1->addAction(sepia);
    fileMenu_1->addAction(contrast);
    fileMenu_1->addAction(inv);
    fileMenu_1->addAction(correction);

    fileMenu->addAction(about);
    ui->menuBar->addMenu(fileMenu);
    ui->menuBar->addMenu(fileMenu_1);
}

void MainWindow::createActions()
{
    about = new QAction(tr("&Справка"), this);
    about->setStatusTip(tr(""));
    connect(about, &QAction::triggered, this, &MainWindow::_about);

    open = new QAction(tr("&Открыть"), this);
    open->setStatusTip(tr(""));
    connect(open, &QAction::triggered, this, &MainWindow::_open);

    sobel = new QAction(tr("&Собель"), this);
    sobel->setStatusTip(tr(""));
    connect(sobel, &QAction::triggered, this, &MainWindow::_sobel);

    razm = new QAction(tr("&Размытие"), this);
    razm->setStatusTip(tr(""));
    connect(razm, &QAction::triggered, this, &MainWindow::_razm);

    gray = new QAction(tr("&Оттенки серого"), this);
    gray->setStatusTip(tr(""));
    connect(gray, &QAction::triggered, this, &MainWindow::_gray);

    wide = new QAction(tr("&Расширение"), this);
    wide->setStatusTip(tr(""));
    connect(wide, &QAction::triggered, this, &MainWindow::_wide);

    gauss = new QAction(tr("&Гаусс"), this);
    gauss->setStatusTip(tr(""));
    connect(gauss, &QAction::triggered, this, &MainWindow::_gauss);

    tight = new QAction(tr("&Сужение"), this);
    tight->setStatusTip(tr(""));
    connect(tight, &QAction::triggered, this, &MainWindow::_tight);

    otsu = new QAction(tr("&Метод Оцу"), this);
    otsu->setStatusTip(tr(""));
    connect(otsu, &QAction::triggered, this, &MainWindow::_otsu);

//    boarders = new QAction(tr("&Выделение границ"), this);
//    boarders->setStatusTip(tr(""));
//    connect(boarders, &QAction::triggered, this, &MainWindow::_boarders);

    median = new QAction(tr("&Медианный фильтр"), this);
    median->setStatusTip(tr(""));
    connect(median, &QAction::triggered, this, &MainWindow::_median);

    tisnenie = new QAction(tr("&Тиснение"), this);
    tisnenie->setStatusTip(tr(""));
    connect(tisnenie, &QAction::triggered, this, &MainWindow::_tisnenie);

    correction = new QAction(tr("&Коррекция с опорным цветом"), this);
    correction->setStatusTip(tr(""));
    connect(correction, &QAction::triggered, this, &MainWindow::_correction);

    inv = new QAction(tr("&Инверсия"), this);
    inv->setStatusTip(tr(""));
    connect(inv, &QAction::triggered, this, &MainWindow::_inv);

    contrast = new QAction(tr("&Контраст"), this);
    contrast->setStatusTip(tr(""));
    connect(contrast, &QAction::triggered, this, &MainWindow::_contrast);

    sepia = new QAction(tr("&Сепия"), this);
    sepia->setStatusTip(tr(""));
    connect(sepia, &QAction::triggered, this, &MainWindow::_sepia);

    linear_contrast = new QAction(tr("&Растяжение контрастности"), this);
    linear_contrast->setStatusTip(tr(""));
    connect(linear_contrast, &QAction::triggered, this, &MainWindow::_linear_contrast);

    bw = new QAction(tr("&Черно-белый"), this);
    bw->setStatusTip(tr(""));
    connect(bw, &QAction::triggered, this, &MainWindow::_bw);

    gray_world = new QAction(tr("&Серый мир"), this);
    gray_world->setStatusTip(tr(""));
    connect(gray_world, &QAction::triggered, this, &MainWindow::_gray_world);
}

void MainWindow::_save()
{

}
