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

#include "MainWindow.h"

MainWindow::MainWindow(const char *windowTitle)
{
    Qt::WindowFlags flags = windowFlags(); //Get the enabled window flags
    flags |= Qt::WindowMinimizeButtonHint; //Add the minimize button
    setWindowFlags(flags);                 //Set the new modified window flags

    this->setWindowTitle(windowTitle);

    rowsNum = 8;
    columnsNum = 8;

    strDisabledSS = QString::fromUtf8("background-color: rgb(255, 255, 255);");
    strEnabledSS = QString::fromUtf8("background-color: rgb(200, 20, 20);");

    this->createLayout();
    this->createWidgets();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createLayout()
{
    vbMainBox = new QVBoxLayout(this);
    grButtonsGrid = new QGridLayout();
    hbOutputBox = new QHBoxLayout();
    vbOptions = new QVBoxLayout();

    this->setLayout(vbMainBox);
    vbMainBox->addLayout(grButtonsGrid);
    grButtonsGrid->setContentsMargins(0,0,0,0);
    vbMainBox->addLayout(hbOutputBox);
}

void MainWindow::createWidgets()
{
    int i=0;
    lbOutput = new QLabel();
    lbOutput->setFrameStyle(QFrame::Box | QFrame::Sunken);
    lbOutput->setLineWidth(1);
    lbOutput->setTextInteractionFlags(Qt::TextSelectableByMouse);
    strOutput = new QString();

    smButtonsMapper = new QSignalMapper(this);
    connect(smButtonsMapper, SIGNAL(mapped(int)), this,
            SIGNAL(btClicked(int)));
    connect(this, SIGNAL(btClicked(int)), this,
            SLOT(handleBtClicked(int)));

    this->placeButtons();

    hbOutputBox->addWidget(lbOutput);
    this->handleBtClicked(-1);

    /***********************OPTION BUTTONS:**************************/
    comboRows = new QComboBox();
    comboColumns = new QComboBox();
    btClearButtons = new QPushButton(tr("Clear all"));
    btSetButtons = new QPushButton(tr("Set all"));

    btClearButtons->setAutoDefault(false);
    btSetButtons->setAutoDefault(false);

    this->fillSizeCombos();
    vbOptions->addWidget(comboRows);
    vbOptions->addWidget(comboColumns);
    vbOptions->addStretch(100);
    vbOptions->addWidget(btClearButtons);
    vbOptions->addWidget(btSetButtons);

    connect(comboRows, SIGNAL(currentIndexChanged(int)), this,
            SLOT(matrixSizeChanged()));
    connect(comboColumns, SIGNAL(currentIndexChanged(int)), this,
            SLOT(matrixSizeChanged()));
    connect(btClearButtons, SIGNAL(released()), this,
            SLOT(handleBtClearButtons()));
    connect(btSetButtons, SIGNAL(released()), this,
            SLOT(handleBtSetButtons()));

}

void MainWindow::placeButtons(void)
{
    int i=0;
    grButtonsGrid->removeItem(vbOptions);
    while(!lstButtons.isEmpty())    //Delete all the current buttons
        delete lstButtons.takeFirst();
    //smButtonsMapper->removeMappings();//necessary??we'll see...#!#

    buttonsNum = columnsNum * rowsNum;
    for(i=0; i<buttonsNum; i++)
    {
        lstButtons.append(new QPushButton());
        lstButtons.at(i)->setText("0");
        lstButtons.at(i)->setFixedSize(30, 30);
        lstButtons.at(i)->setStyleSheet(strDisabledSS);
        connect(lstButtons.at(i), SIGNAL(clicked()), smButtonsMapper,
                SLOT(map()));
        smButtonsMapper->setMapping(lstButtons.at(i), i);
    }

    int c=0, r=0;
    i=0;
    for(c=0; c<columnsNum; c++)
    {
        for(r=0; r<rowsNum; r++)
        {
            grButtonsGrid->addWidget(lstButtons.at(i), r, c);
            lstButtons.at(i)->setAutoDefault(false);
            i++;
        }
    }
    grButtonsGrid->addLayout(vbOptions, 0, columnsNum, 0, 100);
}

void MainWindow::fillSizeCombos(void)
{
    QString str;
    for(int i=1; i<=10; i++)
    {
        str.clear();
        str.append(tr("Rows: "));
        str.append(QString::number(i));
        comboRows->addItem(str);
        str.clear();
        str.append(tr("Columns: "));
        str.append(QString::number(i));
        comboColumns->addItem(str);
    }
    comboRows->setCurrentIndex(rowsNum-1);
    comboColumns->setCurrentIndex(columnsNum-1);
}

void MainWindow::matrixSizeChanged(void)
{
    rowsNum = comboRows->currentIndex() + 1;
    columnsNum = comboColumns->currentIndex() + 1;
    this->placeButtons();
}

void MainWindow::handleBtClicked(int bt_id)
{
    if(bt_id != -1)
    {
        if(lstButtons.at(bt_id)->text() == "0")
        {
            lstButtons.at(bt_id)->setStyleSheet(strEnabledSS);
            lstButtons.at(bt_id)->setText("1");
        }
        else
        {
            lstButtons.at(bt_id)->setStyleSheet(strDisabledSS);
            lstButtons.at(bt_id)->setText("0");
        }
    }

    int i=0, c=0, r=0;
    unsigned long binNum;
    bool ok;
    QString binStr;
    char hexStr[20];
    QString hexQStr;

    strOutput->clear();
    strOutput->append("{ ");
    for(c=0; c<columnsNum; c++)
    {
        binNum=0; ok=1; binStr.clear();
        for(r=0; r<rowsNum; r++)
        {
            binStr.append(lstButtons.at(i)->text());
            i++;
        }
        binNum = binStr.toInt(&ok, 10);
        binary2hex(binNum, hexStr);
        hexQStr.clear();
        hexQStr.append(QString::fromStdString(hexStr));
        if(hexQStr.length() > 0)
        {
            strOutput->append("0x");
            if(hexQStr.length() == 1)
                strOutput->append("0");
            strOutput->append(hexQStr);
        }
        else
            strOutput->append("0x00");
        strOutput->append(", ");

    }
    strOutput->append("'\\0' ");
    strOutput->append(" }");

    lbOutput->setText(*strOutput);
}

void MainWindow::handleBtClearButtons(void)
{
    for(int i=0; i<lstButtons.count(); i++)
    {
        if(lstButtons.at(i)->text() == "1")
            this->btClicked(i);
    }
}

void MainWindow::handleBtSetButtons(void)
{
    for(int i=0; i<lstButtons.count(); i++)
    {
        if(lstButtons.at(i)->text() == "0")
            this->btClicked(i);
    }
}


/* Function to convert binary to hexadecimal. http://bit.ly/1e1JSUD */
void MainWindow::binary2hex(unsigned long n, char hex[])
{
    unsigned long i=0, decimal=0, rem;
    while (n!=0)
    {
        decimal += (n%10)*pow(2,i);
        n/=10;
        ++i;
    }

    /* Now, variable decimal contains binary number in decimal format. */
    i=0;
    while (decimal!=0)
    {
        rem=decimal%16;
        switch(rem)
        {
            case 10:
              hex[i]='A';
              break;
            case 11:
              hex[i]='B';
              break;
            case 12:
              hex[i]='C';
              break;
            case 13:
              hex[i]='D';
              break;
            case 14:
              hex[i]='E';
              break;
            case 15:
              hex[i]='F';
              break;
            default:
              hex[i]=rem+'0';
              break;
        }
        ++i;
        decimal/=16;
    }
    hex[i]='\0';
    strrev(hex);       /* Function to reverse string. */
}

//From StackOverflow:
void MainWindow::strrev(char *str)
{
    char temp, *end_ptr;

      /* If str is NULL or empty, do nothing */
    if((str == NULL) || !(*str))
        return;

    end_ptr = str + strlen(str) - 1;

      /* Swap the chars */
    while(end_ptr > str)
    {
        temp = *str;
        *str = *end_ptr;
        *end_ptr = temp;
        str++;
        end_ptr--;
      }
}
