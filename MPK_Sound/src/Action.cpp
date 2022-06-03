#include <MPK_Sound/include/Action.hpp>

namespace ruff::sound {
void SoundAction::Do() {
    process.start("/usr/bin/paplay", QStringList({sound_file.c_str(), "--device=apps"}));
}
std::string SoundAction::GetType() {
    return "Sound";
}

void CommandAction::Do() {
    process.start(command.c_str());
}

std::string CommandAction::GetType() {
    return "Command";
}
}
