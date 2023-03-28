#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdint.h>
#include <pthread.h>
#include <omp.h>
#include <sys/time.h>

struct arguments {
    int result;
    int n;
    int thread_num;
};

int mc_pi(int n, unsigned int seed);

int parse_arguments(char *str);

void *parallel_function(void *args);

int create_threads(int amount_threads, void *(*function)(void *), struct arguments *args);


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: Arguments <n> and <num_threads> required");
        return EXIT_FAILURE;
    }
    int n = parse_arguments(argv[1]);
    int num_threads = parse_arguments(argv[2]);
    if (n == -1 || num_threads == -1 || n < 1 || num_threads < 1) {
        fprintf(stderr, "Error: arguments parse error or not allowed");
        return EXIT_FAILURE;
    }

    struct arguments args[num_threads];
    int n_per_thread = n / num_threads;
    for (int i = 0; i < num_threads; i++) {
        args[i].n = n_per_thread;
        args[i].thread_num = i;
    }
    args[0].n += n % num_threads;  //if n cannot be distributed evenly

    double startTime = omp_get_wtime();
    create_threads(num_threads, &parallel_function, args);
    double endTime = omp_get_wtime();

    int64_t in_count_total = 0;
    for (int i = 0; i < num_threads; ++i) {
        in_count_total += args[i].result;
    }
    double mc_pi_approx = 4 * in_count_total / (int64_t) n;
    printf("Monte Carlo Pi approximation time = %lf, threads = %d and n = %d : %lf\n", endTime - startTime, num_threads, n, mc_pi_approx);

    return EXIT_SUCCESS;
}

void *parallel_function(void *args) {
    struct arguments *arguments = args;
    unsigned int seed = time(NULL) + arguments->thread_num;
    arguments->result = mc_pi(arguments->n, seed);
    return NULL;
}

int create_threads(int amount_threads, void *(*function)(void *), struct arguments *args) {
    pthread_t thread_ids[amount_threads];
    for (int i = 0; i < amount_threads; ++i) {
        if (pthread_create(&thread_ids[i], NULL, function, (void *) &args[i]) != 0) {
            perror("pthread_create failed");
            return EXIT_FAILURE;
        }
    }
    for (int i = 0; i < amount_threads; ++i) {
        pthread_join(thread_ids[i], NULL);
    }
    return EXIT_SUCCESS;
}

//Source: PS Betriebssysteme Ex03 - https://github.com/uibk-dps-teaching/ps_os_2022/tree/main/exercise03
int mc_pi(int n, unsigned int seed) {
    int in_count = 0;
    for (int i = 0; i < n; ++i) {
        const double x = rand_r(&seed) / (double) RAND_MAX;
        const double y = rand_r(&seed) / (double) RAND_MAX;
        if (x * x + y * y <= 1.f) {
            in_count++;
        }
    }
    return in_count;
}

int parse_arguments(char *str) {
    errno = 0;
    char *endptr;
    int s = (int) strtol(str, &endptr, 0);
    if (errno != 0 || endptr == str || *endptr != '\0') {
        fprintf(stderr, "Error: Parsing Arguments to int");
        return -1;
    }
    return s;
}
