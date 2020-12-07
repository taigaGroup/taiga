//Macros for reading ampl, peds, sigma and operation with them
//Author is Maria L


#include <Riostream.h>
#include <TMath.h>
#include "TString.h"
#include <TMath.h>
#include "TString.h"
#include <TStyle.h>
#include <TDatime.h>
#include <TObject.h>

using namespace std;
using namespace TMath;

void GetAmpWithoutPed (Double_t n, Double_t Ncl, vector <double>& arr, vector <double>& amp) {  //number of clusters, #cluster, raw data, amp-ped//
   
   TString path = "/home/maria/TAIGA/191119.01/peds/191119.ped_001";  //FIXME path to the parameters: separate into dir and name
   
   ifstream in(path.Data());
  
   vector<double> vectofNc;
   vector<double> vectofNpix;
   vector<double> vectofPed;
   vector<double> vectofSigm;
   vector<double> vectofstat;
   vector <double> vectofampl;
   vector <double> vectoftrig;         
   double tmp1, tmp2, tmp3, tmp4, tmp5; 
   
   for(Int_t i=0; i<1408; i++) {
        
       in>>tmp1>>tmp2>>tmp3>>tmp4>>tmp5;
       vectofNc.push_back(tmp1);
       vectofNpix.push_back(tmp2);
       vectofPed.push_back(tmp3);
       vectofSigm.push_back(tmp4);
       vectofstat.push_back(tmp5);       
   }
   
   arr.clear();
   amp.clear();
   
     
   Double_t arrp[64], arrs[64];  // ped and sigma of ONE cluster
   const int nn = (Ncl-1)*64;
  
   for(Int_t i=0; i<64; i++) {
       arrp[i]=vectofPed[nn+i];
       arrs[i]=vectofSigm[nn+i];
                   
   } 
    
    
   if(n ==1) {
      for(Int_t i=4; i<122; i++) {
          if(i%2 ==0) {
             vectofampl.push_back(arr[i]);  
          }
          else {
             vectoftrig.push_back(arr[i]);
           
          }
      }
    
   } 
    
   if(n==2) {
      for(Int_t i=4; i<122; i++) {
          if(i%2 ==0) {
             vectofampl.push_back(arr[i]);  
          }
          else {
              vectoftrig.push_back(arr[i]);
          }
      }
      for(Int_t i=124; i<122+124; i++) {
          if(i%2 ==0) {
             vectofampl.push_back(arr[i]);  
          }
          else {
             vectoftrig.push_back(arr[i]);
          }
      } 
   }
          
          
   for(Int_t i=0; i<vectofampl.size(); i++) {
       amp.push_back(vectofampl[i] -arrp[i]);
   } 
    
    
}

//--------------------------------------------------------------------------------------------------------------//

unsigned int GetDate(string a) 
{   
     char* s = new char[a.length() + 1]; 
     strcpy(s, a.c_str());   
     char c;
     int year, month, day, hour, min, sec;
     sscanf(s,"%4d-%02d-%02d%1c%02d:%02d:%02d",&year,&month,&day,&c,&hour,&min,&sec);
     TDatime d(year,month,day,hour,min,sec);  
      
     return d.Convert();
} 

//--------------------------------------------------------------------------------------------------------------//


void taigaTestEvent()  {     
    
    
   //TString path = "/home/maria/TAIGA/191119.01/outs/"; 
   TString path ="/home/maria/";     //path to the directory
   TString name = "191119.out_001";  // name of file with data
       
   //TPair*  Apair;    
   TMap* map = new TMap();
   
   
   TString Fname_ = path + name;
  
   Int_t Ncl =0;   
   
   if (!path.EndsWith("/")) path += "/";

   void* dir = gSystem->OpenDirectory(path.Data());
       
   if (!dir) {
       cout <<endl<< "No such directory: " << path << endl;
       return;
   }
      
   std::ifstream f;
   f.open(Fname_.Data());
 
   if (!f.good()) {
       cout << "No such file : " << Fname_ << endl;
       f.close();
       return;
   }
   
   vector <double> vectofrd;   // raw data
   vector <double> vectofamp; // data at the end of the prog   

     
   const int DSIZE = 10000;
   char cstr[DSIZE];
   std::stringstream sdata;
   std::string str;
   std::string exp;
   int nstr = 0;
   int nperstr = 0;
   int n = 0;
         
   string* data = new string[50];
 
   while (f.getline(cstr,DSIZE)) {
 
          nstr++;
 
          sdata.clear();
          sdata.str(cstr);
 
          nperstr = 0;
            
          while (sdata >> str) {
     
               data[nperstr] = str;
               nperstr++;
          }
          
          TString time;
          
          if(nperstr == 1) {
             
             vectofrd.clear();
             Ncl = atof(data[0].c_str());
             vectofrd.push_back(atof(data[0].c_str()));
             
          } 
          if(nperstr == 3) {
            
             time = data[2];
             vectofrd.push_back(atof(data[0].c_str()));
             vectofrd.push_back(atof(data[1].c_str()));
             vectofrd.push_back(atof(data[2].c_str()));
          }
        
          else {
              for(Int_t i=0;i<nperstr;i++) {
                  vectofrd.push_back(atof(data[i].c_str()));
              }
            
          }
            
          if(vectofrd[0] ==1 && vectofrd.size()>126)  {             
 
              TObjString *s2 = new TObjString(time);  //this is a key of TMap
//             
              GetAmpWithoutPed (vectofrd[0],vectofrd[1], vectofrd, vectofamp);  //numb of cl, #clust, data, ampl-ped
              TAIGACamera cam;
              TAIGAEvent ev;
              map->Add(s2,cam);
              }
              //vector amp is essensial vector with ampl-ped.
              

          if(vectofrd[0] ==2 && vectofrd.size()>140 )  { 
                 
             TObjString *s2 = new TObjString(time);  //this is a key of TMap
             GetAmpWithoutPed (vectofrd[0],vectofrd[1], vectofrd, vectofamp); //numb of cl, #clust, data, ampl-ped
             TAIGACamera cam;
             TAIGAEvent ev;
//              map->Add(s2,cam);
             
             //vector amp is essensial vector with ampl-ped.
          }
   
    
}

   delete [] data;
   f.close();
}
