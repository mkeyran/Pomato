#ifndef UTILS_H
#define UTILS_H
#include <functional>
#include <memory>
template <typename T>
struct identity
{
  typedef T type;
};

template <typename T>
void with_weak_ptr (std::weak_ptr<T>& weakptr,
                    typename identity<std::function<void(std::shared_ptr<T>&)>>::type func){
    if (auto ptr = weakptr.lock()){
        func(ptr);
    }
}

#endif // UTILS_H
