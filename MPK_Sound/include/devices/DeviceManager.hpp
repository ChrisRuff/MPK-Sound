#pragma once

#include <string>
#include <vector>
#include <thread>
#include <future>
#include <fstream>

#include <QProcess>
#include <QThread>
#include <filesystem>
#include <QFile>
#include <QFileSystemWatcher>
#include <QTimer>

#include "MPK_Sound/include/Bean.hpp"

namespace ruff::sound {

struct Device {
    std::string port{};
    std::string name{};
    std::string port_name{};
};

const std::filesystem::path temp_file = std::filesystem::temp_directory_path() / "MPKSOUND.txt";
class DeviceThread : public QThread
{
Q_OBJECT
public:
    DeviceThread(Device d) : QThread(), device(d) {};
    ~DeviceThread()
    {
        write_process->close();
        if(write_process->waitForFinished(5000))
            write_process->terminate();
        write_process.reset();
        std::cout << "Closing Port: " << device.port << std::endl;
    }
private:
    Device device;
    std::unique_ptr<QProcess> write_process;

    void run() override {
        write_process.reset(new QProcess);
        write_process->setStandardOutputFile(temp_file.c_str());
        std::cout << "Listening to Port: " << device.port << std::endl;
        write_process->start("/usr/bin/aseqdump", QStringList({"-p", QString(device.port.c_str())}));

        QThread::exec();
    }
};

class DeviceManager {
private:
    std::shared_ptr<Bean> press;

    std::unique_ptr<DeviceThread> writer;
public:
    DeviceManager() : press(new Bean){}

public:
    std::vector<Device> List();
    void Read(Device device);

    void Watch(Device device);
    void StopWatch();
public:
    Bean* GetBean() const { return press.get(); }
};

};
