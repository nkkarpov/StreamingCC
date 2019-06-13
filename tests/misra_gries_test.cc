//
// Created by nk-karpov on 2019-05-30.
//



#include "../src/streamingcc_include/misra_gries.h"

#define BOOST_TEST_MODULE ClassTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MisraGriesInt_Test0) {
  using streamingcc::integer::MisraGriesInt;
  auto k = 20;
  MisraGriesInt mg(k);
  std::vector<double> f(101);
  auto total = 0.;
  for (auto j = 0; j < 100; j++) {
    mg.ProcessItem(100, 0.5);
    total += 0.5;
    f[100] += 0.5;
  }
  for (auto i = 0; i < 100; ++i) {
    for (auto j = 0; j < 10; ++j) {
      mg.ProcessItem(i, 0.5);
      total += 0.5;
      f[i] += 0.5;
    }
  }
  for (auto i = 0; i <= 100; ++i) {
    auto est = mg.GetEstimation(i);
    BOOST_CHECK_MESSAGE(est <= f[i], "MisraGriesInt::GetEstimation = " << est);
    BOOST_CHECK_MESSAGE(est >= f[i] - total / k, "MisraGriesInt::GetEstimation = " << est);
  }
};

BOOST_AUTO_TEST_CASE(MisraGriesInt_Test1) {
  using streamingcc::integer::MisraGriesInt;
  auto k = 20;
  auto val = 0.25;
  MisraGriesInt mg(k);
  std::vector<double> f(101);
  auto total = 0.;

  for (auto i = 0; i < 100; ++i) {
    for (auto j = 0; j < 10; ++j) {
      mg.ProcessItem(i, val);
      total += val;
      f[i] += val;
    }
  }

  for (auto j = 0; j < 100; j++) {
    mg.ProcessItem(100, val);
    total += val;
    f[100] += val;
  }

  for (auto i = 0; i <= 100; ++i) {
    auto est = mg.GetEstimation(i);
    BOOST_CHECK_MESSAGE(est <= f[i], "MisraGriesInt::GetEstimation = " << est);
    BOOST_CHECK_MESSAGE(est >= f[i] - total / k, "MisraGriesInt::GetEstimation = " << est);
  }
};