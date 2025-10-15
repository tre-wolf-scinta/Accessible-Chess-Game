// doctest.h - the lightest feature-rich C++ single-header testing framework for unit tests and TDD
//
// Copyright (c) 2016-2023 Viktor Kirilov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
// The documentation can be found at the library's page:
// https://github.com/doctest/doctest/blob/master/doc/markdown/readme.md

// Minimal doctest header for basic testing
// For full version visit: https://github.com/doctest/doctest

#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_LIBRARY_INCLUDED

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <exception>

#define DOCTEST_VERSION_MAJOR 2
#define DOCTEST_VERSION_MINOR 4
#define DOCTEST_VERSION_PATCH 11

namespace doctest {

struct TestCase {
    const char* name;
    void (*func)();
};

class Context {
public:
    int run() {
        std::cout << "Running tests...\n";
        int failed = 0;
        for (auto& test : getTests()) {
            try {
                std::cout << "TEST: " << test.name << " ... ";
                test.func();
                std::cout << "PASSED\n";
            } catch (const std::exception& e) {
                std::cout << "FAILED: " << e.what() << "\n";
                failed++;
            }
        }
        std::cout << "\nTests completed. Failed: " << failed << "\n";
        return failed;
    }

    static std::vector<TestCase>& getTests() {
        static std::vector<TestCase> tests;
        return tests;
    }
};

struct TestRegistrar {
    TestRegistrar(const char* name, void (*func)()) {
        Context::getTests().push_back({name, func});
    }
};

class AssertionException : public std::exception {
    std::string msg;
public:
    AssertionException(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

inline void check(bool condition, const char* expr, const char* file, int line) {
    if (!condition) {
        std::ostringstream oss;
        oss << file << ":" << line << ": CHECK(" << expr << ") failed";
        throw AssertionException(oss.str());
    }
}

} // namespace doctest

#define DOCTEST_CONCAT_IMPL(x, y) x##y
#define DOCTEST_CONCAT(x, y) DOCTEST_CONCAT_IMPL(x, y)

#define TEST_CASE(name) \
    static void DOCTEST_CONCAT(test_func_, __LINE__)(); \
    static doctest::TestRegistrar DOCTEST_CONCAT(test_reg_, __LINE__)(name, &DOCTEST_CONCAT(test_func_, __LINE__)); \
    static void DOCTEST_CONCAT(test_func_, __LINE__)()

#define SUBCASE(name) if (true)

#define CHECK(expr) doctest::check((expr), #expr, __FILE__, __LINE__)
#define CHECK_FALSE(expr) doctest::check(!(expr), #expr, __FILE__, __LINE__)

#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// User should define this before including doctest.h
#else
int main(int argc, char** argv) {
    doctest::Context context;
    return context.run();
}
#endif

#endif // DOCTEST_LIBRARY_INCLUDED
