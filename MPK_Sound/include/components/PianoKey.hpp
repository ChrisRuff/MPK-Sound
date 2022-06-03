#pragma once
#include <QPushButton>
#include <QLabel>

namespace ruff::sound {
class PianoKey : public QWidget {
    Q_OBJECT
private:
    std::unique_ptr <QPushButton> button;
    std::unique_ptr <Action> action;
    std::unique_ptr <QLabel> note;
    std::unique_ptr <CommandDialog> dialog{nullptr};


public:
    PianoKey(int i) {
        button.reset(new QPushButton());
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        button->setAutoFillBackground(true);
        connect(button.get(), &QPushButton::pressed, this, [this]() {
            dialog.reset(new CommandDialog());
            connect(this->dialog->accept_button.get(), &QPushButton::pressed, this, [this](){
                if(this->dialog->sound_button->isChecked())
                {
                    this->action.reset(new SoundAction(this->dialog->file_path->text().toStdString()));
                }
                else if(this->dialog->command_button->isChecked())
                {
                    this->action.reset(new CommandAction(this->dialog->command_box->toPlainText().toStdString()));
                }
                if(this->action)
                {
                    note->setText(this->action->GetType().c_str());
                }
                this->dialog->close();
            });
            dialog->exec();
        });
        note.reset(new QLabel(QString::number(i)));
        note->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(note.get(), Qt::AlignTop);
        vbox->addWidget(button.get());

        this->setLayout(vbox);
    }

    void Press(bool pressed) {
        button->setDown(pressed);

        if(action && pressed)
            action->Do();
    }
};
}