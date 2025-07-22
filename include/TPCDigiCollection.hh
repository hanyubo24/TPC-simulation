#ifndef TPCDigiCollection_h
#define TPCDigiCollection_h 1

#include "G4VDigiCollection.hh"
#include "globals.hh"
#include "TPCDigi.hh"
#include <vector>

class TPCDigiCollection : public G4VDigiCollection {
public:
  TPCDigiCollection(const G4String& moduleName, const G4String& collectionName);
  ~TPCDigiCollection() override;

  void insert(TPCDigi* digi);
  TPCDigi* operator[](G4int i) const;
  size_t entries() const;

private:
  std::vector<TPCDigi*> fDigiList;
};

#endif
