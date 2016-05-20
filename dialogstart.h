#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
#include <QAbstractButton>

class QPushButton;
namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget *parent = 0);
    ~DialogStart();
    int getSqMeters(){return m_squareMeters;}
    int getAnimals(){return m_animals;}
    int getRainInterval(){return m_intervalForRains;}
    void onStartSimButton();

public slots:
//    void onStartSimButtonPressed();
//    void onStartSimButtonReleased();
//    void on_simButton_clicked();

private slots:


    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_clicked();



private:
    Ui::DialogStart *ui;
    int m_squareMeters;
    int m_animals;
    int m_intervalForRains;

};

#endif // DIALOGSTART_H
