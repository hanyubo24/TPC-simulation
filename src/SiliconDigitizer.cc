#include "SiliconDigitizer.hh"
#include "SiliconDigi.hh"
#include "G4DigiManager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "SiliconHit.hh"  
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4PhysicalConstants.hh"
#include <cmath>

SiliconDigitizer::SiliconDigitizer(const G4String& name)
  : G4VDigitizerModule(name) {
  collectionName.push_back("SiliconDigiCollection");
}

SiliconDigitizer::~SiliconDigitizer() {}

void SiliconDigitizer::Digitize() {

  G4double pixelSizeX = 100 * micrometer;
  G4double pixelSizeY = 100 * micrometer;  

  std::map<std::pair<G4int, G4int>, SiliconDigi*> pixelMap;
 
  G4DigiManager* digimgr = G4DigiManager::GetDMpointer();
  if (hitColID ==-1) {
      hitColID= digimgr->GetHitsCollectionID("SiliconSD/SiliconHitsCollection");  
  }

  const SiliconHitsCollection* hitsCol = static_cast<const SiliconHitsCollection*>(digimgr->GetHitsCollection(hitColID));
  if (!hitsCol) return;
  
  auto digiCollection = new SiliconDigiCollection(GetName(), collectionName[0]);

  std::vector<double> fullWaveform(100, 0.0);  
  
  double charge_event =0.0;
  double length_event =0.0;
  double edep_event =0.0;
  double MomIn_event =0.0;
  double massInParticle_event=0.0;
  
  for (size_t i = 0; i < hitsCol->entries(); ++i) {
    SiliconHit* hit = (*hitsCol)[i];
    //if (!hit) return;
    if (!hit) continue;
    auto edep = hit->GetEdep();
    auto hitT = hit->GetTime();
    //auto hitTSmeared = hitT+ G4RandGauss::shoot(0., timeSmearing);
   
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
    //std::cout<< "index i : "<< i <<std::endl; 
   // std::cout<< "YB testing, pre z: "<< PreStepPos_z<<std::endl; 
   // std::cout<< "YB testing, post z: "<< PostStepPos_z<<std::endl; 
    // Energy to charge
    auto charge = edep / ePairEnergy;
    charge *= gain;
    charge_event += charge;
    length_event += stepl;
    edep_event += edep;
    // Timing from depth + smearing
    auto ActualDriftz = hit->GetActualDriftz();
    auto driftTime = ActualDriftz / driftVelocity;
    auto time = driftTime + G4RandGauss::shoot(0., timeSmearing);
    //auto hitTSmeared = hitT+ time;
    auto hitTSmeared = hitT+ G4RandGauss::shoot(0., timeSmearing);
    
    auto wf = GenerateWaveform(edep, hitT);
    for (size_t j = 0; j < wf.size(); ++j){
        fullWaveform[j] += wf[j]; }

    // readout on a layer at z=0
    auto sigma_xy = std::sqrt(2.0*diffusionCons*time);
    G4double dx = G4RandGauss::shoot(0., sigma_xy);
    G4double dy = G4RandGauss::shoot(0., sigma_xy);

    //G4int pixelX = static_cast<G4int>(std::floor((pos.x() + dx ) / pixelSizeX));
    //G4int pixelY = static_cast<G4int>(std::floor((pos.y() + dy ) / pixelSizeY));
    G4int pixelX = 0;
    G4int pixelY =0;
    //if (pixelX < -200 || pixelX >= 200 || pixelY < -100 || pixelY >= 100) {
    //          //continue;
    //}
    std::pair<G4int, G4int> pixelID = {pixelX, pixelY};


    auto* analysisManager = G4AnalysisManager::Instance();
    if (cur_layer == 0){
        analysisManager->FillH2(0, pixelX, pixelY);}
    if (cur_layer==1){
        analysisManager->FillH2(5, pixelX, pixelY);}

    analysisManager->FillH2(1, MomIn, stepdedx); 
    analysisManager->FillH2(3, betagamma, stepdedx); 
    
    analysisManager->FillNtupleDColumn(0, 0, charge);
    analysisManager->FillNtupleDColumn(0, 1, driftTime);
    analysisManager->FillNtupleDColumn(0, 2, time);
    analysisManager->FillNtupleDColumn(0, 3, pixelX);
    analysisManager->FillNtupleDColumn(0, 4, pixelY);
    analysisManager->FillNtupleDColumn(0, 5, edep);
    analysisManager->FillNtupleDColumn(0, 6, stepl);
    analysisManager->FillNtupleDColumn(0, 7, stepdedx);
    analysisManager->FillNtupleDColumn(0, 8, MomIn);
    analysisManager->FillNtupleDColumn(0, 9, massInParticle);
    analysisManager->FillNtupleDColumn(0, 10, betagamma);
    analysisManager->FillNtupleDColumn(0, 11, cur_layer);
    analysisManager->FillNtupleDColumn(0, 12, hitT);
    analysisManager->FillNtupleDColumn(0, 13, hitTSmeared);
    
    auto expectedTOF = [&](G4double mass) {
    //return hitPathLength / c_light * std::sqrt(1 + std::pow(mass / MomIn, 2));
    return hitPathLength / (c_light * (MomIn/ (std::sqrt(MomIn*MomIn + mass*mass))));
    };

    auto logLikelihood = [&](G4double t_expected) {
    G4double delta = hitTSmeared - t_expected;
    return 0.5 * std::pow(delta / timeSmearing, 2);
    };
    
    auto expt_e = expectedTOF(Mass_e);
    auto expt_mu = expectedTOF(Mass_mu);
    auto expt_pi = expectedTOF(Mass_pi);
    auto expt_kaon = expectedTOF(Mass_kaon);
    auto expt_p = expectedTOF(Mass_p);

    auto llh_e = -logLikelihood(expt_e);
    auto llh_mu  = -logLikelihood(expt_mu);
    auto llh_pi = -logLikelihood(expt_pi);
    auto llh_kaon = -logLikelihood(expt_kaon);
    auto llh_p = -logLikelihood(expt_p);

    auto max_num_for_norm = std::max({llh_e, llh_mu, llh_pi, llh_kaon, llh_p});

    auto L_e    =std::exp( llh_e - max_num_for_norm);
    auto L_mu   =std::exp( llh_mu - max_num_for_norm);
    auto L_pi   =std::exp( llh_pi - max_num_for_norm);
    auto L_kaon =std::exp( llh_kaon - max_num_for_norm);
    auto L_p    =std::exp( llh_p - max_num_for_norm);

    auto sum = L_e + L_mu + L_pi + L_kaon + L_p;

    auto P_e    = L_e / sum;
    auto P_mu   = L_mu / sum;
    auto P_pi   = L_pi / sum;
    auto P_kaon = L_kaon / sum;
    auto P_p    = L_p / sum;

    //P_e    = expectedTOF(Mass_e);
    //P_mu   = expectedTOF(Mass_mu);
    //P_pi   = expectedTOF(Mass_pi);
    //P_kaon = expectedTOF(Mass_kaon);
    //P_p    = expectedTOF(Mass_p);

    
    //analysisManager->FillNtupleDColumn(0, 14, llh_e);
    //analysisManager->FillNtupleDColumn(0, 15, llh_mu);
    //analysisManager->FillNtupleDColumn(0, 16, llh_pi);
    //analysisManager->FillNtupleDColumn(0, 17, llh_kaon);
    //analysisManager->FillNtupleDColumn(0, 18, llh_p);
    analysisManager->FillNtupleDColumn(0, 14, P_e);
    analysisManager->FillNtupleDColumn(0, 15, P_mu);
    analysisManager->FillNtupleDColumn(0, 16, P_pi);
    analysisManager->FillNtupleDColumn(0, 17, P_kaon);
    analysisManager->FillNtupleDColumn(0, 18, P_p);
    analysisManager->FillNtupleDColumn(0, 19, llh_e);
    analysisManager->FillNtupleDColumn(0, 20, llh_mu);
    analysisManager->FillNtupleDColumn(0, 21, llh_pi);
    analysisManager->FillNtupleDColumn(0, 22, llh_kaon);
    analysisManager->FillNtupleDColumn(0, 23, llh_p);

    analysisManager->FillNtupleDColumn(0, 24, hitPathLength);
    analysisManager->FillNtupleDColumn(0, 25, expt_e);
    analysisManager->FillNtupleDColumn(0, 26, expt_mu);
    analysisManager->FillNtupleDColumn(0, 27, expt_pi);
    analysisManager->FillNtupleDColumn(0, 28, expt_kaon);
    analysisManager->FillNtupleDColumn(0, 29, expt_p);
    analysisManager->FillNtupleDColumn(0, 30, PreStepPos_x);
    analysisManager->FillNtupleDColumn(0, 31, PreStepPos_y);
    analysisManager->FillNtupleDColumn(0, 32, PreStepPos_z);
    analysisManager->FillNtupleDColumn(0, 33, PostStepPos_x);
    analysisManager->FillNtupleDColumn(0, 34, PostStepPos_y);
    analysisManager->FillNtupleDColumn(0, 35, PostStepPos_z);
    analysisManager->FillNtupleSColumn(0, 36, processName);
    //G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    auto eventID= hit->GetEventID();
    analysisManager->FillNtupleIColumn(0,37, eventID);   
    analysisManager->FillNtupleIColumn(0,38, MomPt);   
    analysisManager->FillNtupleIColumn(0,39, MomPz);   


    analysisManager->AddNtupleRow(0);

    auto* digi = new SiliconDigi();
    digi->SetCharge(charge);
    digi->SetTime(time);
    digi->SetWaveform(fullWaveform);
    digiCollection->insert(digi);
  }
   auto* analysisManager = G4AnalysisManager::Instance();
   auto dedx_event = edep_event/length_event;   
   auto betagamma_event =  MomIn_event / massInParticle_event;

   analysisManager->FillH2(2, MomIn_event, dedx_event); 
   analysisManager->FillH2(4, betagamma_event, dedx_event); 

   analysisManager->FillNtupleDColumn(1, 0, hitsCol->entries());
   analysisManager->FillNtupleDColumn(1, 1, charge_event);
   analysisManager->FillNtupleDColumn(1, 2, length_event);
   analysisManager->FillNtupleDColumn(1, 3, edep_event);
   analysisManager->FillNtupleDColumn(1, 4, MomIn_event);
   analysisManager->FillNtupleDColumn(1, 5, betagamma_event);
   analysisManager->AddNtupleRow(1);

  StoreDigiCollection(digiCollection);
}
std::vector<double> SiliconDigitizer::GenerateWaveform(double edep, double t0) {
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
