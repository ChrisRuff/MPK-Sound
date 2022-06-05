#pragma once
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>

#include <MPK_Sound/include/components/CommandDialog.hpp>
#include <MPK_Sound/include/Bean.hpp>
#include <MPK_Sound/include/components/PianoKey.hpp>

namespace ruff::sound {
class Piano : public QWidget
{
private:
    std::vector<PianoKey*> keys;
    QStackedWidget* board;
    int octave = 4;
public:
    Piano();

public:
    void Press(KeyPress);
    void Octave(bool up);

public:
    void Write(const std::filesystem::path&) const;
    void Read(const std::filesystem::path&);
};
}