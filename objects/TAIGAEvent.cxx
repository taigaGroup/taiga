#include <iostream>

#include "TAIGAEvent.h"

TAIGAEvent::TAIGAEvent() {
}
TAIGAEvent::TAIGAEvent(Int_t nev) :
fNEvent(nev) {

}
TAIGAEvent::~TAIGAEvent() {
}
void TAIGAEvent::Print(TString opt) {
  std::cout << "In Event " << GetNEvent() << " nuber of triggered clusters is "
            << GetNumberOfTriggeredClusters() << std::endl;
  for (Int_t i=0; i<GetNumberOfTriggeredClusters(); i++) {
    std::cout << "Cluster " << fVectOfClusters[i].GetNCluster() << std::endl;
    Int_t counter=0;
    for (Int_t ii=0; ii<8; ii++) {
      for (Int_t iii=0; iii<8; iii++) {
        counter++;
        std::cout << fVectOfClusters[i].GetPixelAmp(counter) << " " << fVectOfClusters[i].IsPixelTriggered(counter) << " ";
      }
      std::cout << std::endl;
    }
  }

}
void TAIGAEvent::AddCluster(TAIGACluster &clr) {
  fVectOfClusters.push_back(clr);
}

ClassImp(TAIGAEvent);
