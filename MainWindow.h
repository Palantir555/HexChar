/*****************************************************************************
Copyright 2013 Juan Carlos Jiménez Caballero -- www.jcjc-dev.com

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QDialog>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QTimer>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QComboBox>

#include <string.h>
#include <stdio.h>
#include <math.h>

class MainWindow : public QDialog
{
    Q_OBJECT
private:
    void createLayout(void);
    void createWidgets(void);
    void fillSizeCombos(void);

    QVBoxLayout *vbMainBox;
    QGridLayout *grButtonsGrid;
    QHBoxLayout *hbOutputBox;
    QVBoxLayout *vbOptions;

    QSignalMapper *smButtonsMapper;
    QList<QPushButton*> lstButtons;
    QPushButton *bt_ptr;
    int rowsNum;
    int columnsNum;
    int buttonsNum;

    QLabel *lbOutput;
    QString *strOutput;

    QString strDisabledSS;
    QString strEnabledSS;

    QComboBox *comboRows;
    QComboBox *comboColumns;
    QPushButton *btClearButtons;
    QPushButton *btSetButtons;
        
public:
    MainWindow(const char *windowTitle);
    ~MainWindow(void);


    void binary2hex(unsigned long n, char hex[]);
    void strrev(char *str);

public slots:
    void placeButtons(void);
    void handleBtClicked(int bt_id=-1);
    void handleBtClearButtons(void);
    void handleBtSetButtons(void);
    void matrixSizeChanged(void);

signals:
    void btClicked(int);
};


#endif //MAINWINDOW_H
