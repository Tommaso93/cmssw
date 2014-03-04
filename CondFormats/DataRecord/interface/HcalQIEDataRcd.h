// name: ratnikov, date: Tue Oct 18 19:00:40 CDT 2005
#ifndef HcalQIEDataRcd_H
#define HcalQIEDataRcd_H

#include "FWCore/Framework/interface/DependentRecordImplementation.h"
#include "Geometry/Records/interface/HcalRecNumberingRecord.h"

class HcalQIEDataRcd : public edm::eventsetup::DependentRecordImplementation<HcalQIEDataRcd, boost::mpl::vector<HcalRecNumberingRecord> > {};

#endif
