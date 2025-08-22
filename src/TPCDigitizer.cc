#include "TPCDigitizer.hh"
#include "TPCDigi.hh"
#include "G4DigiManager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "TPCHit.hh"  
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4PhysicalConstants.hh"
#include <cmath>

TPCDigitizer::TPCDigitizer(const G4String& name)
  : G4VDigitizerModule(name) {
  collectionName.push_back("TPCDigiCollection");

}

TPCDigitizer::~TPCDigitizer() {}

void TPCDigitizer::Digitize() {

  G4DigiManager* digimgr = G4DigiManager::GetDMpointer();
  if (hitColID ==-1) {
      hitColID= digimgr->GetHitsCollectionID("TPCSD/TPCHitsCollection");  
  }

  const TPCHitsCollection* hitsCol = static_cast<const TPCHitsCollection*>(digimgr->GetHitsCollection(hitColID));
  if (!hitsCol) return;
  
  auto digiCollection = new TPCDigiCollection(GetName(), collectionName[0]);

  std::vector<double> fullWaveform(100, 0.0);  
  
  double charge_event =0.0;
  double length_event =0.0;
  double edep_event =0.0;
  double MomIn_event =0.0;
  double massInParticle_event=0.0;
  
  for (size_t i = 0; i < hitsCol->entries(); ++i) {

    TPCHit* hit = (*hitsCol)[i];
    //if (!hit) return;
    if (!hit) continue;
    auto edep = hit->GetEdep();
    auto hitT = hit->GetTime();
   
    auto hitPathLength =  hit->GetPathLength(); 
    auto pos = hit->GetPos();
    auto vertex = hit->GetVertex();
    auto PreStepPos = hit->GetPreStepPos();
    auto PostStepPos = hit->GetPostStepPos();
    auto PreStepPos_x = PreStepPos.x();
    auto PreStepPos_y = PreStepPos.y();
    auto PreStepPos_z = PreStepPos.z();
    auto PostStepPos_x = PostStepPos.x();
    auto PostStepPos_y = PostStepPos.y();
    auto PostStepPos_z = PostStepPos.z();
    auto processName = hit->GetProcessName();
    auto stepl = hit->GetStepLength();
    auto stepdedx = hit->GetDedx();
    auto MomIn = hit->GetMomIn();
    auto MomPt = hit->GetPt();
    auto MomPz = hit->GetPz();
    auto massInParticle = hit->GetParticleMass();
    auto cur_layer= hit->GetHitLayer();

    auto z = pos.z();
    auto betagamma =  MomIn / massInParticle;
    if (i==0){
        MomIn_event = MomIn;
        massInParticle_event = massInParticle;
    }

    auto charge = edep / ePairEnergy;
    charge *= gain;
    charge_event += charge;
    length_event += stepl;
    edep_event += edep;
    // Timing from depth + smearing
    auto ActualDriftz = hit->GetActualDriftz();
    auto driftTime = ActualDriftz / driftVelocity;
    
    auto wf = GenerateWaveform(edep, hitT);
    for (size_t j = 0; j < wf.size(); ++j){
        fullWaveform[j] += wf[j]; }

    auto* analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->FillH2(cur_layer, PreStepPos_x, PreStepPos_y);
    analysisManager->FillH2(10, PreStepPos_x, PreStepPos_y);

    
    analysisManager->FillNtupleDColumn(1, 0, charge);
    analysisManager->FillNtupleDColumn(1, 1, driftTime);
    analysisManager->FillNtupleDColumn(1, 2, stepl);
    analysisManager->FillNtupleDColumn(1, 3, MomIn);
    analysisManager->FillNtupleDColumn(1, 4, massInParticle);
    analysisManager->FillNtupleDColumn(1, 5, hitT);
    
    analysisManager->FillNtupleDColumn(1, 6, hitPathLength);
    analysisManager->FillNtupleDColumn(1, 7, PreStepPos_x);
    analysisManager->FillNtupleDColumn(1, 8, PreStepPos_y);
    analysisManager->FillNtupleDColumn(1, 9, PreStepPos_z);
    analysisManager->FillNtupleDColumn(1, 10, PostStepPos_x);
    analysisManager->FillNtupleDColumn(1, 11, PostStepPos_y);
    analysisManager->FillNtupleDColumn(1, 12, PostStepPos_z);
    analysisManager->FillNtupleSColumn(1, 13, processName);

    auto eventID= hit->GetEventID();
    analysisManager->FillNtupleIColumn(1,14, eventID);   
    analysisManager->FillNtupleIColumn(1,15, MomPt);   
    analysisManager->FillNtupleIColumn(1,16, MomPz);   
    analysisManager->AddNtupleRow(1);

    auto* digi = new TPCDigi();

    digi->SetCharge(charge);
    digi->SetTime(hitT);
    digi->SetWaveform(fullWaveform);
    digiCollection->insert(digi);
  }
   auto* analysisManager = G4AnalysisManager::Instance();
   auto dedx_event = edep_event;   
   auto betagamma_event =  MomIn_event / massInParticle_event;

   analysisManager->FillNtupleDColumn(0, 0, hitsCol->entries());
   analysisManager->FillNtupleDColumn(0, 1, charge_event);
   analysisManager->FillNtupleDColumn(0, 2, length_event);
   analysisManager->FillNtupleDColumn(0, 3, edep_event);
   analysisManager->FillNtupleDColumn(0, 4, MomIn_event);
   analysisManager->AddNtupleRow(0);

  StoreDigiCollection(digiCollection);
}
std::vector<double> TPCDigitizer::GenerateWaveform(double edep, double t0) {
    std::vector<double> wf(100, 0.0);
    double tau = 10 * ns;
    for (int i = 0; i < 100; ++i) {
        double t = i * ns;
        if (t < t0) continue;
        double x = (t - t0) / tau;
        wf[i] = edep * x * std::exp(1.0 - x);  
    }
    return wf;
}
