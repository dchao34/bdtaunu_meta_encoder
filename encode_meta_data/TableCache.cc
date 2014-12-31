#include <map>
#include <set>
#include <string>
#include <cassert>
#include <custom_cpp_utilities/CsvReader.h>

#include "TableCache.h"

using namespace std;
using namespace custom_cpp_utilities;

// Hash function that maps data_label and run to a key for weight_cache.
// Assume 0 <`run` < 10. Simply promote `data_label` by one digit and 
// make `run` the one's digit. 
int TableCache::hash_weight_key(int data_label, int run) const {
  return data_label * 10 + run;
}

// Cache pre-assigned event id's. The format of the table is specified 
// as follows:
// <title line>
// <record 1>
// <record 2>
// ...
// <record N>
//
// Each line is "|" delimited with this title line:
// event_id|data_source|data_label|ml_sample|division|run|event_weight
//
// All event_id's encountered in fname is saved into event_cache.
void TableCache::cache_events(string fname) {

  // Use CsvReader to stream through the table of preassigned events. 
  // See custom_cpp_utilities/CsvReader.h for its documentation.
  string event_id, ml_sample, division;
  CsvReader reader(fname.c_str(), "|");
  while (reader.next()) { 
    event_id = reader.get("event_id");
    ml_sample = reader.get("ml_sample");
    division = reader.get("division");
    auto p = event_cache.insert(event_id);
    assert(p.second);
    auto m = mlsample_cache.insert(make_pair(event_id, ml_sample));
    assert(m.second);
    auto d = division_cache.insert(make_pair(event_id, division));
    assert(d.second);
  }
  return;
}

// Cache event weights. The format of the table is specified 
// as follows:
// <title line>
// <record 1>
// <record 2>
// ...
// <record N>
//
// Each line is "|" delimited with this title line:
// data_label|run|weight
//
// All weights encountered in fname are saved into weight_cache. 
// The map has key: data_label * 10 + run, and value: weight.
void TableCache::cache_event_weights(string fname) {

  // Use CsvReader to stream through the table of preassigned events. 
  // See custom_cpp_utilities/CsvReader.h for its documentation.
  CsvReader reader(fname.c_str(), "|");
  while (reader.next()) { 

    // Assemble key
    int data_label = stoi(reader.get("data_label"));
    int run = stoi(reader.get("run"));
    int key = hash_weight_key(data_label, run);

    // Insert key, value into the map
    double value = stod(reader.get("weight"));
    auto p = weight_cache.insert(make_pair(key, value));
    assert(p.second);
  }
  return;
}

// Check if `event_id` is in `event_cache`. 
bool TableCache::is_cached_event(const string &event_id) const {
  auto it = event_cache.find(event_id);
  return (it != event_cache.end()) ? true : false;
}

// Get `ml_sample` assigned to specified `event_id`.
std::string TableCache::get_ml_sample(const string &event_id) const {
  auto it = mlsample_cache.find(event_id);
  return (it == mlsample_cache.end()) ? "" : it->second;
}

// Get `division` assigned to specified `event_id`.
std::string TableCache::get_division(const string &event_id) const {
  auto it = division_cache.find(event_id);
  return (it == division_cache.end()) ? "" : it->second;
}

// Get event weight corresponding to specified `data_label` and `run`. 
double TableCache::get_event_weight(int data_label, int run) const {
  auto it = weight_cache.find(hash_weight_key(data_label, run));
  return (it == weight_cache.end()) ? -1.0 : it->second;
}
