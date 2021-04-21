#ifndef AP_TEST_COMMON_CONVERT
#define AP_TEST_COMMON_CONVERT

#include <string>
#include <sstream>

namespace convert
{
    template <typename T, typename _Tag>
    struct str
    {
        using type = T;
        using tag = _Tag;
        static type from(const std::string& val) = delete;
        static std::string to(const type& val) = delete;
    };

    struct ap_tag
    {
    };
    struct boost_tag
    {
    };
    struct int_tag
    {
    };
    struct string_tag
    {
    };

    template <typename T>
    struct str<T, ap_tag>
    {
        using type = T;
        using tag = ap_tag;
        static type from(const std::string& val)
        {
            return val;
        }

        static std::string to(const type& val)
        {
            return val.to_dec();
        }
    };

    template <typename T>
    struct str<T, boost_tag>
    {
        using type = T;
        using tag = boost_tag;
        static type from(const std::string& val)
        {
            type result;
            result.assign(val);
            return result;
        }

        static std::string to(const type& val)
        {
            std::stringstream stream;
            stream << val;
            return stream.str();
        }
    };

    template <typename T>
    struct str<T, int_tag>
    {
        using type = T;
        using tag = int_tag;
        static type from(const std::string& val)
        {
            return static_cast<type>(stoll(val));
        }

        static std::string to(const type& val)
        {
            std::stringstream stream;
            stream << val;
            return stream.str();
        }
    };

    template <typename T>
    struct str<T, string_tag>
    {
        using type = T;
        using tag = string_tag;
        static type from(const std::string& val)
        {
            return val;
        }

        static std::string to(const type& val)
        {
            return val;
        }
    };
}

#endif
