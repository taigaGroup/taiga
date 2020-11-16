/* TAIGACamera class is an object for describing the camera detector in the TAIGA_IACT.
*/

// Author: Satyshev Ilyas. JINR

#ifndef TAIGACamera_H
#define TAIGACamera_H

#include <vector>
#include <utility> // std::pair, std::make_pair

#include "TObject.h"

#include "TAIGACluster.h"

class TAIGACamera : public TObject {
public:
  TAIGACamera();
  ~TAIGACamera();

  void Draw(); // TODO implement this one!
  void Print();
  void PrintNeighborsInfo();
  void AddPixelNeighbor(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2);

  Bool_t are2PixelsNeighbors(Int_t NClr1, Int_t NClr2, Int_t NPix1, Int_t NPix2);

  Int_t GetNumberOfPixelNeighbors(Int_t NClr, Int_t NPix) const;
  /** Modifiers **/
  void SetPixelXcor(Double_t xcor, Int_t NClr, Int_t NPix);
  void SetPixelYcor(Double_t ycor, Int_t NClr, Int_t NPix);
  void SetPixelAmp(Double_t amp, Int_t NClr, Int_t NPix);
  void SetIsPixelTriggered(Bool_t mod, Int_t NClr, Int_t NPix);
  /** Accessors **/
  Double_t GetPixelXcor(Int_t NClr, Int_t NPix);
  Double_t GetPixelYcor(Int_t NClr, Int_t NPix);
  Double_t GetPixelAmp (Int_t NClr, Int_t NPix);
  TAIGACluster GetCluster(Int_t NClr) const { return fArrOfClusters[NClr]; }
  TAIGAPixel GetPixel(Int_t NClr, Int_t NPix) const { return fArrOfClusters[NClr].GetPixel(NPix); }

private:
  TAIGACluster* fArrOfClusters;
  std::vector<std::pair<Int_t, Int_t>> fArrOfVectOfNeighbors[NUMBER_OF_CLUSTERS*NUMBER_OF_PIXELS];

  ClassDef (TAIGACamera,0);
};

#endif // TAIGACamera_H
