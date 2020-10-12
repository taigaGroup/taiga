/* TAIGACluster class is an object for describing clusters for the TAIGA_IACT camera.
*/

// Author: Satyshev Ilyas. JINR

#ifndef TAIGACluster_H
#define TAIGACluster_H

#include "TObject.h"

#include "TAIGAPixel.h"

class TAIGACluster : public TObject {
public:
  TAIGACluster();
  ~TAIGACluster();
    /* Copy constructor */
  TAIGACluster(const TAIGACluster &clr);
  void Print(TString opt="");
  void Clear();

  /** Modifiers **/
  void SetNCluster(Int_t NClr) { fNCluster=NClr; }
  void SetPixelXcor(Double_t xcor, Int_t NPix);
  void SetPixelYcor(Double_t ycor, Int_t NPix);
  void SetPixelAmp(Double_t amp, Int_t NPix);
  void SetIsPixelTriggered(Bool_t mod, Int_t NPix);
  /** Accessors **/
  Int_t GetNCluster() const { return fNCluster; }
  Double_t GetPixelXcor (Int_t NPix) const;
  Double_t GetPixelYcor(Int_t NPix) const;
  Double_t GetPixelAmp(Int_t NPix) const;
  TAIGAPixel GetPixel(Int_t NPix) const { return fArrOfPixels[NPix]; }
  Int_t GetNumberOfTriggeredPixels() const;
  Bool_t IsPixelTriggered(Int_t NPix) const;

private:
  Int_t fNCluster=-1;
  TAIGAPixel fArrOfPixels[NUMBER_OF_PIXELS];

  ClassDef (TAIGACluster,1);
};

#endif // TAIGACluster_H
