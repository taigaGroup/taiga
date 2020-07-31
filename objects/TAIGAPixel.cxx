#include <iostream>

#include "TAIGAPixel.h"

TAIGAPixel::TAIGAPixel() {
}
TAIGAPixel::~TAIGAPixel() {
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

ClassImp(TAIGAPixel);
