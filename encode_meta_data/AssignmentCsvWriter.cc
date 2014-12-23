#include <string>

#include "AssignmentCsvWriter.h"

using namespace std;

// Open an output file stream for writing. 
AssignmentCsvWriter::AssignmentCsvWriter(string fname) {
  out.open(fname.c_str(), ofstream::out);
  out << get_title_line() << endl;
}

// Close the output file stream.
AssignmentCsvWriter::~AssignmentCsvWriter() {
  out.close();
}

// Specify the title line. 
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

// Write out a new line that is consistent with the title. 
void AssignmentCsvWriter::write() {
  out << event_id << "|";
  out << static_cast<int>(data_source) << "|";
  out << static_cast<int>(data_label) << "|";
  out << static_cast<int>(ml_sample) << "|";
  out << static_cast<int>(division) << "|";
  out << static_cast<int>(run) << "|";
  out << event_weight << endl;
}
