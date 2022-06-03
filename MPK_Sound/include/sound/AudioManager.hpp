#pragma once

#include <QRegularExpression>
#include <QProcess>

namespace ruff::sound {
struct InputDevice {
    int id;
    std::string name;
};
struct OutputDevice {
    int id;
    std::string name;
};
struct AudioClip {

};
class AudioManager {
private:
    std::unique_ptr<QProcess> audio_controller;
    OutputDevice default_sink;
    std::vector<InputDevice> sources;
    std::vector<int> module_indexs;

public:
    AudioManager();
    ~AudioManager();
    void Reset();

    std::vector<InputDevice> ListSinks();
    void Make(const QStringList& params);
    void MakeInput(const InputDevice&);

public:
    std::vector<InputDevice>& GetSources() { return sources; };
    OutputDevice GetDefaultSink();

};
};


