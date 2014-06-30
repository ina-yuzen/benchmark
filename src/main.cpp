#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

extern "C" {
  extern long concat_using_strcat();
  extern long concat_using_memmove();
  extern long concat_using_strcat_without_malloc();
  extern long concat_using_memmove_without_malloc();
  extern long concat_using_memmove_without_strlen();
}

void print_result(int times, long* array, const char* label) {
  printf("** concat using %s **\n", label);
  long sum = 0;
  for (int i = 0; i < times; i++) {
    sum += array[i];
  }
  double average = (double) sum / times;

  sum = 0;
  for (int i = 0; i < times; i++) {
    sum += (array[i] - average) * (array[i] - average);
  }
  double sd = sqrt((double) sum / times);

  printf("Average: \t%lf\n", average);
  printf("Standard deviation: \t%lf\n", sd);
  printf("Max: \t%ld\n", array[times - 1]);
  printf("Min: \t%ld\n", array[0]);
  printf("Median: \t%lf\n", (times % 2 == 0 ? (array[times / 2] + array[times / 2 - 1]) / 2.0 : array[times/2]));
}

int main() {
  int times = 100;
  long strcat[times];
  long memmove[times];
  long strcat_wm[times];
  long memmove_wm[times];
  long memmove_ws[times];

  printf("Try %d times for each way...\n", times);

  for (int i = 0; i < times; i++) {
    printf("Processing %d times", i);
    fflush(stdout);
    strcat[i] = concat_using_strcat();
    memmove[i] = concat_using_memmove();
    strcat_wm[i] = concat_using_strcat_without_malloc();
    memmove_wm[i] = concat_using_memmove_without_malloc();
    memmove_ws[i] = concat_using_memmove_without_strlen();
    printf("\033[2K\r");
  }

  sort(strcat, strcat + times);
  sort(memmove, memmove + times);
  sort(strcat_wm, strcat_wm + times);
  sort(memmove_wm, memmove_wm + times);
  sort(memmove_ws, memmove_ws + times);

  puts("Done. Results are in micro seconds.\n");

  print_result(times, strcat, "strcat()");
  print_result(times, memmove, "memmove()");
  print_result(times, strcat_wm, "strcat() without memory allocation");
  print_result(times, memmove_wm, "memmove() without memory allocation");
  print_result(times, memmove_ws, "memmove() without memory allocation nor count by strlen()");

  return 0;
}
