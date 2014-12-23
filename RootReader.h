#include <TFile.h>
#include <TTree.h>

/**
 * @brief
 * Class to read ROOT files. It scans for just the event ID. 
 *
 * @detail
 * Overview
 * --------
 * This class is based on the one written in bta_tuple_reader. 
 * The ROOT files it reads are the same as the ones over there; 
 * in particular, BtaTupleMaker output generated for the BDtaunu 
 * analysis. 
 *
 * The difference is that it's stripped down to extract only 
 * eventID's.
 *
 * Usage Example
 * -------------
 *  
 *     // Open a ROOT file for reading
 *     RootReader reader("sp1235r1/root/1.root");
 *
 *     // Loop through each event and extract the event ID
 *     string event_id;
 *     while (reader.next() != RootReader::kEOF) {
 *       event_id = reader.get_eventId();
 *     }
 */
class RootReader {

  public:

    //! Reader status codes
    enum class Status {
      kReadSucceeded = 0,
      kEOF = 1,
    };

    //! Constructor with specified root file name and TTree name. 
    RootReader(const char *root_fname, const char *root_trname = "ntp1");

    //! Read in the next event from the TTree. 
    Status next_record();

    //! Babar event Id. 
    std::string get_eventId() const;

    //! Default constructor. 
    RootReader() = default;

    //! Destructor
    ~RootReader();

  private:

    // Buffer elements 
    // ---------------
    int platform, partition, upperID, lowerID;

    // File Meta Data
    // --------------
    TFile *tfile = nullptr;
    TTree *tr = nullptr;
    int record_index = 0;
    int total_records = 0;

    // Helper functions
    // ----------------
    void PrepareTreeFile(const char *root_fname, const char *root_trname);
    void ClearBuffer();
};
