#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

namespace cop4530 {

template <typename T>
class Stack {
public:
    Stack() = default;
    ~Stack() = default;

    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }
    void push(const T& x) { data.push_back(x); }
    void push(T&& x) { data.push_back(std::move(x)); }
    void pop() { if (!empty()) data.pop_back(); }
    T& top() { return data.back(); }
    const T& top() const { return data.back(); }
    int size() const { return data.size(); }
    void print(std::ostream& os, char ofc = ' ') const {
        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            os << *it << ofc;
        }
    }

    bool operator==(const Stack& rhs) const { return data == rhs.data; }
    bool operator!=(const Stack& rhs) const { return !(*this == rhs); }
    bool operator<=(const Stack& rhs) const { return data <= rhs.data; }

private:
    std::vector<T> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stk) {
    stk.print(os);
    return os;
}

} // namespace cop4530

#endif // STACK_H
