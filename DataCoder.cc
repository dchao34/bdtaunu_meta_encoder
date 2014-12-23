#include <string>
#include <numeric>
#include <initializer_list>
#include <iostream>
#include <cassert>

#include "DataCoder.h"

using namespace std;

// Default constructor. Assign all `MLSampleCode` to `unassigned`. 
// This is done by leaving `ml_intervals` empty. 
// The division assignment is uniform over all divisions.
DataCoder::DataCoder() : 
  rand(static_cast<int>(DivisionCode::div1), 
       static_cast<int>(DivisionCode::div10), 
       0.0, 1.0) {
}

// Manual constructor. The `ml_ratios` are specified in the order 
// { `unassigned` : `explore` : `train` : `validate` : `test` }
// 
// This information is transformed and stored into `ml_intervals`. 
// This list is arranged such that a randomly generated real number
// in the interval [0, 1) determines the assigned `MLSampleCode` in 
// the following way:
//
// Let s be such a random number. Assign to the category
// + `unassigned` if ml_intervals[0] <= s < ml_intervals[1]
// + `explore` if ml_intervals[1] <= s < ml_intervals[2]
// + `train` if ml_intervals[2] <= s < ml_intervals[3]
// + `validate` if ml_intervals[3] <= s < ml_intervals[4]
// + `test` if ml_intervals[4] <= s
//
// The division assignment is uniform over all divisions.
DataCoder::DataCoder(initializer_list<double> ml_ratios) : 
  rand(static_cast<int>(DivisionCode::div1), 
       static_cast<int>(DivisionCode::div10), 
       0.0, 1.0) {

  // If ml_ratios is empty, leave ml_intervals empty so everything
  // gets assigned to `unassigned`. 
  if (ml_ratios.size() != 0) {

    // Make sure there is a ratio specified for each sample. 
    assert(ml_ratios.size() == 5);

    // Force the first element of ml_intervals to be 0.0: 
    // ml_intervals[0] = 0.0
    ml_intervals.push_back(0.0);

    // Subsequent elements are just the normalized cumulative sum of 
    // the ratios. In particular, for 0 < i < 5,
    //
    // ml_intevals[i] = Cumulative sum of ml_ratio from element 0 up to i, 
    // normalized by the sum of of all elements of ml_ratio. 
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

// `DataSourceCode` assignment method. 
// Implicit assumptions:
// + All available Signal MC have already been assigned. Feeding such a 
//   label generates a warning message. This needs to be changed if 
//   more signal MC is made available. 
// + Assume all generic MC to be newly encountered. Modify this function
//   if this is no longer valid. 
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

// Assigns `MLSampleCode` based on a randomly generated real number 
// in the interval [0, 1). 
//
// Let s be such a random number. Assign to the category
// + `unassigned` if ml_intervals[0] <= s < ml_intervals[1]
// + `explore` if ml_intervals[1] <= s < ml_intervals[2]
// + `train` if ml_intervals[2] <= s < ml_intervals[3]
// + `validate` if ml_intervals[3] <= s < ml_intervals[4]
// + `test` if ml_intervals[4] <= s
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

// Assigns `DivisionCode` uniformly over all available division. 
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

// Assigns `DataLabelCode`. Simply translate `data_label`. 
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

// Assigns `DataLabelCode`. Simply translate `run`. 
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
