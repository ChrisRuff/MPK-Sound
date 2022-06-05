#include "MPK_Sound/include/MainWindow.hpp"

namespace ruff::sound {
MainWindow::MainWindow() {
    auto init = [this](){
        this->devices = std::make_unique<DeviceManager>();
        this->audio = std::make_unique<AudioManager>();

        // Create UI elements
        this->piano_preview = std::unique_ptr<Piano>(new Piano);
        this->devices_box = std::unique_ptr<QComboBox>(new QComboBox(this));
        this->sources_box = std::unique_ptr<QComboBox>(new QComboBox(this));
        this->make_mic_button = std::unique_ptr<QPushButton>(new QPushButton("Add Virtual Mic"));
        this->reset_button = std::unique_ptr<QPushButton>(new QPushButton("R"));
        this->file_watcher = std::unique_ptr<QFileSystemWatcher>(new QFileSystemWatcher(this));
        this->down_octave_button = std::unique_ptr<QPushButton>(new QPushButton("<<<"));
        this->up_octave_button = std::unique_ptr<QPushButton>(new QPushButton(">>>"));

        this->piano_preview->Read("/tmp/sounds.conf");
    };

    auto fill = [this](){
        this->file_watcher->addPath(temp_file.c_str());

        QStringList devices_items;
        for(const auto& device : this->devices->GetDevices())
        {
            devices_items.push_back(device.name.c_str());
        }
        this->devices_box->addItems(devices_items);

        QStringList sources_items;
        for(const auto& source : this->audio->GetSources())
        {
            sources_items.push_back(source.name.c_str());
        }
        this->sources_box->addItems(sources_items);

        this->watcher.Initialize(this->devices.get(), &this->CurrentDevice());
        this->watcher.start();
    };

    auto createLayouts = [this](){
        this->make_mic_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        this->reset_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        QHBoxLayout* controls = new QHBoxLayout();
        controls->addWidget(this->devices_box.get());

        QHBoxLayout* hbox2 = new QHBoxLayout();
        hbox2->addWidget(this->down_octave_button.get());
        hbox2->addStretch();
        hbox2->addWidget(this->up_octave_button.get());

        QHBoxLayout* hbox3 = new QHBoxLayout();
        hbox3->addWidget(this->sources_box.get());
        hbox3->addWidget(this->make_mic_button.get());
        hbox3->addWidget(this->reset_button.get());

        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setLineWidth(5);

        QVBoxLayout* vbox = new QVBoxLayout();
        vbox->addWidget(this->piano_preview.get());
        vbox->addLayout(controls);
        vbox->addLayout(hbox2);
        vbox->addWidget(line);
        vbox->addLayout(hbox3);

        QWidget* mainWidget = new QWidget;
        mainWidget->setLayout(vbox);
        this->setCentralWidget(mainWidget);
    };

    auto setupConnects = [this](){
        connect(this->devices_box.get(), &QComboBox::currentIndexChanged, this, [this](){
            this->watcher.Restart(&CurrentDevice());
        });
        connect(this->file_watcher.get(), &QFileSystemWatcher::fileChanged, [this](){
            this->devices->Read(this->CurrentDevice());
        });
        connect(this->devices->GetBean(), &Bean::valueChanged, this, &MainWindow::OnKeyboardPressed);
        connect(this->up_octave_button.get(), &QPushButton::clicked, this, [this](){piano_preview->Octave(true);});
        connect(this->down_octave_button.get(), &QPushButton::clicked, this, [this](){piano_preview->Octave(false);});
        connect(this->make_mic_button.get(), &QPushButton::clicked, this, [this](){this->audio->MakeInput(this->CurrentSource());});
        connect(this->reset_button.get(), &QPushButton::clicked, this, [this](){this->Reset();});
    };

    init();
    fill();
    createLayouts();
    setupConnects();


}
void MainWindow::closeEvent(QCloseEvent *event) {
    this->piano_preview->Write("/tmp/sounds.conf");
    this->watcher.Close();
    this->watcher.quit();
    QWidget::closeEvent(event);
}

void MainWindow::Reset() {
    this->audio->Reset();
    this->devices->StopWatch();
    disconnect(this->devices->GetBean(), &Bean::valueChanged, this, &MainWindow::OnKeyboardPressed);

    this->audio.reset(new AudioManager);
    this->devices.reset(new DeviceManager);

    connect(this->devices->GetBean(), &Bean::valueChanged, this, &MainWindow::OnKeyboardPressed);
    this->watcher.Initialize(this->devices.get(), &this->CurrentDevice());

}

void MainWindow::OnKeyboardPressed() {
    auto key_press = this->devices->GetBean()->getValue();
    piano_preview->Press(key_press);
}

Device& MainWindow::CurrentDevice() {
    return this->devices->GetDevices()[this->devices_box->currentIndex()];
}
InputDevice& MainWindow::CurrentSource() {
    return this->audio->GetSources()[this->sources_box->currentIndex()];
}


};