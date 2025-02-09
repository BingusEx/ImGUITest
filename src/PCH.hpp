#pragma once
#define _USE_MATH_DEFINES

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <iosfwd>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <ratio>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

#include <ShlObj_core.h>
#include <Windows.h>
#include <Psapi.h>
#include <d3d11.h>
#include <tchar.h>

#include "git.h"

#undef cdecl // Workaround for Clang 14 CMake configure error.

//Undef Win32 crap
#undef PlaySound 
#undef DeleteFile 

// Compatible declarations with other sample projects.
#define DLLEXPORT __declspec(dllexport)


//SHUT UUUUUUUUUPPP!!!!!

// The following are pure sillywarnings:
#pragma warning( disable: 4061 )    // enum value is not *explicitly* handled in switch
#pragma warning( disable: 4063 )    // case 'nn' is not a valid value for switch of enum 'Name'
#pragma warning( disable: 4099 )    // first seen using 'struct' now seen using 'class'
#pragma warning( disable: 4127 )    // conditional expression is constant
#pragma warning( disable: 4180 )    // qualifier applied to function type has no meaning
#pragma warning( disable: 4217 )    // member template isn't copy constructor
#pragma warning( disable: 4250 )    // inherits (implements) some member via dominance
#pragma warning( disable: 4251 )    // needs to have dll-interface to be used by clients
#pragma warning( disable: 4275 )    // exported class derived from non-exported class
#pragma warning( disable: 4347 )    // "behavior change", function called instead of template
#pragma warning( disable: 4355 )    // "'this': used in member initializer list
#pragma warning( disable: 4373 )    // override when arg types differ by const/volatile qualifiers
#pragma warning( disable: 4428 )    // MSVC 9: universal-character-name encountered in source
#pragma warning( disable: 4459 )    // local declaration hides global declaration
#pragma warning( disable: 4505 )    // unreferenced function has been removed
#pragma warning( disable: 4510 )    // default constructor could not be generated
#pragma warning( disable: 4511 )    // copy constructor could not be generated
#pragma warning( disable: 4512 )    // assignment operator could not be generated
#pragma warning( disable: 4513 )    // destructor could not be generated
#pragma warning( disable: 4610 )    // can never be instantiated user defined constructor required
#pragma warning( disable: 4623 )    // default constructor could not be generated
#pragma warning( disable: 4624 )    // destructor could not be generated
#pragma warning( disable: 4625 )    // copy constructor could not be generated
#pragma warning( disable: 4626 )    // assignment operator could not be generated
#pragma warning( disable: 4640 )    // a local static object is not thread-safe
#pragma warning( disable: 4646 )    // noreturn function should have a void return type
#pragma warning( disable: 4661 )    // a member of the template class is not defined.
#pragma warning( disable: 4670 )    // a base class of an exception class is inaccessible for catch
#pragma warning( disable: 4672 )    // a base class of an exception class is ambiguous for catch
#pragma warning( disable: 4673 )    // a base class of an exception class is inaccessible for catch
#pragma warning( disable: 4675 )    // resolved overload was found by argument-dependent lookup
#pragma warning( disable: 4702 )    // unreachable code, e.g. in <list> header.
#pragma warning( disable: 4710 )    // call was not inlined
#pragma warning( disable: 4711 )    // call was inlined
#pragma warning( disable: 4820 )    // some padding was added
#pragma warning( disable: 4917 )    // a GUID can only be associated with a class, interface or namespace
#pragma warning( disable: 4996 )    // MSVC 9: a C stdlib function has been "deprecated" (says MS)

#pragma warning( disable: 4834 )    // Temprorary disable nodiscard
#pragma warning( disable: 4101 )     //Yes, Yes MSVC. Thank you for telling me something i already know ffs.

