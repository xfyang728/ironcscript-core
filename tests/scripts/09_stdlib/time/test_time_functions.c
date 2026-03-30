#include <time.h>

int main() {
    time_t current_time;
    clock_t start_clock, end_clock;
    double diff_time;
    struct tm *time_info;
    char time_string[100];
    int i;
    
    // Test time function
    printf("Testing time functions...\n");
    
    current_time = time(NULL);
    printf("Current time (seconds since epoch): %lld\n", (long long)current_time);
    
    // Test gmtime
    time_info = gmtime(&current_time);
    if (time_info) {
        printf("GMT time: %04d-%02d-%02d %02d:%02d:%02d\n", 
               time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday,
               time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    }
    
    // Test strftime
    if (time_info) {
        strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
        printf("Formatted time: %s\n", time_string);
    }
    
    // Test clock function
    start_clock = clock();
    
    // Waste some time
    for (i = 0; i < 100000000; i++) {
        // Do nothing
    }
    
    end_clock = clock();
    diff_time = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.3f seconds\n", diff_time);
    
    // Test difftime
    time_t time1, time2;
    time(&time1);
    
    // Wait a bit
    for (i = 0; i < 100000000; i++) {
        // Do nothing
    }
    
    time(&time2);
    double diff = difftime(time2, time1);
    printf("Difference between times: %.3f seconds\n", diff);
    
    // Test mktime
    struct tm local_time;
    local_time.tm_year = 2024 - 1900; // Year since 1900
    local_time.tm_mon = 0; // January (0-11)
    local_time.tm_mday = 1;
    local_time.tm_hour = 12;
    local_time.tm_min = 0;
    local_time.tm_sec = 0;
    local_time.tm_isdst = 0;
    
    time_t converted_time = mktime(&local_time);
    printf("mktime result: %lld\n", (long long)converted_time);
    
    return 0;
}
