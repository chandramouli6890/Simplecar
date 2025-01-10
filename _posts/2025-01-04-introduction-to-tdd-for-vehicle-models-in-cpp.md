---
layout: post
title: "Part 1: Introduction to Modeling the Dynamics of a Battery Electric Vehicle in C++"
author: "Chandramouli Gnanasambandham"
date: 2025-01-04
tags: [C++, Vehicle Modeling, TDD]
---

*DISCLAIMER: This blog series is based on publicly available knowledge and does
not use any proprietary information or algorithms from my current or past
employers. The content is solely for educational purposes.*

Welcome to this blog series where we’ll build a simple model of a battery
electric vehicle from scratch in C++ while using Test-Driven Development (TDD)
to. Whether you're an engineer, developer, or hobbyist, this series will help
you understand how to simulate dynamic systems in C++ and ditch tools like
Simulink for a flexible, code-first approach.

## What is a Vehicle Model?

A vehicle model simulates how a car behaves under various conditions. This
involves modeling components like:

* **Electric Engine**: Converts electrical energy into torque, propelling the
  vehicle forward.
* **Battery**: Stores electrical energy and supplies power to the electric engine
  for propulsion and auxiliary systems.
* **Drivetrain**: Transfers power from the electric engine to the wheels.
* **Brakes**: Convert vehicle's kinetic energy into heat or friction to reduce
  speed or stop.
* **Steering**: Allows the driver to guide the vehicle along a desired path. 
* **Chassis**: Represents the car's frame and handles dynamics like acceleration
  and braking.
* **Wheels and Tires**: Provide traction and influence vehicle's motion and
  handling.

These models are widely used in:

* Automotive design and testing.
* Simulators (e.g., racing or driver training).
* Robotics (e.g., autonomous vehicles).

In this blog series we’ll build a simplified vehicle model, while ensuring it
can be extended later for more complex simulations.

## Test-Driven Development (TDD)

#### What Is TDD?

Test-Driven Development (TDD) is a programming practice where you write tests
before writing the actual code.

The process looks like this:
1. **Write a test**: Define what the code should do.
2. **Run the test**: It will fail because the code isn’t implemented yet.
3. **Implement code**: Write just enough code to pass the test.
4. **Refactor**: Improve the code while ensuring the test still passes.

#### Why Use TDD for Simulation?
- **Ensures Correctness**: Each small functionality is tested immediately.
- **Guides Design**: Writing tests first encourages modular, well-structured
  code.
- **Prevents Over-Engineering**: You only implement what’s needed to pass the
  test.
- **Confidence in Changes**: Refactoring or adding new features won’t break
  existing functionality.

In this series, TDD will ensure that our vehicle model is robust, extensible,
and easy to understand.

## C++ as the Choice for Modeling Dynamical Systems

Traditionally, Matlab/Simulink has been the default choice for dynamic system
modeling. Like many others, I began my journey into dynamical modeling using
MATLAB/Simulink. However, my perspective has shifted over time. I now firmly
believe that C++ is a far superior option for this purpose. Below is a table
that highlights the key reasons behind my argument.

| **Criteria**              | **MATLAB/Simulink <br> Proprietary Tool**                                                                             | **C++ <br> Open-Source**                                                                   |
|:-------------------------:|-----------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **Licensing Costs**       | <span style="color:red">**High**</span> <br> Increases rapidly as you add toolboxes                                   | <span style="color:green">**Zero**</span> <br> Open-source with a strong developer community                    |
| **Ease of CI/CD**         | <span style="color:red">**Cumbersome**</span> <br> Requires runtime licenses! Not scalable for high-volume production | <span style="color:green">**Easy**</span> <br> Highly scalable deployment using containerization                |
| **Ease of Unit-Testing**  | <span style="color:red">**Cumbersome**</span> <br> Unit-testing requires additional toolboxes                         | <span style="color:green">**Easy**</span> <br> Standardized using frameworks like GTest or CTest                |
| **Ease of Collaboration** | <span style="color:red">**Very Hard**</span> <br> Requires proprietary diff and merge tools with limited reliability  | <span style="color:green">**Very Easy**</span> <br> Code reviews are straightforward with integrated diff tools |
| **Ease of Prototyping**   | <span style="color:green">**Very Easy**</span> <br> Visual, block-based programming that’s intuitive                  | <span style="color:red">**Hard**</span> <br> Text-based programming with a steep learning curve                 |

