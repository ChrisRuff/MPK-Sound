#include <MPK_Sound/include/components/CommandDialog.hpp>

namespace ruff::sound {
CommandDialog::CommandDialog() {
    this->command_button = new QRadioButton();
    this->command_box = new QTextEdit();

    QHBoxLayout* command_hbox = new QHBoxLayout();
    command_hbox->addWidget(command_button);
    command_hbox->addWidget(command_box);

    this->sound_button = new QRadioButton();
    this->sound_box = new QPushButton("Add");
    this->sound_toggle = new QCheckBox();
    this->file_path = new QLabel("");

    QHBoxLayout* sound_hbox = new QHBoxLayout;
    sound_hbox->addWidget(sound_button);
    sound_hbox->addWidget(sound_box);
    sound_hbox->addWidget(file_path);

    QHBoxLayout* sound_hbox_extra = new QHBoxLayout;
    sound_hbox_extra->addStretch();
    sound_hbox_extra->addWidget(new QLabel("Toggle: "));
    sound_hbox_extra->addWidget(sound_toggle);

    this->accept_button = new QPushButton("Accept");

    vbox = std::make_unique<QVBoxLayout>();
    vbox->addLayout(command_hbox);
    vbox->addLayout(sound_hbox);
    vbox->addLayout(sound_hbox_extra);
    vbox->addWidget(accept_button);


    connect(sound_box, &QPushButton::pressed, this, [this, &sound_hbox](){
        auto file = QFileDialog::getOpenFileName();
        this->file_path->setText(file);
    });

    auto toggleCommand = [&](bool toggle){
        command_box->setEnabled(toggle);
    };
    auto toggleSound = [&](bool toggle){
        sound_box->setEnabled(toggle);
        sound_toggle->setEnabled(toggle);
    };

    connect(sound_button, &QRadioButton::pressed, this, [toggleCommand, toggleSound](){
        toggleCommand(false);
        toggleSound(true);
    });
    connect(command_button, &QRadioButton::pressed, this, [toggleCommand, toggleSound](){
        toggleCommand(true);
        toggleSound(false);
    });

    toggleCommand(false);
    toggleSound(false);

    this->setLayout(vbox.get());
    this->show();
}

}