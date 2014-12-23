#ifndef __DATACODER_H__
#define __DATACODER_H__

#include <vector>
#include <string>
#include <initializer_list>

#include "DataCodeDef.h"
#include "RandomNumbers.h"

class DataCoder {
  public:
    DataCoder();
    DataCoder(int div_low, int div_high,
              std::initializer_list<double> ml_ratios);
    ~DataCoder();

    DataSourceCode CodeDataSource(int data_label) const;
    DataLabelCode CodeDataLabel(int data_label) const;
    RunCode CodeRun(int run) const;
    MLSampleCode AssignMLSample(int data_label);
    DivisionCode AssignDivision();

    DataSourceCode CodeDataSource(const std::string &data_label) const;
    DataLabelCode CodeDataLabel(const std::string &data_label) const;
    RunCode CodeRun(const std::string &run) const;
    MLSampleCode AssignMLSample(const std::string &data_label);

  private:
    RandomNumbers rand;
    std::vector<double> ml_intervals;
};

#endif
