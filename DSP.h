/** 数字信号单元
 *  模板order: 信号记忆阶数
 */
template <int order, typename format = unsigned short>
struct Signal {
  format sample[order];
  format &current = sample[order - 1];
};

/** 初始化信号单元
 */
template <int order, typename format = unsigned short>
void
DSPinit(Signal<order, format> &s) {
  memset(s.sample, 0, order * sizeof(format));
}

/** 更新信号
 */
template <int order, typename format = unsigned short>
void
DSPUpdate(Signal<order, format> &s, format sample) {
  memcpy(s.sample, s.sample + 1, (order - 1) * sizeof(format));
  s.current = sample;
}

/** 一阶微分器
 */
template <int order, typename format = unsigned short>
Signal<order - 1, format>
DSPDifferentiator(const Signal<order, format> &s) {
  Signal<order - 1, format> result;
  for(int i = 0; i < order - 1; i++) {
    result.sample[i] = s.sample[i + 1] - s.sample[i];
  }
  return result;
}

