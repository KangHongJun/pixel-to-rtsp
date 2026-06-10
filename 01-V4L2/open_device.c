#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


#define MAX_VIDEO_DEVICES 64

int main(void)
{
    int fd = 0;
    // const char* device_name = "/dev/video";
    
    struct v4l2_capability cap;
    char device_name[32];

    for (int minor = 0; minor<MAX_VIDEO_DEVICES; minor++)
    {
        snprintf(device_name, sizeof(device_name), "/dev/video%d", minor );
        fd = open(device_name, O_RDWR);
        
        if(fd < 0)
        {
            
            if (errno == ENOENT)
                continue;         
            if (errno == EACCES)
            {
                perror(device_name);
                continue; 
            }
            if (errno == EBUSY)
            {
                perror(device_name);
                continue; 
            }
        }

        ioctl(fd, VIDIOC_QUERYCAP, &cap);

        printf("device_name:  %s\n", device_name);
        printf("driver:       %s\n", cap.driver);
        printf("card:         %s\n", cap.card);
        printf("bus_info:     %s\n", cap.bus_info);
        printf("capabilities: 0x%08x\n", cap.capabilities);
        printf("device_caps:  0x%08x\n", cap.device_caps);
        printf("\n\n");
    }
    

    return 0;
}