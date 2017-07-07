#include <sys/statfs.h>  
#include <stdio.h>  
#include <stdint.h>  
#define KB 1024.0                                               // 2^10  
#define MB 1048576.0                                        // 2^20   
#define GB 1073741824.0                                     // 2^30   
  
int main(void)  
{  
    struct statfs diskInfo;  
      
    statfs("/dev/vda1/", &diskInfo);  
    uint64_t blocksize = diskInfo.f_bsize;                   // 每个block里包含的字节数  
    uint64_t totalsize = blocksize * diskInfo.f_blocks;      // 总的字节数，f_blocks为block的数目  
    printf("Total_size = %lld B = %f KB = %f MB = %f GB\n",   
        totalsize,   
        totalsize / KB,   
        totalsize / MB,   
        totalsize / GB);  
    uint64_t freeDisk = diskInfo.f_bfree * blocksize;       // 剩余空间的大小  
    uint64_t availableDisk = diskInfo.f_bavail * blocksize; // 可用空间大小  
    printf("Disk_free = %f MB = %f GB\n"  
            "Disk_available = %f MB = %f GB\n",   
        freeDisk / MB,   
        freeDisk / GB,   
        availableDisk / MB,   
        availableDisk / GB);  
      
    return 0;  
}
