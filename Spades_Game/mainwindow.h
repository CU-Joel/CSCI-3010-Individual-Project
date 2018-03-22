#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <QString>
#include "Game.hpp"
#include <QLabel>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void playGame();
    void showScore();
    void getUserSelection();

private slots:
    void showHand(vector<string> &s);
    void printTextBox(string s);
    void on_startButton_clicked();
    void on_bidButton_clicked();
    void handleUserBid();
    void on_turnButton_clicked();
    void opp1Card(string s);
    void opp2Card(string s);
    void TMCard(string s);
    void playerCard(string s);
    void on_play1_clicked();
    void on_play2_clicked();
    void on_play3_clicked();
    void on_play4_clicked();
    void on_play5_clicked();
    void on_play6_clicked();
    void on_play7_clicked();
    void on_play8_clicked();
    void on_play9_clicked();
    void on_play10_clicked();
    void on_play11_clicked();
    void on_play12_clicked();
    void on_play13_clicked();

private:
    Ui::MainWindow *ui;
    Game G;
    int turnCount;
    int trickCount;
    //QLabel * labelArr[13];
};



#endif // MAINWINDOW_H
