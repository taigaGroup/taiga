/* This is a test macro for testing and debug TAIGACamera class.
*/

// Author: Satyshev Ilyas. JINR
void testCamera()
{
  TAIGACamera camera;
  Double_t curY=0.;
  Double_t dStep=3.;

  for (Int_t i=0; i<NUMBER_OF_CLUSTERS; i++) {
    Double_t curX=0.;
    for (Int_t j=0; j<NUMBER_OF_PIXELS; j++) {
      camera.SetPixelXcor(curX, i+1, j+1);
      camera.SetPixelYcor(curY, i+1, j+1);
      camera.SetPixelAmp((Double_t)(j+1), i+1, j+1);
      if ((i+1)%2 == 0 && (j+1)%2 == 0)
        camera.SetIsPixelTriggered(i+1, i+1, j+1);
      curX += dStep;
    }
    curY += dStep;
  }

  for (Int_t i=0; i<NUMBER_OF_CLUSTERS; i++) {
    for (Int_t j=0; j<NUMBER_OF_PIXELS; j++) {
      Double_t x1 = camera.GetPixelXcor(i+1, j+1);
      Double_t y1 = camera.GetPixelYcor(i+1, j+1);
      for (Int_t ii=0; ii<NUMBER_OF_CLUSTERS; ii++) {
        for (Int_t jj=0; jj<NUMBER_OF_PIXELS; jj++) {
          Double_t x2 = camera.GetPixelXcor(ii+1, jj+1);
          Double_t y2 = camera.GetPixelYcor(ii+1, jj+1);
          Double_t dx = x1-x2;
          Double_t dy = y1-y2;
          Double_t dist = sqrt(dx*dx + dy*dy);
          if (dist < MAX_DIST_BETWEEN_2_NEIGHBORS && dist > 0.) {
            camera.AddPixelNeighbor(i+1, ii+1, j+1, jj+1);
          }
        }
      }
    }
  }
  camera.Print();
}
