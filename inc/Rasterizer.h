//
// Created by daniil on 16.02.2022.
//

#pragma once

#include "Primitive.h"
#include "Fragment.h"
#include "BarycentricCalculator.h"
#include <utility>

class Rasterizer {
private:
    Primitive _primitive;
public:
    explicit Rasterizer(Primitive primitive) : _primitive(std::move(primitive)) {

    };
    [[nodiscard]] std::vector<Fragment> rasterize() const {
        auto& vertices = _primitive.vertices();
        auto& a = vertices[0];
        auto& b = vertices[1];
        auto& c = vertices[2];
        BarycentricCalculator calculator(a.position, b.position, c.position);
        auto matrix = calculator.calculate();
        Vector<2, int> min, max;
        min.x = (int)std::min(std::round(a.position.x), std::min(std::round(b.position.x), std::round(c.position.x)));
        min.y = (int)std::min(std::round(a.position.y), std::min(std::round(b.position.y), std::round(c.position.y)));
        max.x = (int)std::max(std::round(a.position.x), std::max(std::round(b.position.x), std::round(c.position.x)));
        max.y = (int)std::max(std::round(a.position.y), std::max(std::round(b.position.y), std::round(c.position.y)));
        std::vector<Fragment> result;
        for (int x = min.x; x < max.x; x++) {
            for (int y = min.y; y < max.y; y++) {
                auto barycentric = matrix * Vector<3, double>(1., (double)x, (double)y);
                static const double eps = .0;
                if (barycentric.x >= eps && barycentric.y >= eps && barycentric.z >= eps) {
                    Fragment fragment;
                    auto depths = Vector<3, double>(a.position.z, b.position.z, c.position.z);
                    auto bcDepths = barycentric * depths;
                    auto z = (int)(bcDepths.x + bcDepths.y + bcDepths.z);
                    fragment.position() = Vector<3, int>(x, y, z);
                    fragment.worldPosition() = (a.worldPosition * barycentric.x + b.worldPosition * barycentric.y +
                            c.worldPosition * barycentric.z);
                    auto textureXs = Vector<3, double>(a.texture.x, b.texture.x, c.texture.x);
                    auto bcTextureXs = barycentric * textureXs;
                    fragment.texture().x = bcTextureXs.x + bcTextureXs.y + bcTextureXs.z;
                    auto textureYs = Vector<3, double>(a.texture.y, b.texture.y, c.texture.y);
                    auto bcTextureYs = barycentric * textureYs;
                    fragment.texture().y = bcTextureYs.x + bcTextureYs.y + bcTextureYs.z;
                    fragment.normal() = (a.normal * barycentric.x + b.normal *
                            barycentric.y + c.normal * barycentric.z).normalize();
                    result.push_back(fragment);
                }
            }
        }
        return result;
    };
};


