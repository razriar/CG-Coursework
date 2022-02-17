//
// Created by daniil on 15.02.2022.
//

#pragma once

#include "mathematics.h"

class FieldOfView {
private:
    double _near = 1.;
    double _far = 10.;
    double _top = 1.;
    double _bottom = -1.;
    double _right = 1.;
    double _left = -1.;
    Matrix<4, 4, double> _matrix = Matrix<4, 4, double>(
            2. * _near / (_right - _left), 0., (_right + _left) / (_right - _left), 0.,
            0., 2. * _near / (_top - _bottom), (_top + _bottom) / (_top - _bottom), 0.,
            0., 0., (_far + _near) / (_far - _near), -2. * _near * _far / (_far - _near),
            0., 0., 1., 0.);
public:
    [[nodiscard]] const Matrix<4, 4, double>& matrix() const {return _matrix;};
};


