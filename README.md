# ChoruSim

The library is distributed as a precompiled binary only, due to 
ongoing industrial collaboration. The underlying algorithms have been 
accepted for publication, and this repo is made publicly available 
to enable integration and reproducible research use.

## Directory Structure
```
ChoruSim_pub_bin
├── README.md
├── chorusim
│   ├── ChoruSimParser
│   ├── ChoruSimVcdConverter
│   └── libChoruSimulator.a
├── chorusim_pubruntime.h
├── examples
│   └── adder
│       ├── adder_tb.cpp
│       ├── circuit
│       └── result
├── mannual.md
└── utils
    ├── README.md
    ├── builder_config
    ├── chorusimRAM.lib
    ├── syn.ys
    └── translator_config
```

## Prerequisites
+ Operating System:​ Ubuntu 22.04
+ Compiler:​ GCC 12.5.0
+ CUDA Compiler:​ NVCC 12.4 (compiled on arch sm89)
+ Synthesis Tool:​ Yosys 0.61+21 (git sha1 8da8d681d, built with clang++ 18.1.8 -fPIC -O3)
+ Waveform Viewer:​ GTKWave 3.4.0

## Quick Start Guide

### Step 1: Generate the BLIF Netlist (Optional)

A precompiled adder `.blif` file is provided in `examples/adder/circuit/`. You can skip this step for the first try.
To generate the BLIF file yourself:
1. Update the file paths in `examples/adder/circuit/syn.ys`.
2. Run the following command:
```bash
yosys ./examples/adder/circuit/syn.ys
```
3. Ensure the generated `adder.blif` is placed in `examples/adder/circuit/`.

### Step 2: Build the Simulation Model

Compile the circuit into a GPU-accelerated computation model:
```bash
# if failed, run $ mkdir ./examples/adder/result
./chorusim/ChoruSimParser ./utils/builder_config
```

### Step 3: Compile and Run the Testbench

Compile the testbench and link with the simulation runtime library:
```bash
nvcc -std=c++20 -O3 -I. ./examples/adder/adder_tb.cpp -o adder_tb -L./chorusim -lChoruSimulator
./adder_tb
```

### Step 4: Convert Waveform to VCD Format

Convert the simulation output to a standard VCD (Value Change Dump) file:
```bash
./chorusim/ChoruSimVcdConverter ./utils/translator_config
```

### Step 5: View the Simulation Waveform

Visualize the VCD waveform using GTKWave:
```bash
gtkwave ./examples/adder/result/adder.vcd
```

For detailed documentation, refer to `manual.md`.