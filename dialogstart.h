#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
#include <QAbstractButton>

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

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogStart *ui;
    int m_squareMeters;
    int m_animals;
};

#endif // DIALOGSTART_H
