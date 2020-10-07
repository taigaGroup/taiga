#include <iostream>
#include <iomanip>
using std::setw;

#include "TAIGACamera.h"

TAIGACamera::TAIGACamera() {
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS; ii++) {
    fArrOfClusters[ii].SetNCluster(ii+1); // TODO Is first cluster has the number 1
  }
}
TAIGACamera::~TAIGACamera() {

}

void TAIGACamera::Print() {
  UInt_t shiftForNPixel(6), shiftForXcor(10), shiftForYcor(10), shiftForAmp(15), shiftForTrigg(15), shiftForNNeig(15);
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS; ii++) {
    std::cout << "Cluster " << fArrOfClusters[ii].GetNCluster() << std::endl;
    std::cout << "NPixel" << setw(shiftForXcor) << "x" << setw(shiftForYcor) << "y" << setw(shiftForAmp) << "amp"
              << setw(shiftForTrigg) << "trigg" << setw(shiftForNNeig) << "NNeighbors" << std::endl;
    for (Int_t jj = 0; jj < NUMBER_OF_PIXELS; jj++) {
      TAIGAPixel curPixel=GetPixel(ii, jj);
      std::cout << setw(shiftForNPixel) << curPixel.GetNPixel() << setw(shiftForXcor) << curPixel.GetXcor()
           << setw(shiftForYcor) << curPixel.GetYcor() << setw(shiftForAmp) << curPixel.GetAmp()
           << setw(shiftForTrigg) << curPixel.IsItTriggered()
           << setw(shiftForNNeig) << GetNumberOfPixelNeighbors(fArrOfClusters[ii].GetNCluster(), curPixel.GetNPixel())
           << std::endl;
    }
  }
}
void TAIGACamera::PrintNeighborsInfo() {

  std::cout << "It needs to be Implement!" << std::endl;
}
void TAIGACamera::AddPixelNeighbor(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2) {
  std::cout << "[DEBUG] TAIGACamera::AddPixelNeighbor(" <<NClr1 << ", " << NClr2 << ", "
            << NPix1 << "," << NPix2 << ")" << std::endl;
  TAIGAPixel curPix=GetPixel(NClr1, NPix1);
  curPix.AddNeighbor(NClr2, NPix2);
}

Bool_t TAIGACamera::are2PixelsNeighbors(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2) {
  TAIGAPixel curPix=GetPixel(NClr1, NPix1);
  return curPix.IsPixelNeighbor(NClr2, NPix2);
}

Int_t TAIGACamera::GetNumberOfPixelNeighbors(Int_t NClr, Int_t NPix) {
  TAIGAPixel curPix=GetPixel(NClr, NPix);
  return curPix.GetNumberOfNeighbors();
}
void TAIGACamera::SetPixelXcor(Double_t xcor, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr].SetPixelXcor(xcor, NPix);
}
void TAIGACamera::SetPixelYcor(Double_t ycor, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr].SetPixelYcor(ycor, NPix);
}
void TAIGACamera::SetPixelAmp(Double_t amp, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr].SetPixelAmp(amp, NPix);
}
void TAIGACamera::SetIsPixelTriggered(Bool_t mod, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr].SetIsPixelTriggered(mod, NPix);
}
Double_t TAIGACamera::GetPixelXcor(Int_t NClr, Int_t NPix) {
  return fArrOfClusters[NClr].GetPixelXcor(NPix);
}
Double_t TAIGACamera::GetPixelYcor(Int_t NClr, Int_t NPix) {
  return fArrOfClusters[NClr].GetPixelYcor(NPix);
}
