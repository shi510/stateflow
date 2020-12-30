#pragma once
#include <map>
#include <functional>
#include <tuple>
#include <type_traits>

template <typename T,
    typename = std::enable_if_t<std::is_enum<T>::value>
>
struct stateflow
{
    using _StateKeyType = int32_t;

    struct task_base
    {
        virtual _StateKeyType run() = 0;

        virtual ~task_base(){}
    };

    template <typename Fn, typename... Args>
    struct task : task_base
    {
        Fn __fn;
        std::tuple<Args...> __args;

        task(Fn fn, Args... args) :__fn(fn), __args(std::make_tuple(args...)){}

        _StateKeyType run() override
        {
            return static_cast<_StateKeyType>(std::apply(__fn, __args));
        }

        ~task() override{}
    };

    template <T S, typename Fn, typename ...Args>
    void add_task(Fn fn, Args... args)
    {
        __state_map[(_StateKeyType)S] = 
            std::make_shared<task<Fn, Args...>>(fn, args...);
    }

    template <T S>
    void add_task()
    {
    }
    
    template <T S>
    void run()
    {
        auto iter = __state_map.find((_StateKeyType)S);
        while(iter != __state_map.end())
        {
            auto state = iter->second->run();
            iter = __state_map.find(state);
        }
    }

    std::map<_StateKeyType, std::shared_ptr<task_base>> __state_map;
};
