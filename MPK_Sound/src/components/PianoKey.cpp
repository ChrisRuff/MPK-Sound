#include <MPK_Sound/include/components/PianoKey.hpp>
#include <iostream>
#include <QCoreApplication>
#include <QResizeEvent>

namespace ruff::sound {
PianoKey::PianoKey(int i) : id(i) {
    button = new QPushButton("");
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    button->setAutoFillBackground(true);
    connect(button, &QPushButton::pressed, this, [this]() {
        dialog = new CommandDialog();
        connect(this->dialog->accept_button, &QPushButton::pressed, this, [this]() {
            if (this->dialog->sound_button->isChecked()) {
                this->action.reset(new SoundAction(this->dialog->file_path->text().toStdString(),
                                                   this->dialog->sound_toggle->isChecked()));
            } else if (this->dialog->command_button->isChecked()) {
                this->action.reset(new CommandAction(this->dialog->command_box->toPlainText().toStdString()));
            }
            if (this->action) {
                this->note->setText(this->action->GetType().c_str());
                this->file_label->setText(this->action->GetName().c_str());
                this->file_label->adjustSize();
                this->file_label->move(this->button->size().width()/2-this->file_label->size().width()/2, 0);
            }
            this->dialog->close();
        });
        dialog->exec();
    });
    note = new QLabel(QString::number(i));
    note->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    file_label = new VerticalLabel();
    file_label->setParent(this->button);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(note, Qt::AlignTop);
    vbox->addWidget(button);

    this->setLayout(vbox);
}

void PianoKey::Press(bool pressed) {
    button->setDown(pressed);

    if (action && pressed)
        action->Do();
    if (action && !pressed)
        action->Stop();
}

void PianoKey::Write(std::ofstream& out_stream) const {
    out_stream << id << " ";
    if(action)
        action->Write(out_stream);
}
void PianoKey::Read(std::vector<std::string>& line)
{
    this->id = std::stoi(line[0]);
    if(line.size() == 2)
    {
        this->action.reset(new CommandAction(line[1]));
    }
    else if(line.size() == 3)
    {
        this->action.reset(new SoundAction(line[1], line[2].compare("1")==0));
    }
    if(this->action)
    {
        this->note->setText(this->action->GetType().c_str());
        this->file_label->setText(this->action->GetName().c_str());
        this->file_label->adjustSize();
    }
}

void PianoKey::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    auto size = this->button->size();
    auto label_size = this->file_label->size();
    this->file_label->move(size.width()/2-label_size.width()/2, 0);
    this->file_label->setFixedHeight(size.height());
}
};