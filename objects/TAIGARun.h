/* TAIGARun class is an object to run processing.
*/

// Authors: Satyshev Ilyas, Maria L. JINR

#ifndef TAIGARun_H
#define TAIGARun_H

#include <vector>
#include "TObject.h"
#include "TString.h"
#include "Riostream.h"
#include <TMath.h>
#include <TMath.h>
#include <TStyle.h>

using namespace std;
using namespace TMath;


class TAIGACamera;
class TAIGAEvent;

class TAIGARun : public TObject
{
public:
	TAIGARun();
	~TAIGARun();

	void SetCameraFileName(TString str) { cameraFileName=str; }
	void SetEventsFileName(TString str) { eventsFileName=str; }
	void SetPedsFileName  (TString str) { pedsFileNmae=str; }

	TString GetCameraFileName() { return cameraFileName; }
	TString GetEventsFileName() { return eventsFileName; }
	TString GetPedsFileName  () { return pedsFileNmae; }
	
  void readCamera(TAIGACamera *camera);
  void readEvents(std::vector<TAIGAEvent> *vectOfEvents);
  void removePeds(std::vector<TAIGAEvent> *vectOfEvents);

private:
  TString cameraFileName="";
  TString eventsFileName="";
  TString pedsFileNmae="";

  Bool_t cameraReadStatus=kTRUE;
  Bool_t eventsReadStatus=kTRUE;
  
	ClassDef (TAIGARun,1);
};

#endif // TAIGARun_H
