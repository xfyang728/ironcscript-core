#include <gtest/gtest.h>
#include <string>
#include "IronCScript.h"

using namespace cse;

TEST(SimpleExecution, AddOperation) {
    IronCScript engine;
    const std::string script = R"(
        int main() {
            int a = 10;
            int b = 20;
            int c = a + b;
            return c;
        }
    )";
    ASSERT_TRUE(engine.execute(script));
    EXPECT_EQ(engine.getLastReturnValue(), 30);
}

TEST(SimpleExecution, FunctionCall) {
    IronCScript engine;
    const std::string script = R"(
        int add(int a, int b) {
            return a + b;
        }

        int main() {
            return add(15, 25);
        }
    )";
    ASSERT_TRUE(engine.execute(script));
    EXPECT_EQ(engine.getLastReturnValue(), 40);
}

TEST(SimpleExecution, ControlFlow) {
    IronCScript engine;
    const std::string script = R"(
        int main() {
            int sum = 0;
            for (int i = 1; i <= 5; i++) {
                sum += i;
            }
            return sum;
        }
    )";
    ASSERT_TRUE(engine.execute(script));
    EXPECT_EQ(engine.getLastReturnValue(), 15);
}

TEST(SimpleExecution, Recursion) {
    IronCScript engine;
    const std::string script = R"(
        int factorial(int n) {
            if (n <= 1) {
                return 1;
            } else {
                return n * factorial(n - 1);
            }
        }

        int main() {
            return factorial(5);
        }
    )";
    ASSERT_TRUE(engine.execute(script));
    EXPECT_EQ(engine.getLastReturnValue(), 120);
}

TEST(SimpleExecution, FloatArithmetic) {
    IronCScript engine;
    const std::string script = R"(
        int main() {
            double a = 10.5;
            double b = 20.5;
            double c = a + b;
            return (int)c;
        }
    )";
    ASSERT_TRUE(engine.execute(script));
    EXPECT_EQ(engine.getLastReturnValue(), 31);
}