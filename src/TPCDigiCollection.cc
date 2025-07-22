#include "TPCDigiCollection.hh"

TPCDigiCollection::TPCDigiCollection(const G4String& moduleName,
                                             const G4String& collectionName)
  : G4VDigiCollection(moduleName, collectionName) {}

TPCDigiCollection::~TPCDigiCollection() {
  for (auto* d : fDigiList) delete d;
}

void TPCDigiCollection::insert(TPCDigi* digi) {
  fDigiList.push_back(digi);
}

TPCDigi* TPCDigiCollection::operator[](G4int i) const{
  return fDigiList[i];
}

size_t TPCDigiCollection::entries() const {
  return fDigiList.size();
}
