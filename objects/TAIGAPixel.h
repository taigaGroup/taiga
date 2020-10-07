/* TAIGAPixel class is an object to describe a pixel from the TAIGA_IACT camera.
*/

// Author: Satyshev Ilyas. JINR

#ifndef TAIGAPixel_H
#define TAIGAPixel_H

#include <vector>
#include <utility> // std::pair, std::make_pair

#include "TObject.h"
#include "TString.h"

#include "TAIGAGlobalConstants.h"

class TAIGAPixel : public TObject {
public:
  TAIGAPixel();
  ~TAIGAPixel();

  /* Copy constructor */
  TAIGAPixel(const TAIGAPixel &pix);

  void Print(TString opt="");
  void Clear();

  /** Modifiers **/
  void SetNPixel(Int_t NPix) { fNPixel=NPix; }
  void SetXcor(Double_t xcor) { fXCor=xcor; }
  void SetYcor(Double_t ycor) { fYCor=ycor; }
  void SetAmp(Double_t amp) { fAmpl=amp; }
  void SetIsPixelTriggered(Bool_t mod) { fIsItTriggered=mod; }
  void AddNeighbor(Int_t NClr, Int_t NPix);

  /** Accessors **/
  Int_t GetNPixel() const { return fNPixel; }
  Int_t GetNumberOfNeighbors() const { return fVectOfNeighbors.size(); };
  Double_t GetXcor() const { return fXCor; }
  Double_t GetYcor() const { return fYCor; }
  Double_t GetAmp() const { return fAmpl; }
  Bool_t IsItTriggered() const { return fIsItTriggered; }
  Bool_t IsPixelNeighbor(Int_t NClr, Int_t NPix);

  TAIGAPixel* GetItSelf() { return this; } // TODO Is It necessary?
private:
  Int_t fNPixel=-1;
  Double_t fXCor=0.;
  Double_t fYCor=0.;
  Double_t fAmpl=0.;
  Bool_t fIsItTriggered=kFALSE;

  std::vector<std::pair<Int_t, Int_t>> fVectOfNeighbors;

  ClassDef (TAIGAPixel,1);
};

#endif // TAIGAPixel_H
