#include <iterator>
#include "RectSliceManager.h"
#include "RectMaterial.h"

RectSliceManager::RectSliceManager() = default;

void RectSliceManager::SetBlank(IMaterial* blank) {
    this->_blank = blank;
}

void RectSliceManager::SetBlank(float height, float width) {
    this->SetBlank(new RectMaterial(height, width));
}

void RectSliceManager::AddMaterial(IMaterial* material) {
    this->_materials->push(material);
}
void RectSliceManager::AddMaterial(float height, float width) {
    this->AddMaterial(new RectMaterial(height, width));
}

void RectSliceManager::RemoveMaterial(int index) {
    this->_materials->pop(index);
}

void RectSliceManager::SetSlicer(ISlicer* slicer) {
    this->_slicer = slicer;
}

SliceResult RectSliceManager::Slice() {
    // создаем копию, чтобы сортировщик, используемый в некоторых алгоритмах, не изменил контейнер
    Container<IMaterial*> materialsCopy(this->_materials->size());
    std::copy(this->_materials->begin(),
              this->_materials->end(),
              materialsCopy.begin());
    return this->_slicer->Slice(this->_blank, &materialsCopy);
}

void RectSliceManager::EditMaterial(int index, float height, float width) {
    this->_materials->at(index) = new RectMaterial(height, width);
}

int RectSliceManager::MaterialCount() {
    return this->_materials->size();
}

RectSliceManager::~RectSliceManager() {}
