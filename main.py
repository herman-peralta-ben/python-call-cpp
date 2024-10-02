import ctypes
from timeit import default_timer as timer

def setup_simple_sum_lib():
    lib = ctypes.CDLL('./lib/libsimplesum.so')
    # Define the argument and return types of the function
    lib.add.argtypes = [ctypes.c_int, ctypes.c_int]
    lib.add.restype = ctypes.c_int
    return lib

def setup_parallel_sum_lib():
    lib = ctypes.CDLL('./lib/libparallelsum.so')
    # Define the argument and return types for the function
    lib.compute_sum.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
    lib.compute_sum.restype = ctypes.c_long
    return lib

if __name__ == "__main__":
    libsimplesum = setup_simple_sum_lib()
    # Call the C++ function
    result = libsimplesum.add(5, 3)
    print("libsimplesum: The result of adding 5 and 3 is:", result)

    ###########
    libparallelsum = setup_parallel_sum_lib()
    # Create an array in Python and pass it to the C++ function
    # array = (ctypes.c_int * 10)(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    print("libparallelsum: Python setup - start");
    start = timer()
    py_values = [i for i in range(100000000)]
    array = (ctypes.c_int * len(py_values))(*py_values)
    setup_time = timer() - start
    size = len(array)
    print("libparallelsum: Python setup took: {} ms".format(setup_time*1000))

    # Call the C++ function and get the result
    start = timer()
    result = libparallelsum.compute_sum(array, size)
    compute_time = timer() - start;
    print("libparallelsum: The total sum is: {}. Compute time: {} ms".format(result, compute_time*1000))
