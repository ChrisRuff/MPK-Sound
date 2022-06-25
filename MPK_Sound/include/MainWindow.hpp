#pragma once

#include <QMainWindow>

#include <MPK_Sound/include/devices/DeviceManager.hpp>
#include <MPK_Sound/include/components/Piano.hpp>
#include <QComboBox>
#include <MPK_Sound/include/sound/AudioManager.hpp>

namespace ruff::sound {

class WatcherThread : public QThread {
Q_OBJECT
public:
    DeviceManager* manager;
    Device* device;

    WatcherThread() = default;
    void Initialize(DeviceManager* manager, Device* device) {
        this->manager = manager;
        this->device = device;
        if(this->manager && this->device)
        {
            this->manager->Watch(*this->device);
        }
    }
    void Close() {
        this->device = nullptr;
        this->manager->StopWatch();
    }
    void Restart(Device* device) {
        Close();
        this->device = device;
        if(this->manager && this->device)
        {
            this->manager->Watch(*this->device);
        }
    }
private:
};

class MainWindow : public QMainWindow {
private: // Member Variables
    std::unique_ptr<DeviceManager> devices{};
    std::unique_ptr<AudioManager> audio{};

private:
    WatcherThread watcher{};
    std::unique_ptr<QFileSystemWatcher> file_watcher;

public:
    MainWindow();

public:
    void closeEvent(QCloseEvent* event) override;

private: // QComponents
    Piano* piano_preview;
    QComboBox* devices_box;
    QComboBox* sources_box;
    QComboBox* sinks_box;
    QPushButton* make_mic_button;
    QPushButton* reset_button;
    QPushButton* down_octave_button;
    QPushButton* up_octave_button;

public: // Connect functions
    void Reset();
    void OnKeyboardPressed();

private: // Getters/Setters
    Device& CurrentDevice();
    InputDevice& CurrentSource();
};


}


