#ifndef __DATACODER_H__
#define __DATACODER_H__

#include <vector>
#include <string>
#include <initializer_list>

#include "DataCodeDef.h"
#include "RandomNumbers.h"

/**
 * @brief 
 * Class that generates event meta data. 
 * Please see cautionary note before proceeding. 
 *
 * @detail
 *
 * Overview
 * --------
 * This class generates meta data to events in the data set. 
 * In particular, it explicitly specifies the method in which 
 * meta data encodings are assigned.
 *
 * Please see the cautionary note before proceeding. 
 *
 * Meta data are assigned based on the following criteria:
 * + Specific characteristics of the event: These are things such 
 *   as the data origin; e.g. Is it from Monte Carlo? If so, which mode? 
 *   Is it from detector data? If so, on or off peak? 
 * + Event independent: These are often assigned randomly, independently 
 *   of any specific attributes; e.g. every event must be 
 *   assigned a data division. Machine learning sample labels are 
 *   also assigned to Monte Carlo events. 
 *
 * See `README.md` for the description of various categories of meta data.
 *
 * See `DataCoder.cc` for the specific assignment methodology. This class 
 * is intended to be extended/subclassed/modified depending on how meta 
 * data will be used. Just make sure you are careful when doing this; 
 * see the cautionary note. 
 *
 * Machine Learning Sample Assignment
 * ----------------------------------
 * By Default, all Monte Carlo samples are automatically grouped into the 
 * `unassigned` category. Any non-default assignments must be clearly 
 * documented; see cautionary note. 
 *
 * Actually, an event assigned to the `unassigned` category must not be 
 * analyzed until its purpose is clear. You should view these events as 
 * being available, but not yet ready for analysis until properly assigned. 
 *
 * The order of sample ratios specified in the constructor is 
 * "unassigned : explore : train : validate : test" 
 * any of which is a non-negative number. 
 *
 *
 * Caution! 
 * --------
 * This class is intended to be used to generate meta data for *newly*
 * encountered events. Though you can misuse this class to generate 
 * meta data for previously encountered events, you should resist the 
 * urge to do so unless you fully understand the consequences and also 
 * clearly document the changes. You risk breaking the integrity of the 
 * analysis if done cavalierly. 
 *
 * To be precise, you are free to generate meta data as much as you like
 * as long as you don't overwrite previously assigned meta data or analyze
 * data using meta data different from those that have been previously assigned.
 *
 * Usage Example
 * -------------
 *    
 *     // Construct a DataCoder. Generate ML samples in the ratio
 *     // unassigned:explore:train:validate:test = 0:1:3:1:1
 *     DataCoder coder{0, 1, 3, 1, 1};
 *
 *     // Assign a `DataSourceCode` encoding to an event with `data_label`.
 *     // Actually, `data_label` pre-extracted from the event and fed to the coder. 
 *     DataSourceCode data_source = coder.CodeDataSource(data_label);
 *
 *     // Assign a `MLSampleCode` encoding to an event with `data_label`.
 *     MLSampleCode ml_sample = coder.AssignMLSample(data_label);
 *
 *     // etc...
 *
 */
class DataCoder {
  public:

    //! Default constructor. 
    /*! Configures all machine learning assignments to `unassigned`. */
    DataCoder();

    //! Manually specify machine learning assignment ratios. 
    /*! `ml_ratios` is a 5 element initializer list with sample ordering: 
     *  { `unassigned` : `explore` : `train` : `validate` : `test` }. 
     *  Leave empty to assigne everything to `unassigned`. */
    DataCoder(std::initializer_list<double> ml_ratios);

    ~DataCoder() = default;

    //! Assign `DataSourceCode` based on `data_label`.  
    /*! Implicit assumptions:
     * + All available Signal MC have already been assigned. Feeding such a 
     *   label generates a warning message. This needs to be changed if 
     *   more signal MC is made available. 
     * + Assume all generic MC to be newly encountered. Modify this function
     *   if this is no longer valid. */
    DataSourceCode CodeDataSource(int data_label) const;

    //! Assign `DataLabelCode` based on `data_label`.  
    /*! Simply translate `data_label` to a `DataLabelCode` based on the
     *  numbering in the enum class. */
    DataLabelCode CodeDataLabel(int data_label) const;

    //! Assign `RunCode` based on `run`.  
    /*! Simply translate `run` to a `RunCode` based on the
     *  numbering in the enum class. */
    RunCode CodeRun(int run) const;

    //! Assign `MLSampleCode` based on the specified ratio and `data_label`.
    /*! For detector data, assign it to `data`. For Monte Carlo, assign 
     *  the code based on the specified sample ratios. */
    MLSampleCode AssignMLSample(int data_label);

    //! Assign `DivisionCode`. 
    /*! Simply generate a division code uniformly over all available divisions. */
    DivisionCode AssignDivision();

  private:

    // Cached random number generator
    RandomNumbers rand;

    // Stores the specified machine learning ratio, but converted into intervals 
    std::vector<double> ml_intervals;
};

#endif
