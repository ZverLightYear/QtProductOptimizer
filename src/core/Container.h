#ifndef PO_CONTAINER_H
#define PO_CONTAINER_H

#include <vector>

/**
 *  @brief Класс контейнера - обертка над std::vector<T>.
 *  @tparam T - тип хранимых элементов
 */
template<typename T>
class Container : public std::vector<T> {
public:
    /**
     * Конструктор контейнера
     */
    Container(): std::vector<T>(){}

    /**
     * Конструктор контейнера заданного размера
     * @param size - Разер контейнера
     */
    Container(int size): std::vector<T>(size){}

    /**
     * @brief Извлечение элемента из контейнера
     * @param index - индекс элемента в контейнере. При возникновении ошибок выбрасываются исколючения базового класса.
     * @return Элемент контейнера, находящийся по индексу index.
     */
    T pop(int index) {
        /// извлечение элемента
        auto res = this->at(index);
        /// удаление элемента в контейнере
        this->erase(this->begin()+index);
        /// возвращаем извлеченный элемент
        return res;
    }

    /**
     * @brief Помещение элемента в контейнер.
     * @param value - помещаемый элемент.
     */
    void push(T value) {
        /// вызов метода @push_back базового класса
        this->push_back(value);
    }
};

#endif //PO_CONTAINER_H
