#include "MPK_Sound/include/MainWindow.hpp"

namespace ruff::sound {
MainWindow::MainWindow() {
    // Backend services
    this->devices = this->manager.List();

    // Create UI elements
    this->piano_preview = new Piano();
    this->devices_box = new QComboBox();
    QStringList items;
    for(const auto& device : this->devices)
    {
        items.push_back(device.name.c_str());
    }
    this->devices_box->addItems(items);
    this->devices_box->setCurrentIndex(3);
    connect(this->devices_box, &QComboBox::currentIndexChanged, this, [this](){
        this->watcher.Restart(&CurrentDevice());
    });

    file_watcher = new QFileSystemWatcher(this);
    file_watcher->addPath(temp_file.c_str());
    connect(file_watcher, &QFileSystemWatcher::fileChanged, [this](){
        this->manager.Read(this->CurrentDevice());
    });

    QHBoxLayout* controls = new QHBoxLayout(this);
    controls->addWidget(this->devices_box);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(this->piano_preview);
    vbox->addLayout(controls);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(vbox);
    this->setCentralWidget(mainWidget);

    connect(this->manager.GetBean(), &Bean::valueChanged, this, &MainWindow::onKeyboardPressed);

    this->watcher.Initialize(&this->manager, &this->CurrentDevice());
    this->watcher.start();
}

void MainWindow::onKeyboardPressed() {
    auto key_press = this->manager.GetBean()->getValue();
    piano_preview->Highlight(key_press);
}

Device& MainWindow::CurrentDevice() {
    return this->devices[this->devices_box->currentIndex()];
}
};