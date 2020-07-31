void testEvent(Int_t rndIndex=0)
{
  std::vector<TAIGAEvent> vectOfEvents;
  gRandom->SetSeed(rndIndex);
  Int_t NEvents=10;

  for (Int_t ii = 0; ii < NEvents; ii++) {
    TAIGAEvent curEvent;
    curEvent.SetNEvent(ii+1);
    Int_t numberOfTriggClrs=gRandom->Integer(5)+1; // random integer [1-5]
    cout << "Event: " << ii+1 << ", numberOfTriggClrs: " << numberOfTriggClrs << endl;
    for (Int_t jj = 0; jj < numberOfTriggClrs; jj++) {
      TAIGACluster curCluster;
      Int_t NCurClr=gRandom->Integer(21)+1; // random integer [1-22]
      curCluster.SetNCluster(NCurClr);
      for (Int_t kk = 0; kk < NUMBER_OF_PIXELS; kk++) {
        curCluster.SetPixelAmp(4., kk);
        Double_t rnd=gRandom->Uniform(0., 1.);
        if (rnd < 0.3)
          curCluster.SetIsPixelTriggered(kTRUE, kk);
      }
      curEvent.AddCluster(curCluster);
    }
    vectOfEvents.push_back(curEvent);
  }

  for (Int_t ii = 0; ii < vectOfEvents.size(); ii++) {
    //vectOfEvents[ii].Print();
    vectOfEvents[ii].Print("trigg");
  }
}
