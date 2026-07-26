**Compile and run the program with:**

`gcc -mfpu=neon -O3 main.c sad.c -o main`

`./main`

**To inspect the generated assembly code for the two SAD implementations, stop compilation after generating the assembly code:**

`gcc -S sad.c`

**To profile the two SAD implementations:**
1. Compile the profiling harness<br>
`gcc -mfpu=neon -O3 profile_harness.c sad.c -o profile_harness`

3. Run the profiling harness with Callgrind<br>
`valgrind --tool=callgrind ./profile_harness`

5. Extract the number of instructions per function call<br>
`callgrind_annotate callgrind.out.* | grep compute_sad`
