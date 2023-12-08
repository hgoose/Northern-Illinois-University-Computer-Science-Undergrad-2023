#include <QApplication>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <QStringList>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QPolygon>
#include <QBrush>
#include <QPen>
#include <QImage>
#include <QColor>
#include <QGradient>
#include <iostream>
#include <cstdint>
#include <string>
#include <functional>
#include <algorithm>

#define a_sizeof(x) sizeof(x) / sizeof(x[0])

using std::cout;
using std::string;
using std::vector;
using std::endl;

class MainWindow : public QWidget {
private:
    // Members
    
    // Pushbutton Stuff
    vector<QPushButton*> buttons;
    QPushButton* button;
    QPushButton* button2;

    // Label Stuff
    QLabel* label;

    // Color Defititions
    QColor C_blue;
    QColor C_gray;
    QColor C_LPurple;
    QColor C_DPurple;
    QColor C_LBlue;
    QColor C_DBlue;
    QLinearGradient G_purple;
    QLinearGradient G_blue;

    // Bools
    bool topBarVisible;

    // main.moc
    Q_OBJECT

public:

    // Constructor
    MainWindow(QWidget* parent=nullptr) 
        : QWidget(parent),
        C_blue("#18353d"),
        C_gray("#5d5d5d"),
        C_LPurple("#3d2945"),
        C_DPurple("#2d1537"),
        C_LBlue("#1a192c"),
        C_DBlue("#100f21"),
        G_purple(0,0,this->width(), this->height()),
        G_blue(0,0,this->width(), this->height()),
        topBarVisible(true)
    {
        G_purple.setColorAt(0.0, C_LPurple);
        G_purple.setColorAt(1.0, C_DPurple);

        G_blue.setColorAt(0.0, C_LBlue);
        G_blue.setColorAt(1.0, C_DBlue);

        // buttons[0]->setStyleSheet("QPushButton {"
        //            "  border: 2px solid black;"  // Adds a border
        //           "  border-radius: 50px;"
        //           "  background-color: lightgray;"  // Sets a background color
        //           "  color: black;"  // Sets text color
        //           "}"
        //           "QPushButton:hover {"
        //           "  background-color: gray;"  // Changes background on hover
        //           "}"
        //           "QPushButton:pressed {"
        //           "  background-color: darkgray;"  // Changes background when pressed
        //         "}");

        // button = new QPushButton("Example", this);
        // button->setGeometry(0,0,150,100);
        // button->setStyleSheet("QPushButton {"
        //               "  border: 2px solid black;"  // Adds a border
        //               "  border-radius: 50px;"
        //               "  background-color: lightgray;"  // Sets a background color
        //               "  color: black;"  // Sets text color
        //               "}"
        //               "QPushButton:hover {"
        //               "  background-color: gray;"  // Changes background on hover
        //               "}"
        //               "QPushButton:pressed {"
        //               "  background-color: darkgray;"  // Changes background when pressed
        //               "}");
        //
        // connect(button, &QPushButton::clicked, this, &MainWindow::toggleTopBarVisibility);
        //
        // button2 = new QPushButton("Example 2", this);
        // button2->setGeometry(0,100,150,100);

    }

    // Member functions
    void makeButtons(QStringList, uint32_t);
    void displayButtons(int[], int, int);
    void fn(size_t bn, void (MainWindow::*slotFunction)());
    
    void setFillBrush(QPainter&, const QColor&);
    void setFillBrush(QPainter& obj, const QLinearGradient& gradient, const QColor& penColor);
    void paintEvent(QPaintEvent *event) override;
    void setButtonStyleSheet(QString&);
    QPushButton* getButton(const int& position);



public slots:
    void cpptmp();
    void toggleTopBarVisibility();

};


void MainWindow::toggleTopBarVisibility() {
    topBarVisible = !topBarVisible;
    update();
}


void MainWindow::cpptmp() {
    QProcess::startDetached("kitty --working-directory=$HOME/tmp/cpp");
}

void MainWindow::fn(size_t bn, void (MainWindow::*slotFunction)()) {
    connect(buttons[bn], &QPushButton::clicked, this, slotFunction);
}


void MainWindow::makeButtons(QStringList titles, uint32_t size){
    for (uint32_t i=0; i<size; ++i) {
        button = new QPushButton(titles[i], this);
        button->hide();
        buttons.push_back(button);
    }
}

void MainWindow::displayButtons(int positions[], int n_buttons, int p_size) { 
    if (p_size <=0  || ((p_size % 4) != 0)) {
        cout << "Error: Array of positions must have enough values for " 
            << n_buttons << " buttons"
            << " each button requires four distinct values (x,y,w,h)" << endl;
        return;
    } else {
        for (int j=0, count=0; j<p_size; j=j+4, ++count) {
            buttons[count]->setGeometry(positions[j], positions[j+1], positions[j+2], positions[j+3]);
            buttons[count]->show();
        } 
    }
}

void MainWindow::setFillBrush(QPainter& obj, const QColor& color) {
    QBrush newbrush(color);
    QPen newpen(color);

    obj.setBrush(newbrush);
    obj.setPen(newpen);
}

void MainWindow::setFillBrush(QPainter& obj, const QLinearGradient& gradient, const QColor& penColor) {
    QBrush newbrush(gradient);
    QPen newpen(penColor);

    obj.setBrush(newbrush);
    obj.setPen(newpen);
}


void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Get the size of the window
    int width = this->width();
    int height = this->height();

    // Calculate the start position of the divider
    int dividerEndX = width / 5;

    // Leftdivider stuff
    setFillBrush(painter, G_blue, C_LBlue);
    QRect leftDividerRect(0, 0, dividerEndX, height);
    painter.drawRect(leftDividerRect);

    // Right divider stuff
    setFillBrush(painter, C_gray);
    QRect topBarRect(dividerEndX, 0, width, 50);
    if (topBarVisible) {
        painter.drawRect(topBarRect);
    }

}

QPushButton* MainWindow::getButton(const int& position) {
    return this->buttons[position];
}

void MainWindow::setButtonStyleSheet(QString& styleSheet) {
    for (auto it = this->buttons.begin(); it!=this->buttons.end(); ++it ) {
        (*it)->setStyleSheet(styleSheet);
    }
}

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1800, 1000);
    window.setWindowTitle("Title");
    // window.setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f58ef2, stop:1 black);");
    window.show();


    uint32_t n_buttons = 2;
    int buttonWidth = (window.width() / 5)+ 22;
    int positions[] = {
        0, 0, buttonWidth, 150,
        0, 155, buttonWidth, 150
    };
    int p_size = a_sizeof(positions);
    QStringList titlelist{"1", "2"};

    window.makeButtons(titlelist, n_buttons);
    window.displayButtons(positions, n_buttons, p_size);
    window.fn(0,&MainWindow::cpptmp); // Connect button 1
    
    QString styleSheet = ("QPushButton {"                   
        // "  border: 2px solid white;"  // Adds a border
        "border-top: 2px solid white;"
        "border-bottom: 2px solid white;"
          "  border-radius: 10px;"
          "  background-color: #2b294d;"  // Sets a background color
          "  color: white;"  // Sets text color
          "}"
          "QPushButton:hover {"
          "  background-color: gray;"  // Changes background on hover
          "}"
          "QPushButton:pressed {"
          "  background-color: darkgray;"  // Changes background when pressed
    "}");

    window.setButtonStyleSheet(styleSheet);
    // (window.getButton(0))->setStyleSheet(styleSheet);


    return app.exec();
}

#include "main.moc"
