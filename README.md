# Software Optimization Project

This project demonstrates different optimization techniques applied to a sum of absolute differences (SAD) algorithm and analyzes their performance.

## Compile and run the testbench

```bash
gcc -mfpu=neon -O3 main.c sad.c -o main
```

```bash
./main
```

## Inspect the generated assembly code for each implementation

```bash
gcc -S sad.c
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
