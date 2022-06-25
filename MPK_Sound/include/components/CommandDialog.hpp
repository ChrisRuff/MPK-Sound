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

    QRadioButton* command_button;
    QRadioButton* sound_button;

    QTextEdit* command_box;
    QPushButton* sound_box;


    QPushButton* accept_button;

    QLabel* file_path;
    QCheckBox* sound_toggle;

    CommandDialog();

    std::shared_ptr<QPushButton> GetButton();
};
}