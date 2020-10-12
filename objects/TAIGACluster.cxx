#include <iostream>

#include "TAIGACluster.h"

TAIGACluster::TAIGACluster() {
  for (Int_t ii = 0; ii < NUMBER_OF_PIXELS; ii++) {
    fArrOfPixels[ii].SetNPixel(ii+1); // TODO Is first pixel in the any cluster has the number 1
  }
}
TAIGACluster::~TAIGACluster() {
}
TAIGACluster::TAIGACluster(const TAIGACluster &clr) :
fNCluster(clr.GetNCluster()) {
  for (Int_t ii = 0; ii < NUMBER_OF_PIXELS; ii++) {
    this->fArrOfPixels[ii]=clr.GetPixel(ii);
  }
}
void TAIGACluster::Print(TString opt) {
  if (opt == "") {
    std::cout << "NCluster: " << fNCluster << std::endl;
    for (Int_t ii = 0; ii < NUMBER_OF_PIXELS; ii++) {
      fArrOfPixels[ii].Print();
    }
  }
  else if (opt == "trigg") {
    std::cout << "NCluster: " << fNCluster << ", the number of triggered pixels is " << GetNumberOfTriggeredPixels() << std::endl;
    for (Int_t ii = 0; ii < NUMBER_OF_PIXELS; ii++) {
      fArrOfPixels[ii].Print(opt);
    }
  }
}
void TAIGACluster::SetPixelXcor(Double_t xcor, Int_t NPix) {
  fArrOfPixels[NPix-1].SetXcor(xcor);
}
void TAIGACluster::SetPixelYcor(Double_t ycor, Int_t NPix) {
  fArrOfPixels[NPix-1].SetYcor(ycor);
}
void TAIGACluster::SetPixelAmp(Double_t amp, Int_t NPix) {
  fArrOfPixels[NPix-1].SetAmp(amp);
}
void TAIGACluster::SetIsPixelTriggered(Bool_t mod, Int_t NPix) {
  fArrOfPixels[NPix-1].SetIsPixelTriggered(mod);
}
Double_t TAIGACluster::GetPixelXcor(Int_t NPix) const {
  return fArrOfPixels[NPix-1].GetXcor();
}
Double_t TAIGACluster::GetPixelYcor(Int_t NPix) const  {
  return fArrOfPixels[NPix-1].GetYcor();
}
Double_t TAIGACluster::GetPixelAmp(Int_t NPix) const {
  return fArrOfPixels[NPix-1].GetAmp();
}
Bool_t TAIGACluster::IsPixelTriggered(Int_t NPix) const {
  return fArrOfPixels[NPix-1].IsItTriggered();
}
Int_t TAIGACluster::GetNumberOfTriggeredPixels() const {
  Int_t numberOfTriggPixs=0;
  for (Int_t ii = 0; ii < NUMBER_OF_PIXELS; ii++)
    if (fArrOfPixels[ii].IsItTriggered()) numberOfTriggPixs++;
  return numberOfTriggPixs;
}

ClassImp(TAIGACluster);
