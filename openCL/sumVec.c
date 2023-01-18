#include <stdlib.h>
#include <stdio.h>
// Note that
#include <CL/cl.h>

#define LEN(arr) sizeof(arr) / sizeof(arr[0])
// device-side kernel source code, save by way of an array of strings, each statement suggesting the best end with a carriage return in some forums;
// At runtime compiled into an executable from a source on the GPU kernel codes
const char* src[] = { 
    "__kernel void vec_add(__global const float *a, __global const float *b, __global float *c)\n",
    "{\n",
    "    int gid = get_global_id(0);\n",
    "    c[gid] = a[gid] + b[gid];\n",
    "}\n"
};

int main()
{
        // create OpenCL context, the context associated with the GPU devices, see OpenCL 4.3 specification
    cl_context context = clCreateContextFromType(NULL, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);

        // Get the Device ID context, see section 4.3 The OpenCL
    size_t cb;
    clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &cb);
    printf("cf %d\n",cb);
    
    cl_device_id *devices = (cl_device_id*) malloc(cb);
    
    clGetContextInfo(context, CL_CONTEXT_DEVICES, cb, devices, NULL);

        // create a command-queue, see Section 5.1 The OpenCL
    cl_command_queue cmd_queue = clCreateCommandQueue(context, devices[0], 0, NULL);

        // Create kernel, see The OpenCL 5.4 and Section 5.5.1
    cl_program program = clCreateProgramWithSource(context, LEN(src), src, NULL, NULL);
    cl_int err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(program, "vec_add", NULL);

    // Host input terminal initialization
    size_t n = 5;
    float srcA[] = {1, 2, 3, 4, 5};
    float srcB[] = {5, 4, 3, 2, 1};
    float dst[5];

        // Set the kernel input and output parameters, see Section 5.2.1 The OpenCL
    cl_mem memobjs[3];
    memobjs[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * n, srcA, NULL);
    memobjs[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * n, srcB, NULL);
    memobjs[2] = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * n, NULL, NULL);
        // set "a", "b", "c" vector argument, see Section 5.5.2 The OpenCL
    err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobjs[0]);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&memobjs[1]);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&memobjs[2]);

    size_t global_work_size[1] = {n};
        // execute kernel, see the OpenCL 6.1 specification
    err = clEnqueueNDRangeKernel(cmd_queue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);

        // read output array, OpenCL specification detailed in section 5.2.2
    err = clEnqueueReadBuffer(cmd_queue, memobjs[2], CL_TRUE, 0, n*sizeof(cl_float), dst, 0, NULL, NULL);

    for (int i=0; i<n; ++i) {
        printf("-> %.2f\n", dst[i]);
    }
    // printf("num platform: %s\n",Name1);
    return 0;
}