#ifndef __DATACODEDEF_H__
#define __DATACODEDEF_H__

//! Machine learning sample codes
enum class MLSampleCode {
  null = -10,              /*!< Undefined */
  unassigned = -1,        /*!< To be assigned. */
  detector = 0,           /*!< Detector data. */ 
  explore = 1,            /*!< Sample for data exploration. */ 
  train = 2,              /*!< Training sample. */
  validate = 3,           /*!< Validation sample. */
  test = 4,               /*!< Testing sample. */ 
};

//! Data source codes. 
enum class DataSourceCode {
  null = -1,                  /*!< Undefined */
  detector = 0,               /*!< Detector data. */
  signal1 = 1,                /*!< Signal MC. Batch 1. */
  generic1 = 2,               /*!< Generic MC. Batch 1. */
  generic2 = 3,               /*!< Generic MC. Batch 2. */
};

//! Data label codes. 
enum class DataLabelCode {
  null = -1,                  /*!< Undefined */
  off_peak = 0,               /*!< Off-peak detector data. */
  on_peak = 1,                /*!< On-peak detector data. */
  uds = 998,                  /*!< SP mode 998. uds. */
  ccbar = 1005,               /*!< SP mode 1005. ccbar. */
  BpBm = 1235,                /*!< SP mode 1235. BpBm. */
  B0B0bar = 1237,             /*!< SP mode 1237. B0B0bar. */
  tau = 3429,                 /*!< SP mode 3429. tau+tau-. */
  B0_DlDtau_had = 11444,      /*!< SP mode 11444. */
  B0_DlDstau_had = 11445,      /*!< SP mode 11445. */
  Bp_DlDtau_had = 11446,      /*!< SP mode 11446. */
  Bp_DlDstau_had = 11447,      /*!< SP mode 11447. */
};

//! Run codes.
enum class RunCode {
  null = -1, 
  run1 = 1,
  run2 = 2,
  run3 = 3,
  run4 = 4,
  run5 = 5,
  run6 = 6,
};

//! Data division codes.
enum class DivisionCode {
  null = -1, 
  div1 = 1,
  div2 = 2,
  div3 = 3,
  div4 = 4,
  div5 = 5,
  div6 = 6,
  div7 = 7,
  div8 = 8,
  div9 = 9,
  div10 = 10,
};

#endif
