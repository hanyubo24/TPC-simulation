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
/// \file B4/B4a/src/DetectorConstruction.cc
/// \brief Implementation of the B4::DetectorConstruction class

#include "DetectorConstruction.hh"
#include "TPCSensitiveDetector.hh"
#include "G4AutoDelete.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Colour.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"
#include "G4ProductionCuts.hh"
namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  // Lead material defined using NIST Manager
  auto nist = G4NistManager::Instance();
  // nist->FindOrBuildMaterial("G4_Si");
  nist->FindOrBuildMaterial("G4_AIR");
  nist->FindOrBuildMaterial("G4_Galactic");
  auto Ar  = nist->FindOrBuildElement("Ar"); 
  auto CO2 = nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE");

  // Define Argon/CO₂ TPC gas mixture (e.g., 80/20 at 1 atm)
  G4double temperature = 293.15 * kelvin;
  G4double pressure    = 1. * atmosphere;
  G4double density     = 1.6e-3 * g/cm3; // Approximate

  auto TPCGas = new G4Material("TPCGas", density, 2, kStateGas, temperature, pressure);
  TPCGas->AddElement(Ar, 80 * perCent);
  TPCGas->AddMaterial(CO2, 20 * perCent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  

  auto worldSizeXY =3 *m;
  auto worldSizeZ = 3 *m;

  // auto siliconMaterial = G4Material::GetMaterial("G4_Si");
  auto air = G4Material::GetMaterial("G4_AIR");
  auto vacuum = G4Material::GetMaterial("G4_Galactic");
  auto tpcGas = G4Material::GetMaterial("TPCGas");
  //
  // World
  //
  auto worldS = new G4Box("World",  // its name
                          worldSizeXY / 2, worldSizeXY / 2, worldSizeZ / 2);  // its size


  auto worldLV = new G4LogicalVolume(worldS,  // its solid
                                     vacuum,  // its material
                                     "World");  // its name

  auto worldPV = new G4PVPlacement(nullptr,  // no rotation
                                   G4ThreeVector(),  // at (0,0,0)
                                   worldLV,  // its logical volume
                                   "World",  // its name
                                   nullptr,  // its mother  volume
                                   false,  // no boolean operation
                                   0,  // copy number
                                   fCheckOverlaps);  // checking overlaps


 // a cylinder 
  G4double radius_for_testing = 0.05*m;
  G4double size_z = 0.05*m; // full z = *2
  G4int numSlices = 10; // 
  G4double sliceZHalf = size_z / numSlices;

  // 1. Full TPC volume (mother)

  auto gasDet = new G4Tubs("TPC", 0, radius_for_testing, size_z, 0.0*deg, 360.0*deg);
  auto gasLV = new G4LogicalVolume(gasDet, tpcGas, "TPC");  

  // 2. Slice volume (1/N of TPC in Z)
  auto sliceGas = new G4Tubs("TPCSlice", 0, radius_for_testing, sliceZHalf, 0.0*deg, 360.0*deg);
  fsliceLV = new G4LogicalVolume(sliceGas, tpcGas, "TPCSlice"); 

  // 3. Replicate slices along Z
  new G4PVReplica("TPCSlicePhys", fsliceLV, gasLV, kZAxis, numSlices, 2*sliceZHalf);

  // 4. Place full TPC in the world
  fTPCLogic = gasLV; 
  TPCPV = new G4PVPlacement(0, G4ThreeVector(0,0,0), gasLV, "TPC", worldLV, false, 0, fCheckOverlaps);

  // Visualization attributes
  worldLV->SetVisAttributes(G4VisAttributes::GetInvisible());

  //worldLV->SetVisAttributes(G4VisAttributes(G4Colour::White()));
  fTPCLogic->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  //G4ThreeVector fieldValue = G4ThreeVector(0., 1.5*tesla, 0.);
  G4ThreeVector fieldValue = G4ThreeVector(0., 0., 1.5*tesla);

  //G4ThreeVector fieldValue = G4ThreeVector(0., 0., 0.);
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);

  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  auto* TPCSD = new TPCSensitiveDetector("TPCSD");
  sdManager->AddNewDetector(TPCSD);
  fTPCLogic->SetSensitiveDetector(TPCSD);

  auto regionTPC = new G4Region("TPCRegion");
  fTPCLogic->SetRegion(regionTPC);
  regionTPC->AddRootLogicalVolume(fTPCLogic);
  
  auto cuts = new G4ProductionCuts();
  cuts->SetProductionCut(0.1*micrometer, "e-");
  cuts->SetProductionCut(0.1*micrometer, "e+");
  cuts->SetProductionCut(0.1*micrometer, "gamma");
  
  regionTPC->SetProductionCuts(cuts);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B4
