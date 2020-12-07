TAIGACamera camera;
std::vector<TAIGAEvent> vectOfEvents;
void testRun()
{
  TAIGARun run;
  run.SetCameraFileName("/home/ilyas/soft/taigaRoot/taiga/macro/test/data/xy_turn_2019s_EP.txt");
  cout << run.GetCameraFileName() << endl;
  run.readCamera(&camera);
  //camera.Print();
  
  run.SetEventsFileName("/home/ilyas/soft/taigaRoot/taiga/macro/test/data/231119.out_005");
  run.readEvents(&vectOfEvents);

  cout << "NEvents is " << vectOfEvents.size() << endl;
/*  for (Int_t i=0; i<vectOfEvents.size(); i++) {
    vectOfEvents[i].Print();
  }*/
}