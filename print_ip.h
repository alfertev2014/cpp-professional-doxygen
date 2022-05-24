#pragma once

#include <cinttypes>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <iostream>
#include <type_traits>

/*! \brief Печать IP-адреса в целочисленном представлении
 *
 * Адрес может быть представлен в виде произвольного целочисленного типа. Выводить
 * побайтово в беззнаковом виде, начиная со старшего байта, с символом `.` (символ точки)
 * в качестве разделителя. Выводятся все байты числа.
 */
template <typename IpType, typename = std::enable_if_t<
    std::is_integral_v<IpType>
>>
inline void print_ip(IpType ip) {
    using unsigned_t = std::make_unsigned_t<IpType>;
    unsigned_t uip = ip;
    for (auto i = sizeof(IpType); ; ) {
        auto bitOffset = (i - 1) * 8;
        auto byte = static_cast<std::uint32_t>((uip & (static_cast<unsigned_t>(0xFFu) << bitOffset)) >> bitOffset);
        std::cout << byte;
        --i;
        if (i > 0) {
            std::cout << '.';
        } else {
            break;
        }
    }
}

/*! \brief Печать IP-адреса в виде строки
 *
 * Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от
 * содержимого.
 */
template <typename = void>
inline void print_ip(const std::string & ip) {
    std::cout << ip;
}

/*! \brief Печать IP-адреса как контейнера
 *
 * Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`.
 * Выводится полное содержимое контейнера поэлементно и разделяется `.` (символом
 * точка). Элементы выводятся как есть.
 */
template <typename T, template <typename> typename C, typename = std::enable_if_t<
    std::is_same_v<C<T>, std::vector<T>> || std::is_same_v<C<T>, std::list<T>>
>>
inline void print_ip(const C<T> &ip) {
    for (auto it = std::begin(ip); ;) {
        std::cout << *it;
        ++it;
        if (it != std::end(ip)) {
            std::cout << '.';
        } else {
            break;
        }
    }
}

/*! \brief Печать IP-адреса в представлении кортежа
 *
 * Опционально адрес может быть представлен в виде `std::tuple` при условии, что все
 * типы одинаковы. Выводится полное содержимое поэлементно и разделяется `.` (одним
 * символом точка). Элементы выводятся как есть. В случае, если типы кортежа не одинаковы,
 * должна быть выдана ошибка при компиляции кода.
 */
template <typename T, int I = 0, typename ...Ts>
inline void print_ip(const std::tuple<T, T, Ts...> &ip) {
    constexpr auto sz = sizeof...(Ts) + 2;
    if constexpr (I < sz) {
        std::cout << std::get<I>(ip);
        if constexpr (I < sz - 1) {
            std::cout << '.';
            print_ip<T, I + 1, Ts...>(ip);
        }
    }
}

/*! \brief Печать IP-адреса в представлении кортежа
 *
 * Опционально адрес может быть представлен в виде `std::tuple` из одного элемента.
 */
template <typename T>
inline void print_ip(const std::tuple<T> &ip) {
    std::cout << std::get<0>(ip);
}
