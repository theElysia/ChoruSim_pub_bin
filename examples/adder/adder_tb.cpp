#include "chorusim_pubruntime.h"
#include <chrono>
#include <ctime>

using ChoruSim::simulator::ChoruSim_PubRuntime;

/// @brief
void example1()
{
    ChoruSim_PubRuntime dut;
    unsigned long long timestamp = 0;

    dut.init("./examples/adder/result/adder",
             "./examples/adder/result/adder");
    // dut.setRandomSeed((unsigned int)time(NULL));
    dut.setRandomSeed(0);

    // default signal value = 0
    dut.setValue("clk", 0);
    dut.eval();
    // manually set input port (primarily input)
    // a=6 b=3 -> c=9
    dut.dump(timestamp++);
    dut.setValue("clk", 1);
    dut.setValue("rst", 0);
    dut.setValue("a[0]", 0);
    dut.setValue("a[1]", 1);
    dut.setValue("a[2]", 1);
    dut.setValue("a[3]", 0);
    dut.setValue("b[0]", 1);
    dut.setValue("b[1]", 1);
    dut.setValue("b[2]", 0);
    dut.setValue("b[3]", 0);
    dut.eval();
    dut.dump(timestamp++);

    // save snapshot at ...
    dut.saveSnapShot("./examples/adder/result/adder_snapshot1");

    // random stimuli input
    for (int i = 0; i < 5; i++)
    {
        dut.setValue("clk", 0);
        dut.eval();
        dut.dump(timestamp++);
        dut.randomStimuli();
        dut.setValue("clk", 1);
        dut.eval();
        dut.dump(timestamp++);
    }

    // load snapshot from
    dut.loadSnapShot("./examples/adder/result/adder_snapshot1");

    // so you will see (a=6,b=3,c=9) again
    for (int i = 0; i < 2; i++)
    {
        dut.setValue("clk", 0);
        dut.eval();
        dut.dump(timestamp++);
        dut.setValue("clk", 1);
        dut.eval();
        dut.dump(timestamp++);
    }

    // example for forwardClk usage
    // if no eval needed, replace eval with forwardClk
    // note.  stmt  'dut.setValue("clk", 0);'  before forwardClk is a must
    for (int i = 0; i < 5; i++)
    {
        dut.setValue("clk", 0);
        dut.forwardClk(); // replace eval
        dut.dump(timestamp++);
        dut.randomStimuli();
        dut.setValue("clk", 1);
        dut.setValue("rst", 0);
        dut.eval();
        dut.dump(timestamp++);
    }

    printf("finish\n");
}

/// @brief
void example2()
{
    ChoruSim_PubRuntime dut;
    unsigned long long timestamp = 0;

    dut.init("./examples/adder/result/adder",
             "./examples/adder/result/adder");
    // dut.setRandomSeed((unsigned int)time(NULL));
    dut.setRandomSeed(0);

    // for better timing, you should warmup first (run several cycles) for GPU's metircs
    for (int i = 0; i < 5; i++)
    {
        dut.setValue("clk", 0);
        dut.eval();
        dut.dump(timestamp++);
        dut.randomStimuli();
        dut.setValue("clk", 1);
        dut.eval();
        dut.dump(timestamp++);
    }

    // record time
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; i++)
    {
        dut.setValue("clk", 0);
        dut.eval();
        dut.dump(timestamp++);
        dut.randomStimuli();
        dut.setValue("clk", 1);
        dut.eval();
        dut.dump(timestamp++);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    printf("use time %ld ms\n", duration.count());
}

int main()
{
    // example1();
    example2();
    return 0;
}