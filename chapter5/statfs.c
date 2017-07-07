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
    uint64_t blocksize = diskInfo.f_bsize;                   // ÿ��block��������ֽ���  
    uint64_t totalsize = blocksize * diskInfo.f_blocks;      // �ܵ��ֽ�����f_blocksΪblock����Ŀ  
    printf("Total_size = %lld B = %f KB = %f MB = %f GB\n",   
        totalsize,   
        totalsize / KB,   
        totalsize / MB,   
        totalsize / GB);  
    uint64_t freeDisk = diskInfo.f_bfree * blocksize;       // ʣ��ռ�Ĵ�С  
    uint64_t availableDisk = diskInfo.f_bavail * blocksize; // ���ÿռ��С  
    printf("Disk_free = %f MB = %f GB\n"  
            "Disk_available = %f MB = %f GB\n",   
        freeDisk / MB,   
        freeDisk / GB,   
        availableDisk / MB,   
        availableDisk / GB);  
      
    return 0;  
}
