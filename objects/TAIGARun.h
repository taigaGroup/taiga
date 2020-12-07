/* TAIGARun class is an object to run processing.
*/

// Author: Satyshev Ilyas. JINR

#ifndef TAIGARun_H
#define TAIGARun_H

#include <vector>

#include "TObject.h"
#include "TString.h"


class TAIGACamera;
class TAIGAEvent;

class TAIGARun : public TObject
{
public:
  TAIGARun();
  ~TAIGARun();

  void SetCameraFileName(TString str) { cameraFileName=str; }
  void SetEventsFileName(TString str) { eventsFileName=str; }
  void SetPedsFileName  (TString str) { pedsFileName=str; }

  TString GetCameraFileName() { return cameraFileName; }
  TString GetEventsFileName() { return eventsFileName; }
  TString GetPedsFileName  () { return pedsFileName; }

  void readCamera(TAIGACamera *camera);
  void readEvents(std::vector<TAIGAEvent> *vectOfEvents);
  void removePeds(std::vector<TAIGAEvent> *vectOfEvents);

private:
  TString cameraFileName="";
  TString eventsFileName="";
  TString pedsFileName="";

  Bool_t cameraReadStatus=kTRUE;
  Bool_t eventsReadStatus=kTRUE;

	ClassDef (TAIGARun,1);
};

#endif // TAIGARun_H
