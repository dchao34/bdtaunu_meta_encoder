#include <TFile.h>

#include <iostream>
#include <string>

#include "RootReader.h"

using namespace std;

RootReader::RootReader(
  const char *root_fname, 
  const char *root_trname) : 
  tfile(nullptr), tr(nullptr), record_index(0) {
  PrepareTreeFile(root_fname, root_trname);
  tr->SetBranchAddress("platform", &platform);
  tr->SetBranchAddress("partition", &partition);
  tr->SetBranchAddress("upperID", &upperID);
  tr->SetBranchAddress("lowerID", &lowerID);
  ClearBuffer();
}

RootReader::~RootReader() {
  if (tfile != 0) { 
    tfile->Close();
    delete tfile;
  }
}

// Responsible for opening the TFile and getting the TTree.
void RootReader::PrepareTreeFile(const char *root_fname, 
                                 const char *root_trname) {

  tfile = new TFile(root_fname, "r");
  if (tfile->IsZombie()) {
    std::cerr << "TFile* associated to \"" << root_fname;
    std::cerr << "\" is invalid." << std::endl;
    exit(EXIT_FAILURE);
  }

  tr = (TTree*) tfile->Get(root_trname);
  if (!tr) {
    std::cerr << "no TTree with name \"" << root_trname;
    std::cerr << "\" in " << root_fname << std::endl;
    exit(EXIT_FAILURE);
  }

  record_index = 0;
  total_records = tr->GetEntries();
}

// Read in the next event from the TTree. 
RootReader::Status RootReader::next_record() {
  ClearBuffer();
  if (record_index < total_records) {
    tr->GetEntry(record_index++);
    return Status::kReadSucceeded;
  } else {
    return Status::kEOF;
  }
}

string RootReader::get_eventId() const {
  return to_string(platform)
         + ":" + to_string(partition)
         + ":" + to_string(upperID)
         + "/" + to_string(lowerID);
}

void RootReader::ClearBuffer() {
  platform = -999;
  partition = -999;
  upperID = -999;
  lowerID = -999;
}
