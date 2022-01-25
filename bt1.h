#pragma once

struct activations {
  int name;
  int activation;
};

struct edge {
  int name;
  int weight;
  struct edge *next;
};

struct node {
  int name;
  struct edge **visionsubnodehead;
  struct edge *visionsubnodetail;
  
  struct edge **audiosubnodehead;
  struct edge *audiosubnodetail;
  
  struct edge **motionsubnodehead;
  struct edge *motionsubnodetail;
};

struct Queue {
    int front, size;
    unsigned capacity;
    struct activations* array;
};

char* concatenate(char *destination, char *source, int flag);


struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, int item,int weight);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);
int rear(struct Queue* queue);
void display(struct Queue* queue);


void swap(struct activations* a, struct activations* b);
int partition(struct activations* arr, int l, int h);
void quickSortIterative(struct activations* arr, int l, int h);
void printArr(struct activations* arr, int n);


int binarySearch(struct activations* arr, int l, int r, int x);

int abs(int num);
struct activations* signalprocess(struct node** ramlist, struct Queue* Q, struct Queue* Qout, struct activations* input);

/*
This is Bidugu Rahul. 20MCA1466, 20MCA3B. My external viva schedule is clashing with
my insternship induction session.

External viva schedule 		 18/12/2021
Internship induction session 18/12/2021
*/
