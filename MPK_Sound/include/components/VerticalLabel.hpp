//
// Created by chris on 2022-06-25.
//

#pragma once

#include <QLabel>
#include <QString>
#include <QPainter>

class VerticalLabel : public QLabel
{
public:
    VerticalLabel(QString text="") : QLabel(text) {};

private:
    void initPainter(QPainter* painter) const override {
        painter->translate(rect().center());
        painter->rotate(90);
        painter->translate(-rect().center());
    }
};