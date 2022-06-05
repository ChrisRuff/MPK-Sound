#include <MPK_Sound/include/components/Piano.hpp>

namespace ruff::sound {
Piano::Piano() {
    board = new QStackedWidget;
    for(int i = 0; i <= 120; ++i)
    {
        keys.push_back(new PianoKey(i));
    }
    for(int octave = 0; octave < 10; ++octave)
    {
        QHBoxLayout* octave_hbox = new QHBoxLayout;
        for(int i = octave*12; i < octave*12+12 && i < keys.size(); ++i)
        {
            octave_hbox->addWidget(keys[i]);
        }
        QWidget* board_widget = new QWidget;
        board_widget->setLayout(octave_hbox);
        board->addWidget(board_widget);
    }
    this->board->setCurrentIndex(2);
    QVBoxLayout* main = new QVBoxLayout;
    main->addWidget(board);
    this->setLayout(main);
}

void Piano::Press(KeyPress key) {
    keys[key.note]->Press(key.on);
    board->setCurrentIndex(key.note/12);
}

void Piano::Octave(bool up) {
    octave += up ? 1 : -1;
    board->setCurrentIndex(octave);
}

void Piano::Write(const std::filesystem::path& out_path) const {
    std::ofstream out_stream(out_path);
    for(const auto& key : keys)
    {
        key->Write(out_stream);
        out_stream << "\n";
    }
    out_stream.close();
}
void Piano::Read(const std::filesystem::path& in_path) {
    std::ifstream in_stream(in_path);
    std::string line;
    int idx = 0;
    while(getline(in_stream, line))
    {
        int word_count = 0;
        std::vector<std::string> words(3);

        std::stringstream ss(line);
        while(ss >> words[word_count])
        {
            ++word_count;
        }
        words.resize(word_count);
        this->keys[idx++]->Read(words);
    }
}
};
