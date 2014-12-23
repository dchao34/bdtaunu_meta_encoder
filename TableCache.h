#ifndef __TABLECACHE_H_
#define __TABLECACHE_H_

#include <string>
#include <map>
#include <set>

class TableCache {
  public:
    TableCache() = default;
    ~TableCache();

    void cache_events(std::string fname);
    void cache_event_weights(std::string fname);

    bool is_cached_event(const std::string &event_id) const;
    double get_event_weight(int data_label, int run) const;

  //private:
  public:
    std::set<std::string> event_cache;
    std::map<int, double> weight_cache;

    int hash_weight_key(int data_label, int run) const;
};

#endif
