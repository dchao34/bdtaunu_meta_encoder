#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <dirent.h>

#include <encode_meta_data/TableCache.h>
#include <encode_meta_data/RootReader.h>
#include <encode_meta_data/DataCoder.h>
#include <encode_meta_data/AssignmentCsvWriter.h>

using namespace std;

// Get all file names in an ntp directory
int get_fnames(vector<string> &fname_list, string dirname) {

  DIR *dir;
  struct dirent *ent;

  // open directory
  if ((dir = opendir(dirname.c_str())) == NULL) return 1;

  // print all files and directories in the given folder. 
  while ((ent = readdir(dir)) != NULL) {
    string fname(ent->d_name);
    if (fname == "." || fname == "..") continue;
    fname_list.push_back(dirname + "/" + fname);
  }
  closedir(dir);
  return 0;
}

/** 
 *  @brief
 *  Usage: ./code_bdtaunu INPUT_BASE_DIR OUTPUT_FNAME DATA_LABEL RUN
 *
 *  @detail
 *  Input: 
 *  + Pre-assigned event ID's: These are .csv files, separately for
 *    generic and signal MC events. 
 *  + Event weights: This is a .csv file for event weights, tabulated 
 *    for the different data sources and data labels. 
 *  + Event record location: The event records are stored as ROOT files; 
 *    they have been generated from BtaTupleMaker at SLAC. To specificy 
 *    their location to this program, one provides the following:
 *      +# Base directory: This is the directory that contains the ntuples
 *         for the various data sources and data labels. In particular, it 
 *         consists only of subdirecties of the form:
 *
 *         {pr|sp}{DATA_LABEL}r{RUN}
 *
 *      +# Data label: This is either On/Off peak or the SP mode number. 
 *         See README.md for the data label coding. 
 *      +# Run: An integer in [1, 6]. 
 *
 *  Output:
 *  + Newly assigned event ID's: This is a .csv file. In particular, 
 *    for each event in the event records (ROOT files), add a row in the 
 *    new .csv file if it is not already a row in the pre-asssigned .csv 
 *    files. Each row is in the same format as the pre-assigned .csv file. 
 */

//! Print usage message.
void print_usage() {
  cout << "Usage: ./code_bdtaunu ";
  cout << "INPUT_BASE_DIR OUTPUT_FNAME DATA_LABEL RUN" << endl;
}

int main(int argc, char **argv) {

  // Command line parsing.
  if (argc != 5) { print_usage(); return EXIT_FAILURE; }
  string base_dirname = string(argv[1]);
  string out_fname = string(argv[2]);
  int data_label = atoi(argv[3]);
  int run = atoi(argv[4]);

  // Get a list of root files in the designated ntp directory
  string sprun = "sp" + to_string(data_label) + "r" + to_string(run);
  string dirname = base_dirname + "/" + sprun + "/" + "root";
  vector<string> fname_list;
  if (get_fnames(fname_list, dirname)) {
    perror(""); print_usage();
    return EXIT_FAILURE;
  } 

  // Cache pre-assigned event ID's as well as event weights.
  TableCache cache;
  cache.cache_events("../../cached/generic_ml_assignment.csv");
  cache.cache_event_weights("../../cached/event_weights.csv");

  // Construct a DataCoder to encode newly encountered events.
  DataCoder coder;

  // New assignment file to write
  AssignmentCsvWriter output(out_fname);

  for (auto fname : fname_list) {
    cout << "."; cout.flush();

    RootReader reader(fname.c_str());
    while (reader.next_record() != RootReader::Status::kEOF) {
      if (cache.is_cached_event(reader.get_eventId())) continue;
      output.set_event_id(reader.get_eventId());
      output.set_data_source(coder.CodeDataSource(data_label));
      output.set_data_label(coder.CodeDataLabel(data_label));
      output.set_ml_sample(coder.AssignMLSample(data_label));
      output.set_division(coder.AssignDivision());
      output.set_run(coder.CodeRun(run));
      output.set_event_weight(cache.get_event_weight(data_label, run));
      output.write();
    }
  }
  cout << endl;

  return 0;
}
