#include "TPCSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"

TPCSensitiveDetector::TPCSensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name) {
  collectionName.insert("TPCHitsCollection");
}

void TPCSensitiveDetector::Initialize(G4HCofThisEvent* hce) {
 
  fHitsCollection = new TPCHitsCollection(SensitiveDetectorName, collectionName[0]);
 
    if (fHCID < 0) {
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName + "/" + collectionName[0]);
    if (fHCID < 0) {
      G4cerr << "[ERROR] Could not get HCID for " << SensitiveDetectorName << "/" << collectionName[0] << G4endl;
    }
  }

  hce->AddHitsCollection(fHCID, fHitsCollection);


}

G4bool TPCSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
  //G4double edep = step->GetTotalEnergyDeposit();
  //if (edep <= 0) return false;

  //SiliconHit* hit = new SiliconHit();
  //hit->SetEdep(edep);
  //hit->SetPos(step->GetPreStepPoint()->GetPosition());
  //hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());

  //fHitsCollection->insert(hit);
  return true;
}

void TPCSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
  // Optional: add summary or logging here
}
