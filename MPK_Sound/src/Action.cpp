#include <MPK_Sound/include/Action.hpp>

namespace ruff::sound {
void SoundAction::Do() {
    if(process.state() == QProcess::Running)
        process.terminate();
    else if(process.state() == QProcess::NotRunning)
        process.start("/usr/bin/paplay", QStringList({sound_file.c_str(), "--device=apps"}));
}
void SoundAction::Stop() {
    if(toggle)
        process.terminate();
}
std::string SoundAction::GetType() {
    return "Sound";
}

std::string SoundAction::GetName() {
    return sound_file.filename();
}

void SoundAction::Write(std::ofstream& out_stream) const {
    out_stream << sound_file.string() << " " << toggle ? "1" : "0";
}

void CommandAction::Do() {
    if(process.state() == QProcess::Running)
        process.terminate();
    else if(process.state() == QProcess::NotRunning)
        process.start(command.c_str());
}
void CommandAction::Stop() {
}

std::string CommandAction::GetType() {
    return "Command";
}
std::string CommandAction::GetName() {
    return command;
}

void CommandAction::Write(std::ofstream& out_stream) const {
    out_stream << command;
}

}
