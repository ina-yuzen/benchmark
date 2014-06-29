#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

int COUNT = 100000;

long concat_using_strcat() {
  struct timeval a, b;
  char* k = (char*)malloc(6);
  strcpy(k, "abcde");
  int i;

  gettimeofday(&a, NULL);
  for (i = 0; i < COUNT; i++) {
    char* newk = (char*) realloc(k, (strlen(k) + 6) * sizeof(char));
    strcat(newk, "abcde");
    k = newk;
  }
  gettimeofday(&b, NULL);

  return (b.tv_sec * 1e6 + b.tv_usec) - (a.tv_sec * 1e6 + a.tv_usec);
}

long concat_using_memmove() {
  struct timeval a, b;
  char* k = (char*)malloc(6);
  strcpy(k, "abcde");
  int i;

  gettimeofday(&a, NULL);
  for (i = 0; i < COUNT; i++) {
    int len = strlen(k);
    char* newk = (char*) realloc(k, len + 6);
    memmove(newk + len, "abcde", 6);
    k = newk;
  }
  gettimeofday(&b, NULL);
  
  return (b.tv_sec * 1e6 + b.tv_usec) - (a.tv_sec * 1e6 + a.tv_usec);
}

long concat_using_strcat_without_malloc() {
  struct timeval a, b;
  char k[5 * COUNT + 1];
  strcpy(k, "abcde");
  int i;

  gettimeofday(&a, NULL);
  for (i = 0; i < COUNT; i++) {
    strcat(k, "abcde");
  }
  gettimeofday(&b, NULL);

  return (b.tv_sec * 1e6 + b.tv_usec) - (a.tv_sec * 1e6 + a.tv_usec);
}

long concat_using_memmove_without_malloc() {
  struct timeval a, b;
  char k[5 * COUNT + 1];
  strcpy(k, "abcde");
  int i;

  gettimeofday(&a, NULL);
  for (i = 0; i < COUNT; i++) {
    int len = strlen(k);
    memmove(k + len, "abcde", 6);
  }
  gettimeofday(&b, NULL);
  
  return (b.tv_sec * 1e6 + b.tv_usec) - (a.tv_sec * 1e6 + a.tv_usec);
}

long concat_using_memmove_without_strlen() {
  struct timeval a, b;
  char k[5 * COUNT + 1];
  strcpy(k, "abcde");
  int i;

  gettimeofday(&a, NULL);
  for (i = 0; i < COUNT; i++) {
    int len = (i + 1) * 5;
    memmove(k + len, "abcde", 6);
  }
  gettimeofday(&b, NULL);
  
  return (b.tv_sec * 1e6 + b.tv_usec) - (a.tv_sec * 1e6 + a.tv_usec);
}

long concat_using_sprintf() {
  struct timeval a, b;
  char* k = (char*)malloc(6);
  strcpy(k, "abcde");
  int i;

  gettimeofday(&a, NULL);
  for (i = 0; i < COUNT; i++) {
    char* newk = (char*) realloc(k, strlen(k) + 6);
    sprintf(newk, "%s%s", k, "abcde");
    k = newk;
  }
  gettimeofday(&b, NULL);

  return (b.tv_sec * 1e6 + b.tv_usec) - (a.tv_sec * 1e6 + a.tv_usec);
}
