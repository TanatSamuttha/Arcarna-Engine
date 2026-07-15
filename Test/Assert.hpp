#pragma once

#include <iostream>

const float epsilon = 1e-6;

template<typename T>
void Assert (T expect, T value)
{
    std::cout 
        << (abs(expect - value) < epsilon? "Correct" : "Wrong")
        << " -> Expected: " << expect
        << " Value: " << value << '\n';
}

template<typename T>
void Assert (T expect, T value, std::string testName)
{
    std::cout 
        << (abs(expect - value) < epsilon? "Correct" : "Wrong")
        << " -> Expected: " << expect
        << " Value: " << value
        << " Test: " << testName + "\n";
}