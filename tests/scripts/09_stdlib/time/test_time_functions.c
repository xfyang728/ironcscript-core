int main() {
    int current_time;
    int start_clock;
    int end_clock;
    double elapsed_time;
    int i;
    
    // Test time function
    current_time = (int)time(0);
    printf("Current time: %d\n", current_time);
    
    // Test clock function
    start_clock = (int)clock();
    
    // Longer delay
    for (i = 0; i < 10000000; i++) {
        // Do some work to prevent optimization
        if (i % 100000 == 0) {
            // Force some computation
        }
    }
    
    end_clock = (int)clock();
    elapsed_time = (double)(end_clock - start_clock) / 1000;
    printf("Elapsed time: %f seconds\n", elapsed_time);
    printf("Start clock: %d\n", start_clock);
    printf("End clock: %d\n", end_clock);
    printf("Clock difference: %d\n", end_clock - start_clock);
    
    return 0;
}