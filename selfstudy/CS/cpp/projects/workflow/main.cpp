#include <QApplication>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <iostream>
#include <cstdint>
#include <string>

using std::cout;
using std::string;
using std::vector;

class MainWindow : public QWidget {
private:
    Q_OBJECT;
    vector<QPushButton*> buttons;
    QLabel* label;

public:
    MainWindow(QWidget* parent=nullptr) : QWidget(parent) {

        for (int i=0; i<3; ++i) {
            QString a = "Button " + QString::number(i+1);
            makeButton(a);
        }

        displayButtons();
        // button->setGeometry(50,50,200,50);
        // button->show();
        // connect(button,&QPushButton::clicked, this, &MainWindow::onClick);

        label = new QLabel("mane world", this);
        label->setAlignment(Qt::AlignCenter);
        label->setGeometry(50,50,250,50);
        label->hide();
    }

    void makeButton(const QString& textDisplay) {
        QPushButton* button;
        button = new QPushButton(textDisplay, this);
        button->hide();
        buttons.push_back(button);
    }

    void displayButtons() { 
        uint32_t x{50}, y{50};
        for (std::vector<QPushButton*>::iterator it=buttons.begin(); it!=buttons.end(); ++it, y+=150 ) {
            (*it)->setGeometry(x,y,200,150);
            (*it)->show();
        }
    }

public slots:
    void onClick() {
        label->show();
        // QProcess::startDetached("kitty --working-directory=$HOME/tmp/cpp");
    }

};

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1280, 700);
    window.setWindowTitle("Title");
    window.show();

    return app.exec();
}

#include "main.moc"
