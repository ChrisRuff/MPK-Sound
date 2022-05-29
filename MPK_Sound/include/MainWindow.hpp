#pragma once

#include <QMainWindow>

#include <MPK_Sound/include/devices/DeviceManager.hpp>
#include <MPK_Sound/include/components/Piano.hpp>
#include <QComboBox>

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
    DeviceManager manager{};
    std::vector<Device> devices{};

private:
    WatcherThread watcher{};
    QFileSystemWatcher* file_watcher;

public:
    MainWindow();

    void onKeyboardPressed();

private: // QComponents
    Piano* piano_preview;
    QComboBox* devices_box;

public: // Connect functions
private: // Getters/Setters
    Device& CurrentDevice();
};


}


