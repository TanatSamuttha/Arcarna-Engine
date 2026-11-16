#include "Event/Event.hpp"
#include "Assert.hpp"

unsigned int _uint = 0;
float _float = 0;

void Handler (unsigned int a, float b)
{
    _uint += a;
    _float += b;
}

int main ()
{
    Event<unsigned int, float> event = Event<unsigned int, float>::NewEvent();
    event.Subscribe(Handler);

    event.Invoke(2, 3.1);
    
    Assert(2u, _uint, "unsigned int");
    Assert(3.1f, _float, "float");
    
    return 0;
}