#include <map>
#include <functional>

template <typename T,
    typename = std::enable_if_t<std::is_enum<T>::value>
>
struct stateflow
{
    template <T S>
    void add_task(std::function<T()> task)
    {
        __state_map[(int)(S)] = task;
    }

    template <T S>
    void add_task()
    {
    }
    
    template <T S>
    void run()
    {
        auto iter = __state_map.find((int)(S));
        while(iter != __state_map.end())
        {
            auto state = int(iter->second());
            iter = __state_map.find(state);
        }
    }

    std::map<int, std::function<T()>> __state_map;
};
