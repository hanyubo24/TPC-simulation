//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B4/B4a/src/RunAction.cc
/// \brief Implementation of the B4::RunAction class

#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"
#include "G4DigiManager.hh"
#include "G4AutoLock.hh"
namespace {
    G4Mutex analysisFileMutex = G4MUTEX_INITIALIZER;
}

namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(const G4String& outFileName)
: fOutFileName(outFileName)
{
  // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);
    auto* analysisManager = G4AnalysisManager::Instance();

    G4int numSlices = 10;
    G4int bins_x = 100;
    G4int bins_y = 100;
    G4bool hitNtuple = false;
    for (G4int i = 0; i < numSlices; ++i) {
        std::ostringstream name, title;
        name  << "HitMap_layer_" << i;
        title << "HitMap for slice #" << i << ";X (mm);Y (mm)";

        analysisManager->CreateH2(name.str(), title.str(), 
                                  bins_x, -1000., 1000.,   // X binning
                                  bins_y, -1000.,  1000.);   // Y binning
    }

    //analysisManager->SetVerboseLevel(1);
    //analysisManager->SetNtupleMerging(true);
    // index = 10
    analysisManager->CreateH2("HitMap_all", "HitMap;X (mm);Y (mm)", bins_x, -1000., 1000.,bins_y, -1000., 1000.);
    // analysisManager->CreateH2("Dedx_hit", "Dedx per hit:P;Dedx", 500,0,3,500,0,20);
    // analysisManager->CreateH2("Dedx_event", "Dedx per event;P;Dedx ", 500,0,3,500,0,20);
    // analysisManager->CreateH2("Dedx_hit_gb", "Dedx per hit;[betaGamma];Dedx ", 500,0,10,500,0,20);
    // analysisManager->CreateH2("Dedx_event_bg", "Dedx per event;[betaGamma];Dedx ", 500,0,10,500,0,20);
    // analysisManager->CreateH2("HitMap_layer1", "HitMap;PixID X;PixID Y", 400, -200,200, 100,-50, 50 );

    G4cout << "[THREAD] Creating ntuple..." << G4endl;
    analysisManager->CreateNtuple("EventNtuple", "Event signal");
    analysisManager->CreateNtupleDColumn("NumberOfHits");
    analysisManager->CreateNtupleDColumn("Charge");
    analysisManager->CreateNtupleDColumn("TotalLength");
    analysisManager->CreateNtupleDColumn("Dedx");
    analysisManager->CreateNtupleDColumn("MomIn");
    // analysisManager->CreateNtupleDColumn("betagamma");
    analysisManager->FinishNtuple();
  //
    if (hitNtuple){
      analysisManager->CreateNtuple("HitNtuple", "Digitized Signals");
      analysisManager->CreateNtupleDColumn("charge"); 
      analysisManager->CreateNtupleDColumn("driftTime_notSmeared"); // drift to the surface of the silicon
      analysisManager->CreateNtupleDColumn("driftTime_Smeared"); 
      analysisManager->CreateNtupleDColumn("PixIDX");
      analysisManager->CreateNtupleDColumn("PixIDY");
      analysisManager->CreateNtupleDColumn("EnergyDep");
      analysisManager->CreateNtupleDColumn("StepLength"); 
      analysisManager->CreateNtupleDColumn("Dedx");
      analysisManager->CreateNtupleDColumn("MomIn");
      analysisManager->CreateNtupleDColumn("MassIn");
      analysisManager->CreateNtupleDColumn("betagamma");
      analysisManager->CreateNtupleDColumn("layer");
      analysisManager->CreateNtupleDColumn("Gtime"); // global time
      analysisManager->CreateNtupleDColumn("Gtime_smeared"); // Gtime + driftTime_Smeared
      analysisManager->CreateNtupleDColumn("P_e");
      analysisManager->CreateNtupleDColumn("P_mu");
      analysisManager->CreateNtupleDColumn("P_pi");
      analysisManager->CreateNtupleDColumn("P_kaon");
      analysisManager->CreateNtupleDColumn("P_proton");
      analysisManager->CreateNtupleDColumn("L_e");
      analysisManager->CreateNtupleDColumn("L_mu");
      analysisManager->CreateNtupleDColumn("L_pi");
      analysisManager->CreateNtupleDColumn("L_kaon");
      analysisManager->CreateNtupleDColumn("L_proton");
      analysisManager->CreateNtupleDColumn("HitPathLength_fromTrack");
      analysisManager->CreateNtupleDColumn("expt_e");
      analysisManager->CreateNtupleDColumn("expt_mu");
      analysisManager->CreateNtupleDColumn("expt_pi");
      analysisManager->CreateNtupleDColumn("expt_kaon");
      analysisManager->CreateNtupleDColumn("expt_proton");
      analysisManager->CreateNtupleDColumn("prePos_x");
      analysisManager->CreateNtupleDColumn("prePos_y");
      analysisManager->CreateNtupleDColumn("prePos_z");
      analysisManager->CreateNtupleDColumn("postPos_x");
      analysisManager->CreateNtupleDColumn("postPos_y");
      analysisManager->CreateNtupleDColumn("postPos_z");
      analysisManager->CreateNtupleSColumn("processName");
      analysisManager->CreateNtupleIColumn("EventID");
      analysisManager->CreateNtupleIColumn("Pt");
      analysisManager->CreateNtupleIColumn("Pz");

      analysisManager->FinishNtuple();
    }

  //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  // inform the runManager to save random number seed
  // G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
    auto* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true); 
     
    analysisManager->OpenFile(fOutFileName);  // 

 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
        auto* analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile(false);
        G4cout << "[RunAction] Closing output file..." << G4endl;
}
 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B4
