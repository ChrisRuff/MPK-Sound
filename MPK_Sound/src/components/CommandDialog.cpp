#include <MPK_Sound/include/components/CommandDialog.hpp>

namespace ruff::sound {
CommandDialog::CommandDialog() {
    this->command_button = std::make_unique<QRadioButton>();
    this->command_box = std::make_unique<QTextEdit>();

    QHBoxLayout* command_hbox = new QHBoxLayout();
    command_hbox->addWidget(command_button.get());
    command_hbox->addWidget(command_box.get());

    this->sound_button = std::make_unique<QRadioButton>();
    this->sound_box = std::make_unique<QPushButton>("Add");

    QHBoxLayout* sound_hbox = new QHBoxLayout();
    sound_hbox->addWidget(sound_button.get());
    sound_hbox->addWidget(sound_box.get());


    this->accept_button = std::make_unique<QPushButton>("Accept");

    vbox = std::make_unique<QVBoxLayout>();
    vbox->addLayout(command_hbox);
    vbox->addLayout(sound_hbox);
    vbox->addWidget(accept_button.get());

    connect(sound_box.get(), &QPushButton::pressed, this, [this, &sound_hbox](){
        auto file = QFileDialog::getOpenFileName();
        file_path.reset(new QLabel(file));
        sound_hbox->insertWidget(1, file_path.get());
    });

    this->setLayout(vbox.get());
    this->show();
}

}