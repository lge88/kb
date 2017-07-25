// #include <iostream>
#include <cstdio>
#include <pthread.h>

using namespace std;

void* f(void* x) {
  int i = *static_cast<int *>(x);
  printf("hello %d\n", i);
  pthread_exit(nullptr);
}

int main() {
  // cout << "hello\n";
  const static int data[2] = { 0, 1 };
  pthread_t t1, t2;

  pthread_create(&t1, nullptr, f, (void*)&data[0]);
  pthread_create(&t2, nullptr, f, (void*)&data[1]);

  pthread_join(t1, nullptr);
  pthread_join(t2, nullptr);
}
