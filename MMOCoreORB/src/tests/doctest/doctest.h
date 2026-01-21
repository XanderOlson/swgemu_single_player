#ifndef SWGEMU_TESTS_DOCTEST_H
#define SWGEMU_TESTS_DOCTEST_H

#include <cstdio>
#include <cstdlib>

namespace doctest {
namespace detail {
inline void check(bool result, const char* expr, const char* file, int line) {
	if (!result) {
		std::fprintf(stderr, "doctest check failed: %s (%s:%d)\n", expr, file, line);
		std::abort();
	}
}
} // namespace detail
} // namespace doctest

#define DOCTEST_STRINGIFY_IMPL(x) #x
#define DOCTEST_STRINGIFY(x) DOCTEST_STRINGIFY_IMPL(x)
#define DOCTEST_CONCAT_IMPL(a, b) a##b
#define DOCTEST_CONCAT(a, b) DOCTEST_CONCAT_IMPL(a, b)

#define TEST_CASE(name) static void DOCTEST_CONCAT(doctest_case_, __LINE__)()

#define CHECK(expr) doctest::detail::check(static_cast<bool>(expr), DOCTEST_STRINGIFY(expr), __FILE__, __LINE__)
#define CHECK_FALSE(expr) doctest::detail::check(!(expr), "!" DOCTEST_STRINGIFY(expr), __FILE__, __LINE__)

#endif // SWGEMU_TESTS_DOCTEST_H
