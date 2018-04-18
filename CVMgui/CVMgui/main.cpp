#include "MainWindow.h"
#include <QApplication>

/*
1. Update the version to 0.2.0 in AppInfo.h (and also during the following modular assignments). DONE
2. Expand the input of coins with 1 euro coins by adding a push button. DONE
3. Also, create a button for an incorrect coin. If a coin is not recognised, a suitable message must be displayed on the log display. This coin must be returned to the customer (the text must also appear in the log display).
4. If a customer decides when entering coins that he or she no longer wants a Coke, they must be able to press a button to have their money returned.
5. If the machine has no more Coke cans, a suitable message must be displayed on the display and the customer should not be able to enter any more money.
6. Give the buttons suitable colours.
7. Also, create the layout of the buttons in a grid format with a width of 3 buttons.
*/

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   w.show();

   return a.exec();
}
