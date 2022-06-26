#pragma once

#include <QRegularExpression>
#include <QProcess>

namespace ruff::sound {
struct InputDevice { // Source
    int id;
    std::string device_name;
    std::string name;
};
struct OutputDevice { // Sink
    int id;
    std::string device_name;

    std::string name;
    bool default_sink{false};
};

class AudioManager {
private:
    std::unique_ptr<QProcess> audio_controller;
    OutputDevice default_sink;
    std::vector<InputDevice> sources;
    std::vector<OutputDevice> sinks;
    std::vector<int> module_indexs;

private:
    std::vector<InputDevice> ListSources();
    std::vector<OutputDevice> ListSinks();

public:
    AudioManager();
    ~AudioManager();
    void Reset();
    int Make(const QStringList& params);
    void MakeInput(const InputDevice&);
    void SetDefaultSink(int device_id);

public:
    std::vector<InputDevice>& GetSources() { return sources; };
    std::vector<OutputDevice>& GetSinks() { return sinks; };
    OutputDevice GetDefaultSink();

};
};


