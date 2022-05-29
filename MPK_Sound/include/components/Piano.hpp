#pragma once
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include <MPK_Sound/include/devices/Keyboard.hpp>
#include <MPK_Sound/include/Bean.hpp>

namespace ruff::sound {
class Piano : public QWidget
{
private:
    std::vector<QPushButton*> keys;

public:
    Piano();

public:
    void Highlight(KeyPress);
};
}