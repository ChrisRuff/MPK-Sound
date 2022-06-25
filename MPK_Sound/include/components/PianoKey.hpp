#pragma once
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include <MPK_Sound/include/components/CommandDialog.hpp>
#include <MPK_Sound/include/components/VerticalLabel.hpp>

namespace ruff::sound {
class PianoKey : public QWidget {
    Q_OBJECT
private:
    int id;
    QPushButton* button;
    QLabel* note;
    QLabel* file_label;
    CommandDialog* dialog;
    std::unique_ptr<Action> action;

private:
    void resizeEvent(QResizeEvent*) override;

public:
    PianoKey(int i);

    void Press(bool pressed);
public:
    void Write(std::ofstream& out_stream) const;
    void Read(std::vector<std::string>& line);

};
}