#include <iostream>

#include "TAIGAPixel.h"

TAIGAPixel::TAIGAPixel() {
}
TAIGAPixel::~TAIGAPixel() {
  if (GetNumberOfNeighbors() > 0)
    fVectOfNeighbors.clear();
}

TAIGAPixel::TAIGAPixel(const TAIGAPixel &pix) :
 fNPixel(pix.GetNPixel()), fXCor(pix.GetXcor()), fYCor(pix.GetYcor()),
 fAmpl(pix.GetAmp()), fIsItTriggered(pix.IsItTriggered()) {

}
void TAIGAPixel::Print(TString opt) {
  if (opt == "") {
    std::cout << "NPixel: " << fNPixel << ", " << fXCor << ", " << fYCor << ", "
              << fAmpl << ", " << fIsItTriggered << std::endl;
  }
  else if (opt == "trigg")
    if (fIsItTriggered)
      std::cout << "NPixel: " << fNPixel << ", " << fXCor << ", " << fYCor << ", "
                << fAmpl << ", " << fIsItTriggered << std::endl;
}

void TAIGAPixel::AddNeighbor(Int_t NClr, Int_t NPix) {
  if (IsPixelNeighbor(NClr, NPix)) return;
  std::cout << "[DEBUG] TAIGAPixel::AddNeighbor(" <<NClr << ", " << NPix << ")" << std::endl;
  fVectOfNeighbors.push_back(std::make_pair(NClr, NPix));
}

Bool_t TAIGAPixel::IsPixelNeighbor(Int_t NClr, Int_t NPix) {
  if (GetNumberOfNeighbors() < 1) return kFALSE;

  for (Int_t i=0; i<GetNumberOfNeighbors(); i++) {
    if (fVectOfNeighbors[i].first == NClr && fVectOfNeighbors[i].second == NPix)
      return kTRUE;
  }
  return kFALSE;
}
ClassImp(TAIGAPixel);
