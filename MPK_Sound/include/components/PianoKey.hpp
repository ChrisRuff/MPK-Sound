#pragma once
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <MPK_Sound/include/components/CommandDialog.hpp>

namespace ruff::sound {
class PianoKey : public QWidget {
    Q_OBJECT
private:
    int id;
    QPushButton* button;
    QLabel* note;
    CommandDialog* dialog;
    std::unique_ptr<Action>action;


public:
    PianoKey(int i);

    void Press(bool pressed);
public:
    void Write(std::ofstream& out_stream) const;
    void Read(std::vector<std::string>& line);

};
}