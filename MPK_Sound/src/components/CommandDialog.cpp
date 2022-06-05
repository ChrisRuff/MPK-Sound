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
    this->sound_toggle = std::make_unique<QCheckBox>();
    this->file_path = std::make_unique<QLabel>("");

    QHBoxLayout* sound_hbox = new QHBoxLayout;
    sound_hbox->addWidget(sound_button.get());
    sound_hbox->addWidget(sound_box.get());
    sound_hbox->addWidget(file_path.get());

    QHBoxLayout* sound_hbox_extra = new QHBoxLayout;
    sound_hbox_extra->addStretch();
    sound_hbox_extra->addWidget(new QLabel("Toggle: "));
    sound_hbox_extra->addWidget(sound_toggle.get());

    this->accept_button = std::make_unique<QPushButton>("Accept");

    vbox = std::make_unique<QVBoxLayout>();
    vbox->addLayout(command_hbox);
    vbox->addLayout(sound_hbox);
    vbox->addLayout(sound_hbox_extra);
    vbox->addWidget(accept_button.get());

    connect(sound_box.get(), &QPushButton::pressed, this, [this, &sound_hbox](){
        auto file = QFileDialog::getOpenFileName();
        file_path->setText(file);
    });

    this->setLayout(vbox.get());
    this->show();
}

}