As you can clearly see, C++ is a powerful choice for simulating dynamic systems.

## Setup Development Environment

#### Prerequisites

Before we start coding, let's set up the tools and the environment we'll use throughout the series.

1. **C++ compiler**: GCC, Clang or MSVC
2. **Build system**: I will use [bazel](https://bazel.build/install) (version 8.0.0) in this blog series
3. **Version control**: Git and Github to track and share progress.

Get familiar with setting up a C++ project with bazel ([here](https://bazel.build/start/cpp) is a nice tutorial).

#### Write your first test 

Create a new directory

```bash
mkdir simplecar
cd simplecar
```

Define `googletest` as a external dependency in your`./simplecar/WORKSPACE` file

```bazel
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip"],
  strip_prefix = "googletest-1.14.0",
  sha256 = "1f357c27ca988c3f7c6b4bf68a9395005ac6761f034046e9dde0896e3aba00e4",
)
```

Create your first test by creating the `./simplecar/test/test_hello_world.cpp` file

```cpp
#include <string>
#include <gtest/gtest.h>

TEST(HelloWorld, assertHelloWorld)
{
    std::string test_str = "hello world!";
    ASSERT_TRUE(test_str == "Hello World!")
}
```

Create build rule for your first test in your `./simplecar/test/BUILD.bazel` file

```bazel
cc_test(
    name = "test_hello_world",
    srcs = ["test_hello_world.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
)
```

Run the test. You should see that the test fails.

```bash
$ bazel test //test:test_hello_world --test_output=all
...
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from HelloWorld 
[ RUN      ] HelloWorld.assertHelloWorld
test/test_hello_world.cpp:6: Failure
Value of: test_str == "hello world!"
  Actual: false
Expected: true

[  FAILED  ] HelloWorld.assertHelloWorld (0 ms)
[----------] 1 test from HelloWorld (0 ms total)
```

Fix the test and re-run. Note the capitalization in **H**ello and **W**orld

```cpp
...
TEST(HelloWorld, assertHelloWorld)
{
    std::string test_str = "Hello World!";
    ASSERT_TRUE(test_str == "Hello World!")
}
```

Now the test should pass

```bash
PASSED: //test:test_hello_world (see /home/chandramouli/.cache/bazel/_bazel_chandramouli/7cdf1cc68eba8c4eb7bc299947d9a9be/execroot/__main__/bazel-out/k8-fastbuild/testlogs/test/test_hello_world/test.log)
==================== Test output for //test:test_hello_world:
Running main() from gmock_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from HelloWorld
[ RUN      ] HelloWorld.assertHelloWorld
[       OK ] HelloWorld.assertHelloWorld (0 ms)
[----------] 1 test from HelloWorld (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.

Executed 0 out of 1 test: 1 test passes.
There were tests whose specified size is too big. Use the --test_verbose_timeout_warnings command line option to see which ones these are.
```

You just wrote a failing test and fixed it. Awesome! Welcome to test-driven
development.


## Next Steps

In the next [post](https://chandramouli6890.github.io/simplecar/2025/01/10/setting-up-simplecar-project-structure.html),
we’ll set up the foundation for our vehicle model by creating the project
structure and writing the first test for the Vehicle class. This will give us a
starting point for building the rest of the system.

The source code for the series is available on Github:
[https://github.com/chandramouli6890/simplecar](https://github.com/chandramouli6890/simplecar)

To follow along this post, make sure you checkout the following git-tag
```bash
git checkout part1-introduciton
```
