#include <MPK_Sound/include/devices/DeviceManager.hpp>
#include <iostream>

namespace ruff::sound {
std::vector<Device> DeviceManager::List() {
    QProcess process{};
    //aseqdump -l
    process.start("/usr/bin/aseqdump", QStringList("-l"));
    process.waitForFinished();
    QByteArray stdout = process.readAllStandardOutput();
    QStringList output = QString(stdout).split('\n');
    output.remove(0);

    std::vector<Device> devices;
    for (auto& line : output) {
        QStringList device_string = line.split("  ");
        device_string.removeAll(QString(""));
        if (device_string.size() < 3)
            continue;

        Device line_device;
        line_device.port = device_string.at(0).trimmed().toStdString();
        line_device.name = device_string.at(1).trimmed().toStdString();
        line_device.port_name = device_string.at(2).trimmed().toStdString();
        devices.push_back(line_device);
    }

    return devices;
}

void DeviceManager::Read(Device device) {
    QProcess reader;
    reader.start("/usr/bin/tail", QStringList({"-n1", temp_file.c_str()}));
    reader.waitForFinished();
    QString line = reader.readAllStandardOutput();
    this->press->setValue(KeyPress(line));
}

void DeviceManager::Watch(Device device) {
    writer.reset(new DeviceThread(device));
    writer->start();
}

void DeviceManager::StopWatch() {
    writer->quit();
    if(writer->wait(5000))
        writer->terminate();
    writer.reset();
}

}