#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProcess>
#include <iostream>

class MainWindow : public QWidget {
private:
    Q_OBJECT;
    QPushButton* button;
    QLabel* label;

public:
    MainWindow(QWidget* parent=nullptr) : QWidget(parent) {
        button = new QPushButton("Click", this);
        button->setGeometry(50,50,200,50);
        button->show();
        connect(button,&QPushButton::clicked, this, &MainWindow::onClick);

        label = new QLabel("Hello world", this);
        label->setAlignment(Qt::AlignCenter);
        label->setGeometry(50,50,250,50);
        label->hide();
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
