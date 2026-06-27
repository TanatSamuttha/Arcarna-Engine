#pragma once

#include <iostream>

template<typename T>
void Assert (T expect, T value)
{
    std::cout 
        << (expect == value? "Correct" : "Wrong")
        << " -> Expected: " << expect
        << " Value: " << value << '\n';
}

template<typename T>
void Assert (T expect, T value, std::string testName)
{
    std::cout 
        << (expect == value? "Correct" : "Wrong")
        << " -> Expected: " << expect
        << " Value: " << value
        << " Test: " << testName + "\n";
}