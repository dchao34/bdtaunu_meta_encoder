#ifndef __ASSIGNMENTCSVWRITER_H__
#define __ASSIGNMENTCSVWRITER_H__

#include <fstream>
#include <string>

#include "DataCodeDef.h"

class AssignmentCsvWriter {
  public:
    AssignmentCsvWriter(std::string fname);
    ~AssignmentCsvWriter();

    void write();

    void set_event_id(const std::string &_event_id) { event_id = _event_id; }
    void set_data_source(DataSourceCode _data_source) { data_source = _data_source; }
    void set_data_label(DataLabelCode _data_label) { data_label = _data_label; }
    void set_ml_sample(MLSampleCode _ml_sample) { ml_sample = _ml_sample; }
    void set_division(DivisionCode _division) { division = _division; }
    void set_run(RunCode _run) { run = _run; }
    void set_event_weight(double _event_weight) { event_weight = _event_weight; }

  private:
    std::ofstream out;

    std::string event_id;
    DataSourceCode data_source;
    DataLabelCode data_label;
    MLSampleCode ml_sample;
    DivisionCode division;
    RunCode run;
    double event_weight;

    std::string get_title_line() const;

};

#endif
