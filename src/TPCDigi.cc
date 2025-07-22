#include "TPCDigi.hh"
#include "G4ios.hh"

TPCDigi::TPCDigi() : fCharge(0), fTime(0) {}

void TPCDigi::Print() {
  G4cout << "Charge = " << fCharge << " e, Time = " << fTime << " ns" << G4endl;
}
