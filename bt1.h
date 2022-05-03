#pragma once

typedef struct activations {
  int name;
  int activation;
} activations;

typedef struct edge {
  int name;
  int weight;
  struct edge *next;
} edge;

typedef struct node {
  int name;
  edge **visionsubnodehead;
  edge *visionsubnodetail;
  
  edge **audiosubnodehead;
  edge *audiosubnodetail;
  
  edge **motionsubnodehead;
  edge *motionsubnodetail;
} node;

typedef struct Queue {
    int front, size;
    unsigned capacity;
    activations* array;
} Queue;

char* concatenate(char *destination, char *source, int flag);


Queue* createQueue(unsigned capacity);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, int item,int weight);
int dequeue(Queue* queue);
int front(Queue* queue);
int rear(Queue* queue);
void display(Queue* queue);


void swap(activations* a, activations* b);
int partition(activations* arr, int l, int h);
void quickSortIterative(activations* arr, int l, int h);
void printArr(activations* arr, int n);


int binarySearch(activations* arr, int l, int r, int x);

int abs(int num);
activations* signalprocess(node** ramlist, Queue* Q, Queue* Qout, activations* input);

