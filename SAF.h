#include "DSP.h"

template <int order, int filterOrder = order, typename format = unsigned short>
Signal<order - filterOrder + 1, double>
SAFAverage(const Signal<order, format> &s) {
  Signal<order - filterOrder + 1, double> result;
  for(int i = 0; i < order - filterOrder + 1; i++) {
    int sum = 0;
    for(int j = 0; j < filterOrder; j++) {
      sum += s.sample[i + j];
    }
    result.sample[i] = double(sum) / filterOrder;
  }
  return result;
}
