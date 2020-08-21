#include"TApplication.h"
#include<string>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<TROOT.h>
#include<TStyle.h>
#include<TGraph.h>
#include<TH1.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TAxis.h>
#include<TMath.h>
#include<TGaxis.h>
#define Nphe 500

Double_t sim_hist[Nphe];

Double_t resolution(Double_t *x,Double_t *par) {
  Int_t j;
  Double_t y=0,ed=x[0]+1;
  Double_t sigma=par[0]*TMath::Sqrt(10.0*ed);
  Double_t gauss,Kv=par[2]/TMath::Power(1.0+par[3]*x[0],2.0);
  for(j=1;j<Nphe;j++){
    gauss=TMath::Gaus(j,ed,sigma,kTRUE);
    y+=gauss*sim_hist[j-1];
  }
  y=(par[1]/Kv)*y;
  return y;
}

int main(int argc, char **argv){

  TApplication theApp("App",&argc,argv);
  char fname0[100],fname1[100];
  int j;
  Double_t pe[Nphe],exp_hist[Nphe];

  std::ifstream data0,data1;
  sprintf(fname0,"exp_hist.dat");
  data0.open(fname0);
  sprintf(fname1,"sim_hist.dat");
  data1.open(fname1);
  if(!data0 && !data1) {
    printf("file open error \n");
  }
  else{
    for(j=0;j<Nphe;j++){
      data0>>exp_hist[j];
      data1>>sim_hist[j];
      pe[j]=1.0*j;
    }
  }

  data0.close();
  data1.close();

  TGraph *gexp=new TGraph(Nphe,pe,exp_hist);
  TF1 *qmod=new TF1("qmod",resolution,0,100,4);
  qmod->SetParameter(0,0.1);
  qmod->SetParameter(1,0.01);
  qmod->SetParameter(2,0.1);
  qmod->SetParameter(3,0.1);
  gexp->Fit("qmod","R");
  gexp->SetFillColor(kBlue);
  gexp->Draw("AB");

  theApp.Run();
  return 0;
}
