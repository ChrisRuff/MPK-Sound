#pragma once
#include <string>
#include <filesystem>

#include <QProcess>

namespace ruff::sound {
class Action {
protected:
    QProcess process;
public:
    virtual std::string GetType() = 0;
    virtual void Do() = 0;
};

class SoundAction : public Action {
private:
    std::filesystem::path sound_file;
public:
    SoundAction(std::filesystem::path sound_file) : sound_file(sound_file) {}

    void Do() override;
    std::string GetType() override;

};

class CommandAction : public Action {
private:
    std::string command;
public:
    CommandAction(std::string command) : command(command) {}

    void Do() override;
    std::string GetType() override;
};
}