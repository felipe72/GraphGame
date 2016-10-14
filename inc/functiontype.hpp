#ifndef FUNCTION_TYPE_HPP
#define FUNCTION_TYPE_HPP

#include <functional>
#include <utility>

using typeFunction = std::function<void(void)>;
using priority_function = std::pair<int, typeFunction>;

#endif