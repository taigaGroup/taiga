//#include "TAIGARun.h"


TAIGACamera camera;
std::vector<TAIGAEvent> vectOfEvents;

void testRun()
{
  TAIGARun run;
  run.SetCameraFileName("/home/maria/Projects/taigaRoot/macro/test/data/xy_turn_2019s_EP.txt");
  cout << run.GetCameraFileName() << endl;
  run.readCamera(&camera);
  //camera.Print();
  
  run.SetEventsFileName("/home/maria/Projects/taigaRoot/macro/test/data/231119.out_005");
  run.readEvents(&vectOfEvents);

  cout << "NEvents is " << vectOfEvents.size() << endl;
  for (Int_t i=0; i<1; i++) {
    vectOfEvents[i].Print();
  }
  
  run.SetPedsFileName("/home/maria/TAIGA/191119.01/peds/191119.ped_001");
  run.removePeds(&vectOfEvents);
  
  
  for (Int_t i=0; i<1; i++) {
    vectOfEvents[i].Print();
  } 
  
  
  
}
