/* TAIGAEvent class is an object for describing events for the TAIGA_IACT experiments.
*/

// Author: Satyshev Ilyas. JINR

#ifndef TAIGAEvent_H
#define TAIGAEvent_H

#include <vector>

#include "TObject.h"
#include "TString.h"

#include "TAIGACluster.h"

class TAIGAEvent : public TObject {
public:
  TAIGAEvent();
  TAIGAEvent(Int_t nev);
  ~TAIGAEvent();

  void Print(TString opt="");
  void AddCluster(TAIGACluster &clr);
  /** Modifiers **/
  void SetNEvent(Int_t nev) { fNEvent=nev; }
  void SetPixelAmp();
  void IterAmp(Double_t amp) { fIntegralofAmp+=amp; }
  void SetTime(TString time) { fTime=time; }
  /** Accessors **/
  Int_t GetNEvent() const { return fNEvent; }
  Int_t GetNumberOfTriggeredClusters() const { return fVectOfClusters.size(); }
  Double_t GetIntegralofAmp() const { return fIntegralofAmp; }

  TString GetTime() const { return fTime; }

  TAIGACluster & GetCluster(Int_t iClr) { return fVectOfClusters[iClr]; }
private:
  Int_t fNEvent=-1;
  Double_t fIntegralofAmp=0.;

  TString fTime="";

  std::vector<TAIGACluster> fVectOfClusters;

  ClassDef (TAIGAEvent,1);
};

#endif // TAIGAEvent_H
