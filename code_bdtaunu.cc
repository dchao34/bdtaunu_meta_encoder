#include <TFile.h>
#include <TTree.h>

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <set>
#include <random>
#include <vector>
#include <utility>
#include <dirent.h>
#include <custom_cpp_utilities/CsvReader.h>

using namespace std;
using namespace custom_cpp_utilities;

// Print usage message.
void print_usage() {
  cout << "Usage: ./test base_dirname data_label run" << endl;
}

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

// Assemble event id.
string get_event_id(int platform, int partition, int upperID, int lowerID) {
  return to_string(platform)
         + ":" + to_string(partition)
         + ":" + to_string(upperID)
         + "/" + to_string(lowerID);
}

// Cache assigned event id's.
void cache_assigned(string fname, set<string> &s) {
  CsvReader reader(fname.c_str(), "|");
  while (reader.next()) { 
    auto p = s.insert(reader.get("event_id"));
    assert(p.second);
  }
  return;
}

// Check if an event id has already been assigned. 
bool is_assigned(const set<string> &preassigned, const string &event_id) {
  auto it = preassigned.find(event_id);
  return (it != preassigned.end()) ? true : false;
}

// Cache event weights.
void cache_weights(string fname, map<int, double> &wgt) {
  CsvReader reader(fname.c_str(), "|");
  while (reader.next()) { 
    int prefix = stoi(reader.get("data_label"));
    int suffix = stoi(reader.get("run"));
    int key = prefix * 10 + suffix;
    double value = stod(reader.get("weight"));
    auto p = wgt.insert(make_pair(key, value));
    assert(p.second);
  }
  return;
}

// Fetch event weight from cached weights. 
double fetch_weight(const map<int, double> &wgt, int data_label, int run) {
  auto it = wgt.find(data_label * 10 + run);
  return (it == wgt.end()) ? -1.0 : it->second;
}

// Deduce data source based on the data label.
int deduce_data_source(int data_label) {
  switch (data_label) {
    case 0:
    case 1:
      return 0;
      break;
    case 1237:
    case 1235:
    case 1005:
    case 998:
      return 3;
      break;
    default:
      return -1;
  }
}

// Deduce data source based on the data label.
int deduce_ml_sample(int data_label) {
  switch (data_label) {
    case 0:
    case 1:
      return 0;
      break;
    default:
      return -1;
  }
}

// Initialize random engine and division distribution
mt19937 initialize_random_engine() {
  random_device rd;
  mt19937 e(rd());
  return e;
}
uniform_int_distribution<int> initialize_div_dist() {
  uniform_int_distribution<int> uniform_dist(1, 10);
  return uniform_dist;
}

// Generate a division
int generate_division(mt19937 &e, uniform_int_distribution<int> &d) {
  return d(e);
}


// Usage: ./test base_dirname data_label run
int main(int argc, char **argv) {

  // Command line parsing.
  if (argc != 4) { print_usage(); return EXIT_FAILURE; }
  string base_dirname = string(argv[1]);
  int data_label = atoi(argv[2]);
  int run = atoi(argv[3]);

  // Get a list of root files in the designated ntp directory
  string sprun = "sp" + to_string(data_label) + "r" + to_string(run);
  string dirname = base_dirname + "/" + sprun + "/" + "root";
  vector<string> fname_list;
  if (get_fnames(fname_list, dirname)) {
    perror(""); print_usage();
    return EXIT_FAILURE;
  } 

  // Cache event ID's that have already been assigned
  set<string> preassigned;
  cache_assigned("meta/generic_ml_assignment.csv", preassigned);

  // Cache event weights
  map<int, double> event_weights;
  cache_weights("meta/event_weights.csv", event_weights);

  // Initialize random generator and division generator
  auto rand_engine = initialize_random_engine();
  auto div_dist = initialize_div_dist();

  // New assignment file to write
  ofstream out("new.csv", ofstream::out);
  out << "event_id|data_source|data_label|ml_sample|division|run|event_weight" << endl;

  for (auto fname : fname_list) {
    cout << "."; cout.flush();
    
    TFile *f = new TFile(fname.c_str(), "r");
    TTree *tr = (TTree*) f->Get("ntp1");
    int platform, partition, upperID, lowerID;
    tr->SetBranchAddress("platform", &platform);
    tr->SetBranchAddress("partition", &partition);
    tr->SetBranchAddress("upperID", &upperID);
    tr->SetBranchAddress("lowerID", &lowerID);

    int nentries = tr->GetEntries();
    for (int i = 0; i < nentries; i++) {

      tr->GetEntry(i);
      string event_id = get_event_id(platform, partition, upperID, lowerID);

      if (!is_assigned(preassigned, event_id)) {
        out << event_id << "|";
        out << deduce_data_source(data_label) << "|";
        out << data_label << "|";
        out << deduce_ml_sample(data_label) << "|";
        out << generate_division(rand_engine, div_dist) << "|";
        out << run << "|";
        out << fetch_weight(event_weights, data_label, run) << endl;
      }
    }
    f->Close();
    delete f;

  }
  cout << endl;
  out.close();

  return 0;
}
