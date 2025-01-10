---
layout: post
title: "Introduction to Modeling the Dynamics of a Battery Electric Vehicle in C++"
author: "Chandramouli Gnanasambandham"
date: 2025-01-04
tags: [C++, Vehicle Modeling, TDD]
---

<style>
  #next-post-container{
    text-align: right;
    margin-top: 20px;
  }
  #next-post-button {
    padding: 10px 20px;
    color: white;
    border: none;
    border-radius: 5px;
    font-size: 16px;
    cursor: pointer;
    transition: background-color 0.3s ease;
  }

  #next-post-button:hover {
    background-color: gray;
  }
</style>

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

## Why Test-Driven Development (TDD)?

## C++ as the Choice for Modeling Dynamical Systems

Traditionally, Matlab/Simulink has been the default choice for dynamic system
modeling. Like many others, I began my journey into dynamical modeling using
MATLAB/Simulink. However, my perspective has shifted over time. I now firmly
believe that C++ is a far superior option for this purpose. Below is a table
that highlights the key reasons behind my argument.

| **Criteria**              | **MATLAB/Simulink <br> Proprietary Tool**                                                                             | **C++ <br> Open-Source Programming Language**                                                                   |
|:-------------------------:|-----------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **Licensing Costs**       | <span style="color:red">**High**</span> <br> Increases rapidly as you add toolboxes                                   | <span style="color:green">**Zero**</span> <br> Open-source with a strong developer community                    |
| **Ease of CI/CD**         | <span style="color:red">**Cumbersome**</span> <br> Requires runtime licenses! Not scalable for high-volume production | <span style="color:green">**Easy**</span> <br> Highly scalable deployment using containerization                |
| **Ease of Unit-Testing**  | <span style="color:red">**Cumbersome**</span> <br> Unit-testing requires additional toolboxes                         | <span style="color:green">**Easy**</span> <br> Standardized using frameworks like GTest or CTest                |
| **Ease of Collaboration** | <span style="color:red">**Very Hard**</span> <br> Requires proprietary diff and merge tools with limited reliability  | <span style="color:green">**Very Easy**</span> <br> Code reviews are straightforward with integrated diff tools |
| **Ease of Prototyping**   | <span style="color:green">**Very Easy**</span> <br> Visual, block-based programming that’s intuitive                  | <span style="color:red">**Hard**</span> <br> Text-based programming with a steep learning curve                 |

As you can clearly see, C++ is a powerful choice for simulating dynamic systems.

## Setup Development Environment

<div id="next-post-container">
  <button id="next-post-button" style=""><a href="./c++/vehicle modeling/tdd/2025/01/04/introduction-to-tdd-for-vehicle-models-in-cpp.html">Next Post → </a></button>
</div>

link to a page [link](./_posts/2025-01-04-introduction-to-tdd-for-vehicle-models-in-cpp.md)

