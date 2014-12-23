#include <string>
#include <numeric>
#include <initializer_list>
#include <iostream>
#include <cassert>

#include "DataCoder.h"

using namespace std;

DataCoder::DataCoder() : 
  rand(1, 10, 0.0, 1.0) {
}

DataCoder::DataCoder(
  int div_low, int div_high, 
  initializer_list<double> ml_ratios) : 
  rand(div_low, div_high, 0.0, 1.0) {

  if (ml_ratios.size() != 0) {

    assert(ml_ratios.size() == 5);

    ml_intervals.push_back(0.0);

    auto it = ml_ratios.begin();
    auto end = ml_ratios.end() - 1;

    double interval = 0;
    double norm = accumulate(ml_ratios.begin(), ml_ratios.end(), 0.0);

    while (it != end) {
      interval += *it;
      ml_intervals.push_back(interval / norm);
      ++it;
    }

  }
}

DataCoder::~DataCoder() {
}

DataSourceCode DataCoder::CodeDataSource(int data_label) const {
  switch (data_label) {
    case 0:
    case 1:
      return DataSourceCode::detector;
      break;
    case 998:
    case 1005:
    case 1235:
    case 1237:
      return DataSourceCode::generic2;
      break;
    default:
      cerr << endl;
      cerr << "(WARNING) CodeDataSoure: ";
      cerr << "Encountered unexpected data_label "; 
      cerr << data_label << endl;
      cerr << endl;
      return DataSourceCode::null;
  }
}

DataSourceCode DataCoder::CodeDataSource(const string &data_label) const {
  return CodeDataSource(stoi(data_label));
}

MLSampleCode DataCoder::AssignMLSample(int data_label) {
  switch (data_label) {
    case 0:
    case 1:
      return MLSampleCode::detector;
      break;
    default:
      if (ml_intervals.empty()) {
        return MLSampleCode::unassigned;
      } else {
        double s = rand.generate_uniform_real();
        if (ml_intervals[0] <= s && s < ml_intervals[1]) {
          return MLSampleCode::unassigned;
        } else if (ml_intervals[1] <= s && s < ml_intervals[2]) {
          return MLSampleCode::explore;
        } else if (ml_intervals[2] <= s && s < ml_intervals[3]) {
          return MLSampleCode::train;
        } else if (ml_intervals[3] <= s && s < ml_intervals[4]) {
          return MLSampleCode::validate;
        } else if (ml_intervals[4] <= s) {
          return MLSampleCode::test;
        } else {
          return MLSampleCode::null;
        }
      }
  }
}

MLSampleCode DataCoder::AssignMLSample(const string &data_label) {
  return AssignMLSample(stoi(data_label));
}

DivisionCode DataCoder::AssignDivision() {
  int i = rand.generate_uniform_integer();
  switch (i) {
    case 1:
      return DivisionCode::div1;
      break;
    case 2:
      return DivisionCode::div2;
      break;
    case 3:
      return DivisionCode::div3;
      break;
    case 4:
      return DivisionCode::div4;
      break;
    case 5:
      return DivisionCode::div5;
      break;
    case 6:
      return DivisionCode::div6;
      break;
    case 7:
      return DivisionCode::div7;
      break;
    case 8:
      return DivisionCode::div8;
      break;
    case 9:
      return DivisionCode::div9;
      break;
    case 10:
      return DivisionCode::div10;
      break;
    default:
      cerr << endl;
      cerr << "(WARNING) AssignDivision: ";
      cerr << "Encountered unexpected division assignment "; 
      cerr << i;
      cerr << endl;
      return DivisionCode::null;
  }
}

DataLabelCode DataCoder::CodeDataLabel(int data_label) const {
  switch (data_label) {
    case 0:
      return DataLabelCode::off_peak;
      break;
    case 1:
      return DataLabelCode::on_peak;
      break;
    case 998:
      return DataLabelCode::uds;
      break;
    case 1005:
      return DataLabelCode::ccbar;
      break;
    case 1235:
      return DataLabelCode::BpBm;
      break;
    case 1237:
      return DataLabelCode::B0B0bar;
      break;
    case 3429:
      return DataLabelCode::tau;
      break;
    case 11444:
      return DataLabelCode::B0_DlDtau_had;
      break;
    case 11445:
      return DataLabelCode::B0_DlDstau_had;
      break;
    case 11446:
      return DataLabelCode::Bp_DlDtau_had;
      break;
    case 11447:
      return DataLabelCode::Bp_DlDstau_had;
      break;
    default:
      return DataLabelCode::null;
  }
}

DataLabelCode DataCoder::CodeDataLabel(const string &data_label) const {
  return CodeDataLabel(stoi(data_label));
}

RunCode DataCoder::CodeRun(int run) const {
  switch (run) {
    case 1:
      return RunCode::run1;
      break;
    case 2:
      return RunCode::run2;
      break;
    case 3:
      return RunCode::run3;
      break;
    case 4:
      return RunCode::run4;
      break;
    case 5:
      return RunCode::run5;
      break;
    case 6:
      return RunCode::run6;
      break;
    default:
      return RunCode::null;
  }
}

RunCode DataCoder::CodeRun(const string &run) const {
  return CodeRun(stoi(run));
}
