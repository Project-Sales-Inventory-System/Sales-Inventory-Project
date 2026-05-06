#include <string>
#include <algorithm>
#include <cctype>

inline std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";

    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

inline std::string toLower(const std::string& str)
{
    std::string result = str;

    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });

    return result;
}