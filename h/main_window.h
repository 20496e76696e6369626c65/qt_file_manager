#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QMainWindow>

class MainPanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    MainPanel* panel_;
};

#endif // MAIN_WINDOW_H
