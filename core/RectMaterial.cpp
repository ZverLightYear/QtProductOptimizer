#include "RectMaterial.h"

RectMaterial::RectMaterial(float height, float width) {
    this->_height = height;
    this->_width = width;
}

float RectMaterial::Area() const {
    return this->_height * this->_width;
}

float RectMaterial::getWidth() const {
    return this->_width;
}

RectMaterial* RectMaterial::Rotate()
{
    return new RectMaterial(this->_width, this->_height);
}

float RectMaterial::getHeight() const {
    return this->_height;
}

RectMaterial::~RectMaterial() {}
