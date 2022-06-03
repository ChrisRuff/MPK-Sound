#pragma once
#include <string>

#include <QString>

namespace ruff::sound {
struct KeyPress {
    int note{0};
    int velocity{0};
    bool on{false};

    KeyPress() = default;
    KeyPress(QString output) {
        auto pieces = output.split(" ");
        for (auto &piece: pieces) {
            piece = piece.trimmed();
        }
        pieces.removeAll(QString(""));
        if (pieces.size() < 7) return;

        on = pieces.at(2).compare("on") == 0;
        note = pieces.at(5).left(pieces.at(5).size() - 1).toInt();
        velocity = pieces.at(7).toInt();
    }

    bool operator==(const KeyPress& other) const {
        return note == other.note && velocity == other.velocity && on == other.on;
    }

    std::string ToString() {
        std::string out{};
        out += std::to_string(note);
        out += " ";
        out += on ? "Pressed " : "Released ";
        out += "with ";
        out += std::to_string(velocity);
        out += " velocity\n";
        return out;
    }
};
}
namespace std{
    template<>
    struct hash<ruff::sound::KeyPress>
    {
        std::size_t operator()(const ruff::sound::KeyPress& k) const
        {
            using std::hash;
            return (hash<int>()(k.note));
        }
    };
}
