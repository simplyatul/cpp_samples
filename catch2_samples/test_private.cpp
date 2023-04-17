/*
 * run: g++ test_private.cpp
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

struct TestFixture;

class TestTarget
{
public:
	TestTarget(int val = 0) { m_val = val; };

private:
	friend struct TestFixture;

	bool TryToAccessPrivates(int const& val)
	{
		m_val = val;
    return true;
	}

	int m_val;
};

typedef std::unique_ptr<TestTarget> TestTargetPtr_t;

struct TestFixture
{
	TestFixture() = default;

	void ThisCompilesFine()
	{
		TestTargetPtr_t pTarget(new TestTarget(0));

		int test = 8;
		pTarget->TryToAccessPrivates(test);
	}
};

TEST_CASE_METHOD(TestFixture, "TestingPrivates")
{
	TestTargetPtr_t pTarget(new TestTarget(0));
	int test = 8;
	// pTarget->TryToAccessPrivates(test); error: ‘bool TestTarget::TryToAccessPrivates(const int&)’ is private within this context

  TestFixture target;
  target.ThisCompilesFine();
}

