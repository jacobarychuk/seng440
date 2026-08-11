# Software Optimization Project

This project demonstrates different optimization techniques applied to a sum of absolute differences (SAD) algorithm and analyzes their performance.

## Compile and run the testbench
This performs a correctness check that validates the output of the most optimized implementation against the original implementation to ensure that the computation remained unchanged.

```bash
gcc -mfpu=neon -O3 main.c sad.c -o main
```

```bash
./main
```

## Inspect the generated assembly code for each implementation
This will stop after compilation and output the assembly code for each implementation. This includes the original implementation, the resulting implementations from applying different optimization techniques, and the most optimized implementation.

```bash
gcc -mfpu=neon -O3 -S sad.c
```

```bash
cat sad.s
```

## Profile an implementation

1. Choose a compiler option for the desired SAD implementation
```bash
-Doriginal
```
```bash
-Dvectorization
```

2. Compile the profiling harness (replace `-Doriginal` with chosen compiler option)
```bash
gcc -Doriginal -mfpu=neon -O3 profile_harness.c sad.c -o profile_harness
```

3. Run the profiling harness with Callgrind
```bash
valgrind --tool=callgrind ./profile_harness
```

4. Extract the number of instructions per function call<br>
```bash
callgrind_annotate callgrind.out.* | grep compute_sad
```

5. Run the profiling harness with Cachegrind
```bash
valgrind --tool=cachegrind --cache-sim=yes --branch-sim=yes ./profile_harness
```

6. Extract the cache and branch data
```bash
cg_annotate --threshold=0 --show=Dr,D1mr,Bc,Bcm --show-percs=no cachegrind.out.* | grep compute_sad
```
