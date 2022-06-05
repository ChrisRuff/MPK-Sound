#pragma once

#include <QFileDialog>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>

#include <MPK_Sound/include/devices/Keyboard.hpp>
#include <MPK_Sound/include/Action.hpp>

namespace ruff::sound {
class CommandDialog : public QDialog {
    Q_OBJECT
public:
    std::unique_ptr<QVBoxLayout> vbox;

    std::unique_ptr<QRadioButton> command_button;
    std::unique_ptr<QRadioButton> sound_button;

    std::unique_ptr<QTextEdit> command_box;
    std::unique_ptr<QPushButton> sound_box;


    std::unique_ptr<QPushButton> accept_button;

    std::unique_ptr<QLabel> file_path;
    std::unique_ptr<QCheckBox> sound_toggle;

    CommandDialog();

    std::shared_ptr<QPushButton> GetButton();
};
}