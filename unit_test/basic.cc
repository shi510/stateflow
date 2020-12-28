#include <catch2/catch.hpp>
#include <stateflow/stateflow.hpp>
#include <string>

enum class my_state1 : int{
    A, B, C, END
};

TEST_CASE("state mahcine 1", "[sequence flow]")
{
    using myflow1 = stateflow<my_state1>;
    std::string task_names;
    auto task1 = [&task_names]()-> auto
    {
        int your_data = 11;
        task_names += "1";
        if(your_data > 10)
            return my_state1::B;
        else
            return my_state1::C;
    };
    auto task2 = [&task_names]() -> auto
    {
        task_names += "2";
        return my_state1::C;
    };
    auto task3 = [&task_names]() -> auto
    {
        task_names += "3";
        return my_state1::END;
    };

    SECTION( "sequence flow" )
    {
        myflow1 sf;
        sf.add_task<my_state1::A>(task1);
        sf.add_task<my_state1::B>(task2);
        sf.add_task<my_state1::C>(task3);

        // nothing to do in the end state.
        sf.add_task<my_state1::END>();

        sf.run<my_state1::A>();
        REQUIRE( task_names == "123" );
    }
}
