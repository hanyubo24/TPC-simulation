#include "TPCHit.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<TPCHit>* TPCHitAllocator = nullptr;

TPCHit::TPCHit()
  : fEdep(0.), fPos(G4ThreeVector()), fTime(0.) {}

TPCHit::TPCHit(const TPCHit& right)
  : G4VHit(),
    fEdep(right.fEdep),
    fPos(right.fPos),
    fTime(right.fTime) {}

const TPCHit& TPCHit::operator=(const TPCHit& right) {
  if (this != &right) {
    fEdep = right.fEdep;
    fPos = right.fPos;
    fTime = right.fTime;
  }
  return *this;
}

G4bool TPCHit::operator==(const TPCHit& right) const {
  return (this == &right);
}

void* TPCHit::operator new(size_t) {
  if (!TPCHitAllocator) TPCHitAllocator = new G4Allocator<TPCHit>;
  return (void*) TPCHitAllocator->MallocSingle();
}

void TPCHit::operator delete(void* hit) {
  TPCHitAllocator->FreeSingle((TPCHit*) hit);
}

void TPCHit::Print() {
  G4cout << "TPCHit: E = " << G4BestUnit(fEdep, "Energy")
         << ", Pos = " << G4BestUnit(fPos, "Length")
         << ", Time = " << G4BestUnit(fTime, "Time") << G4endl;
}
