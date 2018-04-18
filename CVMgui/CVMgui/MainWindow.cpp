/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QColor>
#include <QLabel>
#include <QPixmap>

#include "AppInfo.h"
#include "MainWindow.h"

MainWindow::MainWindow()                                          //default constructor
{
   pStateMachine = new StateMachine(this);                        //set state machine for this dialog window

   createMenu();                                                  //create menu bar
   createHorizontalGroupBoxes();                                  //create buttons and logger
   createGridGroupBox();                                          //create icon and display

   buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok          //create Ok and Cancel buttons
                                    | QDialogButtonBox::Cancel);
   connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));  //connecting signal and slot for ok and cancel
   connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));  //

   QVBoxLayout *mainLayout = new QVBoxLayout;                     //creating vertical layout for entire window
   mainLayout->setMenuBar(menuBar);                               //sorted top to bottom
   mainLayout->addWidget(horizontalGroupBox1);
   mainLayout->addWidget(horizontalGroupBox2);
   mainLayout->addWidget(gridGroupBox);
   mainLayout->addWidget(horizontalGroupBox3);
   mainLayout->addWidget(buttonBox);

   setLayout(mainLayout);                                         //setting vertical layout
   setWindowTitle(tr(APPNAME_VERSION));                           //setting windowtitle
   pStateMachine->handleEvent(E_INIT);                            //setting initial state statemachine
}

void MainWindow::enableCentButtons(int firstButton, int lastButton, bool enable) {                 //enable/disable buttons
   for (int i = firstButton; i < lastButton + 1; i++) {
      buttons[i]->setEnabled(enable);
   }
}

void MainWindow::setDisplay(const QString &text) {                //set text to be displayed on display
   display->setText(text);
   display->update();
}

void MainWindow::setLogger(const QString &text) {                 //set text to be displayed on logger
   logDisplay->moveCursor(QTextCursor::End);                      //move cursor to end of line
   logDisplay->insertPlainText("\n" + text);                      //newline and put text
   logDisplay->moveCursor(QTextCursor::End);                      //move cursor to end of line
}

void MainWindow::createMenu()                                           //create menu bar
{
   menuBar = new QMenuBar;                                              //new menubar
   fileMenu = new QMenu(tr("&File"), this);                             //new dropdown menu (translate(&title), parent)
   exitAction = fileMenu->addAction(tr("E&xit"));                       //add action to dropdown menu (translate(&string))
   menuBar->addMenu(fileMenu);                                          //add dropdown menu to menubar
   connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));      //connect button click to exit
}

void MainWindow::createHorizontalGroupBoxes()                           //creating horizontal grouped boxes
{
   // HorizontalGroupBox 1 -----------------------------------------------------
   horizontalGroupBox1 = new QGroupBox(tr("Input cents"));              //create new group box with title
   QHBoxLayout *layout1 = new QHBoxLayout;                              //Horizontal layout

   buttons[0] = new QPushButton(tr("5C"));                              //create new pushbutton with title
   layout1->addWidget(buttons[0]);                                      //add button to horizontal layout
   connect(buttons[0], SIGNAL(released()), this, SLOT(coin5C()));       //connect button release to function

   buttons[1] = new QPushButton(tr("10C"));
   layout1->addWidget(buttons[1]);
   connect(buttons[1], SIGNAL(released()), this, SLOT(coin10C()));

   buttons[2] = new QPushButton(tr("20C"));
   layout1->addWidget(buttons[2]);
   connect(buttons[2], SIGNAL(released()), this, SLOT(coin20C()));

   enableCentButtons(0,2,false);                                            //disable all buttons (enabled in statemachine)
   horizontalGroupBox1->setLayout(layout1);                             //Set horizontal box layout as group layout

   // HorizontalGroupBox 2 -----------------------------------------------------
   horizontalGroupBox2 = new QGroupBox(tr("Input cents"));              //create new group box with title
   QHBoxLayout *layout2 = new QHBoxLayout;                              //Horizontal layout

   buttons[3] = new QPushButton(tr("50C"));
   layout2->addWidget(buttons[3]);
   connect(buttons[3], SIGNAL(released()), this, SLOT(coin50C()));

   buttons[4] = new QPushButton(tr("1E"));
   layout2->addWidget(buttons[4]);
   connect(buttons[4], SIGNAL(released()), this, SLOT(coin1E()));

   buttons[5] = new QPushButton(tr("3E"));
   layout2->addWidget(buttons[5]);
   connect(buttons[5], SIGNAL(released()), this, SLOT(coin3E()));

   enableCentButtons(3,5,false);                                            //disable all buttons (enabled in statemachine)
   horizontalGroupBox2->setLayout(layout2);                             //Set horizontal box layout as group layout

   // HorizontalGroupBox 3 -----------------------------------------------------
   horizontalGroupBox3 = new QGroupBox(tr("Logging"));                  //create new group box with title
   QHBoxLayout *layout3 = new QHBoxLayout;                              //horizontal layout
   logDisplay = new QTextEdit("Logging started", this);                 //new text editor with title and parent
   logDisplay->setOverwriteMode(false);                                 //unable to overwrite text
   logDisplay->setReadOnly(true);                                       //read only
   layout3->addWidget(logDisplay);                                      //add text editor to horizontal layout
   horizontalGroupBox3->setLayout(layout3);                             //set horizontal box layout as group layout
}

void MainWindow::createGridGroupBox()
{
   gridGroupBox = new QGroupBox(tr("Display"));                         //create new group box with title
   QGridLayout *layout = new QGridLayout;                               //grid layout

   QPixmap *image = new QPixmap(":/icons/Cola.ico");                    // in CVMresources.qrc //Icon
   QLabel *label = new QLabel;                                          //new label
   label->setPixmap(*image);                                            //set image as label
   layout->addWidget(label, 0, 0);                                      //add label to grid layout with position

   display = new QTextEdit(this);                                       //new text editor with parent
   display->setReadOnly(true);                                          //read only
   display->setTextColor(QColor(0,0,0));                                //text color is black
   display->setFontPointSize(30);                                       //font size is 30 points
   display->setFixedSize(500, 50);                                      //fixed size editor
   display->setOverwriteMode(true);                                     //overwriteable (but read only)
   layout->addWidget(display, 0, 1, 1, 5);                              //add text editor to layout with position and span

   layout->setColumnStretch(1, 10);                                     //column 1 stretched?? (no visible effect)
   layout->setColumnStretch(2, 20);                                     //column 2 stretched?? (no visible effect)
   gridGroupBox->setLayout(layout);                                     //set grid layout as group layout
}

//----------------------------------------------------------- GUI event handlers
void MainWindow::coin5C()
{
   pStateMachine->handleEvent(E_IN5C);
}

void MainWindow::coin10C()
{
   pStateMachine->handleEvent(E_IN10C);
}

void MainWindow::coin20C()
{
   pStateMachine->handleEvent(E_IN20C);
}

void MainWindow::coin50C()
{
   pStateMachine->handleEvent(E_IN50C);
}

void MainWindow::coin1E()
{
   pStateMachine->handleEvent(E_IN1E);
}

void MainWindow::coin3E()
{
   pStateMachine->handleEvent(E_IN3E);
}

