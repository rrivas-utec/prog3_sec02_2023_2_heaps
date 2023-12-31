//
// Created by rrivas on 10/11/2023.
//

#ifndef PROG3_SEC02_2023_2_HEAPS_HEAP_H
#define PROG3_SEC02_2023_2_HEAPS_HEAP_H

#include <vector>
using namespace std;

namespace utec {

    template <
            typename T,
            template <typename ...> class Container=vector,
            typename Compare=std::less<T>
    >
    class heap {
        // Contanedor
        Container<T> cnt;
        Compare cmp;
        // Metodos auxiliares
        static size_t get_left_index(size_t parent_index) { return parent_index * 2; }
        static size_t get_right_index(size_t parent_index) { return parent_index * 2 + 1; }
        static size_t get_parent_index(size_t child_index) { return child_index / 2; }
        static bool is_root(size_t index) { return index == 1; }
        bool has_children(size_t parent_index) {
            auto left_index_calculate = get_left_index(parent_index);
            return left_index_calculate < cnt.size();
        }
        bool has_right_child(size_t parent_index) {
            return get_right_index(parent_index) < cnt.size();
        }
        size_t get_selected_index(size_t parent_index) {    // Busca el mayor de los hijos
            auto left_index = get_left_index(parent_index);
            if (has_right_child(parent_index)) {
                auto right_index = get_right_index(parent_index);
                return cmp(cnt[right_index],cnt[left_index])? left_index: right_index;
            }
            return left_index;
        }

        void percolate_up(size_t index) {
            // CONDICIONES BASES
            // Si es el root detenerse
            if (is_root(index)) return;
            // Obtener el indice del padre
            auto parent_index = get_parent_index(index);
            if (cmp(cnt[index],cnt[parent_index])) return;

            // CONDICIONES RECURSIVAS
            swap(cnt[index], cnt[parent_index]);
            // Ejecutar recursivamente el percolate up
            percolate_up(parent_index);
        }

        void percolate_down(size_t index) {
            // CONDICIONES BASES
            // Si no tiene hijos
            if (!has_children(index)) return;
            // Selecciona al hijo si es MAX: Mayor y si esl MIN: Menor
            auto child_selected_index = get_selected_index(index);
            if (cmp(cnt[child_selected_index], cnt[index])) return;

            // CONDICIONES RECURSIVAS
            swap(cnt[child_selected_index], cnt[index]);
            percolate_down(child_selected_index);
        }

        void heapify(size_t index) {
            // Condicion inicial (obtener el indice del padre
            auto cur_index = get_parent_index(index);
            while (cur_index >= 1) {
                percolate_down(cur_index);
                --cur_index;
            }
        }
    public:
        heap(): cnt(1) {}
        heap(Container<T> c): cnt(c.size() + 1) {
            copy(begin(c), end(c), begin(cnt) + 1); // O(n)
            heapify(size()); // O(n)
        }
        heap(Container<T> c, Compare cmp): cnt(c.size() + 1), cmp(cmp) {
            copy(begin(c), end(c), begin(cnt) + 1); // O(n)
            heapify(size()); // O(n)
        }
        size_t size() { return cnt.size() - 1; }
        bool empty() { return size() == 0; }
        T& top() { return cnt[1];}
        void push (T value) {
            cnt.push_back(value);
            percolate_up(size());
        }

        void pop() {
            swap(top(), cnt.back());
            cnt.pop_back();
            percolate_down(1);
        }

        bool replace(T old, T new_value) {
            auto it = find(begin(cnt)+1, end(cnt), old);
            if (it != end(cnt)) {
                *it = new_value;
                heapify(size());
                return true;
            }
            return false;
        }
    };

}

#endif //PROG3_SEC02_2023_2_HEAPS_HEAP_H
