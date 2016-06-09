#ifndef DIALOGRESULTS_H
#define DIALOGRESULTS_H

#include <QDialog>
#include <QList>
#include "view.h"

namespace Ui {
class DialogResults;

}

class DialogResults : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResults(QList<View*> *viewList, QWidget *parent = 0);
    ~DialogResults();

private:
    Ui::DialogResults *ui;
    QList<View*> m_viewList;
};

#endif // DIALOGRESULTS_H
