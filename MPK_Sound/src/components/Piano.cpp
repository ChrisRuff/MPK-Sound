#include <MPK_Sound/include/components/Piano.hpp>

namespace ruff::sound {
Piano::Piano() {
    board.reset(new QStackedWidget);
    for(int i = 0; i <= 120; ++i)
    {
        keys.emplace_back(std::make_unique<PianoKey>(i));
    }
    for(int octave = 0; octave < 10; ++octave)
    {
        QHBoxLayout* octave_hbox = new QHBoxLayout;
        for(int i = octave*12; i < octave*12+12; ++i)
        {
            octave_hbox->addWidget(keys[i].get());
        }
        QWidget* board_widget = new QWidget;
        board_widget->setLayout(octave_hbox);
        board->addWidget(board_widget);
    }
    this->board->setCurrentIndex(4);
    QVBoxLayout* main = new QVBoxLayout;
    main->addWidget(board.get());
    this->setLayout(main);
}

void Piano::Press(KeyPress key) {
    int idx = (key.note) % keys.size();
    key.note = idx;

    keys[idx]->Press(key.on);
}

void Piano::Octave(bool up) {
    int prev = octave;
    octave += up ? 1 : -1;
    board->setCurrentIndex(octave);
}

};
