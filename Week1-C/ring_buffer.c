#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// Define structure of the ring buffer struct
typedef struct {
    int *buffer_array;
    int head_index;
    int tail_index;
    int capacity;
    int count;
} ringBuffer;


// OPERATIONS

// Initializes the ring buffer
ringBuffer *init(int capacity) {
    ringBuffer *buffer = malloc(sizeof(ringBuffer));       // It should also handle the NULL case but I decided to ignore that for now
    buffer->buffer_array = malloc(sizeof(int) * capacity); 
    buffer->head_index=0; 
    buffer->tail_index=0; 
    buffer->capacity=capacity;
    buffer->count=0;
    return buffer;
}

// Check is it full
int is_full(ringBuffer *buffer, int count) {
    if (buffer->count == buffer->capacity) {
        return 1;
    }
    return 0;
}

// Check is it empty
int is_empty(ringBuffer *buffer, int count) {
    if (buffer->count == 0) {
        return 1;
    }
    return 0;
}

// Write a value into the buffer
void write(ringBuffer *buffer, int data) 
{
    buffer->buffer_array[buffer->head_index] = data;

    // If full, it will overwrite previous values
    if (is_full(buffer, buffer->count)) {
        buffer->head_index = (buffer->head_index + 1) % buffer->capacity;
        buffer->tail_index = (buffer->tail_index + 1) % buffer->capacity;
    } else {
        buffer->head_index = (buffer->head_index + 1) % buffer->capacity;
        buffer->count++;
    }
}

// Read a value from the buffer
int read(ringBuffer *buffer, int *out_data)
{
    if (is_empty(buffer, buffer->count)) {
        printf("Ring buffer is empty - nothing to read.\n");
        return 0; // failure
    }
    *out_data = buffer->buffer_array[buffer->tail_index];
    buffer->tail_index = (buffer->tail_index + 1) % buffer->capacity;
    buffer->count--;
    return 1; // success;
}


#define BUFFER_CAPACITY 5
#define DATASET_SIZE 20


// TEST FUNCTIONS

// Test init
void test_init(void)
{
    ringBuffer *buffer = init(BUFFER_CAPACITY);
    assert(buffer->capacity == 5);
    assert(buffer->count == 0);
    assert(is_empty(buffer, buffer->count));
    printf("PASS: test_init\n");
    free(buffer);
}

// Test a simple write/read case
void test_write_read_basic(void)
{
    ringBuffer *buffer = init(BUFFER_CAPACITY);
    write(buffer, 55);
    int value;
    read(buffer, &value);
    assert(value == 55);
    printf("PASS: test_write_read_basic\n");
    free(buffer);
}

// Test an empty read
void test_empty_read(void) 
{
    ringBuffer *buffer = init(BUFFER_CAPACITY);
    int value;
    assert(read(buffer, &value) == 0);
    assert(is_empty(buffer, buffer->count) == 1);
    printf("PASS: test_empty_read\n");
    free(buffer);
}

// Test the is_full function
void test_is_full(void)
{
    ringBuffer *buffer = init(BUFFER_CAPACITY);
    for (int i = 0; i < BUFFER_CAPACITY; i++) {
        write(buffer, i);
    }
    assert(is_full(buffer, buffer->count) == 1);
    printf("PASS: test_is_full\n");
    free(buffer);
}

// Test the overwrite and wraparound logic
void test_overwrite(void)
{
    ringBuffer *buffer = init(BUFFER_CAPACITY);
    for (int i = 0; i < BUFFER_CAPACITY + 1; i++) {
        write(buffer, i);
    }
    int value;
    read(buffer, &value);
    assert(value == 1);
    assert(buffer->head_index == 1);
    printf("PASS: test_overwrite\n");
    free(buffer);
}


// The main function
int main(void) 
{
    // Initialize the dataset array that will store the output readings 
    int dataset_count = 0;
    int *dataset = malloc(sizeof(int) * DATASET_SIZE);
    
    // Initialize the ring buffer
    ringBuffer *buffer = init(BUFFER_CAPACITY);
    
    // Write to and read from the ring buffer
    write(buffer, 67);
    
    if (read(buffer, &dataset[dataset_count])) {
        printf("Got %d\n", dataset[dataset_count]); 
        dataset_count++;
    }

    write(buffer, 77);

    if (read(buffer, &dataset[dataset_count])) {
        printf("Got %d\n", dataset[dataset_count]); 
        dataset_count++;
    }

    if (read(buffer, &dataset[dataset_count])) {        // Buffer should be empty at this point
        printf("Got %d\n", dataset[dataset_count]); 
        dataset_count++;
    }

    write(buffer, 1);
    write(buffer, 2);
    write(buffer, 3);
    write(buffer, 4);
    write(buffer, 5);
    write(buffer, 6);

    if (read(buffer, &dataset[dataset_count])) {       // Since there were 6 writes, one overwrite should have occured
        printf("Got %d\n", dataset[dataset_count]); 
        dataset_count++;
    }

    // Print whole dataset to make sure it works
    printf("All readings in the dataset: \n");
    for (int i = 0; i < dataset_count; i++) {
        printf("%d\n", dataset[i]);
    }

    // Print the current head and tail indexes
    printf("Head index: %d, Tail index: %d\n", buffer->head_index, buffer->tail_index);

    // Run all the tests
    printf("Running all the tests...\n");
    test_init();
    test_write_read_basic();
    test_empty_read();
    test_is_full();
    test_overwrite();

    // Free memory
    free(dataset);
    free(buffer);
}


