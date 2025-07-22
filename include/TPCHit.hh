#ifndef TPCHit_h
#define TPCHit_h 1

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

class TPCHit : public G4VHit {
public:
  TPCHit();
  ~TPCHit() override = default;

  TPCHit(const TPCHit&);
  const TPCHit& operator=(const TPCHit&);

  G4bool operator==(const TPCHit&) const;

  void* operator new(size_t);
  void  operator delete(void*);

  void SetEdep(G4double edep) { fEdep = edep; }
  void SetTime(G4double time) { fTime = time; }
  void SetPos(const G4ThreeVector& pos) { fPos = pos; }
  void SetStepLength(G4double stepLength) { fstepLength = stepLength; }
  void SetDedx(G4double dedx) { fdedx = dedx; }
  void SetMomIn(G4double mom) { fMomentumIn = mom; }
  void SetPt(G4double pt) { fPt = pt; }
  void SetPz(G4double pz) { fPz = pz; }
  void SetParticleMass(G4double mass) { fParticleMass = mass; }
  void SetHitLayer(G4int layer) { fLayer = layer; }
  void SetEventID(G4int EventID) { fEventID = EventID; }
  void SetActualDriftz(G4double ActualDriftz) { fActualDriftz = ActualDriftz; }
  void SetVertex(const G4ThreeVector& vertex) { fVertex = vertex; } 
  void SetPreStepPos(const G4ThreeVector& preStepPos){fpreStepPos=preStepPos;}
  void SetPostStepPos(const G4ThreeVector& postStepPos){fpostStepPos = postStepPos;}
  void SetPathLength(G4double pathLength) { fpathLength = pathLength; }  
  void SetProcessName(const G4String processName){fprocessName = processName;}


  void AddEdep(G4double edep) { fEdep += edep; }

  G4double GetEdep() const { return fEdep; }
  G4ThreeVector GetPos() const { return fPos; }
  G4double GetTime() const { return fTime; }
  G4double GetStepLength() const { return fstepLength; }
  G4double GetDedx() const { return fdedx; }
  G4double GetMomIn() const { return fMomentumIn; }
  G4double GetPt() const { return fPt; }
  G4double GetPz() const { return fPz; }
  G4double GetParticleMass() const { return fParticleMass; }
  G4int GetHitLayer() const { return fLayer; }
  G4double GetPathLength() const {return fpathLength;}
  G4double GetActualDriftz() const {return fActualDriftz;}
  G4ThreeVector GetVertex() const {return fVertex;}
  G4ThreeVector GetPreStepPos() const {return fpreStepPos;}
  G4ThreeVector GetPostStepPos() const {return fpostStepPos;}
  G4String GetProcessName() const {return fprocessName;}
  G4int GetEventID() const {return fEventID;}
  void Print() override;

private:
  G4double fEdep;
  G4ThreeVector fPos;
  G4ThreeVector fVertex;
  G4ThreeVector fpreStepPos;
  G4ThreeVector fpostStepPos;
  G4double fpathLength;
  G4double fTime;
  G4double fstepLength;
  G4double fdedx;
  G4double fMomentumIn;
  G4double fPt;
  G4double fPz;
  G4double fParticleMass;
  G4String fprocessName;
  G4double fActualDriftz;
  G4int fLayer;
  G4int fEventID;
};

using TPCHitsCollection = G4THitsCollection<TPCHit>;

extern G4ThreadLocal G4Allocator<TPCHit>* TPCHitAllocator;

#endif
