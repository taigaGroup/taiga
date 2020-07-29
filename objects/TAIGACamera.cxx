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
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS*NUMBER_OF_PIXELS; ii++)
    fArrOfVectOfNeighbors[ii].clear();
}

void TAIGACamera::Print() {
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS; ii++) {
    std::cout << "Cluster " << fArrOfClusters[ii].GetNCluster() << std::endl;
    std::cout << "NPixel" << setw(5) << "x" << setw(6) << "y " << setw(6) << "amp " << setw(7) << "trigg "
         << setw(10) << "NNeighbers" << std::endl;
    for (Int_t jj = 0; jj < NUMBER_OF_PIXELS; jj++) {
      TAIGAPixel curPixel=fArrOfClusters[ii].GetPixel(jj);
      std::cout << setw(6) << curPixel.GetNPixel() << " " << setw(3) << curPixel.GetXcor() << " "
           << setw(3) << curPixel.GetYcor() << " " << setw(5) << curPixel.GetAmp() << " "
           << setw(6) << curPixel.IsItTriggered() << " "
           << setw(10) << GetNumberOfPixelNeighbors(fArrOfClusters[ii].GetNCluster()-1, curPixel.GetNPixel()-1) << std::endl; // TODO why -1
    }
  }
}
void TAIGACamera::PrintNeighborsInfo() {
  for (Int_t ii = 0; ii < NUMBER_OF_CLUSTERS*NUMBER_OF_PIXELS; ii++) {
    std::cout << fArrOfVectOfNeighbors[ii].size() << std::endl;
  }
}
void TAIGACamera::AddPixelNeighbor(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2) {
  fArrOfVectOfNeighbors[NClr1*NUMBER_OF_PIXELS+NPix1].push_back(std::make_pair(NClr2, NPix2));
}

Bool_t TAIGACamera::are2PixelsNeighbors(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2) {
  if (GetNumberOfPixelNeighbors(NClr1, NPix1) < 1) return kFALSE;

  for (Int_t ii=0; ii<GetNumberOfPixelNeighbors(NClr1, NPix1);ii++) {
     Int_t curNClr=fArrOfVectOfNeighbors[NClr1*NUMBER_OF_PIXELS+NPix1][ii].first;
     Int_t curNPix=fArrOfVectOfNeighbors[NClr1*NUMBER_OF_PIXELS+NPix1][ii].second;
     if (curNClr == NClr2 && curNPix == NPix2) return kTRUE;
  }
  return kFALSE;
}

Int_t TAIGACamera::GetNumberOfPixelNeighbors(Int_t NClr, Int_t NPix) const {
  return fArrOfVectOfNeighbors[NClr*NUMBER_OF_PIXELS+NPix].size();
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
