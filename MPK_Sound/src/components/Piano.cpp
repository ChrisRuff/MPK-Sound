#include <MPK_Sound/include/components/Piano.hpp>

namespace ruff::sound {
Piano::Piano() {
    QHBoxLayout* board = new QHBoxLayout(this);
    for(int i = 0; i < 27; ++i)
    {
        keys.emplace_back(new QPushButton);
        keys[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        keys[i]->setAutoFillBackground(true);
        board->addWidget(keys[i]);
    }

    this->setLayout(board);
}

void Piano::Highlight(KeyPress key) {
    int idx = (key.note+6) % keys.size();
    keys[idx]->setDown(key.on);
};
};
