#ifndef UTILS_CACEHMANAGER_H
#define UTILS_CACEHMANAGER_H

#include <type_traits>

namespace Utils
{
class CacheManager
{
public:
  CacheManager() = delete;

  template <typename T>
  static auto Write(const T &data) -> void
  {
    static_assert(std::is_trivially_copyable<T>::value,
                  "Cache data must be trivially copyable for baremetal safety.");

    CacheStorage<T>::instance      = data;
    CacheStorage<T>::isInitialized = true;
  }

  template <typename T>
  static auto Get(T &outData) -> bool
  {
    static_assert(std::is_trivially_copyable<T>::value,
                  "Cache data must be trivially copyable for baremetal safety.");
    bool result = false;

    if (CacheStorage<T>::isInitialized)
    {
      outData = CacheStorage<T>::instance;
      result  = true;
    }
    return result;
  }

  template <typename T>
  static auto Remove(void) -> void
  {
    static_assert(std::is_trivially_copyable<T>::value,
                  "Cache data must be trivially copyable for baremetal safety.");

    CacheStorage<T>::isInitialized = false;

    CacheStorage<T>::instance = T{};
  }

private:
  template <typename U>
  struct CacheStorage
  {
    static inline U instance{};
    static inline bool isInitialized{false};
  };
};
} // namespace Utils

#endif // UTILS_CACEHMANAGER_H
