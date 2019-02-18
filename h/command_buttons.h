#ifndef COMMAND_BUTTONS_H
#define COMMAND_BUTTONS_H

#include <QWidget>

class QPushButton;

class CommandButtons : public QWidget
{
    Q_OBJECT
public:

    explicit CommandButtons(QWidget* parent = nullptr);

public slots:

    void            PushView();
    void            PushEdit();
    void            PushMkFile();
    void            PushMove();
    void            PushMkDir();
    void            PushDelete();
    void            PushExit();

private:
    QPushButton* view_;
    QPushButton* edit_;
    QPushButton* mk_file_;
    QPushButton* move_;
    QPushButton* mk_dir_;
    QPushButton* delete_;
    QPushButton* exit_;
};

#endif // COMMAND_BUTTONS_H
