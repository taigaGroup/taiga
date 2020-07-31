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
  if (opt == "") {
    std::cout << "Event " << fNEvent << ", the number of triggered clusters is "
                          << GetNumberOfTriggeredClusters() << std::endl;
    for (Int_t ii = 0; ii < GetNumberOfTriggeredClusters(); ii++) {
      fVectOfClusters[ii].Print();
    }
    std::cout << std::endl;
  }
  else if (opt == "trigg") {
    std::cout << "Event " << fNEvent << ", the number of triggered clusters is "
                          << GetNumberOfTriggeredClusters() << std::endl;
    for (Int_t ii = 0; ii < GetNumberOfTriggeredClusters(); ii++) {
      fVectOfClusters[ii].Print(opt);
    }
    std::cout << std::endl;
  }
}
void TAIGAEvent::AddCluster(TAIGACluster &clr) {
  fVectOfClusters.push_back(clr);
}

ClassImp(TAIGAEvent);
