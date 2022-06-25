#pragma once
#include <fstream>
#include <string>
#include <filesystem>

#include <QProcess>

namespace ruff::sound {
class Action {
protected:
    QProcess process;
public:
    virtual std::string GetType() = 0;
    virtual std::string GetName() = 0;
    virtual void Do() = 0;
    virtual void Stop() = 0;
    virtual void Write(std::ofstream&) const = 0;
};

class SoundAction : public Action {
private:
    std::filesystem::path sound_file;
    bool toggle{true};
public:
    SoundAction(std::filesystem::path sound_file, bool toggle) : sound_file(sound_file), toggle(toggle) {}

    void Do() override;
    void Stop() override;
    std::string GetType() override;
    std::string GetName() override;
    void Write(std::ofstream&) const override;

};

class CommandAction : public Action {
private:
    std::string command;
public:
    CommandAction(std::string command) : command(command) {}

    void Do() override;
    void Stop() override;
    std::string GetType() override;
    std::string GetName() override;
    void Write(std::ofstream&) const override;
};
}