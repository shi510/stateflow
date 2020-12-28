# stateflow
modern C++ state management framework by transition condition.  

## Example
Define your state.  
```c++
#include <stateflow/stateflow.hpp>

enum class my_state : int{
    A, B, C, END
};
```

You have three tasks.  
The `task1` has 2 conditions.  
It transits to `my_state::B` When `your_data` is above 10, otherwise to `my_state::C`.  
The `task2` has no conditions and it transits to `my_state::C`.  
The `task3` has no conditions and it transits to `my_state::END`.  
```c++
auto task1 = []() -> my_state
{
    int your_data = 11;
    std::cout<<"task1"<<std::endl;
    if(your_data > 10)
        return my_state1::B;
    else
        return my_state1::C;
};
auto task2 = []() -> my_state
{
    std::cout<<"task2"<<std::endl;
    return my_state1::C;
};
auto task3 = []() -> my_state
{
    std::cout<<"task3"<<std::endl;
    return my_state1::END;
};
```

You can build transition graph.  
If current state is `my_state::A`, then it executes `task1`.  
Others are same as task1, but at `my_state::END`, it do nothing.  
```c++
stateflow<my_state> sf;
sf.add_task<my_state::A>(task1);
sf.add_task<my_state::B>(task2);
sf.add_task<my_state::C>(task3);
// nothing to do in the end state.
sf.add_task<my_state::END>();
```

Then, run your state machine from `my_state::A`.  
```c++
sf.run<my_state::A>();
```

The result above example should be as below.  
```
task1
task2
task3
```