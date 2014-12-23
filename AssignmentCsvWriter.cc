#include <string>

#include "AssignmentCsvWriter.h"

using namespace std;

AssignmentCsvWriter::AssignmentCsvWriter(string fname) {
  out.open(fname.c_str(), ofstream::out);
  out << get_title_line() << endl;
}

AssignmentCsvWriter::~AssignmentCsvWriter() {
  out.close();
}

string AssignmentCsvWriter::get_title_line() const {
  string s;
  s += "event_id"; s+= "|";
  s += "data_source"; s+= "|";
  s += "data_label"; s+= "|";
  s += "ml_sample"; s+= "|";
  s += "division"; s+= "|";
  s += "run"; s+= "|";
  s += "event_weight";
  return s;
}

void AssignmentCsvWriter::write() {
  out << event_id << "|";
  out << static_cast<int>(data_source) << "|";
  out << static_cast<int>(data_label) << "|";
  out << static_cast<int>(ml_sample) << "|";
  out << static_cast<int>(division) << "|";
  out << static_cast<int>(run) << "|";
  out << event_weight << endl;
}
