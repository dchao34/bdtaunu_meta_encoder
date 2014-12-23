#include <TFile.h>
#include <TTree.h>

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include <encode_meta_data/AssignmentCsvWriter.h>
#include <encode_meta_data/DataCodeDef.h>

using namespace std;

int main() {

  AssignmentCsvWriter writer("csv_writer_test.out");

  writer.set_event_id("abcd");
  writer.set_data_source(DataSourceCode::null);
  writer.set_data_label(DataLabelCode::ccbar);
  writer.set_ml_sample(MLSampleCode::explore);
  writer.set_division(DivisionCode::div3);
  writer.set_run(RunCode::run3);
  writer.set_event_weight(1.0);
  writer.write();

  writer.set_data_source(DataSourceCode::generic2);
  writer.set_division(DivisionCode::div4);
  writer.set_data_label(DataLabelCode::uds);
  writer.set_event_id("31023:1920/-1");
  writer.set_ml_sample(MLSampleCode::train);
  writer.set_event_weight(-10.412);
  writer.set_run(RunCode::run6);
  writer.write();

  cout << "Wrote \"csv_writer_test.out\"" << endl;

  return 0;
}
