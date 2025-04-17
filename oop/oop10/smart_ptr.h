#ifndef SMART_PTR_H
#define SMART_PTR_H

template <typename T>
class smart_ptr {
private:
    T *obj;
public:
    explicit smart_ptr(T *o = nullptr) : obj(o) {}
    ~smart_ptr() { delete obj; }

    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;

    smart_ptr(smart_ptr&& other) noexcept : obj(other.obj) {
        other.obj = nullptr;
    }
    smart_ptr& operator=(smart_ptr&& other) noexcept {
        if (this != &other) {
            delete obj;
            obj = other.obj;
            other.obj = nullptr;
        }
        return *this;
    }

    T* get() const { return obj; }
    T* operator->() const { return obj; }
    T& operator*() const { return *obj; }
};

#endif // SMART_PTR_H
