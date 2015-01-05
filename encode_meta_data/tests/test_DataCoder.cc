#include <TFile.h>
#include <TTree.h>

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include <encode_meta_data/DataCoder.h>

using namespace std;

void init_ml_counts(map<int, int> &ml) {
  ml.clear();
  ml[-10] = 0;
  ml[-1] = 0;
  ml[0] = 0;
  ml[1] = 0;
  ml[2] = 0;
  ml[3] = 0;
  ml[4] = 0;
}

void init_div_counts(map<int, int> &div) {
  div.clear();
  div[-1] = 0;
  div[1] = 0;
  div[2] = 0;
  div[3] = 0;
  div[4] = 0;
  div[5] = 0;
  div[6] = 0;
  div[7] = 0;
  div[8] = 0;
  div[9] = 0;
  div[10] = 0;
}

int main() {

  map<int, int> ml, div;
  double sum;
  DataCoder *c = nullptr;

  cout << endl;

  cout << "Test 1: Default construction. " << endl;
  cout << "The next line should have exactly the ratio 0:1:0:0:0. " << endl;
  init_ml_counts(ml);
  c = new DataCoder;
  for (int i = 0; i < 10000; i++) {
    int ml_sample = static_cast<int>(c->AssignMLSample(998));
    ml[ml_sample] += 1;
    ml_sample = static_cast<int>(c->AssignMLSample(11445));
    ml[ml_sample] += 1;
    ml_sample = static_cast<int>(c->AssignMLSample(1237));
    ml[ml_sample] += 1;
  }
  sum = 0; for (auto p : ml) { sum += p.second; }
  for (auto p : ml) {
    cout << p.first << ":" << p.second / sum << " ";
  }
  cout << endl;
  delete c;
  cout << endl;

  cout << "Test 2: Changing ML sample ratio. " << endl;
  cout << "The next line should have roughly the ratio 0:1:3:1:1. " << endl;
  init_ml_counts(ml);
  c = new DataCoder{0, 1, 3, 1, 1};
  for (int i = 0; i < 10000; i++) {
    int ml_sample = static_cast<int>(c->AssignMLSample(998));
    ml[ml_sample] += 1;
    ml_sample = static_cast<int>(c->AssignMLSample(11445));
    ml[ml_sample] += 1;
    ml_sample = static_cast<int>(c->AssignMLSample(1237));
    ml[ml_sample] += 1;
  }
  sum = 0; for (auto p : ml) { sum += p.second; }
  for (auto p : ml) {
    cout << p.first << ":" << p.second / sum << " ";
  }
  cout << endl;
  delete c;
  cout << endl;

  cout << "The next line should have roughly the ratio 0:0:3:1:0. " << endl;
  init_ml_counts(ml);
  c = new DataCoder{0, 0, 3, 1, 0};
  for (int i = 0; i < 10000; i++) {
    int ml_sample = static_cast<int>(c->AssignMLSample(998));
    ml[ml_sample] += 1;
    ml_sample = static_cast<int>(c->AssignMLSample(11445));
    ml[ml_sample] += 1;
    ml_sample = static_cast<int>(c->AssignMLSample(1237));
    ml[ml_sample] += 1;
  }
  sum = 0; for (auto p : ml) { sum += p.second; }
  for (auto p : ml) {
    cout << p.first << ":" << p.second / sum << " ";
  }
  cout << endl;
  delete c;
  cout << endl;

  cout << "Test 3: Division assignment. " << endl;
  cout << "The next line should have roughly the ratio 0:1:1:...:1" << endl;
  init_ml_counts(div);
  c = new DataCoder;
  for (int i = 0; i < 10000; i++) {
    int division = static_cast<int>(c->AssignDivision());
    div[division] += 1;
  }
  sum = 0; for (auto p : div) { sum += p.second; }
  for (auto p : div) {
    cout << p.first << ":" << p.second / sum << " ";
  }
  cout << endl;
  delete c;
  cout << endl;

  cout << "Test 4: DataLabel test. " << endl;
  cout << "The numbers on either side of the colon should agree for each line:" << endl;
  c = new DataCoder;
  cout << -1 << " : " << static_cast<int>(c->CodeDataLabel(11440)) << endl;
  cout << 0 << " : " << static_cast<int>(c->CodeDataLabel(0)) << endl;
  cout << 1 << " : " << static_cast<int>(c->CodeDataLabel(1)) << endl;
  cout << 998 << " : " << static_cast<int>(c->CodeDataLabel(998)) << endl;
  cout << 1237 << " : " << static_cast<int>(c->CodeDataLabel(1237)) << endl;
  cout << 11444 << " : " << static_cast<int>(c->CodeDataLabel(11444)) << endl;
  cout << 11446 << " : " << static_cast<int>(c->CodeDataLabel(11446)) << endl;
  delete c;
  cout << endl;

  cout << "Test 5: DataSource test. " << endl;
  cout << "The first line must be all 0's. " << endl;
  cout << "The second line must be all 3's. " << endl;
  cout << "The third line must be all 1's. " << endl;
  cout << "This is followed by a warning line and a -1." << endl; 
  c = new DataCoder;
  cout << static_cast<int>(c->CodeDataSource(0)) << " ";
  cout << static_cast<int>(c->CodeDataSource(1)) << " " << endl;
  cout << static_cast<int>(c->CodeDataSource(998)) << " ";
  cout << static_cast<int>(c->CodeDataSource(1005)) << " ";
  cout << static_cast<int>(c->CodeDataSource(1235)) << " ";
  cout << static_cast<int>(c->CodeDataSource(1237)) << " " << endl;
  cout << static_cast<int>(c->CodeDataSource(11444)) << " ";
  cout << static_cast<int>(c->CodeDataSource(11445)) << " " << endl;
  cout << static_cast<int>(c->CodeDataSource(11440)) << endl;
  delete c;
  cout << endl;

  cout << "Test 5: RunCode test. " << endl;
  cout << "The next line should be: -1 1 2 3 4 5 6. " << endl;
  c = new DataCoder;
  cout << static_cast<int>(c->CodeRun(0)) << " ";
  cout << static_cast<int>(c->CodeRun(1)) << " ";
  cout << static_cast<int>(c->CodeRun(2)) << " ";
  cout << static_cast<int>(c->CodeRun(3)) << " ";
  cout << static_cast<int>(c->CodeRun(4)) << " ";
  cout << static_cast<int>(c->CodeRun(5)) << " ";
  cout << static_cast<int>(c->CodeRun(6)) << endl;
  delete c;
  cout << endl;

  return 0;
}
