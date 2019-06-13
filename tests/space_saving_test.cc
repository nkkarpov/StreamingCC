//
// Created by nk-karpov on 2019-05-30.
//


#include "../src/streamingcc_include/space_saving.h"

#define BOOST_TEST_MODULE ClassTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(SpaceSavingInt_Test0) {
  using streamingcc::integer::SpaceSavingInt;
  auto k = 101;
  auto val = 0.25;
  SpaceSavingInt ss(k);
  std::vector<double> f(101);
  auto total = 0.;
  for (auto j = 0; j < 100; j++) {
    ss.ProcessItem(100, val);
    total += val;
    f[100] += val;
  }
  for (auto i = 0; i < 100; ++i) {
    for (auto j = 0; j < 10; ++j) {
      ss.ProcessItem(i, val);
      total += val;
      f[i] += val;
    }
  }
  for (auto i = 0; i <= 100; ++i) {
    auto est = ss.GetEstimation(i);
    BOOST_CHECK_MESSAGE(est >= f[i], "SpaceSavingInt::GetEstimation = " << est);
    BOOST_CHECK_MESSAGE(est <= f[i] + total / k, "SpaceSavingInt::GetEstimation = " << est);
  }
};

BOOST_AUTO_TEST_CASE(SpaceSavingInt_Test1) {
  using streamingcc::integer::SpaceSavingInt;
  auto k = 101;
  auto val = 0.25;
  SpaceSavingInt ss(k);
  std::vector<double> f(101);
  auto total = 0.;
  for (auto i = 0; i < 100; ++i) {
    for (auto j = 0; j < 10; ++j) {
      ss.ProcessItem(i, val);
      total += val;
      f[i] += val;
    }
  }
  for (auto j = 0; j < 100; j++) {
    ss.ProcessItem(100, val);
    total += val;
    f[100] += val;
  }
  for (auto i = 0; i <= 100; ++i) {
    auto est = ss.GetEstimation(i);
    BOOST_CHECK_MESSAGE(est >= f[i], "SpaceSavingInt::GetEstimation = " << est);
    BOOST_CHECK_MESSAGE(est <= f[i] + total / k, "SpaceSavingInt::GetEstimation = " << est);
  }
};