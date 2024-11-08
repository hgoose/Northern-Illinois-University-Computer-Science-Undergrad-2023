// QT Specific
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
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>


// Other includes
#include <iostream>
#include <cstdint>
#include <string>
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

    // Layout stuff
    QWidget* leftDividerWidget; 
    QVBoxLayout* leftLayout; 
    int leftDividerEndX;

    // Label Stuff
    QLabel* selectorHead;

    // Font stuff
    QFont selectorHeadFont;

    // Color Defititions
    QColor C_blue;
    QColor C_gray;
    QColor C_LPurple;
    QColor C_DPurple;
    QColor C_LBlue;
    QColor C_DBlue;
    QLinearGradient G_purple;
    QLinearGradient G_blue;

    // Stylesheets
    QString buttonSheet;
    QString selectorHeadSheet;

    // Bools
    bool topBarVisible;

    // main.moc
    Q_OBJECT

public:

    // Constructor
    MainWindow(QWidget* parent=nullptr) 
        : QWidget(parent),

        // Colors
        C_blue("#2c3f55"),
        C_gray("#d3d3d3"),
        C_LPurple("#3d2945"),
        C_DPurple("#2d1537"),
        C_LBlue("#2c3f55"),
        C_DBlue("#1e2d3e"),
        G_purple(0,0,this->width(), this->height()),
        G_blue(0,0,this->width(), this->height()),

        // Booleans
        topBarVisible(true)
    {
        // Window size
        this->resize(1800,1000);

        G_purple.setColorAt(0.0, C_LPurple);
        G_purple.setColorAt(1.0, C_DPurple);

        G_blue.setColorAt(0.0, C_LBlue);
        G_blue.setColorAt(1.0, C_DBlue);

        leftDividerWidget = new QWidget(this);
        leftLayout = new QVBoxLayout(this);

        QStringList titlelist{"Math", "Computer Science"};
        this->makeButtons(titlelist, 2);

        buttonSheet = "QPushButton {"
            "background-color: #2c3f55;"
            "font-size: 14pt;"
            "color: #fff;"
            "border: 0;"
            "}"
            "QPushButton:hover {"
                "background-color: #334459;"     
                "border-right: 5px solid #63c3ae;"
        "}";

        this->setButtonStyleSheet(buttonSheet);

        selectorHeadSheet = "QLabel {"
            "color: white;"
            "font-size: 20pt;"
            "margin-bottom: 25px;"
        "}";

        this->setLabelStyleSheet(this->selectorHead, selectorHeadSheet);

        fn(0, &MainWindow::toggleTopBarVisibility);

    }

    // Member functions
    void makeButtons(QStringList, uint32_t);
    void displayButtons(int[], int, int);
    void fn(size_t bn, void (MainWindow::*slotFunction)());
    
    void setFillBrush(QPainter&, const QColor&);
    void setFillBrush(QPainter& obj, const QLinearGradient& gradient, const QColor& penColor);
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void setButtonStyleSheet(QString&);
    QPushButton* getButton(const int& position);
    void setLabelStyleSheet(QLabel* label, QString styles);


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
    selectorHead = new QLabel("Categorys", this);
    selectorHead->setAlignment(Qt::AlignCenter);
    // selectorHead->setTextFormat(Qt::italic);
    
    selectorHeadFont = selectorHead->font();
    selectorHeadFont.setItalic(true);
    selectorHead->setFont(selectorHeadFont);


    // selectorHead->
    leftLayout->addWidget(selectorHead);

    for (uint32_t i=0; i<size; ++i) {
        button = new QPushButton(titles[i], this);
        button->setFixedHeight(100);
        leftLayout->addWidget(button); // Add buttons to the left divider's vertical layout
        buttons.push_back(button);
    }
    leftDividerWidget->setLayout(leftLayout);
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

QPushButton* MainWindow::getButton(const int& position) {
    return this->buttons[position];
}

void MainWindow::setButtonStyleSheet(QString& styleSheet) {
    for (auto it = this->buttons.begin(); it!=this->buttons.end(); ++it ) {
        (*it)->setStyleSheet(styleSheet);
    }
}

void MainWindow::setLabelStyleSheet(QLabel* label, QString styles) {
    label->setStyleSheet(styles);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Get the size of the window
    int width = this->width();
    int height = this->height();

    leftDividerEndX = width / 5;

    // Leftdivider stuff
    setFillBrush(painter, G_blue, C_LBlue);
    QRect leftDividerRect(0, 0, leftDividerEndX, height);
    painter.drawRect(leftDividerRect);

    // Right divider stuff
    setFillBrush(painter, C_gray);
    QRect topBarRect(leftDividerEndX, 0, width, height);

    if (topBarVisible) {
        painter.drawRect(topBarRect);
    }

}

void MainWindow::resizeEvent(QResizeEvent* event) {
    // Call base class implementation (important for proper functionality)
    QWidget::resizeEvent(event);

    // Recalculate the width of the left divider
    leftDividerEndX = (this->width() / 5) - 15;

    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->setFixedWidth(leftDividerEndX);
    }

    if (selectorHead) {
        selectorHead->setFixedWidth(leftDividerEndX);
    }
}

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MainWindow window;
    // window.resize(1800, 1000);
    window.setWindowTitle("Title");
    // window.setStyleSheet("background-color: #eeedef;");
    window.show();


    uint32_t n_buttons = 2;
    int buttonWidth = (window.width() / 5)+ 22;
    int positions[] = {
        0, 0, buttonWidth, 150,
        0, 155, buttonWidth, 150
    };
    int p_size = a_sizeof(positions);

    // window.makeButtons(titlelist, n_buttons);
    // window.displayButtons(positions, n_buttons, p_size);
    // window.fn(0,&MainWindow::cpptmp); // Connect button 1
    
    // QString styleSheet = ("QPushButton {"                   
    //     // "  border: 2px solid white;"  // Adds a border
    //     "border-top: 2px solid white;"
    //     "border-bottom: 2px solid white;"
    //       "  border-radius: 10px;"
    //       "  background-color: #2b294d;"  // Sets a background color
    //       "  color: white;"  // Sets text color
    //       "}"
    //       "QPushButton:hover {"
    //       "  background-color: gray;"  // Changes background on hover
    //       "}"
    //       "QPushButton:pressed {"
    //       "  background-color: darkgray;"  // Changes background when pressed
    // "}");
    //
    // window.setButtonStyleSheet(styleSheet);
    // (window.getButton(0))->setStyleSheet(styleSheet);
    //

    return app.exec();



}

#include "main.moc"
