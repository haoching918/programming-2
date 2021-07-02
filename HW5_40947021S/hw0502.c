#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"

int32_t main(int argc, char const *argv[])
{
    const char *cmd = "cat /proc/stat";
    FILE *stat = NULL;
    int32_t lastCPU = 0;
    int32_t lastIdle = 0;
    while (1)
    {
        char buf[100] = {0};
        int64_t idle = 0;
        int64_t CPU = 0;
        uint8_t idx = 1;

        stat = popen(cmd, "r");

        fgets(buf, 100, stat);
        buf[strlen(buf)-1] = 0;

        char *section = strtok(buf, "  ");
        while (1)
        {
            section = strtok(NULL, " ");
            if (section != NULL)
            { 
                if (idx == 4)
                    idle = strtol(section, NULL, 10);
                CPU += strtol(section, NULL, 10);
                idx++;
            }
            else
                break;
        }
        long double usage = 100 - ((idle-lastIdle) * 1.0 / (CPU-lastCPU) * 100.0);
        printf("CPU usage : %.2Lf %%\n", usage);
        sleep(1);

        pclose(stat);

        lastCPU = CPU;
        lastIdle = idle;
    }
    return 0;
}
