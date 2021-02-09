#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QAbstractButton>
#include <QApplication>
#include <QScreen>
#include <QRandomGenerator>

#define SCREEN_POS_SAFE_MARGIN 300

QT_BEGIN_NAMESPACE
namespace Ui { class window; }
QT_END_NAMESPACE

class window : public QMainWindow
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();

private:
    Ui::window *ui;

    std::function<void(QString)> addNewTask, markDone;

    inline static auto getRandomPosOnScreen = []() -> QPoint{ QRandomGenerator gen; return QPoint(gen.global()->bounded(0, QApplication::primaryScreen()->size().width() - SCREEN_POS_SAFE_MARGIN), gen.global()->bounded(0, QApplication::primaryScreen()->size().height() - SCREEN_POS_SAFE_MARGIN)); };

    inline static auto executeMessageBox = [](QMessageBox* messageBox) -> QMessageBox* {messageBox->setWindowModality(Qt::NonModal); messageBox->move(getRandomPosOnScreen()); messageBox->show(); return messageBox;};

    inline static auto connectButton = [](QAbstractButton* button, std::function<void()> lambda) -> QAbstractButton* { connect(button, &QAbstractButton::clicked, lambda); return button; };
};

inline QMessageBox& operator<< (QMessageBox& messageBox, QAbstractButton* button) { messageBox.addButton(button, QMessageBox::ActionRole); return messageBox; }
