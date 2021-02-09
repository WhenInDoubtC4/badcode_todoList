#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::window)
{
    ui->setupUi(this);

    addNewTask = [=](QString task) { window::executeMessageBox(&(*(new QMessageBox(QMessageBox::Critical, "TodoList MX 3000 Pro Plus", task)) << window::connectButton(new QPushButton("Mark done"), [=](){ markDone(task); }))); };
    markDone = [=](QString task) { window::executeMessageBox(&(*(new QMessageBox(QMessageBox::Information, "TodoList MX 3000 Pro Plus", task)) << window::connectButton(new QPushButton("Mark undone"), [=](){ addNewTask(task); }) << new QPushButton("Close"))); };
    connect(ui->pushButton, &QPushButton::clicked, [=] { addNewTask(ui->lineEdit->text()); });
}

window::~window()
{
    delete ui;
}
