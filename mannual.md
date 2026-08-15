# ChoruSim Detailed Manual

## Overview

### Testbench Writing

The testbench interface is similar to Verilator. We provide example implementations; for comprehensive details, refer to `chorusim_pubruntime.h`.

### Builder Configuration (`builder_config`)

Example configuration file:
```
.gpu_num 2
.cudacore 21760 21760
.jobs 4
.dump_level $TOP -1
.max_macrospo_num 1000000
.lut_tail_threshold 2048
.lut_opt_level 0
.blif ./examples/adder/circuit/adder.blif
.output ./examples/adder/result/adder
.part_options $NITER 10 $SEED 0 $DBGLVL 0 $COST_COMPUTATION 1 $COST_STORAGE 0
.proxy_graph_settings $EXACT 0 $FANOUT_MAX 10000 $HYPEREDGE_MAX 50 $HYPEREDGE_APPROX 10
```

Core Settings:
1. `.gpu_num` – Number of target GPUs to use.
2. `.cudacore`​ – Specifies computational load per partition based on GPU core count (e.g., 21760 for RTX 5090).
3. `.dump_level` – Controls signal dumping for waveform generation.
   + Format:  `<scope1> <level1>`, `<scope2> <level2>`...
   + Only registers and top‑module ports are saved.
   + `$TOP` refers to the top‑level module.
   + `scope` follows the hierarchical naming in the design (e.g., for a module `moduleY` instantiated as `u2` inside `moduleX` which is instantiated as `u1` in `$TOP`, the scope is `u1.u2`).
   + `level` is an integer: `-1` saves all nested scopes from the current one; positive `N` saves `N` levels downwards (where `1` means only the current scope, and `0` saves nothing).
4. `.blif` – Input BLIF file path.
5. `.output` – Output compiled model file path.

### Translator Configuration (`translator_config`)

Example configuration file:
```
.target vcd
.jobs 1
.tick_range 0 0
.output ./examples/adder/result/adder.vcd
.part_num 1
.model_base_file ./examples/adder/result/adder
.wave_base_file ./examples/adder/result/adder
```

Core Settings:
1. `.output` – Output VCD file path.
2. `.part_num` – Must match `.gpu_num` in `builder_config`.
3. `.model_base_file` – Must match `.output` in `builder_config`; used to read signal names.
4. `.wave_base_file` – Should match the setting in `tb.cpp`; used to read paged waveform files.