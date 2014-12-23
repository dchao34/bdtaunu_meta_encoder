#include <TFile.h>
#include <TTree.h>

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
