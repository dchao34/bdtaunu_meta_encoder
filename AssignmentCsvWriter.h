#ifndef __ASSIGNMENTCSVWRITER_H__
#define __ASSIGNMENTCSVWRITER_H__

#include <fstream>
#include <string>

#include "DataCodeDef.h"

/**
 * @brief
 * Class that writes meta data for events into a .csv file. 
 *
 * @detail 
 *
 * Overview
 * --------
 * This class writes out a .csv file for the meta data assigned 
 * to an event. It takes care of the formatting so the user can focus
 * on the meta data assignment. 
 *
 * The format is the following:
 * + Row 1 is the title line. It specifies the format, and is currently
 *       event_id|data_source|data_label|ml_sample|division|run|event_weight
 * + Subsequent rows are the records themselves. Each line is a different event. 
 *
 * Usage Example
 * -------------
 *     
 *     // Construct a writer. A new file with name "new.csv" is created with
 *     // the title line inserted.
 *     AssignmentCsvWriter writer("new.csv");
 *
 *     // Assign the column entries for the next record to be written. Notice
 *     // that you are free to assign the columns in any order. 
 *     writer.set_event_id("31415926");
 *     writer.set_ml_sample(MLSampleCode::train);
 *     writer.set_data_source(DataSourceCode::generic2);
 *
 *     // writer.set_somthing(...) etc... Make sure you do assign every column
 *     // you care about. Unassigned entries will have null written in the output.  
 *
 *     // Write out a line into "new.csv" with the currently assigned column values.
 *     writer.write();
 */     
class AssignmentCsvWriter {
  public:

    //! Opens a file for writing. Its path is stored in `fname`. 
    AssignmentCsvWriter(std::string fname);
    ~AssignmentCsvWriter();

    //! Write a new record into the file based on the current cache assignments.
    void write();

    //! Set `event_id` for the record to be written next.
    void set_event_id(const std::string &_event_id) { event_id = _event_id; }

    //! Set `data_source` for the record to be written next.
    void set_data_source(DataSourceCode _data_source) { data_source = _data_source; }

    //! Set `data_label` for the record to be written next.
    void set_data_label(DataLabelCode _data_label) { data_label = _data_label; }

    //! Set `ml_sample` for the record to be written next.
    void set_ml_sample(MLSampleCode _ml_sample) { ml_sample = _ml_sample; }

    //! Set `division` for the record to be written next.
    void set_division(DivisionCode _division) { division = _division; }

    //! Set `run` for the record to be written next.
    void set_run(RunCode _run) { run = _run; }

    //! Set `event_weight` for the record to be written next.
    void set_event_weight(double _event_weight) { event_weight = _event_weight; }

  private:

    // Output file stream.
    std::ofstream out;

    // Cache for the next record to be written.
    std::string event_id;
    DataSourceCode data_source;
    DataLabelCode data_label;
    MLSampleCode ml_sample;
    DivisionCode division;
    RunCode run;
    double event_weight;

    // Get the title line. See .cc file for the specification. 
    std::string get_title_line() const;

};

#endif
