//
// Created by Kaapo on 10-Sep-22.
//

#ifndef ARPSARGE_HPP
#define ARPSARGE_HPP

#include <vector>
#include <string_view>
#include <algorithm>
#include <map>
#include <string>
#include <charconv>

template<typename char_type>
struct char_eq {
    bool operator()(char_type a, char_type b) noexcept {
        return (std::tolower(a) == std::tolower(b));
    }
};

class arpsarge {
public:
    arpsarge(std::int32_t const argc, char const *const *const argv) noexcept {
        for (std::int32_t i = 1; i < argc; ++i) {
            m_args.emplace_back(argv[i]);
        }
    };

    ~arpsarge() noexcept = default;

    bool has(std::string_view option) noexcept {
        return std::any_of(m_args.cbegin(), m_args.cend(), [&option](std::string_view const &sv) {
            return sv == option;
        });
    }

    /// \brief Gets a value from the arguments with a given option key.
    /// \tparam T Type of wanted value
    /// \param option Name of option key
    /// \return Returns the wanted value
    template<class T>
    T getv(std::string_view option) noexcept {
        if (has(option)) {
            auto it = std::find(m_args.begin(), m_args.end(), option);

            if ((it + 1) != m_args.end()) {
                std::string_view svalue{*(it + 1)};
                if constexpr (std::is_same_v<T, bool>) {
                    std::string_view true_view{"true"};
                    return std::search(svalue.begin(), svalue.end(), true_view.begin(), true_view.end(),
                                       char_eq<std::string_view::value_type>()) != svalue.end();
                } else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
                    T result{};
                    auto res = std::from_chars(svalue.data(), svalue.data() + svalue.size(), result);
                    if (res.ec == std::errc::invalid_argument) {
                        return T{};
                    }
                    return result;
                } else {
                    return svalue;
                }

            } else {
                std::cout << "getv: Argument out of bounds! arg: " << option << "\n";
                return T{};
            }

        } else {
            std::cout << "getv: No such argument found: " << option << "\n";
            return T{};
        }
    }

private:
    std::vector<std::string_view> m_args;
};


#endif //REGRAPSA_HPP
