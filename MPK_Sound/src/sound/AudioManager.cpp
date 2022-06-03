#include <MPK_Sound/include/sound/AudioManager.hpp>
#include <iostream>

using namespace ruff::sound;

ruff::sound::AudioManager::AudioManager() {
    this->audio_controller = std::unique_ptr<QProcess>(new QProcess);
    this->sources = ListSinks();
    this->default_sink = GetDefaultSink();
}
AudioManager::~AudioManager() {
    Reset();
}

void AudioManager::Reset() {
    for(int module : module_indexs)
    {
        audio_controller->start("/usr/bin/pactl",
                                QStringList({"unload-module", QString::number(module)}));
        audio_controller->waitForFinished(); // will wait for 30 seconds
    }
}

std::vector<InputDevice> ruff::sound::AudioManager::ListSinks() {
    std::vector<InputDevice> sources;

    QRegularExpression inputsIdentifier = QRegularExpression("index: \\d+\\n\\tname: <alsa_input.*>(?s)(.*?)alsa\\.card_name = \"(.*?)\"");

    audio_controller->start("/usr/bin/pacmd", QStringList("list-sources"));
    audio_controller->waitForFinished();
    QByteArray stdout = audio_controller->readAllStandardOutput();

    auto matches = inputsIdentifier.globalMatch(stdout);
    while(matches.hasNext())
    {
        auto match = matches.next();
        sources.emplace_back(
                (match.captured().section(' ', 1, 1).section('\n', 0, 0).toInt()),
                (match.captured().section('"', -2, -2).toStdString()));
    }

    return sources;
}

void AudioManager::Make(const QStringList& params) {
    audio_controller->start("/usr/bin/pactl", params);
    audio_controller->waitForFinished();

    auto stdout = audio_controller->readAllStandardOutput();
    std::cout << stdout.toStdString() << std::endl;
    module_indexs.push_back(stdout.trimmed().toInt()); // Remove newline
}

void ruff::sound::AudioManager::MakeInput(const ruff::sound::InputDevice& source) {
    if(default_sink.id < 0 || source.id < 0)
    {
        throw "Invalid call to MakeInput";
    }
    std::cout << "Creating virtual mic from source: " << source.id << "-"<< source.name << std::endl;
    this->Make({"load-module", "module-null-sink",
                 "sink_name=output",
                 "sink_properties=device.description=(App+Mic)-Sink"});
    this->Make({"load-module", "module-combine-sink",
                 "sink_name=audio", ("slaves="+std::to_string(default_sink.id)).c_str(),
                "sink_properties=device.description=Audio-Sink"});
    this->Make({"load-module", "module-combine-sink",
                "sink_name=apps", "slaves=output,audio",
                "sink_properties=device.description=Apps-Sink"});
    this->Make({"load-module", "module-loopback", "sink=output",
                ("source="+std::to_string(source.id)).c_str()});
    this->Make({"load-module", "module-remap-source", "master=output.monitor",
                "source_name=output_mic", "source_properties=device.description=(Apps+Mic)-Source"});

}

OutputDevice AudioManager::GetDefaultSink() {
    QRegularExpression default_selector = QRegularExpression("\\* index: [0-9]+");
    audio_controller->start("/usr/bin/pacmd", QStringList("list-sinks"));
    audio_controller->waitForFinished();

    auto stdout = audio_controller->readAllStandardOutput();
    auto default_matched = default_selector.match(stdout);
    if(!default_matched.hasMatch())
    {
        return {-1, ""};
    }
    QString default_match = default_matched.captured();
    int default_id = default_match.right(1).toInt();
    //QString default_name = default_match.section(' ', 2, 2);

    OutputDevice default_device{default_id, ""};
    return default_device;
}



