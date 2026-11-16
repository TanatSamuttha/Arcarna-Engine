#pragma once

#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

template<class ...Args>
class Event
{
private:
    std::vector<std::function<void(Args...)>> Handlers;
    std::queue<unsigned int> FreeSpace;

public:
    static inline Event NewEvent ()
    {
        return Event();
    }

    void Subscribe (std::function<void(Args...)> Handler)
    {
        if (!FreeSpace.empty())
        {
            Handlers[FreeSpace.front()] = std::move(Handler);
            FreeSpace.pop();
        }
        else
            Handlers.push_back(Handler);
    }

    void Unsubscribe (std::function<void(Args...)> Handler)
    {
        auto it = std::find(Handlers.begin(), Handlers.end(), Handler);
        if (it == Handlers.end())
            return;
        else if (it == Handlers.end() - 1)
        {
            Handlers.pop_back();
        }
        else
        {
            *it = nullptr;
            FreeSpace.push(it - Handlers.begin());
        }
    }

    void Invoke (Args... args)
    {
        for (auto Handler : Handlers)
        {
            Handler(std::forward<Args>(args)...);
        }
    }
};