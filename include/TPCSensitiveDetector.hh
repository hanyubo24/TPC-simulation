#ifndef TPCSensitiveDetector_h
#define TPCSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "TPCHit.hh"

class TPCSensitiveDetector : public G4VSensitiveDetector {
public:
  TPCSensitiveDetector(const G4String& name);
  ~TPCSensitiveDetector() override = default;

  void Initialize(G4HCofThisEvent* hce) override;
  G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  void EndOfEvent(G4HCofThisEvent* hce) override;

private:
  TPCHitsCollection* fHitsCollection = nullptr;
  G4int fHCID = -1;
};

#endif
