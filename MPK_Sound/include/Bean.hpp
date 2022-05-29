#pragma once
#include <QObject>
#include <iostream>

#include <MPK_Sound/include/devices/Keyboard.hpp>

namespace ruff::sound {
class Bean : public QObject {
    Q_OBJECT
private:
    Q_PROPERTY(KeyPress val READ getValue WRITE setValue NOTIFY valueChanged)
    KeyPress val_;
public:
    Bean(QObject* parent = nullptr) : QObject(parent) {}

    KeyPress getValue() const { return val_; };
public
slots:
    void setValue(KeyPress val)
    {
        if(val_ != val)
        {
            val_ = val;
            std::cout << val.ToString() << std::endl;
            emit valueChanged(val_);
        }
    };
signals:
    void valueChanged(KeyPress val);

};
}


