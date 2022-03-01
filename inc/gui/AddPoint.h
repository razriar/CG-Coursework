//
// Created by daniil on 27.02.2022.
//

#pragma once

#include "Scene.h"
#include "Modeller.h"
#include "MaterialLibrary.h"
#include <QWidget>
#include <QColorDialog>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDialog>
#include <QPushButton>
#include <map>
#include <utility>

class AddPoint : public QDialog {
public:
    QGridLayout* layout;
    QLineEdit* name{};
    QDoubleSpinBox* xPos;
    QDoubleSpinBox* yPos;
    QDoubleSpinBox* zPos;
    QDoubleSpinBox* rColor;
    QDoubleSpinBox* gColor;
    QDoubleSpinBox* bColor;
    QPushButton* accepter;
    Scene& scene;
    void acceptfunc() {
        auto x = xPos->value();
        auto y = yPos->value();
        auto z = zPos->value();
        PointLight light(Vector<3, double>(x, y, z));
        light.name = name->text().toStdString();
        auto r = rColor->value();
        auto g = gColor->value();
        auto b = bColor->value();
        light.color() = {r, g, b};
        scene.lights().point().push_back(light);
        accept();
    };
    explicit AddPoint(Scene& s) : scene(s) {
        layout = new QGridLayout;
        setLayout(layout);
        auto* nameLabel = new QLabel("Название");
        layout->addWidget(nameLabel, 0, 0);
        name = new QLineEdit;
        layout->addWidget(name, 0, 1);
        auto* xLabel = new QLabel("Позиция по X");
        layout->addWidget(xLabel, 1, 0);
        xPos = new QDoubleSpinBox;
        xPos->setMinimum(-1);
        xPos->setMaximum(1);
        layout->addWidget(xPos, 1, 1);
        auto* yLabel = new QLabel("Позиция по Y");
        layout->addWidget(yLabel, 2, 0);
        yPos = new QDoubleSpinBox;
        yPos->setMinimum(-1);
        yPos->setMaximum(1);
        layout->addWidget(yPos, 2, 1);
        auto* zLabel = new QLabel("Позиция по Z");
        layout->addWidget(zLabel, 3, 0);
        zPos = new QDoubleSpinBox;
        zPos->setMinimum(-1);
        zPos->setMaximum(1);
        layout->addWidget(zPos, 3, 1);
        auto* rLabel = new QLabel("Цвет красный");
        layout->addWidget(rLabel, 4, 0);
        rColor = new QDoubleSpinBox;
        rColor->setMinimum(0);
        rColor->setMaximum(1);
        layout->addWidget(rColor, 4, 1);
        auto* gLabel = new QLabel("Цвет зеленый");
        layout->addWidget(gLabel, 5, 0);
        gColor = new QDoubleSpinBox;
        gColor->setMinimum(0);
        gColor->setMaximum(1);
        layout->addWidget(gColor, 5, 1);
        auto* bLabel = new QLabel("Цвет синий");
        layout->addWidget(bLabel, 6, 0);
        bColor = new QDoubleSpinBox;
        bColor->setMinimum(0);
        bColor->setMaximum(1);
        layout->addWidget(bColor, 6, 1);
        accepter = new QPushButton("Добавить");
        layout->addWidget(accepter, 7, 1);
        connect(accepter, &QPushButton::clicked, this, [this](){ acceptfunc();});
    }
};
