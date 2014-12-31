#ifndef __TABLECACHE_H_
#define __TABLECACHE_H_

#include <string>
#include <map>
#include <set>

/**
 * @brief
 * Class used to cache pre-assigned events as well as their weights.
 *
 * @detail
 * This class reads in the following pre-determined data tables stored
 * in .csv files:
 *
 * + Preassigned event ID's: This is a .csv file such that the first
 *   row is the title line and each subsequent row corresponds to an 
 *   event that has already been assigned a data sample. The format, 
 *   which is described in title line, is:
 *
 *       event_id|data_source|data_label|ml_sample|division|run|event_weight
 *
 * + Event weights: This is a .csv file such that the first is the title
 *   line and each subsequent row saves the event weight corresponding to
 *   an event from run `run` of type `data_label`. The format is:
 *
 *       data_label|run|weight
 *
 * Usage Example
 * -------------
 *
 *     // Default construction. 
 *     TableCache cache;
 *
 *     // Read in the .csv files 
 *     cache.cache_events("preassigned_sigmc_events.csv");
 *     cache.cache_events("preassigned_generic_events.csv");
 *     cache.cache_event_weights("event_weights.csv");
 *
 *     // Check if an event with event ID "31415926" is already assigned
 *     bool is_preassigned = cache.is_cached_event("31415926");
 *
 *     // Get the `ml_sample` and `division` assignment of that event
 *     string ml_sample = cache.get_ml_sample("31415926");
 *     string division = cache.get_division("31415926");
 *
 *     // Look up the event weight for events from run 3 of sp mode 1235
 *     double wgt = get_event_weight(1235, 3);
 *
 */
class TableCache {
  public:

    TableCache() = default;
    ~TableCache() = default;

    //! Cache pre-assigned events from a file whose path is in fname.
    void cache_events(std::string fname);

    //! Cache event weights from a file whose path is in fname.
    void cache_event_weights(std::string fname);

    //! Check whether `event_id` is in the cache. 
    bool is_cached_event(const std::string &event_id) const;

    //! Get `ml_sample` assignment of a cached event.
    /*! Returns `ml_sample` if `event_id` is in the cache.
     *  Otherwise, return empty string. */
    std::string get_ml_sample(const std::string &event_id) const;

    //! Get `division` assignment of a cached event.
    /*! Returns `division` if `event_id` is in the cache.
     *  Otherwise, return empty string. */
    std::string get_division(const std::string &event_id) const;

    //! Look up event weight for events from run `run` of type `data_label`
    double get_event_weight(int data_label, int run) const;

  private:

    // Cached data. Data read from .csv are saved in these data structures. 
    std::set<std::string> event_cache;
    std::map<std::string, std::string> mlsample_cache;
    std::map<std::string, std::string> division_cache;
    std::map<int, double> weight_cache;

    // Hashes a `data_label`/`run` combination to a `weight_cache` key.
    int hash_weight_key(int data_label, int run) const;
};

#endif
