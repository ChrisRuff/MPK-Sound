#include <MPK_Sound/include/Action.hpp>

namespace ruff::sound {
void SoundAction::Do() {
    process.start("/usr/bin/paplay", QStringList({sound_file.c_str(), "--device=apps"}));
}
void SoundAction::Stop() {
    if(toggle)
        process.terminate();
}
std::string SoundAction::GetType() {
    return "Sound";
}

void SoundAction::Write(std::ofstream& out_stream) const {
    out_stream << sound_file.string() << " " << toggle ? "1" : "0";
}

void CommandAction::Do() {
    process.start(command.c_str());
}
void CommandAction::Stop() {
    process.terminate();
}

std::string CommandAction::GetType() {
    return "Command";
}

void CommandAction::Write(std::ofstream& out_stream) const {
    out_stream << command;
}
}
