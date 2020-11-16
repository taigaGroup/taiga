#include <iostream>
#include <iomanip>
using std::setw;

#include "TAIGACamera.h"

TAIGACamera::TAIGACamera() {
  fArrOfClusters = new TAIGACluster [NUMBER_OF_CLUSTERS];
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS; ii++) {
    fArrOfClusters[ii].SetNCluster(ii+1); // TODO does the first cluster has the number 1
  }
}
TAIGACamera::~TAIGACamera() {
  for (Int_t ii=0; ii<NUMBER_OF_CLUSTERS*NUMBER_OF_PIXELS; ii++)
    fArrOfVectOfNeighbors[ii].clear();
  if (fArrOfClusters) delete [] fArrOfClusters;
}

void TAIGACamera::Print() {
  UInt_t shiftForNPixel(6), shiftForXcor(10), shiftForYcor(10), shiftForAmp(15), shiftForTrigg(15), shiftForNNeig(15);
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS; ii++) {
    std::cout << "Cluster " << fArrOfClusters[ii].GetNCluster() << std::endl;
    std::cout << "NPixel" << setw(shiftForXcor) << "x" << setw(shiftForYcor) << "y" << setw(shiftForAmp) << "amp"
              << setw(shiftForTrigg) << "trigg" << setw(shiftForNNeig) << "NNeighbors" << std::endl;
    for (Int_t jj = 0; jj < NUMBER_OF_PIXELS; jj++) {
      TAIGAPixel curPixel=fArrOfClusters[ii].GetPixel(jj);
      std::cout << setw(shiftForNPixel) << curPixel.GetNPixel() << setw(shiftForXcor) << curPixel.GetXcor()
           << setw(shiftForYcor) << curPixel.GetYcor() << setw(shiftForAmp) << curPixel.GetAmp()
           << setw(shiftForTrigg) << curPixel.IsItTriggered()
           << setw(shiftForNNeig) << GetNumberOfPixelNeighbors(fArrOfClusters[ii].GetNCluster(), curPixel.GetNPixel())
           << std::endl;
    }
  }
}
void TAIGACamera::PrintNeighborsInfo() {
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS*NUMBER_OF_PIXELS; ii++) {
    std::cout << fArrOfVectOfNeighbors[ii].size() << std::endl;
  }
}
void TAIGACamera::AddPixelNeighbor(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2) {
  Int_t testNum = (NClr1-1)*NUMBER_OF_PIXELS+NPix1-1;
  if (testNum > NUMBER_OF_CLUSTERS*NUMBER_OF_PIXELS && testNum < 0) {
    std::cerr << "[ERROR]: Pixel with NClr=" << NClr1 << ", NPix=" << NPix1 << " doesn't exist!" << std::endl;
    return;
  }
  if ((NClr1 == NClr2) && (NPix1 == NPix2)) {
    std::cout << "[WARNING]: Don't compare pixel with It self!" << std::endl;
    return;
  }
  if (are2PixelsNeighbors(NClr1, NClr2, NPix1, NPix2)) return;
  fArrOfVectOfNeighbors[(NClr1-1)*NUMBER_OF_PIXELS+NPix1-1].push_back(std::make_pair(NClr2, NPix2));
}

Bool_t TAIGACamera::are2PixelsNeighbors(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2) {
  if (GetNumberOfPixelNeighbors(NClr1, NPix1) < 1) return kFALSE;
  for (Int_t ii=0; ii<GetNumberOfPixelNeighbors(NClr1, NPix1);ii++) {
     Int_t curNClr=fArrOfVectOfNeighbors[(NClr1-1)*NUMBER_OF_PIXELS+NPix1-1][ii].first;
     Int_t curNPix=fArrOfVectOfNeighbors[(NClr1-1)*NUMBER_OF_PIXELS+NPix1-1][ii].second;
     if (curNClr == NClr2 && curNPix == NPix2) return kTRUE;
  }
  return kFALSE;
}

Int_t TAIGACamera::GetNumberOfPixelNeighbors(Int_t NClr, Int_t NPix) const {
  return fArrOfVectOfNeighbors[(NClr-1)*NUMBER_OF_PIXELS+NPix-1].size();
}
void TAIGACamera::SetPixelXcor(Double_t xcor, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr-1].SetPixelXcor(xcor, NPix);
}
void TAIGACamera::SetPixelYcor(Double_t ycor, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr-1].SetPixelYcor(ycor, NPix);
}
void TAIGACamera::SetPixelAmp(Double_t amp, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr-1].SetPixelAmp(amp, NPix);
}
void TAIGACamera::SetIsPixelTriggered(Bool_t mod, Int_t NClr, Int_t NPix) {
  fArrOfClusters[NClr-1].SetIsPixelTriggered(mod, NPix);
}
Double_t TAIGACamera::GetPixelXcor(Int_t NClr, Int_t NPix) {
  return fArrOfClusters[NClr-1].GetPixelXcor(NPix);
}
Double_t TAIGACamera::GetPixelYcor(Int_t NClr, Int_t NPix) {
  return fArrOfClusters[NClr-1].GetPixelYcor(NPix);
}
Double_t TAIGACamera::GetPixelAmp(Int_t NClr, Int_t NPix) {
  return fArrOfClusters[NClr-1].GetPixelAmp(NPix);
}