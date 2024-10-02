## Basic example of how Python can call C++ methods and get the result back

1. Compile the CPP libs (`.so` / `.dll`) into `./lib`.
   * See compile instructions on each cpp file.

2. Run $ `python3 main.py`
   * Check how the setup is done, you need to specify the args and return types of the C++ method using the `ctypes` lib.
   * In some cases, you'll need to convert Python types into ctypes before calling the C++ method.

Example output:

`$ python3 main.py`
```
libsimplesum: The result of adding 5 and 3 is: 8
```

Passing a large array adds overhead on the Python. Please note that this test uses threads to sum each half of the array.

```
libparallelsum: Python setup - start
libparallelsum: Python setup took: 12302 ms
parallel_sum.cpp: result: 4999999950000000
parallel_sum.cpp: 143 ms
libparallelsum: The total sum is: 4999999950000000. Compute time: 143.85287500000032 ms
```
