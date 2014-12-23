#include <TFile.h>
#include <TTree.h>

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include <custom_cpp_utilities/CsvReader.h>
#include <encode_meta_data/TableCache.h>
#include <encode_meta_data/AssignmentCsvWriter.h>

using namespace std;
using namespace custom_cpp_utilities;

int main() {

  CsvReader *csv_reader;

  TableCache *cache = new TableCache;
  cout << "Preparation: Caching event weights." << endl;
  cache->cache_event_weights("cached/event_weights.csv");
  cout << "Preparation: Caching preassigned generic MC events." << endl;
  cout << "Preparation: Caching preassigned signal MC events." << endl;
  cache->cache_events("cached/generic_ml_assignment.csv");
  cache->cache_events("cached/sigmc_ml_assignment.csv");

  cout << "Test 1: Check that all preassigned events are indeed cached. " << endl;

  csv_reader = new CsvReader("cached/generic_ml_assignment.csv", "|");
  while (csv_reader->next()) {
    if (!cache->is_cached_event(csv_reader->get("event_id"))) {
      cout << "Failed" << endl;
      break;
    }
  }
  delete csv_reader;

  csv_reader = new CsvReader("cached/sigmc_ml_assignment.csv", "|");
  while (csv_reader->next()) {
    if (!cache->is_cached_event(csv_reader->get("event_id"))) {
      cout << "Failed" << endl;
      break;
    }
  }
  cout << "Passed" << endl;
  delete csv_reader;

  cout << "Test 2: Check that a few newly encountered eventID's are not cached. " << endl;
  if (cache->is_cached_event("10310") || 
      cache->is_cached_event("1002310/2310:-1") || 
      cache->is_cached_event("abcd")) {
    cout << "Failed" << endl;
  } else {
    cout << "Passed" << endl;
  }

  cout << "Test 3: Check that event weights are correctly cached. " << endl;
  cout << "There are two numbers for all but the last line. They must agree. " << endl;
  cout << "The last line should have all -1's." << endl;
  csv_reader = new CsvReader("cached/event_weights.csv", "|");
  while (csv_reader->next()) {
    int data_label = stoi(csv_reader->get("data_label"));
    int run = stoi(csv_reader->get("run"));
    double weight = stod(csv_reader->get("weight"));
    cout << weight << " " << cache->get_event_weight(data_label, run) << endl;
  }
  cout << cache->get_event_weight(11440, 1) << " ";
  cout << cache->get_event_weight(0, -1) << " ";
  cout << cache->get_event_weight(1, -1) << " ";
  cout << cache->get_event_weight(1237, 9) << " ";
  cout << cache->get_event_weight(11444, -1) << endl;
  cout << endl;

  return 0;
}
