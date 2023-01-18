#include <stdio.h>
#include <CL/cl.h>

int main(int argc, char** argv, char **argp) {
    cl_int status;
    cl_uint numPlatforms = 0;
    cl_platform_id *platforms = NULL;
    size_t numNames = 0;
    
    status = clGetPlatformIDs(0,NULL,&numPlatforms);
    platforms = (cl_platform_id*) malloc(numPlatforms * sizeof(cl_platform_id));
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    printf("numPlatform %d\n",numPlatforms);
    status = clGetPlatformInfo(platforms[0],CL_PLATFORM_NAME,0,NULL,&numNames);
    char Name[numNames];
    status = clGetPlatformInfo(platforms[0],CL_PLATFORM_NAME,sizeof(Name),Name,NULL);
    
    status = clGetPlatformInfo(platforms[1],CL_PLATFORM_NAME,0,NULL,&numNames);
    char Name1[numNames];
    status = clGetPlatformInfo(platforms[1],CL_PLATFORM_NAME,sizeof(Name),Name1,NULL);
    
    status = clGetPlatformInfo(platforms[2],CL_PLATFORM_NAME,0,NULL,&numNames);
    char Name2[numNames];
    status = clGetPlatformInfo(platforms[2],CL_PLATFORM_NAME,sizeof(Name),Name2,NULL);
    
    printf("num platform: %s\n",Name);
    printf("num platform: %s\n",Name1);
    printf("num platform: %s\n",Name2);
    
    return 0;
}